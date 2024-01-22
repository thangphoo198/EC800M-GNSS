#ifndef __QIOT_API_H__
#define __QIOT_API_H__
#ifndef __QTH_TEST__ /* open方案对外提供头文件时不需要定义 */
#include "Quos_kernel.h"
#else
#include "string.h"
#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"

#define quint8_t uint8_t
#define qint8_t int8_t
#define quint16_t uint16_t
#define qint16_t int16_t
#define quint32_t uint32_t
#define qint32_t int32_t
#define quint64_t uint64_t
#define qint64_t int64_t
#define pointer_t unsigned long int
typedef enum
{
    FALSE = 0,
    TRUE = 1
} qbool;

typedef struct Quos_cJSON
{
    /* next/prev allow you to walk array/object chains. Alternatively, use GetArraySize/GetArrayItem/GetObjectItem */
    struct Quos_cJSON *next;
    struct Quos_cJSON *prev;
    /* An array or object item will have a child pointer pointing to a chain of the items in the array/object. */
    struct Quos_cJSON *child;

    /* The type of the item, as above. */
    int type;

    /* The item's string, if type==QUOS_cJSON_String  and type == QUOS_cJSON_Raw */
    char *valuestring;
    /* writing to valueint is DEPRECATED, use Quos_cJSON_SetNumberValue instead */
    int valueint;
    /* The item's number, if type==QUOS_cJSON_Number */
    double valuedouble;

    /* The item's name string, if this item is the child of, or is in the list of subitems of an object. */
    char *string;
} Quos_cJSON;

#endif
enum
{
    QIOT_ATEVENT_TYPE_AUTH = 1,
    QIOT_ATEVENT_TYPE_CONN = 2,
    QIOT_ATEVENT_TYPE_SUBCRIBE = 3,
    QIOT_ATEVENT_TYPE_SEND = 4,
    QIOT_ATEVENT_TYPE_RECV = 5,
    QIOT_ATEVENT_TYPE_LOGOUT = 6,
    QIOT_ATEVENT_TYPE_OTA = 7,
    QIOT_ATEVENT_TYPE_SERVER = 8,
    QIOT_ATEVENT_TYPE_UNAUTH = 10,
};
enum
{
    QIOT_AUTH_SUCC = 10200,                /* 设备认证成功 */
    QIOT_AUTH_ERR_DMP_INSIDE = 10404,      /* DMP内部接口调用失败 */
    QIOT_AUTH_ERR_DONE = 10422,            /* 设备已认证（连接失败）*/
    QIOT_AUTH_ERR_PKPS_INVALID = 10423,    /* 没有找到产品信息（连接失败）*/
    QIOT_AUTH_ERR_PAYLOAD_INVALID = 10424, /* PAYLOAD解析失败（连接失败）*/
    QIOT_AUTH_ERR_SIGN_INVALID = 10425,    /* 签名验证未通过（连接失败）*/
    QIOT_AUTH_ERR_HASH_INVALID = 10427,    /* 散列信息不合法（连接失败）*/
    QIOT_AUTH_ERR_DK_ILLEGAL = 10431,      /* DK不合法 */
    QIOT_AUTH_ERR_FLAG = 10433,            /* Flag不符合规则；仅0000与0001其他非法 */
    QIOT_AUTH_ERR_CLIENTID = 10434,        /* ClientID与passwd中ClientID不匹配 */
    QIOT_AUTH_ERR_DEVICE_INSIDE = 10450,   /* 设备内部错误（连接失败）*/
    QIOT_AUTH_ERR_FAIL = 10500,            /* 设备认证失败（系统发生未知异常）*/
    QIOT_AUTH_ERR_UNKNOWN = 10300,         /* 其他错误 */
};
enum
{
    QIOT_CONN_SUCC = 10200,                 /* 接入成功 */
    QIOT_CONN_ERR_DMP_INSIDE = 10404,       /* DMP内部接口调用失败 */
    QIOT_CONN_ERR_DS_INVALID = 10430,       /* 设备密钥不正确（连接失败）*/
    QIOT_CONN_ERR_DEVICE_FORBID = 10477,    /* 设备被禁用（连接失败）*/
    QIOT_CONN_ERR_FLAG = 10433,            /* Flag不符合规则；仅0000与0001其他非法 */
    QIOT_CONN_ERR_CLIENTID = 10434,        /* ClientID与passwd中ClientID不匹配 */
    QIOT_CONN_ERR_DS = 10437,               /* 设备DS错误 */
    QIOT_CONN_ERR_DEVICE_INSIDE = 10450,    /* 设备内部错误（连接失败）*/
    QIOT_CONN_ERR_VERSION_NOTFOUND = 10471, /* 实现方案版本不支持（连接失败）*/
    QIOT_CONN_ERR_PING = 10473,             /* 接入心跳异常 */
    QIOT_CONN_ERR_NET = 10474,              /* 网络异常 */
    QIOT_CONN_ERR_SERVER_CHANGE = 10475,    /* 服务器发生改变 */
    QIOT_CONN_ERR_AP = 10476,               /* 连接AP异常 */
    QIOT_CONN_ERR_UNKNOW = 10500,           /* 接入失败（系统发生未知异常）*/
};
enum
{
    QIOT_SUBCRIBE_SUCC = 10200, /* 订阅成功 */
    QIOT_SUBCRIBE_ERR = 10300,  /* 订阅失败 */
};
enum
{
    QIOT_SEND_SUCC_TRANS = 10200,    /* 透传数据发送成功 */
    QIOT_SEND_ERR_TRANS = 10300,     /* 透传数据发送失败 */
    QIOT_SEND_SUCC_PHYMODEL = 10210, /* 物模型数据发送成功 */
    QIOT_SEND_ERR_PHYMODEL = 10310,  /* 物模型数据发送失败 */
    QIOT_SEND_SUCC_LOC = 10220,      /* 定位数据发送成功 */
    QIOT_SEND_ERR_FAIL_LOC = 10320,  /* 定位数据发送失败 */
    QIOT_SEND_SUCC_STATE = 10230,    /* 状态数据发送成功 */
    QIOT_SEND_ERR_STATE = 10330,     /* 状态数据发送失败 */
    QIOT_SEND_SUCC_INFO = 10240,     /* 设备信息发送成功 */
    QIOT_SEND_ERR_INFO = 10340,      /* 设备信息发送失败 */
};
enum
{
    QIOT_RECV_SUCC_TRANS = 10200,         /* 收到透传数据 */
    QIOT_RECV_SUCC_PHYMODEL_RECV = 10210, /* 收到物模型下发数据 */
    QIOT_RECV_SUCC_PHYMODEL_REQ = 10211,  /* 收到物模型请求数据 */
    QIOT_RECV_SUCC_SUB_STATE_REQ = 10220, /* 收到子设备状态请求数据 */
    QIOT_RECV_SUCC_SUB_INFO_REQ = 10230,  /* 收到子设备信息请求数据 */
    QIOT_RECV_ERR_BUFFER = 10473,         /* 接收失败,收到数据但长度超过模组buffer限制，AT非缓存模式下有效*/
    QIOT_RECV_ERR_LIMIT = 10428,          /* 数据接收失败，设备被限制消息通信，缓存模式下有效 */
};
enum
{
    QIOT_LOGOUT_SUCC = 10200, /* 断开连接成功 */
};
enum
{
    QIOT_OTA_TASK_NOTIFY = 10700, /* 有升级任务 */
    QIOT_OTA_START = 10701,       /* 模组开始下载 */
    QIOT_OTA_DOWNLOADING = 10702, /* 包下载中 */
    QIOT_OTA_DOWNLOADED = 10703,  /* 包下载完成 */
    QIOT_OTA_UPDATING = 10704,    /* 包更新中 */
    QIOT_OTA_UPDATE_OK = 10705,   /* 包更新完成 */
    QIOT_OTA_UPDATE_FAIL = 10706, /* 包更新失败 */
    QIOT_OTA_UPDATE_FLAG = 10707, /* 首个设备操作结果广播 */
};
enum
{
    QIOT_SERVER_ERRCODE_RATE_LIMIT = 10428,
    QIOT_SERVER_ERRCODE_QUANTITY_LIMIT = 10429,
};
enum
{
    QIOT_SUB_DEV_ERR_No_ASSOCIATION = 10440, /* 子设备与当前网关没有关联关系 */
    QIOT_SUB_DEV_ERR_ALREADY_CONN = 10441,   /* 子设备重复登录 */
    QIOT_SUB_DEV_ERR_UNLOGIN = 10442,        /* 子设备未登录 */
};
/* ql_iotDp.h */
typedef enum
{
    QIOT_DPCMD_TYPE_SYS = 0, /* sys类型命令 */
    QIOT_DPCMD_TYPE_BUS,     /* 业务数据类型命令*/
    QIOT_DPCMD_TYPE_OTA,     /* OTA类型命令 */
    QIOT_DPCMD_TYPE_LAN,     /* LAN类型命令 */
} QIot_dpCmdType_e;

typedef enum
{
    QIOT_DPDATA_TYPE_BOOL = 0,
    QIOT_DPDATA_TYPE_INT,
    QIOT_DPDATA_TYPE_FLOAT,
    QIOT_DPDATA_TYPE_BYTE,
    QIOT_DPDATA_TYPE_STRUCT,
} QIot_dpDataType_e;
/**
 * @brief ttlv链表内存
 * @param ttlvHead ttlv链表头
 * @retval 无返回值
 */
void Ql_iotTtlvFree(void **ttlvHead);
/**
 * 功能 @brief 获取ttlv链表节点个数
 * 输入 @param ttlvHead ttlv链表头指针
 * 输出 @return 返回节点个数
 */
quint32_t Ql_iotTtlvCountGet(const void *ttlvHead);
/**
 * 功能 @brief 获取指定ttlv链表节点的id以及数据类型
 * 输入 @param ttlvHead 链表头
 * 输入 @param index ttlv节点索引
 * 输出 @param id 数据节点id
 * 输出 @param type 数据节点类型
 * 输出 @retval 数据节点指针；NULL表示获取失败
 * 备注 @remark 返回值使用完成后，无需释放
 */
void *Ql_iotTtlvNodeGet(const void *ttlvHead, quint16_t index, quint16_t *id, QIot_dpDataType_e *type);
/**
 * 功能 @brief 获取节点数据类型
 * 输入 @param ttlvNode 数据节点
 * 输出 @param type 数据节点类型
 * 输出 @retval 是否成功获取到该节点
 */
qbool Ql_iotTtlvNodeGetType(const void *ttlvNode, QIot_dpDataType_e *type);
/**
 * 功能 @brief 获取bool节点的数据内容
 * 输入 @param ttlvNode 数据节点
 * 输出 @param value 数据节点内容
 * 输出 @retval 是否成功获取节点内容
 */
qbool Ql_iotTtlvNodeGetBool(const void *ttlvNode, qbool *value);
/**
 * 功能 @brief 获取当点整型类型数据内容
 * 输入 @param ttlvNode 数据节点
 * 输出 @param value 数据节点内容
 * 输出 @retval 是否成功获取节点内容
 */
qbool Ql_iotTtlvNodeGetInt(const void *ttlvNode, qint64_t *value);
/**
 * 功能 @brief 获取节点浮点型数据内容
 * 输入 @param ttlvNode 数据节点
 * 输出 @param value 节点数值内容
 * 输出 @retval 是否成功获取节点内容
 */
qbool Ql_iotTtlvNodeGetFloat(const void *ttlvNode, double *value);
/**
 * 功能 @brief 获取节点的字符串数据内容
 * 输入 @param ttlvNode 数据节点
 * 输出 @retval 返回节点字符串内容地址；NULL表示获取失败
 * 备注 @remark 返回值使用完成后，无需释放
 */
char *Ql_iotTtlvNodeGetString(const void *ttlvNode);
/**
 * 功能 @brief 获取节点的Byte数据内容
 * 输入 @param ttlvNode 数据节点
 * 输出 @param value 数据节点内容
 * 输出 @retval 数据内容长度；0表示拉去失败
 * 备注 @remark 数据内容使用完成后，无需释放
 */
quint32_t Ql_iotTtlvNodeGetByte(const void *ttlvNode, quint8_t **value);
/**
 * 功能 @brief 获取节点的strut数据
 * 输入 @param ttlvNode 数据节点
 * 输出 @retval ttlv链表指针
 * 备注 @remark 返回值使用完成后，无需释放
 */
void *Ql_iotTtlvNodeGetStruct(const void *ttlvNode);
/**
 * 功能 @brief 获取指定id节点数据类型
 * 输入 @param ttlvHead ttlv链表头指针
 * 输入 @param id 数据节点id
 * 输出 @param type 数据节点类型
 * 输出 @retval 函数是否执行成功
 */
qbool Ql_iotTtlvIdGetType(const void *ttlvHead, quint16_t id, QIot_dpDataType_e *type);
/**
 * 功能 @brief 获取指定id节点bool数据内容
 * 输入 @param ttlvHead ttlv链表头指针
 * 输入 @param id 数据节点id
 * 输出 @param value 数据节点的bool内容
 * 输出 @retval 函数是否执行成功
 */
qbool Ql_iotTtlvIdGetBool(const void *ttlvHead, quint16_t id, qbool *value);
/**
 * 功能 @brief 获取指定id节点的整型数据内容
 * 输入 @param ttlvHead ttlv链表头指针
 * 输入 @param id 数据节点id
 * 输出 @param value 数据节点整型数据内容
 * 输出 @retval 函数是否执行成功
 */
qbool Ql_iotTtlvIdGetInt(const void *ttlvHead, quint16_t id, qint64_t *value);
/**
 * 功能 @brief 获取指定id节点的浮点型数据内容
 * 输入 @param ttlvHead ttlv链表头指针
 * 输入 @param id 数据节点id
 * 输出 @param value 数据节点的浮点型数据内容
 * 输出 @retval 函数是否执行成功
 */
qbool Ql_iotTtlvIdGetFloat(const void *ttlvHead, quint16_t id, double *value);
/**
 * 功能 @brief 获取指定id节点的字符串数据内容
 * 输入 @param ttlvHead ttlv链表头指针
 * 输入 @param id 数据节点id
 * 输出 @retval 数据节点字符串内容；NULL表示执行失败
 * 备注 @remark 返回值使用完成，无需释放
 */
char *Ql_iotTtlvIdGetString(const void *ttlvHead, quint16_t id);
/**
 * 功能 @brief 获取指定id节点的Byte数据内容
 * 输入 @param ttlvHead ttlv链表头指针
 * 输入 @param id 数据节点id
 * 输出 @param value 节点Byte数据内容
 * 输出 @retval 返回节点数据内容长度；0表示执行失败
 * 备注 @remark 数据内容使用完成无需释放
 */
quint32_t Ql_iotTtlvIdGetByte(const void *ttlvHead, quint16_t id, quint8_t **value);
/**
 * 功能 @brief 获取指定节点的数据-strut类型
 * 输入 @param ttlvHead ttlv链表头指针
 * 输入 @param id 数据节点id
 * 输出 @retval ttlv子链表头指针
 * 备注 @remark 返回值无需释放
 */
void *Ql_iotTtlvIdGetStruct(const void *ttlvHead, quint16_t id);

/* id为0时即为添加数组节点 */
/**
 * 功能 @brief 向ttlv链表中添加bool类型节点
 * 输入 @param ttlvHead 链表头指针
 * 输入 @param id 添加节点的id
 * 输入 @param value 添加节点的数据内容
 * 输出 @retval 是否添加成功
 */
qbool Ql_iotTtlvIdAddBool(void **ttlvHead, quint16_t id, qbool value);
/**
 * 功能 @brief 向ttlv链表中添加整型类型节点
 * 输入 @param ttlvHead 链表头指针
 * 输入 @param id 添加节点的id
 * 输入 @param value 添加节点的数据内容
 * 输出 @retval 是否添加成功
 */
qbool Ql_iotTtlvIdAddInt(void **ttlvHead, quint16_t id, qint64_t num);
/**
 * 功能 @brief 向ttlv链表中添加浮点型类型节点
 * 输入 @param ttlvHead 链表头指针
 * 输入 @param id 添加节点的id
 * 输入 @param value 添加节点的数据内容
 * 输出 @retval 是否添加成功
 */
qbool Ql_iotTtlvIdAddFloat(void **ttlvHead, quint16_t id, double num);
/**
 * 功能 @brief 向ttlv链表中添加浮点型类型节点， 需要指定小数点最大长度
 * 输入 @param ttlvHead 链表头指针
 * 输入 @param id 添加节点的id
 * 输入 @param value 添加节点的数据内容
 * 输出 @retval 是否添加成功
 */
qbool Ql_iotTtlvIdAddFloat_ex(void **ttlvHead, quint16_t id, double value, quint8_t precision);
/**
 * 功能 @brief 向ttlv链表中添加Byte类型节点
 * 输入 @param ttlvHead 链表头指针
 * 输入 @param id 添加节点的id
 * 输入 @param data 添加节点的数据内容
 * 输入 @param len 数据内容长度
 * 输出 @retval 是否添加成功
 */
qbool Ql_iotTtlvIdAddByte(void **ttlvHead, quint16_t id, const quint8_t *data, quint32_t len);
/**
 * 功能 @brief 向ttlv链表中添加字符串类型节点
 * 输入 @param ttlvHead 链表头指针
 * 输入 @param id 添加节点的id
 * 输入 @param data 添加节点的数据内容
 * 输出 @retval 是否添加成功
 */
qbool Ql_iotTtlvIdAddString(void **ttlvHead, quint16_t id, const char *data);
/**
 * 功能 @brief 向ttlv链表中添加结构体类型节点
 * 输入 @param ttlvHead 链表头指针
 * 输入 @param id 添加节点的id
 * 输入 @param value 添加节点的结构体指针
 * 输出 @retval 是否添加成功
 */
qbool Ql_iotTtlvIdAddStruct(void **ttlvHead, quint16_t id, void *vStruct);
/**
 * 功能 @brief 删除ttlv链表中制定ID的节点
 * 输入 @param ttlvHead 链表头指针
 * 输入 @param id 节点的id
 */
void Ql_iotTtlvRemove(void **ttlvHead, quint16_t id);

/* ql_iotCmdBus.h */
/**
 * 功能 @brief 发送透传数据至平台
 * 输入 @param mode 发送模式：0	QoS = 0，最多发送一次
 *                           1	QoS = 1，最少发送一次
 *                           2	QoS = 2，仅发送一次
 * 输入 @param payload 发送数据内容
 * 输入 @param len 发送数据长度
 * 输出 @retval 是否发送成功
 */
qbool Ql_iotCmdBusPassTransSend(quint16_t mode, quint8_t *payload, quint32_t len);
/**
 * 功能 @brief 发送物模型数据至平台
 * 输入 @param mode 发送模式：0	QoS = 0，最多发送一次
 *                           1	QoS = 1，最少发送一次
 *                           2	QoS = 2，仅发送一次
 * 输入 @param ttlvHead 物模型ttlv链表头指针
 * 输出 @retval 是否发送成功
 * 备注 @remark 需自行调用Ql_iotTtlvFree函数释放 ttlvHead
 */
qbool Ql_iotCmdBusPhymodelReport(quint16_t mode, const void *ttlvHead);
/**
 * 功能 @brief 回复平台查询模型消息
 * 输入 @param mode 发送模式：0	QoS = 0，最多发送一次
 *                           1	QoS = 1，最少发送一次
 *                           2	QoS = 2，仅发送一次
 * 输入 @param PkgId 平台下发查询消息PkgId
 * 输入 @param ttlvHead 物模型ttlv链表头指针
 * 输出 @retval 是否发送成功
 * 备注 @remark 需自行调用Ql_iotTtlvFree函数释放 ttlvHead
 */
qbool Ql_iotCmdBusPhymodelAck(quint16_t mode, quint16_t pkgId, const void *ttlvHead);
/**
 * 功能 @brief 发送透传数据至平台
 * 输入 @param mode 发送模式：0	QoS = 0，最多发送一次
 *                           1	QoS = 1，最少发送一次
 *                           2	QoS = 2，仅发送一次
 * 输入 @param payload 发送数据内容
 * 输入 @param len 发送数据长度
 * 输出 @retval 1~65535：发送成功消息PkgId；-1：发送失败
 * 备注 @remark 为该函数Ql_iotCmdBusPassTransSend的扩展函数；建议优先使用该函数；需自行调用Ql_iotTtlvFree函数释放 ttlvHead
 */
qint32_t Ql_iotCmdBusPassTransSend_ex(quint16_t mode, quint8_t *payload, quint32_t len);
/**
 * 功能 @brief 发送物模型数据至平台
 * 输入 @param mode 发送模式：0	QoS = 0，最多发送一次
 *                           1	QoS = 1，最少发送一次
 *                           2	QoS = 2，仅发送一次
 * 输入 @param ttlvHead 物模型ttlv链表头指针
 * 输出 @retval 1~65535：发送成功消息PkgId；-1：发送失败
 * 备注 @remark 为该函数Ql_iotCmdBusPhymodelReport的扩展函数；建议优先使用该函数
 */
qint32_t Ql_iotCmdBusPhymodelReport_ex(quint16_t mode, const void *ttlvHead);


/* ql_iotCmdLoc.h */
/**
 * 功能 @brief 上报模组内置定位数据至平台
 * 输入 @param titleTtlv 定位数据类型的TTLV链表指针
 * 输出 @retval 函数是否执行成功
 * 备注 @remark 需自行调用Ql_iotTtlvFree函数释放 titleTtlv
 */
qbool Ql_iotCmdBusLocReportInside(void *titleTtlv);
/**
 * 功能 @brief 上报设备外置定位数据至平台
 * 输入 @param nmeaTtlv NMEA数据的TTLV链表指针
 * 输出 @retval 函数是否执行成功
 * 备注 @remark 需自行调用Ql_iotTtlvFree函数释放 nmeaTtlv
 */
qbool Ql_iotCmdBusLocReportOutside(void *nmeaTtlv);
/**
 * 功能 @brief 获取内置定位数据
 * 输入 @param titleTttlv 定位数据类型的TTLV链表指针
 * 输出 @retval ttlv链表头指针，节点是定位数据；null表示获取失败
 * 备注 @remark 返回值在使用完成后需要调用函数Ql_iotTtlvFree()释放该变量
 */
void *Ql_iotLocGetData(const void *titleTtlv);
/**
 * 功能 @brief 获取内置定位功能支持的NMEA类型
 * 输出 @retval ttlv链表头指针，节点为定位支持的NMEA类型；NULL表示获取失败
 * 备注 @remark 返回值在使用完成后需要调用函数Ql_iotTtlvFree()释放该变量；
 */
void *Ql_iotLocGetSupList(void);

/**
 * 功能 @brief 上报模组内置定位数据至平台
 * 输入 @param titleTtlv 定位数据类型的TTLV链表指针
 * 输出 @retval 1~65535：发送成功消息PkgId；-1：发送失败
 * 备注 @remark 为该函数Ql_iotCmdBusLocReportInside的扩展函数；建议优先使用该函数；需自行调用Ql_iotTtlvFree函数释放 titleTtlv
 */
qint32_t Ql_iotCmdBusLocReportInside_ex(void *titleTtlv);
/**
 * 功能 @brief 上报设备外置定位数据至平台
 * 输入 @param nmeaTtlv NMEA数据的TTLV链表指针
 * 输出 @retval 1~65535：发送成功消息PkgId；-1：发送失败
 * 备注 @remark 为该函数Ql_iotCmdBusLocReportOutside的扩展函数；建议优先使用该函数；需自行调用Ql_iotTtlvFree函数释放 nmeaTtlv
 */
qint32_t Ql_iotCmdBusLocReportOutside_ex(void *nmeaTtlv);

/* ql_iotCmdOTA.h */
/**
 * 功能 @brief 向平台请求OTA升级计划
 * 输入 @param mode 额外文件(SHA256)校验方式：
 *                  0 不需要
 *                  1 需要
 * 输出 @retval 函数是否执行成功
 */
qbool Ql_iotCmdOtaRequest(quint32_t mode);
/**
 * 功能 @brief 设备收到升级计划，配置OTA升级行为
 * 输入 @param action OTA升级行为
 *                    0 拒绝升级
 *                    1 确认升级
 *                    2 SOTA升级时，MCU通知下载下一块固件(升级文件较大时，无法一次性将升级包完整下载到本地，将执行分块下载，当一块下载完成时，供MCU读取，MCU读取完成后再下载下一块升级固件)
 *                    3 MCU下载完成所有块固件，通知平台进入更新 
 * 输出 @retval 函数执行是否成功
 */
qbool Ql_iotCmdOtaAction(quint8_t action);
/**
 * 功能 @brief MCU读取模组下载的升级固件数据
 * 输入 @param startAddr 读取固件开始的位置
 * 输出 @param data 存放固件数据的缓存区
 * 输入 @param maxLen 最大读取固件数据长度
 * 输出 @retval 实际读取到固件数据长度；0表示读取失败
 */
quint32_t Ql_iotCmdOtaMcuFWDataRead(quint32_t startAddr, quint8_t data[], quint32_t maxLen);

/* ql_iotCmdSys.h */
/* 设备状态 */
enum
{
    QIOT_DPID_STATUS_BATTERY = 1,   /* 电量 */
    QIOT_DPID_STATUS_VOLTAGE = 2,   /* 电压 */
    QIOT_DPID_STATUS_SIGNAL = 3,    /* 信号强度 */
    QIOT_DPID_STATUS_FLASHFREE = 4, /* 剩余空间 */
    QIOT_DPID_STATUS_RSRP = 5,      /* 参考信号接收功率 */
    QIOT_DPID_STATUS_RSRQ = 6,      /* LTE参考信号接收质量 */
    QIOT_DPID_STATUS_SNR = 7,       /* 信号与干扰加噪声比 */
    QIOT_DPID_STATUS_MAX,
};
/* 模组信息 */
enum
{
    QIOT_DPID_INFO_MODEL_TYPE = 1,   /* 模组型号 */
    QIOT_DPID_INFO_MODEL_VER = 2,    /* 模组版本 */
    QIOT_DPID_INFO_MCU_VER = 3,      /* MCU版本 */
    QIOT_DPID_INFO_CELLID = 4,       /* 基站id */
    QIOT_DPID_INFO_ICCID = 5,        /* SIM卡号 */
    QIOT_DPID_INFO_MCC = 6,          /* 移动国家代码 */
    QIOT_DPID_INFO_MNC = 7,          /* 移动网络代码 */
    QIOT_DPID_INFO_LAC = 8,          /* 位置区代码 */
    QIOT_DPID_INFO_PHONE_NUM = 9,    /* phone号 */
    QIOT_DPID_INFO_SIM_NUM = 10,     /* SIM号 */
    QIOT_DPID_INFO_SDK_VER = 11,     /* quecthingSDK版本号*/
    QIOT_DPID_INFO_LOC_SUPLIST = 12, /* 定位功能支持列表 */
    QIOT_DPIO_INFO_DP_VER = 13,      /* 数据协议版本 */
    QIOT_DPIO_INFO_CP_VER = 14,      /* 通信协议版本号 */
    QIOT_DPID_INFO_MAX,
};
/**
 * 功能 @brief 设备状态上报至平台
 * 输入 @param ids 设备状态ID集合
 * 输入 @param size 设备状态ID个数
 * 输出 @retval 函数是否执行成功
 */
qbool Ql_iotCmdSysStatusReport(quint16_t ids[], quint32_t size);
/**
 * 功能 @brief 设备信息上报至平台
 * 输入 @param ids 设备信息ID集合
 * 输入 @param size 设备信息ID个数
 * 输出 @retval 函数是否执行成功
 */
qbool Ql_iotCmdSysDevInfoReport(quint16_t ids[], quint32_t size);
/**
 * 功能 @brief 获取设备状态
 * 输入 @param ids 设备状态ID集合
 * 输入 @param size 设备状态ID个数
 * 输出 @retval ttlv链表；节点为设备状态；NULL表示获取失败
 * 备注 @remark 返回值需在使用完成后使用Ql_iotTtlvFree()释放资源
 */
void *Ql_iotSysGetDevStatus(quint16_t ids[], quint32_t size);
/**
 * 功能 @brief 获取设备信息
 * 输入 @param ids 设备信息ID集合
 * 输入 @param size 设备信息ID个数
 * 输出 @retval ttlv链表；节点为设备信息；NULL表示获取失败
 * 备注 @remark 返回值需在使用完成后使用Ql_iotTtlvFree()释放资源
 */
void *Ql_iotSysGetDevInfo(quint16_t ids[], quint32_t size);
/**
 * 功能 @brief 触发可绑定
 * 输入 @param bindcode 设备绑定码；字符范围：0~9，A~F，为NULL时系统随机生成
 * 输入 @param timeout 可绑定时间，0为取消绑定
 * 输出 @retval 函数是否执行成功
 * 备注 @remark bindcode长度固定16字节
 */
qbool Ql_iotDBindcodeSet(const char *bindcode, quint32_t timeout);
/**
 * 功能 @brief 获取设备绑定信息
 * 输出 @param bindcode 设备绑定码
 * 输出 @retval 设备绑定剩余超时时长
 * 备注 @remark 返回值使用完，直接丢弃，不可释放
 */
quint32_t Ql_iotDBindcodeGet(char **bindcode);
/* ql_iotConn.h */
 enum
{
    QIOT_DPAPP_M2M = (1 << 0),
    QIOT_DPAPP_SUBDEV = (1 << 1),
    QIOT_DPAPP_LANPHONE = (1 << 2),
} ;
typedef quint32_t QIot_dpAppType_e;

/* quos_modbus.h */
/* 串口校验位 */
typedef enum
{
    QIOT_MBUART_PARITY_NONE  = 0,
    QIOT_MBUART_PARITY_EVEN  = 1,
    QIOT_MBUART_PARITY_ODD   = 2,
    QIOT_MBUART_PARITY_MARK  = 3,
    QIOT_MBUART_PARITY_SPACE = 4,
}QIot_MBParity_e;
/* 串口数据位 */
typedef enum
{
    QIOT_MBUART_DATABITS_5  = 0,
    QIOT_MBUART_DATABITS_6  = 1,
    QIOT_MBUART_DATABITS_7  = 2,
    QIOT_MBUART_DATABITS_8  = 3,
}QIot_MBDataBits_e;
/* 串口停止位 */
typedef enum
{
    QIOT_MBUART_STOPBITS_1   = 0,
    QIOT_MBUART_STOPBITS_1_5 = 1,
    QIOT_MBUART_STOPBITS_2   = 2,
}QIot_MBStopBits_e;

typedef struct
{
    quint16_t port;
    quint32_t baudrate;
    QIot_MBDataBits_e dataBits;
    QIot_MBParity_e parity;
    QIot_MBStopBits_e stopBits;
}QIot_MBPortCfg_t;

/**
 * 功能 @brief modbus发送回调函数
 * 输入 @param port 串口号
 * 输入 @param buf 发送数据内容
 * 出入 @param bufLen 数据长度
 * 输出 @retval 是否发送成功
 */
typedef qbool (*QIot_MBSend_f)(quint16_t port, const quint8_t *buf, quint32_t bufLen);
/**
 * 功能 @brief modbus 初始化回调函数
 * 输入 @param pk 设备联网的产品productKey
 * 输入 @param ps 设备联网的产品productSecret
 * 输入 @param portInfo 串口列表初始化信息
 * 输入 @param portNum 串口号个数
 */
typedef void (*QIot_MBInitCb_f)(char *pk, char *ps,QIot_MBPortCfg_t *portInfo[], quint32_t portNum);

/**
 * 功能 @brief modbus初始化
 * 输入 @param portList 串口号列表
 * 输入 @param portNum 串口号个数
 * 输入 @param sendFunc 串口数据发送函数
 * 输入 @param initCb modbus初始化回调函数
 * 输出 @retval 函数是否执行成功
 */
qbool Ql_iotMBInit(quint16_t portList[],quint32_t portNum,QIot_MBSend_f sendFunc,QIot_MBInitCb_f initCb);
/**
 * 功能 @brief 收到平台下发的物模型数据
 * 输入 @param ttlvHead 物模型ttlv链表
 * 输出 @retval 函数是否执行成功
 */
qbool Ql_iotMBCloudRecv(const void *ttlvHead);
/**
 * 功能 @brief 收到modbus从机数据
 * 输入 @param port 串口号
 * 输入 @param data 从机数据内容
 * 输入 @param len 数据长度
 * 输出 @retval 函数是否执行成功
 */
qbool Ql_iotMBLocalRecv(quint16_t port,quint8_t *data,quint32_t len);
/**
 * 功能 @brief modbus功能注销
 * 输出 @retval函数是否执行成功
 */
qbool Ql_iotMBDeinit(void);
/* ql_iotConfig.h */
typedef enum
{
    QIOT_CONNMODE_IDLE, /* 不连接IOT */
    QIOT_CONNMODE_REQ,  /* 手动发起连接IOT */
    QIOT_CONNMODE_AUTO, /* 联网后主动连接IOT 仅AT方案有效 */
} QIot_connMode_e;
typedef enum
{
    QIOT_PPROTOCOL_MQTT = 1,
} QIot_protocolType_t;
typedef enum
{
    QIOT_STATE_UNINITIALIZE = 0,
    QIOT_STATE_INITIALIZED = 1,
    QIOT_STATE_AUTHENTICATING = 2,
    QIOT_STATE_AUTHENTICATED = 3,
    QIOT_STATE_AUTHENTICATE_FAILED = 4,
    QIOT_STATE_CONNECTING = 5,
    QIOT_STATE_CONNECTED = 6,
    QIOT_STATE_CONNECT_FAIL = 7,
    QIOT_STATE_SUBSCRIBED = 8,
    QIOT_STATE_SUBSCRIBE_FAIL = 9,
    QIOT_STATE_DISCONNECTING = 10,
    QIOT_STATE_DISCONNECTED = 11,
    QIOT_STATE_DISCONNECT_FAIL = 12,
} QIot_state_e;

enum
{
    QIOT_SUBDEVAUTH_NONE = 0,
    QIOT_SUBDEVAUTH_PRODUCT_KEY = 1,
    QIOT_SUBDEVAUTH_PROJECT_ID = 2,
};
typedef quint8_t QIot_subDevAuth_e;
typedef enum
{
    QIOT_SUBDEV_CONN_TCP = 0,
    QIOT_SUBDEV_CONN_UDP = 1,
}QIot_subDevConn_e;
/**
 * 功能 @brief QuecThing功能初始化
 * 输出 @retval 函数是否执行成功
 */
qbool Ql_iotInit(void);
/**
 * 功能 @brief 设置QuecThing连接平台模式
 * 输入 @param mode 0：断开与平台连接；1：发起连接平台
 * 输出 @retval 函数是否执行成功
 */
qbool Ql_iotConfigSetConnmode(QIot_connMode_e mode);
/**
 * 功能 @brief 获取QuecThing连接平台模式
 * 输出 @retval 0：未连接平台；1：发起连接平台；其他值异常
 */
QIot_connMode_e Ql_iotConfigGetConnmode(void);
/**
 * 功能 @brief 设置设备产品信息
 * 输入 @param pk 创建产品时产生的productKey
 * 输入 @param ps 创建产品时产生的productSecret
 * 输出 @retval 函数是否执行成功
 */
qbool Ql_iotConfigSetProductinfo(const char *pk, const char *ps);
/**
 * 功能 @brief 获取设备产品信息
 * 输出 @param pk 创建产品时产生的productKey
 * 输出 @param ps 创建产品时产生的productSecret
 * 输出 @param ver 设备认证协议版本号
 * 备注 @remark 所有获取数据内容均不需要释放；获取到参数内容为NULL，表示获取失败
 */
void Ql_iotConfigGetProductinfo(char **pk, char **ps, char **ver);
/**
 * 功能 @brief 设置服务器信息
 * 输入 @param type 协议类型；当前仅支持1：MQTT协议
 * 输入 @param serverUrl 服务器地址
 * 输出 @retval 函数是否执行成功
 */
qbool Ql_iotConfigSetServer(QIot_protocolType_t type, const char *serverUrl);
/**
 * 功能 @brief 获取设备服务器信息
 * 输出 @param type 协议类型
 * 输出 @param serverUrl 服务器地址信息
 * 备注 @remark 服务器地址信息使用完成后，无需释放
 */
void Ql_iotConfigGetServer(QIot_protocolType_t *type, char **serverUrl);
/**
 * 功能 @brief 设置设备心跳时间
 * 输入 @param lifetime 心跳间隔；单位：秒；范围：1~65535；
 * 输出 @retval 函数是否执行成功
 * 备注 @remark 可选配置参数；心跳默认值为120秒；不配置将使用默认值
 */
qbool Ql_iotConfigSetLifetime(quint32_t lifetime);
/**
 * 功能 @brief 获取设备心跳间隔
 * 输出 @retval 心跳间隔；单位：秒
 */
quint32_t Ql_iotConfigGetLifetime(void);
/**
 * 功能 @brief 设置pdp上下文ID
 * 输入 @param contextID PDP上下文ID
 * 输出 @retval 函数是否执行成功
 * 备注 @remark 可选配置参数；默认值为1，不配置时使用默认值
 */
qbool Ql_iotConfigSetPdpContextId(quint8_t contextID);
/**
 * 功能 @brief 获取PDP上下文ID
 * 输出 @retval PDP上下文ID值
 */
quint8_t Ql_iotConfigGetPdpContextId(void);
/**
 * 功能 @brief 设置与平台连接加密模式
 * 输入 @param flag TRUE：开启加密
 *                  FLASE：关闭加密
 * 输出 @retval 函数是否执行成功
 */
qbool Ql_iotConfigSetSessionFlag(qbool flag);
/**
 * 功能 @brief 获取当前连接平台加密模式
 * 输出 @retval TRUE：已开启加密；FALSE：未开启加密
 * 备注 @remark 默认关闭；可选配置参数
 */
qbool Ql_iotConfigGetSessionFlag(void);
/**
 * 功能 @brief 配置用户程序版本号(追加到模组版本号尾部)
 * 输入 @param appVer 用户程序版本号
 * 输出 @retval 函数是否执行成功
 */
qbool Ql_iotConfigSetAppVersion(const char *appVer); 
/**
 * 功能 @brief 获取版本号
 * 输出 @retval 返回模组以及用户设置版本号；NULL表示获取失败
 * 备注 @remark 函数返回值不需要释放
 */
char *Ql_iotConfigGetSoftVersion(void);
/**
 * 功能 @brief 设置用户版本号以及编号
 * 输入 @param compno MCU编号；最大32字节
 * 输入 @param version 编号对应的软件版本号
 * 输出 @retval 函数是否执行成功
 */
qbool Ql_iotConfigSetMcuVersion(const char *compno, const char *version);
/**
 * 功能 @brief 获取MCU编号以及版本号
 * 输入 @param compno MCU编号
 * 输出 @param version MCU编号对应的版本号
 * 输出 @retval MCU编号对应的版本号长度
 * 备注 @remark 版本号使用完成后无需释放
 */
quint32_t Ql_iotConfigGetMcuVersion(const char *compno, char **version);
/**
 * 功能 @brief 设置QuecThing事件回调函数
 * 输入 @param eventCb 事件回调函数
 */
void Ql_iotConfigSetEventCB(void (*eventCb)(quint32_t event, qint32_t errcode, const void *value, quint32_t valLen));
/**
 * 功能 @brief 获取设备与平台间连接状态
 * 输出 @retval 连接状态
 */
QIot_state_e Ql_iotGetWorkState(void);
/**
 * 功能 @brief 设置自定义设备标识以及标识对应的设备秘钥
 * 输入 @param dk 自定义设备标识；长度4~16字节
 * 输入 @param ds 自定义设备标识对应的设备秘钥；长度固定32字节
 * 输出 @retval 函数是否执行成功
 * 备注 @remark 仅当dk非空以及非默认值时，允许设置设备秘钥；dk以及ds为空时，清除配置dk，ds并回复使用默认dk；dk不为空，ds为空时，清除ds
 */
qbool Ql_iotConfigSetDkDs(const char *dk, const char *ds);
/**
 * 功能 @brief 获取自定义设备标识以及设备秘钥 
 * 输出 @param dk 自定义设备标识
 * 输出 @param ds 自定义设备标识对应的ds
 * 输出 @retval 函数是否执行成功
 * 备注 @remark 参数使用完成后无需释放
 */
qbool Ql_iotConfigGetDkDs(char **dk, char **ds);
/**
 * 功能 @brief 重置设备秘钥以及bindcode
 * 输出 @retval 函数是否执行成功
 */

void Ql_iotRst(void);

/* ql_HOtaConfig.h */
/**
 * 功能 @brief 事件回调函数
 * 输入 @param event 事件类型
 * 输入 @param errcode 事件码
 * 输入 @param value 数据内容
 * 输入 @param valLen 数据内容长度
 * 备注 @remark 部分事件回调没有数据内容；故value可能为NULL
 */
typedef void (*eventCb_f)(quint32_t event, qint32_t errcode, const void *value, quint32_t valLen);
/**
 * 功能 @brief 设置HTTP OTA事件回调函数
 * 输入 @param eventCb 事件回调函数
 */
void Ql_iotHttpOtaSetEventCb(eventCb_f eventCb);
/**
 * 功能 @brief 配置HTTP OTA参数以及向平台请求升级计划
 * 输入 @param battery 设备当前电量；范围0~100
 * 输入 @param upmode 升级模式：1下载固件包完成后，自动升级
 * 输入 @param pk 创建产品时生成的productKey
 * 输入 @param ps 创建产品时生成的productSecret
 * 输入 @param url HTTP OTA平台地址
 * 输出 @retval 函数是否执行成功
 */
qbool Ql_iotHttpOtaReq(quint8_t battery, quint8_t upmode,const char *pk,const char *ps, const char *url);
/**
 * 功能 @brief 获取HTTP OTA配置信息
 * 输出 @param battery 设备电量
 * 输出 @param upmode 设备升级模式
 * 输出 @param pk 创建产品时生成的productKey
 * 输入 @param ps 创建产品时生成的productSecret
 * 输入 @param url HTTP OTA平台地址
 * 备注 @remark 获取到的数据内容无需释放
 */
void Ql_iotHttpOtaGet(quint8_t *battery, quint8_t *upmode,char **pk,char **ps, char **url);

/* ql_iotGwDev.h */
/**
 * 功能 @brief 子设备事件回调函数
 * 输入 @param event 事件类型
 * 输入 @param errcode 事件码
 * 输入 @param subPk 子设备产品productKey
 * 输入 @param subDk 子设备唯一标识
 * 输入 @param value 数据内容
 * 输入 @param valLen 数据内容长度
 */
typedef void (*SubEventCb_f)(quint32_t event, qint32_t errcode, const char *subPk, const char *subDk, const void *value, quint32_t valLen);
/**
 * 功能 @brief 设置子设备事件回调函数
 * 输入 @param eventCb 事件回调函数
 */
void Ql_iotConfigSetSubDevEventCB(SubEventCb_f eventCb);
/**
 * 功能 @brief 子设备发起连接
 * 输入 @param subPk 子设备产品productKey
 * 输入 @param subPs 子设备产品productSecret
 * 输入 @param subDk 子设备唯一标识
 * 输入 @param subDs 子设备秘钥(第一次连接时为空；认证成功后，可获取到子设备秘钥)
 * 输入 @param sessionType 子设备通过网关与平台交互是否需要加密；0：不加密；1：加密
 * 输入 @param keepalive 子设备保活时间；单位：秒
 * 输出 @retval 函数是否执行成功
 */
qbool Ql_iotSubDevConn(const char *subPk, const char *subPs, const char *subDk, const char *subDs, quint8_t sessionType, quint16_t keepalive);
/**
 * 功能 @brief 子设备断开连接
 * 输入 @param subPk 子设备产品productKey
 * 输入 @param subDk 子设备唯一标识
 * 输出 @retval 函数是否执行成功
 */
qbool Ql_iotSubDevDisconn(const char *subPk, const char *subDk);
/**
 * 功能 @brief 子设备发送透传数据至平台
 * 输入 @param subPk 子设备产品productKey
 * 输入 @param subDk 子设备唯一标识
 * 输入 @param payload 透传数据内容
 * 输入 @param payloadLen 透传数据长度
 * 输出 @retval 函数是否执行成功
 */
qbool Ql_iotSubDevPassTransSend(const char *subPk, const char *subDk, quint8_t *payload, quint16_t payloadlen);
/**
 * 功能 @brief 子设备发送物模型数据至平台
 * 输入 @param subPk 子设备产品productKey
 * 输入 @param subDk 子设备唯一标识
 * 输入 @param ttlvHead 物模型ttlv链表
 * 输出 @retval 函数是否执行成功
 * 备注 @remark 物模型ttlvHead资源需自行释放
 */
qbool Ql_iotSubDevTslReport(const char *subPk, const char *subDk, const void *ttlvHead);
/**
 * 功能 @brief 子设备回复平台物模型查询指令
 * 输入 @param subPk 子设备产品productKey
 * 输入 @param subDk 子设备唯一标识
 * 输入 @param pkgId 平台查询物模型消息pkgId
 * 输入 @param ttlvHead 物模型ttlv链表
 * 输出 @retval 物模型ttlvHead资源需自行释放
 */
qbool Ql_iotSubDevTslAck(const char *subPk, const char *subDk, quint16_t pkgId, const void *ttlvHead);
/**
 * 功能 @brief 子设备注销
 * 输入 @param subPk 子设备产品productKey
 * 输入 @param subPs 子设备产品productSecret
 * 输入 @param subDk 子设备唯一标识
 * 输入 @param subDs 子设备秘钥
 * 输出 @retval 函数执行结果
 * 备注 @remark 子设备注销后，subDs将无法登陆平台，需要重新认证
 */
qbool Ql_iotSubDevDeauth(const char *subPk, const char *subPs, const char *subDk, const char *subDs);
/**
 * 功能 @brief 刷新子设备与网关最后交互时间
 * 输入 @param subPk 子设备产品productKey
 * 输入 @param subDk 子设备唯一标识
 * 输出 @retval 函数是否执行成功
 */
qbool Ql_iotSubDevHTB(const char *subPk, const char *subDk);
/**
 * 功能 @brief 子设备发送透传数据至平台
 * 输入 @param subPk 子设备产品productKey
 * 输入 @param subDk 子设备唯一标识
 * 输入 @param payload 透传数据内容
 * 输入 @param payloadLen 透传数据长度
 * 输出 @retval 1~65535：发送成功消息PkgId；-1：发送失败
 */
qint32_t Ql_iotSubDevPassTransSend_ex(const char *subPk, const char *subDk, quint8_t *payload, quint16_t payloadlen);
/**
 * 功能 @brief 子设备发送物模型数据至平台
 * 输入 @param subPk 子设备产品productKey
 * 输入 @param subDk 子设备唯一标识
 * 输入 @param ttlvHead 物模型ttlv链表
 * 输出 @retval 1~65535：发送成功消息PkgId；-1：发送失败
 * 备注 @remark 物模型ttlvHead资源需自行释放；该函数为Ql_iotSubDevTslReport()函数扩展，建议优先使用该函数
 */
qint32_t Ql_iotSubDevTslReport_ex(const char *subPk, const char *subDk, const void *ttlvHead);
#endif
