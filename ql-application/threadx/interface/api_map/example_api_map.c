/*================================================================
  Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/

#include "ql_application.h"
#include "ql_type.h"
#include "ql_func.h"
#include "ql_error.h"
#include "ql_api_map_common.h"
#include <stdio.h>

typedef void (*_api_ql_user_api_map_test_t)(void);
static _api_ql_user_api_map_test_t m_ql_user_api_map_test = NULL;

// do api mapping wrapper
void ql_user_api_map_test(void)
{
	if(NULL == m_ql_user_api_map_test)
	{
		s32 ptr = m_get_api_ptr((char*)__FUNCTION__);
		if(0 == ptr)
		{
			SDK_API_DEBUG_NOTSUP();
			return ;
		}
		m_ql_user_api_map_test = (_api_ql_user_api_map_test_t)ptr;
	}
	return m_ql_user_api_map_test();
}

// call the mapped api to verify the correctness.
void ql_user_api_call(void * argv)
{
	//printf("will call <ql_user_api_map_test> to verify its correctness\r\n");
	ql_user_api_map_test();
}

// startup <ql_user_api_call> when system init done
//application_init(ql_user_api_call, "api_map_test", 1, 0);


