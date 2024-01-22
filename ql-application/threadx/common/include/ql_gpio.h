/*================================================================
  Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/
/**
 ******************************************************************************
 * @file    ql_gpio.h
 * @author  Juson.zhang
 * @version V1.0.0
 * @date    2019/12/17
 * @brief   This file contains the lcd functions's declaration
 ******************************************************************************
 */
#ifndef _QUEC_GPIO_H_
#define _QUEC_GPIO_H_

#ifdef __cplusplus
	extern "C" {
#endif

typedef enum GPIO_PIN_NUMBER_ENUM {
	GPIO_PIN_NO_NOT_ASSIGNED = -1,

	GPIO_PIN_NO_0=0,GPIO_PIN_NO_1,  GPIO_PIN_NO_2,  GPIO_PIN_NO_3,  GPIO_PIN_NO_4,  GPIO_PIN_NO_5,  GPIO_PIN_NO_6,  GPIO_PIN_NO_7,
	GPIO_PIN_NO_8,  GPIO_PIN_NO_9,  GPIO_PIN_NO_10, GPIO_PIN_NO_11, GPIO_PIN_NO_12, GPIO_PIN_NO_13, GPIO_PIN_NO_14, GPIO_PIN_NO_15,
	GPIO_PIN_NO_16, GPIO_PIN_NO_17, GPIO_PIN_NO_18, GPIO_PIN_NO_19, GPIO_PIN_NO_20, GPIO_PIN_NO_21, GPIO_PIN_NO_22, GPIO_PIN_NO_23,
	GPIO_PIN_NO_24, GPIO_PIN_NO_25, GPIO_PIN_NO_26, GPIO_PIN_NO_27, GPIO_PIN_NO_28, GPIO_PIN_NO_29, GPIO_PIN_NO_30, GPIO_PIN_NO_31,
	GPIO_PIN_NO_32, GPIO_PIN_NO_33, GPIO_PIN_NO_34, GPIO_PIN_NO_35, GPIO_PIN_NO_36, GPIO_PIN_NO_37, GPIO_PIN_NO_38, GPIO_PIN_NO_39,	
	GPIO_PIN_NO_40, GPIO_PIN_NO_41, GPIO_PIN_NO_42, GPIO_PIN_NO_43, GPIO_PIN_NO_44, GPIO_PIN_NO_45, GPIO_PIN_NO_46, GPIO_PIN_NO_47,
	GPIO_PIN_NO_48, GPIO_PIN_NO_49, GPIO_PIN_NO_50, GPIO_PIN_NO_51, GPIO_PIN_NO_52, GPIO_PIN_NO_53, GPIO_PIN_NO_54, GPIO_PIN_NO_55,
	GPIO_PIN_NO_56, GPIO_PIN_NO_57, GPIO_PIN_NO_58, GPIO_PIN_NO_59, GPIO_PIN_NO_60, GPIO_PIN_NO_61, GPIO_PIN_NO_62, GPIO_PIN_NO_63,

	GPIO_PIN_NO_64, GPIO_PIN_NO_65, GPIO_PIN_NO_66, GPIO_PIN_NO_67, GPIO_PIN_NO_68, GPIO_PIN_NO_69, GPIO_PIN_NO_70, GPIO_PIN_NO_71,
	GPIO_PIN_NO_72, GPIO_PIN_NO_73, GPIO_PIN_NO_74, GPIO_PIN_NO_75, GPIO_PIN_NO_76, GPIO_PIN_NO_77, GPIO_PIN_NO_78, GPIO_PIN_NO_79,
	GPIO_PIN_NO_80, GPIO_PIN_NO_81, GPIO_PIN_NO_82, GPIO_PIN_NO_83, GPIO_PIN_NO_84, GPIO_PIN_NO_85, GPIO_PIN_NO_86, GPIO_PIN_NO_87,
	GPIO_PIN_NO_88, GPIO_PIN_NO_89, GPIO_PIN_NO_90, GPIO_PIN_NO_91, GPIO_PIN_NO_92, GPIO_PIN_NO_93, GPIO_PIN_NO_94, GPIO_PIN_NO_95,
	GPIO_PIN_NO_96, GPIO_PIN_NO_97, GPIO_PIN_NO_98, GPIO_PIN_NO_99, GPIO_PIN_NO_100, GPIO_PIN_NO_101, GPIO_PIN_NO_102, GPIO_PIN_NO_103,
	GPIO_PIN_NO_104, GPIO_PIN_NO_105, GPIO_PIN_NO_106, GPIO_PIN_NO_107, GPIO_PIN_NO_108, GPIO_PIN_NO_109, GPIO_PIN_NO_110, GPIO_PIN_NO_111,
	GPIO_PIN_NO_112, GPIO_PIN_NO_113, GPIO_PIN_NO_114, GPIO_PIN_NO_115, GPIO_PIN_NO_116, GPIO_PIN_NO_117, GPIO_PIN_NO_118, GPIO_PIN_NO_119,
	GPIO_PIN_NO_120, GPIO_PIN_NO_121, GPIO_PIN_NO_122, GPIO_PIN_NO_123, GPIO_PIN_NO_124, GPIO_PIN_NO_125, GPIO_PIN_NO_126, GPIO_PIN_NO_127,
	GPIO_PIN_NO_MAX,
}GPIO_PIN_NUMBER_E;

typedef enum PIN_DIRECTION_ENUM {
	PIN_DIRECTION_IN = 0,
	PIN_DIRECTION_OUT,
}PIN_DIRECTION_E;

typedef enum PIN_LEVEL_ENUM {
	PIN_LEVEL_LOW = 0,
	PIN_LEVEL_HIGH,
}PIN_LEVEL_E;

typedef enum PIN_PULL_ENUM {
	PIN_PULL_DISABLE = 0,
	PIN_PULL_PU,
	PIN_PULL_PD,
}PIN_PULL_E;

typedef enum PIN_EDGE_ENUM {
	PIN_NO_EDGE = 0,
	PIN_RISING_EDGE,
	PIN_FALLING_EDGE,
	PIN_BOTH_EDGE,
}PIN_EDGE_E;

typedef enum QL_LDO_VOL_ENUM {
	QL_LDO_1_8V,
	QL_LDO_2_8V,
}QL_LDO_VOL_E;

typedef struct quec_gpio_cfg_struct {
	GPIO_PIN_NUMBER_E gpio_pin_num;
	PIN_DIRECTION_E pin_dir;
	PIN_EDGE_E		pin_edge;
	PIN_PULL_E 		pin_pull;
	PIN_LEVEL_E 	pin_level;
}quec_gpio_cfg_t;

typedef enum QL_PIMC_GPIO_ENUM{
	PMIC_GPIO_PIN_209,	
	PMIC_GPIO_PIN_210,
	PMIC_GPIO_PIN_217,
}QL_PIMC_GPIO_E;

typedef enum QL_USIM2_IO_ENUM{
	USIM2_IO_VOL_1_8V,
	USIM2_IO_VOL_3_3V,
}QL_USIM2_IO_E;

int ql_gpio_init(GPIO_PIN_NUMBER_E gpio_num, PIN_DIRECTION_E pin_dir, PIN_PULL_E pin_pull, PIN_LEVEL_E pin_level);
int ql_gpio_deinit(GPIO_PIN_NUMBER_E gpio_num);
int ql_gpio_set_level(GPIO_PIN_NUMBER_E gpio_num, PIN_LEVEL_E pin_level);
int ql_gpio_get_level(GPIO_PIN_NUMBER_E gpio_num, PIN_LEVEL_E *p_pin_level);
int ql_gpio_set_direction(GPIO_PIN_NUMBER_E gpio_num, PIN_DIRECTION_E pin_dir);
int ql_gpio_get_direction(GPIO_PIN_NUMBER_E gpio_num, PIN_DIRECTION_E *p_pin_dir);
int ql_gpio_set_pull(GPIO_PIN_NUMBER_E gpio_num, PIN_PULL_E pin_pull);
int ql_gpio_get_pull(GPIO_PIN_NUMBER_E gpio_num, PIN_PULL_E *p_pin_pull);

int ql_eint_register(GPIO_PIN_NUMBER_E gpio_num, PIN_EDGE_E pin_edge, PIN_PULL_E pin_pull, void *eint_cb, void *wakeup_eint_cb);
int ql_eint_unregister(GPIO_PIN_NUMBER_E gpio_num);
int ql_eint_enable(GPIO_PIN_NUMBER_E gpio_num, PIN_EDGE_E pin_edge);
int ql_eint_disable(GPIO_PIN_NUMBER_E gpio_num);
int ql_eint_enable_wakeup(GPIO_PIN_NUMBER_E gpio_num, PIN_EDGE_E pin_edge);
int ql_eint_disable_wakeup(GPIO_PIN_NUMBER_E gpio_num);

int ql_set_pmic_gpio_level(QL_PIMC_GPIO_E PINx,unsigned       char level);/* somer.zhang-2020/05/11:set pmic gpio out high level(1) or low level(0) */

/*****************************************************************
* Function:     ql_gpio_map_clock 
* 
 Description:    Notice
*                Configure GPIO_122 to output 32K clock(32787Hz).
* Parameters:
*            only:  gpio_num = GPIO_PIN_NO_122 
* Return:        
*               0 , the function execution succeed.
*               -1, the parameter error.
*****************************************************************/

int ql_gpio_map_clock(GPIO_PIN_NUMBER_E gpio_num);

/***********************************************************************
 *
 * Name:   ql_set_usim2_io_vol	
 *
* Description: 设置usim相关引脚电压域（GPIO45~47,此接口仅适用于1606平台项目）
 *
 * Parameters:	onoff： 开启或关闭电压域：0：关闭；1：开启
				vol:	要设置的电压域，参考枚举QL_USIM2_IO_E
 * 
 * Returns: 	0  sucess
				-1 fail
 * Notes:
 *
 ***********************************************************************/
int ql_set_usim2_io_vol(char onoff, QL_USIM2_IO_E vol);

#ifdef __cplusplus
	} /*"C" */
#endif
	
#endif /* _QUEC_GPIO_H_ */

