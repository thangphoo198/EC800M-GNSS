/*================================================================
  Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/


#include <stdio.h>
#include "ql_rtos.h"
#include "ql_application.h"
#include "ql_fota.h"
#include "ql_fs.h"
#include "ql_power.h"
#include "ql_uart.h"

#define fota_exam_log(fmt, ...) printf("[FOTA_EXAM][%s, %d] "fmt"\r\n", __FUNCTION__, __LINE__, ##__VA_ARGS__)


#define FOTA_SERVER_ADDRESS_STEP1 "http://112.31.84.164:8300/august/old_new.bin_1"
#define FOTA_SERVER_ADDRESS_STEP2 "http://112.31.84.164:8300/august/old_new.bin_2"
#define FOTA_FTP_SERVER_USERNAME "quec"
#define FOTA_FTP_SERVER_PASSWD   "quec"
#define PROFILE_IDX 1


void ql_fota_test(void)
{
	int ret = 0;
	//fota_exam_log("========== !!!!!!!!!!!!!!!!!!!! ==========");
    ret = ql_fota_mini_system(PROFILE_IDX, QL_FOTA_DWNLD_MOD_HTTP, FOTA_SERVER_ADDRESS_STEP1 ,FOTA_SERVER_ADDRESS_STEP2, NULL,NULL);
	if(ret != 0){
		fota_exam_log("========== fota test end ==========");
	}
}


#define FOTA_SERVER_ADDRESS_STEP "http://112.31.84.164:8300/august/app.bin"

void ql_full_app_test(void)
{
	int ret = 0;
	//fota_exam_log("========== full fota test success !!!!!!!!!!!!!!!!!!!! ==========");
	fota_exam_log("full fota test star");
    ret = ql_fullfota_app_start(FOTA_SERVER_ADDRESS_STEP);//ql_fota_mini_system(PROFILE_IDX, QL_FOTA_DWNLD_MOD_HTTP, FOTA_SERVER_ADDRESS_STEP1 ,FOTA_SERVER_ADDRESS_STEP2, NULL,NULL);
	if(ret != 0){
		fota_exam_log("==========full fota test end ==========");
	}
}


static ql_flag_t fota_uart_flag;
#define QL_FOTA_UART_READ 0x1

void quec_fota_uart_callback(QL_UART_PORT_NUMBER_E port, void *para)
{
	static char read_flag = 1;
	if(read_flag){
		read_flag = 0;
		ql_rtos_flag_release(fota_uart_flag, QL_FOTA_UART_READ, QL_FLAG_OR);
	}
}

static void quec_fota_uart_test(void * argv)
{
    int ret = -1,event = 0;
	int write_bytes = 0;
	unsigned char data[] = "hello, this is file fota test!!!, please Transfer dfota.bin\n";
	unsigned char read_buf[4096] = {0};
	ql_uart_config_t dcb;
	int count = 0, res = 0,file_len = 0;
	QFILE *fp = NULL;
	qlFotaImgProcCtxPtr ctx = NULL;
	int file_size = 0;

    ret = ql_uart_open(QL_MAIN_UART_PORT, QL_UART_BAUD_115200, QL_FC_HW);
	if (ret) {
		printf("open uart[%d] failed! \n", QL_MAIN_UART_PORT);
		return;
	}
	
	ql_rtos_flag_create(&fota_uart_flag);
	/*****************************************/
	ql_uart_get_dcbconfig(QL_MAIN_UART_PORT, &dcb);
	printf("[%s][%d]baudrate:%d, data_bit:%d, stop_bit:%d, parity_bit:%d, flow_ctrl:%d \r\n", __func__, __LINE__, dcb.baudrate, dcb.data_bit, dcb.stop_bit, dcb.parity_bit, dcb.flow_ctrl);
	dcb.baudrate = QL_UART_BAUD_115200;
	ql_uart_set_dcbconfig(QL_MAIN_UART_PORT, &dcb);
	/*****************************************/

    ql_uart_register_cb(QL_MAIN_UART_PORT, quec_fota_uart_callback);	//use callback to read uart data


	ql_uart_write(QL_MAIN_UART_PORT, data, sizeof(data));
	ql_rtos_flag_wait(fota_uart_flag, QL_FOTA_UART_READ, QL_FLAG_OR, &event, QL_WAIT_FOREVER);

	ctx = ql_fota_init();
	if(!ctx)
	{
		printf("*** fota init fail ***");
		return;
	}
	
	count = 0;
	while((ret >= 0) && (count < 15)){
		ret = ql_uart_read(QL_MAIN_UART_PORT, read_buf, sizeof(read_buf));
		if(ret <= 0){
			count++;
			ql_rtos_task_sleep_ms(10);
			continue;
		}else{
			count = 0;
			file_len += ret;
			res = ql_fota_image_write(ctx, (void *)read_buf, ret);
			if(res < 0){
				printf("ql_fwrite error:%d \n",res);
			}
		}
	}

	if(count >= 15){
		printf("Transfer end:%d ,file_len:%d\n",ret, file_len);
	}
	ql_uart_close(QL_MAIN_UART_PORT);

	ret = ql_fota_image_flush(ctx);
	if(ret)
	{
		printf("*** fota image flush fail ***");
		return;
	}
	printf("ql_fota_image_flush end\n");
	ret = ql_fota_image_verify(ctx);
	if(ret)
	{
		printf("*** fota image verify fail ***");
		return;
	}
	printf("ql_fota_image_verify success! \n");


	printf("ready to power reset!!\n");
	ql_power_reset();
}

//application_init(ql_fota_test, "quec_fota_test", 2, 10);
//application_init(ql_full_app_test, "ql_full_app_test", 2, 10);
//application_init(quec_fota_uart_test, "quec_fota_uart_test", 50, 10);

