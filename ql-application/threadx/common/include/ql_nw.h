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
01/09/2020  Nebula.li      create
22/12/2020  Davison.du     add          Support dual-SIM dual standby
=============================================================================*/

#ifndef __QL_NW_H__
#define __QL_NW_H__

#ifdef __cplusplus
extern "C" {
#endif
#include "ql_type.h"


#define  QL_NW_IND_VOICE_REG_EVENT_FLAG  (1 << 0)  //VOICE注册事件
#define  QL_NW_IND_DATA_REG_EVENT_FLAG  (1 << 1)   //DATA注册事件
#define  QL_NW_IND_SIGNAL_STRENGTH_EVENT_FLAG  (1 << 2)  //信号强度事件
#define  QL_NW_IND_NITZ_TIME_UPDATE_EVENT_FLAG  (1 << 3)  //时间跟新事件

#define QL_NW_CELL_MAX_NUM 10
#define QL_NW_MCC_MAX_LEN 3
#define QL_NW_MNC_MAX_LEN 3
#define QL_NW_LONG_EONS_MAX_LEN 32
#define QL_NW_SHORT_EONS_MAX_LEN 32

#define QL_NW_REG_ON_FLAG 0x01
#define QL_NW_REG_OFF_FLAG 0x02

//#pragma pack(push)
//#pragma pack(1)

typedef enum 
{
	QL_NW_SUCCESS,
	QL_NW_GENERIC_FAILURE,
}QL_NW_ERROR_CODE;

typedef enum {
    QL_NW_PREF_NET_TYPE_GSM  = 0,	/**< GSM */
		
    QL_NW_PREF_NET_TYPE_UMTS,    	/**< UMTS . not supported in EC100Y and EC200S*/
    QL_NW_PREF_NET_TYPE_GSM_UMTS,   	/**< GSM_UMTS, auto. not supported in EC100Y and EC200S */
    QL_NW_PREF_NET_TYPE_GSM_UMTS_PREF_GSM,	/**< GSM_UMTS, GSM preferred. not supported in EC100Y and EC200S */
    QL_NW_PREF_NET_TYPE_GSM_UMTS_PREF_UMTS,	/**< GSM_UMTS, UMTS preferred. not supported in EC100Y and EC200S */
    
    QL_NW_PREF_NET_TYPE_LTE,			/**< LTE */
    
    QL_NW_PREF_NET_TYPE_GSM_LTE_AUTO,		/**< GSM_LTE, auto, single link */
	QL_NW_PREF_NET_TYPE_GSM_LTE_PREF_GSM,	/**< GSM_LTE, GSM preferred, single link */
	QL_NW_PREF_NET_TYPE_GSM_LTE_PREF_LTE,	/**< GSM_LTE, LTE preferred, single link */
	
	QL_NW_PREF_NET_TYPE_UMTS_LTE_AUTO,		/**< UMTS_LTE, auto, single link. not supported in EC100Y and EC200S */
    QL_NW_PREF_NET_TYPE_UMTS_LTE_PREF_UMTS,	/**< UMTS_LTE, UMTS preferred, single link. not supported in EC100Y and EC200S */
    QL_NW_PREF_NET_TYPE_UMTS_LTE_PREF_LTE,	/**< UMTS_LTE, LTE preferred, single link . not supported in EC100Y and EC200S*/
    
    QL_NW_PREF_NET_TYPE_GSM_UMTS_LTE_AUTO,		/**< GSM_UMTS_LTE, auto, single link. not supported in EC100Y and EC200S */
    QL_NW_PREF_NET_TYPE_GSM_UMTS_LTE_PREF_GSM,	/**< GSM_UMTS_LTE, GSM preferred, single link. not supported in EC100Y and EC200S */
    QL_NW_PREF_NET_TYPE_GSM_UMTS_LTE_PREF_UMTS,	/**< GSM_UMTS_LTE, UMTS preferred, single link. not supported in EC100Y and EC200S */
    QL_NW_PREF_NET_TYPE_GSM_UMTS_LTE_PREF_LTE,	/**< GSM_UMTS_LTE, LTE preferred, single link. not supported in EC100Y and EC200S */

    QL_NW_PREF_NET_TYPE_GSM_LTE_DUALLINK,	/**< GSM_LTE, dual link */
    QL_NW_PREF_NET_TYPE_UMTS_LTE_DUALLINK,	/**< UMTS_LTE, dual link. not supported in EC100Y and EC200S */
    QL_NW_PREF_NET_TYPE_GSM_UMTS_LTE_DUALLINK,		/**< GSM_UMTS_LTE, dual link. not supported in EC100Y and EC200S */

} QL_NW_PREFERRED_NETWORK_TYPE;

typedef struct 
{
  QL_NW_PREFERRED_NETWORK_TYPE  preferred_nw_mode;  //首选的网络制式，见QL_NW_PREFERRED_NETWORK_TYPE
  int  roaming_pref;      //漫游开关。 0 关； 1 开
}QL_NW_CONFIG_INFO_T;

typedef struct 
{
  char        nitz_time[32];  //格式：format: YY/MM/DD HH:MM:SS '+/-'TZ daylight,   18/09/19 07:40:18 +32 00.
  unsigned long  abs_time;   //0表示不可用
  unsigned char      leap_sec;   //0表示不可用
}QL_NW_NITZ_TIME_INFO_T;

typedef struct
{
  char long_eons[QL_NW_LONG_EONS_MAX_LEN+1];
  char short_eons[QL_NW_SHORT_EONS_MAX_LEN+1];
  char mcc[QL_NW_MCC_MAX_LEN+1];
  char mnc[QL_NW_MNC_MAX_LEN+1];
}QL_NW_OPERATOR_INFO_T;

typedef enum 
{
  QL_NW_ACCESS_TECH_GSM   = 0,
  QL_NW_ACCESS_TECH_GSM_COMPACT    = 1,
  QL_NW_ACCESS_TECH_UTRAN      = 2,
  QL_NW_ACCESS_TECH_GSM_wEGPRS    = 3,
  QL_NW_ACCESS_TECH_UTRAN_wHSDPA   = 4,
  QL_NW_ACCESS_TECH_UTRAN_wHSUPA     = 5,
  QL_NW_ACCESS_TECH_UTRAN_wHSDPA_HSUPA    = 6,
  QL_NW_ACCESS_TECH_E_UTRAN    = 7,
  QL_NW_ACCESS_TECH_UTRAN_HSPAP   = 8,
  QL_NW_ACCESS_TECH_E_UTRAN_CA   = 9,
  QL_NW_ACCESS_TECH_NONE = 10,
}QL_NW_ACCESS_TECHNOLOGY;

typedef struct 
{
  int status; //0：未知的网络；1：可用的网络；2：当前的网络；3：禁止使用的网络
  QL_NW_OPERATOR_INFO_T operator_name; //运营商信息，见QL_NW_OPERATOR_INFO_T。
  QL_NW_ACCESS_TECHNOLOGY  act;  //注网制式，见QL_NW_RADIO_TECH_TYPE_T。
}QL_NW_SCAN_ENTRY_INFO_T;


typedef enum {
    QL_NW_RADIO_TECH_UNKNOWN = 0,
    QL_NW_RADIO_TECH_GPRS = 1,
    QL_NW_RADIO_TECH_EDGE = 2,
    QL_NW_RADIO_TECH_UMTS = 3,
    QL_NW_RADIO_TECH_IS95A = 4,
    QL_NW_RADIO_TECH_IS95B = 5,
    QL_NW_RADIO_TECH_1xRTT =  6,
    QL_NW_RADIO_TECH_HSDPA = 9,
    QL_NW_RADIO_TECH_HSUPA = 10,
    QL_NW_RADIO_TECH_HSPA = 11,
    QL_NW_RADIO_TECH_EHRPD = 13,
    QL_NW_RADIO_TECH_LTE = 14,
    QL_NW_RADIO_TECH_HSPAP = 15, // HSPA+
    QL_NW_RADIO_TECH_GSM = 16, 
    QL_NW_RADIO_TECH_TD_SCDMA = 17,
    QL_NW_RADIO_TECH_IWLAN = 18,
    QL_NW_RADIO_TECH_LTEP = 19,
    QL_NW_RADIO_TECH_DC_HSPA = 20
} QL_NW_RADIO_TECHNOLOGY;

typedef enum {
  QL_NW_REG_STATE_NOT_REGISTERED=0,  //not registered, MT is not currently searching an operator to register to
  QL_NW_REG_STATE_HOME_NETWORK=1,  //registered, home network
  QL_NW_REG_STATE_TRYING_ATTACH_OR_SEARCHING=2, //not registered, but MT is currently trying to attach or searching an operator to register to
  QL_NW_REG_STATE_DENIED=3, //registration denied
  QL_NW_REG_STATE_UNKNOWN=4, //unknown
  QL_NW_REG_STATE_ROAMING=5, //registered, roaming
  QL_NW_REG_STATE_HOME_NETWORK_SMS_ONLY=6, //registered for “SMS only”, home network (not applicable)
  QL_NW_REG_STATE_ROAMING_SMS_ONLY=7,// registered for “SMS only”, roaming (not applicable)
  QL_NW_REG_STATE_ATTACHED_EMERGENCY_ONLY=8, //attached for emergency bearer services only 
  QL_NW_REG_STATE_HOME_NETWORK_CSFB_NOT_PREFERRED=9, //registered for “CSFB not preferred”, home network (not applicable)
  QL_NW_REG_STATE_ROAMING_CSFB_NOT_PREFERRED=10,//registered for “CSFB not preferred”, roaming (not applicable)
  QL_NW_REG_STATE_EMERGENCY_ONLY=11,//emergency bearer services only
}QL_NW_REG_STATE;

typedef struct
{
	QL_NW_REG_STATE state; //注册状态
	int lac;
	int cid;
	QL_NW_ACCESS_TECHNOLOGY  rat;
	int rejectCause;  //注册被拒绝的原因
	int psc; //Primary Scrambling Code
	//char act[10];  // Network access technology (GSM, WCDMA, LTE etc.)
} QL_NW_COMMON_REG_STATUS_INFO_T;

typedef struct
{
	QL_NW_COMMON_REG_STATUS_INFO_T voice_reg;  //VOICE注册信息，见QL_NW_COMMON_REG_STATUS_INFO_T
	QL_NW_COMMON_REG_STATUS_INFO_T data_reg;   //DATA注册信息。
}QL_NW_REG_STATUS_INFO_T;

typedef struct 
{
  int   nw_selection_mode; //0 自动；1手动
  char  mcc[QL_NW_MCC_MAX_LEN+1];
  char  mnc[QL_NW_MNC_MAX_LEN+1];
  QL_NW_ACCESS_TECHNOLOGY  act;  //selection 制式，见QL_NW_ACCESS_TECHNOLOGY。
}QL_NW_SELECTION_INFO_T;

typedef struct {
  int rssi;  
  int bitErrorRate;   
  int rscp;		
	int ecno;			
} QL_NW_GW_SIGNAL_STRENGTH_INFO_T;

typedef struct {
  int rssi;  
  int rsrp;   
  int rsrq;		
	int cqi;		
} QL_NW_LTE_SIGNAL_STRENGTH_INFO_T;

typedef struct {
    QL_NW_GW_SIGNAL_STRENGTH_INFO_T   GW_SignalStrength;
    QL_NW_LTE_SIGNAL_STRENGTH_INFO_T  LTE_SignalStrength;
}QL_NW_SIGNAL_STRENGTH_INFO_T;

typedef struct
{
    int flag;       /**Cell type, 0:present,1:neighbor.*/
    int cid;        /**Cell ID, (0 indicates information is not represent).*/
    int mcc;        /**This field should be ignored when cid is not present*/
    int mnc;        /**This field should be ignored when cid is not present*/
    int lac;        /**Location area code.(This field should be ignord when cid is not present). */
    int arfcn;      /**Absolute RF channel number. */
    char bsic;       /**Base station identity code. (0 indicates information is not present). */
	int rssi;		/**< Receive signal strength,in dBm */
}QL_MCM_NW_GSM_CELL_INFO_T;

typedef struct
{
    int flag;          /**Cell type, 0:present,1:inter,2:intra.*/
    int cid;           /**Cell ID, (0 indicates information is not represent).*/
    int lcid;          /**UTRAN Cell ID (0 indicates information is not present). */
    int mcc;           /**This field should be ignored when cid is not present*/
    int mnc;           /**This field should be ignored when cid is not present*/
    int lac;           /**Location area code. (This field should be ignored when cid is not present). */
    int uarfcn;        /**UTRA absolute RF channel number. */
    int psc;           /**Primary scrambling code. */
	int rssi;			/**<  Receive signal strength,in dBm */
}QL_MCM_NW_UMTS_CELL_INFO_T;
typedef enum 
{
	QL_NW_CELL_PRESENT,
	QL_NW_CELL_NEIGHBORING,
	QL_NW_CELL_NEIGHBORING_INTRAR,
	QL_NW_CELL_NEIGHBORING_INTER,
}QL_NW_CELL_TYPE_E;

typedef struct
{
    UINT32 flag;          /**Cell type, 0:present,1:inter,2:intra.*/
    UINT32 cid;           /**<Cell ID, (0 indicates information is not represent).*/
    UINT32 mcc;           /**This field should be ignored when cid is not present*/
    UINT32 mnc;           /**This field should be ignored when cid is not present*/
    UINT32 tac;           /**Tracing area code (This field should be ignored when cid is not present). */
    UINT32 pci;           /**Physical cell ID. Range: 0 to 503. */
    UINT32 earfcn;        /**E-UTRA absolute radio frequency channel number of the cell. RANGE: 0 TO 65535. */
	int rssi;		   /**< Receive signal strength,in dBm */
	int sinr;
}QL_MCM_NW_LTE_CELL_INFO_T;

/** Gets cell information. */
typedef struct 
{
    int                 gsm_info_valid;                         /**< Must be set to TRUE if gsm_info is being passed. */
    int                 gsm_info_num;                           /**< Must be set to the number of elements in entry*/
    QL_MCM_NW_GSM_CELL_INFO_T    gsm_info[QL_NW_CELL_MAX_NUM];  /**<   GSM cell information (Serving and neighbor. */  
    int                 umts_info_valid;                        /**< Must be set to TRUE if umts_info is being passed. */
    int                 umts_info_num;                          /**< Must be set to the number of elements in entry*/
    QL_MCM_NW_UMTS_CELL_INFO_T   umts_info[QL_NW_CELL_MAX_NUM];/**<   UMTS cell information (Serving and neighbor). */
    int                 lte_info_valid;                         /**< Must be set to TRUE if lte_info is being passed. */
    int                 lte_info_num;                           /**< Must be set to the number of elements in entry*/
    QL_MCM_NW_LTE_CELL_INFO_T    lte_info[QL_NW_CELL_MAX_NUM];  /**<   LTE cell information (Serving and neighbor). */
}QL_NW_CELL_INFO_T;


typedef enum
{
	QNW_CMD_GET_CONFIG = 0x0001,
	QNW_CMD_SET_CONFIG = 0x0002,
	QNW_CMD_GET_CSQ = 0x0004,
	QNW_CMD_GET_NITZ_TIME = 0x0008,
	QNW_CMD_GET_OPERATOR = 0x0010,
	QNW_CMD_GET_REG_STATUS = 0x0020,
	QNW_CMD_GET_SELECTION = 0x00040,
	QNW_CMD_SET_SELECTION = 0x00080,
	QNW_CMD_GET_SIGNAL_STRENGTH = 0x0100,
	QNW_CMD_GET_CELL = 0x0200,
	QNW_CMD_GET_MNC_MCC = 0x0400,
}QL_NW_CMD_LIST;

typedef struct
{
	QL_NW_CONFIG_INFO_T get_config_info;
	QL_NW_NITZ_TIME_INFO_T get_nitz_info;
	QL_NW_OPERATOR_INFO_T  get_operator_name;
	QL_NW_REG_STATUS_INFO_T  get_reg_status;
	QL_NW_SELECTION_INFO_T	get_selection;
	QL_NW_SIGNAL_STRENGTH_INFO_T	get_signal_strength;
	QL_NW_CELL_INFO_T	get_cell_info;
	unsigned short mcc;
	unsigned short mnc;
	int csq;
} QL_NW_GET_INFO_T;

typedef struct
{
	QL_NW_CONFIG_INFO_T set_config_info;
	QL_NW_SELECTION_INFO_T	set_selection;
} QL_NW_SET_INFO_T;

//#pragma pack(pop)

typedef enum 
{
  QL_NW_DRX_DEFAULT   = 0,
  QL_NW_DRX_320       = 320,   //320ms
  QL_NW_DRX_640       = 640,   //640ms
  QL_NW_DRX_1280      = 1280,  //1280ms
  QL_NW_DRX_2560      = 2560,  //2560ms
}QL_NW_DRX_T;

typedef void (*QL_NW_EventHandlerFunc_t)(unsigned int ind_flag, void *ind_msg_buf, unsigned int ind_msg_len, void *contextPtr);

typedef void (*QL_NW_DSDS_EventHandlerFunc_t)(unsigned int ind_flag, void *ind_msg_buf, unsigned int ind_msg_len, void *contextPtr, unsigned short simid);

typedef void (*QL_NW_Wifiscan_CBFunc_t) (const unsigned short scan_count, const char *scan_info);

/*****************************************************************
* Function: ql_nw_set_config
*
* Description:
* 	配置网络制式、漫游配置。
* 
* Parameters:
* 	pt_info	  		[in] 	对网络制式、漫游设置，见 QL _NW_CONFIG_INFO_T。 
*
* Return:
* 	QL_NW_SUCCESS			成功。
*	QL_NW_GENERIC_FAILURE 	失败。
*
*****************************************************************/
QL_NW_ERROR_CODE ql_nw_set_config(QL_NW_CONFIG_INFO_T  *pt_info);



/*****************************************************************
* Function: ql_nw_get_config
*
* Description:
* 	获取当前设置的网络制。
* 
* Parameters:
* 	pt_info	  		[out] 	获取当前网络制式、漫游配置，见 QL _NW_CONFIG_INFO_T。 
*
* Return:
* 	QL_NW_SUCCESS			成功。
*	QL_NW_GENERIC_FAILURE 	失败。
*
*****************************************************************/
QL_NW_ERROR_CODE ql_nw_get_config(QL_NW_CONFIG_INFO_T  *pt_info);



/*****************************************************************
* Function: ql_nw_get_nitz_time_info
*
* Description:
* 	获取当前基站时间 。
* 
* Parameters:
* 	pt_info	  		[out] 	返回 modem 从基站获取的时间信息。见 QL _NITZ_TIME_INFO_T。 
*
* Return:
* 	QL_NW_SUCCESS			成功。
*	QL_NW_GENERIC_FAILURE 	失败。
*
*****************************************************************/
QL_NW_ERROR_CODE ql_nw_get_nitz_time_info(QL_NW_NITZ_TIME_INFO_T *pt_info);



/*****************************************************************
* Function: ql_nw_event_register
*
* Description:
* 	注册网络事件。 
* 
* Parameters:
* 	bitmask	  		[in] 	多种注册网络事件的掩码(时间上报事件|信号强度上报事件|DATA 注册事件|VOICE 注册事件)。
*
* Return:
* 	QL_NW_SUCCESS			成功。
*	QL_NW_GENERIC_FAILURE 	失败。
*
*****************************************************************/
QL_NW_ERROR_CODE ql_nw_event_register(unsigned int  bitmask);



/*****************************************************************
* Function: ql_nw_get_operator_name
*
* Description:
* 	获取当前注网的运营商信息。
* 
* Parameters:
* 	pt_info	  		[out] 	获取运营商信息。
*
* Return:
* 	QL_NW_SUCCESS			成功。
*	QL_NW_GENERIC_FAILURE 	失败。
*
*****************************************************************/
QL_NW_ERROR_CODE ql_nw_get_operator_name(QL_NW_OPERATOR_INFO_T  *pt_info);



/*****************************************************************
* Function: ql_nw_get_reg_status
*
* Description:
* 	获取当前网络注册信息。
* 
* Parameters:
* 	pt_info	  		[out] 	获取当前网络注册信息
*
* Return:
* 	QL_NW_SUCCESS			成功。
*	QL_NW_GENERIC_FAILURE 	失败。
*
*****************************************************************/
QL_NW_ERROR_CODE ql_nw_get_reg_status(QL_NW_REG_STATUS_INFO_T  *pt_info);


/*****************************************************************
* Function: ql_nw_get_signal_strength
*
* Description:
* 	获取详细信号强度 。
* 
* Parameters:
* 	pt_info	  		[out] 	返回信号强度信息。
*
* Return:
* 	QL_NW_SUCCESS			成功。
*	QL_NW_GENERIC_FAILURE 	失败。
*
*****************************************************************/
QL_NW_ERROR_CODE ql_nw_get_signal_strength(QL_NW_SIGNAL_STRENGTH_INFO_T    *pt_info);



/*****************************************************************
* Function: ql_nw_get_cell_info
*
* Description:
* 	获取当前服务及邻近小区信息。
* 
* Parameters:
* 	pt_info	  		[out] 	返回邻近 CELL 的信息。
*
* Return:
* 	QL_NW_SUCCESS			成功。
*	QL_NW_GENERIC_FAILURE 	失败。
*
*****************************************************************/
QL_NW_ERROR_CODE ql_nw_get_cell_info(QL_NW_CELL_INFO_T  *pt_info);



/*****************************************************************
* Function: ql_nw_add_event_handler
*
* Description:
* 	设置事件回调函数。
* 
* Parameters:
* 	handlerPtr	  		[in] 	事件回调函数。
* 	contextPtr  		[in] 	用户数据。
*
* Return:
* 	QL_NW_SUCCESS			成功。
*	QL_NW_GENERIC_FAILURE 	失败。
*
*****************************************************************/
QL_NW_ERROR_CODE ql_nw_add_event_handler(QL_NW_EventHandlerFunc_t handlerPtr, void* contextPtr);



/*****************************************************************
* Function: ql_nw_get_csq
*
* Description:
* 	获取csq信号强度
* 
* Parameters:
* 	csq	  			[out] 	返回 csq 信号强度信息，范围（0-31）,返回 99 为无效值。 
*
* Return:
* 	QL_NW_SUCCESS			成功。
*	QL_NW_GENERIC_FAILURE 	失败。
*
*****************************************************************/
QL_NW_ERROR_CODE ql_nw_get_csq(int *csq);
	
QL_NW_ERROR_CODE ql_nw_set_selection(QL_NW_SELECTION_INFO_T  *pt_info);
QL_NW_ERROR_CODE ql_nw_get_selection(QL_NW_SELECTION_INFO_T  *pt_info);


/*****************************************************************
* Function: ql_nw_add_dualsim_event_handler
*
* Description:
* 	设置DSDS双卡双待事件回调函数。
* 
* Parameters:
* 	handlerPtr	  		[in] 	事件回调函数。
* 	contextPtr  		[in] 	用户数据。
*
* Return:
* 	QL_NW_SUCCESS			成功。
*	QL_NW_GENERIC_FAILURE 	失败。
*
*****************************************************************/
QL_NW_ERROR_CODE ql_nw_add_dsds_event_handler(QL_NW_DSDS_EventHandlerFunc_t handlerPtr, void* contextPtr);


/*****************************************************************
* Function: ql_nw_get_info
*
* Description:
* 	获取network相关信息
* 
* Parameters:
* 	ql_nw_cmd	  			[int] 	读取network对应信息的bit指令 ，详见：QL_NW_CMD_LIST
*	get_nw_info				[out]   获取运营商、网络注册、信号强度等信息，详见：QL_NW_GET_INFO_T
*	simid					[int]	SIM卡id，0 为 SIM1，1为SIM2
*
*
* Return:
* 	QL_NW_SUCCESS			成功。
*	QL_NW_GENERIC_FAILURE 	失败。
*
*****************************************************************/
QL_NW_ERROR_CODE ql_nw_get_info(unsigned long ql_nw_cmd, QL_NW_GET_INFO_T* get_nw_info, unsigned short simid);


/*****************************************************************
* Function: ql_nw_set_info
*
* Description:
* 	设置network相关信息
* 
* Parameters:
* 	ql_nw_cmd	  			[int] 	设置network对应信息的bit指令 ，详见：QL_NW_CMD_LIST
*	set_nw_info				[int]   对网络制式、漫游config设置、selection信息设置，详见：QL_NW_SET_INFO_T
*	simid					[int]	SIM卡id，0 为 SIM1，1为SIM2
*
* Return:
* 	QL_NW_SUCCESS			成功。
*	QL_NW_GENERIC_FAILURE 	失败。
*
*****************************************************************/
QL_NW_ERROR_CODE ql_nw_set_info(unsigned long ql_nw_cmd, QL_NW_SET_INFO_T* set_nw_info, unsigned short simid);


/*****************************************************************
* Function: ql_nw_get_drxtm
*
* Description:
* 	获取服务小区的寻呼周期
* 
* Parameters:
* 	drx_value_get	  			[int] 	获取的寻呼周期值,单位是ms
*
* Return:
* 	QL_NW_SUCCESS			成功。
*	QL_NW_GENERIC_FAILURE 	失败。
*
*****************************************************************/
QL_NW_ERROR_CODE ql_nw_get_drxtm(int *drx_value_get);


/*****************************************************************
* Function: ql_nw_set_drxtm
*
* Description:
* 	设置服务小区的寻呼周期
* 
* Parameters:
* 	drx_value_set	  			[int] 	设置寻呼周期的值，参见结构体 QL_NW_DRX_T
*
* Return:
* 	QL_NW_SUCCESS			成功。
*	QL_NW_GENERIC_FAILURE 	失败。
*
*****************************************************************/
QL_NW_ERROR_CODE ql_nw_set_drxtm(QL_NW_DRX_T drx_value_set);


/*****************************************************************
* Function: ql_nw_get_rrc_duration
*
* Description:
* 	获取RRC连接时间参数
* 
* Parameters:
* 	rrc_duration_value_get	  			[int] 	RRC连接持续时间,单位是ms
*
* Return:
* 	QL_NW_SUCCESS			成功。
*	QL_NW_GENERIC_FAILURE 	失败。
*
*****************************************************************/
QL_NW_ERROR_CODE ql_nw_get_rrc_duration(int *rrc_duration_value_get);

/*****************************************************************
* Function: ql_nw_set_wifiscan_callback
*
* Description:
* 	设置wifiscan回调函数
* 
* Parameters:
* 	wifiscan_cb	  			[in] 	wifiscan结果回调函数
*
* Return:
* 	QL_NW_SUCCESS			成功。
*	QL_NW_GENERIC_FAILURE 	失败。
*
*NOTE:1>当扫描的超时时间到达(option) 2> 扫描到指定的数量(scanMaxBssidNum) 
* 底层task会触发执行设置的callback
*****************************************************************/
QL_NW_ERROR_CODE ql_nw_set_wifiscan_callback(QL_NW_Wifiscan_CBFunc_t wifiscan_cb);


/*****************************************************************
* Function: ql_nw_get_wifiscan_info
*
* Description:
* 	申请扫描wifiscan参数
* 
* Parameters:
* 	option                   [in]   扫描超时时间，4000-25500ms，默认是12秒，单位是毫秒
*	scanRoundNum             [in]   扫描轮数 1-3，默认是1轮
*	scanMaxBssidNum          [in]   扫描上报数量 4-10，默认是5个，规定了上报的mac地址数量。[最多10个]
*   sacnTimeout              [in]   扫描底层超时时间 0-255，默认是5秒，参数用于配置RRC轮询的timeout时间
*   scanPriority             [in]   扫描优先级      0-1， 默认是0，表示数据优先
*   sendUrcFlag              [in]   扫描结果上报方式 0-1，0表示通过回调函数上报 1表示通过URC的方式上报
* Return:
* 	QL_NW_SUCCESS			成功。
*	QL_NW_GENERIC_FAILURE 	失败。
*
*****************************************************************/
QL_NW_ERROR_CODE ql_nw_get_wifiscan_info(unsigned short option, unsigned short scanRoundNum, unsigned short scanMaxBssidNum, unsigned short sacnTimeout, unsigned short scanPriority, unsigned char sendUrcFlag);

/*****************************************************************
* Function: ql_nw_get_gdcnt
*
* Description:
* 	获取流量统计值
* 
* Parameters:
* 	bytes_send                   [out]   The amount of sent bytes
*	bytes_recv           		 [out]   The amount of received bytes
* Return:
* 	QL_NW_SUCCESS			成功。
*	QL_NW_GENERIC_FAILURE 	失败。
*
*****************************************************************/
QL_NW_ERROR_CODE ql_nw_get_gdcnt(int *bytes_send, int *bytes_recv);


/*****************************************************************
* Function: ql_nw_set_gdcnt
*
* Description:
*	设置流量统计
* 
* Parameters:
*	op					 	[in]	 The operation about data counter 0
							0   	Reset the data counter
							1    	 Save the results of data counter to NVM
* Return:
*	QL_NW_SUCCESS			成功。
*	QL_NW_GENERIC_FAILURE	失败。
*
*****************************************************************/
QL_NW_ERROR_CODE ql_nw_set_gdcnt(unsigned char op);

#ifdef __cplusplus
}
#endif

#endif
