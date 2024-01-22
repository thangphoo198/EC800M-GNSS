/*================================================================
  Copyright (c) 2022, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/

#ifndef _QL_AUDIO_H_
#define _QL_AUDIO_H_


 typedef enum
 {
	 MR475 = 0,/* 4.75 kbps */
	 MR515,    /* 5.15 kbps */
	 MR59,	   /* 5.90 kbps */
	 MR67,	   /* 6.70 kbps */
	 MR74,	   /* 7.40 kbps */
	 MR795,    /* 7.95 kbps */
	 MR102,    /* 10.2 kbps */
	 MR122,    /* 12.2 kbps */
	 MRDTX,    /* DTX		*/
	 N_MODES   /* Not Used	*/
 }QL_AMRENC_MODE;

 typedef enum
 {
	 AMR_TX_WMF = 0,
	 AMR_TX_IF2,
	 AMR_TX_ETS,
 }QL_AMRENC_FORMAT;

 typedef enum
 {
	 AUDIOHAL_DTMF_0 = 0,
	 AUDIOHAL_DTMF_1,
	 AUDIOHAL_DTMF_2,
	 AUDIOHAL_DTMF_3,
	 AUDIOHAL_DTMF_4,
	 AUDIOHAL_DTMF_5,
	 AUDIOHAL_DTMF_6,
	 AUDIOHAL_DTMF_7,
	 AUDIOHAL_DTMF_8,
	 AUDIOHAL_DTMF_9,
	 AUDIOHAL_DTMF_A,
	 AUDIOHAL_DTMF_B,
	 AUDIOHAL_DTMF_C,
	 AUDIOHAL_DTMF_D,
	 AUDIOHAL_DTMF_S,		 //* key
	 AUDIOHAL_DTMF_P,		 //# key
	 AUDIOHAL_COMFORT_425,
	 AUDIOHAL_COMFORT_950,
	 AUDIOHAL_COMFORT_1400,
	 AUDIOHAL_COMFORT_1800,
 } AUDIOHAL_TONE_TYPE_T;

 typedef enum
 {
	 AUDIOHAL_SPK_MUTE		   = 0,
	 AUDIOHAL_SPK_VOL_1,
	 AUDIOHAL_SPK_VOL_2,
	 AUDIOHAL_SPK_VOL_3,
	 AUDIOHAL_SPK_VOL_4,
	 AUDIOHAL_SPK_VOL_5,
	 AUDIOHAL_SPK_VOL_6,
	 AUDIOHAL_SPK_VOL_7,
	 AUDIOHAL_SPK_VOL_8,
	 AUDIOHAL_SPK_VOL_9,
	 AUDIOHAL_SPK_VOL_10,
	 AUDIOHAL_SPK_VOL_11,	 // 11
 
	 AUDIOHAL_SPK_VOL_QTY	 // 12
 } AUDIOHAL_SPK_LEVEL_T;

 typedef enum
 {
	 AUD_INTERNAL_CODEC,
	 AUD_EXTERNAL_CODEC,
 }codec_choose_state;

 typedef enum
 {
	 PCM_FS_32,
	 PCM_FS_64,
	 PCM_FS_128,
	 PCM_FS_256,
	 PCM_FS_512,
	 PCM_FS_1024,
	 PCM_FS_2048,
	 PCM_FS_MAX,
 }ql_pcm_bclk;

 typedef enum
 {
	 PCM_CODEC_SAMPLE_8000 = 8000,
	 PCM_CODEC_SAMPLE_16000 = 16000,
	 PCM_CODEC_SAMPLE_32000 = 32000,
	 PCM_CODEC_SAMPLE_48000 = 48000,
 }ql_pcm_codec_sample;

 typedef enum
 {
	 AUD_PLAYER_ERROR = -1,
	 AUD_PLAYER_START = 0,
	 AUD_PLAYER_PAUSE,
	 AUD_PLAYER_RECOVER,
	 AUD_PLAYER_PLAYING,
	 AUD_PLAYER_NODATA,
	 AUD_PLAYER_LESSDATA,
	 AUD_PLAYER_MOREDATA,
	 AUD_PLAYER_FINISHED,
 }enum_aud_player_state;

 typedef enum
 {
	 AUD_RECORD_ERROR = -1,
	 AUD_RECORD_START = 0,
	 AUD_RECORD_DATA,
	 AUD_RECORD_PAUSE,
	 AUD_RECORD_FINISHED,
 }enum_aud_record_state;

 typedef void	 *PCM_HANDLE_T ;
 typedef struct {
	 unsigned int channels;	//声道数
	 unsigned int samplerate; //采样率
	 unsigned int periodcnt; // 单位每20ms上层缓存的buff大小, value:2~8
 } QL_PCM_CONFIG_T;

 typedef struct ql_codecpcm_config
 {
	 ql_pcm_bclk pcmbclk;
	 ql_pcm_codec_sample sample;
 }ql_codecpcm_config;

 typedef void (*QL_AUDIOHAL_HANDLER_T) (void);
 typedef struct
 {
	 unsigned long* 	 startAddress;
	 unsigned int		 length;
	 unsigned int		 sampleRate;
	 unsigned int		 channelNb;
	 QL_AUDIOHAL_HANDLER_T	halfHandler;
 } QL_AUDIOHALPCM_T;

 typedef void (*cb_on_speakerpa) (unsigned int on);
 
 typedef void(*cb_on_player)(char *p_data, int len, enum_aud_player_state state);
 
 typedef int(*cb_on_record)(char *p_data, int len, enum_aud_record_state state);
 
 int ql_get_audio_state(void);

 /***********************************************************************
  *
  * Name:	ql_set_volume	 
  *
  * Description: 设置系統音量
  *
  * Parameters:  vol:要设置的音量大小，参考枚举AUDIOHAL_SPK_LEVEL_T
  * 
  * Returns:	 no return
  
  * Notes:
  *
  ***********************************************************************/
 void ql_set_volume(AUDIOHAL_SPK_LEVEL_T vol);
 
 /***********************************************************************
  *
  * Name:	ql_get_volume	 
  *
  * Description: 获取当前系統音量
  *
  * Parameters:  
  * 
  * Returns:	 vol 当前的音量值
  
  * Notes:
  *
  ***********************************************************************/
 int ql_get_volume(void);

 /***********************************************************************
  *
  * Name:	ql_bind_speakerpa_cb	 
  *
  * Description: 注册receiver输出的PA回调（对应硬件SPK_N\P）
  *
  * Parameters:  cb 控制PA的回调，返回1代表需要打开，0位关闭
  * 
  * Returns:	
  
  * Notes:
  *
  ***********************************************************************/
 void ql_bind_speakerpa_cb(cb_on_speakerpa cb);

 /***********************************************************************
  *
  * Name:	ql_set_audio_path_earphone	 
  *
  * Description: 设置音频输出输入通道为earphone（模组有开发earphone通道的前提下可用）
  *
  * Parameters:  
  * 
  * Returns:	
  
  * Notes:
  *
  ***********************************************************************/
 void ql_set_audio_path_earphone(void);

 /***********************************************************************
  *
  * Name:	ql_set_audio_path_receiver	 
  *
  * Description: 设置音频输出输入通道为receiver，对应硬件管脚SPK_N\P
  *
  * Parameters:  
  * 
  * Returns:	
  
  * Notes:
  *
  ***********************************************************************/
 void ql_set_audio_path_receiver(void);
 
 /***********************************************************************
  *
  * Name:	ql_set_audio_path_speaker	 
  *
  * Description: 设置音频输出输入通道为speaker（模组有开发speaker（loudspk）通道的前提下可用）
  *
  * Parameters:  
  * 
  * Returns:	
  
  * Notes:
  *
  ***********************************************************************/
 void ql_set_audio_path_speaker(void);

 /***********************************************************************
  *
  * Name:	ql_aud_dtmf_play	 
  *
  * Description: 播放、停止DTMF音
  *
  * Parameters:  tone：要播放的dtmf格式，参考枚举AUDIOHAL_TONE_TYPE_T
  *              onoff: 1为开始播放，0为停止播放
  * Returns:	0 成功
  * 			-1 失败
  *
  ***********************************************************************/
 int ql_aud_dtmf_play(AUDIOHAL_TONE_TYPE_T dtmf, int onoff);

  /***********************************************************************
  *
  * Name:	ql_aud_tone_play	 
  *
  * Description: 播放、停止tone音
  *
  * Parameters:  f1/f2: 播放的tone音频率，支持范围（50~3500hz）
  *              onoff: 1为开始播放，0为停止播放
  * Returns:	0 成功
  * 			-1 失败
  *
  ***********************************************************************/
 int ql_aud_tone_play(int f1, int f2, int onoff);

  /***********************************************************************
  *
  * Name:	ql_codec_choose	 
  *
  * Description: 选择使用内置或外置codec
  *
  * Parameters:  codec_choose: 参考枚举选择内置或外置codec
  *              pcm_config: 该参数仅对外置codec生效，配置输出pcm的基本设置
  * Returns:	
  * 			
  *
  ***********************************************************************/
 void ql_codec_choose(codec_choose_state codec_choose, ql_codecpcm_config* pcm_config);

 /***********************************************************************
  *
  * Name:	ql_set_codecdelay_cnt	 
  *
  * Description: 设置播音结束后底层关闭codec的延时（为防止频繁开关codec产生pop音设计）
  *
  * Parameters:  cnt: 关闭codec的延时，单位:/20ms，默认为4即80ms，最大20即400ms
  *              
  * Returns:	
  * 			
  *
  ***********************************************************************/
 void ql_set_codecdelay_cnt(unsigned int cnt);

  /***********************************************************************
  *
  * Name:	ql_set_dtmf_volume	 
  *
  * Description: 单独设置DTMF/TONE音的输出音量
  *
  * Parameters:  vo: 范围0~10
  *              
  * Returns:	
  * 			
  *
  ***********************************************************************/
 void ql_set_dtmf_volume(int vo);

  /***********************************************************************
  *
  * Name:	ql_audiohal_setresbufcnt	 
  *
  * Description: 设置底层缓存buff大小（此buf在播放前填充，播放结束时会播放清空）
  *
  * Parameters:  cnt: 底层缓存buff的大小，单位：每20ms，范围0~20；
  *											默认值为4即80ms的数据
  *              
  * Returns:	0：成功
  * 			other 失败
  *
  ***********************************************************************/
 int ql_audiohal_setresbufcnt(int cnt);

  /***********************************************************************
  *
  * Name:	ql_set_dsp_gain_table	 
  *
  * Description: 设置RX方向dsp的增益值（设置此接口后再次设置对应音量级生效）
  *
  * Parameters:  profile_id: 播放场景，参考api文档中介绍
  *					gain：	待设置的增益值，一个12位的数组，对应0~11级音量
  *              
  * Returns:	0：成功
  * 			other 失败
  *
  ***********************************************************************/
 int ql_set_dsp_gain_table(unsigned int profile_id, signed short *gain);

 /***********************************************************************
  *
  * Name:	ql_set_txdspgain	 
  *
  * Description: 设置TX方向dsp的增益值（设置此接口后再次设置对应音量级生效）
  *
  * Parameters:  gain：	待设置的增益值，范围-36~12
  *              
  * Returns:	
  * 			
  *
  ***********************************************************************/
 void ql_set_txdspgain(signed char gain);

 /***********************************************************************
  *
  * Name:	ql_get_txdspgain	 
  *
  * Description: 获取TX方向dsp的增益值
  *
  * Parameters:  
  *              
  * Returns:dsp的增益值	
  * 			
  *
  ***********************************************************************/
signed char ql_get_txdspgain(void);

 /***********************************************************************
  *
  * Name:	ql_set_txcodecgain	 
  *
  * Description: 设置TX方向codec的增益值
  *
  * Parameters:  gain：	待设置的增益值，范围0~4
  *              
  * Returns:	
  * 			
  *
  ***********************************************************************/
 void ql_set_txcodecgain(short gain);

 /***********************************************************************
  *
  * Name:	ql_get_txcodecgain	 
  *
  * Description: 获取TX方向codec的增益值
  *
  * Parameters:  
  *              
  * Returns:dsp的增益值	
  * 			
  *
  ***********************************************************************/
short ql_get_txcodecgain(void);

 /***********************************************************************
  *
  * Name:	ql_set_txcodec_gain_table	 
  *
  * Description: 设置TX方向codec的增益值（设置此接口后再次设置对应音量级生效）
  *
  * Parameters:  profile_id: 播放场景，参考api文档中介绍
  *				 PGA_Stage1：增益选项，参考catstudio中对应参数
  *				 PGA_Stage2：增益选项，参考catstudio中对应参数
  *			     diggain：增益选项，参考catstudio中对应参数
  *              
  * Returns:	0：成功
  * 			other 失败			
  *
  ***********************************************************************/
 int ql_set_txcodec_gain_table(unsigned int profile_id, unsigned int PGA_Stage1, unsigned int PGA_Stage2, unsigned int diggain);

 /***********************************************************************
 *
 * Name:   ql_set_rxcodec_gain_table	
 *
 * Description: 设置输出方向codec的增益gain（只针对音量增益）
 *
 * Parameters:	profile_id: 具体需要根据实际使用设置，可咨询移远进行支持
 *				level: 调整的音量级
 *				others: 音量参数，具体可资源移远提供支持
 * Returns:    
 *			   
 *
 ***********************************************************************/
 int ql_set_rxcodec_gain_table(unsigned int profile_id, signed int level, signed int DAC_DigGain, unsigned int DAC_Gain,  unsigned int RCV_Gain, unsigned int ClassG_Mode, unsigned int ClassD_Gain);

/***********************************************************************
*
* Name:   ql_set_eqcoeff_table	
*
* Description: 设置eq音频参数
*
* Parameters:	profile_id: 具体需要根据实际使用设置，可咨询移远进行支持
*				tx_rx: 上下行选择
*				rate: 采样率
*				data: 音量参数，具体可资源移远提供支持
* Returns:    
*			   
*
***********************************************************************/
int ql_set_eqcoeff_table(unsigned int profile_id, signed int tx_rx, unsigned int rate, signed short * data);

 /***********************************************************************
	*
	* Name:   ql_pcm_open	   
	*
	* Description: 打开并配置pcm功能
	*			   
	* Parameters:  config：pcm配置，包括声道数、采样率、缓存大小等，参考QL_PCM_CONFIG
	*			   flags：初始化为播放还是录音，0x4:录音，read；0x8：播放，write
	* Returns:	  pcm_handler 获取的pcm句柄，为空则配置失败
	*
  ***********************************************************************/
 PCM_HANDLE_T ql_pcm_open(QL_PCM_CONFIG_T *config, unsigned int flags);

 /***********************************************************************
	*
	* Name:   ql_pcm_read	   
	*
	* Description: 录制指定大小的pcm数据到指定地址
	*			   
	* Parameters:  handle：ql_pcm_open获取的句柄
	*			   data：录制数据存放的地址
	*			   count：录制pcm数据的大小
	* Returns:	录制的pcm数据大小
	*
  ***********************************************************************/
 int ql_pcm_read(PCM_HANDLE_T handle, void *data, unsigned int count);

  /***********************************************************************
	*
	* Name:   ql_pcm_write	   
	*
	* Description: 将指定地址的cpm数据进行播放
	*			   
	* Parameters:  handle：ql_pcm_open获取的句柄
	*			   data：待播放数据的地址
	*			   count：播放pcm数据的大小
	* Returns:	播放的pcm数据大小
	*
  ***********************************************************************/
 int ql_pcm_write(PCM_HANDLE_T handle, void *data, unsigned int count);

 /***********************************************************************
	*
	* Name:   ql_pcm_close	   
	*
	* Description: 注销ql_pcm_open配置并关闭
	*			   
	* Parameters:  handle：ql_pcm_open获取的句柄
	*			   
	* Returns:	0 成功
	*
  ***********************************************************************/
 int ql_pcm_close(PCM_HANDLE_T handle);

 /***********************************************************************
	*
	* Name:   ql_pcm_play_init	   
	*
	* Description: 初始化RX方向（播放）pcm配置。
	*			   
	* Parameters:  play_cb ：可注册的回调（保留项，暂时未用）
	*			 
	* Returns:	  0 成功
	*
  ***********************************************************************/
 int ql_pcm_play_init(cb_on_player play_cb);

 /***********************************************************************
	 *
	 * Name:   ql_pcm_play 	
	 *
	 * Description: 将pcm数据送往RX方向播放
	 *				
	 * Parameters:	hdl ：保留，直接填NULL即可
	 *			  buffer：待播放的pcm数据地址
	 *				size: 待播放的pcm数据大小
	 * Returns:   填充数据的实际长度
	 *
 ***********************************************************************/
 int ql_pcm_play(int hdl, unsigned char *buffer, int size );

 /***********************************************************************
	 *
	 * Name:   ql_pcm_play_stop 	
	 *
	 * Description: 停止将pcm数据送往RX方向播放
	 *				
	 * Parameters:	hdl ：保留，直接填NULL即可
	 *			  
	 * Returns:   0 成功
	 *
 ***********************************************************************/
 int ql_pcm_play_stop(int hdl);

 /***********************************************************************
	 *
	 * Name:   ql_pcm_play_deinit 	
	 *
	 * Description: 注销ql_pcm_play_init接口的配置
	 *				
	 * Parameters:	hdl ：保留，直接填NULL即可
	 *			  
	 * Returns:   0 成功
	 *
 ***********************************************************************/
 int ql_pcm_play_deinit(int hdl);

 /***********************************************************************
	 *
	 * Name:   ql_pcm_record_init 	
	 *
	 * Description: 初始化TX方向（录音）pcm配置。
	 *				
	 * Parameters:	record_cb ：注册的回调，
	 *				其中回调的第一个参数data返回为录制的数据，第二个size为录制数据的长度
	 *			  
	 * Returns:    0 成功
	 *
 ***********************************************************************/
 int ql_pcm_record_init(cb_on_record record_cb);

 /***********************************************************************
	  *
	  * Name:	ql_pcm_record_deinit	 
	  *
	  * Description: 注销ql_pcm_record_init接口的配置
	  * 			 
	  * Parameters:  hdl ：保留，直接填NULL即可
	  * 		   
	  * Returns:   0 成功
	  *
 ***********************************************************************/
 int ql_pcm_record_deinit(int hdl);

 /***********************************************************************
	*
	* Name:   ql_audio_play_init	   
	*
	* Description: 注册播放回调到底层(主要是底层会通过此回调通知上层播放状态
	*			   其中回调中只有state有作用，参考ql_aud_player_state)
	*			   
	* Parameters:  aud_cb：上层注册的回调函数
	*			   
	* Returns:	  0 成功
	*			  other 失败
  ***********************************************************************/
 int ql_audio_play_init(cb_on_player aud_cb);

 /***********************************************************************
	*
	* Name:   ql_amr_file_play	   
	*
	* Description: 播放amr文件到本地。(此接口为异步接口)
	*
	* Parameters:  file_name：播放的文件名
	*			   
	* Returns:	  0 成功
	*			  other 失败
  ***********************************************************************/
 int ql_amr_file_play(const char *file_name);

 /***********************************************************************
  *
  * Name:	ql_amr_file_play2	 
  *
  * Description: 播放amr数据流到本地。(此接口为异步接口)
  *
  * Parameters:  data：数据地址
  *				 size: 播放数据大小
  * Returns:	  0 成功
  *			      other 失败	
  ***********************************************************************/
 int ql_amr_file_play2(const char *data, unsigned int size);

 /***********************************************************************
  *
  * Name:	ql_amr_file_stop	 
  *
  * Description: 停止播放amr文件/流接口。同上述amr播放对应(此接口为异步接口)
  *
  * Parameters:  
  *
  * Returns:	
  * 			
  ***********************************************************************/
 void ql_amr_file_stop(void);
 
 /***********************************************************************
  *
  * Name:	ql_record_amr_file_start	 
  *
  * Description: 录制amr文件到本地。(仅支持8K单声道)
  *
  * Parameters:  file_name： 待录制的文件名
  *				
  * Returns:	  0 成功
  *			      other 失败	
  ***********************************************************************/
 int ql_record_amr_file_start(char *file_name);

 /***********************************************************************
  *
  * Name:	ql_record_amr_file_stop	 
  *
  * Description: 停止录制amr文件。
  *
  * Parameters:  
  *				
  * Returns:	
  *			   
  ***********************************************************************/
 void ql_record_amr_file_stop(void);

  /***********************************************************************
  *
  * Name:	ql_amrnbenc_do	 
  *
  * Description: 开始进行将pcm数据编码成对应的amr数据
  *
  * Parameters:  input_buff：要编码的pcm数据 （必须是320字节，也就是仅支持8K单声道）
  *				 output_buff：编码后的数据
  * Returns:	output_size:返回编码后的数据大小
  *			   
  ***********************************************************************/
 int ql_amrnbenc_do(unsigned char *input_buff, unsigned char *output_buff);

  /***********************************************************************
  *
  * Name:	ql_amrnbenc_init	 
  *
  * Description: 配置amr格式编码
  *
  * Parameters:  mode 参考枚举QL_AMRENC_MODE
  *				 format 参考枚举 QL_AMRENC_FORMAT
  * Returns:	0:成功
  *			   other 失败
  ***********************************************************************/
 int ql_amrnbenc_init(QL_AMRENC_MODE mode, QL_AMRENC_FORMAT format);

 /***********************************************************************
  *
  * Name:	ql_amrnbenc_deinit	 
  *
  * Description: 注销amr格式编码
  *
  * Parameters:  
  *				 
  * Returns:	0:成功
  *			   other 失败
  **********************************************************************/
 int ql_amrnbenc_deinit(void);

 /***********************************************************************
  *
  * Name:	ql_mp3_file_play	 
  *
  * Description: 播放mp3文件到本地。(此接口为异步接口)
  *
  * Parameters:  file_name：待播放的文件名
  *				 
  * Returns:	
  * 			
  ***********************************************************************/
 int ql_mp3_file_play(char *file_name);
 
  /***********************************************************************
  *
  * Name:	ql_mp3_file_play2	 
  *
  * Description: 播放mp3数据流到本地。(此接口为异步接口)
  *
  * Parameters:  data：数据地址
  *				 size: 播放数据大小
  * Returns:	
  * 			
  ***********************************************************************/
 int ql_mp3_file_play2(char *data, unsigned int size);

  /***********************************************************************
  *
  * Name:	ql_mp3_file_stop	 
  *
  * Description: 停止播放MP3文件接口。同上述MP3播放对应(此接口为异步接口)
  *
  * Parameters:  
  *
  * Returns:	
  * 			
  ***********************************************************************/
 void ql_mp3_file_stop(void);

 /***********************************************************************
   *
   * Name:	 ql_play_mp3_stream_start	  
   *
   * Description: 播放MP3数据流，必须是纯MP3帧，不带头(此接口为同步接口)
   *
   * Parameters:  mp3_buff:待播的MP3数据流（不能带MP3头或其他附加信息）
   *			  mp3_size:待播数据的大小
   * Returns:	 0 成功
   *			 
  ***********************************************************************/
 int ql_play_mp3_stream_start(unsigned char *mp3_buff, int mp3_size );

  /***********************************************************************
   *
   * Name:	 ql_play_mp3_stream_stop	  
   *
   * Description: 停止播放MP3数据流，对应ql_play_mp3_stream_start接口(此接口为同步接口)
   *
   * Parameters:  
   *			  
   * Returns:	 0 成功
   *			 
  ***********************************************************************/
 int ql_play_mp3_stream_stop(void);

 /***********************************************************************
   *
   * Name:	 ql_play_mp3_stream_drain	  
   *
   * Description: 播放ql_play_mp3_stream_start接口的剩余缓存，使用start接口后
   *				一般使用逻辑应为：start->drain->stop，否则容易出现丢后面的数据(此接口为同步接口)
   *
   * Parameters:  
   *			  
   * Returns:	 0 成功
   *			 
  ***********************************************************************/
 int ql_play_mp3_stream_drain(void);

 /***********************************************************************
	*
	* Name:   ql_wav_file_play	   
	*
	* Description: 播放wav文件到本地。(此接口为异步接口)
	*
	* Parameters:  file_name：播放的文件名
	*			   
	* Returns:	  0 成功
	*			  other 失败	  		  
  ***********************************************************************/
 int ql_wav_file_play(char *file_name);

 /***********************************************************************
  *
  * Name:	ql_wav_file_play2	 
  *
  * Description: 播放wav数据流到本地。(此接口为异步接口)
  *
  * Parameters:  data：数据地址
  *				 size: 播放数据大小
  * Returns:	
  * 			
  ***********************************************************************/
 int ql_wav_file_play2(char *data, unsigned int size);

  /***********************************************************************
   *
   * Name:	 ql_far_wavf_play	  
   *
   * Description: 播放wav文件到远端。(此接口为异步接口)
   *
   * Parameters:  file_name：播放的文件名
   *			  
   * Returns:	  0 成功
   *			  other 失败		 
  ***********************************************************************/
 int ql_far_wavf_play(char *file_name);

 /***********************************************************************
  *
  * Name:	ql_far_wavs_play	 
  *
  * Description: 播放wav数据流到远端。(此接口为异步接口)
  *
  * Parameters:  data：数据地址
  *				 size: 播放数据大小
  * Returns:	  0 成功
  *			      other 失败			
  ***********************************************************************/
 int ql_far_wavs_play(char *data, unsigned int size);

 /***********************************************************************
  *
  * Name:	ql_wav_file_stop	 
  *
  * Description: 停止播放wav文件接口。同上述wav播放对应(此接口为异步接口)
  *
  * Parameters:  
  *
  * Returns:	
  * 			
  ***********************************************************************/
 void ql_wav_file_stop(void);

 /***********************************************************************
  *
  * Name:	ql_audio_file_play	 
  *
  * Description: 播放wav文件、liu接口。支持amr/mp3/wav格式，自动识别(此接口为异步接口)
  *
  * Parameters:  file_name: 要播放的文件名
  *
  * Returns:	0 成功
  * 			<0 失败
  *
  ***********************************************************************/
 int ql_audio_file_play(char *file_name);

  /***********************************************************************
  *
  * Name:	ql_audio_file_stop	 
  *
  * Description: 停止播放文件接口。同ql_audio_file_play对应(此接口为异步接口)
  *
  * Parameters:  
  *
  * Returns:	
  * 			
  ***********************************************************************/
 void ql_audio_file_stop(void);

  /***********************************************************************
  *
  * Name:	ql_play_file_start	 
  *
  * Description: 播放文件接口。支持amr/mp3/wav格式，自动识别(此接口为同步接口)
  *
  * Parameters:  file_name: 要播放的文件名
  *
  * Returns:	0 成功
  * 			<0 失败
  *
  ***********************************************************************/
 int ql_play_file_start(char *file_name);

 /***********************************************************************
  *
  * Name:	ql_play_file_stop	 
  *
  * Description: 停止播放文件接口。同ql_play_file_start对应(此接口为同步接口)
  *
  * Parameters:  
  *
  * Returns:	
  * 			
  ***********************************************************************/
 int ql_play_file_stop(void);
 
 /***********************************************************************
  *
  * Name:	ql_audiohal_playpcm	 
  *
  * Description: 播放PCM数据接口。
  *
  * Parameters:  
  *
  * Returns:	
  * 			
  ***********************************************************************/
 int ql_audiohal_playpcm(QL_AUDIOHALPCM_T *playpcm);

 /***********************************************************************
  *
  * Name:	ql_audiohal_recordpcm	 
  *
  * Description: 录制PCM数据接口。
  *
  * Parameters:  
  *
  * Returns:	
  * 			
  ***********************************************************************/
 int ql_audiohal_recordpcm(QL_AUDIOHALPCM_T *recordpcm);
  
 /***********************************************************************
  *
  * Name:	ql_audiohal_playpcm_stop	 
  *
  * Description: 停止播放PCM数据接口。
  *
  * Parameters:  
  *
  * Returns:	
  * 			
  ***********************************************************************/
 void ql_audiohal_playpcm_stop(void);

 /***********************************************************************
  *
  * Name:	ql_audiohal_recordpcm_stop	 
  *
  * Description: 停止录制PCM数据接口。
  *
  * Parameters:  
  *
  * Returns:	
  * 			
  ***********************************************************************/
 void ql_audiohal_recordpcm_stop(void);

#endif
