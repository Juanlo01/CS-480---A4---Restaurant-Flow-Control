// Name: Juan Cota
// Date: 11/15/2024
// RedID: 827272362

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "producer.h"
#include "seating.h"
#include "shared_queue.h"

// Max amount of VIP requests at a time
#define VIP_MAX 5

// Produces Seating Table Requests (General or VIP)
void *Producer(void *arg){

    // Request type (General or VIP)
    int *dequest = (int *)arg; // cast void* to int*
    RequestType request = (RequestType)*dequest; // Dereference into int
    
    // Amount of remaining seat requests
    int extern seatRqsts;

    // Imma be real, idk what this counts as of now 1:22 A.M. 11/15/2024
    // int extern sharedCount; UPDATE: Producer does not need this shit

    // General Request Wait Time (If Applicable)
    int extern ggTime;

    // VIP Request Wait Time (If Applicable)
    int extern vipTime;

    int extern vipCurr;

    // printf("General Producing time is: %d\n", ggTime);
    // printf("%d\n", request);
    
    
    // Produce as long as there are Seating Requests left
    while (seatRqsts > 0){
        // printf("Time to produce General Requests %d\n", ggTime);
        // Is it a general request?
        if (request == 0){
            // Does it take time to produce?
            if (ggTime > 0){
                usleep(ggTime);
                enqueue(request);
            } else{
                enqueue(request);
            }
        }

        // printf("Time to produce VIP Requests %d\n", vipTime);
        // Is it a VIP request
        if (request == 1){
            // Is it able to produce?
            if (vipCurr < VIP_MAX){
                // Does it take time to produce?
                if (vipTime > 0){
                    usleep(vipTime);
                    enqueue(request);
                } else{
                    enqueue(request);
                }
            }
        }
    }
   
    // Lets us know a producer thread is completed

    // General thread is done
    if (request == 0){
        //printf("General Producer Thread is finished\n");
        pthread_exit(0);
    }

    // VIP thread is done
    if (request == 1){
        //printf("VIP Producer Thread is finished\n");
        pthread_exit(0);
    }

}