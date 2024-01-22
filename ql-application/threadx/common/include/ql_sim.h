/*================================================================
  Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/
/*
 * @Author: Pony.ma 
 * @Date: 2020-01-08 09:25:22 
 * @Last Modified by:   Pony.ma 
 * @Last Modified time: 2020-01-08 09:25:22 
 */


#ifndef _QL_SIM_H
#define _QL_SIM_H


#include "ql_gpio.h"

typedef enum
{
	QL_SIM_0,
	QL_SIM_1,
	NUM_OF_QL_SIM
}CMSimID_ex;

//�β�
typedef void (*SwitchSimDoneCb)(UINT8);

#define QL_SIM_MCC_LEN      4   /**  Length of the MCC. */
#define QL_SIM_MNC_MAX      4   /**  Maximum length of the MNC. */
#define QL_SIM_PLMN_NUM_MAX 24  /**  Maximum number of PLMN data sets. */

typedef void (*sim_detect_calback)(PIN_LEVEL_E pinlevel);

typedef enum 
{
	QL_SIM_SUCCESS,
	QL_SIM_GENERIC_FAILURE,
}QL_SIM_ERROR_CODE;



typedef struct 
{
    uint8_t mcc[QL_SIM_MCC_LEN];  /**< MCC value in ASCII characters.*/
    uint8_t mnc[QL_SIM_MNC_MAX];  /**< MNC value in ASCII characters.*/
}QL_SIM_PLMN_INFO;  

typedef struct 
{
    unsigned int          preferred_operator_list_num;                    /**< Must be set to the number of elements in preferred_operator_list. */
    QL_SIM_PLMN_INFO    preferred_operator_list[QL_SIM_PLMN_NUM_MAX];   /**< Preferred operator list. */
}QL_SIM_PREFERRED_OPERATOR_LIST;    /* Message */

#define QL_SIM_PIN_LEN_MAX  16   /**  Maximum length of PIN data. */ 
typedef struct 
{
    uint8_t                     pin_value[QL_SIM_PIN_LEN_MAX];  /*  Value of the PIN */
}QL_SIM_VERIFY_PIN_INFO;  

typedef struct 
{
    uint8_t                     old_pin_value[QL_SIM_PIN_LEN_MAX];  /**< Value of the old PIN as a sequence of ASCII characters. */
    uint8_t                     new_pin_value[QL_SIM_PIN_LEN_MAX];  /**< Value of the new PIN as a sequence of ASCII characters. */
}QL_SIM_CHANGE_PIN_INFO; 

typedef struct 
{
    uint8_t                     puk_value[QL_SIM_PIN_LEN_MAX];      /**< Value of the PUK as a sequence of ASCII characters. */
    uint8_t                     new_pin_value[QL_SIM_PIN_LEN_MAX];  /**< Value of the new PIN as a sequence of ASCII characters. */
}QL_SIM_UNBLOCK_PIN_INFO;  

typedef enum 
{
    QL_SIM_CARD_TYPE_UNKNOWN  = 0,    /**<  Unidentified card type.  */
    QL_SIM_CARD_TYPE_ICC      = 1,    /**<  Card of SIM or RUIM type.  */
    QL_SIM_CARD_TYPE_UICC     = 2,    /**<  Card of USIM or CSIM type.  */
}QL_SIM_CARD_TYPE;  
	
typedef enum 
{
   QL_SIM_STATUS_NOT_INSERTED,
   QL_SIM_STATUS_READY,
   QL_SIM_STATUS_SIM_PIN,
   QL_SIM_STATUS_SIM_PUK,
   QL_SIM_STATUS_PH_SIM_LOCK_PIN,
   QL_SIM_STATUS_PH_SIM_LOCK_PUK,
   QL_SIM_STATUS_PH_FSIM_PIN,
   QL_SIM_STATUS_PH_FSIM_PUK,
   QL_SIM_STATUS_SIM_PIN2,
   QL_SIM_STATUS_SIM_PUK2,
   QL_SIM_STATUS_PH_NET_PIN,
   QL_SIM_STATUS_PH_NET_PUK,
   QL_SIM_STATUS_PH_NET_SUB_PIN,
   QL_SIM_STATUS_PH_NET_SUB_PUK,
   QL_SIM_STATUS_PH_SP_PIN,
   QL_SIM_STATUS_PH_SP_PUK,
   QL_SIM_STATUS_PH_CORP_PIN,
   QL_SIM_STATUS_PH_CORP_PUK,
   QL_SIM_STATUS_BUSY,
   QL_SIM_STATUS_BLOCKED,
   QL_SIM_STATUS_UNKNOWN//20
}QL_SIM_STATUS;    /**< Card state. */

#define QL_SIM_ICCID_LEN 10
#define QL_SIM_IMSI_LEN 16

typedef struct {
    //QL_SIM_STATUS card_status;
    char imsi[QL_SIM_IMSI_LEN];
    UINT8 iccid[QL_SIM_ICCID_LEN*2+1];
    QL_SIM_STATUS card_status;
} QL_SIMCARD_INFO;

typedef struct 
{
    uint8_t                         pin1_num_retries;       /**<   Number of PIN 1 retries. */
    uint8_t                         puk1_num_retries;       /**<   Number of PUK 1 retries. */
    uint8_t                         pin2_num_retries;       /**<   Number of PIN 2 retries. */
    uint8_t                         puk2_num_retries;       /**<   Number of PUK 2 retries. */
}QL_SIM_CARD_PIN_INFO; 



typedef struct 
{
    QL_SIM_CARD_TYPE      card_type; // SIM card type
    QL_SIM_STATUS     card_state;  //SIM card state
    QL_SIM_CARD_PIN_INFO  card_pin_info; // PIN info
}QL_SIM_CARD_INFO; 

typedef enum 
{
    QL_SIM_FILE_TYPE_UNKNOWN      = 0,/**<  Unknown file type  */
    QL_SIM_FILE_TYPE_TRANSPARENT  = 1,/**< File structure consisting of a sequence of bytes.  */
    QL_SIM_FILE_TYPE_CYCLIC       = 2,/**< File structure consisting of a sequence of records, each containing the same fixed size in 
                                                     chronological order. Once all the records have been used, the oldest data is overwritten.  */
    QL_SIM_FILE_TYPE_LINEAR_FIXED  = 3,    /**< File structure consisting of a sequence of records, each containing the same fixed size.  */
}QL_SIM_FILE_TYPE;

typedef enum 
{
    QL_SIM_FILE_ACCESS_TYPE_ALWAYS      =0,
    QL_SIM_FILE_ACCESS_TYPE_CHV1        =1,
    QL_SIM_FILE_ACCESS_TYPE_CHV2        =2,
    QL_SIM_FILE_ACCESS_TYPE_ADM         =3,
}QL_SIM_FILE_ACCESS_TYPE;
	
typedef struct 
{
    QL_SIM_FILE_ACCESS_TYPE read_access;
    QL_SIM_FILE_ACCESS_TYPE update_access;
}QL_SIM_FILE_ACCESS_INFO;

typedef enum 
{
    QL_SIM_FILE_STATUS_INVALID      =0,
    QL_SIM_FILE_STATUS_EFFECTIVE    =1,
}QL_SIM_FILE_STATUS;


typedef struct 
{
    unsigned int                id;
    QL_SIM_FILE_TYPE            type;    /**<   File type: */
    QL_SIM_FILE_ACCESS_INFO     access;    /**<   File access conditions: */
    QL_SIM_FILE_STATUS          status;    /**<   File status: */
    unsigned int                size;      /**<   Size of transparent files.*/
    unsigned int                record_len;    /**<   Size of each cyclic or linear fixed file record.*/
    unsigned int                record_count;   /**<   Number of cyclic or linear fixed file records.*/
}QL_SIM_FILE_INFO; 

typedef struct 
{
    int sw1;
    int sw2;
}QL_SIM_FILE_OPERATION_RET;

#define QL_SIM_DATA_LEN_MAX     255
typedef struct 
{
    unsigned int    data_len;                        /**< Must be set to the number of elements in data. */
    uint8_t     data[QL_SIM_DATA_LEN_MAX];       /**< Data retrieved from the card. */
}QL_SIM_CARD_FILE_DATA; 

typedef enum
{
    QL_SIM_PHONE_BOOK_STORAGE_DC,
    QL_SIM_PHONE_BOOK_STORAGE_EN,
    QL_SIM_PHONE_BOOK_STORAGE_FD,
    QL_SIM_PHONE_BOOK_STORAGE_LD,
    QL_SIM_PHONE_BOOK_STORAGE_MC,
    QL_SIM_PHONE_BOOK_STORAGE_ME,
    QL_SIM_PHONE_BOOK_STORAGE_MT,
    QL_SIM_PHONE_BOOK_STORAGE_ON,
    QL_SIM_PHONE_BOOK_STORAGE_RC,
    QL_SIM_PHONE_BOOK_STORAGE_SM,
    QL_SIM_PHONE_BOOK_STORAGE_AP,
    QL_SIM_PHONE_BOOK_STORAGE_MBDN,
    QL_SIM_PHONE_BOOK_STORAGE_MN,
    QL_SIM_PHONE_BOOK_STORAGE_SDN,
    QL_SIM_PHONE_BOOK_STORAGE_ICI,
    QL_SIM_PHONE_BOOK_STORAGE_OCI,
}QL_SIM_PHONE_BOOK_STORAGE;

#define QL_SIM_PHONE_BOOK_RECORDS_MAX_COUNT 20

typedef struct 
{ // when write, if phonenum is empty, it means to delete this item specified by index  
    int          index;  // the record index in phone book
    uint8_t      username[32];   //  username
    uint8_t      phonenum[24];   //  Phone number, it can include '+'*/
}QL_SIM_PHONE_BOOK_RECORD_INFO;


typedef struct 
{
    int record_count;  //the count of record
    QL_SIM_PHONE_BOOK_RECORD_INFO record[QL_SIM_PHONE_BOOK_RECORDS_MAX_COUNT]; // the list of record
}QL_SIM_PHONE_BOOK_RECORDS_INFO;

/*****************************************************************
* Function: ql_sim_get_cur_SimId
*
* Description:
* 	get current sim ID
*   (˫������ģʽ��)��ȡ��ǰ������SIM��
* Parameters:
* 	
* 	
* Return:
* 	0--sim1
*	1--sim2
*
*****************************************************************/
extern int ql_sim_get_cur_SimId(void);

/*****************************************************************
* Function: ql_sim_switch_card
*
* Description:
* 	switch current sim card 
* 
* Parameters:
* 	simID--what you want to set now
*   callbk--when switch sim done, will run it
* 	
* Return:
* 	0--success
*  -1--fail
*
*****************************************************************/
extern int ql_sim_switch_card(int simID);

/*****************************************************************
* Function: ql_sim_switch_card_ex
*
* Description:
* 	switch current sim card 
* 
* Parameters:
* 	simID--the simcard you want to set now
*   callbk--when switch sim done, will run it
* 	
* Return:
* 	0--success
*  -1--fail
*
*****************************************************************/
extern QL_SIM_ERROR_CODE ql_sim_switch_card_ex(CMSimID_ex simID, SwitchSimDoneCb cb);
/*****************************************************************
* Function: ql_sim_get_simcard_info
*
* Description:
* 	��ȡ�Ŀ�����Ϣ(��imsi,iccid)
* 
* Parameters:
* 	simID--0����1��1����2
*   pt_info--��ȡ����Ϣ�洢��λ��
* 	
* Return:
* 	0--success
*  -1--fail
*
*****************************************************************/
extern QL_SIM_ERROR_CODE ql_sim_get_simcard_info(QL_SIMCARD_INFO *pt_info, CMSimID_ex sim_id);

/*****************************************************************
* Function: ql_sim_get_imsi
*
* Description:
* 	��ȡ SIM ���� IMSI��
* 
* Parameters:
* 	imsi	  		[out] 		SIM ���� IMSI���ַ�����  
* 	imsi_len	  	[in] 		imsi ����ĳ��ȡ�
* Return:
* 	QL_SIM_SUCCESS				�ɹ���
*	QL_SIM_GENERIC_FAILURE		ʧ�ܡ�
*
*****************************************************************/
extern QL_SIM_ERROR_CODE ql_sim_get_imsi(char *imsi,size_t imsi_len);


/*****************************************************************
* Function: ql_sim_get_iccid
*
* Description:
* 	��ȡ SIM ���� ICCID��
* 
* Parameters:
* 	iccid	  		[out] 		SIM ���� ICCID���ַ����� 
* 	iccid_len	  	[in] 		iccid ����ĳ��ȡ�  
* Return:
* 	QL_SIM_SUCCESS				�ɹ���
*	QL_SIM_GENERIC_FAILURE		ʧ�ܡ�
*
*****************************************************************/
extern QL_SIM_ERROR_CODE ql_sim_get_iccid(char *iccid,size_t iccid_len);


/*****************************************************************
* Function: ql_sim_get_phonenumber
*
* Description:
* 	��ȡ SIM ���������롣 
* 
* Parameters:
* 	phonenumber	  		[out] 	SIM ���������룬�ַ�����  
* 	phonenumber_len	  	[in] 	phonenumber ����ĳ��ȡ�  
* Return:
* 	QL_SIM_SUCCESS				�ɹ���
*	QL_SIM_GENERIC_FAILURE		ʧ�ܡ�
*
*****************************************************************/
extern QL_SIM_ERROR_CODE ql_sim_get_phonenumber(char *phonenumber,size_t phonenumber_len);


/*****************************************************************
* Function: ql_sim_verify_pin
*
* Description:
* 	�� SIM ״̬Ϊ���� PIN/PIN2������ PIN/PIN2 �룬������֤�� 
* 
* Parameters:
* 	pt_info	  			[in] 	PIN/PIN2 �룬�� QL_SIM_VERIFY_PIN_INFO�� 
* Return:
* 	QL_SIM_SUCCESS				�ɹ���
*	QL_SIM_GENERIC_FAILURE		ʧ�ܡ�
*
*****************************************************************/
extern QL_SIM_ERROR_CODE ql_sim_verify_pin(QL_SIM_VERIFY_PIN_INFO       *pt_info); // [IN] PIN/PIN2


/*****************************************************************
* Function: ql_sim_change_pin
*
* Description:
* 	���� SIM ���� PIN ��
* 
* Parameters:
* 	pt_info	  			[in] 	����ɵ� PIN ���µ� PIN���� QL_SIM_CHANGE_PIN_INFO��  
* Return:
* 	QL_SIM_SUCCESS				�ɹ���
*	QL_SIM_GENERIC_FAILURE		ʧ�ܡ�
*
*****************************************************************/
extern QL_SIM_ERROR_CODE ql_sim_change_pin(QL_SIM_CHANGE_PIN_INFO       *pt_info );  // [IN] PIN


/*****************************************************************
* Function: ql_sim_unblock_pin
*
* Description:
* 	����δ������� PIN/PIN2 ���SIM ��״̬Ϊ���� PUK/PUK2 ʱ��
*	���� PUK/PUK2 ����µ� PIN/PIN2 ����н�����
* 
* Parameters: 
* 	pt_info	  			[in] 	���� PUK/PUK2 ����µ� PIN/PIN2 �룬�� QL_SIM_UNBLOCK_PIN_INFO��  
* Return:
* 	QL_SIM_SUCCESS				�ɹ���
*	QL_SIM_GENERIC_FAILURE		ʧ�ܡ�
*
*****************************************************************/
extern QL_SIM_ERROR_CODE ql_sim_unblock_pin(QL_SIM_UNBLOCK_PIN_INFO       *pt_info);// [IN] input PUK/PUK2 and new PIN/PIN2


/*****************************************************************
* Function: ql_sim_enable_pin
*
* Description:
* 	���� SIM �� PIN ����֤�� 
* 
* Parameters: 
* 	pt_info			  	[in] 	���� PIN �룬�� QL_SIM_VERIFY_PIN_INFO�� 
* Return:
* 	QL_SIM_SUCCESS				�ɹ���
*	QL_SIM_GENERIC_FAILURE		ʧ�ܡ�
*
*****************************************************************/
extern QL_SIM_ERROR_CODE ql_sim_enable_pin(QL_SIM_VERIFY_PIN_INFO       *pt_info);// [IN] PIN


/*****************************************************************
* Function: ql_sim_disable_pin
*
* Description:
* 	�ر� SIM �� PIN ����֤
* 
* Parameters:
* 	pt_info	  			[in] 	���� PIN �룬�� QL_SIM_VERIFY_PIN_INFO�� 
* Return:
* 	QL_SIM_SUCCESS				�ɹ���
*	QL_SIM_GENERIC_FAILURE		ʧ�ܡ�
*
*****************************************************************/
extern QL_SIM_ERROR_CODE ql_sim_disable_pin(QL_SIM_VERIFY_PIN_INFO       *pt_info );  // [IN] PIN 


/*****************************************************************
* Function: ql_sim_get_card_status
*
* Description:
* 	��ȡ ��ǰSIM ��(����)״̬��Ϣ��
* 
* Parameters:
* 	card_status	  		[out] 	���� SIM ��������Ϣ���� QL_SIM_STATUS 
* Return:
* 	QL_SIM_SUCCESS				�ɹ���
*	QL_SIM_GENERIC_FAILURE		ʧ�ܡ�
*
*****************************************************************/
extern QL_SIM_ERROR_CODE ql_sim_get_card_status(int         *card_status);///< [OUT] sim card status info output


/*****************************************************************
* Function: ql_sim_read_phonebook_record
*
* Description:
* 	��ȡ SIM ����ָ���绰���е�һ��������绰�����¼�� 
* 
* Parameters:
* 	storage	  		[in] 	��Ҫ��ȡ�绰�����¼�ĵ绰���洢λ�á��� QL_SIM_PHONE_BOOK_STORAGE �� 
* 	start_index	  	[in] 	��Ҫ��ȡ�绰�����¼����ʼ��š�start_index Ϊ 0 ��ʾ��ʹ�ñ�Ż�ȡ�绰�����¼��  
* 	end_index	  	[in] 	��Ҫ��ȡ�绰�����¼�Ľ�����š�  
* 	username	  	[in] 	�� start_index Ϊ 0 ʱ��Ч���绰�����е��û�����  
* 	records	  		[out] 	���ص绰�����¼�б��� QL_SIM_PHONE_BOOK_RECORDS_INFO��  
* Return:
* 	QL_SIM_SUCCESS				�ɹ���
*	QL_SIM_GENERIC_FAILURE		ʧ�ܡ�
*
*****************************************************************/
extern QL_SIM_ERROR_CODE ql_sim_read_phonebook_record
(
    QL_SIM_PHONE_BOOK_STORAGE storage, //IN the storage position of the phone book
    int start_index,
    int end_index,
    char *username,
    QL_SIM_PHONE_BOOK_RECORDS_INFO   *records  // the list of records 
);


/*****************************************************************
* Function: ql_sim_write_phonebook_record
*
* Description:
* 	��ȡ SIM ����ָ���绰���е�һ��������绰�����¼�� 
* 
* Parameters:
* 	storage	  		[in] 	��Ҫ��ȡ�绰�����¼�ĵ绰���洢λ�á�   
* 	record	  		[in] 	��Ҫд��ĵ绰�����¼���� QL_SIM_PHONE_BOOK_RECORD_INFO�� 
* Return:
* 	QL_SIM_SUCCESS				�ɹ���
*	QL_SIM_GENERIC_FAILURE		ʧ�ܡ�
*
*****************************************************************/
extern QL_SIM_ERROR_CODE ql_sim_write_phonebook_record
(
    QL_SIM_PHONE_BOOK_STORAGE storage, //IN the storage position of the phone book
    QL_SIM_PHONE_BOOK_RECORD_INFO   *record //IN  a record
);

/*****************************************************************
* Function: ql_sim_config_detect
*
* Description:
* 	����SIM���Ȳ�ι��ܡ� 
* 
* Parameters:
* 	detenable	  		[in] 	�Ƿ�ʹ��SIM ���(0--��ʹ��,1--ʹ��)��   
* 	insertlevel	  		[in] 	SIM������ʱ���SIM���ŵ�ƽ(0--�͵�ƽ,1--�ߵ�ƽ) 
*   detectcallback      [in]    ����⵽SIM������������,���callback�ᱻִ��
* Return:
* 	QL_SIM_SUCCESS				�ɹ���
*	QL_SIM_GENERIC_FAILURE		ʧ�ܡ�
*
*****************************************************************/
QL_SIM_ERROR_CODE ql_sim_config_hot_plug_detect(unsigned char  detenable,PIN_LEVEL_E insertlevel,sim_detect_calback detectcallback);
/*****************************************************************
* Function: ql_sim1_detect_gpio_config
*
* Description:
* 	����SIM���Ȳ�ι��ܼ�����š� 
* 
* Parameters:
* 	detect_gpio			[in] 	���ܼ������,����Ӳ���ͺž�����Ӧ��GPIO����(����ģ��PIN�ź�)
* Return:
* 	QL_SIM_SUCCESS				�ɹ���
*	QL_SIM_GENERIC_FAILURE		ʧ�ܡ�
*
*****************************************************************/
QL_SIM_ERROR_CODE ql_sim1_detect_gpio_config(unsigned int detect_gpio);

/*****************************************************************
* Function: ql_set_dual_sim_single_imei
*
* Description:
* 	To support dual sim single IMEI 
* 
* Parameters:
* 	enable	  		[in] 	0-Not support dual sim single imei; 1-Support.
*
* Return:
* 	QL_SIM_SUCCESS				Operation success.
*	QL_SIM_GENERIC_FAILURE		Operation failed.
*
* Note: This setting will be saved to nvm and will take effect after reset.
*
*****************************************************************/
QL_SIM_ERROR_CODE ql_set_dual_sim_single_imei(unsigned char enable);



#endif

