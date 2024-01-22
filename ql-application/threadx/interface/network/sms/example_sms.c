/*================================================================
  Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/
/*
 ******************************************************************************
 * @file    example_sms.c
 * @author  rami.zhang
 * @version V1.0.0
 * @date    2020/05/08
 * @brief   This file tests sms APIs
 ******************************************************************************
 */

#include <stdio.h>
#include "ql_application.h"
#include "ql_sms.h"
#include <string.h>
#include "ql_uart.h"
#include "ql_rtos.h"

typedef void (*QL_sms_EventHandlerFunc_t)(unsigned int ind_flag, void *ind_msg_buf, unsigned int ind_msg_len, void *contextPtr);
typedef int  sms_status;

#define sms_log(fmt, args...)	printf(fmt, ##args)
#define SERIAL_RX_BUFFER_LEN 2048
static char m_RxBuf_Uart1[SERIAL_RX_BUFFER_LEN];
quec_task_t	sms_test_task_handler = NULL;
quec_task_t sms_test_task_handler_1 = NULL;
ql_queue_t sms_queue=NULL;

int sms_index;
typedef struct{
UINT32 quec_sms_flag;
UINT8  *data;
UINT32 LEN;
}sms_struct_t;
#define QUEC_SMS_QUEUE_MAX 10 
static void sms_search_message_test(void * argv)
{
	ql_rtos_task_sleep_s(1);
	recvmessage payload;
	ql_search_sms_text_message(sms_index, &payload);	
	printf ("---sms payload:%s---\r\n", payload.buf);
}

/*rami:user callback*/
void user_sms_event_handle_callback(unsigned int flag, void* mes_buf, unsigned int mes_length, void* context_handle)
{
	QL_SMS_STATUS_INFO sms_recv;
	int ret = 0;

	switch(flag)
	{
		case QUEC_CI_MSG_PRIM_NEWMSG_IND:
		case QUEC_VOLTE_NEWMSG_IND:
			{
				sms_log(" QUEC_CI_MSG_PRIM_NEWMSG_IND \n");
				
				ret = ql_pdu_decode(&sms_recv, mes_buf, mes_length);
				if (ret == 0)
				{
					//sender's number
					sms_log("sms_recv.number=%s\n", sms_recv.number);

					//sms encode type, 0-GSM7bit, 1-8bit, 2-UCS2
					sms_log("sms_recv.code_type=%d\n", sms_recv.code_type);

					//sms content
					sms_log("sms_recv.body=%s\n", sms_recv.body);

					//sms time
					sms_log("sms_recv.time=%s\n", sms_recv.time);
				}
			}
			break;
		case QUEC_CI_MSG_PRIM_GET_SMSC_ADDR_CNF:
			{
				sms_log(" QUEC_CI_MSG_PRIM_GET_SMSC_ADDR_CNF \n");
			}
			break;
		//gavin 20201222 add newmsg_index case
		case QUEC_CI_MSG_PRIM_NEWMSG_INDEX_IND:
			{
				sms_log(" QUEC_CI_MSG_PRIM_NEWMSG_INDEX_IND \n");
				printf("---sms index: %d---\r\n",(*(QL_NEWMSG_INDEX*)mes_buf).index);
				sms_index = (*(QL_NEWMSG_INDEX*)mes_buf).index;
				ql_rtos_task_create(&sms_test_task_handler_1, 4096, 101, "sms_search_message_test", sms_search_message_test, NULL);				
			}
			break;
		case QUEC_VOLTE_NEWMSG_INDEX_IND :
			{
				sms_log(" QUEC_VOLTE_NEWMSG_INDEX_IND \n");
				printf("---sms index: %d---\r\n",(*(quec_volte_sms_info_cmti*)mes_buf).index);
				sms_index = (*(quec_volte_sms_info_cmti*)mes_buf).index;
				ql_rtos_task_create(&sms_test_task_handler_1, 4096, 101, "sms_search_message_test", sms_search_message_test, NULL);				
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
    int ret=0;
    sms_struct_t quec_sms_queue;
	unsigned int  totalBytes = ql_uart_read(port, m_RxBuf_Uart1, sizeof(m_RxBuf_Uart1));
	if (totalBytes <= 0)
	{
		printf("<-- No data in UART buffer! -->\r\n");
		return;
	}

	if(0 == memcmp(m_RxBuf_Uart1,"AT+CMGST",7)) 
	{
		sms_log("<-%s -->\r\n",m_RxBuf_Uart1);
        quec_sms_queue.quec_sms_flag=0x01;
        quec_sms_queue.data=NULL;
        quec_sms_queue.LEN=0;
        ql_rtos_queue_release(sms_queue, sizeof(sms_struct_t), (u8 *) (&quec_sms_queue), 0xFFFFFFFF);
		goto end;
	}

	if(0 == memcmp(m_RxBuf_Uart1,"AT+CSCA",7)) 
	{
        quec_sms_queue.quec_sms_flag=0x02;
        quec_sms_queue.data=NULL;
        quec_sms_queue.LEN=0;
        ql_rtos_queue_release(sms_queue, sizeof(sms_struct_t), (u8 *) (&quec_sms_queue), 0xFFFFFFFF);
		goto end;
	}

	
end:
	ql_uart_write(port,m_RxBuf_Uart1,totalBytes);
	memset(m_RxBuf_Uart1,0,SERIAL_RX_BUFFER_LEN);
	return;
}

/*rami: the entry function*/
static void sms_test_func_entry(void * argv)
{
	int  ret;
	ql_uart_config_t dcb;
    sms_struct_t quec_sms_msg;
    char smsc[128] = {0};

	sms_log(" break1 \n");
	ql_rtos_task_sleep_s(10);

	(void)ql_sms_add_event_handler(user_sms_event_handle_callback,NULL);
            ql_rtos_queue_create(&sms_queue, sizeof(sms_struct_t), QUEC_SMS_QUEUE_MAX);
	ql_rtos_task_sleep_s(10);

	sms_log(" break2 \n");

    ret = ql_uart_open(QL_MAIN_UART_PORT, QL_UART_BAUD_115200, QL_FC_NONE);
	if (ret) 
	{
	//	APP_DEBUG("open uart[%d] failed! \n", QL_MAIN_UART_PORT);
		return;
	}
	/*****************************************/
	ql_uart_get_dcbconfig(QL_MAIN_UART_PORT, &dcb);
//	APP_DEBUG("[%s][%d]baudrate:%d, data_bit:%d, stop_bit:%d, parity_bit:%d, flow_ctrl:%d \r\n", __func__, __LINE__, dcb.baudrate, dcb.data_bit, dcb.stop_bit, dcb.parity_bit, dcb.flow_ctrl);
	dcb.baudrate = QL_UART_BAUD_115200;
	dcb.data_bit = QL_UART_DATABIT_8;
	ql_uart_set_dcbconfig(QL_MAIN_UART_PORT, &dcb);
	/*****************************************/
    ql_uart_register_cb(QL_MAIN_UART_PORT, quec_main_uart_callback);	//use callback to read uart data

	ql_uart_write(QL_MAIN_UART_PORT,"MAIN_UART_REDY\r\n",16);
   /* 
	ret = ql_sms_send_pdu_msg("+8618355301818","hello,rami",0);
	if(ret != 0)
	{
		sms_log("send pdu message failed ret = %d  \n",ret);
	}
	ql_rtos_task_sleep_s(10);
	ret = ql_sms_send_pdu_msg("+8618355301818", "hello,你好",1);
	if(ret != 0)
	{
		sms_log("send pdu message failed state = %d  \n",ret);
	}
	*/
	#if 0
	//Leven:send pdu test
	ret=ql_sms_send_pdu("0891683108501505F011000D91683135354741F10000FF07F4F29C9E769F01");
	if(ret != 0)
	{
		sms_log("send pdu message failed state = %d  \n",ret);
	}
	#endif

	//mia 20201015 test get sms center num
	while(1)
	{
        ql_rtos_queue_wait(sms_queue, (u8 *)(&quec_sms_msg), sizeof(sms_struct_t), 0XFFFFFFFF);
        switch(quec_sms_msg.quec_sms_flag)
        {
            case 0x01:
                {
                  ret = ql_sms_send_text_msg("+8618355306818","text TEST","GSM");
                    if(ret != 0)
                    {
                        sms_log("send pdu message failed ret = %d  \n",ret);
                    }
                }
            break;
            case 0x02:
                {
                    memset(smsc,0,sizeof(smsc));
                    ql_get_sms_center_address(smsc);
                    if(ret != 0)
                    {
                        sms_log("get center num failed.");
                    }
                    else
                    {
                        sms_log("get center num success, ret = [%d], smsc=%s\n", ret, smsc);
                    }

                }
            break;
            default:sms_log("default");
        }
	}

}

int quec_sms_test(void)
{
	sms_status   status;

	sms_log(" ========= quec_sms_test start =========\n");
	status =ql_rtos_task_create(&sms_test_task_handler, 10240, 100, "sms_test", sms_test_func_entry, NULL);
	return 0;
}


//application_init(quec_sms_test, "quec_sms_test", 4, 0);


