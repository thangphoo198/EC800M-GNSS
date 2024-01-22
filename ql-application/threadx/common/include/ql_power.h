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
 * Description: 创建一个休眠flag,flag最大是32bit，只要有一个bit为1就不会进休眠
 *
 * Parameters:  group_ref:休眠标志组的句柄
 *              name_ptr:休眠标志组名称
 *              
 * Returns:     QL_SLEEP_FLAGS_SUCCESS  成功
 *              QL_SLEEP_FLAGS_ERROR    错误
 *              QL_SLEEP_FLAGS_INVALID  未初始化
 * Notes:
 *
 ***********************************************************************/

unsigned int ql_sleep_flags_create(ql_sleep_flags_ref *group_ref , char *name_ptr);
/***********************************************************************
 *
 * Name:   ql_sleep_flags_set  
 *
 * Description: 设置休眠标志组对应bit，最大32bit，只要有一个bit为1就不会进休眠
 *
 * Parameters:  group_ref:休眠标志组的句柄
 *              flags_to_set:休眠标志组的值
 *              set_option：QL_SLEEP_FLAGS_AND_MASK 算数与上之前的flag值
 *                          QL_SLEEP_FLAGS_OR_MASK  算数或上之前flag值
 *
 * Returns:     QL_SLEEP_FLAGS_SUCCESS  成功
 *              QL_SLEEP_FLAGS_ERROR    错误
 *              QL_SLEEP_FLAGS_INVALID  未初始化
 * Notes:
 *
 ***********************************************************************/
unsigned int ql_sleep_flags_set(ql_sleep_flags_ref group_ref,unsigned int flags_to_set,unsigned int set_option);
/***********************************************************************
 *
 * Name:   ql_sleep_flags_group_delete   
 *
 * Description: 删除一个休眠标志组
 *
 * Parameters:  group_ref:休眠标志组的句柄
 *
 * Returns:     QL_SLEEP_FLAGS_SUCCESS  成功
 *              QL_SLEEP_FLAGS_ERROR    错误
 *              QL_SLEEP_FLAGS_INVALID  未初始化
 * Notes:
 *
 ***********************************************************************/
unsigned int ql_sleep_flags_group_delete(ql_sleep_flags_ref group_ref);
/***********************************************************************
 *
 * Name:   ql_get_current_sleep_flags  
 *
 * Description: 获一个休眠标志组当前值
 *
 * Parameters:  group_ref:休眠标志组的句柄
 *              current_flag_ptr:用于存方休眠标志组值的变量
 *
 * Returns:     QL_SLEEP_FLAGS_SUCCESS  成功
 *              QL_SLEEP_FLAGS_ERROR    错误
 *              QL_SLEEP_FLAGS_INVALID  未初始化
 * Notes:
 *
 ***********************************************************************/
unsigned int ql_get_current_sleep_flags(ql_sleep_flags_ref group_ref,unsigned int *current_flag_ptr);
/***********************************************************************
 *
 * Name:   ql_autosleep_enable    
 *
 * Description: 使能自动进休眠
 *
 * Parameters:  sleep_flag:枚举类型
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
*				1: open  	默认输出电压2.8V
*				0: close              
*
* Return:       void
*              
*****************************************************************/
void ql_set_cam_vdd_output(unsigned char on_off);


/*****************************************************************
* Function:     ql_power_down 
* 
* Description:	设置软件关机并选择模式
*               
* Parameters:
*               normal_flag: 
*				[in]
*
*				1: 正常关机流程：会先关闭射频，再执行关机  
*				0: 强制暴力关机：直接关机（此方法虽然关机快速，但如果当前模组正在擦写flash，
*										直接掉电可能会引起flash的bit位翻转问题，非必要不推荐使用）        
*
* Return:       no return
*              
*****************************************************************/
void ql_power_down(unsigned char normal_flag);

/*****************************************************************
* Function:     ql_power_reset 
* 
* Description:	重启模组(会等待先关闭射频再重启)
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
* Description:	重启模组(不关闭射频直接暴力重启模组)
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
* Description:	获取模组开机原因
*               
* Parameters:   no
*
* Return:       返回开机原因，参考枚举 QL_POWERUP_REASON_E
*              
*****************************************************************/
int ql_get_powerup_reason(void);

/*****************************************************************
* Function:     ql_get_powerdown_reason 
* 
* Description:	获取模组上次关机原因
*               
* Parameters:   no
*
* Return:       返回开机原因，参考枚举 QL_POWERDOWN_REASON_E
*              
*****************************************************************/
int ql_get_powerdown_reason(void);

/*****************************************************************
* Function: 	ql_get_battery_vol 
* 
* Description:	获取vbat电压值
*				
* Parameters:	none
*
* Return:		vbat电压值		
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
* Description:	获取powerkey按下事件
*               
* Parameters:   no
*
* Return:       1 按键按下
*               0 未按下
*****************************************************************/
unsigned char ql_get_pwrkey_status(void);

/*****************************************************************
* Function:     ql_pwrkey_register_irq 
* 
* Description:	注册powerkey按下后的回调
*			注意：以下两点都会引起程序异常甚至死机：
*				  1.禁止在回调中做耗时操作（调用阻塞式接口）；
*				  2.禁止申请未初始化的大数组；
*               
* Parameters:   callback:注册的回调函数
*
* Return:       
*               
*****************************************************************/
typedef void (*ql_pwrkey_cb)(void);

void ql_pwrkey_register_irq(ql_pwrkey_cb callback);


/*****************************************************************
* Function:     ql_pwrkey_intc_enable 
* 
* Description:	使能powerkey检测功能
*               
* Parameters:   onoff ：0 不使能；1：使能
*
* Return:      
*               
*****************************************************************/
void ql_pwrkey_intc_enable(unsigned char onoff);

/*****************************************************************
* Function:     ql_get_vbus_state 
* 
* Description:	获取vbus状态
*               
* Parameters:   none
*
* Return:      1:vbus有效，0：vbus无效
*               
*****************************************************************/
unsigned char ql_get_vbus_state(void);

/*****************************************************************
* Function:     ql_create_a_fake_wake_source 
* 
* Description:	主动设置模组重启的原因
*               
* Parameters:   reason：可设置的重启原因，参考枚举 QL_SW_RESTART_REASON_E
*
* Return:      
*               
*****************************************************************/
void ql_create_a_fake_wake_source(QL_SW_RESTART_REASON_E reason);

/*****************************************************************
* Function:     ql_get_the_fake_wake_source 
* 
* Description:	获取设置的模组重启的原因
*               
* Parameters:   N
*
* Return:      返回重启原因
*               
*****************************************************************/
QL_SW_RESTART_REASON_E ql_get_the_fake_wake_source(void);

/*****************************************************************
* Function:     ql_power_watchdog_reset 
* 
* Description:	主动进行看门狗重启
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
 * Description: 增强型休眠接口，再数传场景下可以更快进入休眠
 *
 * Parameters:	sleep_flag:禁用/启用增强型休眠模式
 *
 *				no_data_time:数传结束后进入休眠所等待时间单位秒，范围：1~50
 * Returns: 	punish_time：若遇到异常情况恢复增强型休眠模式的时间单位分钟，范围：1~600
 *				
 * Notes:
 *
 ***********************************************************************/
void ql_autosleep_enable_ex(QL_SLEEP_FLAG_E sleep_flag,unsigned short no_data_time,unsigned short punish_time);

/***********************************************************************
 *
 * Name:   ql_powerdown_rtc_in_work   
 *
 * Description: 关机后,设置LDO5的工作模式，switch to ldo5：不给RTC供电 switch to ldo5x：给RTC供电
 *
 * Parameters:  flag: 0：switch to ldo5   1：switch to ldo5x
 *
 *             
 * Returns:    0：设置成功         非0：返回失败
 *              
 * Notes:   switch to ldo5x 关机耗流高100uA
 *
 ***********************************************************************/
int ql_powerdown_rtc_in_work(int flag);

#ifdef __cplusplus
	} /*"C" */
#endif

#endif /* _QL_UART_H_ */


