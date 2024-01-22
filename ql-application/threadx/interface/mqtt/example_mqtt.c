/*================================================================
  Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/

#include "MQTTClient.h"
#include "ql_data_call.h"
#include "ql_application.h"
#include "sockets.h"
#include "ql_ssl_hal.h"

#define mqtt_exam_log(fmt, ...) printf("[MQTT_EXAM][%s, %d] "fmt"\r\n", __FUNCTION__, __LINE__, ##__VA_ARGS__)

#define PROFILE_IDX 1
#define SERVER_DOMAIN "broker.hivemq.com"

#define SSL_ENABLE 0

#if SSL_ENABLE
	#define SSL_VERIFY_MODE 1 // SSL_VERIFY_MODE_OPTIONAL
	#define SSL_CERT_FROM 0 // SSL_CERT_FROM_BUF
	#define SSL_CIPHER_LIST "ALL"
	#define SERVER_PORT_VERIFY_SERVER_ONLY 8307
	#define SERVER_PORT_VERIFY_BOTH 8308
	#define SERVER_PORT 8307
#else
	#define SERVER_PORT 1883
#endif

#if (SERVER_PORT == 8307)
	#if (SSL_CERT_FROM == 0)
	const static SSLCertPathPtr rootCA_path =
"\
-----BEGIN CERTIFICATE-----\n\
MIIEhDCCAuwCCQDuE1BpeAeMwzANBgkqhkiG9w0BAQsFADCBgjELMAkGA1UEBhMC\n\
Q04xCzAJBgNVBAgMAkFIMQswCQYDVQQHDAJIRjEQMA4GA1UECgwHUVVFQ1RFTDEL\n\
MAkGA1UECwwCU1QxFjAUBgNVBAMMDTExMi4zMS44NC4xNjQxIjAgBgkqhkiG9w0B\n\
CQEWE2VkZGllLnpoYW5nQHF1ZWN0ZWwwIBcNMjIwMTI1MDcyMzI3WhgPMjEyMjAx\n\
MDEwNzIzMjdaMIGCMQswCQYDVQQGEwJDTjELMAkGA1UECAwCQUgxCzAJBgNVBAcM\n\
AkhGMRAwDgYDVQQKDAdRVUVDVEVMMQswCQYDVQQLDAJTVDEWMBQGA1UEAwwNMTEy\n\
LjMxLjg0LjE2NDEiMCAGCSqGSIb3DQEJARYTZWRkaWUuemhhbmdAcXVlY3RlbDCC\n\
AaIwDQYJKoZIhvcNAQEBBQADggGPADCCAYoCggGBAMt3cjY0eLEDqv8Y7FomA+7N\n\
G5ztAbR7+P/WxjPlodqRDZ5HQORkfAr44gAZcWsKoo4DHTInwr9JBbBnETBMnL8+\n\
13h1PRp5CfwXKFvjppWYvBZfeTwhWQYbSMKINoS+d1Zl11jg/+ZbSd7Fi0bYq8ip\n\
Hbt30H+NANQZP1XQdsCf5/kvn+vXiP4EgJc56JQ9L6ALIF2Q6F3G/PTaYItg463N\n\
lv/S+eRi1VMDSs8Qc+DTlVwlgZZJdSlC8Yjr5pVqoyXm8ENKfSTrdhrLiKSWJTz9\n\
JUr04E7SJ+CoBAnLYNPHR2y0CFS/15aCa1JbK27ZJ/0cvBvzpWdkcgrDtKIcxNYM\n\
9QFPpehb1N4pgqi0NPhCkc/BasfmXUaTwM4ghhi4tQRptKMdTN/kdyC+V5a8Hyhb\n\
Nvw5qeJlLJKpgZ9X3HQzuKstKMkxLNuDIzK9TvO7zLowr+0BetUdllq+fDjXQM0M\n\
+9P3Xv2VmDwGRkmZ0IjYpDjm+qqGTFVLzzVwEqVD6wIDAQABMA0GCSqGSIb3DQEB\n\
CwUAA4IBgQAuNVwkBhd5nyWMmV/ESNxy59Sz+5FcesGclKjs4YocgcKbLD2bS+LN\n\
lKk6zenES7Cq6+l3NMAxxh/QhgHUCThAfREzfPXbmiicrUfaudN4YFivpoFwKIAs\n\
NczsL9S3FPbzAB4nLDATacc2BK0//aKMOU2t3KLNNomKbzlR+EW3wd0F1GoZ9SY6\n\
sCQeLa8Wp1KarOmbvgoFL/DAiTSqjjsU/Lq24dOCCctmG+qXRZxQa4npHD4xJwQJ\n\
qzA0JLu4n+DgoJftm1KpvB0wuzTn6M9+wnk5rv/fGc2t4Zra8B4prEReZZVfy65d\n\
cb8pBdb20Yrmznj+6DR50X/o/8Qzoyj9XpxtjwF23ql0XPYCI7kB03Ms9euP0btc\n\
HFacHapm0qBKx+vWy0V2Qf482OWSbewqaRbud44sErNoKqpqm02yN8PpsCywpFUj\n\
UC5G5DzxzYspMzQv/yidti0scMSKFObseZmNGlRYymCWhXnxmoCFjLpw5RnJSB2+\n\
cZ/1KFFHHZI=\n\
-----END CERTIFICATE-----\n\
";
	#endif
#elif (SERVER_PORT == 8308)
	#if (SSL_CERT_FROM == 0)
	const static SSLCertPathPtr rootCA_path =
"\
-----BEGIN CERTIFICATE-----\n\
MIIEhDCCAuwCCQDuE1BpeAeMwzANBgkqhkiG9w0BAQsFADCBgjELMAkGA1UEBhMC\n\
Q04xCzAJBgNVBAgMAkFIMQswCQYDVQQHDAJIRjEQMA4GA1UECgwHUVVFQ1RFTDEL\n\
MAkGA1UECwwCU1QxFjAUBgNVBAMMDTExMi4zMS44NC4xNjQxIjAgBgkqhkiG9w0B\n\
CQEWE2VkZGllLnpoYW5nQHF1ZWN0ZWwwIBcNMjIwMTI1MDcyMzI3WhgPMjEyMjAx\n\
MDEwNzIzMjdaMIGCMQswCQYDVQQGEwJDTjELMAkGA1UECAwCQUgxCzAJBgNVBAcM\n\
AkhGMRAwDgYDVQQKDAdRVUVDVEVMMQswCQYDVQQLDAJTVDEWMBQGA1UEAwwNMTEy\n\
LjMxLjg0LjE2NDEiMCAGCSqGSIb3DQEJARYTZWRkaWUuemhhbmdAcXVlY3RlbDCC\n\
AaIwDQYJKoZIhvcNAQEBBQADggGPADCCAYoCggGBAMt3cjY0eLEDqv8Y7FomA+7N\n\
G5ztAbR7+P/WxjPlodqRDZ5HQORkfAr44gAZcWsKoo4DHTInwr9JBbBnETBMnL8+\n\
13h1PRp5CfwXKFvjppWYvBZfeTwhWQYbSMKINoS+d1Zl11jg/+ZbSd7Fi0bYq8ip\n\
Hbt30H+NANQZP1XQdsCf5/kvn+vXiP4EgJc56JQ9L6ALIF2Q6F3G/PTaYItg463N\n\
lv/S+eRi1VMDSs8Qc+DTlVwlgZZJdSlC8Yjr5pVqoyXm8ENKfSTrdhrLiKSWJTz9\n\
JUr04E7SJ+CoBAnLYNPHR2y0CFS/15aCa1JbK27ZJ/0cvBvzpWdkcgrDtKIcxNYM\n\
9QFPpehb1N4pgqi0NPhCkc/BasfmXUaTwM4ghhi4tQRptKMdTN/kdyC+V5a8Hyhb\n\
Nvw5qeJlLJKpgZ9X3HQzuKstKMkxLNuDIzK9TvO7zLowr+0BetUdllq+fDjXQM0M\n\
+9P3Xv2VmDwGRkmZ0IjYpDjm+qqGTFVLzzVwEqVD6wIDAQABMA0GCSqGSIb3DQEB\n\
CwUAA4IBgQAuNVwkBhd5nyWMmV/ESNxy59Sz+5FcesGclKjs4YocgcKbLD2bS+LN\n\
lKk6zenES7Cq6+l3NMAxxh/QhgHUCThAfREzfPXbmiicrUfaudN4YFivpoFwKIAs\n\
NczsL9S3FPbzAB4nLDATacc2BK0//aKMOU2t3KLNNomKbzlR+EW3wd0F1GoZ9SY6\n\
sCQeLa8Wp1KarOmbvgoFL/DAiTSqjjsU/Lq24dOCCctmG+qXRZxQa4npHD4xJwQJ\n\
qzA0JLu4n+DgoJftm1KpvB0wuzTn6M9+wnk5rv/fGc2t4Zra8B4prEReZZVfy65d\n\
cb8pBdb20Yrmznj+6DR50X/o/8Qzoyj9XpxtjwF23ql0XPYCI7kB03Ms9euP0btc\n\
HFacHapm0qBKx+vWy0V2Qf482OWSbewqaRbud44sErNoKqpqm02yN8PpsCywpFUj\n\
UC5G5DzxzYspMzQv/yidti0scMSKFObseZmNGlRYymCWhXnxmoCFjLpw5RnJSB2+\n\
cZ/1KFFHHZI=\n\
-----END CERTIFICATE-----\n\
";
	const static SSLCertPathPtr clientCert_path =
"\
-----BEGIN CERTIFICATE-----\n\
MIIDiDCCAnACCQCUKPD5oM5pQzANBgkqhkiG9w0BAQsFADCBijELMAkGA1UEBhMC\n\
Q04xCzAJBgNVBAgMAkFIMQswCQYDVQQHDAJIRjEQMA4GA1UECgwHcXVlY3RlbDEM\n\
MAoGA1UECwwDRFRXMRcwFQYDVQQDDA4xOTIuMTY4LjIxLjE0MDEoMCYGCSqGSIb3\n\
DQEJARYZZWRkaWUuemhhbmdAcXVlY3R0CGVsLmNvbTAeFw0xOTEyMzExMjQ5MTda\n\
Fw0yOTEyMjgxMjQ5MTdaMIGAMQswCQYDVQQGEwJDTjELMAkGA1UECAwCQUgxCzAJ\n\
BgNVBAcMAkhGMRAwDgYDVQQKDAdxdWVjdGVsMQwwCgYDVQQLDANEVFcxDTALBgNV\n\
BAMMBHVzZXIxKDAmBgkqhkiG9w0BCQEWGWVkZGllLwguemhhbmdAcXVlY3RlbC5j\n\
b20wggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDP2MohVbTeWhy/LJXE\n\
vP5bw2We7S27mUKbP8vBMbfYCkgEDj1M4SVInAQbGb1YGw0i+m2NVSfu0Td/D0Qi\n\
LX/KwQahHb+6ZM3roIn77vl5m2jh/HMDI1yG2x5L4JsCMF0g5nZzaaHIdlQOHFgT\n\
sPsMhr/HwKqWzge6OLI9DSNuhS0Tk/sWtH3ylzlTgHeWtMBNsJyRMiXrJbJq827n\n\
Pj0yRgm0qGWa0Cz173ltYK8U0ZXlxdwcLGllt5GiV72f0mMxyXkIbqAyp6YKAmx1\n\
sPwAHGCwdu5zFwOzWvD07mXxvNzjqQTMGXNgdobvHS8/FhldUMLsD+0acVDzp4go\n\
1FA9AgMBAAEwDQYJKoZIhvcNAQELBQADggEBAIQl/BOYfxoCoXbE75N6Xflnccmv\n\
6IQY4hUoT6nA9efRtK58JNOPRGHpuIxxkcWmmVE7FqMV5B3uHCgDZNkkzdo3S02n\n\
ICPje6yBDbNf/5FJWkPMel1QzaLIYfvRXkQPvLq3uSqJoaTUDXmpWa8gPfUIyqNH\n\
qgM6syIorwxU3ZlWK+snh7n6jEJe3cCSIMPulJFYSgx9PYuzhu+lkNYKihd5fN9d\n\
eSAYM9nDP6hQLnyNxgg67evKwxK42fo5JROQV2JYRu03v+gaj2OyNeEPzsPh3Bw+\n\
qbYgf7NVH72yoLxjrN9smmRzWETb3Qw5EuIB9Z04eQDMCBVpkgkwCYMdn64=\n\
-----END CERTIFICATE-----\n\
";
	const static SSLCertPathPtr clientKey_path =
"\
-----BEGIN RSA PRIVATE KEY-----\n\
MIIEowIBAAKCAQEAz9jKIVW03locvyyVxLz+W8Nlnu0tu5lCmz/LwTG32ApIBA49\n\
TOElSJwEGxm9WBsNIvptjVUn7tE3fw9EIi1/ysEGoR2/umTN66CJ++75eZto4fxz\n\
AyNchtseS+CbAjBdIOZ2c2mhyHZUDhxYE7D7DIa/x8Cqls4HujiyPQ0jboUtE5P7\n\
FrR98pc5U4B3lrTATbCckTIl6yWyavNu5z49MkYJtKhlmtAs9e95bWCvFNGV5cXc\n\
HCxpZbeRole9n9JjMcl5CG6gMqemCgJsdbD8ABxgsHbucxcDs1rw9O5l8bzc46kE\n\
zBlzYHaG7x0vPxYZXVDC7A/tGnFQ86eIKNRQPQIDAQABAoIBADNN7u71ifTMx4XF\n\
Cp8Ki7q466+kGgLRnOhXggMJM7knKImfvi/o71wR7s2FuAA0hTSaHkqht36ytAEw\n\
EoBhPMceiHVis33d/hpogUbnwTrsSqJlvzoKE3/SPJM8OOb8azCA0sJAU8f4tVza\n\
UD9kE0QPSu2SuEkLSEsGTbDWOmXAFar8xIpS2rAoWLrPYbLdU7lxxgqbObC1lp/v\n\
ig8v16gD32vLgXJEjDDkMd0j98bFq+LqwuIDMfCGwkUqb3UUZIclJIOT3jWFILA8\n\
0Hduwm8EQ8VdgVAleAzW5JkFvOhz2w5y1IOI1ZfLoGTP7uNAM6nYwu8Ff3dojUrJ\n\
oPNawGECgYEA96fL4LTiWlBRn/Emzhoj6OPiN+ANtJT6zAxL7JmmdWfeutWw58B3\n\
+OHrnUKuV4SNcYE0+RYNBIvMdXuBw//datZq3KJX0Xg+roTIYMJiEi98zeYwjCla\n\
ePm8AAKMPUEzEK5OiH+YGI1o1Cc3MsrVj/xygJbnv+cJkiXHcnLRrsUCgYEA1tmd\n\
mtDbsoBPnj1tzJUYEnGlw1W7uXOtOpDhTT8VPjX9KdBwzUANL5vNgVeYO3JdpDuy\n\
G0TyRx7fVuUipyMZvNi9bGwIgVJ/h6n66K0JupS/HajpXruhy22pfVC59PBlSBC8\n\
gXvQ+91mSIqGK8B+xwgVZYvrkz3RWZETweL1MxkCgYEA2piSfaJL1Xnlwm6CWRN7\n\
tNpI2Bb9IfMKOEd2UL4CzsjDMVjjUHxzqQwJA4NTDc7jZles4VvUW7nl26ELlmxn\n\
DSF7q4nkR/GCKlrr33RUSkb+O2O+YEk0IWoVxlB5ZqwBHe0tRpCROMLAz9pZf4zH\n\
2tLyYoxQvPN6YDTWii/M4x0CgYAl+dEhzEkJBCUOk00VHEVk/TGPlVfZL9kuwO0R\n\
+lSG6oQVIALQRMIP6Doq4pDF8TEcFnEk4MryR0Ky2U2GvW2PM8BHqdDXCv3/vMvc\n\
1LkjgadGVtTpKcEvc/LBc8NqyBMe6dZoDLqjyj6KE/IjSaMfCw69JD4/iG24pywW\n\
2Ub+AQKBgFUzB9R2ql0pMJ7trls+e53udeHcG9HXWe6cZWfHWwiKAVDg/4POquGV\n\
nBzkjVnA88ZYq7iY2xGYZOOWPoI8+jkRpgtI75T00ChbDx+t4Qwb13e3KiNakWcF\n\
cN20g9Ix2D8Lm5Of8b1j70PbvFD9WpMCL1ikc1AXxY2HgTgGoKxj\n\
-----END RSA PRIVATE KEY-----\n\
";
	#endif
#endif


static void messageArrived(MessageData* data)
{
	mqtt_exam_log("Message arrived on topic %.*s: %.*s", data->topicName->lenstring.len, (char*)data->topicName->lenstring.data,data->message->payloadlen, (char*)data->message->payload);
}

static void MQTTEchoTask(void *argv)
{
	/* connect to m2m.eclipse.org, subscribe to a topic, send and receive messages regularly for 3 times */
	MQTTClient client = {0};
	Network network = {0};
	unsigned char sendbuf[80] = {0}, readbuf[80] = {0};
	int rc = 0, 
		count = 0;
	MQTTPacket_connectData connectData = MQTTPacket_connectData_initializer;
	SSLConfig SSLConfig = {
		.en = SSL_ENABLE,
	#if SSL_ENABLE
		.profileIdx = PROFILE_IDX,
		.serverName = SERVER_DOMAIN,
		.serverPort = SERVER_PORT,
		.protocol = 0,
		.dbgLevel = 0,
		.sessionReuseEn = 0,
		.vsn = SSL_VSN_ALL,
		.verify = SSL_VERIFY_MODE,
		.cert.from = SSL_CERT_FROM_BUF,
	#if (SERVER_PORT == 8307)
		.cert.path.rootCA = rootCA_path,
		.cert.path.clientKey = NULL,
		.cert.path.clientCert = NULL,
	#elif (SERVER_PORT == 8308)
		.cert.path.rootCA = rootCA_path,
		.cert.path.clientKey = clientKey_path,
		.cert.path.clientCert = clientCert_path,
		.cert.clientKeyPwd.data = NULL,
		.cert.clientKeyPwd.len = 0,
	#endif
		.cipherList = SSL_CIPHER_LIST,
		.CTRDRBGSeed.data = NULL,
		.CTRDRBGSeed.len = 0
	#endif
	};
	
	argv = 0;
	NetworkInit(&network, &SSLConfig, PROFILE_IDX);
	MQTTClientInit(&client, &network, 30000, sendbuf, sizeof(sendbuf), readbuf, sizeof(readbuf));

	char* address = SERVER_DOMAIN;
	if ((rc = NetworkConnect(&network, address, SERVER_PORT)) != 0)
	{
		mqtt_exam_log("Return code from network connect is %d", rc);
		MQTTClientDeinit(&client);
		goto exit;
	}

	connectData.MQTTVersion = 3;
	connectData.clientID.cstring = "ql_mqtt_sample";

	if ((rc = MQTTConnect(&client, &connectData)) != 0)
	{
		mqtt_exam_log("Return code from MQTT connect is %d", rc);
		NetworkDisconnect(&network);
		MQTTClientDeinit(&client);
		goto exit;
	}
	else
		mqtt_exam_log("MQTT Connected");

#if defined(MQTT_TASK)
	if ((rc = MQTTStartTask(&client)) != 0)
	{
		mqtt_exam_log("Return code from start tasks is %d", rc);
		NetworkDisconnect(&network);
		MQTTClientDeinit(&client);
		goto exit;
	}
#endif

	if ((rc = MQTTSubscribe(&client, "EC800M_REMOTE", 2, messageArrived)) != 0)
	{
		mqtt_exam_log("Return code from MQTT subscribe is %d", rc);
		
		rc = MQTTDisconnect(&client);
		if(rc == SUCCESS)
			mqtt_exam_log("MQTT Disconnected by client");
		else
			mqtt_exam_log("MQTT Disconnected failed by client");
		
		NetworkDisconnect(&network);
		
		MQTTClientDeinit(&client);

		goto exit;
	}

	while (1)
	{
		MQTTMessage message;
		char payload[30];

		message.qos = 1;
		message.retained = 0;
		message.payload = payload;
		sprintf(payload, "message number %d", count);
		message.payloadlen = strlen(payload);

		if ((rc = MQTTPublish(&client, "EC800M_REC", &message)) != 0)
			mqtt_exam_log("Return code from MQTT publish is %d", rc);
#if !defined(MQTT_TASK)
		if ((rc = MQTTYield(&client, 1000)) != 0)
			mqtt_exam_log("Return code from yield is %d", rc);
#endif
		ql_rtos_task_sleep_ms(5000);
	}

	rc = MQTTDisconnect(&client);
	if(rc == SUCCESS)
		mqtt_exam_log("MQTT Disconnected by client");
	else
		mqtt_exam_log("MQTT Disconnected failed by client");

	NetworkDisconnect(&network);
	
	MQTTClientDeinit(&client);

exit:
	
	mqtt_exam_log("========== mqtt test end ==========");
	ql_rtos_task_delete(NULL);
}


static void StartMQTTTask(void)
{
	ql_task_t task = NULL;
	ql_rtos_task_create(&task, 8*1024, 100, "mqtt_test", MQTTEchoTask, NULL);
}

static void ql_nw_status_callback(int profile_idx, int nw_status)
{
	mqtt_exam_log("profile(%d) status: %d", profile_idx, nw_status);
}

static int datacall_start(void)
{
	struct ql_data_call_info info = {0};
	char ip4_addr_str[16] = {0};
	
	mqtt_exam_log("wait for network register done");

	if(ql_network_register_wait(120) != 0)
	{
		mqtt_exam_log("*** network register fail ***");
		return -1;
	}
	else
	{
		mqtt_exam_log("doing network activating ...");
		
		ql_wan_start(ql_nw_status_callback);
		ql_set_auto_connect(PROFILE_IDX, TRUE);
		if(ql_start_data_call(PROFILE_IDX, 0, "v-internet", NULL, NULL, 0) == 0)
		{
			ql_get_data_call_info(PROFILE_IDX, 0, &info);
			
			mqtt_exam_log("info.profile_idx: %d", info.profile_idx);
			mqtt_exam_log("info.ip_version: %d", info.ip_version);
			mqtt_exam_log("info.v4.state: %d", info.v4.state);
			mqtt_exam_log("info.v4.reconnect: %d", info.v4.reconnect);
			
			inet_ntop(AF_INET, &info.v4.addr.ip, ip4_addr_str, sizeof(ip4_addr_str));
			mqtt_exam_log("info.v4.addr.ip: %s", ip4_addr_str);
			
			inet_ntop(AF_INET, &info.v4.addr.pri_dns, ip4_addr_str, sizeof(ip4_addr_str));
			mqtt_exam_log("info.v4.addr.pri_dns: %s", ip4_addr_str);
			
			inet_ntop(AF_INET, &info.v4.addr.sec_dns, ip4_addr_str, sizeof(ip4_addr_str));
			mqtt_exam_log("info.v4.addr.sec_dns: %s", ip4_addr_str);

			return 0;
		}

		mqtt_exam_log("*** network activated fail ***");
		return -1;
	}
}

static void MQTTTest(void *argv)
{
	(void)argv;
	
	mqtt_exam_log("========== mqtt test satrt ==========");
	
	if(datacall_start() == 0)
		StartMQTTTask();
	else
		mqtt_exam_log("========== mqtt test end ==========");
}

application_init(MQTTTest, "mqtttest", 2, 14);

