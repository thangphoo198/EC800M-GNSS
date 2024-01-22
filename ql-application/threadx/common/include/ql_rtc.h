/*================================================================
  Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/



#ifndef _QL_RTC_H_
#define _QL_RTC_H_
	 
#ifdef __cplusplus
	 extern "C" {
#endif

typedef struct ql_rtc_time_struct {
	int tm_sec;	 //seconds [0,59]
	int tm_min;	 //minutes [0,59]
	int tm_hour;  //hour [0,23]
	int tm_mday;  //day of month [1,31]
	int tm_mon;	 //month of year [1,12]
	int tm_year; // since 1970
	int tm_wday; // sunday = 0
}ql_rtc_time_t;

typedef void (*ql_rtc_cb)(void);


/****************************************************************************
 * Function: ql_rtc_set_time
 * Description: RTC设置时间接口
 
 * Parameters::
 	［IN］ tm:传入设置的时间
 * Return:
 	0	表示成功
 	-1  表示失败
******************************************************************************/
int ql_rtc_set_time(ql_rtc_time_t *tm);

/****************************************************************************
 * Function: ql_rtc_get_time
 * Description: 获取RTC当前时间,请注意在开机模组注网后，NITZ会将时间同步到RTC
 
 * Parameters::
 	［IN］ tm:存放获取的时间
 * Return:
 	0	表示成功
 	-1  表示失败
******************************************************************************/
int ql_rtc_get_time(ql_rtc_time_t *tm);

 /****************************************************************************
  * Function: ql_rtc_set_alarm
  * Description: 设置RTC闹钟时间
  
  * Parameters::
	 ［IN］ tm:传入设置的RTC闹钟时间
  * Return:
	 0	 表示成功
	 -1  表示失败
 ******************************************************************************/
 int ql_rtc_set_alarm(ql_rtc_time_t *tm);

 /****************************************************************************
 * Function: ql_rtc_get_alarm
 * Description: 获取RTC设置的闹钟时间
 
 * Parameters::
 	［IN］ tm:存放RTC设置的闹钟时间
 * Return:
 	0	表示成功
 	-1  表示失败
******************************************************************************/
 int ql_rtc_get_alarm(ql_rtc_time_t *tm);
 
 /****************************************************************************
 * Function: ql_rtc_enable_alarm
 * Description: 使能RTC 闹钟
 
 * Parameters::
	on_off		：1：开 ； 0：关
 * Return:
 	无
******************************************************************************/
 void ql_rtc_enable_alarm(unsigned char on_off);

 /****************************************************************************
 * Function: ql_rtc_register_cb
 * Description: RTC注册回调接口，在设置RTC闹钟时注册回调，注意不要在回调函数内运行比较耗时的代码或者函数
 
 * Parameters::
	cb ：注册回调接口地址
 * Return:
 	无
******************************************************************************/
 void ql_rtc_register_cb(ql_rtc_cb cb);
 
 /**
  * Name: ql_rtos_get_tsticks
  * Description: Number of ts ticks that passed since last reset.
  * Para: None
  * Returns: u32 Number of ts ticks that passed since last reset.
  * Note: Increase by 1 per 1/32K s
  **/
 unsigned int ql_rtc_get_ticks(void);
 unsigned long long ql_rtc_get_ticks_uint64(void);
int ql_rtc_get_time_ex(ql_rtc_time_t *tm);

#ifdef __cplusplus
	 } /*"C" */
#endif
 
#endif /* _QL_RTC_H_ */


