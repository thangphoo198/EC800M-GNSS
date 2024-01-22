/*================================================================
  Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/

#ifndef _QL_PING_H
#define _QL_PING_H

#include "ql_rtos.h"

#pragma pack(push)
#pragma pack(1)

typedef struct
{
	int    pdpCid;
	char * host;
	int	   timeout;
	u8  dataSize;
	u8  pingNum;	
	u32 athandle;
	u8  ping_type;
	ql_sem_t qping_bind_sem;
} _ql_ping_cfg_t;

typedef struct
{
	int    pdpCid;
	char * host;
	int	   timeout;
	u8  dataSize;
	u8  pingNum;	
} ql_ping_cfg_t;

typedef struct
{
	char ipSrc[64];
	u8 dataSize;
	u32 rtt;
	u8 ttl;
	u8 sentNum;
	u8 rcvdNum;
	u8 lostNum;
	u32 minRtt;
	u32 maxRtt;
	u32 avgRtt;
} ql_ping_stat_t;

typedef struct
{
	ql_timer_t tmrHdl;
	ql_sem_t semHdl;
	ql_task_t threadHdl;
} ql_ping_dns_t;

typedef enum
{
	QL_PING_INPROGRESS,
	QL_PING_FINISHED
} ql_ping_state_e;

/*****************************************************************
* Function: ql_ping_cb_t
*
* Description:
* 	ʹ�ûص�������ȡping�����
* 
* Parameters:
* 	state	  		[out] 	��ǰping������״̬
* 	err  			[out] 	ping�����Ľ����
* 	statistic  		[out] 	ping������״̬��Ϣ��
*
* Return:
* 	��
*
*****************************************************************/

typedef void (* ql_ping_cb_t)(ql_ping_state_e state, int err, ql_ping_stat_t * statistic);

typedef struct
{
	_ql_ping_cfg_t config;
	ql_ping_stat_t statistic;
	ql_ping_dns_t dns;
	ql_task_t threadHdl;
	ql_ping_cb_t cb;
	u32	reserved;
    void *reserved1;
    u8 reserved2;
} ql_ping_ctx_t;



#pragma pack(pop)
/*****************************************************************
* Function: ql_ping_init
*
* Description:
* 	  ��ʼ��ping�����Ĳ������ڲ�����ڴ����룬������ping��������Ļص�����������ping �����
* 
* Parameters:
* 	cfg	  		[in] 	ping�������ò�����
*	cb			[in]	�ص�������
* Return:
* 	NULL����ʼ��ʧ�ܡ�
*  	��NULL����ʼ���ɹ�������ping���������
*
*****************************************************************/

extern ql_ping_ctx_t * ql_ping_init(ql_ping_cfg_t cfg, ql_ping_cb_t cb);
/*****************************************************************
* Function: ql_ping
*
* Description:
* 	  ping��������������ʽ��ping������������ں�����������
* 
* Parameters:
* 	ping_ctx_ptr	  		[in] 	ping���������
*
* Return:
*	0���ɹ���
*	��0��ʧ�ܡ�
*
*****************************************************************/

extern int ql_ping(ql_ping_ctx_t * ping_ctx_ptr);
/*****************************************************************
* Function: ql_ping_deinit
*
* Description:
* 	  ȥ��ʼ����������ql_ping_init�����ڴ�����ͷš�
* 
* Parameters:
* 	ping_ctx_ptr	  		[in] 	ping���������
*
* Return:
*	��
*****************************************************************/

extern void ql_ping_deinit(ql_ping_ctx_t * ping_ctx_ptr);

#endif
