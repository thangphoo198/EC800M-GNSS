/*================================================================
  Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/

#include "ql_application.h"
#include <time.h>
#include <sys/time.h>
#include <stdio.h>

static void time_test(void * argv)
{
	struct tm *tm_ptr = NULL;
	time_t _time = 0x00000001;
	struct timeval tv = {0};
	
	gettimeofday(&tv, NULL);
	printf("tv_sec: %d\r\n", tv.tv_sec);
	printf("tv_usec: %d\r\n", tv.tv_usec);

	_time = time(NULL);
	printf("seconds: %d\r\n", _time);
	
    tm_ptr =ql_localtime(&_time);
    printf("year: %d\r\n", tm_ptr->tm_year);
	printf("mont: %d\r\n", tm_ptr->tm_mon);
	printf("mday: %d\r\n", tm_ptr->tm_mday);
	printf("wday: %d\r\n", tm_ptr->tm_wday);
	printf("hour: %d\r\n", tm_ptr->tm_hour);
	printf("minu: %d\r\n", tm_ptr->tm_min);
	printf("seco: %d\r\n", tm_ptr->tm_sec);

    struct tm now_time;
    ql_localtime_r(&_time,&now_time);
    printf("year: %d\r\n", now_time.tm_year);
	printf("mont: %d\r\n", now_time.tm_mon);
	printf("mday: %d\r\n", now_time.tm_mday);
	printf("wday: %d\r\n", now_time.tm_wday);
	printf("hour: %d\r\n", now_time.tm_hour);
	printf("minu: %d\r\n", now_time.tm_min);
	printf("seco: %d\r\n", now_time.tm_sec);
    
	tm_ptr = gmtime(&_time);
	printf("year: %d\r\n", tm_ptr->tm_year);
	printf("mont: %d\r\n", tm_ptr->tm_mon);
	printf("mday: %d\r\n", tm_ptr->tm_mday);
	printf("wday: %d\r\n", tm_ptr->tm_wday);
	printf("hour: %d\r\n", tm_ptr->tm_hour);
	printf("minu: %d\r\n", tm_ptr->tm_min);
	printf("seco: %d\r\n", tm_ptr->tm_sec);
}

//application_init(time_test, "time_test", 1, 1);

