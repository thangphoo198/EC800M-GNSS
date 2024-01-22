/*==========================================================================================================
  Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
==========================================================================================================*/
/*==========================================================================================================

                        EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.

WHEN              WHO         WHAT, WHERE, WHY
------------     -------     -------------------------------------------------------------------------------
09/04/2022        Pony.ma    此文件用于测试SIM卡相关的api
25/06/2022        Sharon.li  增加测试双卡切换
===========================================================================================================*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ql_type.h"
#include "ql_rtos.h"
#include "ql_application.h"
#include "ql_data_call.h"
#include "sockets.h"
#include "netdb.h"
#include "ql_sim.h"
#include "ql_gpio.h"
#include "ql_uart.h"
#define QL_USIM1_DET_PIN  GPIO_PIN_NO_49  //is default

#define SIM_HOT_PLUG_MSG_MAX_NUM 10
#define SIM_INSERT_PIN_LEVEL 0

typedef struct
{
	PIN_LEVEL_E pinlevel;
	unsigned int reserved;
}SIM_HOT_PLUG_MSG_T;


static ql_queue_t sim_hot_plug_queue = NULL;

static void quec_sim_detect_callback(PIN_LEVEL_E pinlevel)
{
	SIM_HOT_PLUG_MSG_T sim_hot_plug_msg = {0};
	sim_hot_plug_msg.pinlevel = pinlevel;
	ql_rtos_queue_release(sim_hot_plug_queue, sizeof(SIM_HOT_PLUG_MSG_T), &sim_hot_plug_msg, QL_NO_WAIT);
}


static void ql_sim_test_hot_plug_task(void * argv)
{
	int ret = 0;
	int card_status = 0;
	char data[64] = {0};
	size_t data_len = 32;
	SIM_HOT_PLUG_MSG_T sim_hot_plug_msg = {0};

	//ql_rtos_task_sleep_s(10);

	printf("<--------example_sim.c--ql_sim_test_hot_plug_task----------->\r\n");
	//set detect gpio, if not use default.
	ret = ql_sim1_detect_gpio_config(QL_USIM1_DET_PIN);
	if(ret != QL_SIM_SUCCESS)
		printf("ql_sim1_detect_gpio_config() fail ret(%d)\r\n",ret);

	ql_rtos_queue_create(&sim_hot_plug_queue, sizeof(SIM_HOT_PLUG_MSG_T), SIM_HOT_PLUG_MSG_MAX_NUM);

	ret = ql_sim_config_hot_plug_detect(1,SIM_INSERT_PIN_LEVEL,quec_sim_detect_callback);
	if(ret != QL_SIM_SUCCESS)
		printf("xxxxql_sim_config_hot_plug_detect() fail ret(%d)\r\n",ret);

	ret = ql_sim_get_card_status(&card_status);
	printf("ql_sim_get_card_status ret:%d, status:%d\n",ret,card_status);
	if(QL_SIM_STATUS_READY == card_status)
	{
		ret = ql_sim_get_phonenumber(data, data_len);
		printf("ql_sim_get_phonenumber ret:%d, phonenumber:%s\n",ret,data);
	}

	for(;;)
	{
		ql_rtos_queue_wait(sim_hot_plug_queue, &sim_hot_plug_msg, sizeof(SIM_HOT_PLUG_MSG_T), QL_WAIT_FOREVER);
		if(SIM_INSERT_PIN_LEVEL == sim_hot_plug_msg.pinlevel)
		{
			printf("[APP] SIM Insert Pin level:%d\r\n",sim_hot_plug_msg.pinlevel);
		}
		else
		{
			printf("[APP] SIM Unplug Pin level:%d\r\n",sim_hot_plug_msg.pinlevel);

		}
	}


}
//application_init(ql_sim_test_hot_plug_task, "qlsimHot", 4, 0);


static void ql_sim_get_info()// before run this app, you need a sim card without lock ,and this ori card pin is 1234
{
	int i=0;

	int ret = 0;
	char data[64] = {0};
	size_t data_len = 32;

	int card_status = 0;
	
	ret = ql_sim_get_card_status(&card_status);
	printf("[APP]ql_sim_get_card_status ret:%d, status:%d\n",ret,card_status);
	
	ret = ql_sim_get_imsi(data,data_len);
	printf("ql_sim_get_imsi ret:%d, imsi:%s\n",ret,data);
	memset(data,0,sizeof(data));

	ret = ql_sim_get_iccid(data, data_len);
	printf("ql_sim_get_iccid ret:%d, iccid:%s\n",ret,data);
	memset(data,0,sizeof(data));

	ret = ql_sim_get_phonenumber(data, data_len);
	printf("ql_sim_get_phonenumber ret:%d, phonenumber:%s\n",ret,data);
	memset(data,0,sizeof(data));
			
	QL_SIM_PHONE_BOOK_RECORDS_INFO   records;
	ret = ql_sim_read_phonebook_record(QL_SIM_PHONE_BOOK_STORAGE_SM,1,5,NULL,&records);
	for(i=0;i<records.record_count;i++)
			printf("index:%d, username:%s, phonenum:%s\n",records.record[i].index,records.record[i].username,records.record[i].phonenum);

    QL_SIMCARD_INFO pt_info = {0};
    ret = ql_sim_get_simcard_info(&pt_info, 0);
	if(ret != 0)
	{
		printf("ql_sim_get_simcard_info_0 failed ret = %d  \n",ret);
	}
    printf("pt_info.card_status = %d %x\npt_info.iccid = %s\npt_info.imsi = %s\n",pt_info.card_status, &(pt_info.card_status), pt_info.iccid, pt_info.imsi);
    ret = ql_sim_get_simcard_info(&pt_info, 1);
	if(ret != 0)
	{
		printf("ql_sim_get_simcard_info_1 failed ret = %d  \n",ret);
	}
    printf("pt_info.card_status = %d %x\npt_info.iccid = %s\npt_info.imsi = %s\n",pt_info.card_status, &(pt_info.card_status), pt_info.iccid, pt_info.imsi);

}

static void ql_sim_hot_test(void * argv)
{

		printf("==========Sim ql_sim_hot_test will start==========\n");
		int value =0;	

		ql_rtos_task_sleep_s(2);
		ql_gpio_init(GPIO_PIN_NO_124, PIN_DIRECTION_OUT, PIN_PULL_DISABLE, PIN_LEVEL_LOW);

		while(1)
		{
			ql_gpio_set_level(GPIO_PIN_NO_124, PIN_LEVEL_LOW);//鎷変綆-----璁剧疆浣庣偣璇?
			ql_gpio_get_level(GPIO_PIN_NO_124, &value);
			printf("ql_gpio_get_level1 GPIO_PIN_NO_124 L = %d!!!\n",value);
			ql_gpio_set_level(GPIO_PIN_NO_124, PIN_LEVEL_HIGH);//鎷夐珮-----璁剧疆浣庣偣璇?
			ql_rtos_task_sleep_s(1);
			ql_gpio_get_level(GPIO_PIN_NO_124, &value);	  
			printf("ql_gpio_get_level1 GPIO_PIN_NO_124 H = %d!!!\n",value);

			ql_rtos_task_sleep_s(1);
		}

}
//application_init(ql_sim_hot_test, "ql_sim_hot_test", 2, 0);


typedef enum SIM_CTRL_ENUM {
	SIM_SWITCH_TO_1 = 0,//切换卡1为主卡
	SIM_SWITCH_TO_2,
	SIM_GET_INFO,      //获取SIM卡信息
	SIM_START_DATACALL,//使用当前主卡进行datacall
	SIM_SET_STANDY_MODE,//设置卡的待机模式
	SIM_START_TCP_CLIENT,//发起一次TCP client连接
}SIM_CTRL_TYPE_E;


typedef struct
{
	SIM_CTRL_TYPE_E ctrl_msg;
	unsigned int reserved;
}SIM_CTRL_MSG_T;



#define SERIAL_RX_BUFFER_LEN  2048 
static u8 m_RxBuf_Uart1[SERIAL_RX_BUFFER_LEN];
#define SIM_CTRL_MSG_MAX_NUM 10
static ql_queue_t sim_ctrl_msg_queue = NULL;


static void ql_nw_status_callback(int profile_idx, int nw_status)
{
	printf("profile(%d) status: %d\r\n", profile_idx, nw_status);
}

static void datacall_satrt(void)
{
	printf("wait for network register done\r\n");
	//获取当前主卡的网络注册状态
	if(ql_network_register_wait(120) != 0)
	{
		printf("*** network register fail ***\r\n");
	}
	else
	{
		printf("doing network activing ...\r\n");
		
		ql_wan_start(ql_nw_status_callback);
		ql_set_auto_connect(1, TRUE);
		//使用当前主卡进行数据拨号
		ql_start_data_call(1, 0, "3gnet.mnc001.mcc460.gprs", NULL, NULL, 0);
	}
}


static void quec_switch_sim_callback(UINT8 statue)
{
	printf("%s@%d statu(%d)\r\n",__func__,__LINE__,statue);
}

static void quec_control_uart_callback(QL_UART_PORT_NUMBER_E port, void *para)
{
	int ret1 = 0,ret2=0;
	char buf[50] = {0};
	
	SIM_CTRL_MSG_T sim_ctrl_msg = {0};
	
	unsigned int  totalBytes = ql_uart_read(port, m_RxBuf_Uart1, sizeof(m_RxBuf_Uart1));
	if (totalBytes <= 0)
	{
		printf("<-- No data in UART buffer! -->\r\n");
		return;
	}

	if(0 == memcmp(m_RxBuf_Uart1,"SWITCH_TO_1",11)) 
	{
		printf("<-%s -->\r\n",m_RxBuf_Uart1);
		sim_ctrl_msg.ctrl_msg = SIM_SWITCH_TO_1;
		goto end;
	}

	if(0 == memcmp(m_RxBuf_Uart1,"SWITCH_TO_2",11))
	{
		printf("<-%s -->\r\n",m_RxBuf_Uart1);
		sim_ctrl_msg.ctrl_msg = SIM_SWITCH_TO_2;
		goto end;
	}
	
	if(0 == memcmp(m_RxBuf_Uart1,"SIM_GET_INFO",12)) 
	{
		printf("<-%s -->\r\n",m_RxBuf_Uart1);
		sim_ctrl_msg.ctrl_msg = SIM_GET_INFO;
		goto end;
	}
	
	if(0 == memcmp(m_RxBuf_Uart1,"START_DATACALL",12)) 
	{
		printf("<-%s -->\r\n",m_RxBuf_Uart1);
		sim_ctrl_msg.ctrl_msg = SIM_START_DATACALL;
		goto end;
	}
end:
	ql_uart_write(port,m_RxBuf_Uart1,totalBytes);
	memset(m_RxBuf_Uart1,0,SERIAL_RX_BUFFER_LEN);
	
	ql_rtos_queue_release(sim_ctrl_msg_queue, sizeof(SIM_CTRL_MSG_T), &sim_ctrl_msg, QL_NO_WAIT);
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



static void ql_sim_test_ctrl_task(void)
{
	SIM_CTRL_MSG_T sim_ctrl_msg = {0};
	struct ql_data_call_info info = {0};
	char ip4_addr_str[16] = {0};
	static struct in_addr ip4_addr = {0};
	
	ql_rtos_queue_create(&sim_ctrl_msg_queue, sizeof(SIM_CTRL_MSG_T), SIM_CTRL_MSG_MAX_NUM);
	Ql_Control_Port_Open(QL_MAIN_UART_PORT);

	while(1)
	{
		ql_rtos_queue_wait(sim_ctrl_msg_queue, &sim_ctrl_msg, sizeof(SIM_CTRL_MSG_T), QL_WAIT_FOREVER);
		switch(sim_ctrl_msg.ctrl_msg)
		{
			case SIM_SWITCH_TO_1:
			 	ql_sim_switch_card_ex(QL_SIM_0, quec_switch_sim_callback);
				break;
			
			case SIM_SWITCH_TO_2:
			 	ql_sim_switch_card_ex(QL_SIM_1, quec_switch_sim_callback);
				break;
				
			case SIM_GET_INFO:
				ql_sim_get_info();
				break;
			
			case SIM_START_DATACALL:
				datacall_satrt();
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
				break;

			case SIM_START_TCP_CLIENT: 
				ip4_addr = info.v4.addr.ip;
				if(info.v4.state)
				{
					//do_tcp_client_test(ip4_addr);
				}

		}
	}
}

//application_init(ql_sim_test_ctrl_task, "ql_sim_test_ctrl_task",20, 0);


