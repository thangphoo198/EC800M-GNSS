/*==========================================================================================================
  Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
===========================================================================================================*/


#ifndef _QL_AT_SRV_H_
#define _QL_AT_SRV_H_

#include "ql_type.h"



#define utlSUCCESS  0
#define utlFAILED  -1


typedef enum
{
   TEL_AT_CMD_ATP_0,       
   TEL_AT_CMD_ATP_1,      
   TEL_AT_CMD_ATP_2,      
   TEL_AT_CMD_ATP_3,      
   TEL_AT_CMD_ATP_4,      
   TEL_AT_CMD_ATP_5,      
   TEL_AT_CMD_ATP_6,      
   TEL_AT_CMD_ATP_7,              
//   TEL_ESP_AT_CMD_ATP,          //external serial port
   TEL_MODEM_AT_CMD_ATP,   // act as Modem when linked with PC
   NUM_OF_TEL_ATP
}
TelAtParserID;


/* CI Shell API return code */
//ICAT EXPORTED ENUM
typedef enum CIRC {
    CIRC_SUCCESS=0,
    CIRC_FAIL,
    CIRC_INTERLINK_FAIL, /* the link between application subsystem and communication subsystem is broken */
    CIRC_SH_NULL_CONFIRM_CB,
    CIRC_SH_NULL_FREEREQMEM_CB,
    CIRC_SH_INVALID_HANDLE,
    CIRC_SH_INVALID_OPER,
    CIRC_SH_NULL_REQPARAS,
    CIRC_SG_INVALID_HANDLE,
    CIRC_SG_RESERVED_PRIMID,
    CIRC_SG_NULL_REQPARAS,
    CIRC_SG_NULL_RSPPARAS,
    CIRC_NUM_RESCODES
} _CiReturnCode;

typedef UINT16 CiReturnCode; 

typedef enum ATCI_CME_ERROR
{
	CME_PHONE_FAILURE	  =0,	  //phone failure
	CME_NO_CONNECTION	  =1,	  //no connection to phone
	CME_PHONE_ADP_LINK_RSVD 	=2,   //phone adaptor link reserved
	CME_OPERATION_NOT_ALLOWED	  =3,	  //operation not allowed
	CME_OPERATION_NOT_SUPPORTED 	=4,   //operation not supported
	CME_PH_SIM_PIN_REQUIRED 	=5,   //PH SIM PIN required
	CME_PH_FSIM_PIN_REQUIRED	 =6,	  //PH-FSIM PIN required
	CME_PH_FSIM_PUK_REQUIRED	 =7,	  //PH-FSIM PUK required
	CME_NO_SIM	   =10, //SIM not inserted
	CME_SIM_PIN_REQUIRED	 =11,	//SIM PIN required
	CME_SIM_PUK_REQUIRED	 =12,	//SIM PUK required
	CME_SIM_FAILURE 	=13,	//SIM failure
	CME_SIM_BUSY	 =14,	//SIM busy
	CME_SIM_WRONG	  =15,	//SIM wrong
	CME_INCORRECT_PASSWD	 =16,	//incorrect password
	CME_SIM_PIN2_REQUIRED	  =17,	//SIM PIN2 required
	CME_SIM_PUK2_REQUIRED	  =18,	//SIM PUK2 required
	CME_MEMORY_FULL 	=20,	//memory full
	CME_INVALID_INDEX	  =21,	//invalid index
	CME_NOT_FOUND	  =22,	//not found
	CME_MEMORY_FAILURE	   =23, //memory failure
	CME_TEXT_STRING_TOO_LONG	 =24,	//text string too long
	CME_INVALID_CHAR_IN_STRING	   =25, //invalid characters in text string
	CME_DAIL_STRING_TOO_LONG	 =26,	//dial string too long
	CME_INVALID_CHAR_IN_DIAL_STRING 	=27,	//invalid characters in dial string
	CME_NO_NW_SERVICE	  =30,	//no network service
	CME_NW_TIMEOUT	   =31, //network timeout
	CME_NW_NOT_ALLOWED	   =32, //network not allowed - emergency calls only
	CME_NW_PIN_REQUIRED 	=40,	//network personalization PIN required
	CME_NW_PUK_REQUIRED 	=41,	//network personalization PUK required
	CME_NW_SUB_PIN_REQUIRED 	=42,	//network subset personalization PIN required
	CME_NW_SUB_PUK_REQUIRED 	=43,	//network subset personalization PUK required
	CME_SP_PIN_REQUIRED 	=44,	//service provider personalization PIN required
	CME_SP_PUK_REQUIRED 	=45,	//service provider personalization PUK required
	CME_CP_PIN_REQUIRED 	=46,	//corporate personalization PIN required
	CME_CP_PUK_REQUIRED 	=47,	//corporate personalization PUK required
	CME_HD_KEY_REQUIRED 	=48,	//hidden key required 
	CME_INVALID_PARAM		= 50,   //Invalid Param
	CME_UNKNOWN 	=100,	//unknown		   
	CME_ILLEGAL_MS	   =103,	//Illegal MS (#3)
	CME_ILLEGAL_ME	   =106,	//Illegal ME (#6)
	CME_GPRS_NOT_ALLOWED	 =107,	//GPRS services not allowed (#7)
	CME_PLMN_NOT_ALLOWED	 =111,	//PLMN not allowed (#11)
	CME_LA_NOT_ALLOWED	   =112,	//Location area not allowed (#12)
	CME_ROAMING_NOT_ALLOWED 	=113,	//Roaming not allowed in this location area (#13)
	CME_SERVICE_OP_NOT_SUPPORTED	 =132,	//service option not supported (#32)
	CME_SERVICE_OP_NOT_SUBSCRIBED	  =133, //requested service option not subscribed (#33)
	CME_SERVICE_OP_OUT_OF_ORDER 	=134,	//service option temporarily out of order (#34)
	CME_PDP_AUTH_FAILURE	 =149,	//PDP authentication failure
	CME_INVALID_MOBILE_CLASS	 =150,	//invalid mobile class
	CME_UNSPECIFIED_GPRS_ERR	=148,	//unspecified GPRS error
	
	CMS_ME_FAILURE =300,	//ME failure
	CMS_SMS_SERVICE_RESV =301,	//SMS service of ME reserved
	CMS_OPERATION_NOT_ALLOWED =302,	//operation not allowed
	CMS_OPERATION_NOT_SUPPORTED =303,	//operation not supported
	CMS_INVALID_PDU_MODE_PARA =304,	//invalid PDU mode parameter
	CMS_INVALID_TEXT_MODE_PARA =305,	//invalid text mode parameter
	CMS_NO_SIM =310,	//(U)SIM not inserted
	CMS_SIM_PIN_REQUIRED =311,	//(U)SIM PIN required
	CMS_PH_SIM_PIN_REQUIRED =312,	//PH-(U)SIM PIN required
	CMS_SIM_FAILURE =313,	//(U)SIM failure
	CMS_SIM_BUSY =314,	//(U)SIM busy
	CMS_SIM_WRONG =315,	//(U)SIM wrong
	CMS_SIM_PUK_REQUIRED =316,	//(U)SIM PUK required
	CMS_SIM_PIN2_REQUIRED =317,	//(U)SIM PIN2 required
	CMS_SIM_PUK2_REQUIRED =318,	//(U)SIM PUK2 required
	CMS_MEMORY_FAILURE =320,	//memory failure
	CMS_INVALID_MEMORY_INDEX =321,	//invalid memory index
	CMS_MEMORY_FULL =322,	//memory full
	CMS_SMSC_ADDR_UNKNOWN =330,	//SMSC address unknown
	CMS_NO_NW_SERVICE =331,	//no network service
	CMS_NW_TIMEOUT =332,	//network timeout
	CMS_NO_CNMA_ACK_EXPECTED =340,	//no +CNMA acknowledgement expected
	CMS_UNKNOWN_ERROR =500,	//unknown error
											 
}_AtciCmeError;

typedef UINT16 AtciCmeError; 

typedef enum ATCI_RESULT_CODE
{
	ATCI_RESULT_CODE_NULL, //Timer will not stop
	ATCI_RESULT_CODE_OK,   //Timer will stop, OK will be sent
	ATCI_RESULT_CODE_ERROR, //Timer will stop, ERROR will be sent
	ATCI_RESULT_CODE_CME_ERROR, //Timer will Stop, CME ERROR will be sent
	ATCI_RESULT_CODE_CMS_ERROR, //Timer will Stop, CMS ERROR will be sent
	ATCI_RESULT_CODE_SUPPRESS,       //Timer will Stop, End of AT response without OK or ERROR string
}_AtciResultCode;





#define TEL_INVALID_EXT_CMD 	utlAT_PARAMETER_OP_UNKNOWN
#define TEL_EXT_EXEC_CMD 		utlAT_PARAMETER_OP_EXEC 	//AT+CGMI
#define TEL_EXT_GET_CMD 		utlAT_PARAMETER_OP_GET	   	//?
#define TEL_EXT_SET_CMD 		utlAT_PARAMETER_OP_SET	   	//=
#define TEL_EXT_ACTION_CMD 		utlAT_PARAMETER_OP_ACTION  	//AT+CPAS
#define TEL_EXT_TEST_CMD 		utlAT_PARAMETER_OP_SYNTAX	//=?

#define INITIAL_RETURN_CODE	utlFAILED



#define utlDEFINE_DECIMAL_AT_PARAMETER(     access, presence) {utlAT_DATA_TYPE_DECIMAL    , access, presence}
#define utlDEFINE_STRING_AT_PARAMETER(      access, presence) {utlAT_DATA_TYPE_STRING     , access, presence}














typedef int   utlReturnCode_T, *utlReturnCode_P;

typedef unsigned short MATCmdType;

typedef enum {
    utlAT_PARAMETER_PRESENCE_OPTIONAL,  /* parameter presence is optional */
    utlAT_PARAMETER_PRESENCE_REQUIRED,  /* parameter presence is required */
} utlAtParameterPresence_T;

typedef enum {
    utlAT_DATA_TYPE_DECIMAL,
    utlAT_DATA_TYPE_HEXADECIMAL,
    utlAT_DATA_TYPE_BINARY,
    utlAT_DATA_TYPE_STRING,   /* string double-quotes are optional */
    utlAT_DATA_TYPE_QSTRING,  /* string double-quotes are required */
    utlAT_DATA_TYPE_DIAL_STRING,
} utlAtDataType_T;

typedef enum {
    utlAT_PARAMETER_ACCESS_READ_WRITE,  /* reads and writes  are permitted    */
    utlAT_PARAMETER_ACCESS_READ,        /* attempts to write are ignored      */
    utlAT_PARAMETER_ACCESS_READ_ONLY,   /* attempts to write generates errors */
    utlAT_PARAMETER_ACCESS_WRITE_ONLY   /* attempts to read  generates errors */
} utlAtParameterAccess_T;

typedef enum {
    utlAT_COMMAND_TYPE_BASIC,    /* basic AT command              */
    utlAT_COMMAND_TYPE_EXTENDED, /* extended-parameter AT command */
    utlAT_COMMAND_TYPE_EXACTION  /* extended-action    AT command */
} utlAtCommandType_T;

typedef union utlAtDataValue_U {
    unsigned int  decimal;
    unsigned int  hexadecimal;
    unsigned int  binary;
    char         *string_p;
    char         *qstring_p;
    char         *dial_string_p;
} utlAtDataValue_T, *utlAtDataValue_P;

typedef struct utlAtParameter_S {
    utlAtDataType_T          type;  /* parameter's data type */
    utlAtParameterAccess_T   access;
    utlAtParameterPresence_T presence;
}             utlAtParameter_T, *utlAtParameter_P;

/*--- parameter operations ---*/
typedef enum {
    utlAT_PARAMETER_OP_UNKNOWN,
    utlAT_PARAMETER_OP_EXEC,
    utlAT_PARAMETER_OP_GET,
    utlAT_PARAMETER_OP_SET,
    utlAT_PARAMETER_OP_ACTION,
    utlAT_PARAMETER_OP_SYNTAX
} utlAtParameterOp_T, *utlAtParameterOp_P;

typedef struct utlAtParameterValue_S {
    utlAtDataType_T        type;        /* data type of `value' */
    utlAtParameterAccess_T access;
    bool                   is_default;  /* is `value' set to the default value? */
    utlAtDataValue_T       value;       /* parameter's value                    */
}             utlAtParameterValue_T, *utlAtParameterValue_P;

typedef const utlAtParameterValue_T  *utlAtParameterValue_P2c;

typedef utlReturnCode_T (*utlAtCommandSyntaxFunction_P)     (const utlAtParameterOp_T op, const char *command_name_p, const utlAtParameterValue_P2c parameter_values_p, const size_t num_parameters,const char *info_text_p, unsigned int *xid_p, void *arg_p);
typedef utlReturnCode_T (*utlAtGetParameterFunction_P)      (const utlAtParameterOp_T op, const char *command_name_p, const utlAtParameterValue_P2c parameter_values_p, const size_t num_parameters, const char *info_text_p, unsigned int *xid_p, void *arg_p);
typedef utlReturnCode_T (*utlAtSetParameterFunction_P)      (const utlAtParameterOp_T op, const char *command_name_p, const utlAtParameterValue_P2c parameter_values_p, const size_t num_parameters, const char *info_text_p, unsigned int *xid_p, void *arg_p);

typedef struct utlAtCommand_S {
	MATCmdType mat_cmd;			 /* MAT command type */
    utlAtCommandType_T  type;    /* AT-Command type */
    const char         *name_p;  /* AT-Command name */

    utlAtParameter_P parameters_p;    /* NULL pointer, or pointer to a variable-length array      */
    size_t           num_parameters;  /* number of elements in array pointed to by `parameters_p' */

    struct {
        const char *command_syntax_p;  /* AT-Command usage string (for syntax queries) */
        struct {
            utlAtCommandSyntaxFunction_P command_syntax_function_p;
        } call_backs;
    } usage;

    struct {
        utlAtGetParameterFunction_P get_parameter_function_p;  /* for get requests          */
        utlAtSetParameterFunction_P set_parameter_function_p;  /* for set & action requests */
    } call_backs;
}             utlAtCommand_T, *utlAtCommand_P;

#define RETURNCODE_T utlReturnCode_T


#define utlDEFINE_BASIC_AT_COMMAND(mtype, name, parameters_p,exec_function_p)	\
		{mtype, utlAT_COMMAND_TYPE_BASIC,name,parameters_p,		\
		sizeof(parameters_p)/sizeof(utlAtParameter_T), 		\
		{NULL  , {NULL}}, {NULL,exec_function_p}}

#define utlDEFINE_EXTENDED_AT_COMMAND(mtype, name,parameters_p,syntax,get_function_p, set_function_p) \
		{mtype, utlAT_COMMAND_TYPE_EXTENDED, name, parameters_p, 	\
		sizeof(parameters_p)/sizeof(utlAtParameter_T), 		\
		{syntax, {NULL}},{get_function_p,set_function_p}}

#define utlDEFINE_EXACTION_AT_COMMAND(mtype, name,parameters_p, syntax,action_function_p) \
		{mtype, utlAT_COMMAND_TYPE_EXACTION, name, parameters_p, 	\
		sizeof(parameters_p)/sizeof(utlAtParameter_T), 		\
		{syntax, {NULL}}, {NULL, action_function_p}}


extern unsigned short gusXid;


#define MAKE_AT_HANDLE( sAtpIndex )								\
		(UINT32)(														\
			(													  \
				( (UINT32)sAtpIndex << 13)	 & 0x000FE000		   \
			)													  \
			|														\
			(														\
				( (UINT32)sAtpIndex>35? 0x40000000:0x0) 		\
			)														\
			|														\
			(														  \
				( (gusXid == 0x1fff)? gusXid=11 : ++gusXid) 						\
			)														  \
			)
	
	
#define GET_ATP_INDEX( atHandle ) ( (atHandle >> 13 ) & 0x7F )







#define ATRESP(REQHANDLE, RESULTCODE, ERRCODE, RESPSTRING) atRespStr( REQHANDLE, RESULTCODE, ERRCODE, RESPSTRING )


int atRespStr(UINT32 reqHandle, UINT8 resultCode, UINT16 errCode, char *respString);
//获取AT命令的参数，字符串
BOOL getExtString ( const utlAtParameterValue_P2c param_value_p,
		int index,
		CHAR *outString,
		INT16 maxStringLength,
		INT16 *outStringLength,
		CHAR *defaultString);

//获取AT命令的参数，整形
//获取成功返回TRUE,否则FALSE
BOOL getExtValue( const utlAtParameterValue_P2c param_value_p,
                  int index,
                  int *value_p,
                  int minValue,		//此参数的最小值
                  int maxValue,		//此参数的最大值
                  int DefaultValue);//此参数的默认值

//设置app侧自定义AT指令的cmds
void ql_at_srv_set_app_shell_cmds(utlAtCommand_T *shell_cmds,int num);


#endif


