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

#define TCP_SERVER_DOMAIN "220.180.239.212"
#define TCP_SERVER_PORT 8701
#define TCP_CONNECT_TIMEOUT_S 10
#define TCP_RECV_TIMEOUT_S 10
#define TCP_CLOSE_LINGER_TIME_S 10
#define TCP_CLIENT_SEND_STR "tcp client send string"
#define PROFILE_IDX 1

static struct in_addr ip4_addr = {0};

static void ql_nw_status_callback(int profile_idx, int nw_status)
{
	printf("profile(%d) status: %d\r\n", profile_idx, nw_status);
}

static void datacall_satrt(void)
{
	printf("wait for network register done\r\n");

	if(ql_network_register_wait(120) != 0)
	{
		printf("*** network register fail ***\r\n");
	}
	else
	{
		printf("doing network activing ...\r\n");
		
		ql_wan_start(ql_nw_status_callback);
		ql_set_auto_connect(1, TRUE);
		ql_start_data_call(1, 0, "NULL", NULL, NULL, 0);
	}
}

static void do_tcp_client_test(void)
{
	int sendandrecv_cnt = 0;
	int				sock_nbio	= 1;
	int				ret			= 0;
	int				sock_fd     = -1;
	int				sock_error  = 0;
	socklen_t		optlen = 0;
	fd_set 			read_fds, write_fds;
	struct timeval	t;
	struct addrinfo		* res, hints;
	struct sockaddr_in	* ip4_svr_addr;
	struct sockaddr_in	ip4_local_addr = {0};
	u8 dns_success = 0;
	u8 recv_buf[128] = {0};

	memset(&hints, 0, sizeof(struct addrinfo));
	
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;

	if(getaddrinfo_with_pcid(TCP_SERVER_DOMAIN, NULL, &hints, &res, PROFILE_IDX) != 0)
	{
		printf("*** DNS fail ***\r\n");
		goto exit;
	}

	dns_success = 1;
	
	ret = socket(AF_INET, SOCK_STREAM, 0);
	if(ret < 0)
	{
		printf("*** socket create fail ***\r\n");
		goto exit;
	}

	sock_fd = ret;

	ioctl(sock_fd, FIONBIO, &sock_nbio);

	ip4_local_addr.sin_family = AF_INET;
	ip4_local_addr.sin_port = htons(ql_soc_generate_port());
	ip4_local_addr.sin_addr = ip4_addr;
	
	ret = bind(sock_fd, (struct sockaddr *)&ip4_local_addr, sizeof(ip4_local_addr));
	if(ret < 0)
	{
		printf("*** bind fail ***\r\n");
		goto exit;
	}
	
	ip4_svr_addr = (struct sockaddr_in *)res->ai_addr;
	ip4_svr_addr->sin_port = htons(TCP_SERVER_PORT);

	ret = connect(sock_fd, (struct sockaddr *)ip4_svr_addr, sizeof(struct sockaddr));

	printf("connect ret: %d, errno: %u\r\n", ret, errno);

	if(ret == -1 && errno != EINPROGRESS)
	{
		printf("*** connect fail ***\r\n");
		goto exit;
	}

	t.tv_sec = TCP_CONNECT_TIMEOUT_S;
	t.tv_usec = 0;

	FD_ZERO(&read_fds);
	FD_ZERO(&write_fds);

	FD_SET(sock_fd, &read_fds);
	FD_SET(sock_fd, &write_fds);

	ret = select(sock_fd + 1, &read_fds, &write_fds, NULL, &t);

	printf("select ret: %d\r\n", ret);

	if(ret <= 0)
	{
		printf("*** select timeout or error ***\r\n");
		goto exit;
	}

	if(!FD_ISSET(sock_fd, &read_fds) && !FD_ISSET(sock_fd, &write_fds))
	{
		printf("*** connect fail ***\r\n");
		goto exit;
	}
	else if(FD_ISSET(sock_fd, &read_fds) && FD_ISSET(sock_fd, &write_fds))
	{
		optlen = sizeof(sock_error);
		ret = getsockopt(sock_fd, SOL_SOCKET, SO_ERROR, &sock_error, &optlen);
		if(ret == 0 && sock_error == 0)
		{
			printf("connect success\r\n");
		}
		else
		{
			printf("*** connect fail, sock_err = %d, errno = %u ***\r\n", sock_error, errno);
			goto exit;
		}
	}
	else if(!FD_ISSET(sock_fd, &read_fds) && FD_ISSET(sock_fd, &write_fds))
	{
		printf("connect success\r\n");
	}
	else if(FD_ISSET(sock_fd, &read_fds) && !FD_ISSET(sock_fd, &write_fds))
	{
		printf("*** connect fail ***\r\n");
		goto exit;
	}
	else
	{
		printf("*** connect fail ***\r\n");
		goto exit;
	}
tcpsend:
	ret = send(sock_fd, (const void*)TCP_CLIENT_SEND_STR, strlen(TCP_CLIENT_SEND_STR), 0);
	if(ret < 0)
	{
		printf("*** send fail ***\r\n");
		goto exit;
	}

tcprecv:

	t.tv_sec = TCP_RECV_TIMEOUT_S;
	t.tv_usec = 0;

	FD_ZERO(&read_fds);
	FD_SET(sock_fd, &read_fds);

	ret = select(sock_fd + 1, &read_fds, NULL, NULL, &t);

	printf("select ret: %d\r\n", ret);

	if(ret <= 0)
	{
		printf("*** select timeout or error ***\r\n");
		goto exit;
	}

	if(FD_ISSET(sock_fd, &read_fds))
	{
		ret = recv(sock_fd, recv_buf, sizeof(recv_buf), 0);
		if(ret > 0)
		{
			printf("recv data: [%d]%s\r\n", ret, recv_buf);
		}
		else if(ret == 0)
		{
			printf("*** peer closed ***\r\n");
			goto exit;
		}
		else
		{
			if(!(errno == EINTR || errno == EWOULDBLOCK || errno == EAGAIN))
			{
				printf("*** error occurs ***\r\n");
				goto exit;
			}
			else
			{
				printf("wait for a while\r\n");
				ql_rtos_task_sleep_ms(20);
				goto tcprecv;
			}
		}

	}
	//if(sendandrecv_cnt++<=10)//？会出现什么行为
	if(++sendandrecv_cnt<=10)//连续收发10次
		goto tcpsend;
exit:

	if(dns_success) freeaddrinfo(res);

	if(sock_fd >= 0)
	{
		struct linger linger = {0};

		linger.l_onoff = 1;
		linger.l_linger = TCP_CLOSE_LINGER_TIME_S;

		setsockopt(sock_fd, SOL_SOCKET, SO_LINGER, &linger, sizeof(linger));
        setsockopt(sock_fd, IPPROTO_TCP, TCP_CLOSE_TIMEROUT, &linger.l_linger, sizeof(linger.l_linger));

		close(sock_fd);
	}
}

static void sockets_tcp_client_test(void * argv)
{
	struct ql_data_call_info info = {0};
	char ip4_addr_str[16] = {0};

	printf("========== sockets tcp test will start ...\r\n");

	datacall_satrt();

	ql_get_data_call_info(1, 0, &info);

	printf("info.profile_idx: %d\r\n", info.profile_idx);
	printf("info.ip_version: %d\r\n", info.ip_version);
	printf("info.v4.state: %d\r\n", info.v4.state);
	printf("info.v4.reconnect: %d\r\n", info.v4.reconnect);

	inet_ntop(AF_INET, &info.v4.addr.ip, ip4_addr_str, sizeof(ip4_addr_str));
	printf("info.v4.addr.ip: %s\r\n", ip4_addr_str);

	inet_ntop(AF_INET, &info.v4.addr.pri_dns, ip4_addr_str, sizeof(ip4_addr_str));
	printf("info.v4.addr.pri_dns: %s\r\n", ip4_addr_str);

	inet_ntop(AF_INET, &info.v4.addr.sec_dns, ip4_addr_str, sizeof(ip4_addr_str));
	printf("info.v4.addr.sec_dns: %s\r\n", ip4_addr_str);

	ip4_addr = info.v4.addr.ip;

	if(info.v4.state)
	{
		do_tcp_client_test();
	}

	printf("========== sockets tcp test finished\r\n");
}


//application_init(sockets_tcp_client_test, "sockets_tcp_client_test", 4, 4);

