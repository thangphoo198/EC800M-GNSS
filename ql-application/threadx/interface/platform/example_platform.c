/*================================================================
  Copyright (c) 2022, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/
#include <stdio.h>
#include "ql_rtos.h"
#include "ql_func.h"
#include "ql_otp.h"
#include "ql_application.h"
#include "ql_platform.h"

static void quec_cpu_fre_test(void * argv)
{

	unsigned int curr_pp = 0;
	unsigned int PPx = QL_PP1;

	ql_rtos_task_sleep_s(5);

	ql_cpu_fre_set(PPx);//PP1-PP5
	
	while(1)
	{
		ql_cpu_fre_set(PPx);
		printf("===set cpu fre PP: %d===\n", PPx);
		curr_pp = ql_cpu_fre_get();
		printf("***current  PP: %d***\n", curr_pp);
		PPx = (PPx++)%5 + 1;
		
		ql_rtos_task_sleep_s(10);
		
	}

}

unsigned char EEbuf[2*1024]={0};
unsigned char RTIbuf[4*1024]={0};
unsigned char WDTbuf[1024]={0};
QL_DUMP_BIN_FILE dumpbuf[]={
    {"com_wdtKICK.bin",WDTbuf,sizeof(WDTbuf)},
    {"com_EE_Hbuf.bin",EEbuf,sizeof(EEbuf)},
    {"com_rti_tsk.bin",RTIbuf,sizeof(RTIbuf)}
    
};
static void quec_dump_nvm(void * argv)
{
    int i = 0;
    unsigned int dumpcnt=0;
    ql_flash_save_dump_enable(1);
    ql_get_dump_file(dumpbuf,3);
    //ql_del_dump_file();
    dumpcnt=ql_get_dump_cnt();
    printf("dumpcnt=%d\r\n",dumpcnt);
    //ql_clean_dump_cnt();
    //dumpcnt=ql_get_dump_cnt();
    //printf("ql_clean_dump_cnt();=%d\r\n",dumpcnt);
    printf("\r\n====================com_wdtKICK.bin================================\r\n");
    printf("\r\n-------------------------------------------------------------------\r\n");
    for(i=0;i<1024;i++)
    {
        printf("%c",dumpbuf[0].EEbuf[i]);
    }
    printf("\r\n-------------------------------------------------------------------\r\n");
    printf("\r\n====================com_EE_Hbuf.bin================================\r\n");
    printf("\r\n-------------------------------------------------------------------\r\n");
    for(i=0;i<2*1024;i++)
    {
        printf("%c",dumpbuf[1].EEbuf[i]);
    }
    printf("\r\n-------------------------------------------------------------------\r\n");
    printf("\r\n====================com_rti_tsk.bin================================\r\n");
    printf("\r\n-------------------------------------------------------------------\r\n");
    for(i=0;i<4*1024;i++)
    {
        printf("%c",dumpbuf[2].EEbuf[i]);
    }
     printf("\r\n-------------------------------------------------------------------\r\n");
    ql_rtos_task_delete(NULL);
}

//application_init(quec_cpu_fre_test, "quec_cpu_fre_test", 2, 0);
//application_init(quec_dump_nvm, "quec_dump_test", 2, 0);


