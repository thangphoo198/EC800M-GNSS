/*================================================================
  Copyright (c) 2022, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/
#ifndef _QL_POWER_H_
#define _QL_POWER_H_

#ifdef __cplusplus
	 extern "C" {
#endif
#include "ql_type.h"


#define QL_SLEEP_FLAGS_GROUP_ID         ((unsigned int)0x514C504F)
#define QL_SLEEP_FLAGS_CLEAR_ID         ((unsigned int)0x0)

#define QL_SLEEP_FLAGS_AND_MASK         ((unsigned int)0x2)
#define QL_SLEEP_FLAGS_OR_MASK          ((unsigned int)0x0)

#define QL_SLEEP_FLAGS_GROUP_EMPTY      ((unsigned int)0x0)

#define QL_SLEEP_FLAGS_SUCCESS          ((unsigned int)0x00)
#define QL_SLEEP_FLAGS_ERROR            ((unsigned int)0x01)
#define QL_SLEEP_FLAGS_INVALID          ((unsigned int)0x02)


typedef enum QL_POWERUP_REASON_ENUM
{
	QL_POWERUP_NO_REASON = 0,
	QL_POWERUP_PWRKEY,
	QL_POWERUP_RESET,
	QL_POWERUP_VBAT,
	QL_POWERUP_RTC,
	QL_POWERUP_FAULT,
	QL_POWERUP_VBUS,
}QL_POWERUP_REASON_E;

typedef enum QL_POWERDOWN_REASON_ENUM
{
	QL_POWERDOWN_NO_REASON = 0,
	QL_POWERDOWN_PWRKEY,
	QL_POWERDOWN_VINLDO_HIGH,
	QL_POWERDOWN_VINLDO_LOW,
	QL_POWERDOWN_OVERTEMP,
	QL_POWERDOWN_WDT,
	QL_POWERDOWN_VRTC_LOW,
}QL_POWERDOWN_REASON_E;

typedef enum QL_SW_RESTART_REASON_ENUM
{
	QL_RSTREASON_POWEROFF_CHARGE = 'C', //Charging in "powering off" mode
	QL_RSTREASON_RD_PRODUCTION   = 'R', //Rd production mode
	QL_RSTREASON_RTC_ALARM       = 'A', //rtc Alarm
	QL_RSTREASON_NORMAL_POWERON  = 'N', //Normal powering on
	QL_RSTREASON_ERROR_CONDITION = 'E', //Error reset, eg. watchdog reset triggered by system hang or silent reset
	QL_RSTREASON_ENTER_DOWNLOAD  = 'D', //image Download mode
} QL_SW_RESTART_REASON_E;

typedef void* ql_sleep_flags_ref ;

typedef enum QL_SLEEP_FLAG_ENUM
{
	QL_NOT_ALLOW_SLEEP = 0,
	QL_ALLOW_SLEEP,
}QL_SLEEP_FLAG_E;

/***********************************************************************
 *
 * Name:   ql_sleep_flags_create   
 *
 * Description: ����һ������flag,flag�����32bit��ֻҪ��һ��bitΪ1�Ͳ��������
 *
 * Parameters:  group_ref:���߱�־��ľ��
 *              name_ptr:���߱�־������
 *              
 * Returns:     QL_SLEEP_FLAGS_SUCCESS  �ɹ�
 *              QL_SLEEP_FLAGS_ERROR    ����
 *              QL_SLEEP_FLAGS_INVALID  δ��ʼ��
 * Notes:
 *
 ***********************************************************************/

unsigned int ql_sleep_flags_create(ql_sleep_flags_ref *group_ref , char *name_ptr);
/***********************************************************************
 *
 * Name:   ql_sleep_flags_set  
 *
 * Description: �������߱�־���Ӧbit�����32bit��ֻҪ��һ��bitΪ1�Ͳ��������
 *
 * Parameters:  group_ref:���߱�־��ľ��
 *              flags_to_set:���߱�־���ֵ
 *              set_option��QL_SLEEP_FLAGS_AND_MASK ��������֮ǰ��flagֵ
 *                          QL_SLEEP_FLAGS_OR_MASK  ��������֮ǰflagֵ
 *
 * Returns:     QL_SLEEP_FLAGS_SUCCESS  �ɹ�
 *              QL_SLEEP_FLAGS_ERROR    ����
 *              QL_SLEEP_FLAGS_INVALID  δ��ʼ��
 * Notes:
 *
 ***********************************************************************/
unsigned int ql_sleep_flags_set(ql_sleep_flags_ref group_ref,unsigned int flags_to_set,unsigned int set_option);
/***********************************************************************
 *
 * Name:   ql_sleep_flags_group_delete   
 *
 * Description: ɾ��һ�����߱�־��
 *
 * Parameters:  group_ref:���߱�־��ľ��
 *
 * Returns:     QL_SLEEP_FLAGS_SUCCESS  �ɹ�
 *              QL_SLEEP_FLAGS_ERROR    ����
 *              QL_SLEEP_FLAGS_INVALID  δ��ʼ��
 * Notes:
 *
 ***********************************************************************/
unsigned int ql_sleep_flags_group_delete(ql_sleep_flags_ref group_ref);
/***********************************************************************
 *
 * Name:   ql_get_current_sleep_flags  
 *
 * Description: ��һ�����߱�־�鵱ǰֵ
 *
 * Parameters:  group_ref:���߱�־��ľ��
 *              current_flag_ptr:���ڴ淽���߱�־��ֵ�ı���
 *
 * Returns:     QL_SLEEP_FLAGS_SUCCESS  �ɹ�
 *              QL_SLEEP_FLAGS_ERROR    ����
 *              QL_SLEEP_FLAGS_INVALID  δ��ʼ��
 * Notes:
 *
 ***********************************************************************/
unsigned int ql_get_current_sleep_flags(ql_sleep_flags_ref group_ref,unsigned int *current_flag_ptr);
/***********************************************************************
 *
 * Name:   ql_autosleep_enable    
 *
 * Description: ʹ���Զ�������
 *
 * Parameters:  sleep_flag:ö������
 *
 * Returns:     
 *              
 * Notes:
 *
 ***********************************************************************/
void ql_autosleep_enable(QL_SLEEP_FLAG_E sleep_flag);


/*****************************************************************
* Function:     ql_set_cam_vdd_output 
* 
* Description:	open or close cam avdd
*               
* Parameters:
*               on_off: 
*				[in]
*
*				1: open  	Ĭ�������ѹ2.8V
*				0: close              
*
* Return:       void
*              
*****************************************************************/
void ql_set_cam_vdd_output(unsigned char on_off);


/*****************************************************************
* Function:     ql_power_down 
* 
* Description:	��������ػ���ѡ��ģʽ
*               
* Parameters:
*               normal_flag: 
*				[in]
*
*				1: �����ػ����̣����ȹر���Ƶ����ִ�йػ�  
*				0: ǿ�Ʊ����ػ���ֱ�ӹػ����˷�����Ȼ�ػ����٣��������ǰģ�����ڲ�дflash��
*										ֱ�ӵ�����ܻ�����flash��bitλ��ת���⣬�Ǳ�Ҫ���Ƽ�ʹ�ã�        
*
* Return:       no return
*              
*****************************************************************/
void ql_power_down(unsigned char normal_flag);

/*****************************************************************
* Function:     ql_power_reset 
* 
* Description:	����ģ��(��ȴ��ȹر���Ƶ������)
*               
* Parameters:   no
*
* Return:       no return
*              
*****************************************************************/
void ql_power_reset(void);

/*****************************************************************
* Function:     ql_power_reset 
* 
* Description:	����ģ��(���ر���Ƶֱ�ӱ�������ģ��)
*               
* Parameters:   no
*
* Return:       no return
*              
*****************************************************************/
void ql_power_reset_fast(void);


/*****************************************************************
* Function:     ql_get_powerup_reason 
* 
* Description:	��ȡģ�鿪��ԭ��
*               
* Parameters:   no
*
* Return:       ���ؿ���ԭ�򣬲ο�ö�� QL_POWERUP_REASON_E
*              
*****************************************************************/
int ql_get_powerup_reason(void);

/*****************************************************************
* Function:     ql_get_powerdown_reason 
* 
* Description:	��ȡģ���ϴιػ�ԭ��
*               
* Parameters:   no
*
* Return:       ���ؿ���ԭ�򣬲ο�ö�� QL_POWERDOWN_REASON_E
*              
*****************************************************************/
int ql_get_powerdown_reason(void);

/*****************************************************************
* Function: 	ql_get_battery_vol 
* 
* Description:	��ȡvbat��ѹֵ
*				
* Parameters:	none
*
* Return:		vbat��ѹֵ		
*			   
*****************************************************************/
unsigned short ql_get_battery_vol(void);
int ql_lpm_wakelock_create(char *lock_name, int name_size);
void ql_lpm_wakelock_delete(int wakelock_fd);
int ql_lpm_wakelock_lock(int wakelock_fd);
int ql_lpm_wakelock_unlock(int wakelock_fd);
int ql_lpm_get_wakelock_num(void);
typedef void (*ql_pwrkey_cb)(void);

/*****************************************************************
* Function:     ql_get_pwrkey_status 
* 
* Description:	��ȡpowerkey�����¼�
*               
* Parameters:   no
*
* Return:       1 ��������
*               0 δ����
*****************************************************************/
unsigned char ql_get_pwrkey_status(void);

/*****************************************************************
* Function:     ql_pwrkey_register_irq 
* 
* Description:	ע��powerkey���º�Ļص�
*			ע�⣺�������㶼����������쳣����������
*				  1.��ֹ�ڻص�������ʱ��������������ʽ�ӿڣ���
*				  2.��ֹ����δ��ʼ���Ĵ����飻
*               
* Parameters:   callback:ע��Ļص�����
*
* Return:       
*               
*****************************************************************/
typedef void (*ql_pwrkey_cb)(void);

void ql_pwrkey_register_irq(ql_pwrkey_cb callback);


/*****************************************************************
* Function:     ql_pwrkey_intc_enable 
* 
* Description:	ʹ��powerkey��⹦��
*               
* Parameters:   onoff ��0 ��ʹ�ܣ�1��ʹ��
*
* Return:      
*               
*****************************************************************/
void ql_pwrkey_intc_enable(unsigned char onoff);

/*****************************************************************
* Function:     ql_get_vbus_state 
* 
* Description:	��ȡvbus״̬
*               
* Parameters:   none
*
* Return:      1:vbus��Ч��0��vbus��Ч
*               
*****************************************************************/
unsigned char ql_get_vbus_state(void);

/*****************************************************************
* Function:     ql_create_a_fake_wake_source 
* 
* Description:	��������ģ��������ԭ��
*               
* Parameters:   reason�������õ�����ԭ�򣬲ο�ö�� QL_SW_RESTART_REASON_E
*
* Return:      
*               
*****************************************************************/
void ql_create_a_fake_wake_source(QL_SW_RESTART_REASON_E reason);

/*****************************************************************
* Function:     ql_get_the_fake_wake_source 
* 
* Description:	��ȡ���õ�ģ��������ԭ��
*               
* Parameters:   N
*
* Return:      ��������ԭ��
*               
*****************************************************************/
QL_SW_RESTART_REASON_E ql_get_the_fake_wake_source(void);

/*****************************************************************
* Function:     ql_power_watchdog_reset 
* 
* Description:	�������п��Ź�����
*               
* Parameters:   
*
* Return:      
*               
*****************************************************************/
void ql_power_watchdog_reset(void);


/***********************************************************************
 *
 * Name:   ql_autosleep_enable_ex	
 *
 * Description: ��ǿ�����߽ӿڣ������������¿��Ը����������
 *
 * Parameters:	sleep_flag:����/������ǿ������ģʽ
 *
 *				no_data_time:��������������������ȴ�ʱ�䵥λ�룬��Χ��1~50
 * Returns: 	punish_time���������쳣����ָ���ǿ������ģʽ��ʱ�䵥λ���ӣ���Χ��1~600
 *				
 * Notes:
 *
 ***********************************************************************/
void ql_autosleep_enable_ex(QL_SLEEP_FLAG_E sleep_flag,unsigned short no_data_time,unsigned short punish_time);

/***********************************************************************
 *
 * Name:   ql_powerdown_rtc_in_work   
 *
 * Description: �ػ���,����LDO5�Ĺ���ģʽ��switch to ldo5������RTC���� switch to ldo5x����RTC����
 *
 * Parameters:  flag: 0��switch to ldo5   1��switch to ldo5x
 *
 *             
 * Returns:    0�����óɹ�         ��0������ʧ��
 *              
 * Notes:   switch to ldo5x �ػ�������100uA
 *
 ***********************************************************************/
int ql_powerdown_rtc_in_work(int flag);

#ifdef __cplusplus
	} /*"C" */
#endif

#endif /* _QL_UART_H_ */


