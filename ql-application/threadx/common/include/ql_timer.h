/*================================================================
  Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/
/**
 ******************************************************************************
 * @file    ql_timer.h
 * @author  Juson.zhang
 * @version V1.0.0
 * @date    2020/04/02
 * @brief   This file contains the timer functions's declaration
 ******************************************************************************
 */
#ifndef _QL_TIMER_H_
#define _QL_TIMER_H_
	 
#ifdef __cplusplus
	 extern "C" {
#endif

typedef enum QL_TIMER_FLAG_ENUM
{
	QL_TIMER_PERIOD = 0x1,	/* periodic execution */
	QL_TIMER_AUTO_DELETE = 0x2,	/* one execution */
}QL_TIMER_FLAG_E;

typedef void (*ql_Acctimer_cb)(unsigned int para);

/**
 * Name: ql_start_Acctimer
 * Description: Set RTC timer para and start timer.
 * Para: flag---Execute cycle or Only execute once
 *			period---timeout period,unit:us(NOTE:period>=150us)
 *			timer_cb---timeout callback function
 *			params---callback funtion params
 * Returns: timer_id(1-32).
 * Note: 32KHz
 **/
int ql_start_Acctimer(unsigned int flag, unsigned int period, ql_Acctimer_cb timer_cb, unsigned int params);
int ql_delete_Acctimer(int timer_id);


#ifdef __cplusplus
	 } /*"C" */
#endif
 
#endif /* _QL_TIMER_H_ */



