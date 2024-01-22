#include "ql_power.h"
#include "ql_gpio.h"
#include "ql_application.h"

#define test_log(fmt, args...)	printf(fmt, ##args)
#define LPM_GPIO	GPIO_PIN_NO_0

static int g_lpm_fd = -1;
static int g_cnt = 0;
ql_sleep_flags_ref ql_test_sleep_ref = NULL;

void ql_power_test2(void *argv)
{
    ql_autosleep_enable(QL_ALLOW_SLEEP);
    unsigned int get_sleep_flags=0;
    test_log("\r\n===============autosleep_enable===================\r\n");
    
    while(1)
    {
        ql_sleep_flags_create(&ql_test_sleep_ref,"ql_sleep_test");
        ql_sleep_flags_set(ql_test_sleep_ref,0x00000001, QL_SLEEP_FLAGS_OR_MASK);
        ql_sleep_flags_set(ql_test_sleep_ref,0x00000002, QL_SLEEP_FLAGS_OR_MASK);
        ql_sleep_flags_set(ql_test_sleep_ref,0x00000004, QL_SLEEP_FLAGS_OR_MASK);
        ql_sleep_flags_set(ql_test_sleep_ref,0x00000008, QL_SLEEP_FLAGS_OR_MASK);
        ql_get_current_sleep_flags(ql_test_sleep_ref,&get_sleep_flags);
        test_log("get_sleep_flags1=0x%x\r\n",get_sleep_flags);
        ql_rtos_task_sleep_s(20);
        ql_sleep_flags_set(ql_test_sleep_ref,0x0, QL_SLEEP_FLAGS_AND_MASK);
        ql_get_current_sleep_flags(ql_test_sleep_ref,&get_sleep_flags);
        test_log("get_sleep_flags2=0x%x\r\n",get_sleep_flags);
        ql_rtos_task_sleep_s(20);
        ql_sleep_flags_group_delete(ql_test_sleep_ref);
    }
}

void ql_power_test1(void *argv)
{
    ql_autosleep_enable(QL_ALLOW_SLEEP);
    char lock_name[]="sleep_test";
    int lock_fd = 0;   
    while(1)
    {
        lock_fd = ql_lpm_wakelock_create(lock_name, strlen(lock_name)+1);
        ql_lpm_wakelock_lock(lock_fd);
        ql_lpm_wakelock_lock(lock_fd);
        ql_lpm_wakelock_lock(lock_fd);
        ql_lpm_wakelock_lock(lock_fd);
        ql_rtos_task_sleep_s(10);
        printf("one...");
        ql_lpm_wakelock_unlock(lock_fd);
        ql_rtos_task_sleep_s(10);
        ql_lpm_wakelock_unlock(lock_fd);
        printf("two...");
        ql_rtos_task_sleep_s(10);
        ql_lpm_wakelock_unlock(lock_fd);
        printf("three...");
        ql_rtos_task_sleep_s(10);
        ql_lpm_wakelock_unlock(lock_fd);
        printf("four...");
        ql_rtos_task_sleep_s(10);
        ql_lpm_wakelock_delete(lock_fd);
    }
    
}

static void __lpm_irq_handler(void)
{
	PIN_LEVEL_E value;

	if (g_lpm_fd > 0) {
		g_cnt++;
		ql_gpio_get_level( LPM_GPIO, &value);
		if (value) {	//wake_up
			ql_lpm_wakelock_lock(g_lpm_fd);
			
		}
		else {	//sleep
			ql_lpm_wakelock_unlock(g_lpm_fd);
			
		}
	}	
	printf("DBG===lpm_irq_handler() is called!\n");
	ql_eint_enable_wakeup( LPM_GPIO, PIN_BOTH_EDGE);
}

static void quec_lpm_test(void * argv)
{
	int ret = -1;
	int j = 0;
	test_log("=================enter power reset!!================ \n");

	ret = ql_eint_register( LPM_GPIO, PIN_BOTH_EDGE, PIN_PULL_PD, NULL, __lpm_irq_handler);
	if (ret) {
		test_log("eint register failed, ret = %d\n", ret);
		return;
	}
	ql_eint_enable_wakeup( LPM_GPIO, PIN_BOTH_EDGE);
	
	g_lpm_fd = ql_lpm_wakelock_create("lpm_test_lock", sizeof("lpm_test_lock"));
	if (g_lpm_fd <= 0) {
		test_log("ql_lpm_wakelock_create, lpm_fd = %d\n", g_lpm_fd);
		return;
	}
	//ql_lpm_wakelock_lock(g_lpm_fd);
	ql_autosleep_enable(1);

	while(1) {
		j++;
		test_log("quec_lpm_test_task, id:%d, ==================g_cnt=%d \n", j, g_cnt);
		
		ql_rtos_task_sleep_s(5);
	}

}


//application_init(ql_power_test,"ql_power_test2", 10, 0);
//application_init(ql_power_test1,"ql_power_test1", 10, 0);
//application_init(quec_lpm_test,"quec_lpm_test", 10, 0);


