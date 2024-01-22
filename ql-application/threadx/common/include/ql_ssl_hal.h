/*================================================================
  Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/

#ifndef _QL_SSL_HAL_H
#define _QL_SSL_HAL_H

/*
 * SSL version enumeration
*/
typedef enum
{
	SSL_VSN_SSLV30,
	SSL_VSN_TLSV10,
	SSL_VSN_TLSV11,
	SSL_VSN_TLSV12,
	SSL_VSN_ALL
} SSLVersion;

/*
 * SSL verification enumeration
*/

typedef enum
{
	SSL_VERIFY_MODE_NONE = 0,		// don't verify peer's identification
	SSL_VERIFY_MODE_OPTIONAL = 1,	// verify peer's identification, but continue handshaking when verifies fail
	SSL_VERIFY_MODE_REQUIRED = 2,	// verify peer's identification, but stop handshaking when verifies fail
	SSL_VERIFY_MODE_UNSET = 3 		// Used only for sni_authmode
} SSLVerifyMode;

/*
 * SSL certificate structure
*/

typedef char* SSLCertPathPtr;

typedef struct
{
	SSLCertPathPtr rootCA;
	SSLCertPathPtr clientKey;
	SSLCertPathPtr clientCert;
}SSLCertPath;

typedef enum
{
	SSL_CERT_ROOTCA,
	SSL_CERT_CLIENTKEY,
	SSL_CERT_CLIENTCERT
}SSLCertType;

typedef enum
{
	SSL_CERT_FROM_BUF,	// certificates come from buffer
	SSL_CERT_FROM_FS	// certificates come from file system
}SSLCertFrom;

typedef struct
{
	unsigned char *data;
	int len;
} clientKeyPassword;

typedef struct
{
	SSLCertFrom from;	// specify where certificates come from
	SSLCertPath path;	// specify certificates path
	clientKeyPassword clientKeyPwd;	// client key password
}SSLCert;

/*
 * SSL configuration structure
*/

typedef struct
{
	unsigned char* data;
	int len;
} SSLCTRDRBGSeed;

typedef char* SSLCipherListPtr;

#define SSL_IGNORE_BADCERT_EXPIRED             0x01  /**< The certificate validity has expired. */
#define SSL_IGNORE_BADCERT_REVOKED             0x02  /**< The certificate has been revoked (is on a CRL). */
#define SSL_IGNORE_BADCERT_CN_MISMATCH         0x04  /**< The certificate Common Name (CN) does not match with the expected CN. */
#define SSL_IGNORE_BADCERT_NOT_TRUSTED         0x08  /**< The certificate is not correctly signed by the trusted CA. */
#define SSL_IGNORE_BADCRL_NOT_TRUSTED          0x10  /**< The CRL is not correctly signed by the trusted CA. */
#define SSL_IGNORE_BADCRL_EXPIRED              0x20  /**< The CRL is expired. */
#define SSL_IGNORE_BADCERT_MISSING             0x40  /**< Certificate was missing. */
#define SSL_IGNORE_BADCERT_SKIP_VERIFY         0x80  /**< Certificate verification was skipped. */
#define SSL_IGNORE_BADCERT_OTHER             0x0100  /**< Other reason (can be used by verify callback) */
#define SSL_IGNORE_BADCERT_FUTURE            0x0200  /**< The certificate validity starts in the future. */
#define SSL_IGNORE_BADCRL_FUTURE             0x0400  /**< The CRL is from the future */
#define SSL_IGNORE_BADCERT_KEY_USAGE         0x0800  /**< Usage does not match the keyUsage extension. */
#define SSL_IGNORE_BADCERT_EXT_KEY_USAGE     0x1000  /**< Usage does not match the extendedKeyUsage extension. */
#define SSL_IGNORE_BADCERT_NS_CERT_TYPE      0x2000  /**< Usage does not match the nsCertType extension. */
#define SSL_IGNORE_BADCERT_BAD_MD            0x4000  /**< The certificate is signed with an unacceptable hash. */
#define SSL_IGNORE_BADCERT_BAD_PK            0x8000  /**< The certificate is signed with an unacceptable PK alg (eg RSA vs ECDSA). */
#define SSL_IGNORE_BADCERT_BAD_KEY         0x010000  /**< The certificate is signed with an unacceptable key (eg bad curve, RSA too short). */
#define SSL_IGNORE_BADCRL_BAD_MD           0x020000  /**< The CRL is signed with an unacceptable hash. */
#define SSL_IGNORE_BADCRL_BAD_PK           0x040000  /**< The CRL is signed with an unacceptable PK alg (eg RSA vs ECDSA). */
#define SSL_IGNORE_BADCRL_BAD_KEY          0x080000  /**< The CRL is signed with an unacceptable key (eg bad curve, RSA too short). */

typedef struct
{
	unsigned char en;				// whether to enable ssl, 0:disable, 1:enable
	unsigned char profileIdx;		// profile idx, range:0-15
	char *serverName;				// server name
	unsigned short serverPort;		// server port
	unsigned char protocol;			// 0:SSL/TLS, 1:DTLS
	unsigned char dbgLevel;			// 0:no debug, 1:error, 2:state change, 3:informational, 4:verbose
	unsigned char sessionReuseEn;	// whether to reuse previous ssl session on next connection, 0:disable, 1:enable
	SSLVersion vsn;					// ssl version
	SSLVerifyMode verify;			// verify mode
	unsigned int ignoreVerifyFlags; // flags set on ignoring server certificate verification failure
	SSLCert cert;					// certificate info
	SSLCipherListPtr cipherList;	// cipher list pointer
	SSLCTRDRBGSeed CTRDRBGSeed;		// CTR-DRBG seed
} SSLConfig;

/*
 * SSL context structure
*/

typedef struct
{
	SSLConfig config;
	void *SSL;
} SSLCtx;

void SSLSetConfig(SSLCtx * sslCtx, SSLConfig* config);

int SSLCtxInit(SSLCtx * sslCtx);

void SSLCtxDeinit(SSLCtx * sslCtx);

int SSLHandshake(SSLCtx * sslCtx, int timeout_ms);

int SSLWrite(SSLCtx * sslCtx, const void* data, int sz, int timeout_ms);

int SSLRead(SSLCtx * sslCtx, void* data, int sz, int timeout_ms);

int SSLShutdown(SSLCtx * sslCtx, int timeout_ms);

int SSLGetFd(SSLCtx * sslCtx);

#endif

