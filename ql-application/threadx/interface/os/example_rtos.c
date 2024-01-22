/*================================================================
  Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/

#include "ql_type.h"
#include "ql_func.h"
#include "ql_rtos.h"
#include "ql_application.h"
#include <stdio.h>
#include <string.h>
#include "ql_gpio.h"
#include "ql_boot.h"
static int counter=5;

ql_task_t taskRef1;
ql_task_t taskRef2;
ql_task_t taskRef3;
ql_task_t taskRef4;
ql_task_t taskRef5;
ql_task_t taskRef6;


ql_sem_t  semaRef;
ql_flag_t flagRef;
ql_mutex_t  mutexRef;

ql_queue_t keymsgQRef;//队列的句柄
#define KEYMSGQSIZE 8 /*队列的大小,可容纳消息的个数*/
#define KEYMSGSIZE  8 /*队列中每条消息的大小*/


static void __gpio_irq_handler_gpio05(void)
{
	PIN_LEVEL_E value;
	u8 pinvalue = 0;
	
	ql_gpio_get_level(GPIO_PIN_NO_5, &value);

	if(value == PIN_LEVEL_HIGH)
	{
		pinvalue = 1;
	}
	else
	{
		pinvalue = 0;
	}
	
	ql_rtos_queue_release(keymsgQRef, sizeof(u8), &pinvalue, QL_NO_WAIT);
	ql_eint_enable(GPIO_PIN_NO_5, PIN_BOTH_EDGE);	//is needed to active isr
}





void task1_queue_test(void * argv)
{
    u8 register1[1]={0x00};

	printf("<-------------------------task1_queue_test------------------------>\r\n");
	ql_eint_register(GPIO_PIN_NO_5, PIN_BOTH_EDGE, PIN_PULL_PU, __gpio_irq_handler_gpio05, NULL);
	
	ql_eint_enable(GPIO_PIN_NO_5, PIN_BOTH_EDGE);
    ql_rtos_queue_create(&keymsgQRef, sizeof(u8), KEYMSGQSIZE);

	while(1)
    {
		ql_rtos_queue_wait(keymsgQRef, register1, sizeof(u8), QL_WAIT_FOREVER);
		switch(register1[0])
		{
			case PIN_LEVEL_LOW:
				printf("get gpio[%d] PIN_LEVEL_LOW\r\n", GPIO_PIN_NO_5);
				break;
			case PIN_LEVEL_HIGH:
				
				printf("get gpio[%d] PIN_LEVEL_HIGH\r\n", GPIO_PIN_NO_5);
				break;
		}
		
    }
}

//application_init(task1_queue_test, "task1_queue_test", 10, 0);

void task2(void * argv)
{
    int register1;
   
    {
        /*
        ql_rtos_mutex_lock(mutexRef, QL_WAIT_FOREVER); 
        Register2=counter;
        Register2= Register2-1;
        ql_rtos_task_sleep_s(1);
        counter= Register2;
        printf("counter = %d \n",counter );
        ql_rtos_mutex_unlock(mutexRef); */
        //ql_rtos_task_sleep_s(5);
        //ql_rtos_flag_release(flagRef, 2, QL_FLAG_OR);
        ql_rtos_semaphore_wait(semaRef, QL_WAIT_FOREVER);
        ql_rtos_semaphore_get_cnt(semaRef,&register1);    
        printf("task2 semaphore cnt = %d \r\n",register1);
        //printf("flag2 set\r\n");
    }
}


void task3(void * argv)
{
    char r_date[128]={0};
    u32 flags=0;
    int register1;
  
    {
        //ql_rtos_queue_wait(msgQRef, r_date, 128, QL_WAIT_FOREVER);
        //ql_rtos_flag_wait(flagRef, 7, QL_FLAG_AND_CLEAR,&flags,QL_WAIT_FOREVER);
        
        ql_rtos_semaphore_wait(semaRef, QL_WAIT_FOREVER);
        ql_rtos_semaphore_get_cnt(semaRef,&register1);    
        printf("task3 semaphore cnt = %d \r\n",register1);
        //printf("flags = 0x%x \r\n",flags );
        
    }
}


void task4(void * argv)
{
    char r_date[128]={0};
    u32 flags=0;
    int register1;
    
    {
        //ql_rtos_queue_wait(msgQRef, r_date, 128, QL_WAIT_FOREVER);
        //ql_rtos_flag_wait(flagRef, 7, QL_FLAG_AND_CLEAR,&flags,QL_WAIT_FOREVER);
        
        ql_rtos_semaphore_wait(semaRef, QL_WAIT_FOREVER);
        ql_rtos_semaphore_get_cnt(semaRef,&register1);    
        printf("task4 semaphore cnt = %d \r\n",register1);
        //printf("flags = 0x%x \r\n",flags );
        
    }
}

void task5(void * argv)
{
    char r_date[128]={0};
    u32 flags=0;
    int register1;
   
    {
        //ql_rtos_queue_wait(msgQRef, r_date, 128, QL_WAIT_FOREVER);
        //ql_rtos_flag_wait(flagRef, 7, QL_FLAG_AND_CLEAR,&flags,QL_WAIT_FOREVER);
        
        ql_rtos_semaphore_wait(semaRef, QL_WAIT_FOREVER);
        ql_rtos_semaphore_get_cnt(semaRef,&register1);    
        printf("task5 semaphore cnt = %d \r\n",register1);
        //printf("flags = 0x%x \r\n",flags );
        
    }
}





void task_test_init(void)
{
    printf("test_start...\r\n");
    //ql_rtos_queue_create(&msgQRef, 128, 8);
    ql_rtos_semaphore_create(&semaRef, 3);
    //ql_rtos_task_create(&taskRef1, 1024, 100,"task1", task1, NULL, 0);//set 1
    ql_rtos_task_create(&taskRef2, 1024, 101, "task2", task2, NULL, 0);//set 2
    //ql_rtos_mutex_create(&mutexRef);
    //ql_rtos_flag_create(&flagRef);
    ql_rtos_task_create(&taskRef3, 1024, 102,"task3", task3, NULL, 0);//printf
    ql_rtos_task_create(&taskRef5, 1024, 103,"task5", task4, NULL, 0);//printf
    ql_rtos_task_create(&taskRef6, 1024, 104,"task6", task5, NULL, 0);//printf
    
}

//application_init(task_test_init, "task_test", 10, 0);




void task_test_mempool_size(void)
{
	unsigned int mempool_size=0, continuous_mempool_size=0;;
	ql_rtos_task_sleep_s(2);
	
	printf("task_test_mempool_size...\r\n");
	
	mempool_size = ql_get_mempool_total_size();							/*current heap total size*/

	continuous_mempool_size = ql_get_mempool_max_freebuf_size();		/*current available for application continuous memory size*/
	printf("mempool_size=%d ;continuous_mempool_size=%d ;\r\n",mempool_size,continuous_mempool_size);

}

//application_init(task_test_mempool_size, "task_test_mempool_size", 10, 0);

