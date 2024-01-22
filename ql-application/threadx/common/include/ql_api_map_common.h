/*================================================================
  Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/

#ifndef _QL_API_MAP_COMMON_H
#define _QL_API_MAP_COMMON_H

#ifdef __SDK_API_DEBUG__
#define api_notsup "%s() is not supported\r\n"
#define SDK_API_DEBUG_NOTSUP() ql_trace(api_notsup, (char*)__FUNCTION__)
#else
#define SDK_API_DEBUG_NOTSUP()
#endif

#endif

