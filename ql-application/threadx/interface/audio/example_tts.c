/*================================================================
  Copyright (c) 2022, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/
/**
 ******************************************************************************
 * @file    example_tts.c
 * @author  august.yang
 * @version V1.0.0
 * @date    2022/04/15
 * @brief   This file tests TTS APIs
 ******************************************************************************
 */


#include <stdio.h>
#include "ql_rtos.h"
#include "ql_application.h"
#include "ql_audio.h"
#include "ql_tts.h"

/***************************************************************************  
'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
'��','һ','��','��','��','��','��','��','��','��','ʮ','��','ǧ','��','��',
'��','ӭ','ʹ','��','��','Զ','ģ','��','֧','��','��','��','��','Ԫ',
'΢','��','��','��','��','��','��','��','��','��','С','��','��','��','��',
'��','��','��','��','��','��','��','��','��','��','��','��','��','��','��'
'��','��','��','��','��','Դ','��','��','��','��','��','��','��','��','��',
'��','��','��','��','��','��','��','��','��','��','��','ģ','ʽ','��','��',
'��','��','��','л','л','��','��','��','ע','��','��','��','��','��','��',
'��','��','ģ','ʽ','ʧ','��'
*****************************************************************************/

void test_cb(QL_TTS_ENVENT_E event, char *str)
{
	printf("user_cb :event = %d,str = %s\n",event,str);
}

static void quec_tts_test(void * argv)
{
	//�ȴ�audio��ʼ����
	while(!ql_get_audio_state()){
		ql_rtos_task_sleep_ms(50);
	}
	
	printf("quec_tts_test start ...\r\n");
	
	ql_set_audio_path_receiver();
	
	ql_codec_choose(AUD_INTERNAL_CODEC, NULL);
	ql_tts_init(test_cb);
	ql_set_volume(8);
			
	ql_tts_set_volume(0);									//����tts������������Χ-32768~32767	
	while(1)
	{			
		ql_tts_play(2,"123,��ӭʹ����Զģ��");					//ʹ��GBK���뷽ʽ,Ŀǰ֧�ֵ��ַ�ֻ���ļ�ͷ����
		ql_rtos_task_sleep_s(7);							//�ȴ�5S,����ttsΪ�첽���ţ��������û�ֱ�Ӵ��
	}

}
//application_init(quec_tts_test, "quec_tts_test", 2, 0);
