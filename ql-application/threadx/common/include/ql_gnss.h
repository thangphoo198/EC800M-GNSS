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

    /*是否有效定位*/
    unsigned char valid;
    /*经度*/
    double longitude;
    /*经度E(东经)或W(西经)*/
    unsigned char longitude_cardinal;
    /*纬度*/
    double latitude;
    /*纬度N(北纬)或S(南纬)*/
    unsigned char latitude_cardinal;
    /*hdop精度*/
    float  hdop;
    /*phop精度*/
    float pdop;
    /*航向 0-360*/
    float heading;
    /*速度 km/h*/
    float gps_speed;
    /*信号强度,max=5, data from avg_snr*/
    unsigned char gps_signal;
    /*最大信号?? db*/
    unsigned int max_cnr;
    unsigned int max_cnr2;
    /*最小信号?? db*/
    unsigned int min_cnr;
    /*平均信号?? db*/
    unsigned int avg_cnr;
    /*信号值数??*/
    unsigned int cnrs[QL_GSV_MAX_SATS];
    unsigned int cnrs_index;
    /*定位卫星数量*/
    unsigned int satellites_num;
    /*海拔高度*/
    float altitude;
    /*FWVER*/
    char fwver[32];
    struct tm time;
    unsigned char quality;
    unsigned char navmode;
     /*定位模式*/
    unsigned char fix_mode;
    /*VTG：地面速率 单位：节*/
    double sog;
    /*VTG：地面速率 单位：km/h*/
    double kph;
    /*VTG：地面航向*/
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
 * Description: 打开gnss
 *
 * Parameters:  cb:gnss nmea回调函数
 *             
 * Returns:     0：打开成功
 *              
 * Notes:
 *
 ***********************************************************************/
int ql_gnss_open(gnss_callback cb);
/***********************************************************************
 *
 * Name:   ql_gnss_close    
 *
 * Description: 关闭gnss
 *
 * Parameters:  none
 *             
 * Returns:     0：关闭成功
 *              other: faile
 * Notes:
 *
 ***********************************************************************/
int ql_gnss_close(void);
/***********************************************************************
 *
 * Name:   ql_gnss_cfgsys_set    
 *
 * Description: 设置gnss系统，在调用ql_gnss_open之前设置生效
 *
 * Parameters:	sys_type:
 *						 0	 GPS
 *						 1	 GPS + BeiDou
 *						 3	 GPS + GLONASS + Galileo
 *						 4	 GPS + GLONASS
 *						 5	 GPS + BeiDou + Galileo
 *						 6	 GPS + Galileo
 *						 7	 BeiDou			   
 * Returns: 	 0 ：设置成功
 *				非0：设置失败
 * Notes:
 *
 ***********************************************************************/
int ql_gnss_cfgsys_set(int sys_type);

/***********************************************************************
 *
 * Name:   ql_gnss_cfgmsg_set	
 *
 * Description: 设置gnss吐出的nmea语句类型，在调用ql_gnss_open之前设置生效，在ql_gnss_cfgsys_set之后设置，原因：系统切换，nmea语句恢复默认值
 *
 * Parameters:	nmea_type		   
 *						 0	 禁止输出NMEA语句
 *						bit: 0	 GGA
 *						bit: 1	 RMC
 *						bit: 2	 GSV
 *						bit: 3	 GSA
 *						bit: 4   VTG
 *						bit: 5   GLL
 * Returns: 	 0 ：设置成功
 *				非0：设置失败
 * Notes:
 *
 ***********************************************************************/
int ql_gnss_cfgmsg_set(int nmea_type);

/***********************************************************************
 *
 * Name:   ql_gnss_agps_cfg	
 *
 * Description: 设置agps功能，在调用ql_gnss_open之前设置生效
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
 * Returns: 	 0 ：设置成功
 *				非0：设置失败
 * Notes:
 *
 ***********************************************************************/
int ql_gnss_agps_cfg(ql_AGPSGnssSW gnssagpsflag , char agps_type);

/***********************************************************************
 *
 * Name:   ql_gnss_apflash_cfg	
 *
 * Description: 设置apflash功能，在调用ql_gnss_open之前设置生效
 *
 * Parameters:	gnssapflashflag		   
 *						APFLASH_GNSS_DISABLE,
 *   					APFLASH_GNSS_ENABLE
 * Returns: 	 0 ：设置成功
 *				非0：设置失败
 * Notes:
 *
 ***********************************************************************/
int ql_gnss_apflash_cfg(ql_APFLASHGnssSW gnssapflashflag);

/***********************************************************************
 *
 * Name:   ql_gnss_reset_type_set	
 *
 * Description: 设置gnss芯片冷热温启动，在gnss输出nmea语句后再调用，否则会导致异常或者调用无效
 *
 * Parameters:	type		   
 *						QGPS_RESET_COLD,
 *						QGPS_RESET_HOT,
 *						QGPS_RESET_WARM
 * Returns: 	 0 ：设置成功
 *				非0：设置失败
 * Notes:
 *
 ***********************************************************************/
int ql_gnss_reset_type_set(ql_GPS_RESET_t type);

/***********************************************************************
 *
 * Name:   ql_gnss_get_location	
 *
 * Description: 获取定位数据
 *
 * Parameters:	lolcation	给个二级指针获取到地址后直接访问结构体指针即可获取到位置信息	   
 *						
 *   					
 * Returns: 	 0 ：数据有效
 *				非0：数据无效
 * Notes:
 *
 ***********************************************************************/
int ql_gnss_get_location(ql_gnss_location_t **lolcation);

/***********************************************************************
 *
 * Name:   ql_get_agps_sate_num	
 *
 * Description: 注册获取agps星历卫星个数；可能参与定位的卫星个数；
 *              此回调函属于gnss触发所以必须先open gnss再调用,否则会导致异常
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
 * Description: 用户用于主动发送agps文件，使用此接口就没必要使能自动agps功能了
 *              此接口必须在gnss 输出nmea语句后再调用，否则agps无法起效
 *
 * Parameters:	   
 *						
 *   					
 * Returns: 	 0：success
 *				
 * Notes:
 *
 ***********************************************************************/
int ql_set_agps_file(void);
/***********************************************************************
 *
 * Name:   ql_send_agps_to_gps
 *
 * Description: 用户发送自己的agps数据，数据由客户自己服务器获取
 *              此接口必须在gnss 输出nmea语句后再调用，否则agps无法起效
 * Parameters:	   
 *						
 *   					
 * Returns: 	 0：success
 *				
 * Notes:
 *
 ***********************************************************************/

int ql_send_agps_to_gps(char *data,int len);
/***********************************************************************
 *
 * Name:   ql_set_gnss_nmea_mode
 *
 * Description: 设置nmea输出方式，0:一条nmea语句触发一次回调
 *                                1:1s钟内触发一次回调，一次将整包nmea语句输出
 *
 * Parameters:	   
 *						
 *   					
 * Returns: 	 0：success
 *				
 * Notes:
 *
 ***********************************************************************/
int ql_set_gnss_nmea_mode(char mode);

/***********************************************************************
 *
 * Name:   ql_monitor_param_print
 *
 * Description:用于查看agps服务器请求次数、请求时间，apflash请求次数、请求时间
 * write flash 次数                               
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


