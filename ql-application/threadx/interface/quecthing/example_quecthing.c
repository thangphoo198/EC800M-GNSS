/*================================================================
  Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/
/*************************************************************************
** 创建人 @author  : 吴健超 JCWu
** 版本   @version : V1.0.0 原始版本
** 日期   @date    :
** 功能   @brief   : 
** 硬件   @hardware：任何ANSI-C平台
** 其他   @other   ：
***************************************************************************/

#include "ql_application.h"
#include "ql_data_call.h"
#include "ql_rtos.h"
#include "sockets.h"

#include "Ql_iotApi.h"
#include "ql_log.h"

#define FUNCTION_ATTR_ROM
#define PRINTF_S64     "%lld"
#define HAL_STRSTR(a,b)          strstr((char*)a,(char*)b)
#define HAL_STRLEN(a)            ((NULL==a)?0:strlen((char*)a))
#define HAL_MEMSET               memset

#define QIOT_MQTT_REGISTER_URL "iot-south.quectel.com:1883"
#define QIOT_MQTT_PRODUCT_KEY "p11fQ6"
#define QIOT_MQTT_PRODUCT_SECRET "NEh1am9PWkNqbDRk"

#define QIOT_COAP_BOOTSTRAP_URL "coap://220.180.239.212:8416"
#define QIOT_COAP_PRODUCT_KEY "MXJac1VyQUV1emZj"
#define QIOT_COAP_PRODUCT_SECRET "NlZGU3JUR0pYRGlR"

#define QIOT_MCU_COMPONENT_NO "MCU"
#define QIOT_MCU_VERSION "1"

#define PROFILE_IDX 1
#define _BOOL2STR(X) ((X) ? "TRUE" : "FALSE") /* qbool 转字符串 */

static quint32_t Quos_stringSplit1(char *src, quint32_t srcLen, char **words, quint32_t maxSize, const char *delim, qbool keepEmptyParts)
{
	char *start = src;
	quint32_t num = 0;
	if (NULL == delim)
	{
		return 0;
	}
	quint32_t delimLen = HAL_STRLEN(delim);
	while (maxSize > num && src && (quint32_t)(src - start) < srcLen)
	{
		words[num] = src;
		src = HAL_STRSTR(src, delim);
		if (src)
		{
			HAL_MEMSET(src, 0, delimLen);
			src += delimLen;
		}
		if (keepEmptyParts || HAL_STRLEN(words[num]))
		{
			num++;
		}
	}
	return num;
}


static char *Quos_stringRemoveMarks1(char *strVal)
{
	quint32_t len = HAL_STRLEN(strVal);
	if ('"' == strVal[0] && '"' == strVal[len - 1])
	{
		quint32_t i;
		for (i = 0; i < len - 2; i++)
		{
			strVal[i] = strVal[i + 1];
		}
		strVal[len - 2] = 0;
	}
	return strVal;
}

static void ql_datacall_status_callback(int profile_idx, int status)
{
	printf("profile(%d) status: %d\r\n", profile_idx, status);
}

static int datacall_satrt(void)
{
	int i=0;
	printf("wait for network register done\r\n");

	while(i<10)
	{
		if(ql_network_register_wait(120) == 0)
		{
			break;
		}
		else 
		{
			i++;
		}
		
	}

	if(i>=10)
	{
		printf("*** network register fail ***\r\n");
		return 1;
	}
	
	printf("doing network activing ...\r\n");
	
	ql_wan_start(ql_datacall_status_callback);
	ql_set_auto_connect(1, TRUE);
	ql_start_data_call(1, 0, "3gnet.mnc001.mcc460.gprs", NULL, NULL, 0);

	return 0;
}

	/**************************************************************************
	** 功能	@brief : 物模型数据遍历
	** 输入	@param : 
	** 输出	@retval: 
	***************************************************************************/
	void Ql_iotTtlvHandle(const void *ttlvHead)
	{
		quint32_t count = Ql_iotTtlvCountGet(ttlvHead);
		quint32_t i;
		for(i=0;i<count;i++)
		{
			uint16_t id;
			QIot_dpDataType_e type;
			void *node = Ql_iotTtlvNodeGet(ttlvHead, i, &id, &type);
			if(node)
			{
				switch (type)
				{
				case QIOT_DPDATA_TYPE_BOOL:
				{
					qbool value;
					Ql_iotTtlvNodeGetBool(node, &value);
					printf("model id:%d data:%s\r\n",id,value?"TRUE":"FALSE");
					break;
				}
				case QIOT_DPDATA_TYPE_INT:
				{
					qint64_t num;
					Ql_iotTtlvNodeGetInt(node, &num);
					printf("model id:%d data:"PRINTF_S64"\r\n",id,num);
					break;
				}  
				case QIOT_DPDATA_TYPE_FLOAT:
				{
					double num;
					Ql_iotTtlvNodeGetFloat(node, &num);
					printf("model id:%d data:%lg\r\n",id,num);
					break;
				}				
				case QIOT_DPDATA_TYPE_BYTE:
				{
					quint8_t *value;
					quint32_t len = Ql_iotTtlvNodeGetByte(node, &value);
					printf("model id:%d data:%.*s\r\n",id,len,value);
					break;
				}
				case QIOT_DPDATA_TYPE_STRUCT:
					Ql_iotTtlvHandle(Ql_iotTtlvNodeGetStruct(node));
					break;
				default:
					break;
				}
			}
		}
	}


	/**************************************************************************
	** 功能	@brief : 事件处理回调
	** 输入	@param : 
	** 输出	@retval: 
	***************************************************************************/
	void Ql_iotEventCB(quint32_t event, qint32_t errcode, const void *value, quint32_t valLen)
	{
		printf("event[%d] errcode[%d] valLen[%d]\r\n", event, errcode, valLen);
		switch (event)
		{
		/* 引导认证操作 */
		case QIOT_ATEVENT_TYPE_AUTH:
			printf("auth event,code:%d\r\n",errcode);
			break;
		/* 接入操作 */
		case QIOT_ATEVENT_TYPE_CONN:
			printf("connect event,code:%d\r\n",errcode);
			break;
		/* 订阅操作 */
		case QIOT_ATEVENT_TYPE_SUBCRIBE:
		{
			printf("subcribe event,code:%d\r\n",errcode);
			/* 上报设备状态和模组信息 */
			quint16_t statusIds[] = {QIOT_DPID_STATUS_BATTERY,
										QIOT_DPID_STATUS_VOLTAGE,
										QIOT_DPID_STATUS_SIGNAL,
										QIOT_DPID_STATUS_FLASHFREE,
										QIOT_DPID_STATUS_RSRP,
										QIOT_DPID_STATUS_RSRQ,
										QIOT_DPID_STATUS_SNR};
			quint16_t infoIds[] = {QIOT_DPID_INFO_MODEL_TYPE,
									QIOT_DPID_INFO_MODEL_VER,
									QIOT_DPID_INFO_MCU_VER,
									QIOT_DPID_INFO_CELLID,
									QIOT_DPID_INFO_ICCID,
									QIOT_DPID_INFO_MCC,
									QIOT_DPID_INFO_MNC,
									QIOT_DPID_INFO_LAC,
									QIOT_DPID_INFO_PHONE_NUM,
									QIOT_DPID_INFO_SIM_NUM,
									QIOT_DPID_INFO_SDK_VER,
									QIOT_DPID_INFO_LOC_SUPLIST,
									QIOT_DPIO_INFO_DP_VER,
									QIOT_DPIO_INFO_CP_VER};
			Ql_iotCmdSysStatusReport(statusIds, sizeof(statusIds) / sizeof(statusIds[0]));
			Ql_iotCmdSysDevInfoReport(infoIds, sizeof(infoIds) / sizeof(infoIds[0]));
	#if 0
			/* 发送外部定位数据 */
			void *nmeaTtlv=NULL;
			Ql_iotTtlvIdAddString(&nmeaTtlv,0,"$GPGGA,042523.0,3413.610533,N,10854.063257,E,1,05,2.6,438.5,M,-28.0,M,,*78");
			Ql_iotTtlvIdAddString(&nmeaTtlv,0,"$GPRMC,042523.0,A,3413.610533,N,10854.063257,E,0.0,245.9,190716,0.0,E,A*0F");
			Ql_iotCmdBusLocReportOutside(nmeaTtlv);
			Ql_iotTtlvFree(&nmeaTtlv);
	#endif
			/* 发送内部定位数据 */
			printf("[zfw]data send event,code\r\n");
			void *titleTtlv = NULL;
			Ql_iotTtlvIdAddString(&titleTtlv, 0, "LBS");
			Ql_iotCmdBusLocReportInside(titleTtlv);
			Ql_iotTtlvFree(&titleTtlv);


	    Ql_iotSubDevConn("p11fSx", "dW9jU2FSTDh4M2gw", "869465050034003", NULL, 0, 30);
        Ql_iotSubDevHTB("p11fSx","869465050034003");
        void *ttlvHead = NULL;
        Ql_iotTtlvIdAddBool(&ttlvHead, 1, TRUE);
        Ql_iotTtlvIdAddInt(&ttlvHead, 2, 30);
        Ql_iotSubDevTslReport("p11fSx","869465050034003",ttlvHead);
        Ql_iotTtlvFree(&ttlvHead);
    
			/* ota 请求*/
			Ql_iotCmdOtaRequest(0);
			break;
		}
		/* 发送数据操作 */
		case QIOT_ATEVENT_TYPE_SEND:
			printf("data send event,code:%d\r\n",errcode);
			break;
		/* 接收数据操作 */
		case QIOT_ATEVENT_TYPE_RECV:
			printf("data recv event,code:%d\r\n",errcode);
			/* 收到透传数据 */
			if(QIOT_RECV_SUCC_TRANS == errcode)
			{
				printf("pass data:%.*s\r\n",valLen,(char *)value);
				/* 测试，把收到的透传数据回传到平台 */
				Ql_iotCmdBusPassTransSend(0,(unsigned char *)value,valLen);
			}
			/* 收到物模型下发数据 */
			else if(QIOT_RECV_SUCC_PHYMODEL_RECV == errcode)
			{
				/* 测试，把收到的物模型数据回传到平台 */
				Ql_iotCmdBusPhymodelReport(0,value);
				/* 物模型数据解析 */
				Ql_iotTtlvHandle(value);
			}
			/* 收到物模型请求数据 */
			else if(QIOT_RECV_SUCC_PHYMODEL_REQ == errcode && value)
			{
				quint16_t pkgId = *(quint16_t *)value;
				quint16_t *ids = (quint16_t *)((quint8_t*)value+sizeof(quint16_t));
				void *ttlvHead = NULL;
				printf("model read event,pkgid:%d\r\n",pkgId);
				quint32_t i;
				for(i=0;i<valLen;i++)
				{
					quint16_t modelId = ids[i];
					printf("modelId:%d\r\n",modelId);
					/* id1:bool id2:int id3:string id4:int array id5:string array*/
					switch (modelId)
					{
					case 1:
						Ql_iotTtlvIdAddBool(&ttlvHead, modelId, TRUE);
						break;
					case 2:
						Ql_iotTtlvIdAddInt(&ttlvHead, modelId, 1);
						break;
					case 3:
						Ql_iotTtlvIdAddString(&ttlvHead, modelId, "hello world");
						break;
					case 4:
						{
							void *ttlvArrayHead = NULL;
							Ql_iotTtlvIdAddInt(&ttlvArrayHead, 1, 1);
							Ql_iotTtlvIdAddInt(&ttlvArrayHead, 2, 2);
							Ql_iotTtlvIdAddInt(&ttlvArrayHead, 3, 3);
							Ql_iotTtlvIdAddStruct(&ttlvHead, modelId, ttlvArrayHead);
						}
						break;
					case 5:
						{
							void *ttlvArrayHead = NULL;
							Ql_iotTtlvIdAddString(&ttlvArrayHead, 1, "hello a");
							Ql_iotTtlvIdAddString(&ttlvArrayHead, 2, "hello b");
							Ql_iotTtlvIdAddString(&ttlvArrayHead, 3, "hello c");
							Ql_iotTtlvIdAddStruct(&ttlvHead, modelId, ttlvArrayHead);
						}
						break;
					default:
						break;
					}
				}
				Ql_iotCmdBusPhymodelAck(0, pkgId,ttlvHead);
				Ql_iotTtlvFree(&ttlvHead);
			}
			break;
		/* 注销操作 */
		case QIOT_ATEVENT_TYPE_LOGOUT:
			printf("logout event,code:%d\r\n",errcode);
			break;
		/* FOTA操作 */
		case QIOT_ATEVENT_TYPE_OTA:
		{
			switch (errcode)
			{
			/* 下发升级任务 */
			case QIOT_OTA_TASK_NOTIFY:
			{
				char *words[100];
				quint32_t count = Quos_stringSplit1((char *)value,HAL_STRLEN(value), words, sizeof(words) / sizeof(words[0]),",", FALSE);
				printf("recv ota task\r\n");
				if(count < 6)
				{
					break;
				}
				printf("componentNo:%s,sourceVersion:%s,targetVersion:%s,batteryLimit:%s,minSignalIntensity:%s,minSignalIntensity:%s\r\n",
					words[0],words[1],words[2],words[3],words[4],words[5]);
				Ql_iotCmdOtaAction(1);
				break;
			}
			/* 开始下载 */
			case QIOT_OTA_START:
				printf("ota download start\r\n");
				break;
			/* 下载中 */
			case QIOT_OTA_DOWNLOADING:
				printf("ota downloading\r\n");
				break;
			/* 下载完成 */
			case QIOT_OTA_DOWNLOADED:
			{
				char *words[100];
				quint32_t count = Quos_stringSplit1((char *)value,HAL_STRLEN(value), words, sizeof(words) / sizeof(words[0]),",", FALSE);
				printf("ota download complete\r\n");
				if(count < 4)
				{
					break;
				}
				printf("componentNo:%s,length:%s,startaddr:%s,piece_length:%s\r\n",words[0],words[1],words[2],words[3]);
				/* 如果是SOTA下载完成，则通过API读取文件 */
				if(strcmp(QIOT_MCU_COMPONENT_NO,Quos_stringRemoveMarks1(words[0])) == 0)
				{
					quint8_t readBuf[1024];
					quint32_t ret = Ql_iotCmdOtaMcuFWDataRead(0,readBuf,sizeof(readBuf));
					printf("sota read file...ret:%d\r\n",ret);
					/* SOTA完成后通知云平台MCU进入更新状态 */
					Ql_iotCmdOtaAction(3);
				}
				break;
			}
			/* 更新中 */
			case QIOT_OTA_UPDATING:
				printf("ota updating\r\n");
				break;
			/* 更新完成 */
			case QIOT_OTA_UPDATE_OK:
				printf("ota update success\r\n");
				break;
			/* 更新失败 */
			case QIOT_OTA_UPDATE_FAIL:
				printf("ota update fail\r\n");
				break;
			case QIOT_OTA_UPDATE_FLAG:
				if(((quint32_t *)value)[0] == 0)
				{
					printf("mutil devices confirm update\r\n");
				}
				else
					printf("mutil devices refuse update\r\n");
				break;	 
			default:
				break;
			}
			break;	
		}  
		/* 平台事件 */
		case QIOT_ATEVENT_TYPE_SERVER:
			printf("server event,code:%d\r\n",errcode);
			break; 
		default:
			break;
		}
	}
#ifdef QUEC_ENABLE_GATEWAY
/**************************************************************************
** 功能	@brief : 事件处理回调
** 输入	@param : 
** 输出	@retval: 
***************************************************************************/
void Ql_iotSubEventCB(quint32_t event, qint32_t errcode, const char *subPk, const char *subDk, const void *value, quint32_t valLen)
{
    printf("subPk[%s] subDk[%s] event[%d] errcode[%d] valLen[%d]\r\n", subPk, subDk, event, errcode, valLen);
    if (valLen)
    printf("value:%.*s\r\n", valLen, (char *)value);
}
#endif

/**************************************************************************
** 功能	@brief : 
** 输入	@param : 
** 输出	@retval: 
***************************************************************************/
int FUNCTION_ATTR_ROM quecthing_test(void)
{
	ql_log_mask_set(QL_LOG_APP_MASK,QL_LOG_PORT_USB);

    printf("---------quecting_test start v233333-------\r\n");
    printf("---------quecting_test start v33333-------\r\n");

    struct ql_data_call_info info = {0};
    char ip4_addr_str[16] = {0};
    datacall_satrt();
    ql_rtos_task_sleep_s(2);
    printf("[zfw]ql_get_data_call_info\r\n");
    ql_get_data_call_info(1, 0, &info);
    
    printf("info.profile_idx: %d\r\n", info.profile_idx);
    printf("info.ip_version: %d\r\n", info.ip_version);
    printf("info.v4.state: %d\r\n", info.v4.state);
    printf("info.v4.reconnect: %d\r\n", info.v4.reconnect);

    inet_ntop(AF_INET, &info.v4.addr.ip, ip4_addr_str, sizeof(ip4_addr_str));
    printf("info.v4.addr.ip: %s\r\n", ip4_addr_str);

    inet_ntop(AF_INET, &info.v4.addr.pri_dns, ip4_addr_str, sizeof(ip4_addr_str));
    printf("info.v4.addr.pri_dns: %s\r\n", ip4_addr_str);

    inet_ntop(AF_INET, &info.v4.addr.sec_dns, ip4_addr_str, sizeof(ip4_addr_str));
    printf("info.v4.addr.sec_dns: %s\r\n", ip4_addr_str);
    


    /* 初始化qucsdk */
    Ql_iotInit();

	//HTTP OTA TEST
	//Ql_iotHttpOtaReq(100, 1,"p1124c","NHJHeWcwSG00UlMw", "https://iot-gateway.quectel.com");
	
    /* 设置软件版本标识 */
   // Ql_iotConfigSetAppVersion("app");
    /* 注册事件回调函数 */
    Ql_iotConfigSetEventCB(Ql_iotEventCB);
    #ifdef QUEC_ENABLE_GATEWAY
    Ql_iotConfigSetSubDevEventCB(Ql_iotSubEventCB);
    #endif
    /* 配置产品信息*/
    Ql_iotConfigSetProductinfo(QIOT_MQTT_PRODUCT_KEY, QIOT_MQTT_PRODUCT_SECRET);
    /* 配置服务器信息，可选，默认连接MQTT生产环境服务器 */
    Ql_iotConfigSetServer(QIOT_PPROTOCOL_MQTT,QIOT_MQTT_REGISTER_URL);
    /* 配置PDP context Id，可选，默认为1 */
    Ql_iotConfigSetPdpContextId(1);
    /* 配置lifetime，可选，MQTT默认为120 */
    Ql_iotConfigSetLifetime(120);
    /* 配置外部MCU标识号和版本号，可选，如没有外部MCU则不需要配置 */
   // Ql_iotConfigSetMcuVersion(QIOT_MCU_COMPONENT_NO,QIOT_MCU_VERSION);
    /* 启动云平台连接 */
    Ql_iotConfigSetConnmode(QIOT_CONNMODE_REQ);


	ql_rtos_task_sleep_s(2);
    while (1)
    {
        QIot_state_e status = Ql_iotGetWorkState();
        printf("work status:%d",status);
        ql_rtos_task_sleep_s(100);
    }
}


//application_init(quecthing_test, "quecthing_test", 20, 100);

