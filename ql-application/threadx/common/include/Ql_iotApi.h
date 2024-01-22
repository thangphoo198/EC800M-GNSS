#ifndef __QIOT_API_H__
#define __QIOT_API_H__
#ifndef __QTH_TEST__ /* open���������ṩͷ�ļ�ʱ����Ҫ���� */
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
    QIOT_AUTH_SUCC = 10200,                /* �豸��֤�ɹ� */
    QIOT_AUTH_ERR_DMP_INSIDE = 10404,      /* DMP�ڲ��ӿڵ���ʧ�� */
    QIOT_AUTH_ERR_DONE = 10422,            /* �豸����֤������ʧ�ܣ�*/
    QIOT_AUTH_ERR_PKPS_INVALID = 10423,    /* û���ҵ���Ʒ��Ϣ������ʧ�ܣ�*/
    QIOT_AUTH_ERR_PAYLOAD_INVALID = 10424, /* PAYLOAD����ʧ�ܣ�����ʧ�ܣ�*/
    QIOT_AUTH_ERR_SIGN_INVALID = 10425,    /* ǩ����֤δͨ��������ʧ�ܣ�*/
    QIOT_AUTH_ERR_HASH_INVALID = 10427,    /* ɢ����Ϣ���Ϸ�������ʧ�ܣ�*/
    QIOT_AUTH_ERR_DK_ILLEGAL = 10431,      /* DK���Ϸ� */
    QIOT_AUTH_ERR_FLAG = 10433,            /* Flag�����Ϲ��򣻽�0000��0001�����Ƿ� */
    QIOT_AUTH_ERR_CLIENTID = 10434,        /* ClientID��passwd��ClientID��ƥ�� */
    QIOT_AUTH_ERR_DEVICE_INSIDE = 10450,   /* �豸�ڲ���������ʧ�ܣ�*/
    QIOT_AUTH_ERR_FAIL = 10500,            /* �豸��֤ʧ�ܣ�ϵͳ����δ֪�쳣��*/
    QIOT_AUTH_ERR_UNKNOWN = 10300,         /* �������� */
};
enum
{
    QIOT_CONN_SUCC = 10200,                 /* ����ɹ� */
    QIOT_CONN_ERR_DMP_INSIDE = 10404,       /* DMP�ڲ��ӿڵ���ʧ�� */
    QIOT_CONN_ERR_DS_INVALID = 10430,       /* �豸��Կ����ȷ������ʧ�ܣ�*/
    QIOT_CONN_ERR_DEVICE_FORBID = 10477,    /* �豸�����ã�����ʧ�ܣ�*/
    QIOT_CONN_ERR_FLAG = 10433,            /* Flag�����Ϲ��򣻽�0000��0001�����Ƿ� */
    QIOT_CONN_ERR_CLIENTID = 10434,        /* ClientID��passwd��ClientID��ƥ�� */
    QIOT_CONN_ERR_DS = 10437,               /* �豸DS���� */
    QIOT_CONN_ERR_DEVICE_INSIDE = 10450,    /* �豸�ڲ���������ʧ�ܣ�*/
    QIOT_CONN_ERR_VERSION_NOTFOUND = 10471, /* ʵ�ַ����汾��֧�֣�����ʧ�ܣ�*/
    QIOT_CONN_ERR_PING = 10473,             /* ���������쳣 */
    QIOT_CONN_ERR_NET = 10474,              /* �����쳣 */
    QIOT_CONN_ERR_SERVER_CHANGE = 10475,    /* �����������ı� */
    QIOT_CONN_ERR_AP = 10476,               /* ����AP�쳣 */
    QIOT_CONN_ERR_UNKNOW = 10500,           /* ����ʧ�ܣ�ϵͳ����δ֪�쳣��*/
};
enum
{
    QIOT_SUBCRIBE_SUCC = 10200, /* ���ĳɹ� */
    QIOT_SUBCRIBE_ERR = 10300,  /* ����ʧ�� */
};
enum
{
    QIOT_SEND_SUCC_TRANS = 10200,    /* ͸�����ݷ��ͳɹ� */
    QIOT_SEND_ERR_TRANS = 10300,     /* ͸�����ݷ���ʧ�� */
    QIOT_SEND_SUCC_PHYMODEL = 10210, /* ��ģ�����ݷ��ͳɹ� */
    QIOT_SEND_ERR_PHYMODEL = 10310,  /* ��ģ�����ݷ���ʧ�� */
    QIOT_SEND_SUCC_LOC = 10220,      /* ��λ���ݷ��ͳɹ� */
    QIOT_SEND_ERR_FAIL_LOC = 10320,  /* ��λ���ݷ���ʧ�� */
    QIOT_SEND_SUCC_STATE = 10230,    /* ״̬���ݷ��ͳɹ� */
    QIOT_SEND_ERR_STATE = 10330,     /* ״̬���ݷ���ʧ�� */
    QIOT_SEND_SUCC_INFO = 10240,     /* �豸��Ϣ���ͳɹ� */
    QIOT_SEND_ERR_INFO = 10340,      /* �豸��Ϣ����ʧ�� */
};
enum
{
    QIOT_RECV_SUCC_TRANS = 10200,         /* �յ�͸������ */
    QIOT_RECV_SUCC_PHYMODEL_RECV = 10210, /* �յ���ģ���·����� */
    QIOT_RECV_SUCC_PHYMODEL_REQ = 10211,  /* �յ���ģ���������� */
    QIOT_RECV_SUCC_SUB_STATE_REQ = 10220, /* �յ����豸״̬�������� */
    QIOT_RECV_SUCC_SUB_INFO_REQ = 10230,  /* �յ����豸��Ϣ�������� */
    QIOT_RECV_ERR_BUFFER = 10473,         /* ����ʧ��,�յ����ݵ����ȳ���ģ��buffer���ƣ�AT�ǻ���ģʽ����Ч*/
    QIOT_RECV_ERR_LIMIT = 10428,          /* ���ݽ���ʧ�ܣ��豸��������Ϣͨ�ţ�����ģʽ����Ч */
};
enum
{
    QIOT_LOGOUT_SUCC = 10200, /* �Ͽ����ӳɹ� */
};
enum
{
    QIOT_OTA_TASK_NOTIFY = 10700, /* ���������� */
    QIOT_OTA_START = 10701,       /* ģ�鿪ʼ���� */
    QIOT_OTA_DOWNLOADING = 10702, /* �������� */
    QIOT_OTA_DOWNLOADED = 10703,  /* ��������� */
    QIOT_OTA_UPDATING = 10704,    /* �������� */
    QIOT_OTA_UPDATE_OK = 10705,   /* ��������� */
    QIOT_OTA_UPDATE_FAIL = 10706, /* ������ʧ�� */
    QIOT_OTA_UPDATE_FLAG = 10707, /* �׸��豸��������㲥 */
};
enum
{
    QIOT_SERVER_ERRCODE_RATE_LIMIT = 10428,
    QIOT_SERVER_ERRCODE_QUANTITY_LIMIT = 10429,
};
enum
{
    QIOT_SUB_DEV_ERR_No_ASSOCIATION = 10440, /* ���豸�뵱ǰ����û�й�����ϵ */
    QIOT_SUB_DEV_ERR_ALREADY_CONN = 10441,   /* ���豸�ظ���¼ */
    QIOT_SUB_DEV_ERR_UNLOGIN = 10442,        /* ���豸δ��¼ */
};
/* ql_iotDp.h */
typedef enum
{
    QIOT_DPCMD_TYPE_SYS = 0, /* sys�������� */
    QIOT_DPCMD_TYPE_BUS,     /* ҵ��������������*/
    QIOT_DPCMD_TYPE_OTA,     /* OTA�������� */
    QIOT_DPCMD_TYPE_LAN,     /* LAN�������� */
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
 * @brief ttlv�����ڴ�
 * @param ttlvHead ttlv����ͷ
 * @retval �޷���ֵ
 */
void Ql_iotTtlvFree(void **ttlvHead);
/**
 * ���� @brief ��ȡttlv����ڵ����
 * ���� @param ttlvHead ttlv����ͷָ��
 * ��� @return ���ؽڵ����
 */
quint32_t Ql_iotTtlvCountGet(const void *ttlvHead);
/**
 * ���� @brief ��ȡָ��ttlv����ڵ��id�Լ���������
 * ���� @param ttlvHead ����ͷ
 * ���� @param index ttlv�ڵ�����
 * ��� @param id ���ݽڵ�id
 * ��� @param type ���ݽڵ�����
 * ��� @retval ���ݽڵ�ָ�룻NULL��ʾ��ȡʧ��
 * ��ע @remark ����ֵʹ����ɺ������ͷ�
 */
void *Ql_iotTtlvNodeGet(const void *ttlvHead, quint16_t index, quint16_t *id, QIot_dpDataType_e *type);
/**
 * ���� @brief ��ȡ�ڵ���������
 * ���� @param ttlvNode ���ݽڵ�
 * ��� @param type ���ݽڵ�����
 * ��� @retval �Ƿ�ɹ���ȡ���ýڵ�
 */
qbool Ql_iotTtlvNodeGetType(const void *ttlvNode, QIot_dpDataType_e *type);
/**
 * ���� @brief ��ȡbool�ڵ����������
 * ���� @param ttlvNode ���ݽڵ�
 * ��� @param value ���ݽڵ�����
 * ��� @retval �Ƿ�ɹ���ȡ�ڵ�����
 */
qbool Ql_iotTtlvNodeGetBool(const void *ttlvNode, qbool *value);
/**
 * ���� @brief ��ȡ��������������������
 * ���� @param ttlvNode ���ݽڵ�
 * ��� @param value ���ݽڵ�����
 * ��� @retval �Ƿ�ɹ���ȡ�ڵ�����
 */
qbool Ql_iotTtlvNodeGetInt(const void *ttlvNode, qint64_t *value);
/**
 * ���� @brief ��ȡ�ڵ㸡������������
 * ���� @param ttlvNode ���ݽڵ�
 * ��� @param value �ڵ���ֵ����
 * ��� @retval �Ƿ�ɹ���ȡ�ڵ�����
 */
qbool Ql_iotTtlvNodeGetFloat(const void *ttlvNode, double *value);
/**
 * ���� @brief ��ȡ�ڵ���ַ�����������
 * ���� @param ttlvNode ���ݽڵ�
 * ��� @retval ���ؽڵ��ַ������ݵ�ַ��NULL��ʾ��ȡʧ��
 * ��ע @remark ����ֵʹ����ɺ������ͷ�
 */
char *Ql_iotTtlvNodeGetString(const void *ttlvNode);
/**
 * ���� @brief ��ȡ�ڵ��Byte��������
 * ���� @param ttlvNode ���ݽڵ�
 * ��� @param value ���ݽڵ�����
 * ��� @retval �������ݳ��ȣ�0��ʾ��ȥʧ��
 * ��ע @remark ��������ʹ����ɺ������ͷ�
 */
quint32_t Ql_iotTtlvNodeGetByte(const void *ttlvNode, quint8_t **value);
/**
 * ���� @brief ��ȡ�ڵ��strut����
 * ���� @param ttlvNode ���ݽڵ�
 * ��� @retval ttlv����ָ��
 * ��ע @remark ����ֵʹ����ɺ������ͷ�
 */
void *Ql_iotTtlvNodeGetStruct(const void *ttlvNode);
/**
 * ���� @brief ��ȡָ��id�ڵ���������
 * ���� @param ttlvHead ttlv����ͷָ��
 * ���� @param id ���ݽڵ�id
 * ��� @param type ���ݽڵ�����
 * ��� @retval �����Ƿ�ִ�гɹ�
 */
qbool Ql_iotTtlvIdGetType(const void *ttlvHead, quint16_t id, QIot_dpDataType_e *type);
/**
 * ���� @brief ��ȡָ��id�ڵ�bool��������
 * ���� @param ttlvHead ttlv����ͷָ��
 * ���� @param id ���ݽڵ�id
 * ��� @param value ���ݽڵ��bool����
 * ��� @retval �����Ƿ�ִ�гɹ�
 */
qbool Ql_iotTtlvIdGetBool(const void *ttlvHead, quint16_t id, qbool *value);
/**
 * ���� @brief ��ȡָ��id�ڵ��������������
 * ���� @param ttlvHead ttlv����ͷָ��
 * ���� @param id ���ݽڵ�id
 * ��� @param value ���ݽڵ�������������
 * ��� @retval �����Ƿ�ִ�гɹ�
 */
qbool Ql_iotTtlvIdGetInt(const void *ttlvHead, quint16_t id, qint64_t *value);
/**
 * ���� @brief ��ȡָ��id�ڵ�ĸ�������������
 * ���� @param ttlvHead ttlv����ͷָ��
 * ���� @param id ���ݽڵ�id
 * ��� @param value ���ݽڵ�ĸ�������������
 * ��� @retval �����Ƿ�ִ�гɹ�
 */
qbool Ql_iotTtlvIdGetFloat(const void *ttlvHead, quint16_t id, double *value);
/**
 * ���� @brief ��ȡָ��id�ڵ���ַ�����������
 * ���� @param ttlvHead ttlv����ͷָ��
 * ���� @param id ���ݽڵ�id
 * ��� @retval ���ݽڵ��ַ������ݣ�NULL��ʾִ��ʧ��
 * ��ע @remark ����ֵʹ����ɣ������ͷ�
 */
char *Ql_iotTtlvIdGetString(const void *ttlvHead, quint16_t id);
/**
 * ���� @brief ��ȡָ��id�ڵ��Byte��������
 * ���� @param ttlvHead ttlv����ͷָ��
 * ���� @param id ���ݽڵ�id
 * ��� @param value �ڵ�Byte��������
 * ��� @retval ���ؽڵ��������ݳ��ȣ�0��ʾִ��ʧ��
 * ��ע @remark ��������ʹ����������ͷ�
 */
quint32_t Ql_iotTtlvIdGetByte(const void *ttlvHead, quint16_t id, quint8_t **value);
/**
 * ���� @brief ��ȡָ���ڵ������-strut����
 * ���� @param ttlvHead ttlv����ͷָ��
 * ���� @param id ���ݽڵ�id
 * ��� @retval ttlv������ͷָ��
 * ��ע @remark ����ֵ�����ͷ�
 */
void *Ql_iotTtlvIdGetStruct(const void *ttlvHead, quint16_t id);

/* idΪ0ʱ��Ϊ�������ڵ� */
/**
 * ���� @brief ��ttlv���������bool���ͽڵ�
 * ���� @param ttlvHead ����ͷָ��
 * ���� @param id ��ӽڵ��id
 * ���� @param value ��ӽڵ����������
 * ��� @retval �Ƿ���ӳɹ�
 */
qbool Ql_iotTtlvIdAddBool(void **ttlvHead, quint16_t id, qbool value);
/**
 * ���� @brief ��ttlv����������������ͽڵ�
 * ���� @param ttlvHead ����ͷָ��
 * ���� @param id ��ӽڵ��id
 * ���� @param value ��ӽڵ����������
 * ��� @retval �Ƿ���ӳɹ�
 */
qbool Ql_iotTtlvIdAddInt(void **ttlvHead, quint16_t id, qint64_t num);
/**
 * ���� @brief ��ttlv��������Ӹ��������ͽڵ�
 * ���� @param ttlvHead ����ͷָ��
 * ���� @param id ��ӽڵ��id
 * ���� @param value ��ӽڵ����������
 * ��� @retval �Ƿ���ӳɹ�
 */
qbool Ql_iotTtlvIdAddFloat(void **ttlvHead, quint16_t id, double num);
/**
 * ���� @brief ��ttlv��������Ӹ��������ͽڵ㣬 ��Ҫָ��С������󳤶�
 * ���� @param ttlvHead ����ͷָ��
 * ���� @param id ��ӽڵ��id
 * ���� @param value ��ӽڵ����������
 * ��� @retval �Ƿ���ӳɹ�
 */
qbool Ql_iotTtlvIdAddFloat_ex(void **ttlvHead, quint16_t id, double value, quint8_t precision);
/**
 * ���� @brief ��ttlv���������Byte���ͽڵ�
 * ���� @param ttlvHead ����ͷָ��
 * ���� @param id ��ӽڵ��id
 * ���� @param data ��ӽڵ����������
 * ���� @param len �������ݳ���
 * ��� @retval �Ƿ���ӳɹ�
 */
qbool Ql_iotTtlvIdAddByte(void **ttlvHead, quint16_t id, const quint8_t *data, quint32_t len);
/**
 * ���� @brief ��ttlv����������ַ������ͽڵ�
 * ���� @param ttlvHead ����ͷָ��
 * ���� @param id ��ӽڵ��id
 * ���� @param data ��ӽڵ����������
 * ��� @retval �Ƿ���ӳɹ�
 */
qbool Ql_iotTtlvIdAddString(void **ttlvHead, quint16_t id, const char *data);
/**
 * ���� @brief ��ttlv��������ӽṹ�����ͽڵ�
 * ���� @param ttlvHead ����ͷָ��
 * ���� @param id ��ӽڵ��id
 * ���� @param value ��ӽڵ�Ľṹ��ָ��
 * ��� @retval �Ƿ���ӳɹ�
 */
qbool Ql_iotTtlvIdAddStruct(void **ttlvHead, quint16_t id, void *vStruct);
/**
 * ���� @brief ɾ��ttlv�������ƶ�ID�Ľڵ�
 * ���� @param ttlvHead ����ͷָ��
 * ���� @param id �ڵ��id
 */
void Ql_iotTtlvRemove(void **ttlvHead, quint16_t id);

/* ql_iotCmdBus.h */
/**
 * ���� @brief ����͸��������ƽ̨
 * ���� @param mode ����ģʽ��0	QoS = 0����෢��һ��
 *                           1	QoS = 1�����ٷ���һ��
 *                           2	QoS = 2��������һ��
 * ���� @param payload ������������
 * ���� @param len �������ݳ���
 * ��� @retval �Ƿ��ͳɹ�
 */
qbool Ql_iotCmdBusPassTransSend(quint16_t mode, quint8_t *payload, quint32_t len);
/**
 * ���� @brief ������ģ��������ƽ̨
 * ���� @param mode ����ģʽ��0	QoS = 0����෢��һ��
 *                           1	QoS = 1�����ٷ���һ��
 *                           2	QoS = 2��������һ��
 * ���� @param ttlvHead ��ģ��ttlv����ͷָ��
 * ��� @retval �Ƿ��ͳɹ�
 * ��ע @remark �����е���Ql_iotTtlvFree�����ͷ� ttlvHead
 */
qbool Ql_iotCmdBusPhymodelReport(quint16_t mode, const void *ttlvHead);
/**
 * ���� @brief �ظ�ƽ̨��ѯģ����Ϣ
 * ���� @param mode ����ģʽ��0	QoS = 0����෢��һ��
 *                           1	QoS = 1�����ٷ���һ��
 *                           2	QoS = 2��������һ��
 * ���� @param PkgId ƽ̨�·���ѯ��ϢPkgId
 * ���� @param ttlvHead ��ģ��ttlv����ͷָ��
 * ��� @retval �Ƿ��ͳɹ�
 * ��ע @remark �����е���Ql_iotTtlvFree�����ͷ� ttlvHead
 */
qbool Ql_iotCmdBusPhymodelAck(quint16_t mode, quint16_t pkgId, const void *ttlvHead);
/**
 * ���� @brief ����͸��������ƽ̨
 * ���� @param mode ����ģʽ��0	QoS = 0����෢��һ��
 *                           1	QoS = 1�����ٷ���һ��
 *                           2	QoS = 2��������һ��
 * ���� @param payload ������������
 * ���� @param len �������ݳ���
 * ��� @retval 1~65535�����ͳɹ���ϢPkgId��-1������ʧ��
 * ��ע @remark Ϊ�ú���Ql_iotCmdBusPassTransSend����չ��������������ʹ�øú����������е���Ql_iotTtlvFree�����ͷ� ttlvHead
 */
qint32_t Ql_iotCmdBusPassTransSend_ex(quint16_t mode, quint8_t *payload, quint32_t len);
/**
 * ���� @brief ������ģ��������ƽ̨
 * ���� @param mode ����ģʽ��0	QoS = 0����෢��һ��
 *                           1	QoS = 1�����ٷ���һ��
 *                           2	QoS = 2��������һ��
 * ���� @param ttlvHead ��ģ��ttlv����ͷָ��
 * ��� @retval 1~65535�����ͳɹ���ϢPkgId��-1������ʧ��
 * ��ע @remark Ϊ�ú���Ql_iotCmdBusPhymodelReport����չ��������������ʹ�øú���
 */
qint32_t Ql_iotCmdBusPhymodelReport_ex(quint16_t mode, const void *ttlvHead);


/* ql_iotCmdLoc.h */
/**
 * ���� @brief �ϱ�ģ�����ö�λ������ƽ̨
 * ���� @param titleTtlv ��λ�������͵�TTLV����ָ��
 * ��� @retval �����Ƿ�ִ�гɹ�
 * ��ע @remark �����е���Ql_iotTtlvFree�����ͷ� titleTtlv
 */
qbool Ql_iotCmdBusLocReportInside(void *titleTtlv);
/**
 * ���� @brief �ϱ��豸���ö�λ������ƽ̨
 * ���� @param nmeaTtlv NMEA���ݵ�TTLV����ָ��
 * ��� @retval �����Ƿ�ִ�гɹ�
 * ��ע @remark �����е���Ql_iotTtlvFree�����ͷ� nmeaTtlv
 */
qbool Ql_iotCmdBusLocReportOutside(void *nmeaTtlv);
/**
 * ���� @brief ��ȡ���ö�λ����
 * ���� @param titleTttlv ��λ�������͵�TTLV����ָ��
 * ��� @retval ttlv����ͷָ�룬�ڵ��Ƕ�λ���ݣ�null��ʾ��ȡʧ��
 * ��ע @remark ����ֵ��ʹ����ɺ���Ҫ���ú���Ql_iotTtlvFree()�ͷŸñ���
 */
void *Ql_iotLocGetData(const void *titleTtlv);
/**
 * ���� @brief ��ȡ���ö�λ����֧�ֵ�NMEA����
 * ��� @retval ttlv����ͷָ�룬�ڵ�Ϊ��λ֧�ֵ�NMEA���ͣ�NULL��ʾ��ȡʧ��
 * ��ע @remark ����ֵ��ʹ����ɺ���Ҫ���ú���Ql_iotTtlvFree()�ͷŸñ�����
 */
void *Ql_iotLocGetSupList(void);

/**
 * ���� @brief �ϱ�ģ�����ö�λ������ƽ̨
 * ���� @param titleTtlv ��λ�������͵�TTLV����ָ��
 * ��� @retval 1~65535�����ͳɹ���ϢPkgId��-1������ʧ��
 * ��ע @remark Ϊ�ú���Ql_iotCmdBusLocReportInside����չ��������������ʹ�øú����������е���Ql_iotTtlvFree�����ͷ� titleTtlv
 */
qint32_t Ql_iotCmdBusLocReportInside_ex(void *titleTtlv);
/**
 * ���� @brief �ϱ��豸���ö�λ������ƽ̨
 * ���� @param nmeaTtlv NMEA���ݵ�TTLV����ָ��
 * ��� @retval 1~65535�����ͳɹ���ϢPkgId��-1������ʧ��
 * ��ע @remark Ϊ�ú���Ql_iotCmdBusLocReportOutside����չ��������������ʹ�øú����������е���Ql_iotTtlvFree�����ͷ� nmeaTtlv
 */
qint32_t Ql_iotCmdBusLocReportOutside_ex(void *nmeaTtlv);

/* ql_iotCmdOTA.h */
/**
 * ���� @brief ��ƽ̨����OTA�����ƻ�
 * ���� @param mode �����ļ�(SHA256)У�鷽ʽ��
 *                  0 ����Ҫ
 *                  1 ��Ҫ
 * ��� @retval �����Ƿ�ִ�гɹ�
 */
qbool Ql_iotCmdOtaRequest(quint32_t mode);
/**
 * ���� @brief �豸�յ������ƻ�������OTA������Ϊ
 * ���� @param action OTA������Ϊ
 *                    0 �ܾ�����
 *                    1 ȷ������
 *                    2 SOTA����ʱ��MCU֪ͨ������һ��̼�(�����ļ��ϴ�ʱ���޷�һ���Խ��������������ص����أ���ִ�зֿ����أ���һ���������ʱ����MCU��ȡ��MCU��ȡ��ɺ���������һ�������̼�)
 *                    3 MCU����������п�̼���֪ͨƽ̨������� 
 * ��� @retval ����ִ���Ƿ�ɹ�
 */
qbool Ql_iotCmdOtaAction(quint8_t action);
/**
 * ���� @brief MCU��ȡģ�����ص������̼�����
 * ���� @param startAddr ��ȡ�̼���ʼ��λ��
 * ��� @param data ��Ź̼����ݵĻ�����
 * ���� @param maxLen ����ȡ�̼����ݳ���
 * ��� @retval ʵ�ʶ�ȡ���̼����ݳ��ȣ�0��ʾ��ȡʧ��
 */
quint32_t Ql_iotCmdOtaMcuFWDataRead(quint32_t startAddr, quint8_t data[], quint32_t maxLen);

/* ql_iotCmdSys.h */
/* �豸״̬ */
enum
{
    QIOT_DPID_STATUS_BATTERY = 1,   /* ���� */
    QIOT_DPID_STATUS_VOLTAGE = 2,   /* ��ѹ */
    QIOT_DPID_STATUS_SIGNAL = 3,    /* �ź�ǿ�� */
    QIOT_DPID_STATUS_FLASHFREE = 4, /* ʣ��ռ� */
    QIOT_DPID_STATUS_RSRP = 5,      /* �ο��źŽ��չ��� */
    QIOT_DPID_STATUS_RSRQ = 6,      /* LTE�ο��źŽ������� */
    QIOT_DPID_STATUS_SNR = 7,       /* �ź�����ż������� */
    QIOT_DPID_STATUS_MAX,
};
/* ģ����Ϣ */
enum
{
    QIOT_DPID_INFO_MODEL_TYPE = 1,   /* ģ���ͺ� */
    QIOT_DPID_INFO_MODEL_VER = 2,    /* ģ��汾 */
    QIOT_DPID_INFO_MCU_VER = 3,      /* MCU�汾 */
    QIOT_DPID_INFO_CELLID = 4,       /* ��վid */
    QIOT_DPID_INFO_ICCID = 5,        /* SIM���� */
    QIOT_DPID_INFO_MCC = 6,          /* �ƶ����Ҵ��� */
    QIOT_DPID_INFO_MNC = 7,          /* �ƶ�������� */
    QIOT_DPID_INFO_LAC = 8,          /* λ�������� */
    QIOT_DPID_INFO_PHONE_NUM = 9,    /* phone�� */
    QIOT_DPID_INFO_SIM_NUM = 10,     /* SIM�� */
    QIOT_DPID_INFO_SDK_VER = 11,     /* quecthingSDK�汾��*/
    QIOT_DPID_INFO_LOC_SUPLIST = 12, /* ��λ����֧���б� */
    QIOT_DPIO_INFO_DP_VER = 13,      /* ����Э��汾 */
    QIOT_DPIO_INFO_CP_VER = 14,      /* ͨ��Э��汾�� */
    QIOT_DPID_INFO_MAX,
};
/**
 * ���� @brief �豸״̬�ϱ���ƽ̨
 * ���� @param ids �豸״̬ID����
 * ���� @param size �豸״̬ID����
 * ��� @retval �����Ƿ�ִ�гɹ�
 */
qbool Ql_iotCmdSysStatusReport(quint16_t ids[], quint32_t size);
/**
 * ���� @brief �豸��Ϣ�ϱ���ƽ̨
 * ���� @param ids �豸��ϢID����
 * ���� @param size �豸��ϢID����
 * ��� @retval �����Ƿ�ִ�гɹ�
 */
qbool Ql_iotCmdSysDevInfoReport(quint16_t ids[], quint32_t size);
/**
 * ���� @brief ��ȡ�豸״̬
 * ���� @param ids �豸״̬ID����
 * ���� @param size �豸״̬ID����
 * ��� @retval ttlv�����ڵ�Ϊ�豸״̬��NULL��ʾ��ȡʧ��
 * ��ע @remark ����ֵ����ʹ����ɺ�ʹ��Ql_iotTtlvFree()�ͷ���Դ
 */
void *Ql_iotSysGetDevStatus(quint16_t ids[], quint32_t size);
/**
 * ���� @brief ��ȡ�豸��Ϣ
 * ���� @param ids �豸��ϢID����
 * ���� @param size �豸��ϢID����
 * ��� @retval ttlv�����ڵ�Ϊ�豸��Ϣ��NULL��ʾ��ȡʧ��
 * ��ע @remark ����ֵ����ʹ����ɺ�ʹ��Ql_iotTtlvFree()�ͷ���Դ
 */
void *Ql_iotSysGetDevInfo(quint16_t ids[], quint32_t size);
/**
 * ���� @brief �����ɰ�
 * ���� @param bindcode �豸���룻�ַ���Χ��0~9��A~F��ΪNULLʱϵͳ�������
 * ���� @param timeout �ɰ�ʱ�䣬0Ϊȡ����
 * ��� @retval �����Ƿ�ִ�гɹ�
 * ��ע @remark bindcode���ȹ̶�16�ֽ�
 */
qbool Ql_iotDBindcodeSet(const char *bindcode, quint32_t timeout);
/**
 * ���� @brief ��ȡ�豸����Ϣ
 * ��� @param bindcode �豸����
 * ��� @retval �豸��ʣ�೬ʱʱ��
 * ��ע @remark ����ֵʹ���ֱ꣬�Ӷ����������ͷ�
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
/* ����У��λ */
typedef enum
{
    QIOT_MBUART_PARITY_NONE  = 0,
    QIOT_MBUART_PARITY_EVEN  = 1,
    QIOT_MBUART_PARITY_ODD   = 2,
    QIOT_MBUART_PARITY_MARK  = 3,
    QIOT_MBUART_PARITY_SPACE = 4,
}QIot_MBParity_e;
/* ��������λ */
typedef enum
{
    QIOT_MBUART_DATABITS_5  = 0,
    QIOT_MBUART_DATABITS_6  = 1,
    QIOT_MBUART_DATABITS_7  = 2,
    QIOT_MBUART_DATABITS_8  = 3,
}QIot_MBDataBits_e;
/* ����ֹͣλ */
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
 * ���� @brief modbus���ͻص�����
 * ���� @param port ���ں�
 * ���� @param buf ������������
 * ���� @param bufLen ���ݳ���
 * ��� @retval �Ƿ��ͳɹ�
 */
typedef qbool (*QIot_MBSend_f)(quint16_t port, const quint8_t *buf, quint32_t bufLen);
/**
 * ���� @brief modbus ��ʼ���ص�����
 * ���� @param pk �豸�����Ĳ�ƷproductKey
 * ���� @param ps �豸�����Ĳ�ƷproductSecret
 * ���� @param portInfo �����б��ʼ����Ϣ
 * ���� @param portNum ���ںŸ���
 */
typedef void (*QIot_MBInitCb_f)(char *pk, char *ps,QIot_MBPortCfg_t *portInfo[], quint32_t portNum);

/**
 * ���� @brief modbus��ʼ��
 * ���� @param portList ���ں��б�
 * ���� @param portNum ���ںŸ���
 * ���� @param sendFunc �������ݷ��ͺ���
 * ���� @param initCb modbus��ʼ���ص�����
 * ��� @retval �����Ƿ�ִ�гɹ�
 */
qbool Ql_iotMBInit(quint16_t portList[],quint32_t portNum,QIot_MBSend_f sendFunc,QIot_MBInitCb_f initCb);
/**
 * ���� @brief �յ�ƽ̨�·�����ģ������
 * ���� @param ttlvHead ��ģ��ttlv����
 * ��� @retval �����Ƿ�ִ�гɹ�
 */
qbool Ql_iotMBCloudRecv(const void *ttlvHead);
/**
 * ���� @brief �յ�modbus�ӻ�����
 * ���� @param port ���ں�
 * ���� @param data �ӻ���������
 * ���� @param len ���ݳ���
 * ��� @retval �����Ƿ�ִ�гɹ�
 */
qbool Ql_iotMBLocalRecv(quint16_t port,quint8_t *data,quint32_t len);
/**
 * ���� @brief modbus����ע��
 * ��� @retval�����Ƿ�ִ�гɹ�
 */
qbool Ql_iotMBDeinit(void);
/* ql_iotConfig.h */
typedef enum
{
    QIOT_CONNMODE_IDLE, /* ������IOT */
    QIOT_CONNMODE_REQ,  /* �ֶ���������IOT */
    QIOT_CONNMODE_AUTO, /* ��������������IOT ��AT������Ч */
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
 * ���� @brief QuecThing���ܳ�ʼ��
 * ��� @retval �����Ƿ�ִ�гɹ�
 */
qbool Ql_iotInit(void);
/**
 * ���� @brief ����QuecThing����ƽ̨ģʽ
 * ���� @param mode 0���Ͽ���ƽ̨���ӣ�1����������ƽ̨
 * ��� @retval �����Ƿ�ִ�гɹ�
 */
qbool Ql_iotConfigSetConnmode(QIot_connMode_e mode);
/**
 * ���� @brief ��ȡQuecThing����ƽ̨ģʽ
 * ��� @retval 0��δ����ƽ̨��1����������ƽ̨������ֵ�쳣
 */
QIot_connMode_e Ql_iotConfigGetConnmode(void);
/**
 * ���� @brief �����豸��Ʒ��Ϣ
 * ���� @param pk ������Ʒʱ������productKey
 * ���� @param ps ������Ʒʱ������productSecret
 * ��� @retval �����Ƿ�ִ�гɹ�
 */
qbool Ql_iotConfigSetProductinfo(const char *pk, const char *ps);
/**
 * ���� @brief ��ȡ�豸��Ʒ��Ϣ
 * ��� @param pk ������Ʒʱ������productKey
 * ��� @param ps ������Ʒʱ������productSecret
 * ��� @param ver �豸��֤Э��汾��
 * ��ע @remark ���л�ȡ�������ݾ�����Ҫ�ͷţ���ȡ����������ΪNULL����ʾ��ȡʧ��
 */
void Ql_iotConfigGetProductinfo(char **pk, char **ps, char **ver);
/**
 * ���� @brief ���÷�������Ϣ
 * ���� @param type Э�����ͣ���ǰ��֧��1��MQTTЭ��
 * ���� @param serverUrl ��������ַ
 * ��� @retval �����Ƿ�ִ�гɹ�
 */
qbool Ql_iotConfigSetServer(QIot_protocolType_t type, const char *serverUrl);
/**
 * ���� @brief ��ȡ�豸��������Ϣ
 * ��� @param type Э������
 * ��� @param serverUrl ��������ַ��Ϣ
 * ��ע @remark ��������ַ��Ϣʹ����ɺ������ͷ�
 */
void Ql_iotConfigGetServer(QIot_protocolType_t *type, char **serverUrl);
/**
 * ���� @brief �����豸����ʱ��
 * ���� @param lifetime �����������λ���룻��Χ��1~65535��
 * ��� @retval �����Ƿ�ִ�гɹ�
 * ��ע @remark ��ѡ���ò���������Ĭ��ֵΪ120�룻�����ý�ʹ��Ĭ��ֵ
 */
qbool Ql_iotConfigSetLifetime(quint32_t lifetime);
/**
 * ���� @brief ��ȡ�豸�������
 * ��� @retval �����������λ����
 */
quint32_t Ql_iotConfigGetLifetime(void);
/**
 * ���� @brief ����pdp������ID
 * ���� @param contextID PDP������ID
 * ��� @retval �����Ƿ�ִ�гɹ�
 * ��ע @remark ��ѡ���ò�����Ĭ��ֵΪ1��������ʱʹ��Ĭ��ֵ
 */
qbool Ql_iotConfigSetPdpContextId(quint8_t contextID);
/**
 * ���� @brief ��ȡPDP������ID
 * ��� @retval PDP������IDֵ
 */
quint8_t Ql_iotConfigGetPdpContextId(void);
/**
 * ���� @brief ������ƽ̨���Ӽ���ģʽ
 * ���� @param flag TRUE����������
 *                  FLASE���رռ���
 * ��� @retval �����Ƿ�ִ�гɹ�
 */
qbool Ql_iotConfigSetSessionFlag(qbool flag);
/**
 * ���� @brief ��ȡ��ǰ����ƽ̨����ģʽ
 * ��� @retval TRUE���ѿ������ܣ�FALSE��δ��������
 * ��ע @remark Ĭ�Ϲرգ���ѡ���ò���
 */
qbool Ql_iotConfigGetSessionFlag(void);
/**
 * ���� @brief �����û�����汾��(׷�ӵ�ģ��汾��β��)
 * ���� @param appVer �û�����汾��
 * ��� @retval �����Ƿ�ִ�гɹ�
 */
qbool Ql_iotConfigSetAppVersion(const char *appVer); 
/**
 * ���� @brief ��ȡ�汾��
 * ��� @retval ����ģ���Լ��û����ð汾�ţ�NULL��ʾ��ȡʧ��
 * ��ע @remark ��������ֵ����Ҫ�ͷ�
 */
char *Ql_iotConfigGetSoftVersion(void);
/**
 * ���� @brief �����û��汾���Լ����
 * ���� @param compno MCU��ţ����32�ֽ�
 * ���� @param version ��Ŷ�Ӧ������汾��
 * ��� @retval �����Ƿ�ִ�гɹ�
 */
qbool Ql_iotConfigSetMcuVersion(const char *compno, const char *version);
/**
 * ���� @brief ��ȡMCU����Լ��汾��
 * ���� @param compno MCU���
 * ��� @param version MCU��Ŷ�Ӧ�İ汾��
 * ��� @retval MCU��Ŷ�Ӧ�İ汾�ų���
 * ��ע @remark �汾��ʹ����ɺ������ͷ�
 */
quint32_t Ql_iotConfigGetMcuVersion(const char *compno, char **version);
/**
 * ���� @brief ����QuecThing�¼��ص�����
 * ���� @param eventCb �¼��ص�����
 */
void Ql_iotConfigSetEventCB(void (*eventCb)(quint32_t event, qint32_t errcode, const void *value, quint32_t valLen));
/**
 * ���� @brief ��ȡ�豸��ƽ̨������״̬
 * ��� @retval ����״̬
 */
QIot_state_e Ql_iotGetWorkState(void);
/**
 * ���� @brief �����Զ����豸��ʶ�Լ���ʶ��Ӧ���豸��Կ
 * ���� @param dk �Զ����豸��ʶ������4~16�ֽ�
 * ���� @param ds �Զ����豸��ʶ��Ӧ���豸��Կ�����ȹ̶�32�ֽ�
 * ��� @retval �����Ƿ�ִ�гɹ�
 * ��ע @remark ����dk�ǿ��Լ���Ĭ��ֵʱ�����������豸��Կ��dk�Լ�dsΪ��ʱ���������dk��ds���ظ�ʹ��Ĭ��dk��dk��Ϊ�գ�dsΪ��ʱ�����ds
 */
qbool Ql_iotConfigSetDkDs(const char *dk, const char *ds);
/**
 * ���� @brief ��ȡ�Զ����豸��ʶ�Լ��豸��Կ 
 * ��� @param dk �Զ����豸��ʶ
 * ��� @param ds �Զ����豸��ʶ��Ӧ��ds
 * ��� @retval �����Ƿ�ִ�гɹ�
 * ��ע @remark ����ʹ����ɺ������ͷ�
 */
qbool Ql_iotConfigGetDkDs(char **dk, char **ds);
/**
 * ���� @brief �����豸��Կ�Լ�bindcode
 * ��� @retval �����Ƿ�ִ�гɹ�
 */

void Ql_iotRst(void);

/* ql_HOtaConfig.h */
/**
 * ���� @brief �¼��ص�����
 * ���� @param event �¼�����
 * ���� @param errcode �¼���
 * ���� @param value ��������
 * ���� @param valLen �������ݳ���
 * ��ע @remark �����¼��ص�û���������ݣ���value����ΪNULL
 */
typedef void (*eventCb_f)(quint32_t event, qint32_t errcode, const void *value, quint32_t valLen);
/**
 * ���� @brief ����HTTP OTA�¼��ص�����
 * ���� @param eventCb �¼��ص�����
 */
void Ql_iotHttpOtaSetEventCb(eventCb_f eventCb);
/**
 * ���� @brief ����HTTP OTA�����Լ���ƽ̨���������ƻ�
 * ���� @param battery �豸��ǰ��������Χ0~100
 * ���� @param upmode ����ģʽ��1���ع̼�����ɺ��Զ�����
 * ���� @param pk ������Ʒʱ���ɵ�productKey
 * ���� @param ps ������Ʒʱ���ɵ�productSecret
 * ���� @param url HTTP OTAƽ̨��ַ
 * ��� @retval �����Ƿ�ִ�гɹ�
 */
qbool Ql_iotHttpOtaReq(quint8_t battery, quint8_t upmode,const char *pk,const char *ps, const char *url);
/**
 * ���� @brief ��ȡHTTP OTA������Ϣ
 * ��� @param battery �豸����
 * ��� @param upmode �豸����ģʽ
 * ��� @param pk ������Ʒʱ���ɵ�productKey
 * ���� @param ps ������Ʒʱ���ɵ�productSecret
 * ���� @param url HTTP OTAƽ̨��ַ
 * ��ע @remark ��ȡ�����������������ͷ�
 */
void Ql_iotHttpOtaGet(quint8_t *battery, quint8_t *upmode,char **pk,char **ps, char **url);

/* ql_iotGwDev.h */
/**
 * ���� @brief ���豸�¼��ص�����
 * ���� @param event �¼�����
 * ���� @param errcode �¼���
 * ���� @param subPk ���豸��ƷproductKey
 * ���� @param subDk ���豸Ψһ��ʶ
 * ���� @param value ��������
 * ���� @param valLen �������ݳ���
 */
typedef void (*SubEventCb_f)(quint32_t event, qint32_t errcode, const char *subPk, const char *subDk, const void *value, quint32_t valLen);
/**
 * ���� @brief �������豸�¼��ص�����
 * ���� @param eventCb �¼��ص�����
 */
void Ql_iotConfigSetSubDevEventCB(SubEventCb_f eventCb);
/**
 * ���� @brief ���豸��������
 * ���� @param subPk ���豸��ƷproductKey
 * ���� @param subPs ���豸��ƷproductSecret
 * ���� @param subDk ���豸Ψһ��ʶ
 * ���� @param subDs ���豸��Կ(��һ������ʱΪ�գ���֤�ɹ��󣬿ɻ�ȡ�����豸��Կ)
 * ���� @param sessionType ���豸ͨ��������ƽ̨�����Ƿ���Ҫ���ܣ�0�������ܣ�1������
 * ���� @param keepalive ���豸����ʱ�䣻��λ����
 * ��� @retval �����Ƿ�ִ�гɹ�
 */
qbool Ql_iotSubDevConn(const char *subPk, const char *subPs, const char *subDk, const char *subDs, quint8_t sessionType, quint16_t keepalive);
/**
 * ���� @brief ���豸�Ͽ�����
 * ���� @param subPk ���豸��ƷproductKey
 * ���� @param subDk ���豸Ψһ��ʶ
 * ��� @retval �����Ƿ�ִ�гɹ�
 */
qbool Ql_iotSubDevDisconn(const char *subPk, const char *subDk);
/**
 * ���� @brief ���豸����͸��������ƽ̨
 * ���� @param subPk ���豸��ƷproductKey
 * ���� @param subDk ���豸Ψһ��ʶ
 * ���� @param payload ͸����������
 * ���� @param payloadLen ͸�����ݳ���
 * ��� @retval �����Ƿ�ִ�гɹ�
 */
qbool Ql_iotSubDevPassTransSend(const char *subPk, const char *subDk, quint8_t *payload, quint16_t payloadlen);
/**
 * ���� @brief ���豸������ģ��������ƽ̨
 * ���� @param subPk ���豸��ƷproductKey
 * ���� @param subDk ���豸Ψһ��ʶ
 * ���� @param ttlvHead ��ģ��ttlv����
 * ��� @retval �����Ƿ�ִ�гɹ�
 * ��ע @remark ��ģ��ttlvHead��Դ�������ͷ�
 */
qbool Ql_iotSubDevTslReport(const char *subPk, const char *subDk, const void *ttlvHead);
/**
 * ���� @brief ���豸�ظ�ƽ̨��ģ�Ͳ�ѯָ��
 * ���� @param subPk ���豸��ƷproductKey
 * ���� @param subDk ���豸Ψһ��ʶ
 * ���� @param pkgId ƽ̨��ѯ��ģ����ϢpkgId
 * ���� @param ttlvHead ��ģ��ttlv����
 * ��� @retval ��ģ��ttlvHead��Դ�������ͷ�
 */
qbool Ql_iotSubDevTslAck(const char *subPk, const char *subDk, quint16_t pkgId, const void *ttlvHead);
/**
 * ���� @brief ���豸ע��
 * ���� @param subPk ���豸��ƷproductKey
 * ���� @param subPs ���豸��ƷproductSecret
 * ���� @param subDk ���豸Ψһ��ʶ
 * ���� @param subDs ���豸��Կ
 * ��� @retval ����ִ�н��
 * ��ע @remark ���豸ע����subDs���޷���½ƽ̨����Ҫ������֤
 */
qbool Ql_iotSubDevDeauth(const char *subPk, const char *subPs, const char *subDk, const char *subDs);
/**
 * ���� @brief ˢ�����豸��������󽻻�ʱ��
 * ���� @param subPk ���豸��ƷproductKey
 * ���� @param subDk ���豸Ψһ��ʶ
 * ��� @retval �����Ƿ�ִ�гɹ�
 */
qbool Ql_iotSubDevHTB(const char *subPk, const char *subDk);
/**
 * ���� @brief ���豸����͸��������ƽ̨
 * ���� @param subPk ���豸��ƷproductKey
 * ���� @param subDk ���豸Ψһ��ʶ
 * ���� @param payload ͸����������
 * ���� @param payloadLen ͸�����ݳ���
 * ��� @retval 1~65535�����ͳɹ���ϢPkgId��-1������ʧ��
 */
qint32_t Ql_iotSubDevPassTransSend_ex(const char *subPk, const char *subDk, quint8_t *payload, quint16_t payloadlen);
/**
 * ���� @brief ���豸������ģ��������ƽ̨
 * ���� @param subPk ���豸��ƷproductKey
 * ���� @param subDk ���豸Ψһ��ʶ
 * ���� @param ttlvHead ��ģ��ttlv����
 * ��� @retval 1~65535�����ͳɹ���ϢPkgId��-1������ʧ��
 * ��ע @remark ��ģ��ttlvHead��Դ�������ͷţ��ú���ΪQl_iotSubDevTslReport()������չ����������ʹ�øú���
 */
qint32_t Ql_iotSubDevTslReport_ex(const char *subPk, const char *subDk, const void *ttlvHead);
#endif
