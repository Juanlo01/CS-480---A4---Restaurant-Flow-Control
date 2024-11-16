// Name: Juan Cota
// Date: 11/15/2024
// RedID: 827272362

#ifndef PRODUCER_H
#define PRODUCER_H

#include <stdio.h>
#include <stdlib.h>

// Produces Seating Table Requests (General or VIP)
void *Producer(void *arg);

// Request type (General or VIP)
int request;

// Amount of remaining seat requests
int extern seatRqsts;

// Imma be real, idk what this counts as of now 1:22 A.M. 11/15/2024
int extern sharedCount;

// General Request Wait Time (If Applicable)
int extern ggTime;

// VIP Request Wait Time (If Applicable)
int extern vipTime;

#endif