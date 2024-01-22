/*================================================================
  Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/
#include "ql_power.h"
#include "ql_data_call.h"
#include "sockets.h"
#include <stdio.h>
#include "ql_application.h"
#include "ql_fota.h"
#include "ql_http_client.h"
#include "ql_ftp_client.h"

#define fota_exam_log(fmt, ...) printf("[FOTA_EXAM][%s, %d] "fmt"\r\n", __FUNCTION__, __LINE__, ##__VA_ARGS__)

#define HTTP_FOTA_TEST 1
#define PROFILE_IDX 1
#define FOTA_SSL_EN 0

QL_HTTP_CLIENT_T* fota_httpclient = NULL;
void * fota_ftpclient = NULL;
int fota_process = 0;

qlFotaImgProcCtxPtr ctx = NULL;
static qlFotaProgressCB_t fota_progress_cb = NULL;
int total_len = 0;

#define PRINT_BUF_SIZE 65
static char print_buf[PRINT_BUF_SIZE];

static void print_string(const char * string,int len)
{
	int printed = 0;
	while (printed != len) 
	{
		if ((len - printed) > (PRINT_BUF_SIZE - 1)) 
		{
			memcpy(print_buf, string + printed, (PRINT_BUF_SIZE - 1));
			printed += (PRINT_BUF_SIZE - 1);
			print_buf[PRINT_BUF_SIZE - 1] = '\0';
		} 
		else 
		{
			snprintf(print_buf,len - printed+1, "%s", string + printed);
			printed = len;
		}
		printf("%s", print_buf);
	}
	printf("\n");
}

static int http_response_cb(
    QL_HTTP_CLIENT_T *client,
    QL_HTTP_CLIENT_EVENT_E event,
    int status_code, 
    char *data, 
    int data_len, 
    void *private_data)
{
    int ret=0,write_ret=0;
    char para[64]={0};
    
    static int recv_len = 0;
    switch(event)
    {
        case QL_HTTP_CLIENT_EVENT_SEND_FAIL:
            fota_exam_log("http send failed!\n");
            fota_process =-1;
            break;
        case QL_HTTP_CLIENT_EVENT_SEND_SUCCESSED:
            fota_exam_log("http send successed!\n");
            break;
        case QL_HTTP_CLIENT_EVENT_RECV_HEADER_FAIL:
            fota_exam_log("http parse response header failed!\n");
            fota_process = -1;
            break;
        case QL_HTTP_CLIENT_EVENT_RECV_HEADER_FINISHED:
            fota_exam_log("http recv header status_code:%d;header_len:%d!\n",status_code,data_len);
            print_string(data,data_len);
            ret=ql_http_client_get_header(data,"Content-Length",0,para,sizeof(para));
            total_len = atoi(para);
            if(ret>0)
                fota_exam_log("Content-length[]:%d!\n",total_len);
            if(status_code==200)
                fota_exam_log("http recv response ok!\n");
            ret=1; //继续接受body数据，返回0，不继续接受body数据
            break;
        case QL_HTTP_CLIENT_EVENT_RECV_BODY:
            fota_exam_log("http recv body status_code:%d;recv_body_len:%d!\n",status_code,data_len);
            print_string(data,data_len);
            
            recv_len+=data_len;
            write_ret = ql_fota_image_write(ctx, (void *)data, data_len);
            fota_exam_log("write_ret:%d",write_ret);
    		if(write_ret)
    		{
    			fota_exam_log("*** fota image write fail ***");
    			ret =0;
    			break;
    		}
    		if(total_len>0)
    		    fota_process = ((recv_len*100) /total_len); 
		    if(fota_progress_cb)
		        fota_progress_cb(QL_FOTA_INPROGRESS, fota_process);
            ret=1; //继续接受body数据，返回0，不继续接受body数据
            break;
        case QL_HTTP_CLIENT_EVENT_RECV_BODY_FINISHED:
        #if 1
            if(fota_progress_cb)
			    fota_progress_cb(QL_FOTA_SUCCEED, 100);
			fota_process = 100;
            ret = ql_fota_image_flush(ctx);
        	if(ret)
        	{
        		fota_exam_log("*** fota image flush fail ***");
        	}
        	ret = ql_fota_image_verify(ctx);
    		if(ret)
    		{
    			fota_exam_log("*** fota image verify fail ***");
    			break;
    		}
            if(fota_progress_cb)
              fota_progress_cb(QL_FOTA_SETFLAG, 100);
        #endif
            fota_exam_log("http recv body finished!\n");
            break;
        case QL_HTTP_CLIENT_EVENT_DISCONNECTED:
            fota_exam_log("http be closed by server!\n");
            fota_process =-1;
            break;
        default:
            break;
    }
    return ret;
}

int ftp_write_data(unsigned char *data,int data_len,void*user_data)
{
    int ret = 0;
    static int writen_len = 0;
    
    ret = ql_fota_image_write(ctx, (void *)data, data_len);
    fota_exam_log("write_ret:%d",ret);
	if(ret)
	{
		fota_exam_log("*** fota image write fail ***");
		 if(fota_progress_cb)
		    fota_progress_cb(QL_FOTA_FAIL, -1);
		 fota_process = -1;
		return -1;
	}
	
	writen_len += data_len;
	fota_process =(writen_len*100) /total_len;
	if(writen_len == total_len)
	{
        if(fota_progress_cb)
            fota_progress_cb(QL_FOTA_SUCCEED, 100);
        ret = ql_fota_image_flush(ctx);
        if(ret)
        {
            fota_exam_log("*** fota image flush fail ***");
        }
        ret = ql_fota_image_verify(ctx);
        if(ret)
        {
            fota_exam_log("*** fota image verify fail ***");
            if(fota_progress_cb)
		         fota_progress_cb(QL_FOTA_FAIL, -1);
            return -1;
        }
        if(fota_progress_cb)
              fota_progress_cb(QL_FOTA_SETFLAG, 100);
	}
	else 
	{
        if(fota_progress_cb)
		  fota_progress_cb(QL_FOTA_INPROGRESS, fota_process);
	}
	return 1;
}
static int parse_ftp_url(char * address, char hostname[],char pathname[],char filename[])
{
    const char * data = address;
    char * pos = NULL;
   // If prefix is 'ftp://' ?
	if (!memcmp(data, "ftp", 3)) {
		if (*(data + 3) == 's') {
			// ftps ?
			if (!memcmp(data, "ftps://", 7)) {
				data += 7;
			}
		} else if (*(data + 3) == ':') {
			if (!memcmp(data, "ftp://", 6)) {
				data += 6;
			}
		}
	}
	fota_exam_log("Set url raw data:%s",data);
	if((*data == '[')&&(strstr(data, "]:")))
	{
		fota_exam_log("host ipv6 addr");
	}
	pos = strrchr(data, '/');
    if (pos == NULL) {
        fota_exam_log("ftp url is not match");
    } else {
        fota_exam_log("pos,%s",pos);
        memcpy(filename, pos+1, strlen( pos+1));
        *pos = '\0'; // Set pathname value end
    }
    pos = strchr(data, '/');
    if (pos == NULL) {
        fota_exam_log("ftp url is not match");
    } else {
        memcpy(pathname, pos, strlen( pos));
    }
    
    memcpy(hostname, data, pos-data);
    fota_exam_log("host: %s", hostname);
    fota_exam_log("filename: %s", filename);
    fota_exam_log("subpathname: %s", pathname);

	
}

int ql_fota_get_progress(void)
{
	return fota_process;
}

void ql_fota_ssl_config(SSLConfig * sslCfg)
{
    #if HTTP_FOTA_TEST
	fota_httpclient = ql_http_client_init();
    ql_http_client_setopt(fota_httpclient, QL_HTTP_CLIENT_OPT_SSL_CTX, sslCfg);
    #else 
    fota_ftpclient = ql_ftp_client_new();
    ql_ftp_client_setopt(fota_ftpclient, QL_FTP_CLIENT_OPT_SSL_CTX,sslCfg);
    #endif
    return ;
}


int ql_fota_firmware_download(int profile_idx, qlFotaDwnldMod mode, char * address, char * username, char * password, qlFotaProgressCB_t cb)
{
    int ret=0;
   
    ctx = ql_fota_init();
	if(!ctx)
	{
		fota_exam_log("*** fota init fail ***");
		goto exit;
	}
	
    fota_progress_cb = cb;
    fota_process = 0;

	if(mode == QL_FOTA_DWNLD_MOD_HTTP)
	{
	    if(!fota_httpclient)
            fota_httpclient = ql_http_client_init();
        
	    ql_http_client_setopt(fota_httpclient, QL_HTTP_CLIENT_OPT_ASYN, 0); //同步模式
        ql_http_client_setopt(fota_httpclient, QL_HTTP_CLIENT_OPT_PDP_CID, profile_idx);
        ql_http_client_setopt(fota_httpclient, QL_HTTP_CLIENT_OPT_PROTOCOL_VER, 1); 
        fota_exam_log("fota_client:%p address:%s",fota_httpclient,address);
        ql_http_client_request(fota_httpclient,address,QL_HTTP_CLIENT_REQUEST_GET,QL_HTTP_CLIENT_AUTH_TYPE_NONE,username,password,NULL,0,http_response_cb,NULL);

        if(fota_httpclient)
            ql_http_client_release(fota_httpclient);

	}
	else if(mode ==QL_FOTA_DWNLD_MOD_FTP)
	{
	    QL_FTP_CLIENT_FLIE_INFO_T file_list[1]={0};
	    char hostname[64] = {0};
	    char pathname[256] = {0};
	    char filename[256] = {0};
	    char buf[256] = {0};
	    
        if(!fota_ftpclient)
            fota_ftpclient = ql_ftp_client_new();

        parse_ftp_url(address, hostname,pathname,filename);
        ret=ql_ftp_client_setopt(fota_ftpclient, QL_FTP_CLIENT_OPT_PDP_CID, profile_idx);
        ret=ql_ftp_client_open(fota_ftpclient,hostname,username,password);
        printf("\nql_ftp_client_open[%s] ret=%d;\n",hostname,ret);
		if(ret==-1)
		{
			printf("ql_ftp_client_open error_code=%d\n",ql_ftp_client_get_error_code(fota_ftpclient));
		}
		ret=ql_ftp_client_pwd(fota_ftpclient, buf, sizeof(buf)); 
		printf("\nql_ftp_client_pwd ret=%d; remotedir:%s\n",ret,buf);
		
    	ret=ql_ftp_client_list(fota_ftpclient, pathname,filename,file_list, 1);
		printf("\nql_ftp_client_list[%s] ret=%d file_list[0].size:%d\n",filename,ret,file_list[0].size);
		total_len = file_list[0].size;

        ret=ql_ftp_client_cwd(fota_ftpclient, pathname);
        printf("\nql_ftp_client_cwd[%s] ret=%d\n",pathname, ret);
                
        ret= ql_ftp_client_get(fota_ftpclient,filename,NULL,ftp_write_data,NULL);
        printf("\nql_ftp_client_get ret:%d",ret);

        ql_rtos_task_sleep_s(2);
        ql_ftp_client_release(fota_ftpclient);

	}

	exit:

	    if(ctx) ql_fota_deinit(ctx);
	
}


#if FOTA_SSL_EN
#define FOTA_SERVER_ADDRESS "https://220.180.239.212:8059/Jacinda/dfota.bin"

const static SSLCertPathPtr rootCA_path = 
"\
-----BEGIN CERTIFICATE-----\n\
MIIE5zCCA0+gAwIBAgIJANUsoTOuGtIeMA0GCSqGSIb3DQEBCwUAMIGJMQswCQYD\n\
VQQGEwJDTjELMAkGA1UECAwCQUgxCzAJBgNVBAcMAkhGMRAwDgYDVQQKDAdRVUVD\n\
VEVMMQwwCgYDVQQLDANEVFcxGDAWBgNVBAMMDzIyMC4xODAuMjM5LjIxMjEmMCQG\n\
CSqGSIb3DQEJARYXZWRkaWUuemhhbmdAcXVlY3RlbC5jb20wHhcNMjAwMTAyMTEy\n\
NTQzWhcNMjMwMTAxMTEyNTQzWjCBiTELMAkGA1UEBhMCQ04xCzAJBgNVBAgMAkFI\n\
MQswCQYDVQQHDAJIRjEQMA4GA1UECgwHUVVFQ1RFTDEMMAoGA1UECwwDRFRXMRgw\n\
FgYDVQQDDA8yMjAuMTgwLjIzOS4yMTIxJjAkBgkqhkiG9w0BCQEWF2VkZGllLnpo\n\
YW5nQHF1ZWN0ZWwuY29tMIIBojANBgkqhkiG9w0BAQEFAAOCAY8AMIIBigKCAYEA\n\
tDYkNFB5TYS7XZ2F+eW6zGWOmy2xV3OcTpnz10JHUwSdvUI5xWQ//ACCxG9QeN4f\n\
ALAzkj8tVzeKj5oP9Gz8LnVqhIxv13m8GJDO/dVZEXtpBNgjv7DvsXa1TMjy3QcV\n\
bXfqtWuTSzVCovMkvj+R16uWRWgqSMLCG73FLPE2E2vRGlBQVzAVi2fXYPq346QT\n\
ZLyELoFErGCFgVEaAF1Pnwu1R8Ly0CI45y/riC47Sb3bE/MaBUbR0R7+T5jhnK8G\n\
E0GTLorOZq6CBf8NliRjnEQVtjhUniQju1Dx/35Tifel460kK9ThkmxEddn1w+VH\n\
ZQYG9XWuqdPA6am5rBI+AKUCPeoMRVVlY3lK3J7L4OyRTovY0+IyVT4MKucrzK4z\n\
FfnACTgKr151yMxY3Ar4EPI1iQeuKu5Ha2bZuXLnVZau8NohbdUXBSN+ifPH2uu7\n\
BT91jG6zfS9k6AKhBkGncf0dpuT9c6w06UAplxeakSpnSz5p7O9XGeAZeemahq43\n\
AgMBAAGjUDBOMB0GA1UdDgQWBBSHgJS+a77WT6PHLTVoW+qqVK80uTAfBgNVHSME\n\
GDAWgBSHgJS+a77WT6PHLTVoW+qqVK80uTAMBgNVHRMEBTADAQH/MA0GCSqGSIb3\n\
DQEBCwUAA4IBgQA6WSdvLq+MMmNJAAI8XCANzWq69fxcrvRhLl69hipueomivrFx\n\
cqiG6oI38CBxqiPC9y69fXBY9B7f29emMHnjpC5xoOqfBSVKqR+EbhYUx/n0/Ykx\n\
Pcz6Lad0/8JRLa0QthhnLzMPpeAY7Z3HmcHR0mZFu+vu0irw/3E1GkDm2MQ2958Y\n\
5geLGbktFKF2yGueajcoR8qSmeD+tspBqTWqmdPaDEipPNBvLduOzcGqOnQMKy4/\n\
LLQMZ/OuXTjuJjYE4YtN2wV3/ks02Ae94FE8ZaaMYThMHBz4NITKbLhbMn9cP66w\n\
27B+nt5+DG4zc9AYZRuKhaW6AiMfAewAvFxIyofmPxAKMpC+JBwzDxdbo0ez/Dqr\n\
CFbKuQeWAY3YwgG33pdzOuREMphdGZnJgkd1MqUCNFxMGnZF6WhV31I/e1+uCMYr\n\
4Rw86GtDfs697qxBOXHmNBVqLLekayQxGh7d2UxIVghdCuO6rHjTfmkfvzNH/Vxf\n\
t/YY6UlQvij187Q=\n\
-----END CERTIFICATE-----\n\
";

#else
#define FOTA_SERVER_ADDRESS 	 "http://220.180.239.212:8300/fawei/fbf_dfota.bin"
#define FOTA_FTP_SERVER_ADDRESS  "ftp://220.180.239.212:8309/fawei/fbf_dfota.bin"
#endif

#define FOTA_SERVER_USERNAME NULL
#define FOTA_SERVER_PASSWD NULL

#define FOTA_FTP_SERVER_USERNAME "test"
#define FOTA_FTP_SERVER_PASSWD   "test"


static void qlFotaProgressCB(qlFotaSta sta, int progress)
{
	if(sta == QL_FOTA_INPROGRESS)
	{
		fota_exam_log("fota test downloading (%d)%d ...", sta, progress);
	}
	else if(sta == QL_FOTA_SUCCEED)
	{
		fota_exam_log("fota test downloading (%d)%d ...", sta, progress);
	}
	else if(sta == QL_FOTA_SETFLAG)
	{
		fota_exam_log("fota test update flag setted, will restart to update ...");
		//ql_power_reset();
	}
	else if(sta == QL_FOTA_FAIL)
	{
		fota_exam_log("fota test download failed (%d)%d", sta, progress);
		fota_exam_log("========== fota test end ==========");
	}
}

static void ql_nw_status_callback(int profile_idx, int nw_status)
{
	fota_exam_log("profile(%d) status: %d", profile_idx, nw_status);
}

static int datacall_satrt(void)
{
	struct ql_data_call_info info = {0};
	char ip4_addr_str[16] = {0};
	
	fota_exam_log("wait for network register done");

	if(ql_network_register_wait(120) != 0)
	{
		fota_exam_log("*** network register fail ***");
		return -1;
	}
	else
	{
		fota_exam_log("doing network activating ...");
		
		ql_wan_start(ql_nw_status_callback);
		ql_set_auto_connect(PROFILE_IDX, TRUE);
		if(ql_start_data_call(PROFILE_IDX, 0, "3gnet.mnc001.mcc460.gprs", NULL, NULL, 0) == 0)
		{
			ql_get_data_call_info(PROFILE_IDX, 0, &info);
			
			fota_exam_log("info.profile_idx: %d", info.profile_idx);
			fota_exam_log("info.ip_version: %d", info.ip_version);
			fota_exam_log("info.v4.state: %d", info.v4.state);
			fota_exam_log("info.v4.reconnect: %d", info.v4.reconnect);
			
			inet_ntop(AF_INET, &info.v4.addr.ip, ip4_addr_str, sizeof(ip4_addr_str));
			fota_exam_log("info.v4.addr.ip: %s", ip4_addr_str);
			
			inet_ntop(AF_INET, &info.v4.addr.pri_dns, ip4_addr_str, sizeof(ip4_addr_str));
			fota_exam_log("info.v4.addr.pri_dns: %s", ip4_addr_str);
			
			inet_ntop(AF_INET, &info.v4.addr.sec_dns, ip4_addr_str, sizeof(ip4_addr_str));
			fota_exam_log("info.v4.addr.sec_dns: %s", ip4_addr_str);

			return 0;
		}

		fota_exam_log("*** network activated fail ***");
		return -1;
	}
}


static void httpfotaTest(void *argv)
{
	(void)argv;
    fota_exam_log("========== fota test satrt22222222222222222222 ==========");

	fota_exam_log("========== fota test satrt ==========");

	if(datacall_satrt() == 0)
	{
	#if FOTA_SSL_EN
		SSLConfig sslConfig = 
		{
			.en = 1,
			.profileIdx = PROFILE_IDX,
			.serverName = "220.180.239.212",
			.serverPort = 8059,
			.protocol = 0,
			.dbgLevel = 0,
			.sessionReuseEn = 0,
			.vsn = SSL_VSN_ALL,
			.verify = SSL_VERIFY_MODE_OPTIONAL,
			.cert.from = SSL_CERT_FROM_BUF,
			.cert.path.rootCA = rootCA_path,
			.cert.path.clientKey = NULL,
			.cert.path.clientCert = NULL,
			.cert.clientKeyPwd.data = NULL,
			.cert.clientKeyPwd.len = 0,
			.cipherList = "ALL",
			.CTRDRBGSeed.data = NULL,
			.CTRDRBGSeed.len = 0
		};
		ql_fota_ssl_config(&sslConfig);
	#endif
		
		fota_exam_log("ql_fota_firmware_download enter");
	#if HTTP_FOTA_TEST
		ql_fota_firmware_download(PROFILE_IDX, QL_FOTA_DWNLD_MOD_HTTP, FOTA_SERVER_ADDRESS, FOTA_SERVER_USERNAME, FOTA_SERVER_PASSWD, qlFotaProgressCB);
    #else
		ql_fota_firmware_download(PROFILE_IDX, QL_FOTA_DWNLD_MOD_FTP, FOTA_FTP_SERVER_ADDRESS, FOTA_FTP_SERVER_USERNAME, FOTA_FTP_SERVER_PASSWD, qlFotaProgressCB);
    #endif
	}
	else
		fota_exam_log("========== fota test end ==========");
}

//application_init(httpfotaTest, "httpfotaTest", 10, 2);

