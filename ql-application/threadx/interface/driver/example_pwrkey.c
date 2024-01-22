/*================================================================
  Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/


#include <stdio.h>
#include "ql_power.h"
#include "ql_rtos.h"
#include "ql_application.h"

#define test_log(fmt, args...)	printf(fmt, ##args)

#define QL_PWRKEY_HIGH_FLAG 	0x01
#define QL_PWRKEY_LOW_FLAG 		0x02
#define QL_PWRKEY_MASK_FLAG 	(QL_PWRKEY_HIGH_FLAG|QL_PWRKEY_LOW_FLAG)

static ql_flag_t pwrkey_flag_ref;

static void pwrkey_test_callback(void)
{
	ql_pwrkey_intc_enable(0);	//disable pwrkey intc

	if (1 == ql_get_pwrkey_status()) {	//pwrkey is pressed
		ql_rtos_flag_release(pwrkey_flag_ref, QL_PWRKEY_LOW_FLAG, QL_FLAG_OR);
	}
	else {
		ql_rtos_flag_release(pwrkey_flag_ref, QL_PWRKEY_HIGH_FLAG, QL_FLAG_OR);
	}

	ql_pwrkey_intc_enable(1);	//enable pwrkey intc
}

static void quec_pwrkey_test(void * argv)
{
	int ret = -1;
	unsigned char flag_value = 0;
	unsigned int pwrkey_ticks = 0;

	test_log("[zhyy]enter quec_pwrkey_test! \r\n");
	ql_rtos_flag_create(&pwrkey_flag_ref);
	ql_pwrkey_register_irq(pwrkey_test_callback);
	ql_pwrkey_intc_enable(1);	//enable pwrkey intc

	while (1) {
		ret = ql_rtos_flag_wait(pwrkey_flag_ref, QL_PWRKEY_MASK_FLAG, QL_FLAG_OR_CLEAR, &flag_value, QL_WAIT_FOREVER);
		if (ret) {
			test_log("quec_rtos_flag_wait err!\r\n");
			return;
		}

		if (QL_PWRKEY_LOW_FLAG == flag_value) {
			test_log("PWRKEY has been pressed! \r\n");
			pwrkey_ticks = ql_rtos_get_systicks();
		}
		else if (QL_PWRKEY_HIGH_FLAG == flag_value) {
			test_log("PWRKEY has been released! \r\n");
			if (ql_rtos_get_systicks()-pwrkey_ticks > 130) {	//130*5=650ms,Quectel defined powerkey powndown 650ms 
				test_log("pwrkey long press, ticks=%d \r\n", (ql_rtos_get_systicks()-pwrkey_ticks));
				ql_power_down(1);
			}
			else {
				test_log("pwrkey short press, ticks=%d \r\n", (ql_rtos_get_systicks()-pwrkey_ticks));
			}
		}
	}

}

//application_init(quec_pwrkey_test, "quec_pwrkey_test", 2, 0);


