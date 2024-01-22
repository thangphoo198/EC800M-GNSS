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
	int state; //dial status--�����󶨵�״̬
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
*	�������š�Ĭ��Ϊͬ��ģʽ������ql_set_data_call_asyn_mode����Ϊ�첽ģʽ
* 
* Parameters:
* 	profile_idx	  		[in] 	PDP������ȡֵ1-16�� 1,ΪĬ�ϳ���
* 	ip_version	  		[in] 	IP���ͣ�0 ΪIPv4��1 ΪIPv6��2 ΪIPv4v6��
* 	apn_name	  		[in] 	apn���ơ�
* 	username	  		[in] 	�û����ơ�
* 	password	  		[in] 	�û����롣
* 	auth_type	  		[in] 	��֤����: 0 NONE
*										  1 PAP
*										  2 CHAP
*										  3 PAP or CHAP
*
* Return:
* 	0			�ɹ���
*	-1 			ʧ�ܡ�
*
*****************************************************************/
extern int ql_start_data_call(int profile_idx, int ip_version, char *apn_name, char *username, char *password, int auth_type);


/*****************************************************************
* Function: ql_stop_data_call
*
* Description:
* 	�رղ��š� Ĭ��Ϊͬ��ģʽ������ql_set_data_call_asyn_mode����Ϊ�첽ģʽ
* 
* Parameters:
* 	profile_idx	  		[in] 	PDP������
* 	ip_version	  		[in] 	IP���ͣ�0 ΪIPv4��1 ΪIPv6��2 ΪIPv4v6�� 
*
* Return:
* 	0			�ɹ���
*	-1 			ʧ�ܡ�

*
*****************************************************************/
extern int ql_stop_data_call(int profile_idx, int ip_version);


/*****************************************************************
* Function: ql_get_data_call_info
*
* Description:
* 	��ȡ������Ϣ�� 
* 
* Parameters:
* 	profile_idx	  		[in] 	PDP������ 
* 	ip_version	  		[in] 	IP����
*	info				[out] 	��ȡ������Ϣ�� 
*
* Return:
* 	0			�ɹ���
*	-1 			ʧ�ܡ�
*
*****************************************************************/
extern int ql_get_data_call_info(int profile_idx, int ip_version, struct ql_data_call_info *info);



/*****************************************************************
* Function: ql_set_auto_connect
*
* Description:
* 	�����Զ����ӡ� 
* 
* Parameters:
* 	profile_idx	  		[in] 	PDP������ 
* 	status	  			[in] 	�Զ��������ã�0 ��ֹ�Զ����ӣ�1 �����Զ�����
*
* Return:
* 	0			�ɹ���
*	-1 			ʧ�ܡ�
*
*****************************************************************/
extern int ql_set_auto_connect(int profile_idx, bool status);


/*****************************************************************
* Function: ql_data_call_event_cb_t
*
* Description:
* 	���ݲ���״̬�ص�������
* 
* Parameters:
* 	profile_idx	  			[in] 	PDP������
* 	nw_status	  			[in] 	���ݲ���״̬��0��ʧ�ܣ�1���ɹ��� 
*
* Return:
* 	��
*
*****************************************************************/
typedef void(* ql_data_call_event_cb_t)(int profile_idx, int state);


/*****************************************************************
* Function: ql_set_data_call_asyn_mode
*
* Description:
* 	����ql_start_data_call��ql_stop_data_call�ӿڵ�ִ��ģʽ���������첽ģʽ�Ļص������� 
* 
* Parameters:
* 	enable	  			[in] 	1��ʹ���첽ģʽ��0����ʹ���첽ģʽ,ͬ��ģʽ 
* 	cb	  				[in] 	���ݲ���״̬�ص��������������˴˻ص���������ql_wan_start�ӿ����õĻص�������Ч
*
* Return:
* 	0			�ɹ���
*	-1 			ʧ�ܡ�
* NOTES:
* ���ʹ��ͬ��ģʽ��ql_start_data_call()������������api��ֱ����������
*****************************************************************/
extern int ql_set_data_call_asyn_mode(char enable, ql_data_call_event_cb_t cb);


/*****************************************************************
* Function: ql_network_register_wait
*
* Description:
* 	�ȴ�����ע�� 
* 
* Parameters:
* 	timeout_s	  			[in] 	��ʱʱ�䣬��λ�롣 
*
* Return:
* 	0			ע��ɹ���
*	-1 			ע��ʧ�ܡ�
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
* 	���ݲ���״̬�ص�������ע��׼�����ã���ql_data_call_event_cb_tȡ���������᳤�ڴ��ڣ�������ǰʹ�÷�ʽ
* 
* Parameters:
* 	profile_idx	  			[in] 	PDP������
* 	nw_status	  			[in] 	���ݲ���״̬��0��ʧ�ܣ�1���ɹ��� 
*
* Return:
* 	��
*
*****************************************************************/
typedef void(* nw_status_cb)(int profile_idx, int nw_status);


/*****************************************************************
* Function: ql_wan_start
*
* Description:
* 	��ʼ�����ݷ���ע��׼�����ã���ʼ�����ݷ�����ql_start_data_call�ӿ���ɣ�Ŀǰ֧��ͬ��ģʽ���������ݲ���״̬�ص������������᳤�ڴ��ڣ�������ǰʹ�÷�ʽ 
* 
* Parameters:
* 	nw_cb	  			[in] 	���ݲ���״̬�ص������� 
*
* Return:
* 	0			�ɹ���
*	-1 			ʧ�ܡ�
*
*****************************************************************/
extern int ql_wan_start(nw_status_cb nw_cb);


/*****************************************************************
* Function: ql_set_lwip_dns
*
* Description:
* 	����DNS����
* 
* Parameters:
* 	profile_idx	  			[in] 	PDP������ 
* 	dns1	  				[in] 	DNS1�����ַ��
* 	dns2	  				[in] 	DNS2�����ַ��
*
* Return:
* 	0			�ɹ���
*	-1 			ʧ�ܡ�
*
*****************************************************************/
extern int ql_set_lwip_dns(int profile_idx, char *dns1, char *dns2);

/*****************************************************************
* Function: ql_get_lwip_dns
*
* Description:
* 	����DNS����
* 
* Parameters:
* 	profile_idx	  			[in] 	PDP������ 
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
* 	����IPV6��DNS��������ַ��
* 
* Parameters:
* 	profile_idx	  			[in] 	PDP������ 
* 	dns1	  				[in] 	DNS1�����ַ��
* 	dns2	  				[in] 	DNS2�����ַ��
*
* Return:
* 	0			�ɹ���
*	-1 			ʧ�ܡ�
*
*****************************************************************/
extern int ql_set_lwip_dns_ipv6(int profile_idx, char *dns1, char *dns2);

/*****************************************************************
* Function: ql_get_lwip_dns_ipv6
*
* Description:
* 	��ȡDNS��������ַ��
* 
* Parameters:
* 	profile_idx	  			[in] 	PDP������ 
* 	data	  				[out] 	DNS info��Ҫ��ָ��ָ�����150�ֽڵĿռ�
*
* Return:
* 	0			OK
*	-1 			FAIL
*
*****************************************************************/
extern int ql_get_lwip_dns_ipv6(int profile_idx, char * data);

#endif

