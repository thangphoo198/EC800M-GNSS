/*================================================================
  Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/
/*******************************************************************************
                                 ql_sms.h
author
      rami.zhang
description
      API interface for sms 
creation time
      2020.4.24
*******************************************************************************/
#ifndef __QL_SMS_H__
#define __QL_SMS_H__
		
#ifdef __cplusplus
		extern "C" {
#endif
#include "ql_type.h"
#define sms_log(fmt, ...) custom_log("SMS", fmt, ##__VA_ARGS__)//("[sms][%s, %d] "fmt"\r\n", __func__, __LINE__, ##__VA_ARGS__)

typedef void (*QL_sms_EventHandlerFunc_t)(unsigned int ind_flag, void *ind_msg_buf, unsigned int ind_msg_len, void *contextPtr);

/*
typedef signed   char  int_8;
typedef unsigned char  uint_8;

typedef          short int_16;
typedef unsigned short uint_16;

typedef          int   int_32;
typedef unsigned int   uint_32;

typedef signed char	    int8_t;
typedef unsigned char   u_int8_t;
typedef short		    int16_t;
typedef unsigned short	u_int16_t;
//typedef int		        int32_t;
//typedef unsigned int	u_int32_t;
*/

#define QL_SMS_MIN_LEN                1       
#define MAX_LONGSMS_SEGMENT           8
#define MAX_SMS_LENGTH                (160*4)
#define SMS_BUF_LEN                   (MAX_SMS_LENGTH + 32)
#define MAX_LONGSMS_LENGTH            (160*4*MAX_LONGSMS_SEGMENT)
#define QL_CI_MAX_CI_MSG_PDU_SIZE	  180
#define QL_CI_MAX_ADDRESS_LENGTH      40


/*RAMI:sms indication*/
#define QUEC_SMS_INDICATION_BASE                                 ((uint_32)(0x1000))
#define QUEC_CI_MSG_PRIM_NEWMSG_IND                              ((uint_32)(0x0001 + QUEC_SMS_INDICATION_BASE))
#define QUEC_CI_MSG_PRIM_GET_SMSC_ADDR_CNF                       ((uint_32)(0x0002 + QUEC_SMS_INDICATION_BASE))
#define QUEC_CI_MSG_PRIM_NEWMSG_INDEX_IND                        ((uint_32)(0x0003 + QUEC_SMS_INDICATION_BASE))
//mia.zhong @20201020 [add volte sms report] start
#define QUEC_VOLTE_NEWMSG_IND                                    ((uint_32)(0x0004 + QUEC_SMS_INDICATION_BASE))//cmt
#define QUEC_VOLTE_NEWMSG_INDEX_IND                              ((uint_32)(0x0005 + QUEC_SMS_INDICATION_BASE))//cmti
//mia.zhong @20201020 [add volte sms report] end

#define QUEC_CI_INDICATION_MAX                                   ((uint_32)(0x00FF + QUEC_SMS_INDICATION_BASE))  

//mia.zhong @20201020 [add volte sms report] start
#define VOLTE_SMS_STORAGE_NAME_LEN 3

typedef struct
{
    char     storage[VOLTE_SMS_STORAGE_NAME_LEN];			/**< Where message is stored \sa CiMsgStorage */
    UINT16   index;			                                /**< Memory location */
}quec_volte_sms_info_cmti;
//mia.zhong @20201020 [add volte sms report] end

typedef void*   OSTaskRef;
typedef OSTaskRef				quec_task_t;

//mia.zhong @20210202
typedef enum {
    QL_MSG_STORAGE_BM = 0,  	/**< Broadcast message storage (in volatile memory) */
    QL_MSG_STORAGE_ME,      		/**< ME message storage */
    QL_MSG_STORAGE_MT,      		/**< Any of the storage locations associated with ME */
    QL_MSG_STORAGE_SM,      		/**< SIM message storage */
    QL_MSG_STORAGE_SR,      		/**< Status report storage */

    QL_MSG_NUM_STORAGES
} QL_SMS_MSG_STORAGE;

typedef struct {
    QL_SMS_MSG_STORAGE storage;
    int cur_num;
    int total_nums;
}QL_MSG_SAVE_LOCATION;

typedef struct
{
	quec_task_t task_ref;
	unsigned int ind_flag; 
	void *ind_msg_buf; 
	unsigned int ind_msg_len;
	void *contextPtr;
}USR_SMS_CALLBACK_TASK_ARGV;


struct map_node {
    unsigned short key;
    unsigned short value;
};


typedef struct __pdus {
    unsigned int count;
    char **PDU;
}PDUS;

typedef struct __pduudh {
    unsigned int count;    //Number of bytes of information element
    char IEI;           // Information element identification
    char IED[4];          // Information element data
}PDUUDH;

// user data header
typedef struct __udhs {
    int count;
    PDUUDH UDH;
}UDHS;

//user data array, used to split long sms
typedef struct __uds {
    unsigned int total;
    char **Data;
}UDS;

typedef struct __byte_array {
    char *array;
    unsigned int len;
}BYTEARRAY;

//mia.zhong @20210114 delete message by del_mode
typedef enum {
    QL_SMS_DEL_INDEX = 0,         /* Delete only one message indicated by the index */
    QL_SMS_DEL_RECV_READ,         /* Delete all received read messages */
    QL_SMS_DEL_RECV_READ_SENT,    /* Delete all received read messages as well as sent MO messages */
    QL_SMS_DEL_RECV_READ_MO,      /* Delete received read messages and all MO messages - sent and unsent */
    QL_SMS_DEL_ALL,               /* Delete all messages */
    
    QL_SMS_DEL_MODES_NUMS
}QL_SMS_DELETE_MODE;

enum EnumUDL {
    BIT7UDL = 160,
    BIT8UDL = 140,
    UCS2UDL = 70
};

typedef enum 
{
	QL_SMS_SUCCESS = 0,
	QL_SMS_FAILURE,
}QL_SMS_ERROR_CODE;


typedef enum 
{
	QL_COMPARE_TRUE = 0,
	QL_COMPARE_FAILURE,
}QL_COMPARE;
	

typedef struct QuecCiEtwsMsgInfo_struct{
    UINT8	        warningType;
	UINT8			activateAlert;
	UINT8 			activatePopup;
} QuecCiEtwsMsgInfo;

typedef struct QuecCiAddressType_struct{
    UINT8 NumType;  /* TON: Type of Number */
    UINT8 NumPlan;  /* NPI: Numbering Plan Identification */
} QuecCiAddressType;

typedef struct __QL_NEWMSG {
	UINT16	len;										/**< Length of the TPDU */
	UINT8	data[ QL_CI_MAX_CI_MSG_PDU_SIZE ]; 	/**< TPDU (transfer protocol data unit) */
}QL_NEWMSG;

typedef struct __QL_NEWMSG_INDEX {
    UINT8 		type;			/**< Type of new message received; values are CI_MSG_MSG_TYPE_DELIVER, CI_MSG_MSG_TYPE_STATUS_REPORT, and CI_MSG_MSG_TYPE_CBS \sa CiMsgMsgType */
    UINT8 		storage;			/**< Where message is stored \sa CiMsgStorage */
    UINT16        		index;			/**< Memory location */
}QL_NEWMSG_INDEX;

typedef struct QuecCiAddressInfo_struct{
    QuecCiAddressType AddrType;                 /* Address Type Information */
    UINT8             Length;                   /* Address Length in digits */
    UINT8             Digits[ QL_CI_MAX_ADDRESS_LENGTH ];  /* Address Digits */
	
} QuecCiAddressInfo;

typedef struct QuecCiOptAddressInfo_struct{
    UINT8             Present;      /* Address Info present? */
    QuecCiAddressInfo AddressInfo;  /* Address Info */
} QuecCiOptAddressInfo;


typedef struct QuecCiMsgPrimNewMsgInd_struct{
    UINT8   				type;				/**< Type of new message received; values are CI_MSG_MSG_TYPE_DELIVER, CI_MSG_MSG_TYPE_STATUS_REPORT, and CI_MSG_MSG_TYPE_CBS \sa CiMsgMsgType */
	/*Michal Bukai - SMS Memory Full Feature*/
	char        				ShortMsgId;			/**< Short message id. */
	UINT8                    	msgType;	  		/**< \sa CiMsgStoreDeliveryMsgType */
    INT16           			commandRef;		/**< Additional reference to hold ABSM transaction */
	UINT8     					res1U8[2];			/* Padding */
	UINT8           			messageCoding;    	/**< Message coding. \sa CbCIMessageCoding */
	QL_NEWMSG  					pdumsg;				/**< New message received \sa CiMsgPdu_struct */
    QuecCiOptAddressInfo  		optSca;  	 		/**< Optional service center address \sa CCI API Ref Manual */ // SCR #1777605: Optional Service Center Address
    QuecCiEtwsMsgInfo			etwsInfo;
} QuecCiMsgPrimNewMsgInd;


typedef struct
{
    char number[32];
    char body[280]; // 姣忔潯鏀跺埌鐨勭煭淇￠暱搴︽渶澶т负280
    char time[32];
    int  body_len;
    char *pdu_str;
	char code_type; // sms text's encode type, 0-GSM7bit, 1-8bit, 2-UCS2
}QL_SMS_STATUS_INFO;

typedef struct QlCiAddressType_struct{
    UINT8 NumType;  /* TON: Type of Number */
    UINT8 NumPlan;  /* NPI: Numbering Plan Identification */
} QlCiAddressType;

typedef struct recvmessage_struct{
	char num[32];
	char buf[280];
	int buflen;	
}recvmessage;

/* Address Information structure - used for Calling Number, Called Number, Phonebook, etc. */
#define QUEC_CI_MAX_ADDRESS_LENGTH 40

//ICAT EXPORTED STRUCT
typedef struct QlCiAddressInfo_struct{
    QlCiAddressType AddrType;                 /* Address Type Information */
    UINT8         Length;                   /* Address Length in digits */
    UINT8 Digits[ QUEC_CI_MAX_ADDRESS_LENGTH ];  /* Address Digits */
	
} QlCiAddressInfo;

typedef struct QlStringPoint_struct{
	char front_ptr[128];
	char* cen_tail_ptr;
	char tail_ptr[128];
}QlStringPoint;

typedef struct QlStringLength_struct{
	int front_len;
	int cen_tail_len;
	int tail_len;
}QlStringLength;

typedef struct Qlsmspducode_struct{
    QlStringPoint ptr;  
    QlStringLength strlength; 
} Qlsmspducode;

int ql_pdu_decode(QL_SMS_STATUS_INFO *info, char *data, int datalen);
int pdu_getdata(char *data, int len, char *src);
int bcd_decode(char *data, int index, int isMSB);
char *bit7_unpack(char *data, int septets, int fillbits);
int is_bit7_same(unsigned short UCS2);
int bit7_decode(char *src, int size, char *dst);
int32 map_get_value(struct map_node *map, unsigned int size, unsigned short key);

PDUS *ql_pdu_encode(char* smsc, char *dest_number, char *content, int content_len, int type);
UDS *content_split(char *content, int type);
UDHS *UpdateUDH(UDHS *udhs, int CSMMR, int total, int index);
int septets_to_chars(char *source, int index, int septets);
int septets_length(char *source);
char *pdu_encode_single(char *sca, char *da, char *uc, UDHS *udhs, int type);
BYTEARRAY *BIT7Encoding(char *udc, int *Septets);
char *BIT7Pack(BYTEARRAY *bit7_arr, int udhl);
int ql_array_To_Str(unsigned char *buf, unsigned int buflen, char *out);

QL_SMS_ERROR_CODE ql_set_sms_msg_mode(int messagemode);
//mia.zhong @20210202 get message mode
QL_SMS_ERROR_CODE ql_get_sms_msg_mode(int *messagemode);
QL_SMS_ERROR_CODE ql_set_sms_code_mode(char* codemode);
//mia.zhong @20210202 get code mode
QL_SMS_ERROR_CODE ql_get_sms_code_mode(char *codemode);
QL_SMS_ERROR_CODE ql_sms_send_text_msg(uint_8 *phone_num,uint_8 *data,char* codemode);
QL_SMS_ERROR_CODE ql_sms_send_pdu_msg(uint_8 *phone_num,uint_8 *data,int type);
QL_SMS_ERROR_CODE ql_sms_delete_msg(size_t index);
//mia.zhong @20210114 delete message by del_mode
QL_SMS_ERROR_CODE ql_sms_delete_msg_ex(unsigned int index, QL_SMS_DELETE_MODE del_mode);
//mia.zhong end
QL_SMS_ERROR_CODE ql_get_sms_center_address(uint_8* address);
QL_SMS_ERROR_CODE ql_set_sms_center_address(uint_8* address);
//mia.zhong @20201102 用户可自行添加短信中心前缀
QL_SMS_ERROR_CODE ql_set_sms_center_address_ex(uint_8* address, uint_8* prefix);
//mia.zhong
QL_SMS_ERROR_CODE ql_set_sms_save_location(char* mem1, char* mem2, char* mem3);
//mia.zhong @20210202 get save location
QL_SMS_ERROR_CODE ql_get_sms_save_location_and_nums(QL_MSG_SAVE_LOCATION *save_location_read_delete,QL_MSG_SAVE_LOCATION *save_location_write_send, QL_MSG_SAVE_LOCATION *save_location_recv);
QL_SMS_ERROR_CODE ql_set_sms_recive_dealmode(int dealmode);
QL_SMS_ERROR_CODE ql_search_sms_text_message(int index,recvmessage* payload);
QL_SMS_ERROR_CODE ql_search_sms_pdu_message(int index,char* pdu_payload);
QL_SMS_ERROR_CODE ql_sms_calculate_pdu_msg(uint_8 *data,int* length);
QL_SMS_ERROR_CODE ql_sms_add_event_handler(QL_sms_EventHandlerFunc_t handlerPtr, void* contextPtr);
QL_SMS_ERROR_CODE ql_get_sms_index(int codemode,int* index);
QL_SMS_ERROR_CODE ql_sms_send_pdu(uint_8 *code);



void quec_sms_event_ind(void *paras, int event_flag);

#ifdef __cplusplus
}
#endif

#endif


