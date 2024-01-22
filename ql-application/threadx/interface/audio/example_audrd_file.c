/*================================================================
  Copyright (c) 2022, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/

#include <stdio.h>
#include "ql_rtos.h"
#include "ql_application.h"
#include "ql_audio.h"
#include "ql_fs.h"

int ql_file_cb_play(char *p_data, int len, int res)
{
	printf("[carola] entern ql_file_cb_play res = %d\n", res);
}

static void audio_file_test(void * argv)
{
	int i = 0;
	
	//等待audio底层初始化完成
	while(!ql_get_audio_state()){
		ql_rtos_task_sleep_ms(50);
	}

	printf("audio_file_test start ...\r\n");

	ql_set_audio_path_receiver();						//使用receiver录音
	
	ql_record_amr_file_start("U:/111.amr");				//录音为指定文件名的amr文件
	ql_rtos_task_sleep_s(7); //test only record 7s	
	ql_record_amr_file_stop();
	ql_set_volume(10);
	
	while(ql_access("U:/111.amr",0) == 0){
		ql_audio_file_play("U:/111.amr");
		printf("play start\n");
		ql_rtos_task_sleep_s(10);
	}
	
	printf("not find file!\n");

}

//application_init(audio_file_test, "audio_file_test", 2, 0);
