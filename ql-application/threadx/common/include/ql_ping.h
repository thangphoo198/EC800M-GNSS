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
* 	使用回调函数获取ping结果。
* 
* Parameters:
* 	state	  		[out] 	当前ping操作的状态
* 	err  			[out] 	ping操作的结果。
* 	statistic  		[out] 	ping操作的状态信息。
*
* Return:
* 	无
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
* 	  初始化ping操作的参数，内部会对内存申请，并设置ping操作结果的回调函数，返回ping 句柄。
* 
* Parameters:
* 	cfg	  		[in] 	ping操作配置参数。
*	cb			[in]	回调函数名
* Return:
* 	NULL，初始化失败。
*  	非NULL，初始化成功，返回ping参数句柄。
*
*****************************************************************/

extern ql_ping_ctx_t * ql_ping_init(ql_ping_cfg_t cfg, ql_ping_cb_t cb);
/*****************************************************************
* Function: ql_ping
*
* Description:
* 	  ping操作，非阻塞方式，ping操作结果可以在函调函数处理。
* 
* Parameters:
* 	ping_ctx_ptr	  		[in] 	ping参数句柄。
*
* Return:
*	0，成功。
*	非0，失败。
*
*****************************************************************/

extern int ql_ping(ql_ping_ctx_t * ping_ctx_ptr);
/*****************************************************************
* Function: ql_ping_deinit
*
* Description:
* 	  去初始化操作，对ql_ping_init申请内存进行释放。
* 
* Parameters:
* 	ping_ctx_ptr	  		[in] 	ping参数句柄。
*
* Return:
*	无
*****************************************************************/

extern void ql_ping_deinit(ql_ping_ctx_t * ping_ctx_ptr);

#endif
