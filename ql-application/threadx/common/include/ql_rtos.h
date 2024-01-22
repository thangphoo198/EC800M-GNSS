/*================================================================
  Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/

#ifndef _QL_RTOS_H
#define _QL_RTOS_H

#include "ql_type.h"

#define QUEC_MAX_TASK_PRIORITY 252

typedef int QlOSStatus;
typedef void * ql_task_t;
typedef void * ql_sem_t;
typedef void * ql_mutex_t;
typedef void * ql_queue_t;
typedef void * ql_timer_t;
typedef void * ql_flag_t;

typedef enum
{
	QL_WAIT_FOREVER = (int)0xFFFFFFFF,
	QL_NO_WAIT	  	= 0
} ql_wait_e;

typedef enum
{
	QL_FLAG_AND 		= 5,
	QL_FLAG_AND_CLEAR 	= 6,
	QL_FLAG_OR 			= 7,
	QL_FLAG_OR_CLEAR	= 8
} ql_flag_op_e;

extern QlOSStatus ql_rtos_task_create
(
	ql_task_t 	* taskRef,				/* OS task reference					   	*/
	u32		  	  stackSize,			/* number of bytes in task stack area	   	*/
	u8	 	      priority,				/* task priority        				   	*/
	char	    * taskName,				/* task name							   	*/
	void	  ( * taskStart)(void*), 	/* pointer to task entry point 	   	   		*/
	void*	      argv,					/* task entry argument pointer			   	*/
	...
);


/*2020-09-04新增带时间轮片任务创建函数 pony ma*/
/*这个接口为带有时间片功能任务创建函数，用这个创建任务内部while可以不加系统延时，在和
不带时间片创建混用时，不带时间片任务一定要加任务延时否则会导致带时间片任务无法运行*/
extern QlOSStatus ql_rtos_task_create_ex
(
	ql_task_t 	* taskRef,				/* OS task reference					   	*/
	u32		  	  stackSize,			/* number of bytes in task stack area	   	*/
	u8	 	      priority,				/* task priority        				   	*/
	char	    * taskName,				/* task name							   	*/
	void	  ( * taskStart)(void*), 	/* pointer to task entry point 	   	   		*/
	void*	      argv,					/* task entry argument pointer			   	*/
	...
);
extern QlOSStatus ql_rtos_task_create_xip
(
	ql_task_t 	* taskRef,				/* OS task reference					   	*/
	u32		  	  stackSize,			/* number of bytes in task stack area	   	*/
	u8	 	      priority,				/* task priority        				   	*/
	char	    * taskName,				/* task name							   	*/
	void	  ( * taskStart)(void*), 	/* pointer to task entry point 	   	   		*/
	void*	      argv,					/* task entry argument pointer			   	*/
	...
);

extern QlOSStatus ql_rtos_task_create_withptr
(
	ql_task_t 	* taskRef,				/* OS task reference					   	*/
    void *      stackPtr,
	u32		  	  stackSize,			/* number of bytes in task stack area	   	*/
	u8	 	      priority,				/* task priority        				   	*/
	char	    * taskName,				/* task name							   	*/
	void	  ( * taskStart)(void*), 	/* pointer to task entry point 	   	   		*/
	void*	      argv,					/* task entry argument pointer			   	*/
	...
);


extern QlOSStatus ql_rtos_task_delete
(
	ql_task_t taskRef		/* OS task reference	*/
);

extern void ql_rtos_task_yield(void);

extern QlOSStatus ql_rtos_task_get_current_ref
(
	ql_task_t * taskRef		/* OS task reference	*/
);

extern QlOSStatus ql_rtos_task_change_priority
(
	ql_task_t 	taskRef,			/* OS task reference			*/
	u8 			new_priority,		/* OS task new priority	for in	*/
	u8	 		*old_priority		/* OS task old priority	for out	*/
);

extern QlOSStatus ql_rtos_task_get_priority
(
	ql_task_t 	taskRef,		/* OS task reference			*/
	u8 * 		priority_ptr	/* OS task priority for out		*/
);

QlOSStatus ql_rtos_task_set_name
(
    ql_task_t   taskRef,        /* OS task reference            */
    char *      name            /*OS task name*/
);

extern void ql_rtos_task_sleep_ms
(
	u32 ms	   /* OS task sleep time for ms	*/
);

extern void ql_rtos_task_sleep_s
(
	u32 s	   /* OS task sleep time for s		*/
);

extern QlOSStatus ql_rtos_task_suspend
(
	ql_task_t taskRef		/* OS task reference	*/
);

extern QlOSStatus ql_rtos_task_resume
(
	ql_task_t taskRef		/* OS task reference	*/
);

extern QlOSStatus ql_rtos_semaphore_create
(
	ql_sem_t  	*semaRef,       /* OS semaphore reference                     	*/
	u32         initialCount    /* initial count of the semaphore             	*/
);

extern QlOSStatus ql_rtos_semaphore_wait
(
	ql_sem_t  	semaRef,       /* OS semaphore reference                     	*/
	u32         timeout    	   /* QL_WAIT_FOREVER, QL_NO_WAIT, or timeout	*/
);

extern QlOSStatus ql_rtos_semaphore_release
(
	ql_sem_t   semaRef        /* OS semaphore reference						*/
);

extern QlOSStatus ql_rtos_semaphore_get_cnt
(
	ql_sem_t  	semaRef,       /* OS semaphore reference           				*/
	u32       * cnt_ptr    	   /* out-parm to save the cnt of semaphore      	*/
);

extern QlOSStatus ql_rtos_semaphore_delete
(
	ql_sem_t   semaRef        /* OS semaphore reference                  		*/
);

extern QlOSStatus ql_rtos_mutex_create
(
    ql_mutex_t  *mutexRef        /* OS mutex reference                         */
);

extern QlOSStatus ql_rtos_mutex_lock
(
	ql_mutex_t    mutexRef,       /* OS mutex reference                         */
	u32           timeout   	  /* mutex wait timeout		             		*/
);

extern QlOSStatus ql_rtos_mutex_try_lock
(
	ql_mutex_t  mutexRef        /* OS mutex reference                         */
);

extern QlOSStatus ql_rtos_mutex_unlock
(
	ql_mutex_t  mutexRef        /* OS mutex reference                         */
);

extern QlOSStatus ql_rtos_mutex_delete
(
	ql_mutex_t  mutexRef        /* OS mutex reference                         */
);

extern QlOSStatus ql_rtos_queue_create
(
	ql_queue_t   	*msgQRef,       	/* OS message queue reference              */
	u32         	maxSize,        	/* max message size the queue supports     */
	u32         	maxNumber	      	/* max # of messages in the queue          */
);

extern QlOSStatus ql_rtos_queue_wait
(
	ql_queue_t   	msgQRef,		/* message queue reference                 		*/
	u8  	      	*recvMsg,       /* pointer to the message received         		*/
	u32         	size, 			/* size of the message                     		*/
	u32         	timeout         /* QL_WAIT_FOREVER, QL_NO_WAIT, or timeout  */
);

extern QlOSStatus ql_rtos_queue_release
(
    ql_queue_t		msgQRef,        /* message queue reference                 			*/
    u32         	size,           /* size of the message                     			*/
    u8          	*msgPtr,        /* start address of the data to be sent    			*/
    u32         	timeout         /* QL_WAIT_FOREVER, QL_NO_WAIT, or timeout   	*/
);

extern QlOSStatus ql_rtos_queue_get_cnt
(
	ql_queue_t		msgQRef,        /* message queue reference                 		*/
	u32     		*cnt_ptr    	/* out-parm to save the cnt of message queue	*/
);

extern QlOSStatus ql_rtos_queue_delete
(
	ql_queue_t	msgQRef         /* message queue reference                 		*/
);

extern QlOSStatus ql_rtos_timer_create
(
	ql_timer_t * timerRef					/* OS supplied timer reference	*/
);

extern QlOSStatus ql_rtos_timer_start
(
	ql_timer_t		timerRef,       			/* OS supplied timer reference             			*/
	u32     	 	initialTime,    			/* initial expiration time in ms           			*/
	unsigned char	cyclicalEn, 				/* wether to enable the cyclical mode or not		*/
	void        	(*callBackRoutine)(u32),    /* timer call-back routine     						*/
	u32      	    timerArgc       			/* argument to be passed to call-back on expiration */
);

extern QlOSStatus ql_rtos_timer_stop
(
	ql_timer_t timerRef 				/* OS supplied timer reference	*/
);

extern QlOSStatus ql_rtos_timer_delete
(
	ql_timer_t timerRef 				/* OS supplied timer reference	*/
);

extern QlOSStatus ql_rtos_flag_create
(
    ql_flag_t	*flagRef       /* OS flag reference              		*/
);
extern QlOSStatus ql_rtos_flag_wait
(
	ql_flag_t		flagRef,		/* OS flag reference 					   		*/
	u32			mask,			/* flag mask to wait for				   		*/
	ql_flag_op_e	operation,		/* QL_FLAG_AND, QL_FLAG_AND_CLEAR,	   		*/
									/* QL_FLAG_OR, QL_FLAG_OR_CLEAR		   		*/
	u32			*flags, 		/* Current value of all flags			   		*/
	u32			timeout 		/* QUEC_WAIT_FOREVER, QUEC_NO_WAIT, or timeout  */
);
extern QlOSStatus ql_rtos_flag_release
(
	ql_flag_t	flagRef,            /* OS flag reference 					   		*/
	u32		mask,               /* flag mask to wait for				   		*/
	ql_flag_op_e		operation           /* QL_FLAG_AND, QL_FLAG_AND_CLEAR,	   		*/
									/* QL_FLAG_OR, QL_FLAG_OR_CLEAR		   		*/
);
extern QlOSStatus ql_rtos_flag_delete
(
	ql_flag_t	flagRef         /* OS flag reference	*/
);

extern u32 ql_get_cpu_usage_rate(void);

extern u32 ql_rtos_get_free_heap_size(void);

/**
 * Name: ql_rtos_get_systicks
 * Description: Number of ticks that passed since last reset.
 * Para: None
 * Returns: u32 Number of ticks that passed since last reset.
 * Note: Increase by 1 per 5ms
 **/
extern u32 ql_rtos_get_systicks(void);
/**
 * Name: ql_ext_memheap_init
 * Description: 初始化用户的heap.
 * Para: start:heap的起始地址 end:heap的结束地址
 * Returns: 
 * Note: 
 **/
unsigned int ql_ext_memheap_init(unsigned int start,unsigned int end);
/**
 * Name: ql_ext_malloc
 * Description: 申请一段内存.
 * Para: size：要申请内存大小
 * Returns: null:申请失败，other:发回申请内存首地址.
 * Note: 
 **/
void* ql_ext_malloc(unsigned int size);
/**
 * Name: ql_get_extheap_freesize
 * Description: 获取用户内存池剩余大小.
 * Para: 
 * Returns: 返回剩余大小.
 * Note:
 **/
unsigned int ql_get_extheap_freesize(void);
/**
 * Name: ql_get_extheap_totalSize
 * Description:获取用户内存池总大小.
 * Para: None
 * Returns: 内存总大小.
 * Note: 
 **/
unsigned int ql_get_extheap_totalSize(void);

extern char *ql_rtos_get_current_task_name(void);//2020-09-04新增读取任务名接口 pony

/*****************************************************************
* Function: ql_get_mempool_total_size
*
* Description:
* 	获取当前heap总大小。
* 
* Parameters:
* 	无 
* Return:
* 	heap总大小。
*
*****************************************************************/
u32 ql_get_mempool_total_size(void);

/*****************************************************************
* Function: ql_get_mempool_max_freebuf_size
*
* Description:
* 	获取当前可用连续内存总大小。
* 
* Parameters:
* 	无。  
* Return:
* 	连续内存总大小。
*
*****************************************************************/
u32 ql_get_mempool_max_freebuf_size(void);
/*****************************************************************
* Function: ql_rtos_get_current_task_name
*
* Description:
* 	获取当前任务名。
* 
* Parameters:
* 	无。  
* Return:
* 	连续内存总大小。
*
*****************************************************************/
char *ql_rtos_get_current_task_name(void);


void *malloc (size_t sz);
void free (void * ptr);
void *realloc (void * ptr, size_t sz);
void *calloc (size_t sz, size_t n);
void ql_rtos_task_switch_in_reg(void *cb);
void ql_icu_switch_in_reg(void *cb);
void ql_ostimer_switch_in_reg(void *cb);
void * ql_rtos_get_current_task_ptr(void);


#endif

