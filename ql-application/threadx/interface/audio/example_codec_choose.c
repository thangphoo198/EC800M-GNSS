/*================================================================
  Copyright (c) 2022, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/
#include <stdio.h>
#include "ql_rtos.h"
#include "ql_application.h"
#include "ql_audio.h"
#include "ql_tts.h"
#include "ql_iic.h"


static int rt5616_init_reg[] = {
	0x08080002,	//0002 is the addr, 0808 is the value
	0x08080003,
	0x80000005,
	0x04C0000D,
	0x0808000F,
	0xAFAF0019,
	0x5C5C001C,
	0x0000001E,
	0x38200027,
	0x80800029,
	0x1250002A,
	0x0000003B,
	0x004F003C,
	0x2000003D,
	0x004F003E,
	0x40000045,
	0x0000004D,
	0x0000004E,
	0x0278004F,
	0x00000050,
	0x00000051,
	0x02780052,
	0xC8000053,
	0x98060061,
	0x88000062,
	0xF8FE0063,
	0x0A000064,
	0xCC000065,
	0x3F000066,
	0x003D006A,
	0x3600006C,
	0x80820070,
	0x00000073,
	0x0C000074,
	0x50000080,
	0x0E1C0081,
	0x08000082,
	0x0019008E,
	0x3100008F,
	0x2C000093,
	0x02000094,
	0x208000B0,
	0x000000B1,
	0x001100FA,
};
#define RT5616_INIT_REG_LEN sizeof(rt5616_init_reg)/sizeof(rt5616_init_reg[0])
#define CODEC_IIC_NO 1	//EC600M iic_no 1/EC800M iic_no 0
#define I2C_SLAVE_ADDR  0x1B	//codec 5616

static short ql_rt5616_read_reg(unsigned char RegAddr, unsigned short *p_value)
{
	unsigned short status = 1;
	unsigned char temp_buf[2];
	unsigned char retry_count = 5;

	do 
    {
        status = ql_i2c_read(CODEC_IIC_NO, I2C_SLAVE_ADDR, RegAddr, temp_buf, 2);
		if (status != 0)
		{
            printf("Error:rt5616 [%dth] device[0x%x] addr[0x%x] failed\n", retry_count, I2C_SLAVE_ADDR, RegAddr);
        }	
		else
        {
			*p_value = (((unsigned short)temp_buf[0]) << 8) | temp_buf[1];
			break;
		}
	} while (--retry_count);

	return status;
}

static short ql_rt5616_write_reg(unsigned char RegAddr, unsigned short RegData)
{
    unsigned short status = 1;
    unsigned char param_data[3] = {0x00};
    unsigned char retry_count = 5;

    param_data[0] = (unsigned char)((RegData >> 8) & 0xFF);
    param_data[1] = (unsigned char)(RegData & 0xff);

    do 
    {
        status = ql_i2c_write(CODEC_IIC_NO, I2C_SLAVE_ADDR, RegAddr, param_data, 2);
        if (status != 0)
        {
            printf("Error:[%dth] device[0x%x] addr[0x%x] failed\n", retry_count, I2C_SLAVE_ADDR, RegAddr);
        }        
        else 
        {
            break;
        }
    } while (--retry_count);

    return status;
}

static void ql_rt5616_init(void)
{
	char i = 0;
	
	for (i = 0; i < RT5616_INIT_REG_LEN; i++)
	{
		ql_rt5616_write_reg(rt5616_init_reg[i]&0xFFFF, rt5616_init_reg[i]>>16);
	}
}

static void ql_rt5616_open(void)		//初始化5616型号codec
{
	unsigned short status = 0;
	unsigned short  val = 0;
	ql_i2c_init(CODEC_IIC_NO, 0);		//不同项目的使用的IIC_NO有区别，硬件上也不相同，请根据具体项目更改
	status = ql_rt5616_read_reg(0xFE, &val);
	if ((status == 0) && (0x10EC == val)) 
	{
		ql_rt5616_init();
		printf("quec_rt5616_init!!!\n");
	}

}
static void ql_rt5616_close(void)		//给5616款codec下电
{
	static unsigned int reg_5616_power[] = {0x00000061, 0x00000062, 0x00000063, 0x00000064, 0x00000065, 0x00000066};
	char i = 0;
	
	for (i = 0; i < sizeof(reg_5616_power)/sizeof(reg_5616_power[0]); i++)
	{
		ql_rt5616_write_reg(reg_5616_power[i]&0xFFFF, reg_5616_power[i]>>16);
	}
}


static void quec_codec_test(void * argv)
{
	while(!ql_get_audio_state()){
		ql_rtos_task_sleep_ms(50);
	}
	
	printf("quec_codec_test start ...\r\n");
	
	int i = 0;
	ql_codecpcm_config pcm_config[] = {PCM_FS_256,PCM_CODEC_SAMPLE_16000};
	ql_set_audio_path_receiver();
	ql_set_volume(11);
	
	ql_codec_choose(AUD_EXTERNAL_CODEC, &pcm_config);	//模块内部配置后向外置codec输出pcm数据
	ql_rt5616_open();									//初始化外置codec
	printf("choose external codec play audio ...\r\n");
	ql_tts_init(NULL);
	for(i = 0; i < 10; i++){
		ql_tts_play(2,"quectel,123456");
		ql_rtos_task_sleep_s(5); 
		ql_tts_play(1,"6B228FCE4F7F752879FB8FDC6A215757");
		ql_rtos_task_sleep_s(5);
	}
	ql_rt5616_close();									//关闭外置codec
	printf("external codec test end, close...\r\n");

	ql_codec_choose(AUD_INTERNAL_CODEC, NULL);			//切回内置codec播放audio
	printf("choose internal codec play audio ...\r\n");
	while(1)
	{			
		ql_tts_play(2,"quectel,123欢迎使用移远模块");
		ql_rtos_task_sleep_s(5); 
		ql_tts_play(1,"6B228FCE4F7F752879FB8FDC6A215757");
		ql_rtos_task_sleep_s(5);
	}
}

//application_init(quec_codec_test, "quec_codec_test", 3, 0);

