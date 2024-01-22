/*================================================================
  Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/
/**
 ******************************************************************************
 * @file    example_iic.c
 * @author  Paddy.li
 * @version V1.0.0
 * @date    2019/01/04
 * @brief   This file tests IIC APIs
 ******************************************************************************
 */

#include <stdio.h>
#include "ql_rtos.h"
#include "ql_application.h"
#include "ql_iic.h"


#define I2C_SLAVE_ADDR  0x1B	//codec 5616
#define WHO_AM_I        0x02
#define WHO_AM_I_VALUE  0x12

static void quec_i2c_test(void * argv)
{
	#if 1
	//EC600S:SCL gpio10, SDA gpio11 fun1
	unsigned char i2c_no = 1; //CI2C match to twsi1
	#else
	//EC100Y
	int i2c_no = 0; //CI2C match to twsi0
	#endif
	
	unsigned int iRet=0;
	unsigned int fastmode = 0;
	ql_i2c_init(i2c_no, fastmode);

	unsigned char wrtBuff[2] = {WHO_AM_I_VALUE, 0};
	unsigned char rdBuff[2] = {0, 0};	
	iRet = ql_i2c_write(i2c_no, I2C_SLAVE_ADDR, WHO_AM_I, wrtBuff, 2);
	printf("< write i2c value=0x%x, iRet=%d >\n", WHO_AM_I_VALUE, iRet);
	iRet = ql_i2c_read(i2c_no, I2C_SLAVE_ADDR, WHO_AM_I, rdBuff, 2);
	printf("< read i2c iRet=%d, value=0x%x 0x%x >\n", iRet, rdBuff[1], rdBuff[0]);//Little endian
}

//application_init(quec_i2c_test, "quec_i2c_test", 2, 10);


