/*================================================================
  Copyright (c) 2022, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/
#include "ql_spi_nor.h"
#include "ql_type.h"
#include "ql_rtos.h"
#include "ql_application.h"
#include <stdio.h>

static void ql_spi_nor_test(void * argv)
{
	unsigned char *id;
	unsigned int tx_buf[1024] = {0};
	unsigned int i;
	int ret = 0;
	
	int port_index = EXTERNAL_NORFLASH_PORT33_36;
	int clk = _APBC_SSP_FNCLKSEL_1_625MHZ_;

	printf("[NORFLASH]===== external norflash driver test \r\n");
	for(i=0; i<1024; i++)
	{
		tx_buf[i] = 0xA5A5A5A5;
	}
	
	ql_spi_nor_init(port_index, clk);	

	id = ql_spi_nor_read_id(port_index);
	printf("[NORFLASH]=====norflash ID:0x%02x 0x%02x 0x%02x\r\n", id[0], id[1], id[2]);
	
	ql_spi_nor_erase_chip(port_index);
	printf("[NORFLASH]=====erase:\r\n");
	
	ret = ql_spi_nor_write(port_index, tx_buf, 0x1000, 4096);
	printf("[NORFLASH]=====write\r\n");
	for(i=0; i<1024; i++)
	{
	
		tx_buf[i] = 0;
	}

	ret = ql_spi_nor_read(port_index, tx_buf, 0x1000, 4096);
	printf("[NORFLASH]=====read\r\n");
	for(i=0; i<1024; i++)
	{
		printf("[NORFLASH]=====read[%d]: 0x%08X \r\n", i, tx_buf[i]);
	}
	
		
}
//application_init(ql_spi_nor_test, "ql_spi_nor_test", 12, 6);

