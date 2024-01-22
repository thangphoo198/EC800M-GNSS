/*================================================================
  Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/
#ifndef _QL_FOTA_H_
#define _QL_FOTA_H_
#include "ql_ssl_hal.h"

typedef void* qlFotaImgProcCtxPtr;
struct qmini_fotaupl_param
{
	char              path_name[256];
    UINT8             dl_urc_num;     //max number of urc when downloading
    UINT8             dl_urc_cnt;
	UINT8			  down_fail_stop_open;
	UINT8			  dl_first_pkg_suc;
};
typedef enum
{
	QL_FOTA_DWNLD_MOD_FTP,
	QL_FOTA_DWNLD_MOD_HTTP
}qlFotaDwnldMod;

typedef enum
{
	QL_FOTA_SETFLAG = 2,
	QL_FOTA_INPROGRESS = 1,
	QL_FOTA_SUCCEED = 0,
	QL_FOTA_FAIL = -1
}qlFotaSta;

typedef void* qlFotaImgProcCtxPtr;
typedef void (*qlFotaProgressCB_t)(qlFotaSta sta, int progress);
extern int ql_fota_firmware_download(int profile_idx, qlFotaDwnldMod mode, char * address, char * username, char * password, qlFotaProgressCB_t cb);
extern int ql_fota_get_progress(void);

/*****************************************************************
* Function:     ql_fota_init 
* 
* Description:
*               Parameter used for initialization
*               
*
* Parameters:
*               NULL
* Return:        
*               0 , the function execution succeed.
*               其他值, the parameter error.
*****************************************************************/
extern qlFotaImgProcCtxPtr ql_fota_init(void);

/*****************************************************************
* Function:     ql_fota_image_write 
* 
* Description:
*               fota package brush to flash
*               
*
* Parameters:
*               	context:      Parameter
*                   data     	  data to write
*               	len           Length to write
* Return:        
*               0 , the function execution succeed.
*               其他值, the parameter error.
*****************************************************************/
extern int ql_fota_image_write(qlFotaImgProcCtxPtr context, void * data, int len);
/*****************************************************************
* Function:     ql_fota_image_read 
* 
* Description:
*               read fota package data
*               
*
* Parameters:
*               	context:      Parameter
*                   data     	  data to read
*               	len           Length to read
* Return:        
*               0 , the function execution succeed.
*               其他值, the parameter error.
*****************************************************************/
extern int ql_fota_image_read(qlFotaImgProcCtxPtr context, void * data, int len);
/*****************************************************************
* Function:     ql_fota_image_flush 
* 
* Description:
*               fota package brush to flash
*               
*
* Parameters:
*               	context:      Parameter
*
* Return:        
*               0 , the function execution succeed.
*               其他值, the parameter error.
*****************************************************************/
extern int ql_fota_image_flush(qlFotaImgProcCtxPtr context);
/*****************************************************************
* Function:     ql_fota_image_verify 
* 
* Description:
*               verify fota package correct
*               
*
* Parameters:
*               	context:      Parameter
*
* Return:        
*               0 , the function execution succeed.
*               其他值, the parameter error.
*****************************************************************/
extern int ql_fota_image_verify(qlFotaImgProcCtxPtr context);

/*****************************************************************
* Function:     ql_fota_image_verify_without_setflag 
* 
* Description:
*               verify fota package correct
*               
*
* Parameters:
*               	context:      Parameter
*                   fileSize      fota package size
*               	pIsDfota      fota package mode
* Return:        
*               0 , the function execution succeed.
*               其他值, the parameter error.
*****************************************************************/
extern int ql_fota_image_verify_without_setflag(qlFotaImgProcCtxPtr context, int *fileSize, int *pIsDfota);

/*****************************************************************
* Function:     ql_fota_set_update_flag 
* 
* Description:
*               set updater param
*               
*
* Parameters:
*                   fileSize      fota package size
*               	pIsDfota      fota package mode
* Return:        
*               0 , the function execution succeed.
*               其他值, the parameter error.
*****************************************************************/
extern int ql_fota_set_update_flag(int file_size, int is_dfota);


/*****************************************************************
* Function:     ql_fota_deinit 
* 
* Description:
*               Parameter used for uninitialization
*               
*
* Parameters:
*               	context:      Parameter
*
* Return:        
*               0 , the function execution succeed.
*               其他值, the parameter error.
*****************************************************************/
extern void ql_fota_deinit(qlFotaImgProcCtxPtr context);

/*****************************************************************
* Function:     ql_fota_mini_system 
* 
* Description:
*               This function set url for download fotapkg
*               
*
* Parameters:
*               	profile_idx:
*                   mode          ftp/http
*               	host    	  Small system subcontracting url
* 					host2         url bring into correspondence with host
*					username      Server username
* 					password      Server password
* Return:        
*               0 , the function execution succeed.
*               其他值, the parameter error.
*****************************************************************/
extern int ql_fota_mini_system(int profile_idx, qlFotaDwnldMod mode, char * host, char * host2, char * username, char * password);

/*****************************************************************
* Function:     ql_fullfota_app_start 
* 
* Description:
*               This function set url for download fotapkg
*               
*
* Parameters:
*               	profile_idx:
*                   mode          http
*               	host    	  Small system subcontracting url
* 					host2         url bring into correspondence with host
*					username      Server username
* 					password      Server password
* Return:        
*               0 , the function execution succeed.
*               其他值, the parameter error.
*****************************************************************/
extern int ql_fullfota_app_start(char * host);

#endif
