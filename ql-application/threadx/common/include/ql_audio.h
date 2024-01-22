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
	 unsigned int channels;	//������
	 unsigned int samplerate; //������
	 unsigned int periodcnt; // ��λÿ20ms�ϲ㻺���buff��С, value:2~8
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
  * Description: ����ϵ�y����
  *
  * Parameters:  vol:Ҫ���õ�������С���ο�ö��AUDIOHAL_SPK_LEVEL_T
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
  * Description: ��ȡ��ǰϵ�y����
  *
  * Parameters:  
  * 
  * Returns:	 vol ��ǰ������ֵ
  
  * Notes:
  *
  ***********************************************************************/
 int ql_get_volume(void);

 /***********************************************************************
  *
  * Name:	ql_bind_speakerpa_cb	 
  *
  * Description: ע��receiver�����PA�ص�����ӦӲ��SPK_N\P��
  *
  * Parameters:  cb ����PA�Ļص�������1������Ҫ�򿪣�0λ�ر�
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
  * Description: ������Ƶ�������ͨ��Ϊearphone��ģ���п���earphoneͨ����ǰ���¿��ã�
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
  * Description: ������Ƶ�������ͨ��Ϊreceiver����ӦӲ���ܽ�SPK_N\P
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
  * Description: ������Ƶ�������ͨ��Ϊspeaker��ģ���п���speaker��loudspk��ͨ����ǰ���¿��ã�
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
  * Description: ���š�ֹͣDTMF��
  *
  * Parameters:  tone��Ҫ���ŵ�dtmf��ʽ���ο�ö��AUDIOHAL_TONE_TYPE_T
  *              onoff: 1Ϊ��ʼ���ţ�0Ϊֹͣ����
  * Returns:	0 �ɹ�
  * 			-1 ʧ��
  *
  ***********************************************************************/
 int ql_aud_dtmf_play(AUDIOHAL_TONE_TYPE_T dtmf, int onoff);

  /***********************************************************************
  *
  * Name:	ql_aud_tone_play	 
  *
  * Description: ���š�ֹͣtone��
  *
  * Parameters:  f1/f2: ���ŵ�tone��Ƶ�ʣ�֧�ַ�Χ��50~3500hz��
  *              onoff: 1Ϊ��ʼ���ţ�0Ϊֹͣ����
  * Returns:	0 �ɹ�
  * 			-1 ʧ��
  *
  ***********************************************************************/
 int ql_aud_tone_play(int f1, int f2, int onoff);

  /***********************************************************************
  *
  * Name:	ql_codec_choose	 
  *
  * Description: ѡ��ʹ�����û�����codec
  *
  * Parameters:  codec_choose: �ο�ö��ѡ�����û�����codec
  *              pcm_config: �ò�����������codec��Ч���������pcm�Ļ�������
  * Returns:	
  * 			
  *
  ***********************************************************************/
 void ql_codec_choose(codec_choose_state codec_choose, ql_codecpcm_config* pcm_config);

 /***********************************************************************
  *
  * Name:	ql_set_codecdelay_cnt	 
  *
  * Description: ���ò���������ײ�ر�codec����ʱ��Ϊ��ֹƵ������codec����pop����ƣ�
  *
  * Parameters:  cnt: �ر�codec����ʱ����λ:/20ms��Ĭ��Ϊ4��80ms�����20��400ms
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
  * Description: ��������DTMF/TONE�����������
  *
  * Parameters:  vo: ��Χ0~10
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
  * Description: ���õײ㻺��buff��С����buf�ڲ���ǰ��䣬���Ž���ʱ�Ქ����գ�
  *
  * Parameters:  cnt: �ײ㻺��buff�Ĵ�С����λ��ÿ20ms����Χ0~20��
  *											Ĭ��ֵΪ4��80ms������
  *              
  * Returns:	0���ɹ�
  * 			other ʧ��
  *
  ***********************************************************************/
 int ql_audiohal_setresbufcnt(int cnt);

  /***********************************************************************
  *
  * Name:	ql_set_dsp_gain_table	 
  *
  * Description: ����RX����dsp������ֵ�����ô˽ӿں��ٴ����ö�Ӧ��������Ч��
  *
  * Parameters:  profile_id: ���ų������ο�api�ĵ��н���
  *					gain��	�����õ�����ֵ��һ��12λ�����飬��Ӧ0~11������
  *              
  * Returns:	0���ɹ�
  * 			other ʧ��
  *
  ***********************************************************************/
 int ql_set_dsp_gain_table(unsigned int profile_id, signed short *gain);

 /***********************************************************************
  *
  * Name:	ql_set_txdspgain	 
  *
  * Description: ����TX����dsp������ֵ�����ô˽ӿں��ٴ����ö�Ӧ��������Ч��
  *
  * Parameters:  gain��	�����õ�����ֵ����Χ-36~12
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
  * Description: ��ȡTX����dsp������ֵ
  *
  * Parameters:  
  *              
  * Returns:dsp������ֵ	
  * 			
  *
  ***********************************************************************/
signed char ql_get_txdspgain(void);

 /***********************************************************************
  *
  * Name:	ql_set_txcodecgain	 
  *
  * Description: ����TX����codec������ֵ
  *
  * Parameters:  gain��	�����õ�����ֵ����Χ0~4
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
  * Description: ��ȡTX����codec������ֵ
  *
  * Parameters:  
  *              
  * Returns:dsp������ֵ	
  * 			
  *
  ***********************************************************************/
short ql_get_txcodecgain(void);

 /***********************************************************************
  *
  * Name:	ql_set_txcodec_gain_table	 
  *
  * Description: ����TX����codec������ֵ�����ô˽ӿں��ٴ����ö�Ӧ��������Ч��
  *
  * Parameters:  profile_id: ���ų������ο�api�ĵ��н���
  *				 PGA_Stage1������ѡ��ο�catstudio�ж�Ӧ����
  *				 PGA_Stage2������ѡ��ο�catstudio�ж�Ӧ����
  *			     diggain������ѡ��ο�catstudio�ж�Ӧ����
  *              
  * Returns:	0���ɹ�
  * 			other ʧ��			
  *
  ***********************************************************************/
 int ql_set_txcodec_gain_table(unsigned int profile_id, unsigned int PGA_Stage1, unsigned int PGA_Stage2, unsigned int diggain);

 /***********************************************************************
 *
 * Name:   ql_set_rxcodec_gain_table	
 *
 * Description: �����������codec������gain��ֻ����������棩
 *
 * Parameters:	profile_id: ������Ҫ����ʵ��ʹ�����ã�����ѯ��Զ����֧��
 *				level: ������������
 *				others: �����������������Դ��Զ�ṩ֧��
 * Returns:    
 *			   
 *
 ***********************************************************************/
 int ql_set_rxcodec_gain_table(unsigned int profile_id, signed int level, signed int DAC_DigGain, unsigned int DAC_Gain,  unsigned int RCV_Gain, unsigned int ClassG_Mode, unsigned int ClassD_Gain);

/***********************************************************************
*
* Name:   ql_set_eqcoeff_table	
*
* Description: ����eq��Ƶ����
*
* Parameters:	profile_id: ������Ҫ����ʵ��ʹ�����ã�����ѯ��Զ����֧��
*				tx_rx: ������ѡ��
*				rate: ������
*				data: �����������������Դ��Զ�ṩ֧��
* Returns:    
*			   
*
***********************************************************************/
int ql_set_eqcoeff_table(unsigned int profile_id, signed int tx_rx, unsigned int rate, signed short * data);

 /***********************************************************************
	*
	* Name:   ql_pcm_open	   
	*
	* Description: �򿪲�����pcm����
	*			   
	* Parameters:  config��pcm���ã������������������ʡ������С�ȣ��ο�QL_PCM_CONFIG
	*			   flags����ʼ��Ϊ���Ż���¼����0x4:¼����read��0x8�����ţ�write
	* Returns:	  pcm_handler ��ȡ��pcm�����Ϊ��������ʧ��
	*
  ***********************************************************************/
 PCM_HANDLE_T ql_pcm_open(QL_PCM_CONFIG_T *config, unsigned int flags);

 /***********************************************************************
	*
	* Name:   ql_pcm_read	   
	*
	* Description: ¼��ָ����С��pcm���ݵ�ָ����ַ
	*			   
	* Parameters:  handle��ql_pcm_open��ȡ�ľ��
	*			   data��¼�����ݴ�ŵĵ�ַ
	*			   count��¼��pcm���ݵĴ�С
	* Returns:	¼�Ƶ�pcm���ݴ�С
	*
  ***********************************************************************/
 int ql_pcm_read(PCM_HANDLE_T handle, void *data, unsigned int count);

  /***********************************************************************
	*
	* Name:   ql_pcm_write	   
	*
	* Description: ��ָ����ַ��cpm���ݽ��в���
	*			   
	* Parameters:  handle��ql_pcm_open��ȡ�ľ��
	*			   data�����������ݵĵ�ַ
	*			   count������pcm���ݵĴ�С
	* Returns:	���ŵ�pcm���ݴ�С
	*
  ***********************************************************************/
 int ql_pcm_write(PCM_HANDLE_T handle, void *data, unsigned int count);

 /***********************************************************************
	*
	* Name:   ql_pcm_close	   
	*
	* Description: ע��ql_pcm_open���ò��ر�
	*			   
	* Parameters:  handle��ql_pcm_open��ȡ�ľ��
	*			   
	* Returns:	0 �ɹ�
	*
  ***********************************************************************/
 int ql_pcm_close(PCM_HANDLE_T handle);

 /***********************************************************************
	*
	* Name:   ql_pcm_play_init	   
	*
	* Description: ��ʼ��RX���򣨲��ţ�pcm���á�
	*			   
	* Parameters:  play_cb ����ע��Ļص����������ʱδ�ã�
	*			 
	* Returns:	  0 �ɹ�
	*
  ***********************************************************************/
 int ql_pcm_play_init(cb_on_player play_cb);

 /***********************************************************************
	 *
	 * Name:   ql_pcm_play 	
	 *
	 * Description: ��pcm��������RX���򲥷�
	 *				
	 * Parameters:	hdl ��������ֱ����NULL����
	 *			  buffer�������ŵ�pcm���ݵ�ַ
	 *				size: �����ŵ�pcm���ݴ�С
	 * Returns:   ������ݵ�ʵ�ʳ���
	 *
 ***********************************************************************/
 int ql_pcm_play(int hdl, unsigned char *buffer, int size );

 /***********************************************************************
	 *
	 * Name:   ql_pcm_play_stop 	
	 *
	 * Description: ֹͣ��pcm��������RX���򲥷�
	 *				
	 * Parameters:	hdl ��������ֱ����NULL����
	 *			  
	 * Returns:   0 �ɹ�
	 *
 ***********************************************************************/
 int ql_pcm_play_stop(int hdl);

 /***********************************************************************
	 *
	 * Name:   ql_pcm_play_deinit 	
	 *
	 * Description: ע��ql_pcm_play_init�ӿڵ�����
	 *				
	 * Parameters:	hdl ��������ֱ����NULL����
	 *			  
	 * Returns:   0 �ɹ�
	 *
 ***********************************************************************/
 int ql_pcm_play_deinit(int hdl);

 /***********************************************************************
	 *
	 * Name:   ql_pcm_record_init 	
	 *
	 * Description: ��ʼ��TX����¼����pcm���á�
	 *				
	 * Parameters:	record_cb ��ע��Ļص���
	 *				���лص��ĵ�һ������data����Ϊ¼�Ƶ����ݣ��ڶ���sizeΪ¼�����ݵĳ���
	 *			  
	 * Returns:    0 �ɹ�
	 *
 ***********************************************************************/
 int ql_pcm_record_init(cb_on_record record_cb);

 /***********************************************************************
	  *
	  * Name:	ql_pcm_record_deinit	 
	  *
	  * Description: ע��ql_pcm_record_init�ӿڵ�����
	  * 			 
	  * Parameters:  hdl ��������ֱ����NULL����
	  * 		   
	  * Returns:   0 �ɹ�
	  *
 ***********************************************************************/
 int ql_pcm_record_deinit(int hdl);

 /***********************************************************************
	*
	* Name:   ql_audio_play_init	   
	*
	* Description: ע�Ქ�Żص����ײ�(��Ҫ�ǵײ��ͨ���˻ص�֪ͨ�ϲ㲥��״̬
	*			   ���лص���ֻ��state�����ã��ο�ql_aud_player_state)
	*			   
	* Parameters:  aud_cb���ϲ�ע��Ļص�����
	*			   
	* Returns:	  0 �ɹ�
	*			  other ʧ��
  ***********************************************************************/
 int ql_audio_play_init(cb_on_player aud_cb);

 /***********************************************************************
	*
	* Name:   ql_amr_file_play	   
	*
	* Description: ����amr�ļ������ء�(�˽ӿ�Ϊ�첽�ӿ�)
	*
	* Parameters:  file_name�����ŵ��ļ���
	*			   
	* Returns:	  0 �ɹ�
	*			  other ʧ��
  ***********************************************************************/
 int ql_amr_file_play(const char *file_name);

 /***********************************************************************
  *
  * Name:	ql_amr_file_play2	 
  *
  * Description: ����amr�����������ء�(�˽ӿ�Ϊ�첽�ӿ�)
  *
  * Parameters:  data�����ݵ�ַ
  *				 size: �������ݴ�С
  * Returns:	  0 �ɹ�
  *			      other ʧ��	
  ***********************************************************************/
 int ql_amr_file_play2(const char *data, unsigned int size);

 /***********************************************************************
  *
  * Name:	ql_amr_file_stop	 
  *
  * Description: ֹͣ����amr�ļ�/���ӿڡ�ͬ����amr���Ŷ�Ӧ(�˽ӿ�Ϊ�첽�ӿ�)
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
  * Description: ¼��amr�ļ������ء�(��֧��8K������)
  *
  * Parameters:  file_name�� ��¼�Ƶ��ļ���
  *				
  * Returns:	  0 �ɹ�
  *			      other ʧ��	
  ***********************************************************************/
 int ql_record_amr_file_start(char *file_name);

 /***********************************************************************
  *
  * Name:	ql_record_amr_file_stop	 
  *
  * Description: ֹͣ¼��amr�ļ���
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
  * Description: ��ʼ���н�pcm���ݱ���ɶ�Ӧ��amr����
  *
  * Parameters:  input_buff��Ҫ�����pcm���� ��������320�ֽڣ�Ҳ���ǽ�֧��8K��������
  *				 output_buff������������
  * Returns:	output_size:���ر��������ݴ�С
  *			   
  ***********************************************************************/
 int ql_amrnbenc_do(unsigned char *input_buff, unsigned char *output_buff);

  /***********************************************************************
  *
  * Name:	ql_amrnbenc_init	 
  *
  * Description: ����amr��ʽ����
  *
  * Parameters:  mode �ο�ö��QL_AMRENC_MODE
  *				 format �ο�ö�� QL_AMRENC_FORMAT
  * Returns:	0:�ɹ�
  *			   other ʧ��
  ***********************************************************************/
 int ql_amrnbenc_init(QL_AMRENC_MODE mode, QL_AMRENC_FORMAT format);

 /***********************************************************************
  *
  * Name:	ql_amrnbenc_deinit	 
  *
  * Description: ע��amr��ʽ����
  *
  * Parameters:  
  *				 
  * Returns:	0:�ɹ�
  *			   other ʧ��
  **********************************************************************/
 int ql_amrnbenc_deinit(void);

 /***********************************************************************
  *
  * Name:	ql_mp3_file_play	 
  *
  * Description: ����mp3�ļ������ء�(�˽ӿ�Ϊ�첽�ӿ�)
  *
  * Parameters:  file_name�������ŵ��ļ���
  *				 
  * Returns:	
  * 			
  ***********************************************************************/
 int ql_mp3_file_play(char *file_name);
 
  /***********************************************************************
  *
  * Name:	ql_mp3_file_play2	 
  *
  * Description: ����mp3�����������ء�(�˽ӿ�Ϊ�첽�ӿ�)
  *
  * Parameters:  data�����ݵ�ַ
  *				 size: �������ݴ�С
  * Returns:	
  * 			
  ***********************************************************************/
 int ql_mp3_file_play2(char *data, unsigned int size);

  /***********************************************************************
  *
  * Name:	ql_mp3_file_stop	 
  *
  * Description: ֹͣ����MP3�ļ��ӿڡ�ͬ����MP3���Ŷ�Ӧ(�˽ӿ�Ϊ�첽�ӿ�)
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
   * Description: ����MP3�������������Ǵ�MP3֡������ͷ(�˽ӿ�Ϊͬ���ӿ�)
   *
   * Parameters:  mp3_buff:������MP3�����������ܴ�MP3ͷ������������Ϣ��
   *			  mp3_size:�������ݵĴ�С
   * Returns:	 0 �ɹ�
   *			 
  ***********************************************************************/
 int ql_play_mp3_stream_start(unsigned char *mp3_buff, int mp3_size );

  /***********************************************************************
   *
   * Name:	 ql_play_mp3_stream_stop	  
   *
   * Description: ֹͣ����MP3����������Ӧql_play_mp3_stream_start�ӿ�(�˽ӿ�Ϊͬ���ӿ�)
   *
   * Parameters:  
   *			  
   * Returns:	 0 �ɹ�
   *			 
  ***********************************************************************/
 int ql_play_mp3_stream_stop(void);

 /***********************************************************************
   *
   * Name:	 ql_play_mp3_stream_drain	  
   *
   * Description: ����ql_play_mp3_stream_start�ӿڵ�ʣ�໺�棬ʹ��start�ӿں�
   *				һ��ʹ���߼�ӦΪ��start->drain->stop���������׳��ֶ����������(�˽ӿ�Ϊͬ���ӿ�)
   *
   * Parameters:  
   *			  
   * Returns:	 0 �ɹ�
   *			 
  ***********************************************************************/
 int ql_play_mp3_stream_drain(void);

 /***********************************************************************
	*
	* Name:   ql_wav_file_play	   
	*
	* Description: ����wav�ļ������ء�(�˽ӿ�Ϊ�첽�ӿ�)
	*
	* Parameters:  file_name�����ŵ��ļ���
	*			   
	* Returns:	  0 �ɹ�
	*			  other ʧ��	  		  
  ***********************************************************************/
 int ql_wav_file_play(char *file_name);

 /***********************************************************************
  *
  * Name:	ql_wav_file_play2	 
  *
  * Description: ����wav�����������ء�(�˽ӿ�Ϊ�첽�ӿ�)
  *
  * Parameters:  data�����ݵ�ַ
  *				 size: �������ݴ�С
  * Returns:	
  * 			
  ***********************************************************************/
 int ql_wav_file_play2(char *data, unsigned int size);

  /***********************************************************************
   *
   * Name:	 ql_far_wavf_play	  
   *
   * Description: ����wav�ļ���Զ�ˡ�(�˽ӿ�Ϊ�첽�ӿ�)
   *
   * Parameters:  file_name�����ŵ��ļ���
   *			  
   * Returns:	  0 �ɹ�
   *			  other ʧ��		 
  ***********************************************************************/
 int ql_far_wavf_play(char *file_name);

 /***********************************************************************
  *
  * Name:	ql_far_wavs_play	 
  *
  * Description: ����wav��������Զ�ˡ�(�˽ӿ�Ϊ�첽�ӿ�)
  *
  * Parameters:  data�����ݵ�ַ
  *				 size: �������ݴ�С
  * Returns:	  0 �ɹ�
  *			      other ʧ��			
  ***********************************************************************/
 int ql_far_wavs_play(char *data, unsigned int size);

 /***********************************************************************
  *
  * Name:	ql_wav_file_stop	 
  *
  * Description: ֹͣ����wav�ļ��ӿڡ�ͬ����wav���Ŷ�Ӧ(�˽ӿ�Ϊ�첽�ӿ�)
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
  * Description: ����wav�ļ���liu�ӿڡ�֧��amr/mp3/wav��ʽ���Զ�ʶ��(�˽ӿ�Ϊ�첽�ӿ�)
  *
  * Parameters:  file_name: Ҫ���ŵ��ļ���
  *
  * Returns:	0 �ɹ�
  * 			<0 ʧ��
  *
  ***********************************************************************/
 int ql_audio_file_play(char *file_name);

  /***********************************************************************
  *
  * Name:	ql_audio_file_stop	 
  *
  * Description: ֹͣ�����ļ��ӿڡ�ͬql_audio_file_play��Ӧ(�˽ӿ�Ϊ�첽�ӿ�)
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
  * Description: �����ļ��ӿڡ�֧��amr/mp3/wav��ʽ���Զ�ʶ��(�˽ӿ�Ϊͬ���ӿ�)
  *
  * Parameters:  file_name: Ҫ���ŵ��ļ���
  *
  * Returns:	0 �ɹ�
  * 			<0 ʧ��
  *
  ***********************************************************************/
 int ql_play_file_start(char *file_name);

 /***********************************************************************
  *
  * Name:	ql_play_file_stop	 
  *
  * Description: ֹͣ�����ļ��ӿڡ�ͬql_play_file_start��Ӧ(�˽ӿ�Ϊͬ���ӿ�)
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
  * Description: ����PCM���ݽӿڡ�
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
  * Description: ¼��PCM���ݽӿڡ�
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
  * Description: ֹͣ����PCM���ݽӿڡ�
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
  * Description: ֹͣ¼��PCM���ݽӿڡ�
  *
  * Parameters:  
  *
  * Returns:	
  * 			
  ***********************************************************************/
 void ql_audiohal_recordpcm_stop(void);

#endif
