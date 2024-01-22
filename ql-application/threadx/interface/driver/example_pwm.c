/*================================================================
  Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/


#include <stdio.h>
#include <math.h>
#include "ql_rtos.h"
#include "ql_application.h"
#include "ql_pwm.h"
#include "ql_gpio.h"


#define QL_PWM_TEST_ENABLE
#ifdef QL_PWM_TEST_ENABLE

/*Function: quec_pwm_test1
/*13M ʵ��ֵ ֻ��12.7998M���ң�32Kʵ��ֵΪ32787
*�˰���������pwmƵ�ʿɸ����û�ѡ��ʱ��Դ����Ƶϵ������װֵ���Զ�������Ƶ�ʣ�ѡ��ߵ�ƽ����װֵʱ��(��������ʱ��)ȷ��PWMռ�ձ�:
 ���PWM��Ƶ��Ϊ�� f = MCLK / ( (psc+1)(arr+1) ) ; ���õ�arrΪ10λ�Ĵ����������װֵ����1=<value<1024����Ҫע����װֵ�ķ�Χ��
ע�⣺�˴�psc+1,��Ϊ�˷�ֹ�û�����0��Ƶ����������⣬�ڵײ�������Ѽ�ȥ1���������psc��ֵΪ���٣������ٷ�Ƶ��
*/
static void quec_pwm_test1(void * argv)
{
	ql_rtos_task_sleep_s(2);
    printf("pwm test is running!!!\n");

	unsigned int gpio_num1 = 117;
	unsigned int gpio_num2 = 32;
	unsigned int gpio_num3 = 11;
	unsigned int gpio_num4 = 10;

	unsigned long pwm_psc = 1;


	QL_PWM_CONFIG_EX pwm_parameter1;
	QL_PWM_CONFIG_EX pwm_parameter2;
	QL_PWM_CONFIG_EX pwm_parameter3;
	QL_PWM_CONFIG_EX pwm_parameter4;
	//�����Լ�����ʽ����õ���Ҫ��PWM����߾�ȷ��

	printf("pwm test QUEC_PWM_CLK_SRC_13M!!!\n");
	pwm_parameter1.pwm_psc = pwm_psc;   //(value:1~64)
	pwm_parameter1.high_one_cycle_duration = 195;
	pwm_parameter1.total_one_cycle_duration =389;  //(value: 1<value<1024)	 f=12.7998 MHz/(389+1)=32820 HZ
	pwm_parameter1.clk_src=QL_PWM_CLK_SRC_13M;	
	ql_pwm_config_plus_ex(gpio_num1,&pwm_parameter1);	//����PWM�����ӿ�
	ql_pwm_enable(gpio_num1);							//PWMʹ��

	printf("pwm test QUEC_PWM_CLK_SRC_32K!!!\n");  
	pwm_parameter2.pwm_psc = 1;   		//(value:1~64)
	pwm_parameter2.high_one_cycle_duration = 164;
	pwm_parameter2.total_one_cycle_duration = 327;  //(value: 1<value<1024)	 f=32787/(327+1)=99.96 HZ
	pwm_parameter2.clk_src=QL_PWM_CLK_SRC_32K;
	
	//test_log("PWM=%d\n %d\n %ld\n %d\n %d\n",gpio_num2,pwm_parameter2.clk_src,pwm_parameter2.pwm_psc,pwm_parameter2.high_one_cycle_duration,pwm_parameter2.total_one_cycle_duration); 
	ql_pwm_config_plus_ex(gpio_num2,&pwm_parameter2);
	ql_pwm_enable(gpio_num2);

	pwm_parameter3.pwm_psc = 1;	//(value:1~64)
	pwm_parameter3.high_one_cycle_duration = 17;//17
	pwm_parameter3.total_one_cycle_duration = 33;	//(value: 1<value<1024)	 f=32787/(32+1)=964.32 HZ
	pwm_parameter3.clk_src=QL_PWM_CLK_SRC_32K;
	ql_pwm_config_plus_ex(gpio_num3,&pwm_parameter3);
	ql_pwm_enable(gpio_num3);

	pwm_parameter4.pwm_psc = 1;	//(value:1~64)
	pwm_parameter4.high_one_cycle_duration = 160;	
	pwm_parameter4.total_one_cycle_duration = 320;	//(value: 1<value<1024)	 f=32787/(320+1)=102.14 HZ
	pwm_parameter4.clk_src=QL_PWM_CLK_SRC_32K;
	ql_pwm_config_plus_ex(gpio_num4,&pwm_parameter4);
	ql_pwm_enable(gpio_num4);

	
}

//application_init(quec_pwm_test1, "quec_pwm_test1", 2, 0);


static void quec_gpio_32KHz_test(void * argv)
{
	/*gpio input 32Khz (32787Hz)*/
	printf("quec_gpio_32KHz_test!!!\n");  

	ql_gpio_map_clock(GPIO_PIN_NO_28);	//use GPIO_PIN_NO_28 
	
	ql_gpio_map_clock(GPIO_PIN_NO_20);	//use GPIO_PIN_NO_20

}

//application_init(quec_gpio_32KHz_test, "quec_gpio_32KHz_test", 2, 0);

#endif /* QL_PWM_TEST_ENABLE */

