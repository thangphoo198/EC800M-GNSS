/*================================================================
  Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/

#ifndef _QL_APPLICATION_H
#define _QL_APPLICATION_H

#include "ql_func.h"

#define application_init(app_entry, app_name, stack_size_kib, startup_prio) appRegItem_t _regAppItem_##app_entry _appRegTable_attr_ = {app_entry, app_name, stack_size_kib*1024, startup_prio}

#endif
