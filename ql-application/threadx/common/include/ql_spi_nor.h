/*================================================================
  Copyright (c) 2022, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/


#ifndef __QL_SPI_NOR_H
#define __QL_SPI_NOR_H

//spi时钟频率
#define _APBC_SSP_FNCLKSEL_6_5MHZ_	(0x00)
#define _APBC_SSP_FNCLKSEL_13MHZ_	(0x01)
#define _APBC_SSP_FNCLKSEL_26MHZ_	(0x02)
#define _APBC_SSP_FNCLKSEL_52MHZ_	(0x03)
#define _APBC_SSP_FNCLKSEL_3_25MHZ_	(0x04)
#define _APBC_SSP_FNCLKSEL_1_625MHZ_	(0x05)
#define _APBC_SSP_FNCLKSEL_812_5KHZ_	(0x06)

//port
#define EXTERNAL_NORFLASH_PORT16_19        0
#define EXTERNAL_NORFLASH_PORT33_36        2

//SPI_Nor operation ERROR CODE
#define QUEC_SSPOperationNoError				0x0
#define QUEC_SSPPortInvalidError			    0x20
#define QUEC_SSPBufferParamInvalidError		    0x21
#define QUEC_FlashAddrOutOfRange				0x3d
#define QUEC_SSPWaitTxEmptyTimeOutError			0x80
#define QUEC_SSPRdStatusTimeOutError		    0x81
#define QUEC_SSPWelWaitTxEmptyTimeOutError	    0x82
#define QUEC_SSPWaitForWELTimeOutError		    0x83
#define QUEC_SSPWaitCompleteTimeOutError        0x84
#define QUEC_SSPRxChannelTimeOutError           0x85
#define QUEC_SSPTxChannelTimeOutError           0x86
#define QUEC_SSPNOTREADY						0x87

/***********************************************************************
 *
 * Name:   ql_spi_nor_read_id   
 *
 * Description: 该函数用于读取SPI NOR Flash设备ID。
 *
 * Parameters:  port: SPI总线，参考上面宏定义
 *					EXTERNAL_NORFLASH_PORT16_19、EXTERNAL_NORFLASH_PORT33_36
 *             
 *              
 * Returns:     返回一个保存flash ID的指针（3个字节的大小）
 *             
 * Notes:
 *
 ***********************************************************************/
unsigned char *ql_spi_nor_read_id(int port);

/***********************************************************************
 *
 * Name:   ql_spi_nor_init   
 *
 * Description: 该函数用于初始化SPI总线。调试SPI NOR Flash功能前，必须先调用该接口，
 *				并根据模块硬件设计选择初始化的SPI总线及合适的时钟频率
 *
 * Parameters:  port:SPI总线，参考上面宏定义
 *					EXTERNAL_NORFLASH_PORT16_19、EXTERNAL_NORFLASH_PORT33_36
 *				clk: 时钟频路，参考上述宏定义时钟频率
 *              
 * Returns:     0  成功
 *              other    错误
 * Notes:
 *
 ***********************************************************************/
unsigned int  ql_spi_nor_init(int port, int clk);

/***********************************************************************
 *
 * Name:   ql_spi_nor_read   
 *
 * Description: 该函数用于读取SPI NOR Flash指定地址中指定长度的数据。
 *
 * Parameters:  port: SPI总线,同上
 *              pBuffer: 读取的数据存储在ram中的地址
 *				ReadAddr：读取数据的flash起始地址（24位）
 *				NumByteToRead：需要读取的数据长度，范围0~65535
 *              
 * Returns:     0  成功
 *              other    错误
 * Notes:
 *
 ***********************************************************************/
unsigned int  ql_spi_nor_read(int port, unsigned char* pBuffer,unsigned int ReadAddr,unsigned short NumByteToRead);

/***********************************************************************
 *
 * Name:   ql_spi_nor_write   
 *
 * Description: 该函数用于写入数据至SPI NOR Flash。（写入数据前，需先对分区进行擦除，否则将导致数据写入失败。）
 *
 * Parameters:  port: SPI总线,同上
 *              pBuffer: ram中待写入flash的数据地址
 *				WriteAddr：写入flash的起始地址（24位）
 *				NumByteToWrite：待写入数据的长度，范围0~65535
 *              
 * Returns:     0  成功
 *              other    错误
 * Notes:
 ***********************************************************************/
unsigned int  ql_spi_nor_write(int port, unsigned char* pBuffer,unsigned int WriteAddr,unsigned short NumByteToWrite);

/***********************************************************************
 *
 * Name:   ql_spi_nor_erase_chip   
 *
 * Description: 该函数用于对SPI NOR Flash进行整片擦除。
 *
 * Parameters:  port: SPI总线,同上
 *              
 * Returns:     0  成功
 *              other    错误
 * Notes:
 ***********************************************************************/
unsigned int  ql_spi_nor_erase_chip(int port);

/***********************************************************************
 *
 * Name:   ql_spi_nor_erase_sector   
 *
 * Description: 该函数用于擦除SPI NOR Flash中一个大小为4 KB的扇区
 *
 * Parameters:  port: SPI总线,同上
 *              Dst_Addr:扇区地址
 *              
 * Returns:     0  成功
 *              other    错误
 * Notes:
 ***********************************************************************/
unsigned int  ql_spi_nor_erase_sector(int port, unsigned int Dst_Addr);

/***********************************************************************
 *
 * Name:   ql_spi_nor_reg_write_read   
 *
 * Description: 用于直接读写,同步接口
 *
 * Parameters:  
 *              
 *              
 * Returns:     0  成功
 *              other    错误
 * Notes:
 ***********************************************************************/
void ql_spi_nor_reg_write_read(int port, unsigned char *cmd, unsigned char *data, unsigned char len);


#endif
