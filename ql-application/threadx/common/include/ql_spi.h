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
* 		 port	  		[in] 	SPI引脚选择SS0\SS2。 
* 		spimode	  		[in] 	控制器模式：QL_SPI_MODE0,QL_SPI_MODE1,QL_SPI_MODE2,QL_SPI_MODE3,
*		spiclk			[in] 	传输时钟
* Return:
* 	0			成功。
*	-1 			失败。
*****************************************************************/	
int ql_spi_init(SPI_PORT_E port, SPI_MODE_E spimode, SPI_CLK_E spiclk);

/*****************************************************************
* Function: ql_spi_write
* Description:SPI写数据
*
* Parameters:
* 		port	  		[in] 	SPI引脚选择SS0\SS2。 
* 		buf	  			[in] 	存放写入的数据
*		len				[in] 	写数据的长度
* Return:
* 	0			成功。
*	-1 			失败。
*****************************************************************/
int ql_spi_write(SPI_PORT_E port, unsigned char *buf, unsigned int len);

/*****************************************************************
* Function: ql_spi_read
* Description:SPI读数据
*
* Parameters:
* 		port	  		[in] 	SPI引脚选择SS0\SS2。 
* 		buf	  			[in] 	存放读取的数据
*		len				[in] 	读取数据的长度
* Return:
* 	0			成功。
*	-1 			失败。
*****************************************************************/
int ql_spi_read(SPI_PORT_E port, unsigned char *buf, unsigned int len);

/*****************************************************************
* Function: ql_spi_write_read
* Description:SPI数据读写
*
* Parameters:
* 		port	  		[in] 	SPI引脚选择SS0\SS2。 
* 		inbuf	  		[in] 	存放写入的数据
*		outbuf			[in] 	存放读出的数据
*		len				[in] 	读写数据的长度
* Return:
* 	0			成功。
*	-1 			失败。
*****************************************************************/
int ql_spi_write_read(SPI_PORT_E port, unsigned char *inbuf, unsigned char *outbuf, unsigned int len);

/*****************************************************************
* Function: ql_spi_pio_width_write
* Description:SPI写数据，带位宽参数
*
* Parameters:
* 		port	  		[in] 	SPI引脚选择SS0\SS2。 
* 		buf	  			[in] 	存放写入的数据
*		  len				  [in] 	写数据的长度
* 		bit_width	  [in] 	位宽配置，如8bit/9bit
* Return:
* 	0			成功。
*	-1 			失败。
*****************************************************************/
int ql_spi_pio_width_write(SPI_PORT_E port, unsigned int *buf, unsigned int len, int bit_width);

/*****************************************************************
* Function: ql_spi_pio_width_read
* Description:SPI读数据
*
* Parameters:
* 		port	  		[in] 	SPI引脚选择SS0\SS2。 
* 		buf	  			[in] 	存放读取的数据
*		  len				  [in] 	读取数据的长度
* 		bit_width	  [in] 	位宽配置，如8bit/9bit
* Return:
* 	0			成功。
*	-1 			失败。
*****************************************************************/
int ql_spi_pio_width_read(SPI_PORT_E port, unsigned int *buf, unsigned int len, int bit_width);

/*****************************************************************
* Function: ql_spi_pio_width_write_read
* Description:SPI数据读写
*
* Parameters:
* 		port	  		[in] 	SPI引脚选择SS0\SS2。 
* 		inbuf	  		[in] 	存放写入的数据
*		  outbuf			[in] 	存放读出的数据
*		  len				  [in] 	读写数据的长度
* 		bit_width	  [in] 	位宽配置，如8bit/9bit
* Return:
* 	0			成功。
*	-1 			失败。
*****************************************************************/
int ql_spi_pio_width_write_read(SPI_PORT_E port, unsigned int *inbuf, unsigned int *outbuf, unsigned int len, int bit_width);

#ifdef __cplusplus
	} /*"C" */
#endif

#endif /* _QL_UART_H_ */
