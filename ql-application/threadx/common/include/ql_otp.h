/*================================================================
  Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/
#ifndef __QL_OTP_H
#define __QL_OTP_H

/*****************************************************************
* Function: ql_otp_secboot_whether_enabled
*
* Description:
* 	judge secboot whether enable
* 
* Parameters:
* 	VOID
* Return:
*	return vlue   		meaning   
*	    0  		 		NO-FUSE-ONLY	 		NO-BOOT33-verify 	
*		1				FUSE-ONLY				NO-BOOT33-verify  	
*		2				NO-FUSE-ONLY			BOOT33-verify   		
*		3				FUSE-ONLY				BOOT33-verify   
*****************************************************************/
int ql_otp_secboot_whether_enabled(void);

#endif