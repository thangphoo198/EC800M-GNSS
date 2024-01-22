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
10/04/2022        Sharon.li        此文件查找AT相关的接口，同时调用客户在APP侧实现的AT，此文件在APP侧被编译
===========================================================================================================*/

#include "ql_type.h"
#include "ql_func.h"
#include "ql_error.h"
#include "ql_boot.h"
#include "ql_at_srv.h"
#include "ql_api_map_common.h"

//#define QL_APP_AT_EXAMPLE

extern utlAtCommand_T ql_at_srv_app_shell_cmds[];
extern int ql_at_srv_get_app_shell_cmds_num(void);

//此变量为APP侧变量
unsigned short gusXid = NUM_OF_TEL_ATP; //0 - 10 is reserved value


typedef void (* _api_ql_at_srv_set_app_shell_cmds_t)(utlAtCommand_T *shell_cmds,int num);
typedef int (*_api_atRespStr_t)(UINT32 reqHandle, UINT8 resultCode, UINT16 errCode, char *respString);
typedef BOOL (*_api_getExtString_t)( const utlAtParameterValue_P2c param_value_p,int index,CHAR *outString,INT16 maxStringLength,INT16 *outStringLength,CHAR *defaultString);
typedef BOOL (*_api_getExtValue_t)( const utlAtParameterValue_P2c param_value_p,int index,int *value_p,int minValue,int maxValue,int DefaultValue);

static _api_ql_at_srv_set_app_shell_cmds_t m_ql_at_srv_set_app_shell_cmds = NULL;
static _api_atRespStr_t m_atRespStr = NULL;
static _api_getExtString_t m_getExtString = NULL;
static _api_getExtValue_t m_getExtValue = NULL;

#if 0
void ql_app_get_kernel_gusXid(void)
{
	if(NULL == m_quec_at_srv_set_app_shell_cmds)
	{
		s32 ptr = m_get_api_ptr((char *)__FUNCTION__);
		if(0 == ptr)
		{
			SDK_API_DEBUG_NOTSUP();
			return ;
		}
		m_quec_at_srv_set_app_shell_cmds = (_api_quec_at_srv_set_app_shell_cmds_t)ptr;
	}
	m_quec_at_srv_set_app_shell_cmds(shell_cmds,num);
	return;
}
#endif


void ql_at_srv_set_app_shell_cmds(utlAtCommand_T *shell_cmds,int num)
{
	if(NULL == m_ql_at_srv_set_app_shell_cmds)
	{
		s32 ptr = m_get_api_ptr((char *)__FUNCTION__);
		if(0 == ptr)
		{
			SDK_API_DEBUG_NOTSUP();
			return ;
		}
		m_ql_at_srv_set_app_shell_cmds = (_api_ql_at_srv_set_app_shell_cmds_t)ptr;
	}
	m_ql_at_srv_set_app_shell_cmds(shell_cmds,num);
	return;
}

int atRespStr(UINT32 reqHandle, UINT8 resultCode, UINT16 errCode, char *respString)
{
	if(NULL == m_atRespStr)
	{
		s32 ptr = m_get_api_ptr((char *)__FUNCTION__);
		if(0 == ptr)
		{
			SDK_API_DEBUG_NOTSUP();
			return 0;
		}
		m_atRespStr = (_api_atRespStr_t)ptr;
	}
	return m_atRespStr(reqHandle,resultCode,errCode,respString);
}


BOOL getExtString ( const utlAtParameterValue_P2c param_value_p,
		int index,
		CHAR *outString,
		INT16 maxStringLength,
		INT16 *outStringLength,
		CHAR *defaultString)
{
	if(NULL == m_getExtString)
	{
		s32 ptr = m_get_api_ptr((char *)__FUNCTION__);
		if(0 == ptr)
		{
			SDK_API_DEBUG_NOTSUP();
			return 0;
		}
		m_getExtString = (_api_getExtString_t)ptr;
	}
	return m_getExtString(param_value_p,index,outString,maxStringLength,outStringLength,defaultString);
}


BOOL getExtValue( const utlAtParameterValue_P2c param_value_p,
                  int index,
                  int *value_p,
                  int minValue,
                  int maxValue,
                  int DefaultValue)
{
	if(NULL == m_getExtValue)
	{
		s32 ptr = m_get_api_ptr((char *)__FUNCTION__);
		if(0 == ptr)
		{
			SDK_API_DEBUG_NOTSUP();
			return 0;
		}
		m_getExtValue = (_api_getExtValue_t)ptr;
	}
	return m_getExtValue(param_value_p,index,value_p,minValue,maxValue,DefaultValue);
}

RETURNCODE_T HANDLE_RETURN_VALUE(UINT32 ret)
{
	return ((ret == CIRC_SUCCESS) ? utlSUCCESS : utlFAILED);
}


#ifdef QL_APP_AT_EXAMPLE //自定义AT命令示例


static utlAtParameter_T ql_app_at_test[] = {
	utlDEFINE_STRING_AT_PARAMETER(utlAT_PARAMETER_ACCESS_READ_WRITE, utlAT_PARAMETER_PRESENCE_REQUIRED),//AT命令SET操作时，参数1为字符串，必须携带
	utlDEFINE_STRING_AT_PARAMETER(utlAT_PARAMETER_ACCESS_READ_WRITE, utlAT_PARAMETER_PRESENCE_OPTIONAL),//AT命令SET操作时，参数2为字符串，可选
};
	
static utlAtParameter_T ql_app_at_test_ex[] = {
									//参数的属性                          //必须的参数
	utlDEFINE_DECIMAL_AT_PARAMETER(utlAT_PARAMETER_ACCESS_READ_WRITE,utlAT_PARAMETER_PRESENCE_REQUIRED),//AT命令SET操作时，参数1为十进制整数，必须携带
	utlDEFINE_STRING_AT_PARAMETER(utlAT_PARAMETER_ACCESS_READ_WRITE, utlAT_PARAMETER_PRESENCE_REQUIRED),//AT命令SET操作时，参数1为字符串，必须携带
	utlDEFINE_STRING_AT_PARAMETER(utlAT_PARAMETER_ACCESS_READ_WRITE, utlAT_PARAMETER_PRESENCE_OPTIONAL),//AT命令SET操作时，参数2为字符串，可选
};
RETURNCODE_T  ql_app_at_test_cmd
(
    const utlAtParameterOp_T        op,                  /* AT cmd type          */
    const char                     *command_name_p,      /* AT cmd name          */
    const utlAtParameterValue_P2c   parameter_values_p,  /* AT cmd value         */
    const size_t                    num_parameters,      /* AT cmd number        */
    const char                     *info_text_p,         /* AT cmd usage string  */
    unsigned int                   *xid_p,               /* AT cmd handle        */
    void                           *arg_p                /* AT cmd parser number */
)
{

	RETURNCODE_T    rc            	= INITIAL_RETURN_CODE;
	CiReturnCode    ret           	= CIRC_SUCCESS;
    UINT32 atHandle = MAKE_AT_HANDLE(*(TelAtParserID*)arg_p);
	*xid_p = atHandle;

	#define PARAM_STR_MAX_LEN 24
	char buf[128]={0};
	char *p=buf;
	char param_str[PARAM_STR_MAX_LEN] 	= {0};
	int param_str_len	=0;

	
	switch (op)
	{
		case TEL_EXT_GET_CMD:      /* AT+QLAPPTEST?  */
		    {
				sprintf(buf,"+QLAPPTEST:GET OK\r\n");
				ret = ATRESP(atHandle, ATCI_RESULT_CODE_OK, 0, buf); //输出AT命令执行结果
                break;
            }
		case TEL_EXT_SET_CMD:      /* AT+QLAPPTEST= */
            {
                if (getExtString(parameter_values_p, 0, param_str, PARAM_STR_MAX_LEN-1, &param_str_len, NULL)) //获取参数1的值赋值给param_str
                {
					p+=sprintf(p,"+QLAPPTEST:%s",param_str);
					if(getExtString(parameter_values_p, 1, param_str, PARAM_STR_MAX_LEN-1, &param_str_len, "default value")) //获取参数2的值赋值给param_str，若无参数2，赋默认值"default value"给param_str
					{
						p+=sprintf(p,",%s",param_str);
					}
					p+=sprintf(p,"\r\n");
					ret = ATRESP(atHandle, ATCI_RESULT_CODE_OK, 0, buf);
			    }
				else
				{
					ret = ATRESP(atHandle, ATCI_RESULT_CODE_CME_ERROR, CME_INVALID_PARAM, NULL);
				}
				break;
		    }
		case TEL_EXT_TEST_CMD:     /* AT+QLAPPTEST=? */
		case TEL_EXT_ACTION_CMD:
		default:
			{
				ret = ATRESP(atHandle, ATCI_RESULT_CODE_CME_ERROR, CME_OPERATION_NOT_SUPPORTED, NULL);
				break;
			}
	}
	rc = HANDLE_RETURN_VALUE(ret); /* handle the return value */
	return(rc);
}

#define PARAM_STR_MAX_LEN 24
int  para_date = 20200729;
char para_company_name[PARAM_STR_MAX_LEN]= "QUECTEL\0";
RETURNCODE_T  ql_app_at_test_cmd_ex
(
    const utlAtParameterOp_T        op,                  /* AT cmd type          */
    const char                     *command_name_p,      /* AT cmd name          */
    const utlAtParameterValue_P2c   parameter_values_p,  /* AT cmd value         */
    const size_t                    num_parameters,      /* AT cmd number        */
    const char                     *info_text_p,         /* AT cmd usage string  */
    unsigned int                   *xid_p,               /* AT cmd handle        */
    void                           *arg_p                /* AT cmd parser number */
)
{

	RETURNCODE_T    rc            	= INITIAL_RETURN_CODE;
	CiReturnCode    ret           	= CIRC_SUCCESS;
    UINT32 atHandle = MAKE_AT_HANDLE(*(TelAtParserID*)arg_p);
	*xid_p = atHandle;

	char buf[128]={0};
	char *p=buf;
	char param_str[PARAM_STR_MAX_LEN] 	= {0};
	int param_str_len	=0;
	
	#define DATE_MIN_VALUE 0
	#define DATA_MAX_VALUE 20201231

	
	switch (op)
	{
		case TEL_EXT_GET_CMD:      /* AT+QLAPPTESTEX?  */
		    {
				sprintf(buf,"+QLAPPTESTEX: %d-%s\r\n",para_date,para_company_name);
				ret = ATRESP(atHandle, ATCI_RESULT_CODE_OK, 0, buf); //输出AT命令执行结果
                break;
            }
		case TEL_EXT_SET_CMD:      /* AT+QLAPPTESTEX= */
            {
                if (getExtValue(parameter_values_p, 0, &para_date, DATE_MIN_VALUE, DATA_MAX_VALUE, para_date)) //获取参数1的值赋值给date
                {
					if(getExtString(parameter_values_p, 1, para_company_name, PARAM_STR_MAX_LEN-1, &param_str_len, NULL)) //获取参数2的值赋值给para_company_name
					{
						if(getExtString(parameter_values_p, 2, param_str, PARAM_STR_MAX_LEN-1, &param_str_len, "default value")) //获取参数3的值赋值给param_str，若无参数3，赋默认值"default value"给param_str
						{
							sprintf(buf,"%s",param_str);
						}
						ret = ATRESP(atHandle, ATCI_RESULT_CODE_OK, 0, buf);
					}
					else
						ret = ATRESP(atHandle, ATCI_RESULT_CODE_CME_ERROR, CME_INVALID_PARAM, NULL);//无效的参数
			    }
				else
					ret = ATRESP(atHandle, ATCI_RESULT_CODE_CME_ERROR, CME_INVALID_PARAM, NULL);
				break;
		    }
		case TEL_EXT_TEST_CMD:     /* AT+QLAPPTESTEX=? */
		case TEL_EXT_ACTION_CMD:
		default:
			{
				ret = ATRESP(atHandle, ATCI_RESULT_CODE_CME_ERROR, CME_OPERATION_NOT_SUPPORTED, NULL);
				break;
			}
	}

	rc = HANDLE_RETURN_VALUE(ret); /* handle the return value */
	return(rc);
}

RETURNCODE_T  ql_app_at_test_act_cmd
(
    const utlAtParameterOp_T        op,                  /* AT cmd type          */
    const char                     *command_name_p,      /* AT cmd name          */
    const utlAtParameterValue_P2c   parameter_values_p,  /* AT cmd value         */
    const size_t                    num_parameters,      /* AT cmd number        */
    const char                     *info_text_p,         /* AT cmd usage string  */
    unsigned int                   *xid_p,               /* AT cmd handle        */
    void                           *arg_p                /* AT cmd parser number */
)
{

	RETURNCODE_T    rc            	= INITIAL_RETURN_CODE;
	CiReturnCode    ret           	= CIRC_SUCCESS;
    UINT32 atHandle = MAKE_AT_HANDLE(*(TelAtParserID*)arg_p);
	*xid_p = atHandle;

	char buf[128]={0};

	switch (op)
	{
	
		case TEL_EXT_ACTION_CMD:
			{
				sprintf(buf,"+QLAPPTESTACT:ACT OK");
				ret = ATRESP(atHandle, ATCI_RESULT_CODE_OK, 0, buf);
				break;
			}
		case TEL_EXT_TEST_CMD:     /* AT+QLAPPTESTACT=? */
		case TEL_EXT_GET_CMD:      /* AT+QLAPPTESTACT?  */
		case TEL_EXT_SET_CMD:      /* AT+QLAPPTESTACT= */
		default:
			{
				ret = ATRESP(atHandle, ATCI_RESULT_CODE_CME_ERROR, CME_OPERATION_NOT_SUPPORTED, NULL);
				break;
			}
	}
	rc = HANDLE_RETURN_VALUE(ret); /* handle the return value */
	return(rc);
}

#endif //QL_APP_AT_EXAMPLE


typedef enum{
#ifdef QL_APP_AT_EXAMPLE //自定义AT命令示例
	QL_APP_AT_TEST,
	QL_APP_AT_TEST_EXACTION,
#endif //QL_APP_AT_EXAMPLE
	QL_APP_AT_TYPE_MAX_NUM
}QL_APP_AT_TYPE_E;

utlAtCommand_T ql_at_srv_app_shell_cmds[] = 
{
#ifdef QL_APP_AT_EXAMPLE //自定义AT命令示例
	utlDEFINE_EXTENDED_AT_COMMAND(QL_APP_AT_TEST, "+QLAPPTEST", ql_app_at_test, "+QLAPPTEST:OK",ql_app_at_test_cmd, ql_app_at_test_cmd),//AT+QLAPPTEST
	utlDEFINE_EXACTION_AT_COMMAND(QL_APP_AT_TEST_EXACTION, "+QLAPPTESTACT",  NULL,	"+QLAPPTESTACT:OK", ql_app_at_test_act_cmd),
	utlDEFINE_EXTENDED_AT_COMMAND(QL_APP_AT_TEST, "+QLAPPTESTEX", ql_app_at_test_ex, "+QLAPPTESTEX:OK",ql_app_at_test_cmd_ex, ql_app_at_test_cmd_ex),//AT+QLAPPTESTEX
#endif //QL_APP_AT_EXAMPLE
};

int ql_at_srv_get_app_shell_cmds_num(void)
{
	return sizeof(ql_at_srv_app_shell_cmds)/sizeof(utlAtCommand_T);
}

static void set_app_shell_cmds(void * argv)
{
	ql_at_srv_set_app_shell_cmds(ql_at_srv_app_shell_cmds,ql_at_srv_get_app_shell_cmds_num());
}

//此函数,让Kernel调用--set_app_shell_cmds()
user_boot_init(set_app_shell_cmds,1);



