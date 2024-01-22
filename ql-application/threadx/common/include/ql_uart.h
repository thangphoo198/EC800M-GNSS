/*================================================================
  Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/
#ifndef _QL_UART_H_
#define _QL_UART_H_

#include "ql_type.h"
#ifdef __cplusplus
	 extern "C" {
#endif


typedef enum QL_UART_PORT_NUMBER_ENUM 
{
	QL_DEBUG_UART_PORT, 	//debug uart(GPIO29,30,31,32)
	QL_BT_UART_PORT,		//UART3(GPIO35,36/GPIO53,54)
	QL_MAIN_UART_PORT,		//main uart(GPIO51,52,53,54)
	QL_USB_CDC_PORT,
	QL_U4_UART_PORT,        //UART4
    QL_MAX_UART_PORT,
}QL_UART_PORT_NUMBER_E;

typedef enum QL_UART_FLOWCTRL_ENUM
{
	QL_FC_NONE = 0,
	QL_FC_HW,
}QL_UART_FLOWCTRL_E;

typedef enum QL_UART_BAUD_ENUM
{
	QL_UART_BAUD_300 		= 300,
	QL_UART_BAUD_600    	= 600,
    QL_UART_BAUD_1200       = 1200,
    QL_UART_BAUD_2400       = 2400,
    QL_UART_BAUD_3600       = 3600,
    QL_UART_BAUD_4800       = 4800,
    QL_UART_BAUD_7200       = 7200,
    QL_UART_BAUD_9600       = 9600,
    QL_UART_BAUD_14400      = 14400,
    QL_UART_BAUD_19200      = 19200,
    QL_UART_BAUD_28800      = 28800,
    QL_UART_BAUD_38400      = 38400,
    QL_UART_BAUD_57600      = 57600,
    QL_UART_BAUD_115200     = 115200,
    QL_UART_BAUD_230400     = 230400,
	QL_UART_BAUD_256000     = 256000,
    QL_UART_BAUD_460800     = 460800,
    QL_UART_BAUD_921600     = 921600,
	QL_UART_BAUD_1000000	= 1000000,
	QL_UART_BAUD_1500000	= 1500000,
	QL_UART_BAUD_1842000	= 1842000,
	QL_UART_BAUD_3686400	= 3686400,
}QL_UART_BAUD_E;

typedef enum QL_UART_DATABIT_ENUM
{
	QL_UART_DATABIT_5,
	QL_UART_DATABIT_6,
	QL_UART_DATABIT_7,
	QL_UART_DATABIT_8,
}QL_UART_DATABIT_E;

typedef enum QL_UART_STOPBIT_ENUM
{
	QL_UART_STOP_1,
	QL_UART_STOP_2,
}QL_UART_STOPBIT_E;

typedef enum QL_UART_PARITYBIT_ENUM
{
	QL_UART_PARITY_NONE,
	QL_UART_PARITY_EVEN,
	QL_UART_PARITY_ODD,
}QL_UART_PARITYBIT_E;

typedef struct ql_uart_config_struct
{
	QL_UART_BAUD_E baudrate;
	QL_UART_DATABIT_E data_bit;
	QL_UART_STOPBIT_E stop_bit;
	QL_UART_PARITYBIT_E parity_bit;
	QL_UART_FLOWCTRL_E flow_ctrl;
}ql_uart_config_t;

enum
{
 QL_UART_SUCCESS         =     0,
 QL_UART_OPEN_FAILED     =    -1,
 QL_UART_ALREAD_OPEN     =    -2,
 QL_UART_ONT_OPEN        =    -3,
 QL_UART_ILLEGAL_PORT    =    -4,
 QL_UART_RB_CFG_FAILED   =    -5,
 QL_UART_DCB_PRAM_ERR    =    -6,
 QL_UART_DCB_CFG_ERR     =    -7,
 QL_UART_WRITE_ERR       =    -8,
 QL_UART_WRITE_PRAM_ERR  =    -9,
 QL_UART_WRITE_MALLOC_ERR =   -10,
 QL_UART_READ_ERR         =  -11,
 QL_UART_CTS_HIGH         =  -12,
 QL_UART_IS_SENDING       =   1,
 QL_UART_NOT_SENDING      =   0
};
typedef void (*uart_callback)(QL_UART_PORT_NUMBER_E port, void *para);
typedef void (*uart_callback_ex)(QL_UART_PORT_NUMBER_E port, int len, void *private);

/***********************************************************************
 *
 * Name:   ql_uart_open    
 *
 * Description: �򿪶�Ӧ����
 *
 * Parameters:  baudrate:���ò�����
 *              flow_ctrl:�Ƿ�ʹ������
 * Returns:     0���򿪳ɹ�
 *              
 * Notes:
 *
 ***********************************************************************/
int ql_uart_open(QL_UART_PORT_NUMBER_E port, QL_UART_BAUD_E baudrate, QL_UART_FLOWCTRL_E flow_ctrl);
/***********************************************************************
 *
 * Name:   ql_uart_close    
 *
 * Description: �رն�Ӧ����
 *
 * Parameters:  port:Ҫ�رյ�port��
 *             
 * Returns:     0���رճɹ�
 *              other: faile
 * Notes:
 *
 ***********************************************************************/
int ql_uart_close(QL_UART_PORT_NUMBER_E port);
/***********************************************************************
 *
 * Name:   ql_uart_set_dcbconfig   
 *
 * Description: ���ö�Ӧ����ģʽ
 *
 * Parameters:  port:��Ӧ�Ĵ��ڣ�cdc����������
 *              dcb:ģʽ����
 * Returns:     0��send_success
 *              other: faile
 * Notes:
 *
 ***********************************************************************/
int ql_uart_set_dcbconfig(QL_UART_PORT_NUMBER_E port, ql_uart_config_t *dcb);
/***********************************************************************
 *
 * Name:   ql_uart_get_dcbconfig   
 *
 * Description: ��ȡ��Ӧ���ڵ�ǰ��ģʽ
 *
 * Parameters:  port:Ҫ��ȡģʽ�Ĵ���
 *              dcb:�淽ģʽ���ڴ�
 * Returns:     0��send_success
 *              other: faile
 * Notes:
 *
 ***********************************************************************/

int ql_uart_get_dcbconfig(QL_UART_PORT_NUMBER_E port, ql_uart_config_t *dcb);
/***********************************************************************
 *
 * Name:  ql_uart_write  
 *
 * Description: ���ⲿ��������
 *
 * Parameters:  data:Ҫ���͵������׵�ַ
 *              len:Ҫ���͵����ݳ���
 * Returns:     0��send_success
 *              other: faile
 * Notes:
 *
 ***********************************************************************/
int ql_uart_write(QL_UART_PORT_NUMBER_E port, unsigned char *data, int len);
/***********************************************************************
 *
 * Name:   ql_uart_read    
 *
 * Description: ���մ�������
 *
 * Parameters:  data:Ҫ���յ����ݴ��λ���׵�ַ
 *              len:Ҫ���յ����ݳ���
 * Returns:     0��send_success
 *              other: faile
 * Notes:
 *
 ***********************************************************************/
int ql_uart_read(QL_UART_PORT_NUMBER_E port, unsigned char *data, int len);
/***********************************************************************
 *
 * Name:   ql_uart_register_cb    
 *
 * Description: ע����ջص���������
 *
 * Parameters:  port:ע��ص��Ĵ��ں�
 *              uart_cb:�ͻ��ص�����
 * Returns:     
 *              
 * Notes:
 *
 ***********************************************************************/
void ql_uart_register_cb(QL_UART_PORT_NUMBER_E port, uart_callback uart_cb);
/***********************************************************************
 *
 * Name:   ql_uart_register_cb_ex    
 *
 * Description: ע��ص���������
 *
 * Parameters:  port:ע��ص��Ĵ��ں�
 *              uart_cb:�ͻ��ص�����
 *              private ������
 * Returns:     
 *              
 * Notes:
 *
 ***********************************************************************/

void ql_uart_register_cb_ex(QL_UART_PORT_NUMBER_E port, uart_callback_ex uart_cb, void *private);
/***********************************************************************
 *
 * Name:   ql_uart_flush_fifo   
 *
 * Description: ��մ���fifo
 *
 * Parameters:  port:Ҫ��յĴ���fifo�˿ں�
 *              
 * Returns:     none
 *              
 * Notes:
 *
 ***********************************************************************/

void ql_uart_flush_fifo(QL_UART_PORT_NUMBER_E port);

/*****************************************************************
* Function:     ql_uart_is_sending 
* 
* Description:
*               Return the status of the serial port is sending data or not.
*
* Parameters:
*               port:
*               [in]   uart port.
* Return:        
*               FALSE, not sending.
*               TRUE,  is sending.
*****************************************************************/
unsigned char ql_uart_is_sending(QL_UART_PORT_NUMBER_E port);

/*****************************************************************
* Function:     ql_uart_get_rx_data_len
* 
* Description:
*               ����rx��fifo��ʣ�����ֽ�����.
*
* Parameters:
*               port:
*               [in]   uart port.
* Return:        
*               rx fifoʣ���ֽ���.
*               .
*****************************************************************/

unsigned int ql_uart_get_rxrb_data_len(QL_UART_PORT_NUMBER_E port);

#ifdef __cplusplus
	} /*"C" */
#endif

#endif /* _QL_UART_H_ */


