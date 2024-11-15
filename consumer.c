#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>
#include "consumer.h"
#include "shared_queue.h"

// Consumes Seating Table Requests (General and VIP)
void *Consumer(void *arg){
    // Robot type (TX or R9)
    int *RID = (int *)arg; // cast void* to int*
    int robot = *RID; // Dereference into int

    // Refer to consumer.c
    int extern sharedCount;

    // Amount of remaining seat requests
    int extern seatRqsts;

    // Amount of time it takes r9 to consume (After dequeueing)
    int extern r9ZZZ;

    // Amount of time it takes tx to consume (After dequeueing)
    int extern txZZZ;
    
    
    //printf("TX sleep time is: %d\n", txZZZ);
        
        // Is the consumer TX?
        if (robot == 2){
            if (txZZZ > 0){
                dequeue();
                // Consume after dequeue
                usleep(txZZZ);
            }else{
                dequeue();
            }
        }

        // Is the consumer R9?
        if (robot == 3){
            if (r9ZZZ > 0){
                dequeue();
                // Consume after dequeue
                usleep(txZZZ);
            }else{
                dequeue();
            }
        }
            
    // Lets us know a consumer thread is completed

    // TX thread is done
    if (robot == 2){
        printf("T-X Consumer Thread is finished\n");
        pthread_exit(0);
    }

    // R9 thread is done
    if (robot == 3){
        printf("Rev-9 Consumer Thread is finished\n");
        pthread_exit(0);
    }
}
        


