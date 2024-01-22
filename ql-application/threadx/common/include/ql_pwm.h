/*================================================================
  Copyright (c) 2022, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/


#ifndef _QL_PWM_H
#define _QL_PWM_H


#ifdef __cplusplus
extern "C" {
#endif


typedef enum QL_PWM_CYCLE_RANGE_ENUM
{
    QL_PWM_CYCLE_ABOVE_1US,
	QL_PWM_CYCLE_ABOVE_10US,
    QL_PWM_CYCLE_ABOVE_1MS
} QL_PWM_CYCLE_RANGE_E;
	
typedef enum
{
	QL_PWM_CLK_SRC_13M,
	QL_PWM_CLK_SRC_32K,
}QL_PWM_CLK_SRC_E;
		

typedef struct
{
  unsigned long        pwm_psc;    //(value:1~64)  example:choose 13 MHz,  maximum is 13000000/1=13 MHz, minimum is 13000000/64 = 203,125 KHz.
  unsigned short       high_one_cycle_duration;  //Time that PWM_OUT puls is high in term of "clk_freq" define above. This value is written to PWDUTY register.
  unsigned short       total_one_cycle_duration; //(1<value< 1023) One cycle of PWM_OUT puls (high and low) in term of "clk_freq" define above. This value is written to PERVAL register.
  QL_PWM_CLK_SRC_E   clk_src;       //The clock source,32KHz  and  13MHz
}QL_PWM_CONFIG_EX;


/******************************************************************
*	 Functions
******************************************************************/

/*****************************************************************
* Function: ql_pwm_enable
*
* Description: 	
*此函数打开pwm功能
* 
* Parameters:
* 	gpio_num			[in] 	选择PWM的GPIO口。
*
* Return:
* 	0	             成功。
*	-1               失败。
*
*****************************************************************/
int ql_pwm_enable(unsigned int gpio_num);

/*****************************************************************
* Function: ql_pwm_disable
*
* Description: 	
*此函数关闭pwm功能
* 
* Parameters:
* 	gpio_num			[in] 	选择PWM的GPIO口。
*
* Return:
* 	0	             成功。
*	-1               失败。
*
*****************************************************************/
int ql_pwm_disable(unsigned int gpio_num);


/*****************************************************************
* Function: ql_pwm_config_plus_ex
*
* Description: 	2022-02-28
*此函数产生的pwm频率可根据用户选择时钟源、分频系数、重装值来自定义设置频率；选择高电平、重装值时间(整个周期时间)确定PWM占空比。 
* 
* Parameters:
* 	gpio_num			[in] 	选择PWM的GPIO口。
* 	pwm_parameter	  　[in] 	设置分频系数、高电平、重装值、时钟源等参数
*
* Return:
* 	0	             成功。
*	-1               失败。
*
*****************************************************************/
int ql_pwm_config_plus_ex(unsigned int gpio_num,QL_PWM_CONFIG_EX *pwm_parameter);



#ifdef __cplusplus
} /*"C" */
#endif

#endif

