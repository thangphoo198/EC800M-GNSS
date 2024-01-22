/*================================================================
  Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/
#include <stdarg.h>
#include "ql_type.h"
#include "ql_data_call.h"
#include "ql_rtos.h"
#include "ql_application.h"
#include <stdio.h>
#include "sockets.h"
#include "ql_uart.h"
#include "ql_func.h"

#define MSG_MAX_NUM 10
#define APP_DEBUG printf	


typedef enum 
{
	QUEC_START_DATACALL,
	QUEC_START_DATACALL_APN_CHANGE,
	QUEC_STOP_DATACALL,
	QUEC_START_DATACALL_V6,//����ipV6���ݲ���
}DATACALL_ACTION_E;

typedef struct
{
	int flag;
	DATACALL_ACTION_E msg;
}DATACALL_ACTION_T;

static char SetApnFlag = 0;
char ApnName[]="3gnet";


static ql_queue_t rtos_test_queue = NULL;
#if 1
#define SERIAL_RX_BUFFER_LEN  2048
static u8 m_RxBuf_Uart1[SERIAL_RX_BUFFER_LEN];

static void quec_control_uart_callback(QL_UART_PORT_NUMBER_E port, void *para)
{
	int ret1 = 0,ret2=0;
	char buf[50] = {0};
	
	unsigned int  totalBytes = ql_uart_read(port, m_RxBuf_Uart1, sizeof(m_RxBuf_Uart1));
	if (totalBytes <= 0)
	{
		printf("<-- No data in UART buffer! -->\r\n");
		return;
	}

	if(0 == memcmp(m_RxBuf_Uart1,"QUEC_START_DATACALL",14)) //�������ݲ���
	{
		APP_DEBUG("<-%s -->\r\n",m_RxBuf_Uart1);
		DATACALL_ACTION_T quecdatacall_msg = {0};
		quecdatacall_msg.msg = QUEC_START_DATACALL;
		SetApnFlag = 0;

		ql_rtos_queue_release(rtos_test_queue, sizeof(DATACALL_ACTION_T), (u8*)(&quecdatacall_msg), 0);
		
		goto end;
	}
	
	if(0 == memcmp(m_RxBuf_Uart1,"QUEC_START_V6_DATACALL",22)) //�������ݲ���
	{
		APP_DEBUG("<-%s -->\r\n",m_RxBuf_Uart1);
		DATACALL_ACTION_T quecdatacall_msg = {0};
		quecdatacall_msg.msg = QUEC_START_DATACALL_V6;
		SetApnFlag = 0;

		ql_rtos_queue_release(rtos_test_queue, sizeof(DATACALL_ACTION_T), (u8*)(&quecdatacall_msg), 0);
		
		goto end;
	}
	
	if(0 == memcmp(m_RxBuf_Uart1,"APN_CHANGE",10)) //APN �����ı�
	{
		APP_DEBUG("<-%s -->\r\n",m_RxBuf_Uart1);
		DATACALL_ACTION_T quecdatacall_msg = {0};
		quecdatacall_msg.msg = QUEC_START_DATACALL_APN_CHANGE;
		SetApnFlag = 1;

		ql_rtos_queue_release(rtos_test_queue, sizeof(DATACALL_ACTION_T), (u8*)(&quecdatacall_msg), 0);
		
		goto end;
	}

	if(0 == memcmp(m_RxBuf_Uart1,"Stop_DataCall",13)) //ֹͣ���ݲ���
	{
		APP_DEBUG("<-%s -->\r\n",m_RxBuf_Uart1);
		
		DATACALL_ACTION_T quecdatacall_msg = {0};
		quecdatacall_msg.msg = QUEC_STOP_DATACALL;
		ql_rtos_queue_release(rtos_test_queue, sizeof(DATACALL_ACTION_T), (u8*)(&quecdatacall_msg), 0);
		
		goto end;
	}
	
end:
	ql_uart_write(port,m_RxBuf_Uart1,totalBytes);
	memset(m_RxBuf_Uart1,0,SERIAL_RX_BUFFER_LEN);
	return;
}

static unsigned char ControlPortInitFlag = 0;
static unsigned char Ql_Control_Port_Open(QL_UART_PORT_NUMBER_E port)
{
	int ires;
	
	ires = ql_uart_open(port, QL_UART_BAUD_115200, QL_FC_NONE);
	if (ires) 
	{
		printf("ql_open cdc fail\r\n");
		return 0xff;
	}
	
    ql_uart_register_cb(port, quec_control_uart_callback);	//use callback to read uart data
	ControlPortInitFlag = 1;
	return 0;
}           

static void myprintk(const char *str, ...)
{
	va_list varg;
	int retv;
	static char sbuffer[2200];  
	int i,j,len;
    int port_no = QL_MAIN_UART_PORT;
	unsigned char ret;
	if(!ControlPortInitFlag)
		Ql_Control_Port_Open(QL_MAIN_UART_PORT);
    memset(sbuffer, 0, sizeof(sbuffer));
    va_start( varg, str );                  
    retv=vsprintf(sbuffer, str,  varg); 
    va_end( varg );
    len = strlen(sbuffer);

	ql_uart_write(port_no,sbuffer, len);
}
#endif

int data_call_state=-1;

static void ql_nw_status_callback(int profile_idx, int nw_status)
{
	printf("[APP]ql_nw_status_callback: profile%d status=%d\r\n", profile_idx, nw_status);
	data_call_state=nw_status;
}

static void ql_data_call_cb(int profile_idx, int nw_status)
{
	data_call_state=nw_status;
	
	printf("[APP]ql_data_call_cb: profile(%d) status(%d) data_call_state(%d)\r\n", profile_idx, nw_status,data_call_state);
}


static void datacall_test_sencond(void * argv)
{
	struct ql_data_call_info info = {0};
	char ip4_addr_str[16] = {0};
	int i=2,ret=0;

	printf("<-----------------example_datacall.c---------------------->\r\n");
	Ql_Control_Port_Open(QL_MAIN_UART_PORT);
	


	while(1)
	{

		printf("========== datacall test will start[%d] ==========\r\n",i);
		printf("wait for network register done\r\n");
		if(ql_network_register_wait(120) != 0)
		{
			printf("*** network register fail ***\r\n");
		}
		else
		{
			//data_call_state=-1;
			//ql_wan_start(ql_nw_status_callback);//�˴����õĻص�������ql_set_data_call_asyn_mode�ӿڵĻص�ȡ�������˽ӿ��Ա�������
			ql_set_auto_connect(1, TRUE);
			if(i==1)
			{
				ql_set_data_call_asyn_mode(1, ql_data_call_cb);
				printf("Enable data call Asyn mode\r\n");
			}
			else if(i==2)
			{
				ql_set_data_call_asyn_mode(0, ql_data_call_cb);
				printf("Enable data call Sync mode\r\n");
			}
			ret=ql_start_data_call(1, 0,NULL, NULL, NULL, 0);
			printf("ql_start_data_call  ret=%d\r\n", ret);
			
			while(data_call_state == -1)
			{
				ql_rtos_task_sleep_ms(5000);
				printf("loop data_call_state=%d\n", data_call_state);
			}
			
			//printf("data_call_state=%d\n\n", data_call_state);

			ql_get_data_call_info(1, 0, &info);
			printf("info.profile_idx: %d\r\n", info.profile_idx);
			printf("info.ip_version: %d\r\n", info.ip_version);
			printf("info.v4.state: %d\r\n", info.v4.state);
			printf("info.v4.reconnect: %d\r\n", info.v4.reconnect);

			inet_ntop(AF_INET, &info.v4.addr.ip, ip4_addr_str, sizeof(ip4_addr_str));
			printf("info.v4.addr.ip: %s\r\n", ip4_addr_str);

			inet_ntop(AF_INET, &info.v4.addr.pri_dns, ip4_addr_str, sizeof(ip4_addr_str));
			printf("info.v4.addr.pri_dns: %s\r\n", ip4_addr_str);

			inet_ntop(AF_INET, &info.v4.addr.sec_dns, ip4_addr_str, sizeof(ip4_addr_str));
			printf("info.v4.addr.sec_dns: %s\r\n", ip4_addr_str);
		}
		

		ret=ql_stop_data_call(1, 0);
		printf("ql_stop_data_call  ret=%d\r\n", ret);
		
		ql_rtos_task_sleep_ms(5000);
	}
}



static void datacall_test_one(void * argv)
{
	struct ql_data_call_info info = {0};
	char ip4_addr_str[16] = {0};
	char ip6_addr_str[64] = {0};
	
	static struct in_addr ip4_addr = {0};
	int ret=0;

	printf("<-----------------example_datacall.c---------------------->\r\n");
	Ql_Control_Port_Open(QL_MAIN_UART_PORT);
	
	ql_rtos_queue_create(&rtos_test_queue, sizeof(DATACALL_ACTION_T), MSG_MAX_NUM);

	DATACALL_ACTION_T msg;

	while(1)
	{
		ql_rtos_queue_wait(rtos_test_queue, (u8*)(&msg), sizeof(msg), 0xFFFFFFFF);  // wait for the message from main task

		switch(msg.msg)
		{
			case QUEC_START_DATACALL:
			case QUEC_START_DATACALL_APN_CHANGE:
				printf("wait for network register done\r\n");
				if(ql_network_register_wait(120) != 0)
				{
					printf("*** network register fail ***\r\n");
				}
				else
				{
					ql_wan_start(ql_nw_status_callback);//�˴����õĻص�������ql_set_data_call_asyn_mode�ӿڵĻص�ȡ�������˽ӿ��Ա�������
					//ql_set_auto_connect(1, TRUE);
					ql_set_data_call_asyn_mode(0, ql_data_call_cb);
					
					if(SetApnFlag)
					{
						printf("Enable data call Sync mode APN Name:%s\r\n",ApnName);
						ret=ql_start_data_call(1, 0,ApnName, NULL, NULL, 0);
					}
					else
					{
						printf("Enable data call Sync mode APN Name:NULL\r\n");
						ret=ql_start_data_call(1, 0,NULL, NULL, NULL, 0);
					}
					printf("ql_start_data_call  ret=%d\r\n", ret);
					
					while(data_call_state == -1)
					{
						ql_rtos_task_sleep_ms(100);
					}
					printf("data_call_state Success=%d\n\n", data_call_state);

					ql_get_data_call_info(1, 0, &info);
					printf("info.profile_idx: %d\r\n", info.profile_idx);
					printf("info.ip_version: %d\r\n", info.ip_version);
					printf("info.v4.state: %d\r\n", info.v4.state);
					printf("info.v4.reconnect: %d\r\n", info.v4.reconnect);

					inet_ntop(AF_INET, &info.v4.addr.ip, ip4_addr_str, sizeof(ip4_addr_str));
					printf("info.v4.addr.ip: %s\r\n", ip4_addr_str);

					inet_ntop(AF_INET, &info.v4.addr.pri_dns, ip4_addr_str, sizeof(ip4_addr_str));
					printf("info.v4.addr.pri_dns: %s\r\n", ip4_addr_str);

					inet_ntop(AF_INET, &info.v4.addr.sec_dns, ip4_addr_str, sizeof(ip4_addr_str));
					printf("info.v4.addr.sec_dns: %s\r\n", ip4_addr_str);
				}
				break;
				
			case QUEC_STOP_DATACALL:
				ret=ql_stop_data_call(1, 0);
				printf("ql_stop_data_call  ret=%d\r\n", ret);
				break;
				
			case QUEC_START_DATACALL_V6://V6 ���ݲ���
				
				ql_set_data_call_asyn_mode(0, ql_data_call_cb);
				ret= ql_start_data_call(1,1,NULL, NULL, NULL, 0);
				
				while(data_call_state == -1)
				{
					ql_rtos_task_sleep_ms(100);
				}
				
				printf("data_call_state Success=%d\n\n", data_call_state);
				
				ql_get_data_call_info(1, 1, &info);
				
				printf("[ST-INFO] profile_idx: %d\r\n", info.profile_idx);
				printf("[ST-INFO] ip_version: %d\r\n", info.ip_version);
				printf("[ST-INFO] v6.state: %d\r\n", info.v6.state);
				printf("[ST-INFO] v6.reconnect: %d\r\n", info.v6.reconnect);
				inet_ntop(AF_INET6, &info.v6.addr.ip, ip6_addr_str, sizeof(ip6_addr_str));
				printf("[ST-INFO] v6.addr.ip: %s\r\n", ip6_addr_str);
				inet_ntop(AF_INET6, &info.v6.addr.pri_dns, ip6_addr_str, sizeof(ip6_addr_str));
				printf("[ST-INFO] v6.addr.pri_dns: %s\r\n", ip6_addr_str);
				inet_ntop(AF_INET6, &info.v6.addr.sec_dns, ip6_addr_str, sizeof(ip6_addr_str));
				printf("[ST-INFO] v6.addr.sec_dns: %s\r\n", ip6_addr_str);
				
				break;
		}
	}
}
application_init(datacall_test_one, "datacall_test", 2, 0);


