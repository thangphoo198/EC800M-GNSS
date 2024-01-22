/*================================================================
  Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/
#include "ql_rtos.h"
#include "ql_fs.h"
#include "sockets.h"
#include "ql_data_call.h"
#include "ql_ftp_client.h"
#include "ql_application.h"
#include "ql_log.h"
#define PROFILE_IDX 1

#define TEST_FILE_NAME				"test.txt"
#define TEST_DEVICE_FILE_NAME		"test_device.txt"

#define U_DISK						"U:"
#define U_ROOT_PATH					""U_DISK"/"
#define U_FILE_TEST_FILE 			""U_DISK"/"TEST_FILE_NAME""
#define U_FILE_TEST_DEVICE_FILE 	""U_DISK"/"TEST_DEVICE_FILE_NAME""

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
	ql_set_auto_connect(PROFILE_IDX, TRUE);
	ql_start_data_call(PROFILE_IDX, 0, "3gnet.mnc001.mcc460.gprs", NULL, NULL, 0);

	return 0;
}

char data_tmp[]="hello\n";
int read_data_count=0;
int read_data(unsigned char *data,int data_len,void*user_data)
{
	memcpy(data,data_tmp,sizeof(data_tmp));
	if(read_data_count++<30)
		return sizeof(data_tmp);
	else
		return 0;
}
#define PRINT_BUF_SIZE 65
static char print_buf[PRINT_BUF_SIZE];
int write_data(unsigned char *data,int data_len,void*user_data)
{

	int printed = 0;
	while (printed != data_len) 
	{
		if ((data_len - printed) > (PRINT_BUF_SIZE - 1)) 
		{
			memcpy(print_buf, data + printed, (PRINT_BUF_SIZE - 1));
			printed += (PRINT_BUF_SIZE - 1);
			print_buf[PRINT_BUF_SIZE - 1] = '\0';
		} 
		else 
		{
			snprintf(print_buf,data_len - printed+1, "%s", data + printed);
			printed = data_len;
		}
		printf("\r\n%s\r\n", print_buf);
	}
	return 1;
}


static void ql_ftp_client_test(void *arg)
{
    char buf[256]={0};
    int response_code,run_num=0,ret=0,i=0;
    void * client = NULL;
	struct ql_data_call_info info = {0};
	char ip4_addr_str[16] = {0};
	char hostname[64]="220.180.239.212:8309";
	char username[]="test";
	char password[]="test";
	QL_FTP_CLIENT_FLIE_INFO_T file_list[5]={0};
	FILE_ID * fp = NULL;
	
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
    client = ql_ftp_client_new();
	while (client&&(run_num<10000)) 
	{
		read_data_count=0;
		printf("\n\n==============ftp_client_test[%d]================\n",run_num);
		
		ret=ql_ftp_client_setopt(client, QL_FTP_CLIENT_OPT_PDP_CID, PROFILE_IDX);              /*set PDP cid,if not set,using default PDP*/
		
		ret=ql_ftp_client_open(client,hostname,username,password);
		printf("\nql_ftp_client_open[%s] ret=%d;\n",hostname,ret);
		if(ret==-1)
		{
			printf("ql_ftp_client_open error_code=%d\n",ql_ftp_client_get_error_code(client));
		}

		ret=ql_ftp_client_pwd(client, buf, sizeof(buf));
		printf("\nql_ftp_client_pwd ret=%d; remotedir:%s\n",ret,buf);

		ret=ql_ftp_client_mkdir(client, "ftptest");
		printf("\nql_ftp_client_mkdir[ftptest] ret=%d\n",ret);

		ret=ql_ftp_client_cwd(client, "ftptest");
		printf("\nql_ftp_client_cwd[ftptest] ret=%d\n",ret);

		ret=ql_ftp_client_pwd(client, buf, sizeof(buf));
		printf("\nql_ftp_client_pwd ret=%d; remotedir:%s\n",ret,buf);

		ret=ql_ftp_client_cwd(client, "/");
		printf("\nql_ftp_client_cwd[/] ret=%d\n",ret);

		ret=ql_ftp_client_rmdir(client, "ftptest");
		printf("\nql_ftp_client_rmdir[ftptest] ret=%d\n",ret);

		ret=ql_ftp_client_list(client, "/fawei_test",NULL,file_list, 5);
		printf("\nql_ftp_client_list[/fawei_test] ret=%d\n",ret);
		for(i=0;i<ret;i++)
		{
			printf("file%d:%s\n   type:%d\n   size:%d\n   group:%s\n   permissions:%d\n   time:%04d-%02d-%02d %02d:%02d:%02d\n",i,
				file_list[i].filename,
				file_list[i].type, 
				file_list[i].size,
				file_list[i].group,
				file_list[i].permissions,
				file_list[i].timestamp.tm_year+1900,
				file_list[i].timestamp.tm_mon+1,
				file_list[i].timestamp.tm_mday,
				file_list[i].timestamp.tm_hour,
				file_list[i].timestamp.tm_min,
				file_list[i].timestamp.tm_sec
				);
		}



		ret=ql_ftp_client_list(client, "/fawei_test","test3.txt",file_list, 1);
		printf("\nql_ftp_client_list[/fawei_test/test3.txt] ret=%d\n",ret);
		for(i=0;i<ret;i++)
		{
			printf("file%d:%s\n   type:%d\n   size:%d\n   group:%s\n   permissions:%d\n   time:%04d-%02d-%02d %02d:%02d:%02d\n",i,
				file_list[i].filename,
				file_list[i].type, 
				file_list[i].size,
				file_list[i].group,
				file_list[i].permissions,
				file_list[i].timestamp.tm_year+1900,
				file_list[i].timestamp.tm_mon+1,
				file_list[i].timestamp.tm_mday,
				file_list[i].timestamp.tm_hour,
				file_list[i].timestamp.tm_min,
				file_list[i].timestamp.tm_sec
				);
		}
        ret=ql_ftp_client_cwd(client, "/fawei_test");
        printf("\nql_ftp_client_cwd[/fawei_test] ret=%d\n",ret);

		ret= ql_ftp_client_get(client,"test.txt",NULL,write_data,NULL);
		printf("\nql_ftp_client_get[test.txt->test.txt] ret=%d\n",ret);

		fp = ql_fopen(U_FILE_TEST_DEVICE_FILE, "wb+");
		if(fp)
		{
			printf("open: %s\n",U_FILE_TEST_DEVICE_FILE);
			ql_fclose(fp);
		}
		else
		{
			printf("ql_fopen failed\n");
		}

		ret= ql_ftp_client_get(client,"test.txt",U_FILE_TEST_DEVICE_FILE,NULL,NULL);
		printf("\nql_ftp_client_get[test.txt->test_device.txt] ret=%d\n",ret);

		fp = ql_fopen(U_FILE_TEST_DEVICE_FILE, "rb");
		if(fp)
		{
			printf("ql_fread start\n");
			while(1)
			{
				int n=ql_fread(buf,65, 1,fp);
				
				if(n>0)
				{
					buf[n]=0;
					printf("%s",buf);
				}
				else
				{
					printf("\nql_fread end\n");
					break;
				}
			}
			ql_fclose(fp);
		}
		else
		{
			printf("ql_fopen failed\n");
		}

		ret= ql_ftp_client_put(client,U_FILE_TEST_DEVICE_FILE,NULL,NULL,NULL);
		printf("\nql_ftp_client_put[test_device.txt->test_device.txt] ret=%d\n",ret);

		ret= ql_ftp_client_put(client,U_FILE_TEST_DEVICE_FILE,"test_device_tmp.txt",NULL,NULL);
		printf("\nql_ftp_client_put[test_device.txt->test_device_tmp.txt] ret=%d\n",ret);

		ret= ql_ftp_client_put(client,U_FILE_TEST_DEVICE_FILE,"test_device_create.txt",read_data,NULL);
		printf("\nql_ftp_client_put[test_device.txt->test_device_create.txt] ret=%d\n",ret);
		
		ret=ql_ftp_client_delete(client,"test_device_tmp.txt");
		printf("\nql_ftp_client_delete[test_device_tmp.txt] ret=%d\n",ret);

		ret=ql_ftp_client_delete(client,"test_device_create.txt");
		printf("\nql_ftp_client_delete[test_device_create.txt] ret=%d\n",ret);

		ret=ql_ftp_client_close(client);
		printf("\nql_ftp_client_close ret=%d\n",ret);
		
		printf("\n\n==============ftp_client_test[%d] end================\n",run_num);
		run_num++;
		ql_rtos_task_sleep_s(10); 
		
	}
	ql_ftp_client_release(client); /*release http resources*/
}

//application_init(ql_ftp_client_test, "ql_ftp_client_test", 10, 2);
