/*================================================================
  Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ql_type.h"
#include "ql_rtos.h"
#include "ql_application.h"
#include "ql_data_call.h"
#include "sockets.h"
#include "netdb.h"
#include "ql_ssl_hal.h"

#define ssl_exam_log(fmt, ...) printf("[SSL_EXAM] [%s, %d] "fmt"\r\n", __FUNCTION__, __LINE__, ##__VA_ARGS__)

#define SSL_SERVER_DOMAIN "www.baidu.com"
#define SSL_SERVER_PORT 443
#define CONNECT_TIMEOUT_S 10
#define SEND_TIMEOUT_S 10
#define RECV_TIMEOUT_S 3
#define CLOSE_LINGER_TIME_S 10
#define SSL_CLIENT_SEND_STR \
"\
GET / HTTP/1.1\r\n\
Host: www.baidu.com:443\r\n\
Content-Length: 0\r\n\
\r\n\
"
#define PROFILE_IDX 1

const static SSLCertPathPtr rootCA_path = 
"\
-----BEGIN CERTIFICATE-----\n\
MIIJrzCCCJegAwIBAgIMLO4ZPBiCeOo+Q3VzMA0GCSqGSIb3DQEBCwUAMGYxCzAJ\n\
BgNVBAYTAkJFMRkwFwYDVQQKExBHbG9iYWxTaWduIG52LXNhMTwwOgYDVQQDEzNH\n\
bG9iYWxTaWduIE9yZ2FuaXphdGlvbiBWYWxpZGF0aW9uIENBIC0gU0hBMjU2IC0g\n\
RzIwHhcNMTkwNTA5MDEyMjAyWhcNMjAwNjI1MDUzMTAyWjCBpzELMAkGA1UEBhMC\n\
Q04xEDAOBgNVBAgTB2JlaWppbmcxEDAOBgNVBAcTB2JlaWppbmcxJTAjBgNVBAsT\n\
HHNlcnZpY2Ugb3BlcmF0aW9uIGRlcGFydG1lbnQxOTA3BgNVBAoTMEJlaWppbmcg\n\
QmFpZHUgTmV0Y29tIFNjaWVuY2UgVGVjaG5vbG9neSBDby4sIEx0ZDESMBAGA1UE\n\
AxMJYmFpZHUuY29tMIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAtMa/\n\
2lMgD+pA87hSF2Y7NgGNErSZDdObbBhTsRkIsPpzRz4NOnlieGEuVDxJfFbawL5h\n\
VdVCcGoQvvW9jWSWIQCTYwmHtxm6DiA+SchT7QKPRgHroQeTc7vt8bPJ4vvd8Dkq\n\
g630QZi8huq6dKim49DlxY6zC7LSrJF0Dv+AECM2YmUItIf1VwwlxwDY9ahduDNB\n\
pypf2/pwniG7rkIWZgdp/hwmKoEPq3Pj1lIgpG2obNRmSKRv8mgKxWWhTr8EekBD\n\
HNN1+3WsGdZKNQVuz9Vl0UTKawxYBMSFTx++LDLR8cYo+/kmNrVt+suWoqDQvPhR\n\
3wdEvY9vZ8DUr9nNwwIDAQABo4IGGTCCBhUwDgYDVR0PAQH/BAQDAgWgMIGgBggr\n\
BgEFBQcBAQSBkzCBkDBNBggrBgEFBQcwAoZBaHR0cDovL3NlY3VyZS5nbG9iYWxz\n\
aWduLmNvbS9jYWNlcnQvZ3Nvcmdhbml6YXRpb252YWxzaGEyZzJyMS5jcnQwPwYI\n\
KwYBBQUHMAGGM2h0dHA6Ly9vY3NwMi5nbG9iYWxzaWduLmNvbS9nc29yZ2FuaXph\n\
dGlvbnZhbHNoYTJnMjBWBgNVHSAETzBNMEEGCSsGAQQBoDIBFDA0MDIGCCsGAQUF\n\
BwIBFiZodHRwczovL3d3dy5nbG9iYWxzaWduLmNvbS9yZXBvc2l0b3J5LzAIBgZn\n\
gQwBAgIwCQYDVR0TBAIwADBJBgNVHR8EQjBAMD6gPKA6hjhodHRwOi8vY3JsLmds\n\
b2JhbHNpZ24uY29tL2dzL2dzb3JnYW5pemF0aW9udmFsc2hhMmcyLmNybDCCA0kG\n\
A1UdEQSCA0AwggM8ggliYWlkdS5jb22CEmNsaWNrLmhtLmJhaWR1LmNvbYIQY20u\n\
cG9zLmJhaWR1LmNvbYIQbG9nLmhtLmJhaWR1LmNvbYIUdXBkYXRlLnBhbi5iYWlk\n\
dS5jb22CEHduLnBvcy5iYWlkdS5jb22CCCouOTEuY29tggsqLmFpcGFnZS5jboIM\n\
Ki5haXBhZ2UuY29tgg0qLmFwb2xsby5hdXRvggsqLmJhaWR1LmNvbYIOKi5iYWlk\n\
dWJjZS5jb22CEiouYmFpZHVjb250ZW50LmNvbYIOKi5iYWlkdXBjcy5jb22CESou\n\
YmFpZHVzdGF0aWMuY29tggwqLmJhaWZhZS5jb22CDiouYmFpZnViYW8uY29tgg8q\n\
LmJjZS5iYWlkdS5jb22CDSouYmNlaG9zdC5jb22CCyouYmRpbWcuY29tgg4qLmJk\n\
c3RhdGljLmNvbYINKi5iZHRqcmN2LmNvbYIRKi5iai5iYWlkdWJjZS5jb22CDSou\n\
Y2h1YW5rZS5jb22CCyouZGxuZWwuY29tggsqLmRsbmVsLm9yZ4ISKi5kdWVyb3Mu\n\
YmFpZHUuY29tghAqLmV5dW4uYmFpZHUuY29tghEqLmZhbnlpLmJhaWR1LmNvbYIR\n\
Ki5nei5iYWlkdWJjZS5jb22CEiouaGFvMTIzLmJhaWR1LmNvbYIMKi5oYW8xMjMu\n\
Y29tggwqLmhhbzIyMi5jb22CDiouaW0uYmFpZHUuY29tgg8qLm1hcC5iYWlkdS5j\n\
b22CDyoubWJkLmJhaWR1LmNvbYIMKi5taXBjZG4uY29tghAqLm5ld3MuYmFpZHUu\n\
Y29tggsqLm51b21pLmNvbYIQKi5zYWZlLmJhaWR1LmNvbYIOKi5zbWFydGFwcHMu\n\
Y26CESouc3NsMi5kdWFwcHMuY29tgg4qLnN1LmJhaWR1LmNvbYINKi50cnVzdGdv\n\
LmNvbYISKi54dWVzaHUuYmFpZHUuY29tggthcG9sbG8uYXV0b4IKYmFpZmFlLmNv\n\
bYIMYmFpZnViYW8uY29tggZkd3ouY26CD21jdC55Lm51b21pLmNvbYIMd3d3LmJh\n\
aWR1LmNughB3d3cuYmFpZHUuY29tLmNuMB0GA1UdJQQWMBQGCCsGAQUFBwMBBggr\n\
BgEFBQcDAjAdBgNVHQ4EFgQUdrXm1kn4+DbqdaltXk1VWzdc/ccwHwYDVR0jBBgw\n\
FoAUlt5h8b0cFilTHMDMfTuDAEDmGnwwggEEBgorBgEEAdZ5AgQCBIH1BIHyAPAA\n\
dgC72d+8H4pxtZOUI5eqkntHOFeVCqtS6BqQlmQ2jh7RhQAAAWqaLuGaAAAEAwBH\n\
MEUCICx7TcD5hUeKLQrAeTvWtLVm+Kr7glitIzb+Frymg5khAiEAwC/NnJkgy32R\n\
X9KLxhMQc7XBVAMzQZ+masUUk89pK2sAdgBvU3asMfAxGdiZAKRRFf93FRwR2QLB\n\
ACkGjbIImjfZEwAAAWqaLt5PAAAEAwBHMEUCIAMyaJ450OtfGWHbpxJpbyhEgQKl\n\
PMKjE9V+mCZfIBqgAiEAp4tis7C0RDLiEf9FjVURLDarKZNEyDRcznw1VzGuqxIw\n\
DQYJKoZIhvcNAQELBQADggEBAKq5zVKO3DZdR9SL8zIXBkaDYKMnBUkpsRtGbjj+\n\
k/4JQ2zSoVgkEkK3q0H4Rwp9ZLV13FpFFLKkGGuctzuPs37SvcBySzUFrg0tGR9Q\n\
c3Ja35cYO9sq895EzmQtwR6EzHYkPjBnIyboT/cL9uxp139RqaBvuMQU4sBKSsQA\n\
XVdqyUHEJSsyGKpiqB5JgXMcgV9e+uSUMsNQbY6qzGxMUwz6j040eZ+lYMD4UHW4\n\
oZ0B5qslIww7JAJAWCT/NAKLlGEQaC+2gOPQX0oKpwLSwJg+HegCyCdxJrKoh7bb\n\
nRBHS8ITYjTG0Dw5CTklj/6i9PP735snPfzQKOht3N0X0x8=\n\
-----END CERTIFICATE-----\n\
";

static u8 recv_buf[1461] = {0};

static struct in_addr ip4_addr = {0};

static void ql_nw_status_callback(int profile_idx, int nw_status)
{
	ssl_exam_log("profile(%d) status: %d", profile_idx, nw_status);
}

static void datacall_satrt(void)
{
	ssl_exam_log("wait for network register done");

	if(ql_network_register_wait(120) != 0)
	{
		ssl_exam_log("*** network register fail ***");
	}
	else
	{
		ssl_exam_log("doing network activing ...");
		
		ql_wan_start(ql_nw_status_callback);
		ql_set_auto_connect(1, TRUE);
		ql_start_data_call(1, 0, "3gnet.mnc001.mcc460.gprs", NULL, NULL, 0);
	}
}

static void do_ssl_client_test(void)
{
	int ret = 0;
	unsigned char ssl_inited = 0;
	unsigned char ssl_connected = 0;
	SSLCtx sslCtx = {0};
	SSLConfig sslConfig = 
	{
		.en = 1,
		.profileIdx = PROFILE_IDX,
		.serverName = SSL_SERVER_DOMAIN,
		.serverPort = SSL_SERVER_PORT,
		.protocol = 0,
		.dbgLevel = 2,
		.sessionReuseEn = 0,
		.vsn = SSL_VSN_ALL,
		.verify = SSL_VERIFY_MODE_NONE,
		.ignoreVerifyFlags = SSL_IGNORE_BADCERT_NOT_TRUSTED,
		.cert.from = SSL_CERT_FROM_BUF,
		.cert.path.rootCA = rootCA_path,
		.cert.path.clientKey = NULL,
		.cert.path.clientCert = NULL,
		.cert.clientKeyPwd.data = NULL,
		.cert.clientKeyPwd.len = 0,
		.cipherList = "ALL",
		.CTRDRBGSeed.data = NULL,
		.CTRDRBGSeed.len = 0
	};

do_ssl_conn:

	SSLSetConfig(&sslCtx, &sslConfig);
	
	ret = SSLCtxInit(&sslCtx);
	if(ret)
	{
		ssl_exam_log("*** ssl init fail ***");
		goto exit;
	}

	ssl_inited = 1;

	ret = SSLHandshake(&sslCtx, (CONNECT_TIMEOUT_S) * 1000);
	if(ret)
	{
		ssl_exam_log("*** ssl hand shake fail ***");
		goto exit;
	}

	ssl_connected = 1;

do_ssl_write:
	ret = SSLWrite(&sslCtx, (const void*)SSL_CLIENT_SEND_STR, strlen(SSL_CLIENT_SEND_STR), (SEND_TIMEOUT_S) * 1000);
	if(ret < 0)
	{
		ssl_exam_log("*** send fail ***");
		goto exit;
	}

do_ssl_read:
	ssl_exam_log("ssl recv data:");
	do
	{
		ret = SSLRead(&sslCtx, recv_buf, sizeof(recv_buf)-1, (RECV_TIMEOUT_S) * 1000);
		if(ret < 0)
		{
			ssl_exam_log("*** recv finished ***");
			goto exit;
		}
		else
		{
			recv_buf[ret] = 0;
			printf("%s", recv_buf);
		}
	}while(1);

	printf("\r\n");

exit:
	if(ssl_connected)
		SSLShutdown(&sslCtx, (CLOSE_LINGER_TIME_S) * 1000);
	if(ssl_inited)
		SSLCtxDeinit(&sslCtx);
}

static void ssl_client_test(void * argv)
{
	struct ql_data_call_info info = {0};
	char ip4_addr_str[16] = {0};

	ssl_exam_log("========== ssl test will start ...");

	datacall_satrt();

	ql_get_data_call_info(1, 0, &info);

	ssl_exam_log("info.profile_idx: %d", info.profile_idx);
	ssl_exam_log("info.ip_version: %d", info.ip_version);
	ssl_exam_log("info.v4.state: %d", info.v4.state);
	ssl_exam_log("info.v4.reconnect: %d", info.v4.reconnect);

	inet_ntop(AF_INET, &info.v4.addr.ip, ip4_addr_str, sizeof(ip4_addr_str));
	ssl_exam_log("info.v4.addr.ip: %s", ip4_addr_str);

	inet_ntop(AF_INET, &info.v4.addr.pri_dns, ip4_addr_str, sizeof(ip4_addr_str));
	ssl_exam_log("info.v4.addr.pri_dns: %s", ip4_addr_str);

	inet_ntop(AF_INET, &info.v4.addr.sec_dns, ip4_addr_str, sizeof(ip4_addr_str));
	ssl_exam_log("info.v4.addr.sec_dns: %s", ip4_addr_str);

	ip4_addr = info.v4.addr.ip;

	if(info.v4.state)
	{
		do_ssl_client_test();
	}

	ssl_exam_log("========== ssl test finished");
}

//application_init(ssl_client_test, "ssl_client_test", 8, 4);


