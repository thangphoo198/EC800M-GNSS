/**  
  @file
  example_cell_locator.c

  @brief
  quectel locator example.

*/
/*============================================================================
  Copyright (c) 2017 Quectel Wireless Solution, Co., Ltd.  All Rights Reserved.
  Quectel Wireless Solution Proprietary and Confidential.
 =============================================================================*/
/*===========================================================================

                        EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.


WHEN        WHO            WHAT, WHERE, WHY
----------  ------------   ----------------------------------------------------
27/03/2020  Archer.Jia      create
=============================================================================*/


#include <stdio.h>
#include "ql_rtos.h"
#include "ql_data_call.h"
#include "ql_http_client.h"
#include "ql_application.h"
#include "ql_cell_locator.h"
#include "ql_nw.h"
#include "ql_log.h"

#define CELL_LOCATOR_SERVER_DOMAIN "www.queclocator.com"


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

static void ql_cell_call_back(QL_CELL_LOC_STATE_E state, ql_cell_cfg *cell_cfg)
{	
	printf("cb lng: %f, lat: %f, accuracy: %d err:%d\n",cell_cfg->lng, cell_cfg->lat, cell_cfg->accuracy, cell_cfg->err.err_code);
}

static void ql_cell_locator_test(void *arg)
{
	int ret,i ;
	char token [32] ="1111111122222222";
//	char token [32] ="1234567812345678";

/*	ql_cell_wifiinfo ext_wifiinfo[3]={
	{"44:6a:2e:11:d7:d1","quec_wifi1",-30},
	{"44:6a:2e:11:d7:c2","quec_wifi2",-39},
	{"44:6a:2e:11:d6:e1","quec_wifi3",-59}
	}; //user enters WIFI address
*/	
	struct ql_data_call_info info = {0};
	char ip4_addr_str[16] = {0};
	int port = 80;
	int timeout = 10;
	ql_cell_cfg *g_cell_cfg = NULL;
	
	ret = datacall_satrt();
	if(ret)
    {
        printf("datacall_satrt error.\n");
        return ;
    }
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
    ql_log_mask_set(QL_LOG_APP_MASK,QL_LOG_PORT_USB);
	printf("cell_locator started!! \r\n");
	g_cell_cfg = malloc(sizeof(ql_cell_cfg));
	if(g_cell_cfg == NULL)
		printf("g_cell_cfg malloc failed !!\n");
    ret = ql_cell_locator_init(g_cell_cfg);
    if(ret)
    {
        printf("ql_cell_locator_init error.\n");
        return ;
    }
	ret = ql_cell_locator_set_server(g_cell_cfg,CELL_LOCATOR_SERVER_DOMAIN, port);
    if(ret)
    {
        printf("ql_cell_locator_set_server error.\n");
        return ;
    }

	 ret = ql_cell_locator_set_cid(g_cell_cfg,1);
    if(ret)
    {
        printf("ql_cell_locator_set_cid error.\n");
        return ;
    }

	 ret = ql_cell_locator_set_timeout(g_cell_cfg,timeout);
    if(ret)
    {
        printf("ql_cell_locator_set_timeout error.\n");
        return ;
    }

    ret = ql_cell_locator_set_token(g_cell_cfg,token, strlen(token));
    if(ret)
    {
        printf("ql_cell_locator_set_token error.\n");
        return ;
    }

	ret = ql_cell_locator_setopt(g_cell_cfg, QL_CELL_OPT_ASYN, 0);
    if(ret)
    {
        printf("ql_cell_locator set ASYN error.\n");
        return ;
    }

	ret = ql_cell_locator_setopt(g_cell_cfg, QL_CELL_OPT_ASYN_CB, ql_cell_call_back);/*Asynchronous callback*/
    if(ret)
    {
        printf("ql_cell_locator set ASYN_CB error.\n");
        return ;
    }
	
	ret = ql_cell_locator_setopt(g_cell_cfg, QL_CELL_OPT_METHOD, QL_CELL_TYPE_CELL);
    if(ret)
    {
        printf("ql_cell_locator set METHOD error.\n");
        return ;
    }

	for(i=0;i<10;i++)
	{
    	ret = ql_cell_locator_perform(g_cell_cfg);
    	if(ret)
			printf("ql_cell_locator_perform ret %d  error:%d \n",ret,g_cell_cfg->err.err_code);

		printf("lng: %f, lat: %f, accuracy: %d city_code:%s err:%d\n",g_cell_cfg->lng,g_cell_cfg->lat,g_cell_cfg->accuracy,g_cell_cfg->city_code,g_cell_cfg->err.err_code);
		ql_rtos_task_sleep_s(10);
	
	}
    ql_cell_locator_release(g_cell_cfg);
	
    return;
	
}

//application_init(ql_cell_locator_test, "ql_cell_locator_test", 10, 3);



