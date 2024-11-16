// Name: Juan Cota
// Date: 11/15/2024
// RedID: 827272362

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

// Inserts requests into queue
void enqueue(int request);

// Removes requests from queue
void dequeue();

// Prints the queue (For testing)
void printQueue();


#endif
