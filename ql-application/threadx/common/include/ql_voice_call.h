/*================================================================
  Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/
/*******************************************************************************
                                 ql_voice_call.h
author
      rami.zhang
description
      API interface for voice call 
creation time
      2020.3.19
*******************************************************************************/
#ifndef __QL_VOICE_CALL_H__
#define __QL_VOICE_CALL_H__
		
#ifdef __cplusplus
		extern "C" {
#endif


typedef void*   OSTaskRef;
typedef OSTaskRef				quec_task_t;

typedef signed   char  int_8;
typedef unsigned char  uint_8;

typedef          short int_16;
typedef unsigned short uint_16;

typedef          int   int_32;
typedef unsigned int   uint_32;




typedef void (*QL_voice_call_EventHandlerFunc_t)(unsigned int ind_flag, void *ind_msg_buf, unsigned int ind_msg_len, void *contextPtr);


/*RAMI:call indication*/
#define QUEC_VOICE_CALL_INDICATION_BASE                          ((uint_32)(0x1000))
#define QUEC_CC_INCOMING_CALL_IND                                ((uint_32)(0x0001 + QUEC_VOICE_CALL_INDICATION_BASE))
#define QUEC_CC_WAITING_CALL_IND                                 ((uint_32)(0x0002 + QUEC_VOICE_CALL_INDICATION_BASE)) 
#define QUEC_CC_ALERTING_CALL_IND                                ((uint_32)(0x0003 + QUEC_VOICE_CALL_INDICATION_BASE)) 
#define QUEC_CC_CONNECT_CALL_IND                                 ((uint_32)(0x0004 + QUEC_VOICE_CALL_INDICATION_BASE))
#define QUEC_CC_DISCONNECT_CALL_IND                              ((uint_32)(0x0005 + QUEC_VOICE_CALL_INDICATION_BASE)) 
#define QUEC_CC_DTMF_CALL_IND                                    ((uint_32)(0x0006 + QUEC_VOICE_CALL_INDICATION_BASE))

//add volte call report by @mia.zhong 20201019 
#define QUEC_VOLTE_INCOMING_CALL_IND                             ((uint_32)(0x0007 + QUEC_VOICE_CALL_INDICATION_BASE))
#define QUEC_VOLTE_CONNECT_CALL_IND                              ((uint_32)(0x0008 + QUEC_VOICE_CALL_INDICATION_BASE))
#define QUEC_VOLTE_DISCONNECT_CALL_IND                           ((uint_32)(0x0009 + QUEC_VOICE_CALL_INDICATION_BASE))
#define QUEC_VOLTE_WAITING_CALL_IND                              ((uint_32)(0x000A + QUEC_VOICE_CALL_INDICATION_BASE))
//@mia.zhong 20201019

//Fitz.xu 20210722: Add call event ind for mo call
#define QUEC_DIALING_CALL_IND                                    ((uint_32)(0x000B + QUEC_VOICE_CALL_INDICATION_BASE))
#define QUEC_ALERTING_CALL_IND                                   ((uint_32)(0x000C + QUEC_VOICE_CALL_INDICATION_BASE))

#define QUEC_CC_INDICATION_MAX                                   ((uint_32)(0x00FF + QUEC_VOICE_CALL_INDICATION_BASE))  


//Fitz.xu 20211021: To fix compile error
/* Address Information structure - used for Calling Number, Called Number, Phonebook, etc. */
#define CI_MAX_ADDRESS_LENGTH 40
#define ATCI_NULL_TERMINATOR_LENGTH 1



//add volte call report by @mia.zhong 20201019	
typedef struct
{
    UINT16 id;
    UINT16 dir;
    int status; //for DSCI stat
    UINT16 type;
	UINT16 mpty;
    char Digits[ CI_MAX_ADDRESS_LENGTH + ATCI_NULL_TERMINATOR_LENGTH ];
    UINT16 num_type;
    char release_direction;
}quec_volte_call_info;
//@mia.zhong 20201019

typedef enum 
{
	QL_VOICE_CALL_SUCCESS = 0,
	QL_VOICE_CALL_FAILURE,
}QL_VOICE_CALL_ERROR_CODE;

typedef struct
{
	quec_task_t task_ref;
	unsigned int ind_flag; 
	void *ind_msg_buf; 
	unsigned int ind_msg_len;
	void *contextPtr;
}USR_CALLBACK_TASK_ARGV;

typedef struct 
{
     UINT16 CallId;
}Quec_call_incoming;


typedef struct 
{
     UINT16 CallId;
	 UINT8  CliValidity;
}Quec_call_waiting;


typedef Quec_call_incoming Quec_call_connect;

typedef struct 
{
     UINT16 CallId;
	 UINT8  cause;
}Quec_call_disconnect;

/*Declared function header*/
void voice_call_usr_callback_task(void *argv);
QL_VOICE_CALL_ERROR_CODE ql_voice_auto_answer(int seconds);
QL_VOICE_CALL_ERROR_CODE ql_voice_call_start(char* phone_num);
QL_VOICE_CALL_ERROR_CODE ql_voice_call_answer();
QL_VOICE_CALL_ERROR_CODE ql_voice_call_end();
QL_VOICE_CALL_ERROR_CODE ql_voice_call_start_dtmf(int paracount, char dtmf, ...);
QL_VOICE_CALL_ERROR_CODE ql_voice_call_wait(int paracount, int enable, ...);
QL_VOICE_CALL_ERROR_CODE ql_voice_call_fw_set(int reason, int fwmode, char* phone_num);
QL_VOICE_CALL_ERROR_CODE ql_voice_call_add_event_handler(QL_voice_call_EventHandlerFunc_t handlerPtr, void* contextPtr);


void quec_call_event_ind(void *paras, uint_32 event_flag);


#ifdef __cplusplus
}
#endif

#endif


