#ifndef CONSUMER_H
#define CONSUMER_H

#include <stdio.h>
#include <stdlib.h>

// Consumes Seating Table Requests (General and VIP)
void *Consumer(void *arg);

// Refer to consumer.c
int extern sharedCount;

// Amount of remaining seat requests
int extern seatRqsts;

// Amount of time it takes r9 to consume (After dequeueing)
int extern r9ZZZ;

// Amount of time it takes tx to consume (After dequeueing)
int extern txZZZ;


#endif