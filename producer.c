#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "producer.h"
#include "shared_queue.h"

#define VIP_MAX 5

void *generalProducer(){
    int extern ggTime;

    printf("General Producing time is: %d\n", ggTime);

    int request = 0; // General Request

    sharedCount;
    seatRqsts;


    while (seatRqsts > 0){

        

        if (ggTime > 0){
            usleep(ggTime);
        }

        

        enqueue(request);

    }
   
    printf("General Producer Thread is finished\n");
    pthread_exit(0);
    
}

void *vipProducer(){
    unsigned int vipCount = 0;
    int extern vipTime;

    printf("VIP producing time is: %d\n", vipTime);

    int request = 1; // VIP Request
    //int extern vipCap; // Maximum VIP Requests
    sharedCount;
    seatRqsts;

    // printf("%d\n", *vipTime); // Test Print (VIP request wait time)

    while (seatRqsts > 0){

        // printQueue();

        if (vipCount < VIP_MAX){
            

            if (vipTime > 0){
            usleep(vipTime);
            }

            vipCount++;

            

            enqueue(request);
            
            
        }
        
    }
   
    printf("VIP Producer Thread is finished\n");
    pthread_exit(0);
    
}

