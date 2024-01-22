
/*==========================================================================================================
  Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
===========================================================================================================*/

#include <stdio.h>
#include "ql_uart.h"
#include "ql_application.h"
#include "ql_log.h"

#define test_log(fmt, args...)	printf(fmt, ##args)









void quec_uart_callback(QL_UART_PORT_NUMBER_E port, void *para)
{
	int read_len = 0;
	char r_data[1024] = {0};
	read_len = ql_uart_read(port, r_data, sizeof(r_data));
	test_log("uart[%d] callback read data, data:%s, read_len:%d \n", port, r_data, read_len);
}

static void quec_main_uart_test(void * argv)
{
    int ret = -1;
    char r_data[128] = {0};
	int write_bytes = 0;
	unsigned char data[] = "hello, this is main uart test!!!\n";
	ql_uart_config_t dcb;
    ql_log_mask_set(QL_LOG_APP_MASK, QL_LOG_PORT_UART);
    ret = ql_uart_open(QL_MAIN_UART_PORT, QL_UART_BAUD_115200, QL_FC_NONE);
	if (ret) {
		test_log("open uart[%d] failed! %d \n", QL_MAIN_UART_PORT,ret);
		return;
	}

	/*****************************************/
	ql_uart_get_dcbconfig(QL_MAIN_UART_PORT, &dcb);
	test_log("[%s][%d]baudrate:%d, data_bit:%d, stop_bit:%d, parity_bit:%d, flow_ctrl:%d \r\n", __func__, __LINE__, dcb.baudrate, dcb.data_bit, dcb.stop_bit, dcb.parity_bit, dcb.flow_ctrl);
	dcb.baudrate = QL_UART_BAUD_115200;
	ql_uart_set_dcbconfig(QL_MAIN_UART_PORT, &dcb);
	/*****************************************/

    ql_uart_register_cb(QL_MAIN_UART_PORT, quec_uart_callback);	//use callback to read uart data
    
	while (1)
	{   test_log("I still alive...%s\r\n",r_data);
        ret = ql_uart_write(QL_MAIN_UART_PORT, data, sizeof(data));
        if(ret == QL_UART_CTS_HIGH)
        {
           test_log("CTS_HIGH");
        }
		ql_rtos_task_sleep_s(5);
		
	}    
}


void quec_usbcdc_callback(QL_UART_PORT_NUMBER_E port, void *para)
{
	int read_len = 0;
	char r_data[1024] = {0};
	read_len = ql_uart_read(port, r_data, sizeof(r_data));
	test_log("uart[%d] callback read data, data:%s, read_len:%d \n", port, r_data, read_len);
}

static void quec_usbcdc_test(void * argv)
{
    int ret = -1;
    char r_data[128] = {0};
	int write_bytes = 0;
	unsigned char data[] = "hello, this is uart test!!!, abcdefghijklmnopqrstuvwxyz, 1234567890\n";
	ql_uart_config_t dcb;

    ql_uart_open(QL_USB_CDC_PORT, QL_UART_BAUD_115200, QL_FC_NONE);

    ql_uart_register_cb(QL_USB_CDC_PORT, quec_usbcdc_callback);	//use callback to read uart data
    
	while (1)
	{   test_log("I still alive...%s\r\n",r_data);
        ql_uart_open(QL_USB_CDC_PORT, QL_UART_BAUD_115200, QL_FC_NONE);
        ret = ql_uart_write(QL_USB_CDC_PORT, data, sizeof(data));
		ql_rtos_task_sleep_s(5);
        ql_uart_close(QL_USB_CDC_PORT);
		
	}    
}


static void ql_test_baudrate(void * argv)
{
    int ret = -1;
    char r_data[128] = {0};
	int write_bytes = 0;
	unsigned char data[] = "hello, this is uart test!!!, abcdefghijklmnopqrstuvwxyz, 1234567890\n";
	ql_uart_config_t dcb;
    ql_log_mask_set(QL_LOG_APP_MASK, QL_LOG_PORT_UART);
    ret = ql_uart_open(QL_MAIN_UART_PORT, QL_UART_BAUD_256000, QL_FC_NONE);
	if (ret) {
		test_log("open uart[%d] failed! %d \n", QL_MAIN_UART_PORT,ret);
		return;
	}

	/*****************************************/
	ql_uart_get_dcbconfig(QL_MAIN_UART_PORT, &dcb);
	test_log("[%s][%d]baudrate:%d, data_bit:%d, stop_bit:%d, parity_bit:%d, flow_ctrl:%d \r\n", __func__, __LINE__, dcb.baudrate, dcb.data_bit, dcb.stop_bit, dcb.parity_bit, dcb.flow_ctrl);
	dcb.baudrate = QL_UART_BAUD_256000;
	ql_uart_set_dcbconfig(QL_MAIN_UART_PORT, &dcb);
	/*****************************************/

    ql_uart_register_cb(QL_MAIN_UART_PORT, quec_uart_callback);	//use callback to read uart data
    
	while (1)
	{   test_log("I still alive...%s\r\n",r_data);
        ret = ql_uart_write(QL_MAIN_UART_PORT, data, sizeof(data));
        if(ret == QL_UART_CTS_HIGH)
        {
           test_log("CTS_HIGH");
        }
		ql_rtos_task_sleep_s(2);
		
	}    
}


/*流控休眠唤醒测试方法：模块休眠的时候，串口工具发数据给模块，利用其它唤醒源唤醒模块，看模块收到uart数据是否完整*/
//application_init(quec_main_uart_test, "quec_uart_test1", 10, 0);
//application_init(quec_usbcdc_test, "quec_usb", 10, 0);
//application_init(ql_test_baudrate, "ql_test_baudrate", 10, 0);




