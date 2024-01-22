/*================================================================
  Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>


#include "ql_rtos.h"
#include "ql_application.h"
#include "ql_dev.h"



static void ql_dev_test_task(void * argv)
{
	int ret = 0,j=0;
	char data[64] = {0};
	QL_DEV_MODEM_FUNCTION function = 0;
	int current_fun=0;
	int rst = 0;
	ql_rtos_task_sleep_s(5);
	while(j<10000)
	{
		ql_rtos_task_sleep_s(10);
		printf("\n==========Device info test[start]==========\n");
		
		ret = ql_dev_get_imei(data,sizeof(data));
		printf("ql_dev_get_imei ret=%d; IMEI:%s \n",ret,data);
		memset(data,0,sizeof(data));

		ret = ql_dev_get_model(data,sizeof(data));
		printf("ql_dev_get_model ret=%d; model:%s \n",ret,data);
		memset(data,0,sizeof(data));

		ret = ql_dev_get_sn(data,sizeof(data));
		printf("ql_dev_get_sn ret=%d; sn:%s \n",ret,data);
		memset(data,0,sizeof(data));

		ret = ql_dev_get_firmware_version(data,sizeof(data));
		printf("ql_dev_get_firmware_version ret=%d; firmware_version:%s \n",ret,data);
		memset(data,0,sizeof(data));

		if(function==5)
			function=0;
		else 
			function++;
		ret = ql_dev_set_modem_fun(function,rst);
		printf("ql_dev_get_modem_fun ret=%d; modem_fun:%d; rst:%d\n",ret,function,rst);
		printf("==========Device info test[end]==========\n\n");
		j++;
	}
}

application_init(ql_dev_test_task, "ql_dev_test_task", 2, 0);

