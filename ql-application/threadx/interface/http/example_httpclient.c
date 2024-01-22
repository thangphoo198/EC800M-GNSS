/*================================================================
  Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/
#include <stdio.h>
#include "ql_rtos.h"
#include "ql_data_call.h"
#include "ql_http_client.h"
#include "ql_application.h"
#include "ql_log.h"

#define PROFILE_IDX 1


#define PRINT_BUF_SIZE 65
static char print_buf[PRINT_BUF_SIZE];

void print_string(const char * string,int len)
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



static int response_cb(
	QL_HTTP_CLIENT_T *client,
	QL_HTTP_CLIENT_EVENT_E event,
	int status_code, 
	char *data, 
	int data_len, 
	void *private_data)
{
	int ret=0;
	char para[64]={0};
	switch(event)
	{
		case QL_HTTP_CLIENT_EVENT_SEND_FAIL:
			printf("http send failed!\n");
			break;
		case QL_HTTP_CLIENT_EVENT_SEND_SUCCESSED:
			printf("http send successed!\n");
			break;
		case QL_HTTP_CLIENT_EVENT_RECV_HEADER_FAIL:
			printf("http parse response header failed!\n");
			break;
		case QL_HTTP_CLIENT_EVENT_RECV_HEADER_FINISHED:
			printf("http recv header status_code:%d;header_len:%d!\n",status_code,data_len);
			print_string(data,data_len);
			ret=ql_http_client_get_header(data,"Content-Type",0,para,sizeof(para));
			if(ret>0)
				printf("Content-Type[len:%d]:%s!\n",ret,para);
			if(status_code==200)
				printf("http recv response ok!\n");
			ret=1; //继续接受body数据，返回0，不继续接受body数据
			break;
		case QL_HTTP_CLIENT_EVENT_RECV_BODY:
			printf("http recv body status_code:%d;recv_body_len:%d!\n",status_code,data_len);
			print_string(data,data_len);
			ret=1; //继续接受body数据，返回0，不继续接受body数据
			break;
		case QL_HTTP_CLIENT_EVENT_RECV_BODY_FINISHED:
			printf("http recv body finished!\n");
			break;
		case QL_HTTP_CLIENT_EVENT_DISCONNECTED:
			printf("http be closed by server!\n");
			break;
		default:
			break;
	}
	return ret;
}

static void ql_datacall_status_callback(int profile_idx, int status)
{
	printf("profile(%d) status: %d\r\n", profile_idx, status);
}

static int datacall_satrt(void)
{
	int i=0;
	printf("wait for network register done\r\n");

	while(i<10)
	{
		if(ql_network_register_wait(120) == 0)
		{
			break;
		}
		else 
		{
			i++;
		}
		
	}

	if(i>=10)
	{
		printf("*** network register fail ***\r\n");
		return 1;
	}
	
	printf("doing network activing ...\r\n");
	
	ql_wan_start(ql_datacall_status_callback);
	ql_set_auto_connect(1, TRUE);
	ql_start_data_call(1, 0, "3gnet.mnc001.mcc460.gprs", NULL, NULL, 0);

	return 0;
}

const static SSLCertPathPtr rootCA_path = 
"\
-----BEGIN CERTIFICATE-----\n\
MIIJrzCCCJegAwIBAgIMLO4ZPBiCeOo+Q3VzMA0GCSqGSIb3DQEBCwUAMGYxCzAJ\n\
BgNVBAYTAkJFMRkwFwYDVQQKExBHbG9iYWxTaWduIG52LXNhMTwwOgYDVQQDEzNH\n\
bG9iYWxTaWduIE9yZ2FuaXphdGlvbiBWYWxpZGF0aW9uIENBIC0gU0hBMjU2IC0g\n\
RzIwHhcNMTkwNTA5MDEyMjAyWhcNMjAwNjI1MDUzMTAyWjCBpzELMAkGA1UEBhMC\n\
Q04xEDAOBgNVBAgTB2JlaWppbmcxEDAOBgNVBAcTB2JlaWppbmcxJTAjBgNVBAsT\n\
HHNlcnZpY2Ugb3BlcmF0aW9uIGRlcGFydG1lbnQxOTA3BgNVBAoTMEJlaWppbmcg\n\
QmFpZHUgTmV0Y29tIFNjaWVuY2UgVGVjaG5vbG9neSBDby4sIEx0ZDESMBAGA1UE\n\
AxMJYmFpZHUuY29tMIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAtMa/\n\
2lMgD+pA87hSF2Y7NgGNErSZDdObbBhTsRkIsPpzRz4NOnlieGEuVDxJfFbawL5h\n\
VdVCcGoQvvW9jWSWIQCTYwmHtxm6DiA+SchT7QKPRgHroQeTc7vt8bPJ4vvd8Dkq\n\
g630QZi8huq6dKim49DlxY6zC7LSrJF0Dv+AECM2YmUItIf1VwwlxwDY9ahduDNB\n\
pypf2/pwniG7rkIWZgdp/hwmKoEPq3Pj1lIgpG2obNRmSKRv8mgKxWWhTr8EekBD\n\
HNN1+3WsGdZKNQVuz9Vl0UTKawxYBMSFTx++LDLR8cYo+/kmNrVt+suWoqDQvPhR\n\
3wdEvY9vZ8DUr9nNwwIDAQABo4IGGTCCBhUwDgYDVR0PAQH/BAQDAgWgMIGgBggr\n\
BgEFBQcBAQSBkzCBkDBNBggrBgEFBQcwAoZBaHR0cDovL3NlY3VyZS5nbG9iYWxz\n\
aWduLmNvbS9jYWNlcnQvZ3Nvcmdhbml6YXRpb252YWxzaGEyZzJyMS5jcnQwPwYI\n\
KwYBBQUHMAGGM2h0dHA6Ly9vY3NwMi5nbG9iYWxzaWduLmNvbS9nc29yZ2FuaXph\n\
dGlvbnZhbHNoYTJnMjBWBgNVHSAETzBNMEEGCSsGAQQBoDIBFDA0MDIGCCsGAQUF\n\
BwIBFiZodHRwczovL3d3dy5nbG9iYWxzaWduLmNvbS9yZXBvc2l0b3J5LzAIBgZn\n\
gQwBAgIwCQYDVR0TBAIwADBJBgNVHR8EQjBAMD6gPKA6hjhodHRwOi8vY3JsLmds\n\
b2JhbHNpZ24uY29tL2dzL2dzb3JnYW5pemF0aW9udmFsc2hhMmcyLmNybDCCA0kG\n\
A1UdEQSCA0AwggM8ggliYWlkdS5jb22CEmNsaWNrLmhtLmJhaWR1LmNvbYIQY20u\n\
cG9zLmJhaWR1LmNvbYIQbG9nLmhtLmJhaWR1LmNvbYIUdXBkYXRlLnBhbi5iYWlk\n\
dS5jb22CEHduLnBvcy5iYWlkdS5jb22CCCouOTEuY29tggsqLmFpcGFnZS5jboIM\n\
Ki5haXBhZ2UuY29tgg0qLmFwb2xsby5hdXRvggsqLmJhaWR1LmNvbYIOKi5iYWlk\n\
dWJjZS5jb22CEiouYmFpZHVjb250ZW50LmNvbYIOKi5iYWlkdXBjcy5jb22CESou\n\
YmFpZHVzdGF0aWMuY29tggwqLmJhaWZhZS5jb22CDiouYmFpZnViYW8uY29tgg8q\n\
LmJjZS5iYWlkdS5jb22CDSouYmNlaG9zdC5jb22CCyouYmRpbWcuY29tgg4qLmJk\n\
c3RhdGljLmNvbYINKi5iZHRqcmN2LmNvbYIRKi5iai5iYWlkdWJjZS5jb22CDSou\n\
Y2h1YW5rZS5jb22CCyouZGxuZWwuY29tggsqLmRsbmVsLm9yZ4ISKi5kdWVyb3Mu\n\
YmFpZHUuY29tghAqLmV5dW4uYmFpZHUuY29tghEqLmZhbnlpLmJhaWR1LmNvbYIR\n\
Ki5nei5iYWlkdWJjZS5jb22CEiouaGFvMTIzLmJhaWR1LmNvbYIMKi5oYW8xMjMu\n\
Y29tggwqLmhhbzIyMi5jb22CDiouaW0uYmFpZHUuY29tgg8qLm1hcC5iYWlkdS5j\n\
b22CDyoubWJkLmJhaWR1LmNvbYIMKi5taXBjZG4uY29tghAqLm5ld3MuYmFpZHUu\n\
Y29tggsqLm51b21pLmNvbYIQKi5zYWZlLmJhaWR1LmNvbYIOKi5zbWFydGFwcHMu\n\
Y26CESouc3NsMi5kdWFwcHMuY29tgg4qLnN1LmJhaWR1LmNvbYINKi50cnVzdGdv\n\
LmNvbYISKi54dWVzaHUuYmFpZHUuY29tggthcG9sbG8uYXV0b4IKYmFpZmFlLmNv\n\
bYIMYmFpZnViYW8uY29tggZkd3ouY26CD21jdC55Lm51b21pLmNvbYIMd3d3LmJh\n\
aWR1LmNughB3d3cuYmFpZHUuY29tLmNuMB0GA1UdJQQWMBQGCCsGAQUFBwMBBggr\n\
BgEFBQcDAjAdBgNVHQ4EFgQUdrXm1kn4+DbqdaltXk1VWzdc/ccwHwYDVR0jBBgw\n\
FoAUlt5h8b0cFilTHMDMfTuDAEDmGnwwggEEBgorBgEEAdZ5AgQCBIH1BIHyAPAA\n\
dgC72d+8H4pxtZOUI5eqkntHOFeVCqtS6BqQlmQ2jh7RhQAAAWqaLuGaAAAEAwBH\n\
MEUCICx7TcD5hUeKLQrAeTvWtLVm+Kr7glitIzb+Frymg5khAiEAwC/NnJkgy32R\n\
X9KLxhMQc7XBVAMzQZ+masUUk89pK2sAdgBvU3asMfAxGdiZAKRRFf93FRwR2QLB\n\
ACkGjbIImjfZEwAAAWqaLt5PAAAEAwBHMEUCIAMyaJ450OtfGWHbpxJpbyhEgQKl\n\
PMKjE9V+mCZfIBqgAiEAp4tis7C0RDLiEf9FjVURLDarKZNEyDRcznw1VzGuqxIw\n\
DQYJKoZIhvcNAQELBQADggEBAKq5zVKO3DZdR9SL8zIXBkaDYKMnBUkpsRtGbjj+\n\
k/4JQ2zSoVgkEkK3q0H4Rwp9ZLV13FpFFLKkGGuctzuPs37SvcBySzUFrg0tGR9Q\n\
c3Ja35cYO9sq895EzmQtwR6EzHYkPjBnIyboT/cL9uxp139RqaBvuMQU4sBKSsQA\n\
XVdqyUHEJSsyGKpiqB5JgXMcgV9e+uSUMsNQbY6qzGxMUwz6j040eZ+lYMD4UHW4\n\
oZ0B5qslIww7JAJAWCT/NAKLlGEQaC+2gOPQX0oKpwLSwJg+HegCyCdxJrKoh7bb\n\
nRBHS8ITYjTG0Dw5CTklj/6i9PP735snPfzQKOht3N0X0x8=\n\
-----END CERTIFICATE-----\n\
";

static void ql_http_client_test(void *arg)
{
    char private_data[]="hello world!";
    int response_code,run_num=0,ret=0;
    struct http_client * client = NULL;
    struct http_client_list * header = NULL;
	struct ql_data_call_info info = {0};
	char ip4_addr_str[16] = {0};
	char url[64]="https://www.baidu.com";
	char data[]="{uaername:test;password:test}";

	SSLConfig sslConfig = 
	{
		.en = 1,
		.profileIdx = PROFILE_IDX,
		.serverName = "www.baidu.com",
		.serverPort = 443,
		.protocol = 0,
		.dbgLevel = 3,
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
	
    ql_log_mask_set(QL_LOG_APP_MASK,QL_LOG_PORT_USB);

	if(datacall_satrt()!=0)
		return;

	ql_get_data_call_info(1, 0, &info);

	printf("info.profile_idx: %d\r\n", info.profile_idx);
	printf("info.ip_version: %d\r\n", info.ip_version);
	printf("info.v4.state: %d\r\n", info.v4.state);
	printf("info.v4.reconnect: %d\r\n", info.v4.reconnect);

	inet_ntop(AF_INET, &info.v4.addr.ip, ip4_addr_str, sizeof(ip4_addr_str));
	printf("info.v4.addr.ip: %s\r\n", ip4_addr_str);

	inet_ntop(AF_INET, &info.v4.addr.pri_dns, ip4_addr_str, sizeof(ip4_addr_str));
	printf("info.v4.addr.pri_dns: %s\r\n", ip4_addr_str);

	inet_ntop(AF_INET, &info.v4.addr.sec_dns, ip4_addr_str, sizeof(ip4_addr_str));
	printf("info.v4.addr.sec_dns: %s\r\n", ip4_addr_str);

	
    ql_rtos_task_sleep_s(5); 
    client = ql_http_client_init();
	while (client&&(run_num<10)) 
	{
		
		printf("\n\n==============http_client_test[%d]================\n",run_num);
		

		ret=ql_http_client_setopt(client, QL_HTTP_CLIENT_OPT_PDP_CID, PROFILE_IDX);              /*set PDP cid,if not set,using default PDP*/
		ret=ql_http_client_setopt(client, QL_HTTP_CLIENT_OPT_PROTOCOL_VER, 1);              /*"0" is HTTP 1.1, "1" is HTTP 1.0*/

		ret=ql_http_client_setopt(client, QL_HTTP_CLIENT_OPT_ENABLE_COOKIE, 1);              /*"0" is HTTP 1.1, "1" is HTTP 1.0*/
		printf("ql_http_client_setopt: QL_HTTP_CLIENT_OPT_ENABLE_COOKIE    ret :%d  \n",ret);

		ret=ql_http_client_setopt(client, QL_HTTP_CLIENT_OPT_SSL_CTX, &sslConfig);

		if(run_num==3)
        	header=ql_http_client_list_append(header, "Connection: keep-alive\r\n");
		
		ret=ql_http_client_setopt(client, QL_HTTP_CLIENT_OPT_HTTPHEADER, header);
		if(ret==QL_HTTP_CLIENT_ERR_LAST_REQUEST_NOT_FINISH)
		{
			printf("last request not finish, not to set!\n");
		}
		
		ret=ql_http_client_request(client,url,QL_HTTP_CLIENT_REQUEST_GET,QL_HTTP_CLIENT_AUTH_TYPE_NONE,NULL,NULL,NULL,0,response_cb,private_data);
		if(ret==QL_HTTP_CLIENT_ERR_LAST_REQUEST_NOT_FINISH)
		{
			printf("last request not finish, can not to request again!\n");
		}
		
		printf("ql_http_client_request ret=%d!\n",ret);
		
		printf("\n\n==============http_client_test[%d] end================\n",run_num);
		run_num++;
		ql_rtos_task_sleep_s(5);
	}
	ql_http_client_release(client); /*release http resources*/
}

//application_init(ql_http_client_test, "ql_http_client_test", 10, 2);


