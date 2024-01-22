/*================================================================
  Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/

#ifndef _QL_BOOT_H
#define _QL_BOOT_H

#include "ql_func.h"

#define user_boot_init(user_boot_entry, startup_prio) userBootItem_t _userBootItem_##user_boot_entry _userBoot_attr_ = {user_boot_entry, startup_prio}

#ifndef _userKernelItem_
#define user_kernel_init(user_kernel_entry) userKernelItem_t _userKernelItem_ _userKernel_attr_ = {user_kernel_entry, KERNEL_TASK_NAME, KERNEL_TASK_STACK_SIZE, 0}
#else
#error "User can only set one kernel item, now you have set more than one !!!"
#endif

#endif
