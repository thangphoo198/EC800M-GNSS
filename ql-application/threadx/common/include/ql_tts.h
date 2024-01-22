/*================================================================
  Copyright (c) 2022, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/
#ifndef QL_TTS_TSAKMGR_H
#define QL_TTS_TSAKMGR_H



typedef enum {
    QL_TTS_EVT_INIT,
    QL_TTS_EVT_DEINIT,
    QL_TTS_EVT_PLAY_START,
    QL_TTS_EVT_PLAY_STOP,
    QL_TTS_EVT_PLAY_FINISH,
    QL_TTS_EVT_PLAY_FAILED,
    QL_TTS_EVT_PLAY_INTERRUPT,
} QL_TTS_ENVENT_E;

typedef void (*ql_tts_cb_type)(QL_TTS_ENVENT_E event, char *str);

/***********************************************************************
*
* Name:   ql_tts_init    
*
* Description: 初始化tts功能。
*
* Parameters:  usr_cb：注册的播放状态的回调，具体状态参考QL_TTS_ENVENT_E
*			  
* Returns:	  0 成功
*			  
***********************************************************************/
int ql_tts_init(ql_tts_cb_type usr_cb);

/***********************************************************************
*
* Name:   ql_tts_play    
*
* Description: 播放tts文本。
*
* Parameters:  mode：播放tts的编码格式：目前此参数无用，只支持GBK编码
*			  string:对应mode编码的文本，最大50个字符
* Returns:	  0 成功
*			  
***********************************************************************/
int ql_tts_play(int mode, const char* string);
/*mode:
	1--UNICODE16(Size end conversion)  
	2--UTF-8  
*/
/***********************************************************************
*
* Name:   ql_tts_stop	 
*
* Description: 停止播放tts文本，立即打断。
*
* Parameters:  
*			  
* Returns:	  0 成功
*			  
***********************************************************************/
int ql_tts_stop(void);

/*
/***********************************************************************
*
* Name:   ql_tts_deinit	 
*
* Description: 注销当前TTS资源
*
* Parameters: 
*			  
* Returns:	 0 成功
*			  
***********************************************************************/
int ql_tts_deinit(void);

/***********************************************************************
*
* Name:   ql_tts_set_volume	 
*
* Description: 单独设置tts资源音量。
*
* Parameters:  volume：设置音量（-32768~32767）
*			  
* Returns:	  0 成功
*			  
***********************************************************************/
int ql_tts_set_volume(int volume);


/***********************************************************************
*
* Name:   ql_tts_state	 
*
* Description: 获取当前是否正在播放tts。
*
* Parameters:  
*			  
* Returns:	  1 正在播放
*			  0 未播放
***********************************************************************/
int ql_tts_state(void);

/***********************************************************************
*
* Name:   ql_tts_get_volume	 
*
* Description: 获取设置tts资源音量。
*
* Parameters: 
*			  
* Returns:	 当前设置的tts音量
*			  
***********************************************************************/
int ql_tts_get_volume(void);

/***********************************************************************
*
* Name:   ql_tts_set_speed	 
*
* Description: 设置tts播放速度。
*
* Parameters: speed 设置速度（-32768~32767）
*			  
* Returns:	 0 成功
*			  
***********************************************************************/
int ql_tts_set_speed(int speed);

/***********************************************************************
*
* Name:   ql_tts_get_speed	 
*
* Description: 获取设置tts的播放速度。
*
* Parameters: 
*			  
* Returns:	 当前设置的tts播放速度
*			  
***********************************************************************/
int ql_tts_get_speed(void);


/***********************************************************************
*
* Name:   ql_tts_digit_mode	 
*
* Description: 设置tts的数字处理策略。
*
* Parameters: mode：
*		0 自动判断;
*		1 数字作号码处理;
*		2 数字作数值处理;
*			  
* Returns:	 0 成功
*			  
***********************************************************************/
int ql_tts_digit_mode(int mode);

/***********************************************************************
*
* Name:   ql_get_tts_digit_mode	 
*
* Description: 获取当前tts的数字处理策略。
*
* Parameters: 
*		
*			  
* Returns:	0 自动判断;
*			1 数字作号码处理;
*			2 数字作数值处理;
*			  
***********************************************************************/
int ql_get_tts_digit_mode(void);

#endif/*QUECTEL_APPTCPIP_SUPPORT*/
