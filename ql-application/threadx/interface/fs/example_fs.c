/*================================================================
  Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ql_fs.h"
#include "ql_uart.h"
#include "ql_audio.h"
#include "ql_application.h"
#include "ql_rtos.h"
#include "ql_func.h"
//#include "ql_spi_nor.h"


#define test_log(fmt, args...)	printf(fmt, ##args)


//#define EXTERNAL_FS      0

#define FILE_NAME			"testFile.txt"
#define FILE_CONTENT 		"1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define DIR_NAME			"testDir"

#define C_DISK				"C:"
#define C_ROOT_PATH			""C_DISK"/"
#define C_FILE_UNDER_ROOT 	""C_DISK"/"FILE_NAME""
#define C_DIR_PATH 			""C_DISK"/"DIR_NAME""
#define C_FILE_UNDER_DIR	""C_DIR_PATH"/"FILE_NAME""


#define U_DISK				"U:"
#define U_ROOT_PATH			""U_DISK"/"
#define U_FILE_UNDER_ROOT 	""U_DISK"/"FILE_NAME""
#define U_DIR_PATH 			""U_DISK"/"DIR_NAME""
#define U_FILE_UNDER_DIR	""U_DIR_PATH"/"FILE_NAME""

#define B_DISK				"B:"
#define B_ROOT_PATH			""B_DISK"/"
#define B_FILE_UNDER_ROOT 	""B_DISK"/"FILE_NAME""
#define B_DIR_PATH 			""B_DISK"/"DIR_NAME""
#define B_FILE_UNDER_DIR	""B_DIR_PATH"/"FILE_NAME""


/*---- ql_file_demo 使用说明 ----*/

/*describe ：demo实现了wav格式音频文件通过串口传输写入到FS中，并进行播放的功能
**1.demo用到了主串口和调试串口，主串口用作cmd、data等信息的交互，调试串口用作log的打印
**2.QCOM打开主串口，有以下指令
**2.1 FILE_NEW:filename.wav   //新建文件
**2.2 FILE_SIZE:filesize   //需指定要写入到FS的wav文件大小
**2.3 FILE_INPUT         //输入此指令后，按照主串口交互信息进行wav文件的导入
**2.4 FILE_PLAY:filename.wav //播放写入到FS的wav文件
**2.5 FILE_REMOVE:filename.wav //删除指定的文件
*/

#define MAX_FILE_PATH_SIZE  64
#define UART_FILE_DEMO_BUFFSIZE   2048


//指向文件创建的路径
unsigned char *pFilePath = NULL;
unsigned char filePath_buf[MAX_FILE_PATH_SIZE] = {0};

//此变量记录当前MainUart处于什么模式,0:cmd模式；1:数据模式
static unsigned char mainUartMode = 0;

//此数组记录MianUart收到的cmd数据
static unsigned char main_uart_cmd_buff[UART_FILE_DEMO_BUFFSIZE];
//指向接收到数据的buffer
static unsigned char * MainUartDataPtr =  NULL;


static unsigned int file_size	= 0;//记录当前要写入文件的大小

char buf[128] = {0};//用于主串口与上位机交互的LOG信息buf

typedef enum 
{
	FILE_NOCMD,
	FILE_NEW,
	FILE_INPUT,
	FILE_SIZE,
	FILE_WRITE,
	FILE_PLAY,
	FILE_REMOVE,
	
}FILE_DEMO_E;


typedef struct
{
	FILE_DEMO_E msg;
	void *pdata;
	unsigned int datalen;
	void *pFilePath;
}UART_FILE_ACTION_T;

static ql_queue_t rtos_test_queue = NULL;


int ql_cb1_wav_file_play(char *p_data, int len, int res) //p_data and len is not usd
{
	test_log("[carola] entern ql_cb_wav_file_play res = %d\n", res);
}

void quec_uart1_callback(QL_UART_PORT_NUMBER_E port, void *para)
{
	UART_FILE_ACTION_T quecuart_file_msg = {0};
	quecuart_file_msg.pFilePath = filePath_buf;
	char *p = NULL;
	if(mainUartMode == 0)
	{
		ql_uart_read(QL_MAIN_UART_PORT,main_uart_cmd_buff, UART_FILE_DEMO_BUFFSIZE);	
	}
	else 
	{
		unsigned int total_read = 0;
		unsigned char * tempPtr = MainUartDataPtr;
		//此变量记录每次MainUart收到的数据的个数(byte)
		unsigned int MainUartReadBytes = 0;
		while(file_size > total_read)
		{
			tempPtr += MainUartReadBytes;
			MainUartReadBytes = ql_uart_read(QL_MAIN_UART_PORT,tempPtr, UART_FILE_DEMO_BUFFSIZE);	
			total_read += MainUartReadBytes; 
			//test_log("total_read:%d, MainUartReadBytes:%d",total_read,MainUartReadBytes);
		}
		
		//如果上面数据接收完成，发送消息给Mian task进行将数据写入文件里
		quecuart_file_msg.msg=FILE_WRITE;
		quecuart_file_msg.pdata = MainUartDataPtr;
		quecuart_file_msg.datalen = file_size;

		mainUartMode = 0;//重新变为cmd 模式
	}
	

	if(0 == memcmp(main_uart_cmd_buff,"FILE_NEW",8)) 
	{
		test_log("<-- read_buff data %s! -->\r\n",main_uart_cmd_buff);
		quecuart_file_msg.msg = FILE_NEW;
		p = strstr(main_uart_cmd_buff,":");
		if(p)
		{
			sprintf(quecuart_file_msg.pFilePath,"U:\/\%s",p+1);
			test_log("file_path %s\r\n",quecuart_file_msg.pFilePath);
		}
		goto end;
	}
	if(0 == memcmp(main_uart_cmd_buff,"FILE_SIZE",9)) 
	{
		test_log("<-- read_buff data %s! -->\r\n",main_uart_cmd_buff);
		quecuart_file_msg.msg = FILE_SIZE;
		
		p = strstr(main_uart_cmd_buff,":");
		if(p)
		{	
			file_size = atoi(p+1);
			test_log("will write size:%d\r\n",file_size);
			MainUartDataPtr = malloc(file_size);
			
		}
		goto end;
	}
	
	if(0 == memcmp(main_uart_cmd_buff,"FILE_INPUT",10)) 
	{
		test_log("<-- read_buff data %s! -->\r\n",main_uart_cmd_buff);
		quecuart_file_msg.msg = FILE_INPUT;
		mainUartMode =1;//将串口更改为数据模式
		
		goto end;
	}

	if(0 == memcmp(main_uart_cmd_buff,"FILE_PLAY",9)) 
	{
		test_log("<-- read_buff data %s! -->\r\n",main_uart_cmd_buff);
		quecuart_file_msg.msg = FILE_PLAY;
		p = strstr(main_uart_cmd_buff,":");
		if(p)
		{
			sprintf(quecuart_file_msg.pFilePath,"U:\/\%s",p+1);
			test_log("file_path %s\r\n",quecuart_file_msg.pFilePath);
		}
		goto end;
	}

	if(0 == memcmp(main_uart_cmd_buff,"FILE_REMOVE",11)) 
	{
		test_log("<-- read_buff data %s! -->\r\n",main_uart_cmd_buff);
		quecuart_file_msg.msg = FILE_REMOVE;
		p = strstr(main_uart_cmd_buff,":");
		if(p)
		{
			sprintf(quecuart_file_msg.pFilePath,"U:\/\%s",p+1);
		}	
		goto end;
	}
	
end:
	//ql_uart_write(port,read_buff,readbytes);
	
    memset(main_uart_cmd_buff,0,UART_FILE_DEMO_BUFFSIZE);
	
	ql_rtos_queue_release(rtos_test_queue, sizeof(UART_FILE_ACTION_T), (u8*)(&quecuart_file_msg), 0);
	return;
}

static void ql_file_demo(void * argv)
{
	test_log("<----Test a file and uart demo---->\r\n");
	test_log("%s\r\n",U_FILE_UNDER_ROOT);
	QFILE * fp = NULL;
	int ret =-1;
	
	//等待audio初始化好
	while(!ql_get_audio_state()){
		ql_rtos_task_sleep_ms(50);
	}

	printf("wav_test start ...\r\n");
	
	ql_audio_play_init(ql_cb1_wav_file_play);
	ql_set_audio_path_receiver();
	ql_set_volume(10);
	ql_codec_choose(AUD_INTERNAL_CODEC, NULL);
	
	ql_uart_register_cb(QL_MAIN_UART_PORT, quec_uart1_callback);		
    ql_uart_open(QL_MAIN_UART_PORT, QL_UART_BAUD_115200, QL_FC_HW);
	ql_rtos_queue_create(&rtos_test_queue, sizeof(UART_FILE_ACTION_T), 10);
	UART_FILE_ACTION_T cmd_msg;
	
	while(1)
	{
		
		ql_rtos_queue_wait(rtos_test_queue, (u8*)(&cmd_msg), sizeof(cmd_msg), 0xFFFFFFFF);
		switch (cmd_msg.msg)
		{
			case FILE_NEW:
				test_log("creat a new file\r\n");
				pFilePath = (unsigned char *)cmd_msg.pFilePath;
				fp = ql_fopen(pFilePath, "w+");
			
			    if(NULL == fp)
			    {
					test_log("[FS]ERROR!!! *** file create fail: %s \r\n", pFilePath);
				}
				sprintf(buf,"[FS]SUCCESS!!! *** file create OK: %s \r\n", pFilePath);
			break;
			case FILE_SIZE:
				sprintf(buf,"%s\r\n","File_size read OK");
				
			break;	
			case FILE_INPUT:
				sprintf(buf,"%s\r\n","please input content");
			break;
			case FILE_WRITE:
				test_log("write a file\r\n");
				
				ret = ql_fwrite((void *)cmd_msg.pdata, cmd_msg.datalen, 1, fp);
				if(ret < 0) 
				{
					test_log("[FS]ERROR!!! *** file write fail: %s \r\n", pFilePath);
				}
				ql_fclose(fp);//关闭文件
				fp = NULL;

				//增加校验机制
				//打开文件
				fp = ql_fopen(pFilePath, "r");
				//
				unsigned char * ptemp = malloc(cmd_msg.datalen);
				memset(ptemp,0,cmd_msg.datalen);
				ret = ql_fread((void *)ptemp,cmd_msg.datalen , 1, fp);
				if(ret < 0)
				{
					test_log("[FS]ERROR!!! *** file read fail: %s \r\n", pFilePath);
				}
				ql_fclose(fp);//关闭文件
				fp = NULL;
				ret = memcmp(cmd_msg.pdata,ptemp,cmd_msg.datalen);
				if(0 == ret)
				{
					test_log("[FS] success! read and write data are same,Write FS ok\r\n");
					free(cmd_msg.pdata);
					MainUartDataPtr = NULL;
					free(ptemp);
					ptemp = NULL;
					file_size = 0;
					
					//告诉上位机FS校验和写入完成
					sprintf(buf,"%s\r\n","[FS] success! read and write data are same,Write FS ok\r\n");
	
				}


			break;
			case FILE_PLAY://文件播放
				pFilePath = (unsigned char *)cmd_msg.pFilePath;
				ret = ql_audio_file_play(pFilePath);			//play wav file, custoner_fs.bin文件中需包含对应文件名的wav文件
				if(-1 == ret)
				{
					sprintf(buf,"Not find：%s，can not play!!! \r\n",pFilePath);
				}
				else 
				{
					sprintf(buf,"%s play....	\n",pFilePath);
					printf("%s play....	\n",pFilePath);
					ql_rtos_task_sleep_s(2);
					ql_audio_file_stop();
				}
				
			break;

			case FILE_REMOVE://文件删除
				pFilePath = (unsigned char *)cmd_msg.pFilePath;
				ret = ql_remove(pFilePath);
				if(0 == ret)
				{
					test_log("[FS]SUCCESS!!! *** file remove OK: %s \r\n", pFilePath);
					sprintf(buf,"[FS]SUCCESS!!! *** file remove OK: %s \r\n",pFilePath);
				}
				else
				{
					test_log("[FS]ERROR!!! *** file remove fail: %s \r\n", pFilePath);
					sprintf(buf,"[FS]ERROR!!! *** file remove fail: %s \r\n", pFilePath);
				}
			break;
			
		}
		ql_uart_write(QL_MAIN_UART_PORT,buf,128);
		cmd_msg.msg = FILE_NOCMD;
		cmd_msg.datalen = 0;
		cmd_msg.pdata = NULL;
		cmd_msg.pFilePath = NULL;
		memset(buf,0,128);
		ret = -1;
	}
}


static void file_test(void)
{
	QFILE * fp = NULL;
    QFILE * u_fp = NULL;
	QFILE * b_fp = NULL;
	char buf[2048] = {0};
	int ret=0,cnt=0;
	printf("========== fs testing\r\n");
	while (1)
	{
		cnt++;
		memset(buf,0,strlen(FILE_CONTENT));
		
		fp = ql_fopen(U_FILE_UNDER_ROOT, "w+");
		if(fp == NULL)
		{
			printf("[FS]ERROR!!! *** file create fail: %s ***\r\n", U_FILE_UNDER_ROOT);
			goto exit;
		}
		ret = ql_fwrite((void *)FILE_CONTENT, strlen(FILE_CONTENT), 1, fp);
		if(ret < 0) 
		{
			printf("[FS]ERROR!!! *** file write fail: %s ***\r\n", U_FILE_UNDER_ROOT);
			goto exit;
		}
		//printf("[FS] file write: [%d]%s\r\n", ret, FILE_CONTENT);
		
		ret = ql_fseek(fp,0,0);   //增加seek，将文件游标置位到初始阶段，防止文件比对时不一致
		if(ret < 0)
		{
			printf("[FS]ERROR!!! *** file seek fail: %s ***\r\n", U_FILE_UNDER_ROOT);
			goto exit;
		}
		
		ret = ql_fread((void *)buf, strlen(FILE_CONTENT), 1, fp);
		if(ret < 0)
		{
			printf("[FS]ERROR!!! *** file read fail: %s ***\r\n", U_FILE_UNDER_ROOT);
			goto exit;
		}
		ret = strcmp(FILE_CONTENT,buf);
		if (ret == 0)
		{
			printf("[FS] success! read and write data are same,Test cnt(%d)\r\n",cnt);
		}
		else
		{
			while(1)
			{
				ql_rtos_task_sleep_s(10);
				printf("[FS]ERROR!!! read and write data are NOT same!!!!Test cnt(%d), STOP!STOP!STOP!\r\n",cnt);
			}
				
		}
		//printf("[FS] file read: [%d]%s\r\n", ret, buf);


	exit:
		if(fp)
		{
			ql_fclose(fp);
			//printf("[FS] file closed: %s\r\n", U_FILE_UNDER_ROOT);
		}
		if(u_fp)
		{
			ql_fclose(u_fp);
			//printf("[FS] file closed: %s\r\n", U_FILE_UNDER_ROOT);
		}
		if(b_fp)
		{
			ql_fclose(b_fp);
		//	printf("[FS] file closed: %s\r\n", B_FILE_UNDER_ROOT);
		}
		ql_rtos_task_sleep_ms(5);

		if (cnt > 50)
		{
			printf("Test cnt(%d), Ruturn\r\n",cnt);
			return ;
		}
	}
}


#if EXTERNAL_FS
//测试外挂Nor Flash的FS系统
static void ex_file_test(void)
{
	QFILE * fp = NULL;
	char buf[100] = {0};
	int ret;

	printf("[EXFS] ========== file test satrt\r\n");
	
	fp = ql_fopen(C_FILE_UNDER_ROOT, "w+");
	if(fp == NULL)
	{
		printf("[EXFS] *** file create fail: %s ***\r\n", C_FILE_UNDER_ROOT);
		goto exit;
	}
	printf("[EXFS] file created: %s\r\n", C_FILE_UNDER_ROOT);
	
	ret = ql_fwrite((void *)FILE_CONTENT, strlen(FILE_CONTENT), 1, fp);
	if(ret < 0) 
	{
		printf("[EXFS] *** file write fail: %s ***\r\n", C_FILE_UNDER_ROOT);
		goto exit;
	}
	printf("[EXFS] file write: [%d]%s\r\n", ret, FILE_CONTENT);
	
	memset(buf ,0 ,sizeof(buf));
	
	ret = ql_fseek(fp,0,0);
	if (ret < 0)
	{
		printf("[EXFS] file seek err\r\n");
	}
	
	ret = ql_fread((void *)buf, strlen(FILE_CONTENT),1,fp);
	if(ret < 0) 
	{
		printf("[EXFS] *** file read fail: %s ***\r\n", C_FILE_UNDER_ROOT);
		goto exit;
	}
	printf("[EXFS] file read: [%d]%s\r\n", ret, buf);
	
exit:
	if(fp)
	{
		ql_fclose(fp);
		printf("[EXFS] file closed: %s\r\n", C_FILE_UNDER_ROOT);
	}
	printf("[EXFS] ========== file test finished\r\n");
}
#endif

static void list_dir(const char *path)
{
	QDIR * dp = NULL;
	struct lfs_info info = {0};
	int ret;
	
	dp = ql_opendir(path);
	if(dp == NULL)
	{
		printf("[FS] *** dir open fail: %s ***\r\n", path);
		return;
	}
	printf("[FS] dir opened: %s\r\n", path);

	printf("[FS] ----- start dir list -----\r\n");
	printf("[FS] type\tsize\tname\r\n");
	while(1)
	{
		ret = ql_readdir(dp, &info);
		if(ret < 0)
		{
			printf("[FS] *** dir read fail: %s ***\r\n", path);
			break;
		}
		else if(ret == 0)
		{
			printf("[FS] ----- end of dir list -----\r\n");
			break;
		}
		else
		{
			printf("[FS] %-4d\t%-4d\t%s\r\n", info.type, info.size, info.name);
		}
	}

	if(dp)
	{
		ql_closedir(dp);
		printf("[FS] dir closed: %s\r\n", path);
	}
}

static void dir_test(void)
{
	int ret;
	
	printf("[FS] ========== dir test satrt\r\n");

	// make a directory
	ret = ql_mkdir(U_DIR_PATH, 0x777);
	if(ret < 0)
	{
		printf("[FS] *** dir make fail: %s ***\r\n", U_DIR_PATH);
		goto exit;
	}
	printf("[FS] dir made: %s\r\n", U_DIR_PATH);

	// copy "U:/testFile.txt" to "U:/testDir/testFile.txt"
	ret = ql_copy(U_FILE_UNDER_ROOT, U_FILE_UNDER_DIR);
	if(ret < 0)
	{
		printf("[FS] *** file(\"%s\") copied to (\"%s\") fail ***\r\n", U_FILE_UNDER_ROOT, U_FILE_UNDER_DIR);
		goto exit;
	}
	printf("[FS] file(\"%s\") has copied to (\"%s\")\r\n", U_FILE_UNDER_ROOT, U_FILE_UNDER_DIR);

	// list "U:/"
	list_dir(U_ROOT_PATH);
	
	// list "U:/testDir"
	list_dir(U_DIR_PATH);

exit:
	printf("[FS] ========== dir test finished\r\n");
}

static void cross_disk_test(void)
{
	int ret;
	QFILE * u_fp = NULL;
	QFILE * b_fp = NULL;
	char buf[64] = {0};

	printf("[FS] ========== cross disk test satrt\r\n");

	// copy "U:/testFile.txt" to "B:/testFile.txt"
	ret = ql_copy(U_FILE_UNDER_ROOT, B_FILE_UNDER_ROOT);
	if(ret < 0)
	{
		printf("[FS] *** file(\"%s\") copied to (\"%s\") fail ***\r\n", U_FILE_UNDER_ROOT, B_FILE_UNDER_ROOT);
		goto exit;
	}
	printf("[FS] file(\"%s\") has copied to (\"%s\")\r\n", U_FILE_UNDER_ROOT, B_FILE_UNDER_ROOT);

	// make directory: "B:/testDir"
	ret = ql_mkdir(B_DIR_PATH, 0x777);
	if(ret < 0)
	{
		printf("[FS] *** dir make fail: %s ***\r\n", B_DIR_PATH);
		goto exit;
	}
	printf("[FS] dir made: %s\r\n", B_DIR_PATH);

	// copy "U:/testDir" to "B:/testDir"
	ret = ql_copy(U_DIR_PATH, B_DIR_PATH);
	if(ret < 0)
	{
		printf("[FS] *** dir(\"%s\") copied to (\"%s\") fail ***\r\n", U_DIR_PATH, B_DIR_PATH);
		goto exit;
	}
	printf("[FS] dir(\"%s\") has copied to (\"%s\")\r\n", U_DIR_PATH, B_DIR_PATH);

	// list "U:/"
	list_dir(U_ROOT_PATH);
	
	// list "U:/testDir"
	list_dir(U_DIR_PATH);

	// list "B:/"
	list_dir(B_ROOT_PATH);
	
	// list "B:/testDir"
	list_dir(B_DIR_PATH);

	u_fp = ql_fopen(U_FILE_UNDER_ROOT, "r");
	if(u_fp == NULL)
	{
		printf("[FS] *** file open fail: %s ***\r\n", U_FILE_UNDER_ROOT);
		goto exit;
	}
	printf("[FS] file open: %s\r\n", U_FILE_UNDER_ROOT);

	ret = ql_fread((void *)buf, sizeof(buf), 1, u_fp);
	if(ret < 0)
	{
		printf("[FS] *** file read fail: %s ***\r\n", U_FILE_UNDER_ROOT);
		goto exit;
	}
	printf("[FS] file read: [%d]%s\r\n", ret, buf);

	b_fp = ql_fopen(B_FILE_UNDER_ROOT, "r");
	if(b_fp == NULL)
	{
		printf("[FS] *** file open fail: %s ***\r\n", B_FILE_UNDER_ROOT);
		goto exit;
	}
	printf("[FS] file open: %s\r\n", B_FILE_UNDER_ROOT);

	ret = ql_fread((void *)buf, sizeof(buf), 1, b_fp);
	if(ret < 0)
	{
		printf("[FS] *** file read fail: %s ***\r\n", B_FILE_UNDER_ROOT);
		goto exit;
	}
	printf("[FS] file read: [%d]%s\r\n", ret, buf);

exit:
	if(u_fp)
	{
		ql_fclose(u_fp);
		printf("[FS] file closed: %s\r\n", B_FILE_UNDER_ROOT);
	}
	if(b_fp)
	{
		ql_fclose(b_fp);
		printf("[FS] file closed: %s\r\n", B_FILE_UNDER_ROOT);
	}
	printf("[FS] ========== cross disk test finished\r\n");
}

static void fs_test(void * argv)
{
	int ret;
	printf("[FS] ========== fs test will start ...\r\n");

#if EXTERNAL_FS
	int port_index = EXTERNAL_NORFLASH_PORT33_36;
	int clk = _APBC_SSP_FNCLKSEL_1_625MHZ_;
	
	printf("[FS] ========== exflash init  \r\n");
	ql_spi_nor_init(port_index, clk);	

	ret = qextfs_init('C', "external_fs", 1, port_index, 0, 0x100000);
	printf("[FS] ========== exfs init : %d  \r\n", ret);
	if(!ret)
	{
		printf("[FS] ========== exfs init success  \r\n");
		ex_file_test();
	}
#endif

	file_test();
	//dir_test();
	//cross_disk_test();
	
	printf("[FS] ========== fs test finished\r\n");
}

//application_init(fs_test, "fs_test", 8, 6);
//application_init(ql_file_demo, "ql_file_demo", 10, 0);

