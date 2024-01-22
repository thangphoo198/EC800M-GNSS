/*==========================================================================================================
  Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
===========================================================================================================*/

/*==========================================================================================================

                        EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.

WHEN              WHO         WHAT, WHERE, WHY
------------     -------     -------------------------------------------------------------------------------
09/04/2022        Sharon.li  此文件是QuecOpen APP的日志系统接口

===========================================================================================================*/

#ifndef _QL_LOG_H
#define _QL_LOG_H

#include "ql_type.h"



/*========================================================================
*Internal function Declarations
*========================================================================*/
extern void _ql_os_log(const char* fmt, ...);

extern void _ql_fs_log(const char* fmt, ...);

extern void _ql_app_log(const char* fmt, ...);

extern char * _ql_log_get_short_file_name(char * file_name);






/*========================================================================
 *  Enumeration Definition
 *========================================================================*/

//the on-off mask of various modules, one module occupy one bit  
typedef enum
{	
	QL_LOG_BSP_MASK           = 0x0000000000000001,
		
	QL_LOG_OS_MASK            = 0x0000000000000002,
	
	QL_LOG_FS_MASK            = 0x0000000000000004,
	
	QL_LOG_TCPIP_MASK         = 0x0000000000000008,
	
	QL_LOG_MQTT_MASK          = 0x0000000000000010,
	
	QL_LOG_APP_MASK           = 0x0000000000000020,
	
}ql_log_module_mask;


typedef enum
{
	QL_LOG_PORT_UART = 0x1,
	QL_LOG_PORT_USB  = 0x2,
}ql_log_port_mask;

typedef enum 
{
   QL_DEBUG_LOG_OPEN = 0,
   QL_DEBUG_LOG_CLOSE
}qL_debug_log_mode_e;


/*========================================================================
*External  function Declarations
*========================================================================*/

/*-----------------------------------------------------------------------------------------
 * Function: module log on-off
 *
 * Parameter:
 *    <module_mask>: 	[IN] the on-off mask of various modules.
 *    <port_mask>: 	    [IN] the on-off mask of UART and USB.
 *		
 * Return:
 *    
-----------------------------------------------------------------------------------------*/
extern void ql_log_mask_set(UINT64 module_mask, UINT32 port_mask);


/*========================================================================
 *  Macro Definition
 *========================================================================*/
#define SHORT_FILE								_ql_log_get_short_file_name(__FILE__)

/*-----------------------------------------------------------------------------------------
 * Function: OS module log print
 *
 * Parameter:
 *    <fmt>: 	[IN] log output format.
 *    <...>: 	[IN] log output parameter.
 *		
 * Return:
 *    
-----------------------------------------------------------------------------------------*/
#define ql_os_log(fmt, ...) _ql_os_log("[%s, %d] "fmt"\r\n", SHORT_FILE, __LINE__, ##__VA_ARGS__)


/*-----------------------------------------------------------------------------------------
 * Function: FS module log print
 *
 * Parameter:
 *    <fmt>: 	[IN] log output format.
 *    <...>: 	[IN] log output parameter.
 *		
 * Return:
 *    
-----------------------------------------------------------------------------------------*/
#define ql_fs_log(fmt, ...) _ql_fs_log("[%s, %d] "fmt"\r\n", SHORT_FILE, __LINE__, ##__VA_ARGS__)


/*-----------------------------------------------------------------------------------------
 * Function: APP module log print
 *
 * Parameter:
 *    <fmt>: 	[IN] log output format.
 *    <...>: 	[IN] log output parameter.
 *		
 * Return:
 *    
-----------------------------------------------------------------------------------------*/
#define ql_app_log(fmt, ...) _ql_app_log("[%s, %d] "fmt"\r\n", SHORT_FILE, __LINE__, ##__VA_ARGS__)


int printf( const char *format, ... );
void ql_debug_log_enable(void);
void ql_debug_log_disable(void);



#endif


