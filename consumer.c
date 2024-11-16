// Name: Juan Cota
// Date: 11/15/2024
// RedID: 827272362

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>
#include "seating.h"
#include "consumer.h"
#include "shared_queue.h"
#include "log.h"

    // Consumes Seating Table Requests (General and VIP)
    void *Consumer(void *arg){

        // Robot type (TX or R9)
        int *RID = (int *)arg; // cast void* to int*
        ConsumerType robot = (ConsumerType)*RID; // Dereference into int

        // Keeps track of requests consumed
        int extern consumed;

        // Amount of remaining seat requests
        int extern totalRqsts;

        // Amount of time it takes r9 to consume (After dequeueing)
        int extern r9ZZZ;

        // Amount of time it takes tx to consume (After dequeueing)
        int extern txZZZ;

        int reportCounter = 0;
        
        
        //printf("TX sleep time is: %d\n", txZZZ);
            
        //printf("Total Requests: %d\n",totalRqsts);

        while (consumed < totalRqsts - 1){
            //printf("Consumed %d\n", consumed);
            //printf("Time for tx to consume %d\n", txZZZ);
            // Is the consumer TX?
            if (robot == 0){
                if (txZZZ > 0){
                    dequeue(robot);
                    // Consume after dequeue
                    usleep(txZZZ);
                }else{
                    dequeue(robot);
                }
            }

            //printf("Time for r9 to consume %d\n", r9ZZZ);
            // Is the consumer R9?
            if (robot == 1){
                if (r9ZZZ > 0){
                    dequeue(robot);
                    // Consume after dequeue
                    usleep(txZZZ);
                }else{
                    dequeue(robot);
                }
            }
        }

        

        // Lets us know a consumer thread is completed

        // TX thread is done
        if (robot == 0){
            //printf("T-X Consumer Thread is finished\n");
            reportCounter++;
                pthread_exit(0);
        }

        // R9 thread is done
        if (robot == 1){
            //printf("Rev-9 Consumer Thread is finished\n"
            pthread_exit(0);
        }
    }
            


