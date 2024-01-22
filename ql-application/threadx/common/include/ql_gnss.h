/*================================================================
  Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/
#ifndef _QL_GNSS_H_
#define _QL_GNSS_H_

#ifdef __cplusplus
	 extern "C" {
#endif
#include <time.h>

#define QL_GSV_MAX_SATS  (10)

typedef enum
{
    AGPS_GNSS_DISABLE,
    AGPS_GNSS_ENABLE
}ql_AGPSGnssSW;
typedef enum
{
    APFLASH_GNSS_DISABLE,
    APFLASH_GNSS_ENABLE
}ql_APFLASHGnssSW;

typedef enum{
	QGPS_RESET_COLD,
	QGPS_RESET_HOT,
	QGPS_RESET_WARM
}ql_GPS_RESET_t;

typedef struct {
    char             gps_sate_num;
    char             gps_sate_vaild_num;
    char             bds_sate_num;
    char             bds_sate_vaild_num;
    char             gal_sate_num;
    char             gal_sate_vaild_num;
    char             glo_sate_num;
    char             glo_sate_vaild_num;

}quec_gnss_sate_num_t;

typedef void (*gnss_ephemeris_info)(quec_gnss_sate_num_t * gnss_sate_num);

typedef struct ql_gnss_location_struct {

    /*�Ƿ���Ч��λ*/
    unsigned char valid;
    /*����*/
    double longitude;
    /*����E(����)��W(����)*/
    unsigned char longitude_cardinal;
    /*γ��*/
    double latitude;
    /*γ��N(��γ)��S(��γ)*/
    unsigned char latitude_cardinal;
    /*hdop����*/
    float  hdop;
    /*phop����*/
    float pdop;
    /*���� 0-360*/
    float heading;
    /*�ٶ� km/h*/
    float gps_speed;
    /*�ź�ǿ��,max=5, data from avg_snr*/
    unsigned char gps_signal;
    /*����ź�?? db*/
    unsigned int max_cnr;
    unsigned int max_cnr2;
    /*��С�ź�?? db*/
    unsigned int min_cnr;
    /*ƽ���ź�?? db*/
    unsigned int avg_cnr;
    /*�ź�ֵ��??*/
    unsigned int cnrs[QL_GSV_MAX_SATS];
    unsigned int cnrs_index;
    /*��λ��������*/
    unsigned int satellites_num;
    /*���θ߶�*/
    float altitude;
    /*FWVER*/
    char fwver[32];
    struct tm time;
    unsigned char quality;
    unsigned char navmode;
     /*��λģʽ*/
    unsigned char fix_mode;
    /*VTG���������� ��λ����*/
    double sog;
    /*VTG���������� ��λ��km/h*/
    double kph;
    /*VTG�����溽��*/
    double cogt;
}ql_gnss_location_t;

enum{
   STR_MODE,
   PACKET_MODE
};

typedef void (*gnss_callback)(char *data, int len);

/***********************************************************************
 *
 * Name:   ql_gnss_open    
 *
 * Description: ��gnss
 *
 * Parameters:  cb:gnss nmea�ص�����
 *             
 * Returns:     0���򿪳ɹ�
 *              
 * Notes:
 *
 ***********************************************************************/
int ql_gnss_open(gnss_callback cb);
/***********************************************************************
 *
 * Name:   ql_gnss_close    
 *
 * Description: �ر�gnss
 *
 * Parameters:  none
 *             
 * Returns:     0���رճɹ�
 *              other: faile
 * Notes:
 *
 ***********************************************************************/
int ql_gnss_close(void);
/***********************************************************************
 *
 * Name:   ql_gnss_cfgsys_set    
 *
 * Description: ����gnssϵͳ���ڵ���ql_gnss_open֮ǰ������Ч
 *
 * Parameters:	sys_type:
 *						 0	 GPS
 *						 1	 GPS + BeiDou
 *						 3	 GPS + GLONASS + Galileo
 *						 4	 GPS + GLONASS
 *						 5	 GPS + BeiDou + Galileo
 *						 6	 GPS + Galileo
 *						 7	 BeiDou			   
 * Returns: 	 0 �����óɹ�
 *				��0������ʧ��
 * Notes:
 *
 ***********************************************************************/
int ql_gnss_cfgsys_set(int sys_type);

/***********************************************************************
 *
 * Name:   ql_gnss_cfgmsg_set	
 *
 * Description: ����gnss�³���nmea������ͣ��ڵ���ql_gnss_open֮ǰ������Ч����ql_gnss_cfgsys_set֮�����ã�ԭ��ϵͳ�л���nmea���ָ�Ĭ��ֵ
 *
 * Parameters:	nmea_type		   
 *						 0	 ��ֹ���NMEA���
 *						bit: 0	 GGA
 *						bit: 1	 RMC
 *						bit: 2	 GSV
 *						bit: 3	 GSA
 *						bit: 4   VTG
 *						bit: 5   GLL
 * Returns: 	 0 �����óɹ�
 *				��0������ʧ��
 * Notes:
 *
 ***********************************************************************/
int ql_gnss_cfgmsg_set(int nmea_type);

/***********************************************************************
 *
 * Name:   ql_gnss_agps_cfg	
 *
 * Description: ����agps���ܣ��ڵ���ql_gnss_open֮ǰ������Ч
 *
 * Parameters:	gnssagpsflag		   
 *						AGPS_GNSS_DISABLE,
 *   					AGPS_GNSS_ENABLE
 *              agps_type
 *                      bit: 0   GPS
 *                      bit: 1   BDS
 *                      bit: 2   GL
 *                      bit: 3   GA
 *                      bit: 4   QZ                
 * Returns: 	 0 �����óɹ�
 *				��0������ʧ��
 * Notes:
 *
 ***********************************************************************/
int ql_gnss_agps_cfg(ql_AGPSGnssSW gnssagpsflag , char agps_type);

/***********************************************************************
 *
 * Name:   ql_gnss_apflash_cfg	
 *
 * Description: ����apflash���ܣ��ڵ���ql_gnss_open֮ǰ������Ч
 *
 * Parameters:	gnssapflashflag		   
 *						APFLASH_GNSS_DISABLE,
 *   					APFLASH_GNSS_ENABLE
 * Returns: 	 0 �����óɹ�
 *				��0������ʧ��
 * Notes:
 *
 ***********************************************************************/
int ql_gnss_apflash_cfg(ql_APFLASHGnssSW gnssapflashflag);

/***********************************************************************
 *
 * Name:   ql_gnss_reset_type_set	
 *
 * Description: ����gnssоƬ��������������gnss���nmea�����ٵ��ã�����ᵼ���쳣���ߵ�����Ч
 *
 * Parameters:	type		   
 *						QGPS_RESET_COLD,
 *						QGPS_RESET_HOT,
 *						QGPS_RESET_WARM
 * Returns: 	 0 �����óɹ�
 *				��0������ʧ��
 * Notes:
 *
 ***********************************************************************/
int ql_gnss_reset_type_set(ql_GPS_RESET_t type);

/***********************************************************************
 *
 * Name:   ql_gnss_get_location	
 *
 * Description: ��ȡ��λ����
 *
 * Parameters:	lolcation	��������ָ���ȡ����ַ��ֱ�ӷ��ʽṹ��ָ�뼴�ɻ�ȡ��λ����Ϣ	   
 *						
 *   					
 * Returns: 	 0 ��������Ч
 *				��0��������Ч
 * Notes:
 *
 ***********************************************************************/
int ql_gnss_get_location(ql_gnss_location_t **lolcation);

/***********************************************************************
 *
 * Name:   ql_get_agps_sate_num	
 *
 * Description: ע���ȡagps�������Ǹ��������ܲ��붨λ�����Ǹ�����
 *              �˻ص�������gnss�������Ա�����open gnss�ٵ���,����ᵼ���쳣
 * Parameters:	   
 *						
 *   					
 * Returns: 	 
 *				
 * Notes:
 *
 ***********************************************************************/
void ql_get_agps_sate_num( gnss_ephemeris_info cb);
/***********************************************************************
 *
 * Name:   ql_set_agps_file
 *
 * Description: �û�������������agps�ļ���ʹ�ô˽ӿھ�û��Ҫʹ���Զ�agps������
 *              �˽ӿڱ�����gnss ���nmea�����ٵ��ã�����agps�޷���Ч
 *
 * Parameters:	   
 *						
 *   					
 * Returns: 	 0��success
 *				
 * Notes:
 *
 ***********************************************************************/
int ql_set_agps_file(void);
/***********************************************************************
 *
 * Name:   ql_send_agps_to_gps
 *
 * Description: �û������Լ���agps���ݣ������ɿͻ��Լ���������ȡ
 *              �˽ӿڱ�����gnss ���nmea�����ٵ��ã�����agps�޷���Ч
 * Parameters:	   
 *						
 *   					
 * Returns: 	 0��success
 *				
 * Notes:
 *
 ***********************************************************************/

int ql_send_agps_to_gps(char *data,int len);
/***********************************************************************
 *
 * Name:   ql_set_gnss_nmea_mode
 *
 * Description: ����nmea�����ʽ��0:һ��nmea��䴥��һ�λص�
 *                                1:1s���ڴ���һ�λص���һ�ν�����nmea������
 *
 * Parameters:	   
 *						
 *   					
 * Returns: 	 0��success
 *				
 * Notes:
 *
 ***********************************************************************/
int ql_set_gnss_nmea_mode(char mode);

/***********************************************************************
 *
 * Name:   ql_monitor_param_print
 *
 * Description:���ڲ鿴agps�������������������ʱ�䣬apflash�������������ʱ��
 * write flash ����                               
 *
 * Parameters:	   
 *						
 *   					
 * Returns: 	
 *				
 * Notes:
 *
 ***********************************************************************/
void ql_monitor_param_print(void);


#ifdef __cplusplus
	} /*"C" */
#endif

#endif /* _QL_GNSS_H_ */


