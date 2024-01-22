
/*==========================================================================================================
  Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
===========================================================================================================*/
/*新版本不需要再同步ntp*/
#include <stdio.h>
#include "ql_application.h"
#include "ql_log.h"
#include "ql_gnss.h"
#include "ql_rtos.h"
#include "ql_ntp.h"
#include "ql_data_call.h"
#include "sockets.h"
#include "netdb.h"


#define test_log(fmt, args...)	printf(fmt, ##args)


static void ql_nw_status_callback(int profile_idx, int nw_status)
{
	printf("profile(%d) status: %d\r\n", profile_idx, nw_status);
}

static void datacall_start(void)
{
	printf("wait for network register done\r\n");

	if(ql_network_register_wait(30) != 0)
	{
		printf("*** network register fail ***\r\n");
	}
	else
	{

		printf("doing network activing ...\r\n");
		
		ql_wan_start(ql_nw_status_callback);
		ql_set_auto_connect(1, TRUE);
		ql_start_data_call(1, 0, NULL, NULL, NULL, 0);

	}
}


void quec_gnss_callback(char *data, int len)
{
    int i=0;
	for(i=0;i<len;i++)
	{
        printf("%c",data[i]);
    }
}

void quec_gnss_agps_callback(quec_gnss_sate_num_t * gps_sate)
{
    printf("gps_num:%d;gps_vailed_num:%d\nbds_num:%d;bds_vailed_num:%d\n",
        gps_sate->gps_sate_num,gps_sate->gps_sate_vaild_num,
        gps_sate->bds_sate_num,gps_sate->bds_sate_vaild_num);
}
static void quec_gnss_test(void * argv)
{
    int i;
    ql_gnss_location_t * gps_location = NULL;
    struct ql_data_call_info info = {0};
	char ip4_addr_str[16] = {0};
     u32 flags = 0;
	int ret =0 ; 
    unsigned int reset_type = 0;
    int time = 0;
    #if 1
    datacall_start();                               //使用gps之前先注网
    #endif
	ql_gnss_cfgsys_set(1);							//设置GPS+BDS
	ql_gnss_cfgmsg_set(31);							//设置GGA/RMC/GSV/GSA/VTG

	ql_gnss_agps_cfg(AGPS_GNSS_ENABLE,1);				//使能AGPS

	//ql_gnss_apflash_cfg(APFLASH_GNSS_DISABLE);		//使能APFLASH

    ql_set_gnss_nmea_mode(PACKET_MODE);
	
    //ql_gnss_get_location(&gps_location);
    while(1)
    {
        printf("[GPS ]  GPS  heap(%d)\r\n",ql_rtos_get_free_heap_size());
        printf("========GPS OPEN :[%d]s===== !\n",time);
        ql_gnss_open(quec_gnss_callback);
        ql_get_agps_sate_num(quec_gnss_agps_callback);  //注册获取agps卫星数量回调函数
        ql_rtos_task_sleep_s(5);
       // printf("========GPS CLOSE!!===== !\n");
        //ql_gnss_close();
        if(reset_type==0){
            time = 1;
            ql_rtos_task_sleep_s(time);
        }
        else if(reset_type==1){
            time = 60;
            ql_rtos_task_sleep_s(time); 
            
        }
        else if(reset_type==2){
            time = 60*10;
            ql_rtos_task_sleep_s(time);
        }
        else if(reset_type==3){
            time = 60*30;
            ql_rtos_task_sleep_s(time);
        }
        else if(reset_type==4){
            time = 60*60;
            ql_rtos_task_sleep_s(time);
        }
        else if(reset_type==5){
            time = 60*60*2;
            ql_rtos_task_sleep_s(time);
        }else{
            time = 60*60*4;
            ql_rtos_task_sleep_s(time);
            reset_type = 0;
        }
        reset_type++;
    }
}

application_init(quec_gnss_test, "quec_gnss_test", 10, 0);

