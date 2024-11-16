// Name: Juan Cota
// Date: 11/15/2024
// RedID: 827272362

#ifndef CONSUMER_H
#define CONSUMER_H

#include <stdio.h>
#include <stdlib.h>

// Consumes Seating Table Requests (General and VIP)
void *Consumer(void *arg);

unsigned int extern consumedLog[2];
unsigned int extern producedLog[2];

// Refer to consumer.c
int extern sharedCount;

// Amount of remaining seat requests
int extern totalRqsts;

// Amount of time it takes r9 to consume (After dequeueing)
int extern r9ZZZ;

// Amount of time it takes tx to consume (After dequeueing)
int extern txZZZ;


#endif