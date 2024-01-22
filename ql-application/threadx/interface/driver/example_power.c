/*================================================================
  Copyright (c) 2022, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/


#include <stdio.h>
#include "ql_rtos.h"
#include "ql_application.h"
#include "ql_power.h"
#include "ql_uart.h"


#define SERIAL_RX_BUFFER_LEN  2048 
static u8 m_RxBuf_Uart1[SERIAL_RX_BUFFER_LEN];

static void  quec_power_test1(void)
{
	int powerup_reason = 0;
	int powerdown_reason = 0;
	char wake_reason = 0;
	printf("enter power api test!! \n");
	ql_rtos_task_sleep_s(5);
	powerup_reason = ql_get_powerup_reason();
	printf("power up reason: 0x%x\n", powerup_reason);

	powerdown_reason = ql_get_powerdown_reason();
	printf("power down reason: 0x%x\n", powerdown_reason);

	wake_reason = ql_get_the_fake_wake_source();
	printf("wake reason:%d, %c\n", wake_reason,wake_reason);
	
	ql_create_a_fake_wake_source(QL_RSTREASON_POWEROFF_CHARGE);
	
	ql_rtos_task_sleep_s(30);
	//ql_power_down(1);
	printf("enter power reset!! \n");
	ql_power_reset();
}


static void quec_main_uart_callback(QL_UART_PORT_NUMBER_E port, void *para)
{
	unsigned int  totalBytes = ql_uart_read(port, m_RxBuf_Uart1, sizeof(m_RxBuf_Uart1));
	if (totalBytes <= 0)
	{
		printf("<-- No data in UART buffer! -->\r\n");
		return;
	}

	if(0 == memcmp(m_RxBuf_Uart1,"create_a_fake_wake_source",25)) 
	{
		printf("<-%s -->\r\n",m_RxBuf_Uart1);
		ql_create_a_fake_wake_source('C');
		return;
	}

	if(0 == memcmp(m_RxBuf_Uart1,"power_reset",11)) 
	{
		printf("<-%s -->\r\n",m_RxBuf_Uart1);
		ql_power_reset();
		return;
	}

	if(0 == memcmp(m_RxBuf_Uart1,"get_wake_source",15)) 
	{
		unsigned char get_reason;	
		printf("<-%s -->\r\n",m_RxBuf_Uart1);
		get_reason = ql_get_the_fake_wake_source();
		printf("get_reason-------------------:%d	%c\r\n",get_reason,get_reason);
		return;
	}
}


static void quec_power_test(void * argv)
{
	int ret =0;
	//power_test_v1();
	//power_test_v2();
	//power_test_v3();
	ql_uart_config_t dcb;

	printf("<-------------------example_power.c------------------------->\r\n");

    ret = ql_uart_open(QL_MAIN_UART_PORT, QL_UART_BAUD_115200, QL_FC_HW);
	if (ret) 
	{
		printf("open uart[%d] failed! \n", QL_MAIN_UART_PORT);
		return;
	}
	/*****************************************/
	ql_uart_get_dcbconfig(QL_MAIN_UART_PORT, &dcb);
	printf("[%s][%d]baudrate:%d, data_bit:%d, stop_bit:%d, parity_bit:%d, flow_ctrl:%d \r\n", __func__, __LINE__, dcb.baudrate, dcb.data_bit, dcb.stop_bit, dcb.parity_bit, dcb.flow_ctrl);
	dcb.baudrate = QL_UART_BAUD_115200;
	ql_uart_set_dcbconfig(QL_MAIN_UART_PORT, &dcb);
	/*****************************************/

    ql_uart_register_cb(QL_MAIN_UART_PORT, quec_main_uart_callback);	//use callback to read uart data


	for(;;)
	{
		ql_rtos_task_sleep_s(10);
	}
}

//application_init(quec_power_test, "quec_power_test", 2, 0);



static void  quec_set_cam_vdd_test(void)
{

	
	printf("enter ql_set_cam_vdd_output test!! \n");
	ql_rtos_task_sleep_s(2);
	while(1)
	{
		printf("enter test!! \n");
		ql_set_cam_vdd_output(1);
		ql_rtos_task_sleep_s(5);
		ql_set_cam_vdd_output(0);
		ql_rtos_task_sleep_s(5);
	}

}

static void quec_power_vbus_state_get(void)
{
	unsigned char vbus_state = 0;
	printf("enter power api test!! \n");

	ql_rtos_task_sleep_s(5);
	vbus_state = ql_get_vbus_state();
	printf("ql_get_vbus_state: 0x%d\n", vbus_state);
	
	printf("leave power api test!! \n");
}

//application_init(quec_power_vbus_state_get, "quec_power_vbus_state_get", 2, 0);
//application_init(quec_set_cam_vdd_test, "quec_set_cam_vdd_test", 2, 0);
//application_init(quec_power_test1, "quec_power_test1", 2, 0);

