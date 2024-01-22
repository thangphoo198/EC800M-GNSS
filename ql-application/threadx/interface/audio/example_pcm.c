/*================================================================
  Copyright (c) 2022, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/


#include "ql_type.h"
#include "ql_func.h"
#include "ql_audio.h"
#include "ql_rtos.h"
#include "ql_application.h"
#include <stdio.h>


#define QL_PCM_BLOCK_FLAG		(0x01)
#define QL_PCM_NONBLOCK_FLAG	(0x02)
#define QL_PCM_READ_FLAG    	(0x04)
#define QL_PCM_WRITE_FLAG		(0x08)

static ql_task_t pcm_stream_test_task_handler = NULL;
static unsigned char tmp_buf[1*1024] = {0};

void pcm_test(void *arg)
{
	int read_ret = -1, write_ret = -1;
	PCM_HANDLE_T read_hdl, write_hdl;
	QL_PCM_CONFIG_T pcm_config = {1, 8000, 0};
	
	//等待audio初始化好
	while(!ql_get_audio_state()){
		ql_rtos_task_sleep_ms(50);
	}
	ql_codec_choose(AUD_INTERNAL_CODEC, NULL);

	printf("pcm_test start ...\r\n");
	
	ql_set_audio_path_receiver();
	ql_set_volume(10);

	read_hdl = ql_pcm_open(&pcm_config, QL_PCM_READ_FLAG|QL_PCM_BLOCK_FLAG);
	if (read_hdl == NULL) {
		printf("ql_pcm_open read fail\n");
		return;
	}
	write_hdl = ql_pcm_open(&pcm_config, QL_PCM_WRITE_FLAG|QL_PCM_BLOCK_FLAG);
	if (write_hdl == NULL) {
		printf("ql_pcm_open write fail\n");
		return;
	}
	while (1) {
			read_ret = ql_pcm_read(read_hdl, tmp_buf, 320);                   //褰曢煶
			printf("ql_pcm_read, pcm read:%d\n", read_ret);
			if (read_ret > 0) {
				write_ret = ql_pcm_write(write_hdl, tmp_buf, read_ret);		  //鎾煶
				printf("ql_pcm_write, pcm write:%d\n", write_ret);
			}		
	}
	ql_pcm_close(read_hdl);
	ql_pcm_close(write_hdl);
}

//application_init(pcm_test, "pcm_test", 2, 2);

