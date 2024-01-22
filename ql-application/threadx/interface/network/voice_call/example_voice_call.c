/*================================================================
  Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/
/*
 ******************************************************************************
 * @file    example_voice_call.c
 * @author  rami.zhang
 * @version V1.0.0
 * @date    2020/03/23
 * @brief   This file tests voice call APIs
 ******************************************************************************
 */

#include <stdio.h>
#include "ql_application.h"
#include "ql_voice_call.h"
#include <string.h>
#include "ql_uart.h"
#include "ql_audio.h"

#define APP_DEBUG(fmt, args...)	printf(fmt, ##args)
#define voice_log(fmt, args...)	printf(fmt, ##args)

#define SERIAL_RX_BUFFER_LEN  2048
static u8 m_RxBuf_Uart1[SERIAL_RX_BUFFER_LEN];

typedef void (*QL_voice_call_EventHandlerFunc_t)(unsigned int ind_flag, void *ind_msg_buf, unsigned int ind_msg_len, void *contextPtr);
typedef int  voice_status;

quec_task_t	voice_test_task_handler = NULL;

/*rami:user callback*/
void user_event_handle_callback(unsigned int flag, void* mes_buf, unsigned int mes_length, void* context_handle)
{
	switch(flag)
	{
		case QUEC_CC_INCOMING_CALL_IND:
			{
				voice_log(" QUEC_CC_INCOMING_CALL_IND \n");
			}
			break;
		case QUEC_CC_WAITING_CALL_IND:
			{
				voice_log(" QUEC_CC_WAITING_CALL_IND \n");
			}
			break;
		case QUEC_CC_CONNECT_CALL_IND:
			{
				voice_log(" QUEC_CC_CONNECT_CALL_IND \n");
			}
			break;
		case QUEC_CC_DISCONNECT_CALL_IND:
			{
				voice_log(" QUEC_CC_DISCONNECT_CALL_IND \n");
			}
			break;
		case QUEC_VOLTE_INCOMING_CALL_IND:
			{
				voice_log(" QUEC_VOLTE_INCOMING_CALL_IND \n");
			}
			break;
		case QUEC_VOLTE_CONNECT_CALL_IND:
			{
				voice_log(" QUEC_VOLTE_CONNECT_CALL_IND \n");
			}
			break;
		case QUEC_VOLTE_DISCONNECT_CALL_IND:
			{
				voice_log(" QUEC_VOLTE_DISCONNECT_CALL_IND \n");
			}
			break;
		case QUEC_VOLTE_WAITING_CALL_IND:
			{
				voice_log(" QUEC_VOLTE_WAITING_CALL_IND \n");
			}
			break;
		case QUEC_DIALING_CALL_IND:
			{
				voice_log(" QUEC_DIALING_CALL_IND \n");
			}
			break;
		case QUEC_ALERTING_CALL_IND:
			{
				voice_log(" QUEC_ALERTING_CALL_IND \n");
			}
			break;
		default:
			break;
			
	}
	
}



static void quec_main_uart_callback(QL_UART_PORT_NUMBER_E port, void *para)
{
	int ret1 = 0,ret2=0;
	char buf[50] = {0};
	
	unsigned int  totalBytes = ql_uart_read(port, m_RxBuf_Uart1, sizeof(m_RxBuf_Uart1));
	if (totalBytes <= 0)
	{
		printf("<-- No data in UART buffer! -->\r\n");
		return;
	}

	if(0 == memcmp(m_RxBuf_Uart1,"ATD",3)) 
	{
		APP_DEBUG("<-%s -->\r\n",m_RxBuf_Uart1);
		ret1 = strstr(m_RxBuf_Uart1,"ATD");
		ret2 = strstr(m_RxBuf_Uart1,";\r\n");
		//APP_DEBUG("ret1(%d)ret2(%d)\r\n",ret1,ret2);
		if(ret2)
		{
			memcpy(buf,m_RxBuf_Uart1+3,ret2-(ret1+3));
			
			APP_DEBUG("Call Number:(%s)\r\n",buf);
			ret1 = ql_voice_call_start(buf);
			voice_log(" ret1 is %d  \n",ret1);
		}
		
		goto end;
	}

	if(0 == memcmp(m_RxBuf_Uart1,"ATH",3)) //挂断电话
	{
		APP_DEBUG("<-%s -->\r\n",m_RxBuf_Uart1);
		ret1 = ql_voice_call_end();
		goto end;
	}
	
end:
	ql_uart_write(port,m_RxBuf_Uart1,totalBytes);
	memset(m_RxBuf_Uart1,0,SERIAL_RX_BUFFER_LEN);
	return;
}


static void voice_test_func_entry(void * argv)
{
	int  character,ret1 = 0,ret2 = 0;
	char buf[128] = {0};
	int ret =0;
	ql_uart_config_t dcb;

	ql_rtos_task_sleep_s(5);

	printf("<-------------------example_voice_call.c------------------------->\r\n");

	ql_codec_choose(AUD_INTERNAL_CODEC, NULL);//使用内置codec
	ql_voice_call_add_event_handler(user_event_handle_callback,NULL);//注册call事件相关的回调函数

    ret = ql_uart_open(QL_MAIN_UART_PORT, QL_UART_BAUD_115200, QL_FC_NONE);
	if (ret) 
	{
		APP_DEBUG("open uart[%d] failed! \n", QL_MAIN_UART_PORT);
		return;
	}
	/*****************************************/
	ql_uart_get_dcbconfig(QL_MAIN_UART_PORT, &dcb);
	APP_DEBUG("[%s][%d]baudrate:%d, data_bit:%d, stop_bit:%d, parity_bit:%d, flow_ctrl:%d \r\n", __func__, __LINE__, dcb.baudrate, dcb.data_bit, dcb.stop_bit, dcb.parity_bit, dcb.flow_ctrl);
	dcb.baudrate = QL_UART_BAUD_115200;
	dcb.data_bit = QL_UART_DATABIT_8;
	ql_uart_set_dcbconfig(QL_MAIN_UART_PORT, &dcb);
	/*****************************************/
    ql_uart_register_cb(QL_MAIN_UART_PORT, quec_main_uart_callback);	//use callback to read uart data

	ql_uart_write(QL_MAIN_UART_PORT,"MAIN_UART_REDY\r\n",16);

	while(1)
	{
	
		ql_rtos_task_sleep_s(10);
	}	

}

int quec_voice_call_test(void)
{
	voice_status   status;

	//voice_log(" quec_voice_call_test start \n");
	status =ql_rtos_task_create(&voice_test_task_handler, 4096, 100, "voice_test", voice_test_func_entry, NULL);
	/*
	status = quec_rtos_task_create(&voice_test_task_handler, 2048, 100, "voice_test", voice_test_func_entry, "I am voice call test");
	*/
	return 0;
}


//application_init(quec_voice_call_test, "quec_voice_call_test", 2, 0);

