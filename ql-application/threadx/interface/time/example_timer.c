/*================================================================
  Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/
/**
 ******************************************************************************
 * @file    example_timer.c
 * @author  Juson.zhang
 * @version V1.0.0
 * @date    2020/04/02
 * @brief   This file tests timer's APIs
 ******************************************************************************
 */

#include <stdio.h>
#include "ql_rtos.h"
#include "ql_type.h"
#include "ql_application.h"
#include "ql_timer.h"

#define test_log(fmt, args...)	printf(fmt, ##args)

static unsigned int g_timer_cnt = 0;
void ql_Acctimer_test_cb(unsigned int param)
{
	g_timer_cnt++;
}

static void quec_timer_test(void * argv)
{
	int timer_id = 0;
	timer_id = ql_start_Acctimer(QL_TIMER_PERIOD, 1000, ql_Acctimer_test_cb, 0);
	test_log("timer_id=%d \n", timer_id);

	while (1) {
		test_log("DKM 1ms timer, g_timer_cnt=%d \n", g_timer_cnt);
		ql_rtos_task_sleep_s(1);
	}
}

 application_init(quec_timer_test, "quec_timer_test", 2, 0);


