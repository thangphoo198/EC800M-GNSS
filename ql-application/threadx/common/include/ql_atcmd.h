
/**  
  @file
  ql_at.h

  @brief
  This file provides the definitions for at functions, and declares the 
  common functions.

*/
/*============================================================================
  Copyright (c) 2017 Quectel Wireless Solution, Co., Ltd.  All Rights Reserved.
  Quectel Wireless Solution Proprietary and Confidential.
 =============================================================================*/
/*===========================================================================

                        EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.


WHEN        WHO            WHAT, WHERE, WHY
----------  ------------   ----------------------------------------------------
11/03/2020  Nebula.li      create
=============================================================================*/

#ifndef __QL_AT_H__
#define __QL_AT_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef enum QL_AT_RESP_STATUS_ENUM{
	QL_AT_RESP_OK = 0,
	QL_AT_RESP_ERROR,
	QL_AT_RESP_CME_ERROR,
	QL_AT_RESP_CMS_ERROR,
	QL_AT_RESP_INVALID_PARAM,
	QL_AT_RESP_TIME_OUT,
	QL_AT_RESP_SYS_ERROR,
}QL_AT_RESP_STATUS_E;

typedef void(*ql_atcmd_asyc_cb)(QL_AT_RESP_STATUS_E errno,char * buffer,unsigned int len);
QL_AT_RESP_STATUS_E ql_atcmd_send_sync(char *cmd,char *resp,int resp_len,char *include_str,int time_out);
QL_AT_RESP_STATUS_E ql_atcmd_send_sync_by_simid (char *cmd,char *resp,int resp_len,char *include_str,int time_out, unsigned short simid);
/***********************************************************************
 *
 * Name:   ql_atcmd_send_async    
 *
 * Description: ����ATָ�����������ǰ�߳�
 *
 * Parameters:  data��at�ַ���
 *              len�� at�ַ�������
 * Returns: 0: SUCCESS
 *
 * Notes:
 *
 ***********************************************************************/
QL_AT_RESP_STATUS_E ql_atcmd_send_async(char *data , unsigned int len);
/***********************************************************************
 *
 * Name:   ql_atcmd_send_async    
 *
 * Description: ɾ���첽at���л���
 *
 * Parameters:  VOID
 *              
 * Returns: 0 :SUCCESS
 *
 * Notes:
 *
 ***********************************************************************/

int ql_atcmd_async_close(void);
/***********************************************************************
 *
 * Name:   ql_atcmd_send_async    
 *
 * Description: ��ʼ���첽at
 *
 * Parameters: stack_ptr��  �첽at����ջ��ʼ��ַ����ΪNULL;
 *             stack_size�� ����ջ��С
 *             cb���û��ص�����
 * Returns:    0��success
 *
 * Notes:
 *
 ***********************************************************************/
int ql_atcmd_async_init(void *stack_ptr,unsigned int stack_size,ql_atcmd_asyc_cb cb);





int ql_atcmd_get_line_num(char *result);
int ql_atcmd_get_para_num_one_line(char *result,int line_index);
int ql_atcmd_get_para_value_str(char *result,int line_index,int para_index, char *para_value,int para_value_len);


#ifdef __cplusplus
}
#endif

#endif

