#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>
#include "consumer.h"
#include "shared_queue.h"

void *TEGGS(){
    int extern sharedCount;
    int extern txZZZ;
    

    
    printf("TX sleep time is: %d\n", txZZZ);
        
            if (txZZZ > 0){
                usleep(txZZZ);
                dequeue();
            }else{
                dequeue();
            }
        

        printf("TX Consumer Thread is finished\n");
        pthread_exit(0);
    }
        


void *R9(){
   
    int extern sharedCount;
    int extern seatRqsts;
    int extern r9ZZZ;

    printf("r9 sleep time is: %d\n", r9ZZZ);

    while (sharedCount < seatRqsts){
        if (r9ZZZ > 0){
                usleep(txZZZ);
                dequeue();
            }else{
                dequeue();
            }
    }

    printf("R9 Consumer Thread is finished\n");
    pthread_exit(0);
}