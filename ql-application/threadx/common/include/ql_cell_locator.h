/**  
  @file
  ql_nw.h

  @brief
  This file provides the definitions for nw, and declares the 
  API functions.

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
03/24/2020  Archer.jia     create
=============================================================================*/

#ifndef __QL_CELL_LOCATOR_H__
#define __QL_CELL_LOCATOR_H__

#include "sockets.h"

#ifdef __cplusplus
extern "C" {
#endif

/**/
#define LOCATOR_MAX_ADDRESS_SIZE (256)
#define LOCATOR_MAX_ERR_MSG_SIZE (256)
#define LOCATOR_MAX_WIFI_NUM (5)
#define QUECLOCATOR_DEFAULT_SERVER_ADDR     "www.queclocator.com"
#define QUECLOCATOR_MAX_SERVER_LENGTH      (255)
#define QUECLOCATOR_DEFAULT_SERVER_PORT         80
#define QUECLOCATOR_DEFAULT_TIMEOUT             300
#define QUECLOCATOR_SERVER_PATH                 "/location/QLOC"

#define QUEC_MAX(a, b)      (a) > (b) ? (a) : (b)

#define QUECLOCATOR_FREQUENCY_DEFAULT (10)

#define QL_QUECLOCATOR_CONTENT_TYPE_ENHANCE    "05"
#define AUTH_TOTKEN_LEN 16
#define CITY_CODE_LEN 6

/*WIFI SCAN configuration item parameters*/
#define QL_LOC_WIFI_TIMEOUT_MIN 			4000
#define QL_LOC_WIFI_TIMEOUT_MAX 			255000
#define QL_LOC_WIFI_SCAN_ROUND_MIN  		1
#define QL_LOC_WIFI_SCAN_ROUND_MAX 			3
#define QL_LOC_WIFI_SCAN_MAX_BSSID_MIN  	2
#define QL_LOC_WIFI_SCAN_MAX_BSSID_MAX 		10
#define QL_LOC_WIFI_SCAN_TIMEOUT_MIN  		0
#define QL_LOC_WIFI_SCAN_TIMEOUT_MAX 		255
#define QL_LOC_WIFI_SCAN_PRIORITY_4G  		0
#define QL_LOC_WIFI_SCAN_PRIORITY_WIFI 		1


typedef enum
{
	QL_CELL_LOCATOR_ERR_UNKNOWN=-1,
	QL_CELL_LOCATOR_ERR_SUCCESS = 0,
	QL_CELL_LOCATOR_ERR_TOKEN_NOT_SET,
	QL_CELL_LOCATOR_ERR_NETWORK_MODE_UNKNOWN,
	QL_CELL_LOCATOR_ERR_ENCODE_REQ_INFO_ERROR,
	QL_CELL_LOCATOR_ERR_MAKE_MD5VALUE_ERROR,
	QL_CELL_LOCATOR_ERR_TLV_ENCODE_ERROR,
	QL_CELL_LOCATOR_ERR_SEND_REQ_INFO_ERROR,
	QL_CELL_LOCATOR_ERR_PARSE_RESPONSE_INFO_ERROR,
	QL_CELL_LOCATOR_ERR_PERFORM_TOO_FAST,
/*below errors are defined by server*/
	QL_CELL_LOCATOR_ERR_TOKEN_INVALID,
	QL_CELL_LOCATOR_ERR_DEVICE_POSITED_BEYOND_TIMES_PER_DAY,
	QL_CELL_LOCATOR_ERR_TOKEN_POSITED_BEYOND_MAX_TIMES,
	QL_CELL_LOCATOR_ERR_TOKEN_OUT_OF_DATE,
	QL_CELL_LOCATOR_ERR_IMEI_NOT_ACCESSIBLE_TO_SERVER,
	QL_CELL_LOCATOR_ERR_TOKEN_POSITED_BEYOND_MAX_TIMES_PER_DAY,
	QL_CELL_LOCATOR_ERR_TOKEN_POSITED_BEYOND_MAX_TIMES_PER_CYCLE,
	QL_CELL_LOCATOR_ERR_CONNECTED_DEVICES_NUM_BEYOND_MAX_NUM,
	
/*below errors are defined for debug*/
	QL_CELL_LOCATOR_ERR_SET_LOCAL_RREQUEST_INFO_ERROR,
	QL_CELL_LOCATOR_ERR_HTTP_CLIENT_INIT_ERROR,
	QL_CELL_LOCATOR_ERR_CELL_CFG_NULL
	
} QL_CELL_LOCATOR_ERR_E;
	
/* External incoming type method*/
typedef enum
{
	QL_CELL_TYPE_BEGIN	= 0,
	QL_CELL_TYPE_WIFI	= 6, /*wifi*/
	QL_CELL_TYPE_CELL	= 7, /*cell*/
	QL_CELL_TYPE_CELL_WIFI = 8, /*cell+wifi*/
	QL_CELL_TYPE_NUM
}QL_CELL_LOC_TYPE_E;

typedef enum
{
	QL_CELL_ERR_SUCCESS = 0,  //成功
	QL_CELL_ERR_DNS_FAIL, //对服务器进行DNS解析失败
	QL_CELL_ERR_SOCK_CREATE_FAIL, //创建socket失败
	QL_CELL_ERR_SOCK_BIND_FAIL, //对socket进行bind操作失败
	QL_CELL_ERR_SOCK_CONN_FAIL, //执行socket连接失败
	QL_CELL_ERR_SOCK_SEND_FAIL, //发送数据失败
	QL_CELL_ERR_SOCK_RECV_FAIL, //接收数据失败
	QL_CELL_ERR_RESP_TIMEOUT, //请求超时
	QL_CELL_ERR_NO_MEMORY, //请求缓存不足
	QL_CELL_ERR_LAST_REQUEST_NOT_FINISH, //上次请求还未完成
	QL_CELL_ERR_UNKNOWN //其他错误
} QL_CELL_LOC_ERR_E;

typedef enum {
	QL_CELL_OPT_ASYN, //Set the request execution mode, 0: synchronous; 1: asynchronous
	QL_CELL_OPT_ASYN_CB, //Asynchronous callback
	QL_CELL_OPT_INPUT_WIFI_NUM,//number of WIFI input
	QL_CELL_OPT_INPUT_WIFI_MAC, //External input WIFI MAC
	QL_CELL_OPT_METHOD, //positioning method
	QL_CELL_OPT_WIFI_TIMEOUT, //wifi Upper-layer application timeout,(4000-255000ms), the default is 12 seconds, Unit: milliseconds
	QL_CELL_OPT_WIFI_SCAN_ROUND_NUM, //Number of scan rounds (1-3), default 1
	QL_CELL_OPT_WIFI_SCAN_MAX_BSSID_NUM, //The number of scans (4-10), the default is 5
	QL_CELL_OPT_WIFI_SCAN_TIMEOUT, //RRC polling timeout, the default 7s, unit:seconds
	QL_CELL_OPT_WIFI_SCAN_PRIORITY, //wifi and 4g multiplex RF channel, both cannot be used at the same time, the default is 0 (4G priority)
}QL_CELL_LOC_OPT_E;

typedef enum
{
	QL_CELL_FINISHED,
	QL_CELL_INPROGRESS,
} QL_CELL_LOC_STATE_E;

typedef struct {
    int err_code;
    char err_msg[LOCATOR_MAX_ERR_MSG_SIZE];
} ql_cell_err;

typedef struct {
    /*longtitude*/
    double lon;
    /*latitude*/
    double lat;
    /*accuracy*/
    unsigned short accuracy;
    /*address info, not support yet*/
    unsigned char addrinfo[LOCATOR_MAX_ADDRESS_SIZE];
    /*address length, not support yet*/
    unsigned short addrlen;
    /*result*/
    ql_cell_err err;
} ql_cell_resp;


typedef struct 
{
	float lng;
	float lat;
    unsigned short accuracy;
}	cell_loc_info;

typedef struct
{
	char wifi_mac[18];
	char wifi_ssid[32];
	short wifi_rssi;
} ql_cell_wifiinfo;
typedef void (*QL_CELL_LOC_RESPONSE_CB)(QL_CELL_LOC_STATE_E state, struct cell_cfg_st *cell_cfg);

typedef struct cell_cfg_st
{
    char            server[QUECLOCATOR_MAX_SERVER_LENGTH + 1];
    unsigned short  sever_port;
    char            token[AUTH_TOTKEN_LEN+1];
    unsigned short  timeout;
    int             cell_num;
    /*last time for send request to server*/
    time_t    lasttime;
    /*visit server frequency*/
    unsigned int    frequency;
	/* pdp NO.*/
	int cid;	
	QL_CELL_LOC_RESPONSE_CB rsp_cb; 
	int asyn_f;
	float lng;
	float lat;
	char city_code[CITY_CODE_LEN+1];
    unsigned short accuracy;
	unsigned short loc_method;
	ql_cell_err err;
	int wifi_num;
	ql_cell_wifiinfo cell_wifiinfo[LOCATOR_MAX_WIFI_NUM];
	unsigned short wifi_timeout;
	unsigned short scanRoundNum;
	unsigned short scanMaxBssidNum;
	unsigned short sacnTimeout;
	unsigned short scanPriority;
}	ql_cell_cfg;

/*-----------------------------------------------------------------------------------------------*/
/**
  @brief cell locator init function, when you want to use cell locator, call this function first!
  @return if success return 0, else return -1
  */
/*-----------------------------------------------------------------------------------------------*/
int ql_cell_locator_init(ql_cell_cfg *g_cell_cfg);

int ql_cell_locator_release(ql_cell_cfg *g_cell_cfg);

int ql_cell_locator_set_cid(ql_cell_cfg *g_cell_cfg, int pdp);


/*-----------------------------------------------------------------------------------------------*/
/**
  @brief set locator query server and port, server length must be less than 255 bytes.
  @param[in] server the query server ip address
  @param[in] port the query server port 
  @return if success return 0, else return -1
  */
/*-----------------------------------------------------------------------------------------------*/
int ql_cell_locator_set_server(ql_cell_cfg *g_cell_cfg,  char *loc_server, int port);

/*-----------------------------------------------------------------------------------------------*/
/**
  @brief set locator query timeout, the value must between 1-300 [seconds]
  @param[in] timeout value of query timeout
  @return if success return 0, else return -1
  */
/*-----------------------------------------------------------------------------------------------*/
int ql_cell_locator_set_timeout(ql_cell_cfg *g_cell_cfg, unsigned short timeout);


/*-----------------------------------------------------------------------------------------------*/
/**
  @brief set locator query token, token length must be 16 bytes. the token Used to verify that 
         the client accessing the service is valid.
  @param[in] token string of token which want to be setted.
  @param[in] length of token string.
  @return if success return 0, else return -1
  */
/*-----------------------------------------------------------------------------------------------*/
int ql_cell_locator_set_token(ql_cell_cfg *g_cell_cfg, const char *token, int len);


/*-----------------------------------------------------------------------------------------------*/
/**
  @brief set locator extended item parameter configuration.
  @param[in] QL_CELL_OPT_E
  @return if success return 0, else return -1
  */
/*-----------------------------------------------------------------------------------------------*/
QL_CELL_LOC_ERR_E ql_cell_locator_setopt(ql_cell_cfg *cell_cfg, int tag, ...);

/*-----------------------------------------------------------------------------------------------*/
/**
  @brief perform cell locator query 
  @param[out] resp include query result or set the error_msg and error_code
  @return if success return 0, else return -1
  */
/*-----------------------------------------------------------------------------------------------*/
int ql_cell_locator_perform(ql_cell_cfg *g_cell_cfg);


#ifdef __cplusplus
}
#endif

#endif



