 /*================================================================
   Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
   Quectel Wireless Solutions Proprietary and Confidential.
 =================================================================*/
 /*  example_rtc: we just use APP_OFFSET, and SYS_OFFSET is not used, but we can set it in quec_rtc.c*/
 
#include <stdio.h>
#include "ql_rtos.h"
#include "ql_type.h"
#include "ql_application.h"
#include "ql_rtc.h"
 

const char * week_days[] = 
{
	"SUN","MON","TUS","WED","THU","FRI","SAT"
};
 
#define	weekday_to_string(a)	(week_days[(a)])
 void ql_rtc_print_time(ql_rtc_time_t *tmp)
 {
	 if(tmp->tm_wday > 6 || tmp->tm_wday < 0)
	 {
		 tmp->tm_wday = 0;
	 }
	 
	 printf("%d-%0.2d-%0.2d %0.2d:%0.2d:%0.2d [%s]\r\n",
			 tmp->tm_year,
			 tmp->tm_mon,
			 tmp->tm_mday,
			 tmp->tm_hour,
			 tmp->tm_min,
			 tmp->tm_sec,
			 weekday_to_string(tmp->tm_wday));
 } 



 //  当开机注网后,NITZ会自动将时间更新到RTC
 static void ql_rtc_sync_test(void * argv)
 {
	 unsigned int t1 = 0, t2 = 0;
	 ql_rtc_time_t tm = {0};
	 ql_rtc_get_time(&tm);
	 ql_rtos_task_sleep_s(8);
	 printf("enter rtc api test!! \n");
 
 
	 /* test rtc ticks */
	 t1 = ql_rtc_get_ticks();
	 ql_rtos_task_sleep_ms(100);
	 t2 = ql_rtc_get_ticks();	 
	 printf("ql_rtc_get_ticks, t1:%d, t2:%d, t2-t1:%d!	time=%d ms \r\n", t1, t2, t2-t1,1000*(t2-t1)/32768);
	 
	 while (1) 
	 {
		 ql_rtc_get_time(&tm);
		 printf("=========print current net time===========\r\n");
		 ql_rtc_print_time(&tm);
		 ql_rtos_task_sleep_s(2);
	 }
 }
 
 //application_init(ql_rtc_sync_test, "ql_rtc_sync_test", 2, 10);
 
 
  void ql_rtc_test_callback(void)
  {
		ql_rtc_time_t test_tm = {0};
	
	//test alarm expired
	printf("[%s] \r\n",__func__);
	//disable RTC alarm
	ql_rtc_enable_alarm(0);
	//get alarm time
	printf("=========print alarm time===========\r\n");
	ql_rtc_get_alarm(&test_tm);
	ql_rtc_print_time(&test_tm);

	test_tm.tm_min += 1;
	ql_rtc_set_alarm(&test_tm);
	printf("=========print open system alarm time===========\r\n");
	ql_rtc_print_time(&test_tm);
	ql_rtc_enable_alarm(1);
	ql_powerdown_rtc_in_work(1); //增加此接口，关机后，LDO5给rtc供电，解决关机后，开不了机
	ql_power_down(1);	//power off system //manual plug-out usb , to avoid EXTON_WU
	//wait for RTC_ALARM_WU after 3min
 
  }
  
  /*The test for set time */
  static void ql_rtc_set_test(void * argv)
  {
	  unsigned int t1 = 0, t2 = 0;
	  ql_rtc_time_t tm = {0};
	 // ql_rtc_get_time(&tm);
	  ql_rtos_task_sleep_s(4);
	  printf("enter rtc api set test!! \n");
  
	  //2058-2-2 02:02:02 []
	  tm.tm_sec  = 2;
	  tm.tm_min  = 2;
	  tm.tm_hour = 2;
	  tm.tm_mday = 2;
	  tm.tm_mon  = 2;
	  tm.tm_year = 2018;
	  tm.tm_wday = 5;
	  ql_rtc_set_time(&tm);
  
	 //set alarm
	 tm.tm_sec += 20;
	 ql_rtc_set_alarm(&tm);
 
	 ql_rtc_get_alarm(&tm);
	 ql_rtc_print_time(&tm);
	 
	 //init callback , once alarm expire callback would be invoke
	 ql_rtc_register_cb(ql_rtc_test_callback);
 
	 //enable RTC alarm
	 ql_rtc_enable_alarm(1);
	 
	  while (1) 
	  {
		  ql_rtc_get_time(&tm);
		  printf("=========print current time===========\r\n");
		  ql_rtc_print_time(&tm);
		  ql_rtos_task_sleep_s(2);
	  }
  }
  
// application_init(ql_rtc_set_test, "ql_rtc_set_test", 2, 10);
  
 
