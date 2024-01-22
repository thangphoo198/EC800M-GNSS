/*================================================================
  Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ql_type.h"
#include "ql_application.h"
#include "ql_data_call.h"
#include "ql_ping.h"

#define PING_CID 1
#define PING_HOST "www.baidu.com"
#define PING_TO_MS 4000
#define PING_DATA_SIZE 32
#define PING_NUM 4

ql_sem_t g_ql_ping_sem = NULL;


static void ql_nw_status_callback(int profile_idx, int nw_status)
{
	printf("profile(%d) status: %d\r\n", profile_idx, nw_status);
}

static int datacall_satrt(void)
{
	int ret = 0;
	
	printf("wait for network register done\r\n");

	if(ql_network_register_wait(120) != 0)
	{
		printf("*** network register fail ***\r\n");
		ret = -1;
	}
	else
	{
		printf("doing network activation ...\r\n");
		
		ql_wan_start(ql_nw_status_callback);
		ql_set_auto_connect(1, TRUE);
		ret = ql_start_data_call(1, 0, "3gnet.mnc001.mcc460.gprs", NULL, NULL, 0);
		if(ret)
		{
			printf("*** network active fail ***\r\n");
		}
	}

	return ret;
}

static void ql_ping_cb(ql_ping_state_e state, int err, ql_ping_stat_t * statistic)
{
	printf("ping cb stat %d  \r\n",state);
	if(state == QL_PING_INPROGRESS)
	{
		if(err == 0)
			printf("ping:\tip: %s\tdatasize: %3d\trtt: %4d\tttl: %4d\r\n",statistic->ipSrc, statistic->dataSize, statistic->rtt, statistic->ttl);
		else
			printf("ping:\terror: %d\r\n", err);
	}
	else
	{
		printf("ping:\tsend: %d\trecv: %d\tlost: %d\tminRtt: %d\tmaxRtt: %d\r\n", statistic->sentNum, statistic->rcvdNum, statistic->lostNum, statistic->minRtt, statistic->maxRtt);
	}
	if(statistic->sentNum >= PING_NUM|| statistic->rcvdNum >= PING_NUM)
	{
		
		printf("ping cb send count %d recv count %d  \r\n",statistic->sentNum,statistic->rcvdNum);
		ql_rtos_semaphore_release(g_ql_ping_sem);
	
}
}

static void ping_test(void * argv)
{
	int ret = 0;
	ql_ping_ctx_t *ctx = NULL;
	ql_ping_cfg_t cfg = {
		.pdpCid = PING_CID,
		.host = PING_HOST,
		.timeout = PING_TO_MS,
		.dataSize = PING_DATA_SIZE,
		.pingNum = PING_NUM
	};
	
	if(datacall_satrt())
	{
		printf("*** data call fail ***\r\n");
		return;
	}

	ctx = ql_ping_init(cfg, ql_ping_cb);
	printf("*** ql_ping_cb %p ***\r\n",ql_ping_cb);
	
	if(ctx == NULL)
	{
		printf("*** ping init fail ***\r\n");
		return;
	}

	ql_rtos_semaphore_create(&g_ql_ping_sem,0);
	printf("*** begin ping ***\r\n");
	ql_ping(ctx);
	ql_rtos_semaphore_wait(g_ql_ping_sem,QL_WAIT_FOREVER);
	printf("*** end ping ***\r\n");
	ql_ping_deinit(ctx);
	ql_rtos_semaphore_delete(g_ql_ping_sem);
}

//application_init(ping_test, "ping_test", 4, 0);
