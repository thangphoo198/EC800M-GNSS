/*================================================================
  Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/


#ifndef __QL_FTP_CLIENT_H__
#define __QL_FTP_CLIENT_H__

#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif


#define MAX_FILE_NAME_SIZE		256
#define MAX_OWNER_SIZE		64


typedef enum
{
	QL_FTP_CLIENT_ERR_SUCCESS = 0,  //�ɹ�
	QL_FTP_CLIENT_ERR_INVALID_CLIENT, //�����õ�http client���
	QL_FTP_CLIENT_ERR_INVALID_HOST, //�����õ�����������ַ
	QL_FTP_CLIENT_ERR_DNS_FAIL, //�Է���������DNS����ʧ��
	QL_FTP_CLIENT_ERR_SOCK_CREATE_FAIL, //����socketʧ��
	QL_FTP_CLIENT_ERR_SOCK_BIND_FAIL, //��socket����bind����ʧ��
	QL_FTP_CLIENT_ERR_SOCK_CONN_FAIL, //ִ��socket����ʧ��
	QL_FTP_CLIENT_ERR_SOCK_SEND_FAIL, //��������ʧ��
	QL_FTP_CLIENT_ERR_SOCK_RECV_FAIL, //��������ʧ��
	QL_FTP_CLIENT_ERR_SOCK_CLOSE_FAIL, //�Ͽ�����ʧ��
	QL_FTP_CLIENT_ERR_SOCK_DISCONNECTED, //���ӶϿ�
	QL_FTP_CLIENT_ERR_SSL_CONN_FAIL, // SSL ����ʧ��
	QL_FTP_CLIENT_ERR_RESP_TIMEOUT, //����ʱ
	QL_FTP_CLIENT_ERR_CREATE_FILE_FAIL,//�����ļ�ʧ��
	QL_FTP_CLIENT_ERR_NO_FILE,//�ļ�������
	QL_FTP_CLIENT_ERR_NO_DIR,//Ŀ¼������
	QL_FTP_CLIENT_ERR_UNKNOWN, //��������
} QL_FTP_CLIENT_ERR_E;

typedef enum {
	QL_FTP_CLIENT_OPT_PDP_CID, //����ftp clientʹ�õ�����ͨ��CID,ִ�����ݲ��Ų���ʱʹ�õ�CID
	QL_FTP_CLIENT_OPT_SSL_CTX, //����SSL 
	QL_FTP_CLIENT_OPT_DAT_ADDR_TYPE,
}QL_FTP_CLIENT_OPT_E;


typedef struct{
	char filename[MAX_FILE_NAME_SIZE]; 	//�ļ���Ŀ¼��
	int type;							//���ͣ�0��δ֪��1��Ŀ¼��2���ļ�
	int permissions;					//Ȩ��
	int links;							//������
	char owner[MAX_OWNER_SIZE];			//�����û�
	char group[MAX_OWNER_SIZE];			//�����û���
	struct tm timestamp;				//����ʱ��
	unsigned long size;					//�ļ���С���ֽ�
}QL_FTP_CLIENT_FLIE_INFO_T;

/*****************************************************************
* Function: QL_FTP_CLIENT_WRITE_CB
*
* Description:
* 	ʹ�ûص��������մ�FTP��������ȡ���ļ����ݡ�
* 
* Parameters:
* 	data	  		[in] 	���յ������ݡ�
* 	data_len  		[in] 	���յ������ݳ��ȡ�
* 	user_data  		[in] 	�û�����
*
* Return:
* 	���� 0, �������պ������ݡ�
* 	0, ���ټ������պ������ݡ�
*
*****************************************************************/
typedef int(*QL_FTP_CLIENT_WRITE_CB)(unsigned char *data,int data_len,void*user_data);


/*****************************************************************
* Function: QL_FTP_CLIENT_READ_CB
*
* Description:
* 	ʹ�ûص������������ݵ�FTP��������
* 
* Parameters:
* 	data	  		[out] 	��Ҫ���͵����ݡ�
* 	data_len  		[out] 	�洢�������ݵ���󳤶ȡ�
* 	user_data  		[in] 	�û�����
*
* Return:
* 	���� 0��ʵ����Ҫ���͵����ݳ��ȡ�
*  	0��û����Ҫ���͵������ˡ�
*
*****************************************************************/
typedef int(*QL_FTP_CLIENT_READ_CB)(unsigned char *data,int data_len,void*user_data);


/*****************************************************************
* Function: ql_ftp_client_new
*
* Description:
* 	����ftp client �����
* 
* Parameters:
* 	��
*
* Return:
* 	��Ϊ NULL, ftp client �����
* 	NULL, ����ʧ�ܡ�
*
*****************************************************************/
void *ql_ftp_client_new(void);


/*****************************************************************
* Function: ql_ftp_client_release
*
* Description:
* 	�ͷ�ftp client��Դ��
* 
* Parameters:
* 	client	  		[in] 	ftp client �����
*
* Return:
* 	0���ɹ���
*  	-1��ʧ�ܡ�
*
*****************************************************************/
void ql_ftp_client_release(void *client);


/*****************************************************************
* Function: ql_ftp_client_setopt
*
* Description:
* 	����ftp client������ԡ�
* 
* Parameters:
* 	client	  		[in] 	ftp client �����
* 	tag	  			[in] 	���Ա�ǩ����QL_FTP_CLIENT_OPT_E��
* 	...	  			[in] 	���Բ�����
*							tagΪQL_FTP_CLIENT_OPT_PDP_CID�ǣ��˲���Ϊint�ͣ�ִ�����ݲ��Ų���ʱʹ�õ�CIDֵ��
*							tagΪQL_FTP_CLIENT_OPT_SSL_CTX�ǣ��˲���Ϊָ�룬SSL �����
*
* Return:
* 	0���ɹ���
*  	-1��ʧ�ܡ�
*
*****************************************************************/
int ql_ftp_client_setopt(void *client, QL_FTP_CLIENT_OPT_E tag, ...);


/*****************************************************************
* Function: ql_ftp_client_open
*
* Description:
* 	����ftp��������
* 
* Parameters:
* 	client	  		[in] 	ftp client �����
* 	hostname	  	[in] 	ftp ��������ַ��
* 	username	  	[in] 	�û�����
* 	password	  	[in] 	���롣
*
* Return:
* 	0���ɹ���
*  	-1��ʧ�ܡ�
*
*****************************************************************/
int ql_ftp_client_open(void *client,char *hostname,char *username,char *password);


/*****************************************************************
* Function: ql_ftp_client_close
*
* Description:
* 	�Ͽ���ftp�����������ӡ�
* 
* Parameters:
* 	client	  		[in] 	ftp client �����
*
* Return:
* 	0���ɹ���
*  	-1��ʧ�ܡ�
*
*****************************************************************/
int ql_ftp_client_close(void *client);


/*****************************************************************
* Function: ql_ftp_client_get
*
* Description:
* 	��ftp�����������ļ���
* 
* Parameters:
* 	client	  		[in] 	ftp client �����
* 	remotefile	  	[in] 	��Ҫ��ȡ��ftp���������ļ����ļ��������԰�����Ի����·����
* 	localfile	  	[in] 	�洢�����ص��ļ��������԰�����Ի����·�������ΪNULL�����ftp���������ļ�ͬ��������Ĭ��ʹ�õ�Ŀ¼ΪU:/��
* 	write_cb	  	[in] 	ʹ�ûص��������մ�FTP��������ȡ���ļ����ݡ�
* 	user_data	  	[in] 	�û����ݡ�
*
* Return:
* 	0���ɹ���
*  	-1��ʧ�ܡ�
*
*****************************************************************/
int ql_ftp_client_get(void *client,char *remotefile,char *localfile,QL_FTP_CLIENT_WRITE_CB write_cb,void* user_data);


/*****************************************************************
* Function: ql_ftp_client_put
*
* Description:
* 	�ϴ������ļ�����������
* 
* Parameters:
* 	client	  		[in] 	ftp client �����
* 	localfile	  	[in] 	��Ҫ�ϴ��ı����ļ��������԰�����Ի����·��������Ĭ��ʹ�õ�Ŀ¼ΪU:/��
* 	remotefile	  	[in] 	�洢��ftp���������ļ����ļ��������԰�����Ի����·�������ΪNULL����ͱ����ļ�ͬ����
* 	read_cb	  		[in] 	ʹ�ûص������������ݵ�FTP����������������˴˻ص�������localfile������Ч��remotefile�����������á�
* 	user_data	  	[in] 	�û����ݡ�
*
* Return:
* 	0���ɹ���
*  	-1��ʧ�ܡ�
*
*****************************************************************/
int ql_ftp_client_put(void *client,char *localfile,char *remotefile,QL_FTP_CLIENT_READ_CB read_cb,void* user_data);


/*****************************************************************
* Function: ql_ftp_client_delete
*
* Description:
* 	ɾ��ftp���������ļ���
* 
* Parameters:
* 	client	  		[in] 	ftp client �����
* 	remotefile	  	[in] 	��Ҫɾ����ftp���������ļ����ļ��������԰�����Ի����·����
*
* Return:
* 	0���ɹ���
*  	-1��ʧ�ܡ�
*
*****************************************************************/
int ql_ftp_client_delete(void *client,char *remotefile);


/*****************************************************************
* Function: ql_ftp_client_cwd
*
* Description:
* 	����ftp��������ǰʹ�õ�Ŀ¼��
* 
* Parameters:
* 	client	  		[in] 	ftp client �����
* 	path	  		[in] 	ftp������Ŀ¼����������Ի����·����
*
* Return:
* 	0���ɹ���
*  	-1��ʧ�ܡ�
*
*****************************************************************/
int ql_ftp_client_cwd(void *client, char *path);


/*****************************************************************
* Function: ql_ftp_client_lcwd
*
* Description:
* 	���ı��ص�ǰʹ�õ�Ŀ¼��
* 
* Parameters:
* 	client	  		[in] 	ftp client �����
* 	path	  		[in] 	����Ŀ¼����������Ի����·����
*
* Return:
* 	0���ɹ���
*  	-1��ʧ�ܡ�
*
*****************************************************************/
int ql_ftp_client_lcwd(void *client, char *path);


/*****************************************************************
* Function: ql_ftp_client_pwd
*
* Description:
* 	��ȡftp��������ǰʹ�õ�Ŀ¼��
* 
* Parameters:
* 	client	  		[in] 	ftp client �����
* 	path	  		[out] 	ftp������Ŀ¼������·����
*	path_len		[in]	path�����洢���ȡ�
*
* Return:
* 	0���ɹ���
*  	-1��ʧ�ܡ�
*
*****************************************************************/
int ql_ftp_client_pwd(void *client, char *path, int path_len);


/*****************************************************************
* Function: ql_ftp_client_lpwd
*
* Description:
* 	��ȡ���ص�ǰʹ�õ�Ŀ¼��
* 
* Parameters:
* 	client	  		[in] 	ftp client �����
* 	path	  		[out] 	����Ŀ¼������·����
*	path_len		[in]	path�����洢���ȡ�
*
* Return:
* 	0���ɹ���
*  	-1��ʧ�ܡ�
*
*****************************************************************/
int ql_ftp_client_lpwd(void *client, char *path, int path_len);


/*****************************************************************
* Function: ql_ftp_client_mkdir
*
* Description:
* 	��ftp���������½�Ŀ¼��
* 
* Parameters:
* 	client	  		[in] 	ftp client �����
* 	path	  		[in] 	��Ҫ�½���ftp������Ŀ¼����������Ի����·����
*
* Return:
* 	0���ɹ���
*  	-1��ʧ�ܡ�
*
*****************************************************************/
int ql_ftp_client_mkdir(void *client, char *path);


/*****************************************************************
* Function: ql_ftp_client_rmdir
*
* Description:
* 	ɾ��ftp�������ϵ�Ŀ¼��
* 
* Parameters:
* 	client	  		[in] 	ftp client �����
* 	path	  		[in] 	��Ҫɾ����ftp������Ŀ¼����������Ի����·����
*
* Return:
* 	0���ɹ���
*  	-1��ʧ�ܡ�
*
*****************************************************************/
int ql_ftp_client_rmdir(void *client, char *path);


/*****************************************************************
* Function: ql_ftp_client_list
*
* Description:
* 	��ȡָ��ftp��������Ŀ¼���ļ���Ŀ¼�б�
* 
* Parameters:
* 	client	  		[in] 	ftp client �����
* 	path_or_file	[in] 	ftp�������ϵ�Ŀ¼���ļ�����������Ի����·����
* 	match			[in] 	ֻ�г�����match�ַ��Ľ����
* 	file_info_list	[out] 	��ȡ�����ļ���Ŀ¼�б�
* 	max_file_num	[in] 	file_info_list���Դ洢�������������
*
* Return:
* 	����0��ʵ�ʻ�ȡ���Ľ��������
*  	-1��ʧ�ܡ�
*
*****************************************************************/
int ql_ftp_client_list(void *client, char *path_or_file,char *match,QL_FTP_CLIENT_FLIE_INFO_T *file_info_list, int max_file_num);


/*****************************************************************
* Function: ql_ftp_client_get_error_code
*
* Description:
* 	��ȡ��ǰ����ִ�еĴ����롣
* 
* Parameters:
* 	client	  		[in] 	ftp client �����
*
* Return:
* 	����100��Ϊftp���������ص���Ӧ�롣
*  	С��100��Ϊ����ִ�еĴ����룬��QL_FTP_CLIENT_ERR_E��
*
*****************************************************************/
int ql_ftp_client_get_error_code(void *client);

#ifdef __cplusplus
}
#endif

#endif
