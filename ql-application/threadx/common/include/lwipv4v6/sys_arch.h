#ifndef __LWIP_SYSARCH_H__
#define __LWIP_SYSARCH_H__

#include "opt.h"
#include "err.h"
#include "cc.h"
//#include "UART.h"
#include "debug.h"
//#include "osa.h"
//#include "osa_old_api.h"
#include "mem.h"
#include <stdlib.h>

typedef UINT32 sys_prot_t;
typedef void * sys_mutex_t;
typedef void * sys_sem_t;
typedef void * sys_mbox_t;
typedef void * sys_thread_t;
typedef void (*printCallback)   (char *printstr);
typedef void (*lwip_thread_fn)  (void *pArgs);
typedef err_t (*lwip_run_entry)  (void *pArgs);

/*The interface is adapter to AT cmder*/
struct lwip_thread_msgq_msg_st {
	u32_t msgID;
	void *pArgs;
    printCallback print;
    lwip_run_entry run_entry;
};

extern u8_t lwip_init_flag;
extern u8_t lwip_urt_debug;
extern u8_t lwip_rtiline_debug;
extern u8_t lwip_mifi_flag;
extern u8_t lwip_hop_limit;
extern u32_t lwip_rng_num;
extern u32_t g_server_ip;

extern msg_t msg_null;
extern UINT8 booting_done;
extern UINT32 uart_initialized;

/** Return code for timeouts from sys_arch_mbox_fetch and sys_arch_sem_wait */
#define SYS_ARCH_TIMEOUT 0xffffffffUL

/** sys_mbox_tryfetch() returns SYS_MBOX_EMPTY if appropriate.
 * For now we use the same magic value, but we allow this to change in future.
 */
#define SYS_MBOX_EMPTY  SYS_ARCH_TIMEOUT
#define SYS_MBOX_NULL   NULL
#define SYS_SEM_NULL    NULL

/*Note:should keep the same value as uart.h define*/
#define UART_INIT_DONE_TEMP_HERE    0xDEAFBEED

/*define DNS set pos*/
#define NETIF_SET_DNS_SERVER           (1)   /*set dns relay server using netif config*/
#define WEB_SET_DNS_SERVER             (2)   /*set dns relay server by webui config*/
#define API_SET_DNS_SERVER             (3)   /*set dns relay server by lwip_api function*/
#define RESET_DEFAULT_DNS_SERVER       (0xFF) /*reset dns relay server by default netif*/

#define LWIP_PLATFORM_DONGLE_MODE      (0)
#define LWIP_PLATFORM_MIFI_MODE        (1)
#define LWIP_PLATFORM_BRIDGE_MODE      (2)
#define LWIP_PLATFORM_DEFINE_END       (3)

#define LWIP_ENABLE                    (1)
#define LWIP_DISABLE                   (0)
#define LWIP_TASK_PENDING              (0)
#define LWIP_TASK_RUNING               (1)
#define LWIP_TASK_EXITING              (2)
#define NEWLINE "\r\n"

#define U32_DIFF(a, b) (((a) >= (b)) ? ((a) - (b)) : (((a) + ((b) ^ 0xFFFFFFFF) + 1)))
#define MAKE_HASH_KEY(ipaddr, flg, port) ((ipaddr)&0xFF000000|(flg)|(port))
#define MAKE_HASH_KEY_2(ipaddr, port)    ((ipaddr)&0xFFFF0000|(port))
#define LWIP_FLAGS_HOTBIT_CHECK(flags, hotbit)    (((flags) & (hotbit)) ? 1 : 0)
#define LWIP_FLAGS_HOTBIT_CLEAR(flags, hotbit)    ((flags) &= ~(hotbit))
#define LWIP_FLAGS_HOTBIT_SET(flags, hotbit)      ((flags) |= (hotbit))


#define IS_LWIP_DONGLE_MODE         (LWIP_PLATFORM_DONGLE_MODE == lwip_mifi_flag)
#define IS_LWIP_MIFI_MODE           (LWIP_PLATFORM_MIFI_MODE == lwip_mifi_flag)
#define IS_LWIP_BRIDGE_MODE         (LWIP_PLATFORM_BRIDGE_MODE == lwip_mifi_flag)
#define IS_NOT_LWIP_MIFI_MODE       (LWIP_PLATFORM_MIFI_MODE != lwip_mifi_flag) /*maybe dongle or bridge, bridge mode based on dongle*/

/* 169.254.x.x */
#define IP_169_254_HEADER           (0xFEA9)
#define IS_IP_169_254(addr)         (((addr)&0xFFFF) == IP_169_254_HEADER)
#define IP_169_254_ADDR             (0x0100FEA9)

/* 127.0.0.1 */
#define IP_LOOPBACK_ADDRESS         (0x100007F)

/* 192.168.x.x */
#define IP_192_168_HEADER           (0xA8C0)
#define IS_IP_192_168(addr)         (((addr)&0xFFFF) == IP_192_168_HEADER)
#define IP_192_168_ADDR             (0x0100A8C0)

#define IP4_IS_BROADCAST(ip, pc)    ((((ip)&0xFFFFFF) == ((pc)&0xFFFFFF))&& (((ip)>>24) == 0xFF))
/* ip is packet ip address, pc is pc ip address*/
#define IP4_ROUTER_PC(ip, pc)       (IP4_IS_BROADCAST(ip, pc) || ((ip) == (pc)))
/* addr is in network order */
#define IS_LOCAL_IP_ADDR(addr)      (((addr)&0xFFFFFF) == (htonl(g_server_ip) & 0xFFFFFF))
#define IS_ROUTER_IP_ADDR(addr)     ((addr) == htonl(g_server_ip))

/* 1 tick is 5 ms */
#define SYS_ONE_TICK            (5)
#define SYS_ONE_SECOND          (1000/SYS_ONE_TICK)

#define LWIP_RAND       lwip_sys_rand

u32_t disableInterrupts(void);
void restoreInterrupts(u32_t cpsr);
void RTI_LOG(const char* fmt, ...);
void LWIP_LOG(const char *fmt, ...);
void lwipCheckHeapMem( void *pMem );
#if 0
OSA_STATUS OsaSemaphoreCheck( OsaRefT OsaRef);
OsaRefT OsaCurrentThreadRef(void);
u32_t OSATaskGetSysParam1(OSATaskRef OsaRef);
void OSATaskSetSysParam1(OSATaskRef OsaRef, u32_t value);
#endif
#if LWIP_RECORED_LINE_FLAG
void lwip_record_line(const char *string, unsigned int line);
#endif
void lwip_assert_now_callback(void * ctx);
void lwip_record_assert(const char *string, unsigned int line);

#if LWIP_DEBUG
/*LWIP_DIAG, using diagprintf*/
/*debug, define on debug.h, macro*/
/*cat3, using lwip_filename_linenumber format to define.*/
#define LWIP_DIAG(debug, cat3, fmt, args...)            \
{                                                           \
    if (LWIP_DEBUGF_SWITCH_CHECK(debug))                    \
    {                                                       \
        DIAG_FILTER(MIFI, LWIP, cat3, DIAG_INFORMATION)     \
        diagPrintf(fmt, ##args);                            \
    }                                                       \
}
#else
#define LWIP_DIAG(debug, cat3, fmt, args...)
#endif

/*LWIP_DIAG_S, using diagprintf, but no DEBUG check*/
/*DEBUG check will only do once at begining */
/*debug, define on debug.h, macro*/
/*cat3, using lwip_filename_linenumber format to define.*/
#define LWIP_DIAG_S(cat3, fmt, args...)            \
{                                                  \
    DIAG_FILTER(MIFI, LWIP, cat3, DIAG_INFORMATION)     \
    diagPrintf(fmt, ##args);                            \
}

#define RETURN(x, cat3) \
do { \
    LWIP_DIAG(DIAG_ON_DEBUG, cat3, "ERR_RTE in %s, line %d", __FUNCTION__, __LINE__); \
    return (x); \
} while(0)

static inline u8_t lwip_assert_fn(u8_t assertion, const char *function, unsigned int line)
{
	if (1 == assertion) {
		return 0;
	} else {
		lwip_record_assert(function, line);
		return 1;
	}
	
}
#define LWIP_ASSERT(assertion)  lwip_assert_fn((assertion), __FUNCTION__, __LINE__)

/*******************************************************************/
/********************Global inline function define *****************/
/*******************************************************************/
u32_t lwip_sys_rand(void);
void sys_init(void);
void sys_msleep(u32_t ms);
void sys_thread_delete(sys_thread_t thread);
int sys_thread_check(sys_thread_t thread);
sys_thread_t sys_thread_new(const char *name, lwip_thread_fn thread, 
                                    void *arg, int stacksize, int prio);

#if 0
u32_t sys_disableInterrupts_fn(const char* fun, const int line);
void sys_restoreInterrupts_fn(u32_t cpsr, const char* fun, const int line);
#define sys_disableInterrupts()      sys_disableInterrupts_fn(__FUNCTION__, __LINE__)
#define sys_restoreInterrupts(cpsr)  sys_restoreInterrupts_fn((cpsr), __FUNCTION__, __LINE__)

#if LWIP_SYS_PROTECT_USING_MUTEX
void sys_arch_protect(sys_prot_t* pval);
void sys_arch_unprotect(sys_prot_t val);
#else
void sys_arch_protect_fn(sys_prot_t* pval, const char* fun, const int line);
void sys_arch_unprotect_fn(sys_prot_t val, const char* fun, const int line);
#define sys_arch_protect(pval)      sys_arch_protect_fn((pval), __FUNCTION__, __LINE__)
#define sys_arch_unprotect(val)     sys_arch_unprotect_fn((val), __FUNCTION__, __LINE__)
#endif
#endif

static inline u32_t sys_disableInterrupts_fn(const char* fun, const int line)
{
    //if (lwip_selfline_debug) {lwip_record_line(fun, line);}
    return disableInterrupts();
}
static inline void sys_restoreInterrupts_fn(u32_t cpsr, const char* fun, const int line)
{
    //if (lwip_selfline_debug) {lwip_record_line(fun, line);}
    restoreInterrupts(cpsr);
}
#define sys_disableInterrupts()      sys_disableInterrupts_fn(__FUNCTION__, __LINE__)
#define sys_restoreInterrupts(cpsr)  sys_restoreInterrupts_fn((cpsr), __FUNCTION__, __LINE__)

static inline void sys_arch_protect_fn(sys_prot_t* pval, const char* fun, const int line)
{
    //if (lwip_selfline_debug) {lwip_record_line(fun, line);}
    *pval = disableInterrupts();
}
static inline void sys_arch_unprotect_fn(sys_prot_t val, const char* fun, const int line)
{
    //if (lwip_selfline_debug) {lwip_record_line(fun, line);}
    restoreInterrupts(val);
}
#define sys_arch_protect(pval)      sys_arch_protect_fn((pval), __FUNCTION__, __LINE__)
#define sys_arch_unprotect(val)     sys_arch_unprotect_fn((val), __FUNCTION__, __LINE__)
#if 0
static inline int sys_sem_valid(sys_sem_t *sem)
{
    if (OS_SUCCESS == OSASemaphoreCheck (*sem)) {
#if IS_LWIP_PLATFORM_1802_1802S
        lwipCheckHeapMem(*sem);
#endif
        return 1;
    } else {
        return 0;
    }
}

static inline err_t sys_sem_new(sys_sem_t *sem, u8_t count)
{
    OSA_STATUS status;

    status = OSASemaphoreCreate(sem, count, OS_FIFO);
    ASSERT(OS_SUCCESS == status);
    return ERR_OK;
}

static inline void sys_sem_free(sys_sem_t *sem)
{
    if (sys_sem_valid(sem)) {
        OSASemaphoreDelete(*sem);   
        *sem = SYS_SEM_NULL;
    } else {
        /*for inline function, must use LWIP_DEBUGF*/    
		LWIP_DEBUGF(DIAG_ON_DEBUG, ("lwiperr: sys_sem_free, sys_sem_valid failed, sem=%lx", sem));
	}
}

static inline void sys_sem_set_invalid(sys_sem_t *sem)
{
    *sem = SYS_SEM_NULL;
}

static inline void sys_sem_signal(sys_sem_t *sem)
{
    if (OS_SUCCESS == OSASemaphoreCheck (*sem)) {
        OSASemaphoreRelease(*sem);
    } else {
        /*for inline function, must use LWIP_DEBUGF*/
		LWIP_DEBUGF(DIAG_ON_DEBUG, ("lwiperr: sys_sem_signal, OSASemaphoreCheck failed, sem=%lx", sem));
	}
}

static inline u32_t sys_arch_sem_wait(sys_sem_t *sem, u32_t timeout)
{
    OSA_STATUS  status;
    int count;

    if (OS_SUCCESS != OSASemaphoreCheck (*sem))
	{
        /*for inline function, must use LWIP_DEBUGF*/        
        LWIP_DEBUGF(DIAG_ON_DEBUG, ("fatal warning! fun: %s, line: %d, semsig: %lx", __FUNCTION__, __LINE__, *sem));
        return SYS_ARCH_TIMEOUT;
    }

    if (timeout == 0) {
        status = OSASemaphoreAcquire(*sem, OSA_SUSPEND);
    } else {
        count =  (timeout+(SYS_ONE_TICK-1))/SYS_ONE_TICK;
        status = OSASemaphoreAcquire(*sem, count);
    }

    if (OS_SUCCESS == status) {
        return ERR_OK;
    }
    return SYS_ARCH_TIMEOUT;
}

static inline err_t sys_mbox_new(sys_mbox_t *mbox, int size)
{
    OSA_STATUS status;

    status = OSAMsgQCreate( mbox,
#ifdef OSA_QUEUE_NAMES
                            "lwipMbox",
#endif
                            MBOX_MAX_SIZE,
                            size,
                            OS_FIFO);
    ASSERT(OS_SUCCESS == status);
    return ERR_OK;
}

static inline void sys_mbox_poll(sys_mbox_t *mbox,  u32_t *count)
{
    OSAMsgQPoll( *mbox, count);
}

static inline void sys_mbox_post(sys_mbox_t *mbox,  msg_t msg)
{
    msg_t*      msg_ptr;
    msg_ptr = (msg != NULL) ? (&msg) : (&msg_null);

    OSAMsgQSend( *mbox,
                 sizeof(void*),
                 (UINT8*)msg_ptr,
                 OSA_SUSPEND);
}

static inline err_t sys_mbox_trypost(sys_mbox_t *mbox, msg_t msg)
{
    OSA_STATUS  status;
    msg_t*      msg_ptr;
    u32_t       nums = 0;

    msg_ptr = (msg != NULL) ? (&msg) : (&msg_null);
    while (nums++ < 5)
    {
        status = OSAMsgQSend( *mbox,
                              sizeof(void*),
                              (UINT8*)msg_ptr,
                              OSA_NO_SUSPEND);

        if (OS_SUCCESS == status)
        {
            return ERR_OK;
        }
    }
    return ERR_MEM;
}

static inline u32_t sys_arch_mbox_fetch(sys_mbox_t *mbox, msg_t* msg, u32_t timeout)
{
    OSA_STATUS  status;
    int count;

    if (timeout == 0) {
        status = OSAMsgQRecv( *mbox, (UINT8*)msg, sizeof(void*), OSA_SUSPEND);
    } else {
        count =  (timeout+(SYS_ONE_TICK-1))/SYS_ONE_TICK;
        status = OSAMsgQRecv( *mbox, (UINT8*)msg, sizeof(void*), count);
    }

    if (OS_SUCCESS == status) {
        return ERR_OK;
    }

    return SYS_ARCH_TIMEOUT;
}

static inline u32_t sys_arch_mbox_tryfetch(sys_mbox_t *mbox, msg_t* msg)
{
    return sys_arch_mbox_fetch(mbox, msg, 5*SYS_ONE_TICK);
}

static inline u32_t sys_arch_mbox_tryfetch_nosuspend(sys_mbox_t *mbox, msg_t* msg)
{
    OSA_STATUS  status;

    status = OSAMsgQRecv( *mbox, (UINT8*)msg, sizeof(void*), OSA_NO_SUSPEND);

    if (OS_SUCCESS == status) {
        return ERR_OK;
    }
    return SYS_ARCH_TIMEOUT;
}

static inline void sys_mbox_free(sys_mbox_t *mbox)
{
    if (*mbox) {
        OSAMsgQDelete(*mbox);
        *mbox = SYS_MBOX_NULL;
    }
}

static inline int sys_mbox_valid(sys_mbox_t *mbox)
{
    return SYS_MBOX_NULL != *mbox;
}

static inline void sys_mbox_set_invalid(sys_mbox_t *mbox)
{
    *mbox = SYS_MBOX_NULL;
}


static inline u32_t sys_jiffies(void)
{
    return (OSAGetTicks() * SYS_ONE_TICK);
}

static inline u32_t sys_now(void)
{
    return (OSAGetTicks() * SYS_ONE_TICK);
}

static inline u32_t sys_now_tick(void)
{
    return OSAGetTicks();
}

static inline u32_t sys_gen_rand()
{
    u32_t rng = LWIP_RAND() + lwip_rng_num;
    return rng;
}
#endif
#ifdef QUEC_PATCH_066_029 //(!LWIP_SYS_PROTECT_USING_MUTEX)
static inline sys_prot_t sys_arch_protect(sys_prot_t* pval)
{
    return diag_lock(pval);
}

static inline void sys_arch_unprotect(sys_prot_t val)
{
    diag_unlock(val);
}
#endif

#endif /* __LWIP_SYSARCH_H__ */
