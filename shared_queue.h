#ifndef SHARED_QUEUE_H
#define SHARED_QUEUE_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE 18


pthread_mutex_t mutex;
pthread_cond_t cond;


unsigned int sharedQ[MAX_QUEUE];
unsigned int producedLog[2];
unsigned int consumedLog[2];
unsigned int inRequestQueue[2];

int sharedCount;
int totalRqsts;
int seatRqsts;
int count;

unsigned int extern vipCount;

int vipCap;

int ggTime;

void enqueue(int request);

void dequeue();

void printQueue();


#endif
