/*================================================================
  Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ql_type.h"
#include "ql_rtos.h"
#include "ql_application.h"
#include "ql_data_call.h"
#include "sockets.h"
#include "netdb.h"
#include "ql_ntp.h"


#define NTP_SERVER_DOMAIN "ntp.aliyun.com"
//#define NTP_SERVER_DOMAIN "www.baidu.com"

#define PDP_NTP_TEST 1
#define NTP_SERVER_PORT 123

static struct in_addr ip4_addr = {0};


static void ql_nw_status_callback(int profile_idx, int nw_status)
{
	printf("profile(%d) status: %d\r\n", profile_idx, nw_status);
}

static void datacall_start(void)
{
	printf("wait for network register done\r\n");

	if(ql_network_register_wait(30) != 0)
	{
		printf("*** network register fail ***\r\n");
	}
	else
	{

		printf("doing network activing ...\r\n");
		
		ql_wan_start(ql_nw_status_callback);
		ql_set_auto_connect(1, TRUE);
		ql_start_data_call(1, 0, "3gnet.mnc001.mcc460.gprs", NULL, NULL, 0);

	}
}

void get_ntp_callback(int ntp_status)
{
	printf("========== get ntp status:%d ...\r\n", ntp_status);
}

 void ql_ntp_test(void * argv)
{
	struct ql_data_call_info info = {0};
	char ip4_addr_str[16] = {0};
	int ret =0 ;
	
	printf("========== NTP test will start ...\r\n");

	datacall_start();

	while(1){

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

		printf("========ql_ntp_server set========== !\n");
		ret = ql_ntp_set_server(NTP_SERVER_DOMAIN);
		printf("========ql_ntp_client set:%d==server %s======== !\n", ret, NTP_SERVER_DOMAIN);
		ret = ql_ntp_set_cid(1);
		if(ret != QL_NTP_SUCCESS)
			printf("ql_ntp_init failed!!\n");
		
		printf("========ql_ntp_sync!!===== !\n");

		ql_ntp_sync_ex(get_ntp_callback);/*通过回调获取状态值0 成功，1 失败*/
		ql_rtos_task_sleep_s(5);
		
	}
        printf("========== NTP test  end ...\r\n");
			
}


//application_init(ql_ntp_test,"ql_ntp_test", 4, 5);

