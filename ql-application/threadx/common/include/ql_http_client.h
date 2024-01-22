/*================================================================
  Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/


#ifndef __QL_HTTP_CLIENT_H__
#define __QL_HTTP_CLIENT_H__

#include "sockets.h"
#include "ql_ssl_hal.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef enum
{
	QL_HTTP_CLIENT_ERR_SUCCESS = 0,  //成功
	QL_HTTP_CLIENT_ERR_INVALID_CLIENT, //不可用的http client句柄
	QL_HTTP_CLIENT_ERR_INVALID_METHOD, //不可用的请求方式
	QL_HTTP_CLIENT_ERR_INVALID_URL, //不可用的请求URL
	QL_HTTP_CLIENT_ERR_DNS_FAIL, //对服务器进行DNS解析失败
	QL_HTTP_CLIENT_ERR_SOCK_CREATE_FAIL, //创建socket失败
	QL_HTTP_CLIENT_ERR_SOCK_BIND_FAIL, //对socket进行bind操作失败
	QL_HTTP_CLIENT_ERR_SOCK_CONN_FAIL, //执行socket连接失败
	QL_HTTP_CLIENT_ERR_SOCK_SEND_FAIL, //发送数据失败
	QL_HTTP_CLIENT_ERR_SOCK_RECV_FAIL, //接收数据失败
	QL_HTTP_CLIENT_ERR_SOCK_CLOSE_FAIL, //断开连接失败
	QL_HTTP_CLIENT_ERR_SSL_CONN_FAIL, // SSL connect fail
	QL_HTTP_CLIENT_ERR_RESP_TIMEOUT, //请求超时
	QL_HTTP_CLIENT_ERR_RESP_INVALID_VER, //不可用的协议版本
	QL_HTTP_CLIENT_ERR_RESP_INVALID_LOCATION, //不可用的location域
	QL_HTTP_CLIENT_ERR_LAST_REQUEST_NOT_FINISH, //上次请求还未完成
	QL_HTTP_CLIENT_ERR_NO_MEMORY, //http 请求缓存不足
	QL_HTTP_CLIENT_ERR_UNKNOWN //其他错误
} QL_HTTP_CLIENT_ERR_E;

typedef enum
{
	QL_HTTP_CLIENT_EVENT_SEND_FAIL=0, //http 请求发送失败
	QL_HTTP_CLIENT_EVENT_SEND_SUCCESSED, //http 请求发送成功
	QL_HTTP_CLIENT_EVENT_RECV_HEADER_FAIL, //http 接收响应header失败，header检查失败
	QL_HTTP_CLIENT_EVENT_RECV_HEADER_FINISHED, //http 接收响应header完成
	QL_HTTP_CLIENT_EVENT_RECV_BODY, //http 开始接收body数据
	QL_HTTP_CLIENT_EVENT_RECV_BODY_FINISHED, //http 接收body数据完成
	QL_HTTP_CLIENT_EVENT_DISCONNECTED //服务器断开连接
} QL_HTTP_CLIENT_EVENT_E;



typedef enum {
	QL_HTTP_CLIENT_OPT_PROTOCOL_VER, //设置http client协议版本,0：http/1.0；1：http/1.1
	QL_HTTP_CLIENT_OPT_HTTPHEADER, //设置http client自定义header,ql_http_client_list_append函数创建的一个header list
	QL_HTTP_CLIENT_OPT_PDP_CID, //设置http client使用的数据通道CID,执行数据拨号操作时使用的CID
	QL_HTTP_CLIENT_OPT_BIND_PORT,//设置http client使用的客户端网络端口
	QL_HTTP_CLIENT_OPT_ASYN, //设置http client请求执行模式,0：同步；1：异步
	QL_HTTP_CLIENT_OPT_ENABLE_COOKIE, //使能http client使用cookie,0：不使能cookie；1：使能cookie
	QL_HTTP_CLIENT_OPT_SSL_CTX, //设置SSL 
	QL_HTTP_CLIENT_OPT_RECV_TIMEOUT_MS, //设置http client接收数据的超时时间(ms)
	QL_HTTP_CLIENT_OPT_HOSTFIELD_USEDPORT,    //设置指定的url是否使用默认的port 某些客户有自己特定的url，如果使用默认的port发送head会被服务器拒绝断开连接。
}QL_HTTP_CLIENT_OPT_E;

typedef enum 
{
	QL_HTTP_CLIENT_REQUEST_GET, //GET请求
	QL_HTTP_CLIENT_REQUEST_POST, //POST请求
	QL_HTTP_CLIENT_REQUEST_MAX
}QL_HTTP_CLIENT_REQUEST_METHOD_E;

typedef enum 
{
	QL_HTTP_CLIENT_AUTH_TYPE_NONE=0, //不使用验证
	QL_HTTP_CLIENT_AUTH_TYPE_BASE = 1, //使用base验证
	QL_HTTP_CLIENT_AUTH_TYPE_DIGEST=2 //使用digest验证
}QL_HTTP_CLIENT_AUTH_TYPE_E;

typedef enum 
{
	QL_HTTP_CLIENT_HTTP1_0=0, //http/1.0版本协议
	QL_HTTP_CLIENT_HTTP1_1 =1, //http/1.1版本协议
}QL_HTTP_CLIENT_PROTOCL_VER_E;


typedef struct QL_HTTP_CLIENT_LIST{
	char * data;
	struct QL_HTTP_CLIENT_LIST * next;
}QL_HTTP_CLIENT_LIST_T;


typedef struct 
{
	char * url; // dup from user setting
	char * host; //
	char * path; //
	char * name;
	char * password;
	unsigned short int port;
	int auth_type;
	int https;
	char * auth_value;
	struct sockaddr_in ip;
	struct sockaddr_in6 ip6;
	int use_ip6;
	int url_is_ip6_address;
	int fd;
}QL_HTTP_SERVSER;

typedef struct 
{
  QL_HTTP_CLIENT_LIST_T * response_header;
  int status_code;
  int response_data_length;
}QL_HTTP_RESPONSE;

typedef struct 
{
	QL_HTTP_SERVSER server; // 服务信息
	QL_HTTP_CLIENT_LIST_T * private_header; // 自定义请求header
	QL_HTTP_CLIENT_REQUEST_METHOD_E method;
	int enable_cookie;
	QL_HTTP_CLIENT_LIST_T * cookie;
	SSLCtx sslCtx;
	int connection_state;
	QL_HTTP_CLIENT_PROTOCL_VER_E protocol_ver;
	char * location;
	int cid;
	unsigned short port;
	const char * data; 
	int data_len; 
	QL_HTTP_RESPONSE response; 
	void *rsp_cb; 
	void * rsp_cb_user_data;
	char *mem_buf;
	int asyn_f;
	void *send_recv_task_ref;
	void  *mutex_ref;
	QL_HTTP_CLIENT_ERR_E error_code;
    unsigned int timeout_ms;
    int bHostFieldUsedPort;       //1:使用默认端口， 0:不使用默认端口
}QL_HTTP_CLIENT_T;

/*****************************************************************
* Function: QL_HTTP_CLIENT_RESPONSE_CB
*
* Description:
* 	发送 HTTP 请求后，当相关事件发生时自动调用该回调函数。
* 
* Parameters:
*	client			[In] 	HTTP 客户端句柄。由 ql_http_client_init()获取。
*	event			[In] 	客户端调用 ql_http_client_request()后发生的事件类型。详见参第 3.3.3.4章。
*	status_code		[In] 	HTTP 服务器端返回的状态码。当 event 为如下三种事件时方返回状态码；当 event 为其他事件时，该参数始终为 0。详见QL_HTTP_CLIENT_EVENT_E。
*							QL_HTTP_CLIENT_EVENT_RECV_HEADER_FINISHED、QL_HTTP_CLIENT_EVENT_RECV_BODY、QL_HTTP_CLIENT_EVENT_RECV_BODY_FINISHED。
*	data			[In] 	HTTP 客户端接收到的数据。若 event 为 QL_HTTP_CLIENT_EVENT_RECV_HEADER_FINISHED，该参数表示服务器端响应的消息头（完整消息头）。
*							若 event 为 QL_HTTP_CLIENT_EVENT_RECV_BODY，该参数表示服务器端返回的消息体数据。此 事 件 可 能 会 发 生 多 次 ，
*							所 有 接 收 数 据 组 成 一 组 完 整 的 消 息 体 数 据 。 仅 当 接 收 到QL_HTTP_CLIENT_EVENT_RECV_BODY_FINISHED 方可表示所有消息体数据接收完成。
*							若 event 为其他事件时，该参数为 NULL。
*	data_len		[In] 	接收数据的长度。若 event 为 QL_HTTP_CLIENT_EVENT_RECV_HEADER_FINISHED，该参数表示服务器端响
*							应的消息头（完整消息头）的长度。单位：字节。若 event 为 QL_HTTP_CLIENT_EVENT_RECV_BODY，
*							该参数表示服务器端返回的消息体数据的长度。单位：字节。
*							若 event 为其他事件时，该参数为 0。
*	private_data	[In] 	传递至该回调函数的用户数据。
*
* Return:
*	0, 不再接收服务端返回数据，服务端返回数据将被丢弃。
*	1, 继续接收服务端返回数据。
*
*****************************************************************/
typedef int (*QL_HTTP_CLIENT_RESPONSE_CB)(QL_HTTP_CLIENT_T *client,QL_HTTP_CLIENT_EVENT_E event,int status_code, char *data, int data_len, void *private_data);

/*****************************************************************
* Function: ql_http_client_init
*
* Description:
* 	该函数用于初始化 HTTP 客户端资源并创建一个新的 HTTP 客户端句柄。
* 
* Parameters:
* 	无。
*
* Return:
*	NULL，失败。
*	非NULL，成功，返回一个新的 HTTP 客户端句柄。
*
*****************************************************************/
extern QL_HTTP_CLIENT_T * ql_http_client_init(void);

/*****************************************************************
* Function: ql_http_client_release
*
* Description:
* 	该函数用于释放 HTTP 客户端资源。
* 
* Parameters:
*	client	  [in] 	HTTP 客户端句柄。由 ql_http_client_init()获取。
*
* Return:
*	无。
*
*****************************************************************/
extern void ql_http_client_release(QL_HTTP_CLIENT_T *client);

/*****************************************************************
* Function: ql_http_client_request
*
* Description:
* 	该函数用于发送 HTTP 请求。
* 
* Parameters:
*	client				[In] 	HTTP 客户端句柄。由 ql_http_client_init()获取。
*	url					[In] 	HTTP 请求 URL。
*	method				[In] 	HTTP 请求方式。详见 QL_HTTP_CLIENT_OPT_E。
*	auth_type			[In] 	HTTP 请求验证类型。详见 QL_HTTP_CLIENT_AUTH_TYPE_E。
*	username 			[In] 	HTTP 请求验证使用的用户名。
*	password			[In] 	HTTP 请求验证使用的密码。
*	data				[In] 	HTTP 请求待发送数据。
*	data_len			[In] 	HTTP 请求待发送数据的长度。单位：字节。
*	rsp_cb				[In] 	HTTP 请求回调函数。详见 QL_HTTP_CLIENT_RESPONSE_CB。
*	rsp_cb_user_data	[In] 	传递至回调函数 QL_HTTP_CLIENT_RESPONSE_CB()的用户数据。
*
* Return:
*	无。
*
*****************************************************************/
extern QL_HTTP_CLIENT_ERR_E ql_http_client_request(
	QL_HTTP_CLIENT_T *client,
	char *url,
	QL_HTTP_CLIENT_REQUEST_METHOD_E method,
	QL_HTTP_CLIENT_AUTH_TYPE_E auth_type,
	char *username,
	char* password,
	char *data,
	int data_len,
	QL_HTTP_CLIENT_RESPONSE_CB rsp_cb,
	void *rsp_cb_user_data
);

/*****************************************************************
* Function: ql_http_client_list_append
*
* Description:
* 	该函数用于创建消息头列表或更新消息头列表。
* 
* Parameters:
*	list		[In] 	指针，指向消息头列表。设置为 NULL 时创建新的消息头列表；不为 NULL 时，向指定的消息头列表增加内容。
*	data		[In] 	消息头字符串，以“\r\n”结尾。例如：Connection: keep-alive\r\n。
*
* Return:
*	NULL，失败
*	非NULL，执行成功则返回消息头列表指针。
*
*****************************************************************/

extern QL_HTTP_CLIENT_LIST_T * ql_http_client_list_append(QL_HTTP_CLIENT_LIST_T * list, const char * data);

/*****************************************************************
* Function: ql_http_client_list_append
*
* Description:
* 	该函数用于销毁消息头列表以释放消息头列表资源。若当前有 HTTP 请求使用消息头列表、且请求尚未完成时，不可调用该函数销毁此消息头列表。
* 
* Parameters:
*	list		[In] 	指针，指向消息头列表。
*
* Return:
* 无。
*
*****************************************************************/
extern void ql_http_client_list_destroy(QL_HTTP_CLIENT_LIST_T *list);

/*****************************************************************
* Function: ql_http_client_setopt
*
* Description:
* 	该函数用于配置 HTTP 客户端属性。
* 
* Parameters:
*	client		[In] 	HTTP 客户端句柄。由 ql_http_client_init()获取。
*	tag			[In] 	属性标签，详见QL_HTTP_CLIENT_OPT_E。
*
* Return:
* 详见QL_HTTP_CLIENT_ERR_E。
*
*****************************************************************/
extern QL_HTTP_CLIENT_ERR_E ql_http_client_setopt(QL_HTTP_CLIENT_T *client, int tag, ...);


/*****************************************************************
* Function: ql_http_client_get_header
*
* Description:
* 	该函数用于获取 HTTP 消息头中指定键值的实际长度。
* 
* Parameters:
*	header		[In] 	 HTTP 消息头。
*	key			[In] 	HTTP 消息头中的键名。
*	index		[In] 	HTTP 客户端句柄。由 ql_http_client_init()获取。
*	value		[In] 	HTTP 消息头中指定的键值。
*	value_len	[In] 	指定键值的最大字节长度。单位：字节。
*
* Return:
*	0 消息头中不存在指定索引的键名。
*	大于 0 指定索引的键值的实际长度。单位：字节。

*
*****************************************************************/
extern int ql_http_client_get_header(char *header,char *key,int index,char *value,int value_len);



#ifdef __cplusplus
}
#endif

#endif


