/*================================================================
  Copyright (c) 2022, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/


#ifndef __QL_SPI_NOR_H
#define __QL_SPI_NOR_H

//spiʱ��Ƶ��
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
 * Description: �ú������ڶ�ȡSPI NOR Flash�豸ID��
 *
 * Parameters:  port: SPI���ߣ��ο�����궨��
 *					EXTERNAL_NORFLASH_PORT16_19��EXTERNAL_NORFLASH_PORT33_36
 *             
 *              
 * Returns:     ����һ������flash ID��ָ�루3���ֽڵĴ�С��
 *             
 * Notes:
 *
 ***********************************************************************/
unsigned char *ql_spi_nor_read_id(int port);

/***********************************************************************
 *
 * Name:   ql_spi_nor_init   
 *
 * Description: �ú������ڳ�ʼ��SPI���ߡ�����SPI NOR Flash����ǰ�������ȵ��øýӿڣ�
 *				������ģ��Ӳ�����ѡ���ʼ����SPI���߼����ʵ�ʱ��Ƶ��
 *
 * Parameters:  port:SPI���ߣ��ο�����궨��
 *					EXTERNAL_NORFLASH_PORT16_19��EXTERNAL_NORFLASH_PORT33_36
 *				clk: ʱ��Ƶ·���ο������궨��ʱ��Ƶ��
 *              
 * Returns:     0  �ɹ�
 *              other    ����
 * Notes:
 *
 ***********************************************************************/
unsigned int  ql_spi_nor_init(int port, int clk);

/***********************************************************************
 *
 * Name:   ql_spi_nor_read   
 *
 * Description: �ú������ڶ�ȡSPI NOR Flashָ����ַ��ָ�����ȵ����ݡ�
 *
 * Parameters:  port: SPI����,ͬ��
 *              pBuffer: ��ȡ�����ݴ洢��ram�еĵ�ַ
 *				ReadAddr����ȡ���ݵ�flash��ʼ��ַ��24λ��
 *				NumByteToRead����Ҫ��ȡ�����ݳ��ȣ���Χ0~65535
 *              
 * Returns:     0  �ɹ�
 *              other    ����
 * Notes:
 *
 ***********************************************************************/
unsigned int  ql_spi_nor_read(int port, unsigned char* pBuffer,unsigned int ReadAddr,unsigned short NumByteToRead);

/***********************************************************************
 *
 * Name:   ql_spi_nor_write   
 *
 * Description: �ú�������д��������SPI NOR Flash����д������ǰ�����ȶԷ������в��������򽫵�������д��ʧ�ܡ���
 *
 * Parameters:  port: SPI����,ͬ��
 *              pBuffer: ram�д�д��flash�����ݵ�ַ
 *				WriteAddr��д��flash����ʼ��ַ��24λ��
 *				NumByteToWrite����д�����ݵĳ��ȣ���Χ0~65535
 *              
 * Returns:     0  �ɹ�
 *              other    ����
 * Notes:
 ***********************************************************************/
unsigned int  ql_spi_nor_write(int port, unsigned char* pBuffer,unsigned int WriteAddr,unsigned short NumByteToWrite);

/***********************************************************************
 *
 * Name:   ql_spi_nor_erase_chip   
 *
 * Description: �ú������ڶ�SPI NOR Flash������Ƭ������
 *
 * Parameters:  port: SPI����,ͬ��
 *              
 * Returns:     0  �ɹ�
 *              other    ����
 * Notes:
 ***********************************************************************/
unsigned int  ql_spi_nor_erase_chip(int port);

/***********************************************************************
 *
 * Name:   ql_spi_nor_erase_sector   
 *
 * Description: �ú������ڲ���SPI NOR Flash��һ����СΪ4 KB������
 *
 * Parameters:  port: SPI����,ͬ��
 *              Dst_Addr:������ַ
 *              
 * Returns:     0  �ɹ�
 *              other    ����
 * Notes:
 ***********************************************************************/
unsigned int  ql_spi_nor_erase_sector(int port, unsigned int Dst_Addr);

/***********************************************************************
 *
 * Name:   ql_spi_nor_reg_write_read   
 *
 * Description: ����ֱ�Ӷ�д,ͬ���ӿ�
 *
 * Parameters:  
 *              
 *              
 * Returns:     0  �ɹ�
 *              other    ����
 * Notes:
 ***********************************************************************/
void ql_spi_nor_reg_write_read(int port, unsigned char *cmd, unsigned char *data, unsigned char len);


#endif
