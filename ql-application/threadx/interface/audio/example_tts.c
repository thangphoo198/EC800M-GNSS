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
'零','一','二','三','四','五','六','七','八','九','十','百','千','万','点',
'欢','迎','使','用','移','远','模','块','支','付','宝','到','账','元',
'微','信','收','款','云','音','箱','量','变','大','小','最','级','连','网',
'成','功','拆','除','报','警','超','减','速','慢','点','蓝','牙','重','新'
'你','好','我','们','电','源','打','开','关','闭','别','推','动','碰','车',
'辆','已','设','撤','防','非','法','启','动','无','感','模','式','在','这',
'里','开','启','谢','谢','再','见','请','注','意','解','锁','连','接','断',
'配','对','模','式','失','败'
*****************************************************************************/

void test_cb(QL_TTS_ENVENT_E event, char *str)
{
	printf("user_cb :event = %d,str = %s\n",event,str);
}

static void quec_tts_test(void * argv)
{
	//等待audio初始化好
	while(!ql_get_audio_state()){
		ql_rtos_task_sleep_ms(50);
	}
	
	printf("quec_tts_test start ...\r\n");
	
	ql_set_audio_path_receiver();
	
	ql_codec_choose(AUD_INTERNAL_CODEC, NULL);
	ql_tts_init(test_cb);
	ql_set_volume(8);
			
	ql_tts_set_volume(0);									//设置tts音量，参数范围-32768~32767	
	while(1)
	{			
		ql_tts_play(2,"123,欢迎使用移远模块");					//使用GBK编码方式,目前支持的字符只有文件头描述
		ql_rtos_task_sleep_s(7);							//等待5S,由于tts为异步播放，连续调用会直接打断
	}

}
//application_init(quec_tts_test, "quec_tts_test", 2, 0);
