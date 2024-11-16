// Name: Juan Cota
// Date: 11/15/2024
// RedID: 827272362

#ifndef SHARED_QUEUE_H
#define SHARED_QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include "seating.h"

#define MAX_QUEUE 18

unsigned int extern vipCount;

// Inserts requests into queue
void enqueue(RequestType request);

// Removes requests from queue
void dequeue(ConsumerType robot);

// Prints the queue (For testing)
void printQueue();


#endif
