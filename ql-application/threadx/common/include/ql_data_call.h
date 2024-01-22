/*================================================================
  Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/

#ifndef __QL_DATA_CALL_H__
#define __QL_DATA_CALL_H__

#include "inet.h"
#include "inet6.h"
#include "stdbool.h"
#include "stdint.h"


struct v4_address_status
{
	struct in_addr ip;
	struct in_addr pri_dns;
	struct in_addr sec_dns;
};

struct v4_info
{
	int state; //dial status
	int reconnect; //re-dial flag
	struct v4_address_status addr; //IPv4 address information
};

struct v6_address_status
{
	struct in6_addr ip;
	struct in6_addr pri_dns;
	struct in6_addr sec_dns;
};

struct v6_info
{
	int state; //dial status--网卡绑定的状态
	int reconnect; //re-dial flag
	struct v6_address_status addr; //IPv6 address information
};

struct ql_data_call_info
{
	int profile_idx;
	int ip_version;
	struct v4_info v4;
	struct v6_info v6;
};


/*****************************************************************
* Function: ql_start_data_call
*
* Description:
*	启动拨号。默认为同步模式，可由ql_set_data_call_asyn_mode设置为异步模式
* 
* Parameters:
* 	profile_idx	  		[in] 	PDP索引，取值1-16。 1,为默认承载
* 	ip_version	  		[in] 	IP类型：0 为IPv4，1 为IPv6，2 为IPv4v6。
* 	apn_name	  		[in] 	apn名称。
* 	username	  		[in] 	用户名称。
* 	password	  		[in] 	用户密码。
* 	auth_type	  		[in] 	认证类型: 0 NONE
*										  1 PAP
*										  2 CHAP
*										  3 PAP or CHAP
*
* Return:
* 	0			成功。
*	-1 			失败。
*
*****************************************************************/
extern int ql_start_data_call(int profile_idx, int ip_version, char *apn_name, char *username, char *password, int auth_type);


/*****************************************************************
* Function: ql_stop_data_call
*
* Description:
* 	关闭拨号。 默认为同步模式，可由ql_set_data_call_asyn_mode设置为异步模式
* 
* Parameters:
* 	profile_idx	  		[in] 	PDP索引。
* 	ip_version	  		[in] 	IP类型：0 为IPv4，1 为IPv6，2 为IPv4v6。 
*
* Return:
* 	0			成功。
*	-1 			失败。

*
*****************************************************************/
extern int ql_stop_data_call(int profile_idx, int ip_version);


/*****************************************************************
* Function: ql_get_data_call_info
*
* Description:
* 	获取拨号信息。 
* 
* Parameters:
* 	profile_idx	  		[in] 	PDP索引。 
* 	ip_version	  		[in] 	IP类型
*	info				[out] 	获取拨号信息。 
*
* Return:
* 	0			成功。
*	-1 			失败。
*
*****************************************************************/
extern int ql_get_data_call_info(int profile_idx, int ip_version, struct ql_data_call_info *info);



/*****************************************************************
* Function: ql_set_auto_connect
*
* Description:
* 	设置自动连接。 
* 
* Parameters:
* 	profile_idx	  		[in] 	PDP索引。 
* 	status	  			[in] 	自动连接设置：0 禁止自动连接，1 启用自动连接
*
* Return:
* 	0			成功。
*	-1 			失败。
*
*****************************************************************/
extern int ql_set_auto_connect(int profile_idx, bool status);


/*****************************************************************
* Function: ql_data_call_event_cb_t
*
* Description:
* 	数据拨号状态回调函数。
* 
* Parameters:
* 	profile_idx	  			[in] 	PDP索引。
* 	nw_status	  			[in] 	数据拨号状态，0：失败；1：成功。 
*
* Return:
* 	无
*
*****************************************************************/
typedef void(* ql_data_call_event_cb_t)(int profile_idx, int state);


/*****************************************************************
* Function: ql_set_data_call_asyn_mode
*
* Description:
* 	设置ql_start_data_call和ql_stop_data_call接口的执行模式，并设置异步模式的回调函数， 
* 
* Parameters:
* 	enable	  			[in] 	1：使能异步模式；0：不使能异步模式,同步模式 
* 	cb	  				[in] 	数据拨号状态回调函数。当设置了此回调函数，则ql_wan_start接口设置的回调函数无效
*
* Return:
* 	0			成功。
*	-1 			失败。
* NOTES:
* 如果使能同步模式，ql_start_data_call()将会变成阻塞的api，直至函数返回
*****************************************************************/
extern int ql_set_data_call_asyn_mode(char enable, ql_data_call_event_cb_t cb);


/*****************************************************************
* Function: ql_network_register_wait
*
* Description:
* 	等待网络注册 
* 
* Parameters:
* 	timeout_s	  			[in] 	超时时间，单位秒。 
*
* Return:
* 	0			注册成功。
*	-1 			注册失败。
*
*****************************************************************/
#ifdef __OCPU_COMPILER_GCC__
	extern int ql_network_register_wait(u32 timeout_s);
#else
	extern int ql_network_register_wait(uint32 timeout_s);
#endif

/*****************************************************************
* Function: nw_status_cb
*
* Description:
* 	数据拨号状态回调函数。注：准备弃用，由ql_data_call_event_cb_t取代。函数会长期存在，兼容以前使用方式
* 
* Parameters:
* 	profile_idx	  			[in] 	PDP索引。
* 	nw_status	  			[in] 	数据拨号状态，0：失败；1：成功。 
*
* Return:
* 	无
*
*****************************************************************/
typedef void(* nw_status_cb)(int profile_idx, int nw_status);


/*****************************************************************
* Function: ql_wan_start
*
* Description:
* 	初始化数据服务。注：准备弃用，初始化数据服务在ql_start_data_call接口完成，目前支持同步模式下设置数据拨号状态回调函数。函数会长期存在，兼容以前使用方式 
* 
* Parameters:
* 	nw_cb	  			[in] 	数据拨号状态回调函数。 
*
* Return:
* 	0			成功。
*	-1 			失败。
*
*****************************************************************/
extern int ql_wan_start(nw_status_cb nw_cb);


/*****************************************************************
* Function: ql_set_lwip_dns
*
* Description:
* 	设置DNS服务。
* 
* Parameters:
* 	profile_idx	  			[in] 	PDP索引。 
* 	dns1	  				[in] 	DNS1服务地址。
* 	dns2	  				[in] 	DNS2服务地址。
*
* Return:
* 	0			成功。
*	-1 			失败。
*
*****************************************************************/
extern int ql_set_lwip_dns(int profile_idx, char *dns1, char *dns2);

/*****************************************************************
* Function: ql_get_lwip_dns
*
* Description:
* 	设置DNS服务。
* 
* Parameters:
* 	profile_idx	  			[in] 	PDP索引。 
* 	data	  				[out] 	DNS info
*
* Return:
* 	0			OK
*	-1 			FAIL
*
*****************************************************************/

extern int ql_get_lwip_dns(int profile_idx, char * data);

/*****************************************************************
* Function: ql_set_lwip_dns_ipv6
*
* Description:
* 	设置IPV6的DNS服务器地址。
* 
* Parameters:
* 	profile_idx	  			[in] 	PDP索引。 
* 	dns1	  				[in] 	DNS1服务地址。
* 	dns2	  				[in] 	DNS2服务地址。
*
* Return:
* 	0			成功。
*	-1 			失败。
*
*****************************************************************/
extern int ql_set_lwip_dns_ipv6(int profile_idx, char *dns1, char *dns2);

/*****************************************************************
* Function: ql_get_lwip_dns_ipv6
*
* Description:
* 	获取DNS服务器地址。
* 
* Parameters:
* 	profile_idx	  			[in] 	PDP索引。 
* 	data	  				[out] 	DNS info，要求指针指向大于150字节的空间
*
* Return:
* 	0			OK
*	-1 			FAIL
*
*****************************************************************/
extern int ql_get_lwip_dns_ipv6(int profile_idx, char * data);

#endif

