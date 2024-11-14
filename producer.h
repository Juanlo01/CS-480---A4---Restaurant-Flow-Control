#ifndef PRODUCER_H
#define PRODUCER_H

#include <stdio.h>
#include <stdlib.h>

int request;

unsigned int vipCount;

int extern vipCap;

int extern ggTime;
int extern vipTime;
int extern sharedCount;
int extern seatRqsts;

void *generalProducer();

void *vipProducer();

#endif