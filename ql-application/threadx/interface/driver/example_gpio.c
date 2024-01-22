/*================================================================
  Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/
/**
 ******************************************************************************
 * @file    example_gpio.c
 * @author  Juson.zhang
 * @version V1.0.0
 * @date    2019/01/02
 * @brief   This file tests GPIO's APIs
 ******************************************************************************
 */

#include <stdio.h>
#include "ql_gpio.h"
#include "ql_rtos.h"
#include "ql_uart.h"
#include "ql_application.h"
#include "ql_type.h"
//#include "global_types.h"
#include "ql_func.h"

//#define GPIO_UART_TEST
#ifdef GPIO_UART_TEST//august add gpio test to uart
#define QL_GPIO_TEST_PORT	QL_USB_CDC_PORT

static int i = 0;
static int g_gpio = 0;
static int g_eint = 0;
static int c_flag = 1;
static unsigned char uart_data[20] = {0};

void gpio_irq_handler_test01(void)
{
	int l=0;
	unsigned char buf[64] = {0};
	snprintf(buf, sizeof(buf)," eint test: %d  \n",i++);
	ql_uart_write(QL_GPIO_TEST_PORT, buf, sizeof(buf));
	ql_eint_enable(g_gpio , g_eint);
}

int chnum(char p)
{
	int num = 0;
	if(p>='0' && p<='9')
		num = p - '0';
	return num;
}
int read_direction(char p)
{
	if(p == 'O' || p == 'o') return PIN_DIRECTION_OUT;
	else if(p == 'I' || p == 'i') return PIN_DIRECTION_IN;
	else return -1;
}

int read_pull(char p)
{
	if(p == 'U' || p == 'u') return PIN_PULL_PU;
	else if(p == 'D' || p == 'd') return PIN_PULL_PD;
	else if(p == 'N' || p == 'n') return PIN_PULL_DISABLE;
	else return -1;
}

int read_level(char p)
{
	if(p == 'H' || p == 'h') return PIN_LEVEL_HIGH;
	else if(p == 'L' || p == 'l') return PIN_LEVEL_LOW;
	else return -1;
}

int read_eint(char p)
{
 	if(p == 'N' || p == 'n') return PIN_NO_EDGE;
	else if(p == 'R' || p == 'r') return PIN_RISING_EDGE;
	else if(p == 'F' || p == 'f') return PIN_FALLING_EDGE;
	else if(p == 'B' || p == 'b') return PIN_BOTH_EDGE;
	else return -1;
}

void incorrect_command(void)
{
	unsigned char buff[64] = {0};
	snprintf(buff, sizeof(buff)," Undefined command, please re-enter \r\n");
	ql_uart_write(QL_GPIO_TEST_PORT, buff, sizeof(buff));

}

void quec_gpio_uart_callback(QL_UART_PORT_NUMBER_E port, void *para)
{
	
	c_flag = 2;
	memset(uart_data,0,sizeof(uart_data));
	ql_uart_read(port,uart_data, sizeof(uart_data));
	
}

static void quec_gpio_test(void * argv)
{
	int ret = -1;
	int i = 0,j = 1;
	int gpio_num = 0;
	unsigned char level = 0;
	unsigned char buf[64] = {0};
	unsigned char data[] = "hello, please select gpio 0~127!!!\n";
	ret = ql_uart_open(QL_GPIO_TEST_PORT, QL_UART_BAUD_115200, QL_FC_NONE);
	if (ret) {
		printf("open uart[%d] failed! \n", QL_GPIO_TEST_PORT);
		return;
	}
	ql_uart_register_cb(QL_GPIO_TEST_PORT, quec_gpio_uart_callback);	//use callback to read uart data		
	ql_uart_write(QL_GPIO_TEST_PORT, data, sizeof(data));
	while(c_flag)
	{
		if(c_flag == 2)
		{
			for(i = 0;i < 15;i++)
			{
				if(uart_data[i] == '#')
				{	
					gpio_num = chnum(uart_data[i+2])*100+chnum(uart_data[i+3])*10+chnum(uart_data[i+4]);
					j = 0;
					if(gpio_num > GPIO_PIN_NO_MAX){
						incorrect_command();
						break;
					}
					switch(uart_data[i+1])
					{
						//The format is set as:INIT GPIO OUT/IN PU/PD/N  H/L
						case 'i':
						case 'I':
							ret = ql_gpio_init(gpio_num, read_direction(uart_data[i+5]), read_pull(uart_data[i+6]),read_level(uart_data[i+7]));
							if(ret < 0){
								memset(buf, 0, sizeof(buf));
								snprintf(buf, sizeof(buf), "gpio %d init filed \r\n",gpio_num);
								ql_uart_write(QL_GPIO_TEST_PORT,buf, sizeof(buf));
								break;
							}
							if((read_direction(uart_data[i+5])== -1) || (read_pull(uart_data[i+6])== -1) || (read_level(uart_data[i+7])== -1)){
								incorrect_command();
								break;
							}
							memset(buf, 0, sizeof(buf));
							snprintf(buf, sizeof(buf), "init gpio %d direction: %d pull: %d level: %d \r\n",gpio_num,
								read_direction(uart_data[i+5]),read_pull(uart_data[i+6]),read_level(uart_data[i+7]));
							ql_uart_write(QL_GPIO_TEST_PORT,buf, sizeof(buf));
							break;
							
						//The format is set as:GET GPIO LEVEL
						case 'g':
						case 'G':
							ql_gpio_get_level(gpio_num, &level);
							memset(buf, 0, sizeof(buf));
							snprintf(buf, sizeof(buf), " ==== get gpio %d level is %d ==== \n",gpio_num,level);
							ql_uart_write(QL_GPIO_TEST_PORT,buf, sizeof(buf));
							break;
							
						//The format is set as:SET GPIO H/L
						case 's':
						case 'S':
							ret = ql_gpio_set_level(gpio_num,read_level(uart_data[i+5]));
							if(ret == -1){
								memset(buf, 0, sizeof(buf));
								snprintf(buf, sizeof(buf)," gpio %d uninitialized \n",gpio_num);
								ql_uart_write(QL_GPIO_TEST_PORT, buf, sizeof(buf));
								break;
							}
							if(read_level(uart_data[i+5]) == -1){
								incorrect_command();
								break;
							}
							memset(buf, 0, sizeof(buf));
							snprintf(buf, sizeof(buf)," **** set gpio %d level is %d **** \n",gpio_num, read_level(uart_data[i+5]));
							ql_uart_write(QL_GPIO_TEST_PORT, buf, sizeof(buf));
							break;

						//The format is set as:EINT GPIO N/R/F/B
						case 'e':
						case 'E':
							if(read_eint(uart_data[i+5]) == -1){
								incorrect_command();
								break;
							}
							if(ql_eint_register((g_gpio = gpio_num),(g_eint = read_eint(uart_data[i+5])),PIN_PULL_PD, gpio_irq_handler_test01,NULL)) {
								memset(buf, 0, sizeof(buf));
								snprintf(buf, sizeof(buf),"eint register failed \n");
								ql_uart_write(QL_GPIO_TEST_PORT, buf, sizeof(buf));
								break;
							}
							ql_eint_enable(gpio_num, read_eint(uart_data[i+5]));
							memset(buf, 0, sizeof(buf));
							snprintf(buf, sizeof(buf)," eint gpio %d way is %d \r\n",gpio_num, read_eint(uart_data[i+5]));
							ql_uart_write(QL_GPIO_TEST_PORT, buf, sizeof(buf));
							break;
						default: incorrect_command();break;
					}				
				}				
			}
			if(j) incorrect_command();
			else j = 1;
			c_flag = 1;
		}
		ql_rtos_task_sleep_ms(500);
	}
}

#else

#define test_log(fmt, args...)	printf(fmt, ##args)

#ifndef QUEC_ARR_SIZE
#define QUEC_ARR_SIZE(a)         	( sizeof(a) / sizeof(a[0]) )
#endif


static quec_gpio_cfg_t __quec_gpio_cfg[] =
{
	{GPIO_PIN_NO_31, PIN_DIRECTION_OUT, PIN_NO_EDGE, PIN_PULL_DISABLE, PIN_LEVEL_LOW},
	{GPIO_PIN_NO_32, PIN_DIRECTION_OUT, PIN_NO_EDGE, PIN_PULL_DISABLE, PIN_LEVEL_LOW},
	
#if 0
	{GPIO_PIN_NO_0, PIN_DIRECTION_OUT, PIN_NO_EDGE, PIN_PULL_DISABLE, PIN_LEVEL_LOW},
	{GPIO_PIN_NO_1, PIN_DIRECTION_OUT, PIN_NO_EDGE, PIN_PULL_DISABLE, PIN_LEVEL_LOW},
	{GPIO_PIN_NO_10, PIN_DIRECTION_OUT, PIN_NO_EDGE, PIN_PULL_DISABLE, PIN_LEVEL_LOW},
	{GPIO_PIN_NO_11, PIN_DIRECTION_OUT, PIN_NO_EDGE, PIN_PULL_DISABLE, PIN_LEVEL_LOW},
	{GPIO_PIN_NO_33, PIN_DIRECTION_OUT, PIN_NO_EDGE, PIN_PULL_DISABLE, PIN_LEVEL_LOW},
	{GPIO_PIN_NO_34, PIN_DIRECTION_OUT, PIN_NO_EDGE, PIN_PULL_DISABLE, PIN_LEVEL_LOW},
	{GPIO_PIN_NO_35, PIN_DIRECTION_OUT, PIN_NO_EDGE, PIN_PULL_DISABLE, PIN_LEVEL_LOW},
	{GPIO_PIN_NO_36, PIN_DIRECTION_OUT, PIN_NO_EDGE, PIN_PULL_DISABLE, PIN_LEVEL_LOW},

	{GPIO_PIN_NO_16, PIN_DIRECTION_OUT, PIN_NO_EDGE, PIN_PULL_DISABLE, PIN_LEVEL_LOW},
	{GPIO_PIN_NO_17, PIN_DIRECTION_OUT, PIN_NO_EDGE, PIN_PULL_DISABLE, PIN_LEVEL_LOW},
	{GPIO_PIN_NO_18, PIN_DIRECTION_OUT, PIN_NO_EDGE, PIN_PULL_DISABLE, PIN_LEVEL_LOW},
	{GPIO_PIN_NO_19, PIN_DIRECTION_OUT, PIN_NO_EDGE, PIN_PULL_DISABLE, PIN_LEVEL_LOW},
	{GPIO_PIN_NO_49, PIN_DIRECTION_OUT, PIN_NO_EDGE, PIN_PULL_DISABLE, PIN_LEVEL_LOW},
	{GPIO_PIN_NO_50, PIN_DIRECTION_OUT, PIN_NO_EDGE, PIN_PULL_DISABLE, PIN_LEVEL_LOW},
	{GPIO_PIN_NO_85, PIN_DIRECTION_OUT, PIN_NO_EDGE, PIN_PULL_DISABLE, PIN_LEVEL_LOW},
	{GPIO_PIN_NO_121, PIN_DIRECTION_OUT, PIN_NO_EDGE, PIN_PULL_DISABLE, PIN_LEVEL_LOW},
	{GPIO_PIN_NO_122, PIN_DIRECTION_OUT, PIN_NO_EDGE, PIN_PULL_DISABLE, PIN_LEVEL_LOW},
	{GPIO_PIN_NO_124, PIN_DIRECTION_OUT, PIN_NO_EDGE, PIN_PULL_DISABLE, PIN_LEVEL_LOW},
	

	{GPIO_PIN_NO_8, PIN_DIRECTION_OUT, PIN_NO_EDGE, PIN_PULL_DISABLE, PIN_LEVEL_LOW},
	{GPIO_PIN_NO_9, PIN_DIRECTION_OUT, PIN_NO_EDGE, PIN_PULL_DISABLE, PIN_LEVEL_LOW},
	{GPIO_PIN_NO_20, PIN_DIRECTION_OUT, PIN_NO_EDGE, PIN_PULL_DISABLE, PIN_LEVEL_LOW},
	{GPIO_PIN_NO_21, PIN_DIRECTION_OUT, PIN_NO_EDGE, PIN_PULL_DISABLE, PIN_LEVEL_LOW},
	{GPIO_PIN_NO_22, PIN_DIRECTION_OUT, PIN_NO_EDGE, PIN_PULL_DISABLE, PIN_LEVEL_LOW},
	{GPIO_PIN_NO_24, PIN_DIRECTION_OUT, PIN_NO_EDGE, PIN_PULL_DISABLE, PIN_LEVEL_LOW},
	{GPIO_PIN_NO_25, PIN_DIRECTION_OUT, PIN_NO_EDGE, PIN_PULL_DISABLE, PIN_LEVEL_LOW},
	{GPIO_PIN_NO_26, PIN_DIRECTION_OUT, PIN_NO_EDGE, PIN_PULL_DISABLE, PIN_LEVEL_LOW},
	{GPIO_PIN_NO_71, PIN_DIRECTION_OUT, PIN_NO_EDGE, PIN_PULL_DISABLE, PIN_LEVEL_LOW},
	{GPIO_PIN_NO_74, PIN_DIRECTION_OUT, PIN_NO_EDGE, PIN_PULL_DISABLE, PIN_LEVEL_LOW},
	{GPIO_PIN_NO_78, PIN_DIRECTION_OUT, PIN_NO_EDGE, PIN_PULL_DISABLE, PIN_LEVEL_LOW},
	{GPIO_PIN_NO_77, PIN_DIRECTION_OUT, PIN_NO_EDGE, PIN_PULL_DISABLE, PIN_LEVEL_LOW},
	{GPIO_PIN_NO_76, PIN_DIRECTION_OUT, PIN_NO_EDGE, PIN_PULL_DISABLE, PIN_LEVEL_LOW},
	{GPIO_PIN_NO_75, PIN_DIRECTION_OUT, PIN_NO_EDGE, PIN_PULL_DISABLE, PIN_LEVEL_LOW},
	{GPIO_PIN_NO_72, PIN_DIRECTION_OUT, PIN_NO_EDGE, PIN_PULL_DISABLE, PIN_LEVEL_LOW},
	{GPIO_PIN_NO_73, PIN_DIRECTION_OUT, PIN_NO_EDGE, PIN_PULL_DISABLE, PIN_LEVEL_LOW},
	{GPIO_PIN_NO_81, PIN_DIRECTION_OUT, PIN_NO_EDGE, PIN_PULL_DISABLE, PIN_LEVEL_LOW},
	{GPIO_PIN_NO_82, PIN_DIRECTION_OUT, PIN_NO_EDGE, PIN_PULL_DISABLE, PIN_LEVEL_LOW},
	
	{GPIO_PIN_NO_37, PIN_DIRECTION_OUT, PIN_NO_EDGE, PIN_PULL_DISABLE, PIN_LEVEL_LOW},
	{GPIO_PIN_NO_38, PIN_DIRECTION_OUT, PIN_NO_EDGE, PIN_PULL_DISABLE, PIN_LEVEL_LOW},
	{GPIO_PIN_NO_39, PIN_DIRECTION_OUT, PIN_NO_EDGE, PIN_PULL_DISABLE, PIN_LEVEL_LOW},
	{GPIO_PIN_NO_40, PIN_DIRECTION_OUT, PIN_NO_EDGE, PIN_PULL_DISABLE, PIN_LEVEL_LOW},
	{GPIO_PIN_NO_41, PIN_DIRECTION_OUT, PIN_NO_EDGE, PIN_PULL_DISABLE, PIN_LEVEL_LOW},
	{GPIO_PIN_NO_42, PIN_DIRECTION_OUT, PIN_NO_EDGE, PIN_PULL_DISABLE, PIN_LEVEL_LOW},
	{GPIO_PIN_NO_43, PIN_DIRECTION_OUT, PIN_NO_EDGE, PIN_PULL_DISABLE, PIN_LEVEL_LOW},
#endif
};

static QlOSStatus __quec_gpio_cust_config(void)
{
	int i=0;
	
	for(i=0; i<QUEC_ARR_SIZE(__quec_gpio_cfg) ; i++)
	{
		ql_gpio_init(__quec_gpio_cfg[i].gpio_pin_num, __quec_gpio_cfg[i].pin_dir, __quec_gpio_cfg[i].pin_pull, __quec_gpio_cfg[i].pin_level);

	}

	return 0;
}

static void quec_gpio_test(void * argv)
{
	int i = 0, j = 0;
	unsigned char level = 0;

	__quec_gpio_cust_config();
	ql_rtos_task_sleep_s(1);
	
	while(1) {
	 	j++;
		test_log("quec_gpio_test_task, id:%d \n", j);
		for(i=0; i<QUEC_ARR_SIZE(__quec_gpio_cfg) ; i++) {
			ql_gpio_set_level(__quec_gpio_cfg[i].gpio_pin_num, PIN_LEVEL_LOW);
			test_log("===Set gpio[%d] level is %d=== \n", __quec_gpio_cfg[i].gpio_pin_num, PIN_LEVEL_LOW);
		}
		ql_rtos_task_sleep_s(3);
		
		for(i=0; i<QUEC_ARR_SIZE(__quec_gpio_cfg) ; i++) {
			ql_gpio_get_level(__quec_gpio_cfg[i].gpio_pin_num, &level);
			test_log("***Get gpio[%d] level is %d*** \n", __quec_gpio_cfg[i].gpio_pin_num, level);
		}
		ql_rtos_task_sleep_s(3);

		for(i=0; i<QUEC_ARR_SIZE(__quec_gpio_cfg) ; i++) {
			ql_gpio_set_level(__quec_gpio_cfg[i].gpio_pin_num, PIN_LEVEL_HIGH);
			test_log("===Set gpio[%d] level is %d=== \n", __quec_gpio_cfg[i].gpio_pin_num, PIN_LEVEL_HIGH);
		}
		ql_rtos_task_sleep_s(3);

		for(i=0; i<QUEC_ARR_SIZE(__quec_gpio_cfg) ; i++) {
			ql_gpio_get_level(__quec_gpio_cfg[i].gpio_pin_num, &level);
			test_log("***Get gpio[%d] level is %d*** \n", __quec_gpio_cfg[i].gpio_pin_num, level);
		}
		ql_rtos_task_sleep_s(3);
		break;
	}

}

#endif

//application_init(quec_gpio_test, "quec_gpio_test", 2, 0);

