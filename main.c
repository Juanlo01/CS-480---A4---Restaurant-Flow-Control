// Name: Juan Cota
// Date: 11/15/2024
// RedID: 827272362

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

    extern pthread_mutex_t mutex;
    extern pthread_cond_t cond;

    unsigned int extern consumedLog[2];
    unsigned int extern producedLog[2];

    unsigned int extern txConsumed[2];
    unsigned int extern r9Consumed[2]; 

    unsigned int *temp[2] = {&txConsumed[0], &r9Consumed[0]};
    unsigned int **dptr = temp; // Create a double pointer for compatibility

    extern int txZZZ;
    extern int r9ZZZ;
    extern int totalRqsts;
    extern int seatRqsts;
    extern int ggTime;

    int ggRequest = 0;
    int vipRequest = 1;
    int txID = 0;
    int r9ID = 1;

    while ((opt = getopt(argc, argv, "s:x:r:g:v:")) != -1 ){
        switch (opt){
            case 's' : 
                seatRqsts = atof(optarg);
                totalRqsts = seatRqsts;
                if (seatRqsts){
                } else{
                    seatRqsts = 0;
                }
            break;
            case 'x' : 
                txZZZ = atof(optarg);
                if (txZZZ){
                } else{
                    txZZZ = 0;
                }
            break;
            case 'r' : 
                r9ZZZ = atof(optarg);
                if (r9ZZZ){
                } else{
                    r9ZZZ = 0;
                }
            break;
            case 'g' : 
                ggTime = atof(optarg);
                if (ggTime){
                } else{
                    ggTime = 0;
                }
            break;
            case 'v' : 
                vipTime = atof(optarg);
                if (vipTime){
                } else{
                    vipTime = 0;
                }
            break;
            default:
            break;
        }
    
    }

    // Initialize mutex & condition variables
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    // General Producer
    pthread_create(&producer1, NULL, Producer, &ggRequest); 

    // VIP Producer
    pthread_create(&producer2, NULL, Producer, &vipRequest);

    // T-X Consumer
    pthread_create(&consumer1, NULL, Consumer, &txID);

    // Rev-9 Consumer
    pthread_create(&consumer2, NULL, Consumer, &r9ID);
    
    // General Producer join
    pthread_join(producer1, NULL);

    // VIP Producer join
    pthread_join(producer2, NULL);

    // T-X Consumer join
    pthread_join(consumer1, NULL);

    // Rev-9 Consumer join
    pthread_join(consumer2, NULL);

    // Outputs Request Report
    output_production_history(producedLog, dptr);

    // Destroy mutex & condition variables
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
    
    return 0;
}
