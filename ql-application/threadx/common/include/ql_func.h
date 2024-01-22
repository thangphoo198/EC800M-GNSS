/*================================================================
  Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/
#ifndef __QL_FUNC_H__
#define __QL_FUNC_H__

#include "ql_type.h"



typedef void (*userBoot_t)(void * argv);
typedef struct
{
	userBoot_t user_boot_entry;
	u8 startup_prio;
} userBootItem_t;
#define _userBoot_attr_ __attribute__((unused, section(".userBootTable")))



typedef void (*userKernel_t)(void * argv);
typedef struct
{
	userKernel_t user_kernel_entry;
	char *user_kernel_name;
	u32 stack_size_byte;
	u8 startup_prio;
} userKernelItem_t;
#define KERNEL_TASK_STACK_SIZE 2048
#define KERNEL_TASK_NAME "kernel"
#define _userKernel_attr_ __attribute__((unused, section(".userKernelTable")))



typedef void (*app_t)(void * argv);
typedef struct
{
	app_t app_entry;
	char *app_name;
	u32 stack_size_byte;
	u8 startup_prio;
} appRegItem_t;
#define _appRegTable_attr_ __attribute__((unused, section(".appRegTable")))



typedef s32 (*_ql_trace_t)(char* fmt, ... );
typedef s32 (*_get_api_ptr_t)(char* func_name );

typedef struct {
	void (*trace)(char* fmt, ... );
	s32 (*sprintf)(char *, const char *, ...);
	s32 (*snprintf)(char*, u32, const char*, ...);
	s32 (*sscanf)(const char*, const char*, ...);
} ql_static_mapping;

typedef struct func_map         
{
    u32   *table_size;
    void  *get_fun_ptr_dep_name;
	//add system info here
}func_mapping;

typedef struct app_cfg         
{
    u32 debug_mode;
	//add customer conifg here
}app_cfg;

typedef struct sys_info         
{
    u32 heam_size;
    u32 availible_heap_size;
	//add system info here
}sys_info;

typedef struct boot_para          
{
    void *static_maping;
    void *kernel_maping;
}boot_para;

/* Entry Point */
typedef struct {
    void    (*boot)(boot_para *boottime_para);
	void    (*kernel)(void *kerneltime_para);
    void    (*main)(void *runtime_para);
    u32     *app_config;
    u32     *system_infomation;
    u32     data_load_addr;
    u32     data_ram_start;
    u32     data_ram_end;
}ql_open_entry;

extern _ql_trace_t ql_trace;
extern u32 func_table_size;
extern _get_api_ptr_t m_get_api_ptr;

#endif  // End-of '__QL_FUNC_H__'

