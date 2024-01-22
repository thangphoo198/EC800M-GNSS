/*================================================================
  Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/
/**
 ******************************************************************************
 * @file    example_eint.c
 * @author  Juson.zhang
 * @version V1.0.0
 * @date    2019/01/02
 * @brief   This file tests GPIO eint APIs
 ******************************************************************************
 */

#include <stdio.h>
#include "ql_gpio.h"
#include "ql_rtos.h"
#include "ql_application.h"
#include "ql_power.h"
#define test_log(fmt, args...)	printf(fmt, ##args)

#define K1_DN_FLAG (0x01)
#define K1_UP_FLAG (0x02)
#define K2_DN_FLAG (0x04)
#define K2_UP_FLAG (0x08)
#define PTT_DN_FLAG (0x10)
#define PTT_UP_FLAG (0x20)
#define UP_DN_FLAG (0x40)
#define UP_UP_FLAG (0x80)
#define DN_DN_FLAG (0x100)
#define DN_UP_FLAG (0x200)

#define ANY_KEY_FLAG (0x3FF)

static int g_test01_cnt = 0;
static int g_test02_cnt = 0;
static int g_test03_cnt = 0;
static int g_test04_cnt = 0;
static int g_test05_cnt = 0;

static ql_flag_t key_flag;

static void __gpio_irq_handler_test01(void)
{
	PIN_LEVEL_E value;
	
	g_test01_cnt++;
	ql_gpio_get_level(GPIO_PIN_NO_5, &value);
	test_log("get gpio[%d] level%d \r\n", GPIO_PIN_NO_5, value);

	if(value == PIN_LEVEL_HIGH)
	{
		ql_rtos_flag_release(key_flag, K1_DN_FLAG, QL_FLAG_OR);
	}
	else
	{
		ql_rtos_flag_release(key_flag, K1_UP_FLAG, QL_FLAG_OR);
	}
	ql_eint_enable(GPIO_PIN_NO_5, PIN_BOTH_EDGE);	//is needed to active isr
	//ql_eint_enable_wakeup(GPIO_PIN_NO_5, PIN_BOTH_EDGE);
}

static void __gpio_irq_handler_test02(void)
{
	PIN_LEVEL_E value;
	
	g_test02_cnt++;
	ql_gpio_get_level(GPIO_PIN_NO_121, &value);
	test_log("get gpio[%d] level%d \r\n", GPIO_PIN_NO_121, value);

	if(value == PIN_LEVEL_HIGH)
	{
		ql_rtos_flag_release(key_flag, K2_DN_FLAG, QL_FLAG_OR);
	}
	else
	{
		ql_rtos_flag_release(key_flag, K2_UP_FLAG, QL_FLAG_OR);
	}
	//ql_eint_enable(GPIO_PIN_NO_121, PIN_BOTH_EDGE);	//is needed to active isr
	ql_eint_enable_wakeup(GPIO_PIN_NO_121, PIN_BOTH_EDGE);
}

static void __gpio_irq_handler_test03(void)
{
	PIN_LEVEL_E value;
	
	g_test03_cnt++;
	ql_gpio_get_level(GPIO_PIN_NO_11, &value);
	test_log("get gpio[%d] level%d \r\n", GPIO_PIN_NO_11, value);

	if(value == PIN_LEVEL_HIGH)
	{
		ql_rtos_flag_release(key_flag, PTT_DN_FLAG, QL_FLAG_OR);
	}
	else
	{
		ql_rtos_flag_release(key_flag, PTT_UP_FLAG, QL_FLAG_OR);
	}
	ql_eint_enable(GPIO_PIN_NO_11, PIN_BOTH_EDGE);	//is needed to active isr
}

static void __gpio_irq_handler_test04(void)
{
	PIN_LEVEL_E value;
	
	g_test04_cnt++;
	ql_gpio_get_level(GPIO_PIN_NO_3, &value);
	test_log("get gpio[%d] level%d \r\n", GPIO_PIN_NO_3, value);

	if(value == PIN_LEVEL_HIGH)
	{
		ql_rtos_flag_release(key_flag, UP_DN_FLAG, QL_FLAG_OR);
	}
	else
	{
		ql_rtos_flag_release(key_flag, UP_UP_FLAG, QL_FLAG_OR);
	}
	ql_eint_enable(GPIO_PIN_NO_3, PIN_BOTH_EDGE);	//is needed to active isr
}

static void __gpio_irq_handler_test05(void)
{
	PIN_LEVEL_E value;
	
	g_test05_cnt++;
	ql_gpio_get_level(GPIO_PIN_NO_4, &value);
	test_log("get gpio[%d] level%d \r\n", GPIO_PIN_NO_4, value);

	if(value == PIN_LEVEL_HIGH)
	{
		ql_rtos_flag_release(key_flag, DN_DN_FLAG, QL_FLAG_OR);
	}
	else
	{
		ql_rtos_flag_release(key_flag, DN_UP_FLAG, QL_FLAG_OR);
	}
	ql_eint_enable(GPIO_PIN_NO_4, PIN_BOTH_EDGE);	//is needed to active isr
}

static void quec_gpio_task(void* argv)
{
    ql_gpio_init(GPIO_PIN_NO_36,PIN_DIRECTION_OUT,PIN_PULL_PD,PIN_LEVEL_HIGH);
    unsigned int cnt=0;
    ql_rtos_task_sleep_ms(10000);
    while(1)
    {
        ql_gpio_set_level(GPIO_PIN_NO_36,PIN_LEVEL_LOW);
        cnt++;
        printf("\r\ngpio[36]------cnt %d\r\n",cnt);
        ql_rtos_task_sleep_ms(1000);
        ql_gpio_set_level(GPIO_PIN_NO_36,PIN_LEVEL_HIGH);
        cnt++;
        printf("\r\ngpio[36]------cnt %d\r\n",cnt);
        ql_rtos_task_sleep_ms(1000);
    }
    
}
static void quec_eint_test(void * argv)
{
	int ret = -1;
	int j = 0;
	unsigned int event = 0;
	ql_rtos_flag_create(&key_flag);
    ql_autosleep_enable(QL_ALLOW_SLEEP);
	ret = ql_eint_register(GPIO_PIN_NO_5, PIN_BOTH_EDGE, PIN_PULL_PU, __gpio_irq_handler_test01, NULL);
	// ret = ql_eint_register(GPIO_PIN_NO_5, PIN_BOTH_EDGE, PIN_PULL_PU, __gpio_irq_handler_test01, NULL);
	if (ret) {
		test_log("eint register failed, ret = %d\n", ret);
		return;
	}
	ql_eint_enable(GPIO_PIN_NO_5, PIN_BOTH_EDGE);
	//ql_eint_enable_wakeup(GPIO_PIN_NO_5, PIN_BOTH_EDGE);

	ret = ql_eint_register(GPIO_PIN_NO_121, PIN_BOTH_EDGE, PIN_PULL_PU,NULL, __gpio_irq_handler_test02);
	// ret = ql_eint_register(GPIO_PIN_NO_121, PIN_BOTH_EDGE, PIN_PULL_PU, __gpio_irq_handler_test02, NULL);
	if (ret) {
		test_log("eint register failed, ret = %d\n", ret);
		return;
	}
	ql_eint_enable_wakeup(GPIO_PIN_NO_121, PIN_BOTH_EDGE);
    // ql_eint_enable(GPIO_PIN_NO_121, PIN_BOTH_EDGE);

	ret = ql_eint_register(GPIO_PIN_NO_11, PIN_BOTH_EDGE, PIN_PULL_PU, __gpio_irq_handler_test03, NULL);
	if (ret) {
		test_log("eint register failed, ret = %d\n", ret);
		return;
	}
	ql_eint_enable(GPIO_PIN_NO_11, PIN_BOTH_EDGE);
	ret = ql_eint_register(GPIO_PIN_NO_3, PIN_BOTH_EDGE, PIN_PULL_PU, __gpio_irq_handler_test04, NULL);
	if (ret) {
		test_log("eint register failed, ret = %d\n", ret);
		return;
	}
	ql_eint_enable(GPIO_PIN_NO_3, PIN_BOTH_EDGE);
	ret = ql_eint_register(GPIO_PIN_NO_4, PIN_BOTH_EDGE, PIN_PULL_PU, __gpio_irq_handler_test05, NULL);
	if (ret) {
		test_log("eint register failed, ret = %d\n", ret);
		return;
	}
	ql_eint_enable(GPIO_PIN_NO_4, PIN_BOTH_EDGE);

	while(1) {
		ql_rtos_flag_wait(key_flag, ANY_KEY_FLAG, QL_FLAG_OR_CLEAR, &event, QL_WAIT_FOREVER);
	 	j++;
		test_log("id:%d, event:0x%X, test01_cnt=%d, test02_cnt=%d, test03_cnt=%d, test04_cnt=%d, test05_cnt=%d\r\n", j, event, g_test01_cnt, g_test02_cnt, g_test03_cnt, g_test04_cnt, g_test05_cnt);
		// ql_rtos_task_sleep_s(3);
	}

}

//application_init(quec_eint_test, "quec_eint_test", 2, 0);
//application_init(quec_gpio_task, "quec_gpio_test", 2, 0);


