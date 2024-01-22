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
* Description: ��ʼ��tts���ܡ�
*
* Parameters:  usr_cb��ע��Ĳ���״̬�Ļص�������״̬�ο�QL_TTS_ENVENT_E
*			  
* Returns:	  0 �ɹ�
*			  
***********************************************************************/
int ql_tts_init(ql_tts_cb_type usr_cb);

/***********************************************************************
*
* Name:   ql_tts_play    
*
* Description: ����tts�ı���
*
* Parameters:  mode������tts�ı����ʽ��Ŀǰ�˲������ã�ֻ֧��GBK����
*			  string:��Ӧmode������ı������50���ַ�
* Returns:	  0 �ɹ�
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
* Description: ֹͣ����tts�ı���������ϡ�
*
* Parameters:  
*			  
* Returns:	  0 �ɹ�
*			  
***********************************************************************/
int ql_tts_stop(void);

/*
/***********************************************************************
*
* Name:   ql_tts_deinit	 
*
* Description: ע����ǰTTS��Դ
*
* Parameters: 
*			  
* Returns:	 0 �ɹ�
*			  
***********************************************************************/
int ql_tts_deinit(void);

/***********************************************************************
*
* Name:   ql_tts_set_volume	 
*
* Description: ��������tts��Դ������
*
* Parameters:  volume������������-32768~32767��
*			  
* Returns:	  0 �ɹ�
*			  
***********************************************************************/
int ql_tts_set_volume(int volume);


/***********************************************************************
*
* Name:   ql_tts_state	 
*
* Description: ��ȡ��ǰ�Ƿ����ڲ���tts��
*
* Parameters:  
*			  
* Returns:	  1 ���ڲ���
*			  0 δ����
***********************************************************************/
int ql_tts_state(void);

/***********************************************************************
*
* Name:   ql_tts_get_volume	 
*
* Description: ��ȡ����tts��Դ������
*
* Parameters: 
*			  
* Returns:	 ��ǰ���õ�tts����
*			  
***********************************************************************/
int ql_tts_get_volume(void);

/***********************************************************************
*
* Name:   ql_tts_set_speed	 
*
* Description: ����tts�����ٶȡ�
*
* Parameters: speed �����ٶȣ�-32768~32767��
*			  
* Returns:	 0 �ɹ�
*			  
***********************************************************************/
int ql_tts_set_speed(int speed);

/***********************************************************************
*
* Name:   ql_tts_get_speed	 
*
* Description: ��ȡ����tts�Ĳ����ٶȡ�
*
* Parameters: 
*			  
* Returns:	 ��ǰ���õ�tts�����ٶ�
*			  
***********************************************************************/
int ql_tts_get_speed(void);


/***********************************************************************
*
* Name:   ql_tts_digit_mode	 
*
* Description: ����tts�����ִ�����ԡ�
*
* Parameters: mode��
*		0 �Զ��ж�;
*		1 ���������봦��;
*		2 ��������ֵ����;
*			  
* Returns:	 0 �ɹ�
*			  
***********************************************************************/
int ql_tts_digit_mode(int mode);

/***********************************************************************
*
* Name:   ql_get_tts_digit_mode	 
*
* Description: ��ȡ��ǰtts�����ִ�����ԡ�
*
* Parameters: 
*		
*			  
* Returns:	0 �Զ��ж�;
*			1 ���������봦��;
*			2 ��������ֵ����;
*			  
***********************************************************************/
int ql_get_tts_digit_mode(void);

#endif/*QUECTEL_APPTCPIP_SUPPORT*/
