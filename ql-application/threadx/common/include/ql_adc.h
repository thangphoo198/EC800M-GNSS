/*============================================================================
  Copyright (c) 2022 Quectel Wireless Solution, Co., Ltd.  All Rights Reserved.
  Quectel Wireless Solution Proprietary and Confidential.
 =============================================================================*/

#ifndef _QL_ADC_H
#define _QL_ADC_H


#ifdef __cplusplus
extern "C" {
#endif

/*========================================================================
 *  Macro Definition
 *========================================================================*/
 typedef enum
{
	ADC_CHANNEL_ADC0    = 0,
	ADC_CHANNEL_ADC1    = 1,
	ADC_CHANNEL_VBAT    = 2,
}QL_ADC_CHANNEL_TYPE_E;


typedef enum
{
	ADC_READ_FAIL    = 0,
	ADC_READ_SUCCESS = 1,
}QL_ADC_READ_STATE_E;



/*****************************************************************
* Function: ql_adc_init
*
* Description:
* 	��ʼ��ADC
* 
* Parameters:
* 	void	  			
*
* Return:
* 	0			�ɹ���
*	-1 	ʧ�ܡ�
*
*****************************************************************/
int ql_adc_init(void);

/*****************************************************************
* Function: ql_adc_read
*
* Description:
* 	��ȡADC��ֵ
* 
* Parameters:
* 	adc_channel  [in] ADCͨ��  ,�ο�	  	QUEC_ADC_CHANNEL_TYPE_E
*   p_batvol     [out] ADC��ֵ
*
* Return:
* 	0			��ȡʧ�ܡ�
*	1 	        ��ȡ�ɹ���
*   �ο�QL_ADC_READ_STATE_E
*
*****************************************************************/
int ql_adc_read(unsigned char adc_channel, unsigned short *p_batvol);

/*****************************************************************
* Function: ql_get_cur_source_vol
*
* Description:
* 
* Parameters:
*
*
* Return:
*
*   
* ��EC100Y ֧�ִ˽ӿ�
*****************************************************************/

int ql_get_cur_source_vol(void);

////���½ӿڲ�����ʹ��
void ql_adc_onff(unsigned char status);

int ql_adc_read_raw_value(unsigned char adc_channel, unsigned short *p_batvol);

#ifdef __cplusplus
} /*"C" */
#endif

#endif

