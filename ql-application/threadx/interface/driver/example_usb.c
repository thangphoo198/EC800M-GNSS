/*================================================================
  Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/

#include <stdio.h>
#include "ql_application.h"
#include "ql_usb_descriptor.h"


#define APP_DEBUG(fmt, args...)	printf(fmt, ##args)
#define USB_CDC_PID_TEST           1
#define USB_CDC_PID_VALUE          0x6001
#define USB_DESCRIPTOR_TYPE_STRING 3

UINT8   usb_connect = 0;
UINT8   quec_product[] = {0x10, 0x03, 'A', 0x00, 'n', 0x00, 'd', 0x00, 'r', 0x00, 'o', 0x00, 'i', 0x00, 'd', 0x00};
UINT16  len_product = sizeof(quec_product);
UINT8   protuctid = 2;
UINT8   *prost=quec_product;

//NOTE:The callback function must not invoke any “blocking??operating system calls.
void Ql_Usb_Detect_Handler(unsigned int states)
{   

	usb_connect = states; 

	if(states)
	{	
        printf("[OPEN]USB Connect\r\n");
	} 
	else
		printf("[OPEN]USB Disconnect\r\n");
}


static void quec_usb_test(void * argv)
{   
    INT     reg=0;
	INT		usb_connect_state = -1;	
	APP_DEBUG("<------example_usb.c------>\r\n");

	//注册USB连接与断开的回调函??
	ql_usbdect_register_cb(Ql_Usb_Detect_Handler);
	   
    while(1)
    {	
        if(usb_connect)
        { 
			usb_connect = NULL;
			if(ql_usb_get_type())
			{
				APP_DEBUG("PC usb!\r\n");
			}
			else
			{
				APP_DEBUG("Adaptor usb!\r\n");
			}
        }
		usb_connect_state = ql_usb_connect_state();
		APP_DEBUG("usb_connect_state = %d\r\n",usb_connect_state);
		ql_rtos_task_sleep_s(1); 
	}
}

//application_init(quec_usb_test, "quec_usb_test", 2, 0);