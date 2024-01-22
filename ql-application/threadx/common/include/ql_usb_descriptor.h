
/*================================================================
  Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/


#ifndef __QL_USB_H__
#define __QL_USB_H__


//states: 1>USB���� 0>USB�γ�
typedef void (*usbdectcb)(unsigned int states);

/*************************************************
*ע��USB������γ��ļ��ص�����
*�����ɹ�����0��������1
/************************************************/
int ql_usbdect_register_cb(usbdectcb cb);


/*****************************************************************
* Function: ql_usb_get_type
*
* Description:
* 	��ȡUSB�����͡� 
* 
* Parameters:
* 	void	  		  
* Return:
* 	1				USB����ö�١�
*	0		        USBδ������ö��,��USB,�����ǵ�Դ��������
*
NOTES:�˽ӿں�ʱ2s
*****************************************************************/
extern int ql_usb_get_type(void);


/*****************************************************************
* Function: ql_usb_connect_state
*
* Description:
* 	��ȡUSB������״̬,d+,d-�� [!!!�˽ӿ�Ŀǰ��bug,������ʹ��@2022/04/26]
* 
* Parameters:
* 	void	  		  
* Return:
* 	1				USB����ö���ҿ�������ͨѶ��
*	0		        USBδ���ӡ�
*
*****************************************************************/
int ql_usb_connect_state(void);


#endif


