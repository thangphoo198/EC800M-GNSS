/*******************************************************************************
 * Copyright (c) 2014, 2015 IBM Corp.
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * and Eclipse Distribution License v1.0 which accompany this distribution.
 *
 * The Eclipse Public License is available at
 *    http://www.eclipse.org/legal/epl-v10.html
 * and the Eclipse Distribution License is available at
 *   http://www.eclipse.org/org/documents/edl-v10.php.
 *
 * Contributors:
 *    Allan Stockdill-Mander - initial API and implementation and/or initial documentation
 *******************************************************************************/

#if !defined(MQTTQlRTOS_H)
#define MQTTQlRTOS_H

#include "ql_rtos.h"
#include "ql_ssl_hal.h"


typedef struct Timer 
{
	unsigned long long timeout_ticks;
	unsigned long long start_tick_val;
} Timer;

typedef struct Network Network;

struct Network
{
	int cid;
	int my_socket;
	int af;
	SSLCtx sslCtx;
	int (*mqttread) (Network*, unsigned char*, int, int);
	int (*mqttwrite) (Network*, unsigned char*, int, int);
	void (*disconnect) (Network*);
};

void TimerInit(Timer*);
char TimerIsExpired(Timer*);
void TimerCountdownMS(Timer*, unsigned int);
void TimerCountdown(Timer*, unsigned int);
int TimerLeftMS(Timer*);

typedef struct Mutex
{
	ql_mutex_t mutex;
} Mutex;

void MutexInit(Mutex*);
void MutexDeinit(Mutex* mutex);
int MutexLock(Mutex*);
int MutexUnlock(Mutex*);

typedef struct Thread
{
	ql_task_t task;
	unsigned int stack_size;
	unsigned char priority;
} Thread;

int ThreadStart(Thread*, void (*fn)(void*), void* arg);
void ThreadStop(Thread*);

int QlRTOS_read(Network*, unsigned char*, int, int);
int QlRTOS_write(Network*, unsigned char*, int, int);
void QlRTOS_disconnect(Network*);

void NetworkInit(Network*, SSLConfig*, int);
int NetworkConnect(Network*, char*, int);
void NetworkDisconnect(Network*);

#endif
