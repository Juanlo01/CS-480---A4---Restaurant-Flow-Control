#ifndef SHARED_QUEUE_H
#define SHARED_QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_QUEUE 18


pthread_mutex_t mutex;
pthread_mutex_t condition_mutex;
pthread_cond_t condition_cond;


unsigned int sharedQ[MAX_QUEUE];
unsigned int produced[2];
unsigned int consumed[2];
unsigned int inRequestQueue[2];

int sharedCount;
int seatRqsts;
int count;

unsigned int extern vipCount;

int vipCap;

int ggTime;

void enqueue(int request);

void dequeue();

void printQueue();


#endif
