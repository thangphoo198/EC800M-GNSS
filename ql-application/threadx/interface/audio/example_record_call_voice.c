/*================================================================
  Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/

#include <stdio.h>
#include <string.h>
#include "ql_fs.h"
#include "ql_application.h"
#include "ql_rtos.h"
#include "ql_func.h"
#include "ql_spi_nor.h"
#include "ql_audio.h"
#include "ql_gpio.h"

#define EXTERNAL_FS      1

#define FILE_RECORD_NAME    "ql_record_file.wav"

#define C_DISK				"C:"
#define C_ROOT_PATH			""C_DISK"/"
#define C_FILE_RECORD_ROOT 	""C_DISK"/"FILE_RECORD_NAME""


#define U_DISK				"U:"
#define U_ROOT_PATH			""U_DISK"/"
#define U_FILE_RECORD_ROOT 	""U_DIR_PATH"/"FILE_RECORD_NAME""




static void record_test(void * argv)
{
	int ret;
	printf("[FS] ========== fs test will start ...\r\n");

	ql_set_audio_path_receiver();
	ql_set_volume(10);
	ql_codec_choose(AUD_INTERNAL_CODEC, NULL);

#if EXTERNAL_FS    //使用外挂flash 配置外挂flash
	int port_index = EXTERNAL_NORFLASH_PORT16_19;
	int clk = _APBC_SSP_FNCLKSEL_26MHZ_;
	
	printf("[FS] ========== exflash init  \r\n");
	ql_spi_nor_init(port_index, clk);	

	ret = qextfs_init('C', "external_fs", 1, port_index, 0, 0x400000);
	printf("[FS] ========== exfs init : %d	\r\n", ret);
	if(!ret)
	{
		printf("[FS] ========== exfs init success  \r\n");
	}
#endif
	ql_remove(C_FILE_RECORD_ROOT);   //删除上次录音文件

	ql_set_record_calldata_init(C_FILE_RECORD_ROOT,1,8000,4);  //配置录音数据写到外挂flash 单声道 8k/16k采样率 tx和rx混合数据   ，，数据从拨电话开始

	ql_rtos_task_sleep_s(60);   //60s后停止录制
	printf("[FS] please hung up the phone!!\r\n");// 挂断电话
	ql_set_record_calldata_stop();
	ql_rtos_task_sleep_s(10);   // 挂断电话
	ql_wav_file_play(C_FILE_RECORD_ROOT);  //播放录制的音频
}
//application_init(record_test, "record_test", 4, 6);
