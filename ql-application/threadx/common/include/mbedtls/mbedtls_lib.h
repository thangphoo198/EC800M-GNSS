/*================================================================
  Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/
#ifndef MBEDTLS_LIB_H
#define MBEDTLS_LIB_H

#include "net_sockets.h"
#include "ctr_drbg.h"
#include "debug.h"
#include "entropy.h"
#include "pk.h"
#include "ssl.h"
#include "x509_crt.h"
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>


void mbedtls_net_free( mbedtls_net_context *ctx );
void mbedtls_x509_crt_free( mbedtls_x509_crt *crt );
void mbedtls_pk_free( mbedtls_pk_context *ctx );
void mbedtls_ssl_free( mbedtls_ssl_context *ssl );
void mbedtls_ssl_config_free( mbedtls_ssl_config *conf );	
void mbedtls_ctr_drbg_free( mbedtls_ctr_drbg_context *ctx );
void mbedtls_entropy_free( mbedtls_entropy_context *ctx );
void mbedtls_net_init( mbedtls_net_context *ctx );
void mbedtls_ssl_init( mbedtls_ssl_context *ssl );	
void mbedtls_ssl_config_init( mbedtls_ssl_config *conf );
void mbedtls_ctr_drbg_init( mbedtls_ctr_drbg_context *ctx );
void mbedtls_x509_crt_init( mbedtls_x509_crt *crt );
void mbedtls_pk_init( mbedtls_pk_context *ctx );
void mbedtls_entropy_init( mbedtls_entropy_context *ctx );
void mbedtls_debug_set_threshold( int threshold );
void mbedtls_ssl_conf_dbg( mbedtls_ssl_config *conf,
                  void (*f_dbg)(void *, int, const char *, int, const char *),
                  void  *p_dbg );
int mbedtls_ctr_drbg_seed( mbedtls_ctr_drbg_context *ctx,
                           int (*f_entropy)(void *, unsigned char *, size_t),
                           void *p_entropy,
                           const unsigned char *custom,
                           size_t len );
int mbedtls_x509_crt_parse( mbedtls_x509_crt *chain,
                            const unsigned char *buf,
                            size_t buflen );
int mbedtls_x509_crt_parse_file( mbedtls_x509_crt *chain, const char *path );
int mbedtls_pk_parse_keyfile( mbedtls_pk_context *ctx,
                      const char *path, const char *pwd );
int mbedtls_ssl_conf_psk( mbedtls_ssl_config *conf,
                const unsigned char *psk, size_t psk_len,
                const unsigned char *psk_identity, size_t psk_identity_len );

int mbedtls_net_connect( mbedtls_net_context *ctx,
					 #if defined (MBEDTLS_WITH_ASR)
						 int cid,
					 #endif
						 const char *host,
                         const char *port, int proto );
int mbedtls_net_bind( mbedtls_net_context *ctx,
					#if defined (MBEDTLS_WITH_ASR)
					int cid,
					#endif
					const char *bind_ip,
					const char *port, int proto );
int mbedtls_net_set_block( mbedtls_net_context *ctx );
int mbedtls_ssl_config_defaults( mbedtls_ssl_config *conf,
                                 int endpoint, int transport, int preset );
void mbedtls_ssl_conf_verify( mbedtls_ssl_config *conf,
                     int (*f_vrfy)(void *, mbedtls_x509_crt *, int, uint32_t *),
                     void *p_vrfy );
void mbedtls_ssl_conf_authmode( mbedtls_ssl_config *conf, int authmode );
void mbedtls_ssl_conf_rng( mbedtls_ssl_config *conf,
                  int (*f_rng)(void *, unsigned char *, size_t),
                  void *p_rng );
void mbedtls_ssl_conf_ca_chain( mbedtls_ssl_config *conf,
                               mbedtls_x509_crt *ca_chain,
                               mbedtls_x509_crl *ca_crl );
int mbedtls_ssl_conf_own_cert( mbedtls_ssl_config *conf,
                              mbedtls_x509_crt *own_cert,
                              mbedtls_pk_context *pk_key );
void mbedtls_ssl_conf_read_timeout( mbedtls_ssl_config *conf, uint32_t timeout );
int mbedtls_ssl_setup( mbedtls_ssl_context *ssl,
                       const mbedtls_ssl_config *conf );
void mbedtls_ssl_conf_ciphersuites( mbedtls_ssl_config *conf,
                                   const int *ciphersuites );
int mbedtls_ssl_set_hostname( mbedtls_ssl_context *ssl, const char *hostname );
void mbedtls_ssl_set_bio( mbedtls_ssl_context *ssl,
        void *p_bio,
        mbedtls_ssl_send_t *f_send,
        mbedtls_ssl_recv_t *f_recv,
        mbedtls_ssl_recv_timeout_t *f_recv_timeout );
int mbedtls_ssl_handshake( mbedtls_ssl_context *ssl );
uint32_t mbedtls_ssl_get_verify_result( const mbedtls_ssl_context *ssl );
int mbedtls_ssl_close_notify( mbedtls_ssl_context *ssl );
int mbedtls_ssl_write( mbedtls_ssl_context *ssl, const unsigned char *buf, size_t len );
int mbedtls_ssl_read( mbedtls_ssl_context *ssl, unsigned char *buf, size_t len );
int mbedtls_entropy_func( void *data, unsigned char *output, size_t len );

int mbedtls_ctr_drbg_random( void *p_rng, unsigned char *output,
                             size_t output_len );

int mbedtls_net_recv_timeout( void *ctx, unsigned char *buf,
                              size_t len, uint32_t timeout );
int mbedtls_net_send( void *ctx, const unsigned char *buf, size_t len );
int mbedtls_net_recv( void *ctx, unsigned char *buf, size_t len );

#ifdef QUEC_MEBEDTLS_OPEN

#define _IN_ /* indicate an input parameter */
#define _OU_ /* indicate a output parameter */


/* log print/upload related variables */
/* MAX size of log buffer for one log item including header and content */
#define MAX_LOG_MSG_LEN (511)

#define TIME_FORMAT_STR_LEN (20)


#include <time.h>
#include "utlTime.h"

#ifdef timerclear
#undef timerclear
#endif

#ifdef timerisset
#undef timerisset
#endif

#ifdef timercmp
#undef timercmp
#endif

#ifdef timeradd
#undef timeradd
#endif

#ifdef timersub
#undef timersub
#endif

#define	timerclear(tvp)		((tvp)->tv_sec = (tvp)->tv_usec = 0)
#define	timerisset(tvp)		((tvp)->tv_sec || (tvp)->tv_usec)
#define	timercmp(tvp, uvp, cmp)					\
	(((tvp)->tv_sec == (uvp)->tv_sec) ?				\
	    ((tvp)->tv_usec cmp (uvp)->tv_usec) :			\
	    ((tvp)->tv_sec cmp (uvp)->tv_sec))
#define	timeradd(tvp, uvp, vvp)						\
	do {								\
		(vvp)->tv_sec = (tvp)->tv_sec + (uvp)->tv_sec;		\
		(vvp)->tv_usec = (tvp)->tv_usec + (uvp)->tv_usec;	\
		if ((vvp)->tv_usec >= 1000000) {			\
			(vvp)->tv_sec++;				\
			(vvp)->tv_usec -= 1000000;			\
		}							\
	} while (0)
#define	timersub(tvp, uvp, vvp)						\
	do {								\
		(vvp)->tv_sec = (tvp)->tv_sec - (uvp)->tv_sec;		\
		(vvp)->tv_usec = (tvp)->tv_usec - (uvp)->tv_usec;	\
		if ((vvp)->tv_usec < 0) {				\
			(vvp)->tv_sec--;				\
			(vvp)->tv_usec += 1000000;			\
		}							\
	} while (0)

/**************** QCloud IoT C-SDK constants begin ************************/

/* MAX size of client ID */
#define MAX_SIZE_OF_CLIENT_ID (80)

/* MAX size of product ID */
#define MAX_SIZE_OF_PRODUCT_ID (10)

/* MAX size of product secret */
#define MAX_SIZE_OF_PRODUCT_SECRET (32)

/* MAX size of device name */
#define MAX_SIZE_OF_DEVICE_NAME (48)

/* MAX size of device secret */
#define MAX_SIZE_OF_DEVICE_SECRET (64)

/* MAX size of device cert file name */
#define MAX_SIZE_OF_DEVICE_CERT_FILE_NAME (128)

/* MAX size of device key file name */
#define MAX_SIZE_OF_DEVICE_SECRET_FILE_NAME (128)

/* MAX size of region len */
#define MAX_SIZE_OF_REGION (64)

/* MAX num of subdevice */
#define MAX_NUM_SUB_DEV (1)

typedef enum {
    QCLOUD_RET_MQTT_ALREADY_CONNECTED           = 4,  // Already connected with MQTT server
    QCLOUD_RET_MQTT_CONNACK_CONNECTION_ACCEPTED = 3,  // MQTT connection accepted by server
    QCLOUD_RET_MQTT_MANUALLY_DISCONNECTED       = 2,  // Manually disconnected with MQTT server
    QCLOUD_RET_MQTT_RECONNECTED                 = 1,  // Reconnected with MQTT server successfully

    QCLOUD_RET_SUCCESS = 0,  // Successful return

    QCLOUD_ERR_FAILURE  = -1001,  // Generic failure return
    QCLOUD_ERR_INVAL    = -1002,  // Invalid parameter
    QCLOUD_ERR_DEV_INFO = -1003,  // Fail to get device info
    QCLOUD_ERR_MALLOC   = -1004,  // Fail to malloc memory

    QCLOUD_ERR_HTTP_CLOSED         = -3,   // HTTP server close the connection
    QCLOUD_ERR_HTTP                = -4,   // HTTP unknown error
    QCLOUD_ERR_HTTP_PRTCL          = -5,   // HTTP protocol error
    QCLOUD_ERR_HTTP_UNRESOLVED_DNS = -6,   // HTTP DNS resolve failed
    QCLOUD_ERR_HTTP_PARSE          = -7,   // HTTP URL parse failed
    QCLOUD_ERR_HTTP_CONN           = -8,   // HTTP connect failed
    QCLOUD_ERR_HTTP_AUTH           = -9,   // HTTP auth failed
    QCLOUD_ERR_HTTP_NOT_FOUND      = -10,  // HTTP 404
    QCLOUD_ERR_HTTP_TIMEOUT        = -11,  // HTTP timeout

    QCLOUD_ERR_MQTT_PUSH_TO_LIST_FAILED                   = -102,  // Fail to push node to MQTT waiting list
    QCLOUD_ERR_MQTT_NO_CONN                               = -103,  // Not connected with MQTT server
    QCLOUD_ERR_MQTT_UNKNOWN                               = -104,  // MQTT unknown error
    QCLOUD_ERR_MQTT_ATTEMPTING_RECONNECT                  = -105,  // Reconnecting with MQTT server
    QCLOUD_ERR_MQTT_RECONNECT_TIMEOUT                     = -106,  // MQTT reconnect timeout
    QCLOUD_ERR_MQTT_MAX_SUBSCRIPTIONS                     = -107,  // MQTT topic subscription out of range
    QCLOUD_ERR_MQTT_SUB                                   = -108,  // MQTT topic subscription fail
    QCLOUD_ERR_MQTT_NOTHING_TO_READ                       = -109,  // MQTT nothing to read
    QCLOUD_ERR_MQTT_PACKET_READ                           = -110,  // Something wrong when reading MQTT packet
    QCLOUD_ERR_MQTT_REQUEST_TIMEOUT                       = -111,  // MQTT request timeout
    QCLOUD_ERR_MQTT_CONNACK_UNKNOWN                       = -112,  // MQTT connection refused: unknown error
    QCLOUD_ERR_MQTT_CONNACK_UNACCEPTABLE_PROTOCOL_VERSION = -113,  // MQTT connection refused: protocol version invalid
    QCLOUD_ERR_MQTT_CONNACK_IDENTIFIER_REJECTED           = -114,  // MQTT connection refused: identifier rejected
    QCLOUD_ERR_MQTT_CONNACK_SERVER_UNAVAILABLE            = -115,  // MQTT connection refused: service not available
    QCLOUD_ERR_MQTT_CONNACK_BAD_USERDATA                  = -116,  // MQTT connection refused: bad user name or password
    QCLOUD_ERR_MQTT_CONNACK_NOT_AUTHORIZED                = -117,  // MQTT connection refused: not authorized
    QCLOUD_ERR_RX_MESSAGE_INVAL                           = -118,  // MQTT received invalid msg
    QCLOUD_ERR_BUF_TOO_SHORT                              = -119,  // MQTT recv buffer not enough
    QCLOUD_ERR_MQTT_QOS_NOT_SUPPORT                       = -120,  // MQTT QoS level not supported
    QCLOUD_ERR_MQTT_UNSUB_FAIL                            = -121,  // MQTT unsubscribe failed

    QCLOUD_ERR_JSON_PARSE            = -132,  // JSON parsing error
    QCLOUD_ERR_JSON_BUFFER_TRUNCATED = -133,  // JSON buffer truncated
    QCLOUD_ERR_JSON_BUFFER_TOO_SMALL = -134,  // JSON parsing buffer not enough
    QCLOUD_ERR_JSON                  = -135,  // JSON generation error
    QCLOUD_ERR_MAX_JSON_TOKEN        = -136,  // JSON token out of range

    QCLOUD_ERR_MAX_APPENDING_REQUEST = -137,  // appending request out of range
    QCLOUD_ERR_MAX_TOPIC_LENGTH      = -138,  // Topic length oversize

    QCLOUD_ERR_COAP_NULL              = -150,  // COAP null pointer
    QCLOUD_ERR_COAP_DATA_SIZE         = -151,  // COAP data size out of range
    QCLOUD_ERR_COAP_INTERNAL          = -152,  // COAP interval error
    QCLOUD_ERR_COAP_BADMSG            = -153,  // COAP bad msg
    QCLOUD_ERR_DTLS_PEER_CLOSE_NOTIFY = -160,  // DTLS connection is closed

    QCLOUD_ERR_PROPERTY_EXIST     = -201,  // property already exist
    QCLOUD_ERR_NOT_PROPERTY_EXIST = -202,  // property not exist
    QCLOUD_ERR_REPORT_TIMEOUT     = -203,  // update timeout
    QCLOUD_ERR_REPORT_REJECTED    = -204,  // update rejected by server
    QCLOUD_ERR_GET_TIMEOUT        = -205,  // get timeout
    QCLOUD_ERR_GET_REJECTED       = -206,  // get rejected by server

    QCLOUD_ERR_ACTION_EXIST     = -210,  // acion already exist
    QCLOUD_ERR_NOT_ACTION_EXIST = -211,  // acion not exist

    QCLOUD_ERR_GATEWAY_CREATE_SESSION_FAIL = -221,  // Gateway fail to create sub-device session
    QCLOUD_ERR_GATEWAY_SESSION_NO_EXIST    = -222,  // Gateway sub-device session not exist
    QCLOUD_ERR_GATEWAY_SESSION_TIMEOUT     = -223,  // Gateway sub-device session timeout
    QCLOUD_ERR_GATEWAY_SUBDEV_ONLINE       = -224,  // Gateway sub-device online
    QCLOUD_ERR_GATEWAY_SUBDEV_OFFLINE      = -225,  // Gateway sub-device offline

    QCLOUD_ERR_TCP_SOCKET_FAILED   = -601,  // TLS TCP socket connect fail
    QCLOUD_ERR_TCP_UNKNOWN_HOST    = -602,  // TCP unknown host (DNS fail)
    QCLOUD_ERR_TCP_CONNECT         = -603,  // TCP/UDP socket connect fail
    QCLOUD_ERR_TCP_READ_TIMEOUT    = -604,  // TCP read timeout
    QCLOUD_ERR_TCP_WRITE_TIMEOUT   = -605,  // TCP write timeout
    QCLOUD_ERR_TCP_READ_FAIL       = -606,  // TCP read error
    QCLOUD_ERR_TCP_WRITE_FAIL      = -607,  // TCP write error
    QCLOUD_ERR_TCP_PEER_SHUTDOWN   = -608,  // TCP server close connection
    QCLOUD_ERR_TCP_NOTHING_TO_READ = -609,  // TCP socket nothing to read

    QCLOUD_ERR_SSL_INIT            = -701,  // TLS/SSL init fail
    QCLOUD_ERR_SSL_CERT            = -702,  // TLS/SSL certificate issue
    QCLOUD_ERR_SSL_CONNECT         = -703,  // TLS/SSL connect fail
    QCLOUD_ERR_SSL_CONNECT_TIMEOUT = -704,  // TLS/SSL connect timeout
    QCLOUD_ERR_SSL_WRITE_TIMEOUT   = -705,  // TLS/SSL write timeout
    QCLOUD_ERR_SSL_WRITE           = -706,  // TLS/SSL write error
    QCLOUD_ERR_SSL_READ_TIMEOUT    = -707,  // TLS/SSL read timeout
    QCLOUD_ERR_SSL_READ            = -708,  // TLS/SSL read error
    QCLOUD_ERR_SSL_NOTHING_TO_READ = -709,  // TLS/SSL nothing to read

    QCLOUD_ERR_BIND_PARA_ERR        = -801,  // bind sub device param error
    QCLOUD_ERR_BIND_SUBDEV_ERR      = -802,  // sub device not exist or illegal
    QCLOUD_ERR_BIND_SIGN_ERR        = -803,  // signature check err
    QCLOUD_ERR_BIND_SIGN_METHOD_RRR = -804,  // signmethod not supporte
    QCLOUD_ERR_BIND_SIGN_EXPIRED    = -805,  // signature expired
    QCLOUD_ERR_BIND_BEEN_BINDED     = -806,  // sub device has been binded by other gateway
    QCLOUD_ERR_BIND_SUBDEV_FORBID   = -807,  // sub device not allow to bind
    QCLOUD_ERR_BIND_OP_FORBID       = -808,  // operation not permit
    QCLOUD_ERR_BIND_REPEATED_REQ    = -809,  // repeated bind request,has been binded
} IoT_Return_Code;

typedef struct {
	unsigned char profile_idx;
    const char *ca_crt;
    uint16_t    ca_crt_len;

#ifdef AUTH_MODE_CERT
    // Device with certificate
    const char *cert_file;  // public certificate file
    const char *key_file;   // pravite certificate file
#else

    // Device with PSK
    const char *psk;     // PSK string
    char psk_id[MAX_SIZE_OF_CLIENT_ID + 1];  // PSK ID
#endif

    size_t psk_length;  // PSK length

    unsigned int timeout_ms;  // SSL handshake timeout in millisecond

}SSLConnectParams;

typedef SSLConnectParams TLSConnectParams;


typedef bool (*LogMessageHandler)(const char *message);

typedef enum { eLOG_DISABLE = 0, eLOG_ERROR = 1, eLOG_WARN = 2, eLOG_INFO = 3, eLOG_DEBUG = 4 } LOG_LEVEL;


struct Timer {
	struct timeval end_time;
};
typedef struct Timer Timer;


/**
 * @brief Check if a timer is expired
 *
 * Call this function passing in a timer to check if that timer has expired.
 *
 * @param timer - pointer to the timer to be checked for expiration
 * @return bool - true = timer expired, false = timer not expired
 */
bool expired(Timer *timer);

/**
 * @brief Create a timer (milliseconds)
 *
 * Sets the timer to expire in a specified number of milliseconds.
 *
 * @param timer - pointer to the timer to be set to expire in milliseconds
 * @param timeout_ms - set the timer to expire in this number of milliseconds
 */
void countdown_ms(Timer *timer, unsigned int timeout_ms);

/**
 * @brief Create a timer (seconds)
 *
 * Sets the timer to expire in a specified number of seconds.
 *
 * @param timer - pointer to the timer to be set to expire in seconds
 * @param timeout - set the timer to expire in this number of seconds
 */
void countdown(Timer *timer, unsigned int timeout);

/**
 * @brief Check the time remaining on a give timer
 *
 * Checks the input timer and returns the number of milliseconds remaining on
 * the timer.
 *
 * @param timer - pointer to the timer to be set to checked
 * @return int - milliseconds left on the countdown timer
 */

int left_ms(Timer *timer);

/**
 * @brief Initialize a timer
 *
 * Performs any initialization required to the timer passed in.
 *
 * @param timer - pointer to the timer to be initialized
 */
void InitTimer(Timer *timer);

/**
 * @brief Malloc memory
 *
 * @param size   Expected memory size (unit: byte)
 * @return       pointer to the memory
 */
void *HAL_Malloc(_IN_ uint32_t size);

/**
 * @brief Free memory
 *
 * @param ptr   pointer to the pre-malloc memory
 */
void HAL_Free(_IN_ void *ptr);

void IOT_Log_Gen(const char *file, const char *func, const int line, const int level, const char *fmt, ...);

/* Simple APIs for log generation in different level */
#define Log_d(fmt, ...) IOT_Log_Gen(__FILE__, __FUNCTION__, __LINE__, eLOG_DEBUG, fmt, ##__VA_ARGS__)
#define Log_i(fmt, ...) IOT_Log_Gen(__FILE__, __FUNCTION__, __LINE__, eLOG_INFO, fmt, ##__VA_ARGS__)
#define Log_w(fmt, ...) IOT_Log_Gen(__FILE__, __FUNCTION__, __LINE__, eLOG_WARN, fmt, ##__VA_ARGS__)
#define Log_e(fmt, ...) IOT_Log_Gen(__FILE__, __FUNCTION__, __LINE__, eLOG_ERROR, fmt, ##__VA_ARGS__)

#endif

#endif

