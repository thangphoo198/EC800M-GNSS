/*================================================================
  Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/

#ifndef _QL_SPI_H_
#define _QL_SPI_H_
	 
#ifdef __cplusplus
	 extern "C" {
#endif


typedef enum SPI_CLK_ENUM
{	
	SPI_CLK_INVALID=-1,
	SPI_CLK_100KHZ=0,
	SPI_CLK_200KHZ,
	SPI_CLK_300KHZ,
	SPI_CLK_400KHZ,
	SPI_CLK_500KHZ,
	SPI_CLK_600KHZ,
	SPI_CLK_700KHZ,
	SPI_CLK_812_5KHZ,
	SPI_CLK_1_625MHZ,
	SPI_CLK_3_25MHZ,
	SPI_CLK_6_5MHZ,
	SPI_CLK_13MHZ,
	SPI_CLK_26MHZ,
	SPI_CLK_52MHZ,
	SPI_CLK_MAX,
}SPI_CLK_E;

typedef enum SPI_MODE_ENUM
{	
	SPI_MODE_INVALID=-1,
	SPI_MODE0=0,
	SPI_MODE1,
	SPI_MODE2,
	SPI_MODE3,
	SPI_MODE_MAX,
}SPI_MODE_E;

typedef enum SPI_PORT_ENUM
{
	SPI_PORT_INVALID = -1,
	SPI_PORT0 = 0,	//GPIO16-GPIO19
	SPI_PORT1 = 1,	//GPIO33-GPIO36
	SPI_PORT_MAX,
}SPI_PORT_E;

/*****************************************************************
* Function: ql_spi_init
* Description: SPI_INIT
*
* Parameters:
* 		 port	  		[in] 	SPI����ѡ��SS0\SS2�� 
* 		spimode	  		[in] 	������ģʽ��QL_SPI_MODE0,QL_SPI_MODE1,QL_SPI_MODE2,QL_SPI_MODE3,
*		spiclk			[in] 	����ʱ��
* Return:
* 	0			�ɹ���
*	-1 			ʧ�ܡ�
*****************************************************************/	
int ql_spi_init(SPI_PORT_E port, SPI_MODE_E spimode, SPI_CLK_E spiclk);

/*****************************************************************
* Function: ql_spi_write
* Description:SPIд����
*
* Parameters:
* 		port	  		[in] 	SPI����ѡ��SS0\SS2�� 
* 		buf	  			[in] 	���д�������
*		len				[in] 	д���ݵĳ���
* Return:
* 	0			�ɹ���
*	-1 			ʧ�ܡ�
*****************************************************************/
int ql_spi_write(SPI_PORT_E port, unsigned char *buf, unsigned int len);

/*****************************************************************
* Function: ql_spi_read
* Description:SPI������
*
* Parameters:
* 		port	  		[in] 	SPI����ѡ��SS0\SS2�� 
* 		buf	  			[in] 	��Ŷ�ȡ������
*		len				[in] 	��ȡ���ݵĳ���
* Return:
* 	0			�ɹ���
*	-1 			ʧ�ܡ�
*****************************************************************/
int ql_spi_read(SPI_PORT_E port, unsigned char *buf, unsigned int len);

/*****************************************************************
* Function: ql_spi_write_read
* Description:SPI���ݶ�д
*
* Parameters:
* 		port	  		[in] 	SPI����ѡ��SS0\SS2�� 
* 		inbuf	  		[in] 	���д�������
*		outbuf			[in] 	��Ŷ���������
*		len				[in] 	��д���ݵĳ���
* Return:
* 	0			�ɹ���
*	-1 			ʧ�ܡ�
*****************************************************************/
int ql_spi_write_read(SPI_PORT_E port, unsigned char *inbuf, unsigned char *outbuf, unsigned int len);

/*****************************************************************
* Function: ql_spi_pio_width_write
* Description:SPIд���ݣ���λ�����
*
* Parameters:
* 		port	  		[in] 	SPI����ѡ��SS0\SS2�� 
* 		buf	  			[in] 	���д�������
*		  len				  [in] 	д���ݵĳ���
* 		bit_width	  [in] 	λ�����ã���8bit/9bit
* Return:
* 	0			�ɹ���
*	-1 			ʧ�ܡ�
*****************************************************************/
int ql_spi_pio_width_write(SPI_PORT_E port, unsigned int *buf, unsigned int len, int bit_width);

/*****************************************************************
* Function: ql_spi_pio_width_read
* Description:SPI������
*
* Parameters:
* 		port	  		[in] 	SPI����ѡ��SS0\SS2�� 
* 		buf	  			[in] 	��Ŷ�ȡ������
*		  len				  [in] 	��ȡ���ݵĳ���
* 		bit_width	  [in] 	λ�����ã���8bit/9bit
* Return:
* 	0			�ɹ���
*	-1 			ʧ�ܡ�
*****************************************************************/
int ql_spi_pio_width_read(SPI_PORT_E port, unsigned int *buf, unsigned int len, int bit_width);

/*****************************************************************
* Function: ql_spi_pio_width_write_read
* Description:SPI���ݶ�д
*
* Parameters:
* 		port	  		[in] 	SPI����ѡ��SS0\SS2�� 
* 		inbuf	  		[in] 	���д�������
*		  outbuf			[in] 	��Ŷ���������
*		  len				  [in] 	��д���ݵĳ���
* 		bit_width	  [in] 	λ�����ã���8bit/9bit
* Return:
* 	0			�ɹ���
*	-1 			ʧ�ܡ�
*****************************************************************/
int ql_spi_pio_width_write_read(SPI_PORT_E port, unsigned int *inbuf, unsigned int *outbuf, unsigned int len, int bit_width);

#ifdef __cplusplus
	} /*"C" */
#endif

#endif /* _QL_UART_H_ */
