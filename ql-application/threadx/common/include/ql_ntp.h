/*============================================================================
  Copyright (c) 2022 Quectel Wireless Solution, Co., Ltd.  All Rights Reserved.
  Quectel Wireless Solution Proprietary and Confidential.
 =============================================================================*/

#ifndef __QL_NTP_H__
#define __QL_NTP_H__

#include "sockets.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef enum 
{
	QL_NTP_SUCCESS,
	QL_NTP_GENERIC_FAILURE,
}QL_NTP_ERROR_CODE;

typedef void (*ql_ntp_status_cb) (int ntp_status);

 /****************************************************************************
 * Function: ql_ntp_sync_ex
 * Description: sync ntp time
 
 * Parameters::
 	［IN/OUT］ ntp_status_cb:ntp callback to get the result if sync
 * Return:
    void
******************************************************************************/
void ql_ntp_sync_ex(ql_ntp_status_cb ntp_status_cb);


  /****************************************************************************
  * Function: ql_ntp_set_cid
  * Description: set pdp cid
  
  * Parameters::
     ［IN］ pdp:pdp cid value
  * Return:
     QL_NTP_SUCCESS   sucess
     QL_NTP_GENERIC_FAILURE  fail
 ******************************************************************************/
QL_NTP_ERROR_CODE ql_ntp_set_cid(int pdp);

/****************************************************************************
* Function: ql_ntp_set_server
* Description: set ntp server url 

* Parameters::
  ［IN］ntp_svr:ntp server url 
* Return:
  QL_NTP_SUCCESS   sucess
  QL_NTP_GENERIC_FAILURE  fail
******************************************************************************/
QL_NTP_ERROR_CODE ql_ntp_set_server(char *ntp_svr);

 /****************************************************************************
 * Function: ql_ntp_sync
 * Description: sync ntp time
 
 * Parameters::
 	void
 * Return:
    void
******************************************************************************/
void ql_ntp_sync(void);

#ifdef __cplusplus
}
#endif

#endif

