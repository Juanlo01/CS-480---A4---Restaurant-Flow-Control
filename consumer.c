#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>
#include "consumer.h"
#include "shared_queue.h"
#include "log.h"

    // Consumes Seating Table Requests (General and VIP)
    void *Consumer(void *arg){
        unsigned int extern consumedLog[2];
        unsigned int extern producedLog[2]; 

        unsigned int *temp[2] = {&consumedLog[0], &consumedLog[1]};
        unsigned int **dptr = temp; // Create a double pointer for compatibility

        // Robot type (TX or R9)
        int *RID = (int *)arg; // cast void* to int*
        int robot = *RID; // Dereference into int

        // Keeps track of requests consumed
        int extern consumed;

        // Amount of remaining seat requests
        int extern totalRqsts;

        // Amount of time it takes r9 to consume (After dequeueing)
        int extern r9ZZZ;

        // Amount of time it takes tx to consume (After dequeueing)
        int extern txZZZ;
        
        
        //printf("TX sleep time is: %d\n", txZZZ);
            
        //printf("Total Requests: %d\n",totalRqsts);

        while (consumed < totalRqsts){
            //printf("Consumed %d\n", consumed);
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
            output_production_history(producedLog, dptr);
            pthread_exit(0);
        }

        // R9 thread is done
        if (robot == 1){
            //printf("Rev-9 Consumer Thread is finished\n");
            pthread_exit(0);
        }
    }
            


