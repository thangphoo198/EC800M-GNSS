/*================================================================
  Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/

#ifndef _QL_DEV_H
#define _QL_DEV_H

typedef enum 
{
	QL_DEV_SUCCESS,
	QL_DEV_GENERIC_FAILURE,
}QL_DEV_ERROR_CODE;

typedef enum
{
	QL_DEV_MODEM_MIN_FUN = 0 ,								//modem��С����
	QL_DEV_MODEM_FULL_FUN,									//modemȫ����
	QL_DEV_MODEM_DISABLE_RECEIVE_RF_CIRCUITS=3,				//modem�ر���Ƶ���յ�·
	QL_DEV_MODEM_DISABLE_TRANSMIT_AND_RECEIVE_RF_CIRCUITS,	//modem�ر���Ƶ����ͽ��յ�·
	QL_DEV_MODEM_DISABLE_SIM,								//modem�ر� SIM��
	QL_DEV_MODEM_TURN_OFF_FULL_SECONDARY_RECEIVE,			//modem��ȫ�رո�������
}QL_DEV_MODEM_FUNCTION;

/*****************************************************************
* Function: ql_dev_get_model
*
* Description:
* 	��ȡ�豸�ͺš�
* 
* Parameters:
* 	model	  		[out] 	�豸�ͺţ��ַ����� 
* 	model_len	  	[in] 	model ����ĳ��ȡ�  
*
* Return:
* 	QL_DEV_SUCCESS			�ɹ���
*	QL_DEV_GENERIC_FAILURE 	ʧ�ܡ�
*
*****************************************************************/
QL_DEV_ERROR_CODE ql_dev_get_model(char*model,unsigned int model_len);



/*****************************************************************
* Function: ql_dev_get_sn
*
* Description:
* 	��ȡ�豸 SN�� 
* 
* Parameters:
* 	sn	  		[out] 	�豸 SN���ַ����� 
* 	sn_len	  	[in] 	sn ����ĳ���
*
* Return:
* 	QL_DEV_SUCCESS			�ɹ���
*	QL_DEV_GENERIC_FAILURE 	ʧ�ܡ�
*
*****************************************************************/
QL_DEV_ERROR_CODE ql_dev_get_sn(char*sn, unsigned int sn_len);

/*****************************************************************
* Function: ql_dev_set_modem_fun
*
* Description:
* 	�����豸�� modem ���ܡ�
* 
* Parameters:
* 	function	  	[in] 	��Ҫ���õ� modem ���ܣ��� 4.1 QL_DEV_MODEM_FUNCTION�� 
* 	rst	  			[in] 	���� modem ����ǰ���Ƿ����� modem��0����������1�������� 
*
* Return:
* 	QL_DEV_SUCCESS			�ɹ���
*	QL_DEV_GENERIC_FAILURE 	ʧ�ܡ�
*
*****************************************************************/
QL_DEV_ERROR_CODE ql_dev_set_modem_fun(QL_DEV_MODEM_FUNCTION function,int rst);

/*****************************************************************
* Function: ql_dev_get_modem_fun
*
* Description:
* 	��ȡ�豸�� modem ��ǰ�Ĺ��ܡ�
* 
* Parameters:
* 	function	  		[out] 	�����豸�� modem ��ǰ�Ĺ��ܣ�ֵ����� 4.1 QL_DEV_MODEM_FUNCTION�� 
*
* Return:
* 	QL_DEV_SUCCESS			�ɹ���
*	QL_DEV_GENERIC_FAILURE 	ʧ�ܡ�
*
*****************************************************************/
QL_DEV_ERROR_CODE ql_dev_get_modem_fun(int* function);

/*****************************************************************
* Function: ql_dev_get_firmware_version
*
* Description:
* 	��ȡ�豸�Ĺ̼��汾�� 
* 
* Parameters:
* 	version	  		[out] 	�豸�Ĺ̼��汾���ַ�����
* 	version_len	  	[in] 	version ����ĳ��� 
*
* Return:
* 	QL_DEV_SUCCESS			�ɹ���
*	QL_DEV_GENERIC_FAILURE 	ʧ�ܡ�
*
*****************************************************************/
QL_DEV_ERROR_CODE ql_dev_get_firmware_version(char *version,unsigned int version_len);

/*****************************************************************
* Function: ql_dev_get_firmware_version
*
* Description:
* 	��ȡ�ͻ��豸�Ĺ̼��汾�� 
* 
* Parameters:
* 	version	  		[out] 	�ͻ��豸�Ĺ̼��汾���ַ�����
* 	version_len	  	[in] 	version ����ĳ��� 
*
* Return:
* 	QL_DEV_SUCCESS			�ɹ���
*	QL_DEV_GENERIC_FAILURE 	ʧ�ܡ�
*
*****************************************************************/
QL_DEV_ERROR_CODE ql_dev_get_cust_firmware_version(char *version,unsigned int version_len);

/*****************************************************************
* Function: ql_dev_get_imei
*
* Description:
* 	��ȡ�豸�� IMEI��
* 
* Parameters:
* 	imei	  		[out] 	�豸�� IMSI���ַ����� 
* 	imei_len	  	[in] 	imei ����ĳ��ȡ� 
* Return:
* 	QL_DEV_SUCCESS			�ɹ���
*	QL_DEV_GENERIC_FAILURE 	ʧ�ܡ�
*
*****************************************************************/
QL_DEV_ERROR_CODE ql_dev_get_imei(char *imei,unsigned int imei_len);

/*****************************************************************
* Function: ql_dev_get_cpu_uid
*
* Description:
* 	��ȡ�豸��cpu_uid�� 
* 
* Parameters:
* 	uid_ret	  		[in] ���ڱ����豸��cpu_uid��
*
* Return:
* 	�ޡ�
*
*****************************************************************/
void ql_dev_get_cpu_uid(unsigned long long * uid_ret);

#endif

