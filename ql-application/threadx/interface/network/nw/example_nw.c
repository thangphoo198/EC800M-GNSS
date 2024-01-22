/*============================================================================
  Copyright (c) 2017 Quectel Wireless Solution, Co., Ltd.  All Rights Reserved.
  Quectel Wireless Solution Proprietary and Confidential.
 =============================================================================*/
/*===========================================================================

                        EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.


WHEN        WHO            WHAT, WHERE, WHY
----------  ------------   ----------------------------------------------------
24/07/2019  Nebula.li      create
13/06/2022  Sharon.li      增加设置网络模式后，立刻查询注册状态的example
=============================================================================*/

#include <stdio.h>
#include "ql_nw.h"
#include "ql_rtos.h"
#include "ql_application.h"

//#define QL_DUAL_SIM_SUPPORT
#define QL_WIFISCAN_SUPPORT

ql_task_t ql_test_task_ref;
void ql_nw_notify_cb(unsigned int ind_flag, void *ind_msg_buf, unsigned int ind_msg_len, void *contextPtr)
{
    switch(ind_flag)
    {
        case QL_NW_IND_VOICE_REG_EVENT_FLAG:
        {
             QL_NW_COMMON_REG_STATUS_INFO_T  *voice_reg_status=(QL_NW_COMMON_REG_STATUS_INFO_T  *)ind_msg_buf;
                printf("QL_NW_IND_VOICE_REG_EVENT:\n\
state:%d; lac:0x%x; cid:0x%x; rat:%d; rejectCause:%d; psc:0x%x;\n", 
                        voice_reg_status->state,
                        voice_reg_status->lac,
                        voice_reg_status->cid,
                        voice_reg_status->rat,
                        voice_reg_status->rejectCause,
                        voice_reg_status->psc);
        }
        break;
        case QL_NW_IND_DATA_REG_EVENT_FLAG:
        {
             QL_NW_COMMON_REG_STATUS_INFO_T  *data_reg_status=(QL_NW_COMMON_REG_STATUS_INFO_T  *)ind_msg_buf;
                printf("QL_NW_IND_DATA_REG_EVENT:\n\
state:%d; lac:0x%x; cid:0x%x; rat:%d; rejectCause:%d;\n", 
                        data_reg_status->state,
                        data_reg_status->lac,
                        data_reg_status->cid,
                        data_reg_status->rat,
                        data_reg_status->rejectCause);
        }
        break;
        case QL_NW_IND_SIGNAL_STRENGTH_EVENT_FLAG:
        {
            QL_NW_SIGNAL_STRENGTH_INFO_T *signal=(QL_NW_SIGNAL_STRENGTH_INFO_T *)ind_msg_buf;
            printf("QL_NW_IND_SIGNAL_STRENGTH_EVENT:\n");
            printf("GW: rssi:%d; bitErrorRate:%d; rscp:%d; ecno:%d;\n",
            signal->GW_SignalStrength.rssi,
            signal->GW_SignalStrength.bitErrorRate,
            signal->GW_SignalStrength.rscp,
            signal->GW_SignalStrength.ecno);
            printf("LTE: rssi:%d; rsrp:%d; rsrq:%d; cqi:%d;\n",
            signal->LTE_SignalStrength.rssi,
            signal->LTE_SignalStrength.rsrp,
            signal->LTE_SignalStrength.rsrq,
            signal->LTE_SignalStrength.cqi);
        }
        break;
        case QL_NW_IND_NITZ_TIME_UPDATE_EVENT_FLAG:
        {
            QL_NW_NITZ_TIME_INFO_T  *time_info=(QL_NW_NITZ_TIME_INFO_T *)ind_msg_buf;
            printf("QL_NW_IND_NITZ_TIME_UPDATE_EVENT:\nnitz_time:%s; abs_time:%ld; leap_sec:%d\n",time_info->nitz_time,time_info->abs_time,time_info->leap_sec);
            printf("now time:%ld\n",time(NULL));
        }
        break;
    }
}

void ql_nw_dsds_notify_cb(unsigned int ind_flag, void *ind_msg_buf, unsigned int ind_msg_len, void *contextPtr, unsigned simid)
{

	printf ("\n\n====================ql_nw_dsds_notify_cb:[%d]===================\r\n", simid);
    switch(ind_flag)
    {
        case QL_NW_IND_VOICE_REG_EVENT_FLAG:
        {
             QL_NW_COMMON_REG_STATUS_INFO_T  *voice_reg_status=(QL_NW_COMMON_REG_STATUS_INFO_T  *)ind_msg_buf;
                printf("QL_NW_DSDS_IND_VOICE_REG_EVENT:\n\
state:%d; lac:0x%x; cid:0x%x; rat:%d; rejectCause:%d; psc:0x%x;\n", 
                        voice_reg_status->state,
                        voice_reg_status->lac,
                        voice_reg_status->cid,
                        voice_reg_status->rat,
                        voice_reg_status->rejectCause,
                        voice_reg_status->psc);
        }
        break;
        case QL_NW_IND_DATA_REG_EVENT_FLAG:
        {
             QL_NW_COMMON_REG_STATUS_INFO_T  *data_reg_status=(QL_NW_COMMON_REG_STATUS_INFO_T  *)ind_msg_buf;
                printf("QL_NW_DSDS_IND_DATA_REG_EVENT:\n\
state:%d; lac:0x%x; cid:0x%x; rat:%d; rejectCause:%d;\n", 
                        data_reg_status->state,
                        data_reg_status->lac,
                        data_reg_status->cid,
                        data_reg_status->rat,
                        data_reg_status->rejectCause);
        }
        break;
        case QL_NW_IND_SIGNAL_STRENGTH_EVENT_FLAG:
        {
            QL_NW_SIGNAL_STRENGTH_INFO_T *signal=(QL_NW_SIGNAL_STRENGTH_INFO_T *)ind_msg_buf;
            printf("QL_NW_DSDS_IND_SIGNAL_STRENGTH_EVENT:\n");
            printf("GW: rssi:%d; bitErrorRate:%d; rscp:%d; ecno:%d;\n",
            signal->GW_SignalStrength.rssi,
            signal->GW_SignalStrength.bitErrorRate,
            signal->GW_SignalStrength.rscp,
            signal->GW_SignalStrength.ecno);
            printf("LTE: rssi:%d; rsrp:%d; rsrq:%d; cqi:%d;\n",
            signal->LTE_SignalStrength.rssi,
            signal->LTE_SignalStrength.rsrp,
            signal->LTE_SignalStrength.rsrq,
            signal->LTE_SignalStrength.cqi);
        }
        break;
        case QL_NW_IND_NITZ_TIME_UPDATE_EVENT_FLAG:
        {
            QL_NW_NITZ_TIME_INFO_T  *time_info=(QL_NW_NITZ_TIME_INFO_T *)ind_msg_buf;
            printf("QL_NW_DSDS_IND_NITZ_TIME_UPDATE_EVENT:\nnitz_time:%s; abs_time:%ld; leap_sec:%d\n",time_info->nitz_time,time_info->abs_time,time_info->leap_sec);
            printf("now time:%ld\n",time(NULL));
        }
        break;
    }
}

#ifdef QL_WIFISCAN_SUPPORT

void ql_wifiscan_callback (const unsigned short scan_count, const char *scan_info)
{
	printf ("=[APP]==wiifscan:%d\n %s===\r\n", scan_count, scan_info);
}


void ql_nw_test_wifiscan_task()
{
	ql_rtos_task_sleep_s(40);
	QL_NW_ERROR_CODE ret = 0;
	printf("\n\n============ql nw wifiscan start============\n");

	while(1)
	{
		ql_nw_set_wifiscan_callback(ql_wifiscan_callback);
		ret = ql_nw_get_wifiscan_info(15000,2,10,5,1,0);//超时时间15s,搜索10个

		printf("Start wifiscan ret(%d), wait result\r\n",ret);

		ql_rtos_task_sleep_s(20);
	}
}


//application_init(ql_nw_test_wifiscan_task, "ql_nw_test_wifiscan_task", 10, 0);

#endif

void ql_nw_test_task(void *arg)
{
	int i=0,j=0,ret=0,mode=0,csq=0;	
	int recv_cnt=0,send_cnt=0;
	
	int k =10;
	while(k--)
	{
		printf("send_cnt:%d,recv_cnt:%d\n", send_cnt, recv_cnt);
		ql_rtos_task_sleep_s(5);
		
		ql_nw_set_gdcnt(1);
		ql_nw_get_gdcnt( &send_cnt,&recv_cnt);
	}
	
#ifdef QL_DUAL_SIM_SUPPORT
	unsigned short simid = 0;
	QL_NW_GET_INFO_T* ql_nw_get_s = malloc(sizeof(QL_NW_GET_INFO_T));	
	if (ql_nw_get_s == NULL)
	{
		printf ("++++ql_nw_get memory malloc failure!");
		return; 	
	}

	unsigned long ql_nw_cmd = 0;
	//ql_nw_cmd |= QNW_CMD_GET_CELL;				
	
	ql_nw_cmd |= QNW_CMD_GET_CONFIG;
	ql_nw_cmd |= QNW_CMD_GET_CSQ;
	ql_nw_cmd |= QNW_CMD_GET_OPERATOR;
	ql_nw_cmd |= QNW_CMD_GET_REG_STATUS;
	ql_nw_cmd |= QNW_CMD_GET_SELECTION;
	ql_nw_cmd |= QNW_CMD_GET_SIGNAL_STRENGTH;
	ql_nw_cmd |= QNW_CMD_GET_CELL;
	ql_nw_cmd |= QNW_CMD_GET_MNC_MCC;	
	ql_nw_cmd |= QNW_CMD_GET_NITZ_TIME;				
	
	ql_nw_event_register(0x0f);
	ql_nw_add_dsds_event_handler(ql_nw_dsds_notify_cb, NULL);

	while(j<2)
	{		
		printf("\n\n====================ql nw test[%d] start===================\n", j);
		ql_rtos_task_sleep_s(30);

		memset (ql_nw_get_s, 0, sizeof(QL_NW_GET_INFO_T));
		ret = ql_nw_get_info (ql_nw_cmd, ql_nw_get_s,simid);
		printf("++++nql_nw_get_config ret=%d preferred_nw_mode:%d; roaming_pref:%d\n",ret,ql_nw_get_s->get_config_info.preferred_nw_mode,ql_nw_get_s->get_config_info.roaming_pref);

		printf("++++get_reg_status data: state:%d; lac:0x%x; cid:0x%x; rat:%d; rejectCause:%d;\n", 
				ql_nw_get_s->get_reg_status.data_reg.state,
				ql_nw_get_s->get_reg_status.data_reg.lac,
				ql_nw_get_s->get_reg_status.data_reg.cid,
				ql_nw_get_s->get_reg_status.data_reg.rat,
				ql_nw_get_s->get_reg_status.data_reg.rejectCause);

		printf("++++ql_nw_get_csq ret=%d csq:%d\n",ret,ql_nw_get_s->csq);	

		printf("++++get_signal_strength LTE: rssi:%d; rsrp:%d; rsrq:%d; cqi:%d;\n",
				ql_nw_get_s->get_signal_strength.LTE_SignalStrength.rssi,
				ql_nw_get_s->get_signal_strength.LTE_SignalStrength.rsrp,
				ql_nw_get_s->get_signal_strength.LTE_SignalStrength.rsrq,
				ql_nw_get_s->get_signal_strength.LTE_SignalStrength.cqi);

		printf("++++get_operator_name ret = %d long_eons:%s; short_eons:%s; mcc:%s; mnc:%s\n", 
			ret,ql_nw_get_s->get_operator_name.long_eons,ql_nw_get_s->get_operator_name.short_eons,
			ql_nw_get_s->get_operator_name.mcc,ql_nw_get_s->get_operator_name.mnc);

		printf("++++get_selection ret = %d nw_selection_mode:%d; mcc:%s; mnc:%s; act:%d\n",
			ret,
			ql_nw_get_s->get_selection.nw_selection_mode,
			ql_nw_get_s->get_selection.mcc,
			ql_nw_get_s->get_selection.mnc,
			ql_nw_get_s->get_selection.act);
		
		printf("++++get_nitz_info ret = %d nitz_time:%s; abs_time:%ld; leap_sec:%d\n", 
			ret,ql_nw_get_s->get_nitz_info.nitz_time,ql_nw_get_s->get_nitz_info.abs_time,
			ql_nw_get_s->get_nitz_info.leap_sec);

		printf("++++lte_info_valid:%d  lte_info_num:%d\r\n", ql_nw_get_s->get_cell_info.lte_info_valid, ql_nw_get_s->get_cell_info.lte_info_num);
		if(ql_nw_get_s->get_cell_info.lte_info_valid)
		{
			for(i=0;i<ql_nw_get_s->get_cell_info.lte_info_num;i++)
			{
				printf("++++get_cell_info %d [LTE] cid:%d, mcc:%d, mnc:%d, tac:%d, pci:%d, earfcn:%d, rssi:%d\n",
				i,
				ql_nw_get_s->get_cell_info.lte_info[i].cid,
				ql_nw_get_s->get_cell_info.lte_info[i].mcc,
				ql_nw_get_s->get_cell_info.lte_info[i].mnc,
				ql_nw_get_s->get_cell_info.lte_info[i].tac,
				ql_nw_get_s->get_cell_info.lte_info[i].pci,
				ql_nw_get_s->get_cell_info.lte_info[i].earfcn,
				ql_nw_get_s->get_cell_info.lte_info[i].rssi);
			}
		}
		j++;
		simid++;
	}
	
	//free(ql_nw_get_s);

#else	

	QL_NW_CONFIG_INFO_T  *ql_nw_config_info=calloc(1,sizeof(QL_NW_CONFIG_INFO_T));
	QL_NW_NITZ_TIME_INFO_T  *ql_nw_nitz_time_info=calloc(1,sizeof(QL_NW_NITZ_TIME_INFO_T));
	QL_NW_OPERATOR_INFO_T  *ql_nw_operator_name_info=calloc(1,sizeof(QL_NW_OPERATOR_INFO_T));
	QL_NW_REG_STATUS_INFO_T  *ql_nw_reg_status=calloc(1,sizeof(QL_NW_REG_STATUS_INFO_T));
	QL_NW_SIGNAL_STRENGTH_INFO_T  *ql_nw_signal_strength=calloc(1,sizeof(QL_NW_SIGNAL_STRENGTH_INFO_T));
	QL_NW_SELECTION_INFO_T  *ql_nw_selection_info=calloc(1,sizeof(QL_NW_SELECTION_INFO_T));
	QL_NW_CELL_INFO_T  *ql_nw_cell_info=malloc(sizeof(QL_NW_CELL_INFO_T));

	ql_nw_event_register(0x0f);
	ql_nw_add_event_handler(ql_nw_notify_cb, NULL);
	ql_rtos_task_sleep_s(5);
	while(j<10000)
	{
	 	j++;
		ql_rtos_task_sleep_s(10);
		printf("\n\n====================ql nw test[%d] start===================\n", j);
		ret=ql_nw_get_config(ql_nw_config_info);
		printf("\nql_nw_get_config ret=%d\n preferred_nw_mode:%d; roaming_pref:%d\n",ret,ql_nw_config_info->preferred_nw_mode,ql_nw_config_info->roaming_pref);

		
        ret=ql_nw_get_reg_status(ql_nw_reg_status);
        printf("\nql_nw_get_reg_status ret = %d\n",ret);
 		printf("voice: state:%d; lac:0x%x; cid:0x%x; rat:%d; rejectCause:%d; psc:0x%x;\n", 
                ql_nw_reg_status->voice_reg.state,
                ql_nw_reg_status->voice_reg.lac,
                ql_nw_reg_status->voice_reg.cid,
                ql_nw_reg_status->voice_reg.rat,
                ql_nw_reg_status->voice_reg.rejectCause,
                ql_nw_reg_status->voice_reg.psc);
		printf("data: state:%d; lac:0x%x; cid:0x%x; rat:%d; rejectCause:%d;\n", 
                ql_nw_reg_status->data_reg.state,
                ql_nw_reg_status->data_reg.lac,
                ql_nw_reg_status->data_reg.cid,
                ql_nw_reg_status->data_reg.rat,
                ql_nw_reg_status->data_reg.rejectCause);
		
		ret=ql_nw_get_csq(&csq);
		printf("\nql_nw_get_csq ret=%d\n csq:%d\n",ret,csq);

        ret=ql_nw_get_signal_strength(ql_nw_signal_strength);
        printf("\nql_nw_get_signal_strength ret = %d\n", ret);
        printf("GW: rssi:%d; bitErrorRate:%d; rscp:%d; ecno:%d;\n",
        ql_nw_signal_strength->GW_SignalStrength.rssi,
        ql_nw_signal_strength->GW_SignalStrength.bitErrorRate,
        ql_nw_signal_strength->GW_SignalStrength.rscp,
        ql_nw_signal_strength->GW_SignalStrength.ecno);
        printf("LTE: rssi:%d; rsrp:%d; rsrq:%d; cqi:%d;\n",
        ql_nw_signal_strength->LTE_SignalStrength.rssi,
        ql_nw_signal_strength->LTE_SignalStrength.rsrp,
        ql_nw_signal_strength->LTE_SignalStrength.rsrq,
        ql_nw_signal_strength->LTE_SignalStrength.cqi);
		
        ret=ql_nw_get_operator_name(ql_nw_operator_name_info);
        printf("\nql_nw_get_operator_name ret = %d\n long_eons:%s; short_eons:%s; mcc:%s; mnc:%s\n", ret,ql_nw_operator_name_info->long_eons,ql_nw_operator_name_info->short_eons,ql_nw_operator_name_info->mcc,ql_nw_operator_name_info->mnc);

		
        ret=ql_nw_get_selection(ql_nw_selection_info);
        printf("\nql_nw_get_selection ret = %d\n nw_selection_mode:%d; mcc:%s; mnc:%s; act:%d\n",
        ret,
        ql_nw_selection_info->nw_selection_mode,
        ql_nw_selection_info->mcc,
        ql_nw_selection_info->mnc,
        ql_nw_selection_info->act);

		
        ret=ql_nw_get_nitz_time_info(ql_nw_nitz_time_info);
        printf("\nql_nw_get_nitz_time_info ret = %d\n nitz_time:%s; abs_time:%ld; leap_sec:%d\n", ret,ql_nw_nitz_time_info->nitz_time,ql_nw_nitz_time_info->abs_time,ql_nw_nitz_time_info->leap_sec);
		
		/**获取当前服务和邻区的信息**/
        ret=ql_nw_get_cell_info(ql_nw_cell_info);
        printf("\nql_nw_get_ql_nw_cell_info ret = %d\n", ret);
        if(ql_nw_cell_info->gsm_info_valid)
        {
            for(i=0;i<ql_nw_cell_info->gsm_info_num;i++)
            {
                printf("Cell_%d [GSM] cid:%d, mcc:%d, mnc:%d, lac:%d, arfcn:%d, bsic:%d, rssi:%d\n",
                i,
                ql_nw_cell_info->gsm_info[i].cid,
                ql_nw_cell_info->gsm_info[i].mcc,
                ql_nw_cell_info->gsm_info[i].mnc,
                ql_nw_cell_info->gsm_info[i].lac,
                ql_nw_cell_info->gsm_info[i].arfcn,
                ql_nw_cell_info->gsm_info[i].bsic,
				ql_nw_cell_info->gsm_info[i].rssi);
            }
        }
        if(ql_nw_cell_info->umts_info_valid)
        {
            for(i=0;i<ql_nw_cell_info->umts_info_num;i++)
            {
                printf("Cell_%d [UMTS] cid:%d, lcid:%d, mcc:%d, mnc:%d, lac:%d, uarfcn:%d, psc:%d, rssi:%d\n",
                i,
                ql_nw_cell_info->umts_info[i].cid,
                ql_nw_cell_info->umts_info[i].lcid,
                ql_nw_cell_info->umts_info[i].mcc,
                ql_nw_cell_info->umts_info[i].mnc,
                ql_nw_cell_info->umts_info[i].lac,
                ql_nw_cell_info->umts_info[i].uarfcn,
                ql_nw_cell_info->umts_info[i].psc,
				ql_nw_cell_info->umts_info[i].rssi);
            }
        }
        if(ql_nw_cell_info->lte_info_valid)
        {
            for(i=0;i<ql_nw_cell_info->lte_info_num;i++)
            {
                printf("Cell_%d [LTE] cid:%d, mcc:%d, mnc:%d, tac:%d, pci:%d, earfcn:%d, rssi:%d\n",
                i,
                ql_nw_cell_info->lte_info[i].cid,
                ql_nw_cell_info->lte_info[i].mcc,
                ql_nw_cell_info->lte_info[i].mnc,
                ql_nw_cell_info->lte_info[i].tac,
                ql_nw_cell_info->lte_info[i].pci,
                ql_nw_cell_info->lte_info[i].earfcn,
				ql_nw_cell_info->lte_info[i].rssi);
            }
        }
		
		printf("====================ql nw test[%d] end===================\n\n", j);
	}
#endif

}


//测试获取当前服务小区和邻区信息的接口
static void ql_test_cell_task(void)
{
	int ret = 0,i=0;
	
	QL_NW_CELL_INFO_T  *ql_nw_cell_info=malloc(sizeof(QL_NW_CELL_INFO_T));
	
	while(1)
	{
		ql_rtos_task_sleep_s(30);
		/**获取当前服务和邻区的信息**/
		ret=ql_nw_get_cell_info(ql_nw_cell_info);
        if(ql_nw_cell_info->lte_info_valid)
        {
            for(i=0;i<ql_nw_cell_info->lte_info_num;i++)
            {
				if(ql_nw_cell_info->lte_info[i].flag == 0)//服务小区
				{
                	printf("\nServingcell Cell_%d [LTE] cid:%d, mcc:%d, mnc:%d, tac:%d, pci:%d, earfcn:%d, rssi:%d\n",
		                i,
		                ql_nw_cell_info->lte_info[i].cid,
		                ql_nw_cell_info->lte_info[i].mcc,
		                ql_nw_cell_info->lte_info[i].mnc,
		                ql_nw_cell_info->lte_info[i].tac,
		                ql_nw_cell_info->lte_info[i].pci,
		                ql_nw_cell_info->lte_info[i].earfcn,
						ql_nw_cell_info->lte_info[i].rssi);
				}
				else//邻区
				{
                	printf("\nNeighbourcell Cell_%d [LTE] cid:%d, mcc:%d, mnc:%d, tac:%d, pci:%d, earfcn:%d, rssi:%d\n",
		                i,
		                ql_nw_cell_info->lte_info[i].cid,
		                ql_nw_cell_info->lte_info[i].mcc,
		                ql_nw_cell_info->lte_info[i].mnc,
		                ql_nw_cell_info->lte_info[i].tac,
		                ql_nw_cell_info->lte_info[i].pci,
		                ql_nw_cell_info->lte_info[i].earfcn,
						ql_nw_cell_info->lte_info[i].rssi);
				}
            }
        }


	}
}





void ql_nw_set_test_task()
{
	QL_NW_CONFIG_INFO_T info;
	int ret;
	int drx = 0;
	int sendbyte = 0,recvbyte = 0;
	
	info.preferred_nw_mode = QL_NW_PREF_NET_TYPE_LTE;//仅搜索LTE制式
	info.roaming_pref = 1;
	
	ql_rtos_task_sleep_s(3);
	ql_nw_set_config(&info);

	while(1)
	{   
		drx = 0;
		ret = ql_network_register_wait(10); 
		if(0 == ret)//说明注册成功
		{
			ql_nw_get_drxtm(&drx);
			ql_nw_get_gdcnt(&sendbyte,&recvbyte);//流量统计
		}
		
		printf("%s@%d,ql_nw_wait_register ret(%d),drx(%d),sendbyte(%d),recvbyte(%d)\r\n",__func__,__LINE__,ret,drx,sendbyte,recvbyte);
		ql_rtos_task_sleep_s(10);
	}

}



int ql_nw_test_init(void *arg)
{
	QlOSStatus   status;

	status =ql_rtos_task_create(&ql_test_task_ref, 4096, 100, "ql_nw_test_task", ql_nw_test_task, NULL);
	return 0;
}

//application_init(ql_test_cell_task, "ql_nw_test_init", 2, 0);


