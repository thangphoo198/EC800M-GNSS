/*================================================================
  Copyright (c) 2022, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/

#include "ql_type.h"
#include "ql_func.h"
#include "ql_audio.h"
#include "ql_rtos.h"
#include "ql_application.h"
#include <stdio.h>

int ql_cb_wav_file_play(char *p_data, int len, int res) //p_data and len is not usd
{
	printf("[carola] entern ql_cb_wav_file_play res = %d\n", res);
}

void wav_test(void *argv)
{
	//等待audio初始化好
	while(!ql_get_audio_state()){
		ql_rtos_task_sleep_ms(50);
	}
	int i = 0;
	printf("wav_test start ...\r\n");
	
	//ql_audio_play_init(ql_cb_wav_file_play);
	ql_set_audio_path_receiver();
	ql_set_volume(10);
	ql_codec_choose(AUD_INTERNAL_CODEC, NULL);

	ql_wav_file_play("U:/test.wav"); //play wav file, custoner_fs.bin文件中需包含对应文件名的wav文件
	ql_rtos_task_sleep_s(2);
	ql_wav_file_stop();
}

//application_init(wav_test, "wav_test", 5, 2);

