/*================================================================
  Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/



#ifndef _QL_RTC_H_
#define _QL_RTC_H_
	 
#ifdef __cplusplus
	 extern "C" {
#endif

typedef struct ql_rtc_time_struct {
	int tm_sec;	 //seconds [0,59]
	int tm_min;	 //minutes [0,59]
	int tm_hour;  //hour [0,23]
	int tm_mday;  //day of month [1,31]
	int tm_mon;	 //month of year [1,12]
	int tm_year; // since 1970
	int tm_wday; // sunday = 0
}ql_rtc_time_t;

typedef void (*ql_rtc_cb)(void);


/****************************************************************************
 * Function: ql_rtc_set_time
 * Description: RTC����ʱ��ӿ�
 
 * Parameters::
 	��IN�� tm:�������õ�ʱ��
 * Return:
 	0	��ʾ�ɹ�
 	-1  ��ʾʧ��
******************************************************************************/
int ql_rtc_set_time(ql_rtc_time_t *tm);

/****************************************************************************
 * Function: ql_rtc_get_time
 * Description: ��ȡRTC��ǰʱ��,��ע���ڿ���ģ��ע����NITZ�Ὣʱ��ͬ����RTC
 
 * Parameters::
 	��IN�� tm:��Ż�ȡ��ʱ��
 * Return:
 	0	��ʾ�ɹ�
 	-1  ��ʾʧ��
******************************************************************************/
int ql_rtc_get_time(ql_rtc_time_t *tm);

 /****************************************************************************
  * Function: ql_rtc_set_alarm
  * Description: ����RTC����ʱ��
  
  * Parameters::
	 ��IN�� tm:�������õ�RTC����ʱ��
  * Return:
	 0	 ��ʾ�ɹ�
	 -1  ��ʾʧ��
 ******************************************************************************/
 int ql_rtc_set_alarm(ql_rtc_time_t *tm);

 /****************************************************************************
 * Function: ql_rtc_get_alarm
 * Description: ��ȡRTC���õ�����ʱ��
 
 * Parameters::
 	��IN�� tm:���RTC���õ�����ʱ��
 * Return:
 	0	��ʾ�ɹ�
 	-1  ��ʾʧ��
******************************************************************************/
 int ql_rtc_get_alarm(ql_rtc_time_t *tm);
 
 /****************************************************************************
 * Function: ql_rtc_enable_alarm
 * Description: ʹ��RTC ����
 
 * Parameters::
	on_off		��1���� �� 0����
 * Return:
 	��
******************************************************************************/
 void ql_rtc_enable_alarm(unsigned char on_off);

 /****************************************************************************
 * Function: ql_rtc_register_cb
 * Description: RTCע��ص��ӿڣ�������RTC����ʱע��ص���ע�ⲻҪ�ڻص����������бȽϺ�ʱ�Ĵ�����ߺ���
 
 * Parameters::
	cb ��ע��ص��ӿڵ�ַ
 * Return:
 	��
******************************************************************************/
 void ql_rtc_register_cb(ql_rtc_cb cb);
 
 /**
  * Name: ql_rtos_get_tsticks
  * Description: Number of ts ticks that passed since last reset.
  * Para: None
  * Returns: u32 Number of ts ticks that passed since last reset.
  * Note: Increase by 1 per 1/32K s
  **/
 unsigned int ql_rtc_get_ticks(void);
 unsigned long long ql_rtc_get_ticks_uint64(void);
int ql_rtc_get_time_ex(ql_rtc_time_t *tm);

#ifdef __cplusplus
	 } /*"C" */
#endif
 
#endif /* _QL_RTC_H_ */


