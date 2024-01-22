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
	QL_HTTP_CLIENT_ERR_SUCCESS = 0,  //�ɹ�
	QL_HTTP_CLIENT_ERR_INVALID_CLIENT, //�����õ�http client���
	QL_HTTP_CLIENT_ERR_INVALID_METHOD, //�����õ�����ʽ
	QL_HTTP_CLIENT_ERR_INVALID_URL, //�����õ�����URL
	QL_HTTP_CLIENT_ERR_DNS_FAIL, //�Է���������DNS����ʧ��
	QL_HTTP_CLIENT_ERR_SOCK_CREATE_FAIL, //����socketʧ��
	QL_HTTP_CLIENT_ERR_SOCK_BIND_FAIL, //��socket����bind����ʧ��
	QL_HTTP_CLIENT_ERR_SOCK_CONN_FAIL, //ִ��socket����ʧ��
	QL_HTTP_CLIENT_ERR_SOCK_SEND_FAIL, //��������ʧ��
	QL_HTTP_CLIENT_ERR_SOCK_RECV_FAIL, //��������ʧ��
	QL_HTTP_CLIENT_ERR_SOCK_CLOSE_FAIL, //�Ͽ�����ʧ��
	QL_HTTP_CLIENT_ERR_SSL_CONN_FAIL, // SSL connect fail
	QL_HTTP_CLIENT_ERR_RESP_TIMEOUT, //����ʱ
	QL_HTTP_CLIENT_ERR_RESP_INVALID_VER, //�����õ�Э��汾
	QL_HTTP_CLIENT_ERR_RESP_INVALID_LOCATION, //�����õ�location��
	QL_HTTP_CLIENT_ERR_LAST_REQUEST_NOT_FINISH, //�ϴ�����δ���
	QL_HTTP_CLIENT_ERR_NO_MEMORY, //http ���󻺴治��
	QL_HTTP_CLIENT_ERR_UNKNOWN //��������
} QL_HTTP_CLIENT_ERR_E;

typedef enum
{
	QL_HTTP_CLIENT_EVENT_SEND_FAIL=0, //http ������ʧ��
	QL_HTTP_CLIENT_EVENT_SEND_SUCCESSED, //http �����ͳɹ�
	QL_HTTP_CLIENT_EVENT_RECV_HEADER_FAIL, //http ������Ӧheaderʧ�ܣ�header���ʧ��
	QL_HTTP_CLIENT_EVENT_RECV_HEADER_FINISHED, //http ������Ӧheader���
	QL_HTTP_CLIENT_EVENT_RECV_BODY, //http ��ʼ����body����
	QL_HTTP_CLIENT_EVENT_RECV_BODY_FINISHED, //http ����body�������
	QL_HTTP_CLIENT_EVENT_DISCONNECTED //�������Ͽ�����
} QL_HTTP_CLIENT_EVENT_E;



typedef enum {
	QL_HTTP_CLIENT_OPT_PROTOCOL_VER, //����http clientЭ��汾,0��http/1.0��1��http/1.1
	QL_HTTP_CLIENT_OPT_HTTPHEADER, //����http client�Զ���header,ql_http_client_list_append����������һ��header list
	QL_HTTP_CLIENT_OPT_PDP_CID, //����http clientʹ�õ�����ͨ��CID,ִ�����ݲ��Ų���ʱʹ�õ�CID
	QL_HTTP_CLIENT_OPT_BIND_PORT,//����http clientʹ�õĿͻ�������˿�
	QL_HTTP_CLIENT_OPT_ASYN, //����http client����ִ��ģʽ,0��ͬ����1���첽
	QL_HTTP_CLIENT_OPT_ENABLE_COOKIE, //ʹ��http clientʹ��cookie,0����ʹ��cookie��1��ʹ��cookie
	QL_HTTP_CLIENT_OPT_SSL_CTX, //����SSL 
	QL_HTTP_CLIENT_OPT_RECV_TIMEOUT_MS, //����http client�������ݵĳ�ʱʱ��(ms)
	QL_HTTP_CLIENT_OPT_HOSTFIELD_USEDPORT,    //����ָ����url�Ƿ�ʹ��Ĭ�ϵ�port ĳЩ�ͻ����Լ��ض���url�����ʹ��Ĭ�ϵ�port����head�ᱻ�������ܾ��Ͽ����ӡ�
}QL_HTTP_CLIENT_OPT_E;

typedef enum 
{
	QL_HTTP_CLIENT_REQUEST_GET, //GET����
	QL_HTTP_CLIENT_REQUEST_POST, //POST����
	QL_HTTP_CLIENT_REQUEST_MAX
}QL_HTTP_CLIENT_REQUEST_METHOD_E;

typedef enum 
{
	QL_HTTP_CLIENT_AUTH_TYPE_NONE=0, //��ʹ����֤
	QL_HTTP_CLIENT_AUTH_TYPE_BASE = 1, //ʹ��base��֤
	QL_HTTP_CLIENT_AUTH_TYPE_DIGEST=2 //ʹ��digest��֤
}QL_HTTP_CLIENT_AUTH_TYPE_E;

typedef enum 
{
	QL_HTTP_CLIENT_HTTP1_0=0, //http/1.0�汾Э��
	QL_HTTP_CLIENT_HTTP1_1 =1, //http/1.1�汾Э��
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
	QL_HTTP_SERVSER server; // ������Ϣ
	QL_HTTP_CLIENT_LIST_T * private_header; // �Զ�������header
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
    int bHostFieldUsedPort;       //1:ʹ��Ĭ�϶˿ڣ� 0:��ʹ��Ĭ�϶˿�
}QL_HTTP_CLIENT_T;

/*****************************************************************
* Function: QL_HTTP_CLIENT_RESPONSE_CB
*
* Description:
* 	���� HTTP ����󣬵�����¼�����ʱ�Զ����øûص�������
* 
* Parameters:
*	client			[In] 	HTTP �ͻ��˾������ ql_http_client_init()��ȡ��
*	event			[In] 	�ͻ��˵��� ql_http_client_request()�������¼����͡�����ε� 3.3.3.4�¡�
*	status_code		[In] 	HTTP �������˷��ص�״̬�롣�� event Ϊ���������¼�ʱ������״̬�룻�� event Ϊ�����¼�ʱ���ò���ʼ��Ϊ 0�����QL_HTTP_CLIENT_EVENT_E��
*							QL_HTTP_CLIENT_EVENT_RECV_HEADER_FINISHED��QL_HTTP_CLIENT_EVENT_RECV_BODY��QL_HTTP_CLIENT_EVENT_RECV_BODY_FINISHED��
*	data			[In] 	HTTP �ͻ��˽��յ������ݡ��� event Ϊ QL_HTTP_CLIENT_EVENT_RECV_HEADER_FINISHED���ò�����ʾ����������Ӧ����Ϣͷ��������Ϣͷ����
*							�� event Ϊ QL_HTTP_CLIENT_EVENT_RECV_BODY���ò�����ʾ�������˷��ص���Ϣ�����ݡ��� �� �� �� �� �� �� �� �� �� ��
*							�� �� �� �� �� �� �� �� һ �� �� �� �� �� Ϣ �� �� �� �� �� �� �� �� ��QL_HTTP_CLIENT_EVENT_RECV_BODY_FINISHED ���ɱ�ʾ������Ϣ�����ݽ�����ɡ�
*							�� event Ϊ�����¼�ʱ���ò���Ϊ NULL��
*	data_len		[In] 	�������ݵĳ��ȡ��� event Ϊ QL_HTTP_CLIENT_EVENT_RECV_HEADER_FINISHED���ò�����ʾ����������
*							Ӧ����Ϣͷ��������Ϣͷ���ĳ��ȡ���λ���ֽڡ��� event Ϊ QL_HTTP_CLIENT_EVENT_RECV_BODY��
*							�ò�����ʾ�������˷��ص���Ϣ�����ݵĳ��ȡ���λ���ֽڡ�
*							�� event Ϊ�����¼�ʱ���ò���Ϊ 0��
*	private_data	[In] 	�������ûص��������û����ݡ�
*
* Return:
*	0, ���ٽ��շ���˷������ݣ�����˷������ݽ���������
*	1, �������շ���˷������ݡ�
*
*****************************************************************/
typedef int (*QL_HTTP_CLIENT_RESPONSE_CB)(QL_HTTP_CLIENT_T *client,QL_HTTP_CLIENT_EVENT_E event,int status_code, char *data, int data_len, void *private_data);

/*****************************************************************
* Function: ql_http_client_init
*
* Description:
* 	�ú������ڳ�ʼ�� HTTP �ͻ�����Դ������һ���µ� HTTP �ͻ��˾����
* 
* Parameters:
* 	�ޡ�
*
* Return:
*	NULL��ʧ�ܡ�
*	��NULL���ɹ�������һ���µ� HTTP �ͻ��˾����
*
*****************************************************************/
extern QL_HTTP_CLIENT_T * ql_http_client_init(void);

/*****************************************************************
* Function: ql_http_client_release
*
* Description:
* 	�ú��������ͷ� HTTP �ͻ�����Դ��
* 
* Parameters:
*	client	  [in] 	HTTP �ͻ��˾������ ql_http_client_init()��ȡ��
*
* Return:
*	�ޡ�
*
*****************************************************************/
extern void ql_http_client_release(QL_HTTP_CLIENT_T *client);

/*****************************************************************
* Function: ql_http_client_request
*
* Description:
* 	�ú������ڷ��� HTTP ����
* 
* Parameters:
*	client				[In] 	HTTP �ͻ��˾������ ql_http_client_init()��ȡ��
*	url					[In] 	HTTP ���� URL��
*	method				[In] 	HTTP ����ʽ����� QL_HTTP_CLIENT_OPT_E��
*	auth_type			[In] 	HTTP ������֤���͡���� QL_HTTP_CLIENT_AUTH_TYPE_E��
*	username 			[In] 	HTTP ������֤ʹ�õ��û�����
*	password			[In] 	HTTP ������֤ʹ�õ����롣
*	data				[In] 	HTTP ������������ݡ�
*	data_len			[In] 	HTTP ������������ݵĳ��ȡ���λ���ֽڡ�
*	rsp_cb				[In] 	HTTP ����ص���������� QL_HTTP_CLIENT_RESPONSE_CB��
*	rsp_cb_user_data	[In] 	�������ص����� QL_HTTP_CLIENT_RESPONSE_CB()���û����ݡ�
*
* Return:
*	�ޡ�
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
* 	�ú������ڴ�����Ϣͷ�б�������Ϣͷ�б�
* 
* Parameters:
*	list		[In] 	ָ�룬ָ����Ϣͷ�б�����Ϊ NULL ʱ�����µ���Ϣͷ�б���Ϊ NULL ʱ����ָ������Ϣͷ�б��������ݡ�
*	data		[In] 	��Ϣͷ�ַ������ԡ�\r\n����β�����磺Connection: keep-alive\r\n��
*
* Return:
*	NULL��ʧ��
*	��NULL��ִ�гɹ��򷵻���Ϣͷ�б�ָ�롣
*
*****************************************************************/

extern QL_HTTP_CLIENT_LIST_T * ql_http_client_list_append(QL_HTTP_CLIENT_LIST_T * list, const char * data);

/*****************************************************************
* Function: ql_http_client_list_append
*
* Description:
* 	�ú�������������Ϣͷ�б����ͷ���Ϣͷ�б���Դ������ǰ�� HTTP ����ʹ����Ϣͷ�б���������δ���ʱ�����ɵ��øú������ٴ���Ϣͷ�б�
* 
* Parameters:
*	list		[In] 	ָ�룬ָ����Ϣͷ�б�
*
* Return:
* �ޡ�
*
*****************************************************************/
extern void ql_http_client_list_destroy(QL_HTTP_CLIENT_LIST_T *list);

/*****************************************************************
* Function: ql_http_client_setopt
*
* Description:
* 	�ú����������� HTTP �ͻ������ԡ�
* 
* Parameters:
*	client		[In] 	HTTP �ͻ��˾������ ql_http_client_init()��ȡ��
*	tag			[In] 	���Ա�ǩ�����QL_HTTP_CLIENT_OPT_E��
*
* Return:
* ���QL_HTTP_CLIENT_ERR_E��
*
*****************************************************************/
extern QL_HTTP_CLIENT_ERR_E ql_http_client_setopt(QL_HTTP_CLIENT_T *client, int tag, ...);


/*****************************************************************
* Function: ql_http_client_get_header
*
* Description:
* 	�ú������ڻ�ȡ HTTP ��Ϣͷ��ָ����ֵ��ʵ�ʳ��ȡ�
* 
* Parameters:
*	header		[In] 	 HTTP ��Ϣͷ��
*	key			[In] 	HTTP ��Ϣͷ�еļ�����
*	index		[In] 	HTTP �ͻ��˾������ ql_http_client_init()��ȡ��
*	value		[In] 	HTTP ��Ϣͷ��ָ���ļ�ֵ��
*	value_len	[In] 	ָ����ֵ������ֽڳ��ȡ���λ���ֽڡ�
*
* Return:
*	0 ��Ϣͷ�в�����ָ�������ļ�����
*	���� 0 ָ�������ļ�ֵ��ʵ�ʳ��ȡ���λ���ֽڡ�

*
*****************************************************************/
extern int ql_http_client_get_header(char *header,char *key,int index,char *value,int value_len);



#ifdef __cplusplus
}
#endif

#endif


