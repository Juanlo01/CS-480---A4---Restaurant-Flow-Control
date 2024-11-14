#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "log.h"
#include "producer.h"
#include "consumer.h"
#include "shared_queue.h"

#define MAX_QUEUE 18
#define BADEXIT 1



int main(int argc, char *argv[]){

    int opt;

    pthread_t producer1;
    pthread_t producer2;
    pthread_t consumer1;
    pthread_t consumer2;

    extern int txZZZ;
    extern int r9ZZZ;
    extern int seatRqsts;
    extern int ggTime;

    

    while ((opt = getopt(argc, argv, "s:x:r:g:v:")) != -1 ){
        switch (opt){
            case 's' : 
                seatRqsts = atof(optarg);
                if (seatRqsts){
                    printf("Total number of seating requests is %d\n", seatRqsts);
                } else{
                    printf("Invalid argument\n");
                    return BADEXIT;
                }
            break;
            case 'x' : 
                txZZZ = atof(optarg);
                if (txZZZ){
                    printf("T-X robot will sleep for %d milliseconds\n", txZZZ);
                } else{
                    printf("Invalid argument\n");
                    return BADEXIT;
                }
            break;
            case 'r' : 
                r9ZZZ = atof(optarg);
                if (r9ZZZ){
                    printf("Rev-9 robot will sleep for %d milliseconds\n", r9ZZZ);
                } else{
                    printf("Invalid argument\n");
                    return BADEXIT;
                }
            break;
            case 'g' : 
                ggTime = atof(optarg);
                if (ggTime){
                    printf("Average time general greeter robots will produce and insert general table requests is %d\n", ggTime);
                } else{
                    printf("Invalid argument\n");
                    return BADEXIT;
                }
            break;
            case 'v' : 
                vipTime = atof(optarg);
                if (vipTime){
                    printf("Average time VIP room greeter robots will produce and insert VIP room requests is %d\n", vipTime);
                } else{
                    printf("Invalid argument\n");
                    return BADEXIT;
                }
            break;
            default:
                printf("default\n");
            break;
        }
    
    }

    pthread_create(&producer1, NULL, generalProducer, NULL); // VIP Greeter Robot
    //usleep(1000);
    pthread_create(&producer2, NULL, vipProducer, NULL); // General Greeter Robot
    //usleep(1000); // Busy Waiting *PLACEHOLDER FOR SEMAPHORES*
    pthread_create(&consumer1, NULL, TEGGS, NULL); // T-X Consumer Robot
    //usleep(1000);
    pthread_create(&consumer2, NULL, R9, NULL); // Rev-9 Consumer Robot
    
    // pthread_join(producer1, NULL);
    // pthread_join(producer2, NULL);
    // pthread_join(consumer1, NULL);
    // pthread_join(consumer2, NULL);
    
    return 0;
}
