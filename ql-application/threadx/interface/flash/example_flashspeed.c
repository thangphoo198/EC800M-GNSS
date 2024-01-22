/*================================================================
  Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/

/*读取写入速度量化(xxxKB/s)：
1. open a file by w+
2. get time ticks before write data
3. write 4096 byte data 
4. get time ticks after write data,and calculate the speed 
5. get time ticks before read, read data, get time ticks after read
6. calculate read speed
*/

#include <stdio.h>
#include "ql_fs.h"
#include "ql_application.h"
#include "ql_rtos.h"
#include "ql_rtc.h"

#define CHIP_SECTOR_SIZE 		  0x1000

#define TEST_TIME 			7000000     //总共测试的次数
#define TEST_TIME_DELAY     10         //每次独写之间间隔时间s

#define FLASH_TYPE			"fota_param"      //选择读写的flash分区

#define FILE_CONTENT_LEN    4096 
#define FILE_CONTENT 		"123456789012345678901234567890123456789012345678901234567890123"\
                            "123456789012345678901234567890123456789012345678901234567890123"\
                            "123456789012345678901234567890123456789012345678901234567890123"\
                            "123456789012345678901234567890123456789012345678901234567890123"\
                            "123456789012345678901234567890123456789012345678901234567890123"\
                            "123456789012345678901234567890123456789012345678901234567890123"\
                            "123456789012345678901234567890123456789012345678901234567890123"\
                            "123456789012345678901234567890123456789012345678901234567890123"\
                            "123456789012345678901234567890123456789012345678901234567890123"\
                            "123456789012345678901234567890123456789012345678901234567890123"\
                            "123456789012345678901234567890123456789012345678901234567890123"\
                            "123456789012345678901234567890123456789012345678901234567890123"\
                            "123456789012345678901234567890123456789012345678901234567890123"\
                            "123456789012345678901234567890123456789012345678901234567890123"\
                            "123456789012345678901234567890123456789012345678901234567890123"\
                            "123456789012345678901234567890123456789012345678901234567890123"\
                            "123456789012345678901234567890123456789012345678901234567890123"\
                            "123456789012345678901234567890123456789012345678901234567890123"\
                            "123456789012345678901234567890123456789012345678901234567890123"\
                            "123456789012345678901234567890123456789012345678901234567890123"\
                            "123456789012345678901234567890123456789012345678901234567890123"\
                            "123456789012345678901234567890123456789012345678901234567890123"\
                            "123456789012345678901234567890123456789012345678901234567890123"\
                            "123456789012345678901234567890123456789012345678901234567890123"\
                            "123456789012345678901234567890123456789012345678901234567890123"\
                            "123456789012345678901234567890123456789012345678901234567890123"\
                            "123456789012345678901234567890123456789012345678901234567890123"\
                            "123456789012345678901234567890123456789012345678901234567890123"\
                            "123456789012345678901234567890123456789012345678901234567890123"\
                            "123456789012345678901234567890123456789012345678901234567890123"\
                            "123456789012345678901234567890123456789012345678901234567890123"\
                            "123456789012345678901234567890123456789012345678901234567890123"\
                            "123456789012345678901234567890123456789012345678901234567890123"\
                            "123456789012345678901234567890123456789012345678901234567890123"\
                            "123456789012345678901234567890123456789012345678901234567890123"\
                            "123456789012345678901234567890123456789012345678901234567890123"\
                            "123456789012345678901234567890123456789012345678901234567890123"\
                            "123456789012345678901234567890123456789012345678901234567890123"\
                            "123456789012345678901234567890123456789012345678901234567890123"\
                            "123456789012345678901234567890123456789012345678901234567890123"\
                            "123456789012345678901234567890123456789012345678901234567890123"\
                            "123456789012345678901234567890123456789012345678901234567890123"\
                            "123456789012345678901234567890123456789012345678901234567890123"\
                            "123456789012345678901234567890123456789012345678901234567890123"\
                            "123456789012345678901234567890123456789012345678901234567890123"\
                            "123456789012345678901234567890123456789012345678901234567890123"\
                            "123456789012345678901234567890123456789012345678901234567890123"\
                            "123456789012345678901234567890123456789012345678901234567890123"\
                            "123456789012345678901234567890123456789012345678901234567890123"\
                            "123456789012345678901234567890123456789012345678901234567890123"\
                            "123456789012345678901234567890123456789012345678901234567890123"\
                            "123456789012345678901234567890123456789012345678901234567890123"\
                            "123456789012345678901234567890123456789012345678901234567890123"\
                            "123456789012345678901234567890123456789012345678901234567890123"\
                            "123456789012345678901234567890123456789012345678901234567890123"\
                            "123456789012345678901234567890123456789012345678901234567890123"\
                            "123456789012345678901234567890123456789012345678901234567890123"\
                            "123456789012345678901234567890123456789012345678901234567890123"\
                            "123456789012345678901234567890123456789012345678901234567890123"\
                            "123456789012345678901234567890123456789012345678901234567890123"\
                            "123456789012345678901234567890123456789012345678901234567890123"\
                            "123456789012345678901234567890123456789012345678901234567890123"\
                            "123456789012345678901234567890123456789012345678901234567890123"\
                            "123456789012345678901234567890123456789012345678901234567890123"
                            
                            

#define FILE_CONTENT1 	    "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()~<>"\
                            "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()~<>"\
                            "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()~<>"\
                            "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()~<>"\
                            "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()~<>"\
                            "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()~<>"\
                            "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()~<>"\
                           "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()~<>"\
                           "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()~<>"\
                           "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()~<>"\
                           "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()~<>"\
                           "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()~<>"\
                           "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()~<>"\
                           "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()~<>"\
                           "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()~<>"\
                           "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()~<>"\
                           "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()~<>"\
                           "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()~<>"\
                           "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()~<>"\
                           "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()~<>"\
                           "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()~<>"\
                           "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()~<>"\
                           "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()~<>"\
                           "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()~<>"\
                           "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()~<>"\
                           "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()~<>"\
                           "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()~<>"\
                           "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()~<>"\
                           "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()~<>"\
                           "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()~<>"\
                           "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()~<>"\
                           "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()~<>"\
                           "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()~<>"\
                           "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()~<>"\
                           "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()~<>"\
                           "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()~<>"\
                           "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()~<>"\
                           "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()~<>"\
                           "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()~<>"\
                           "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()~<>"\
                           "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()~<>"\
                           "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()~<>"\
                           "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()~<>"\
                           "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()~<>"\
                           "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()~<>"\
                           "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()~<>"\
                           "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()~<>"\
                           "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()~<>"\
                           "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()~<>"\
                           "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()~<>"\
                           "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()~<>"\
                           "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()~<>"\
                           "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()~<>"\
                           "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()~<>"\
                           "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()~<>"\
                           "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()~<>"\
                           "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()~<>"\
                           "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()~<>"\
                           "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()~<>"\
                           "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()~<>"\
                           "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()~<>"\
                           "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()~<>"\
                           "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()~<>"\
                           "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()~<>"
                               
                            



int32_t nor_flash_read(uint32_t offset, void *buf, uint32_t nbytes) 
{
	return ql_norflash_do_read(FLASH_TYPE, offset, buf, nbytes);
    //return hal_flash_read((hal_partition_t)KV_PARTITION, &offset, buf, nbytes);

}
int32_t nor_flash_write(uint32_t offset, void *buf, uint32_t nbytes) 

{

	return ql_norflash_do_write(FLASH_TYPE, offset, buf, nbytes);
    //return hal_flash_read((hal_partition_t)KV_PARTITION, &offset, buf, nbytes);

}
int32_t nor_flash_erase(uint32_t offset, uint32_t size)

{

	return ql_norflash_do_erase(FLASH_TYPE, offset, size);
    //return hal_flash_erase((hal_partition_t)KV_PARTITION, offset, size);

}



static void WR_test_100Free(unsigned int i)
{	
    uint32_t  start_address = 0;
    uint32_t  size = 0;
    char buf[FILE_CONTENT_LEN] = {0};
	int ret = -1;
	float ticks_0_w, ticks_1_w, ticks_2_w, ticks_3_w;
	float speed_w, speed_r;

    ql_norflash_get_addr(FLASH_TYPE, &start_address, &size);
    printf("start_address: 0x%08x, size: %d\r\n", start_address, size);

    
    ticks_0_w = ql_rtc_get_ticks();
	ret = nor_flash_erase(start_address, FILE_CONTENT_LEN);
	ticks_1_w = ql_rtc_get_ticks();
    if(ret == 0)
    {
        printf("flash erase succeed\r\n");
    }
    else 
    {
        printf("flash_erase_error=%d\r\n ", ret);
    }
	printf("[flash_Speed] ========== ql_rtc_get_ticks ticks_1=%.2f\r\n", ticks_1_w);
	printf("[flash_Speed] ========== Delta ticks(Write_100Free)=%.2f\r\n", ticks_1_w - ticks_0_w);
	speed_w = 32768.00*4/(ABS(ticks_1_w - ticks_0_w));     //speed_w (KB) = write times * 4096 / delta ticks /32768 /1024
	printf("[flash_Speed] ========== Erase_Speed_100Free=%.2fKB/s\r\n", speed_w);

    memset(buf, 0, FILE_CONTENT_LEN);
   	ret=nor_flash_read(	start_address, buf, FILE_CONTENT_LEN);
                printf("read status: %d\r\n", ret);
                printf("readbuff = %s\r\n",buf);
   
   
    if(i%2)
    {
    	ticks_0_w = ql_rtc_get_ticks();
    	ret=nor_flash_write(start_address, FILE_CONTENT, FILE_CONTENT_LEN);
    	ticks_1_w = ql_rtc_get_ticks();
        printf("write status: %d\r\n", ret);
    	printf("[flash_Speed] ========== ql_rtc_get_ticks ticks_1=%.2f\r\n", ticks_1_w);
    	printf("[flash_Speed] ========== Delta ticks(Write_100Free)=%.2f\r\n", ticks_1_w - ticks_0_w);
    	speed_w = 32768.00*4/(ABS(ticks_1_w - ticks_0_w));     //speed_w (KB) = write times * 4096 / delta ticks /32768 /1024
    	printf("[flash_Speed] ========== Write_Speed_100Free=%.2fKB/s\r\n", speed_w);
    }
    else 
    {
        ticks_0_w = ql_rtc_get_ticks();
        ret=nor_flash_write(start_address, FILE_CONTENT1, FILE_CONTENT_LEN);
        ticks_1_w = ql_rtc_get_ticks();
        printf("write status: %d\r\n", ret);
        printf("[flash_Speed] ========== ql_rtc_get_ticks ticks_1=%.2f\r\n", ticks_1_w);
        printf("[flash_Speed] ========== Delta ticks(Write_100Free)=%.2f\r\n", ticks_1_w - ticks_0_w);
        speed_w = 32768.00*4/(ABS(ticks_1_w - ticks_0_w));     //speed_w (KB) = write times * 4096 / delta ticks /32768 /1024
        printf("[flash_Speed] ========== Write_Speed_100Free=%.2fKB/s\r\n", speed_w);
    }

    memset(buf, 0, FILE_CONTENT_LEN);
	ticks_2_w = ql_rtc_get_ticks();
	ret=nor_flash_read(	start_address, buf, FILE_CONTENT_LEN);
	ticks_3_w = ql_rtc_get_ticks();
    printf("read status: %d\r\n", ret);
    printf("readbuff = %s\r\n",buf);
    printf("[flash_Speed] ========== ql_rtc_get_ticks ticks_2=%.2f\r\n", ticks_2_w);
	printf("[flash_Speed] ========== ql_rtc_get_ticks ticks_3=%.2f\r\n", ticks_3_w);
	printf("[flash_Speed] ========== Delta ticks(Read_100Free)=%.2f\r\n", ticks_3_w - ticks_2_w);
	speed_r = 32768.00*4/(ABS(ticks_3_w - ticks_2_w));
	printf("[flash_Speed] ========== Read_Speed_100Free=%.2fKB/s\r\n", speed_r);


}

#define TONGJI_UNIT 50

static void WR_test_E_W_R_JiSuan_Ms_Time(unsigned int i,uint32_t start_addr,uint32_t teset_size)
{	
    uint32_t  start_address = 0;
    uint32_t  size = 0;
	unsigned int cnt = 0;
    char buf[FILE_CONTENT_LEN+1] = {0};
    char w_buf_0[FILE_CONTENT_LEN+1] = {0};
    char w_buf_1[FILE_CONTENT_LEN+1] = {0};
	
	int ret = -1;
	float ticks_0_w, ticks_1_w, ticks_2_w, ticks_3_w;
	float speed_w, speed_r;

	float speed_e_50 =0,speed_w_50=0, speed_r_50=0;

   	memset(buf, 0, FILE_CONTENT_LEN);
   	memset(w_buf_0, 0x55, FILE_CONTENT_LEN);
   	memset(w_buf_1, 0xAA, FILE_CONTENT_LEN);

	printf("[flash_Speed] ========== flash_speed test Start\r\n");

    ql_norflash_get_addr(FLASH_TYPE, &start_address, &size);
    printf("start_address: 0x%08x, size: %d\r\n", start_address, size);
	
	for (unsigned int i = 1; i < TEST_TIME; i++)
	{
		/////1、擦除时间统计
	    ticks_0_w = ql_rtc_get_ticks();
		ret = nor_flash_erase(start_address, FILE_CONTENT_LEN);
		ticks_1_w = ql_rtc_get_ticks();
	    if(ret == 0)
	    {
	        //printf("flash erase succeed\r\n");
	    }
	    else 
	    {
	        printf("ERR:flash_erase_error=%d\r\n ", ret);
			while(1)
			{
				ql_rtos_task_sleep_s(1);
			}

	    }
		speed_w = ((ABS(ticks_1_w - ticks_0_w))*1000)/32768.00;     //擦除4K 花费的时间
		//printf("[flash_Speed] ========== Erase_Speed_100Free=%.2fms\r\n", speed_w);
		speed_e_50+=speed_w;

		/////2、写时间统计
		ticks_0_w = ql_rtc_get_ticks();
	    if(i%2)
	    	ret=nor_flash_write(start_address, w_buf_0, FILE_CONTENT_LEN);
	    else 
	        ret=nor_flash_write(start_address, w_buf_1, FILE_CONTENT_LEN);
		
		ticks_1_w = ql_rtc_get_ticks();
		speed_w = ((ABS(ticks_1_w - ticks_0_w))*1000)/32768.00;	  //写4K 花费的时间
		//printf("[flash_Speed] ========== Write_Speed_100Free=%.2fms\r\n", speed_w);
		speed_w_50 +=speed_w;

		////3、读时间统计
	    memset(buf, 0, FILE_CONTENT_LEN);
		ticks_2_w = ql_rtc_get_ticks();
		ret=nor_flash_read(	start_address, buf, FILE_CONTENT_LEN);
		ticks_3_w = ql_rtc_get_ticks();
		speed_r = ((ABS(ticks_3_w - ticks_2_w))*1000)/32768.00;
		//printf("[flash_Speed] ========== Read_Speed_100Free=%.2fms\r\n", speed_r);
		speed_r_50 += speed_r;
		
		////4、写入和读出对比
		if((i%2))
		{
			if(0 != memcmp(buf,w_buf_0,FILE_CONTENT_LEN))
			{
				printf("R_buf:%s\r\n",buf);
				printf("W_buf:%s\r\n",w_buf_0);
				while(1)
				{
					printf("ERR:R != W, Test End!! CNT(%d)\r\n",i);
					ql_rtos_task_sleep_ms(1000); 
				}
			}
		}
		else
		{
			if(0 != memcmp(buf,w_buf_1,FILE_CONTENT_LEN))
			{
				printf("R_buf:%s\r\n",buf);
				printf("W_buf:%s\r\n",w_buf_1);
				while(1)
				{
					printf("ERR:R != W, Test End!! CNT(%d)\r\n",i);
					ql_rtos_task_sleep_ms(1000); 
				}
			}
		}
		
		if(i%TONGJI_UNIT == 0)
		{
			printf("[flash_Speed] ========== Erase_Speed_100Free=%.2fms\r\n", speed_e_50/TONGJI_UNIT);
			printf("[flash_Speed] ========== Write_Speed_100Free=%.2fms\r\n", speed_w_50/TONGJI_UNIT);
			printf("[flash_Speed] ========== Read_Speed_100Free=%.2fms\r\n", speed_r_50/TONGJI_UNIT);
			printf("[flash_Speed] ========== flash_speed_100free test RunTime-%d\r\n", i);//这里是擦写的次数
			speed_e_50 =0;
			speed_w_50 =0;
			speed_r_50 =0; 
		}
		
		ql_rtos_task_sleep_ms(TEST_TIME_DELAY); 
	}
}



static void rtos_test_sub_task(void * argv)
{
	ql_rtos_task_sleep_s(40);	
	WR_test_E_W_R_JiSuan_Ms_Time(0,0,0);
}

static ql_task_t test_task_ref = NULL;
static void flash_speed_test(void * argv)
{
	ql_rtos_task_create(&test_task_ref, 20*1024, 67, "FlashTest", rtos_test_sub_task,NULL);

    while(1)
    {
        //printf("flash  speed test over\r\n" );
        ql_rtos_task_sleep_s(1);
    }
}
//application_init(flash_speed_test, "flashtest", 20, 10);


