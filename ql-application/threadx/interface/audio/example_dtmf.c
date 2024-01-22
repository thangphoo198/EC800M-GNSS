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


void dtmf_test(void *argv)
{
	int i = 0,tone = 0,f1 = 100,f2 = 100;
	
	//等待audio底层初始化完成
	while(!ql_get_audio_state()){
		ql_rtos_task_sleep_ms(50);
	}
	
	printf("dtmf_test start ...\r\n");
	ql_codec_choose(AUD_INTERNAL_CODEC, NULL);
	ql_set_audio_path_receiver();
	ql_set_volume(8);
	while(1)
	{	
#if 0	//dtmf
		ql_aud_dtmf_play(tone, 1);		//tone范围 0~15
		ql_rtos_task_sleep_s(2);
		ql_aud_dtmf_play(tone, 0);
		ql_rtos_task_sleep_s(2);
		if(tone < 15) tone++;
#else	//tone
		ql_aud_tone_play(f1,f2, 1);		//f1,f2为频率范围 50~3500
		ql_rtos_task_sleep_s(2);
		ql_aud_tone_play(f1,f2, 0);		//1为打开，0为关闭
		ql_rtos_task_sleep_s(2);
		if(f1 <= 3500){
			f1 += 100;
			f2 =f1;
		}
#endif
	}
}

//application_init(dtmf_test, "dtmf_test", 2, 2);


