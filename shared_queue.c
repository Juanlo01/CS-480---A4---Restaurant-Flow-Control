#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdatomic.h>
#include "shared_queue.h"
#include "producer.h"
#include "consumer.h"
#include "log.h"


#define MAX_QUEUE 18

unsigned int sharedQ[MAX_QUEUE];

unsigned int produced[2] = {0, 0};

unsigned int consumed[2] = {0, 0};

unsigned int inRequestQueue[2] = {0, 0};

// size of the queue
int queueSize = 0;

// total seating requests
int seatRqsts = 120;

// total requests sent
int sharedCount = 0;

// current count of the queue
int queueCount = 0;

int txZZZ = 0; // time tx sleeps
int r9ZZZ = 0; // time r9 sleeps
int ggTime = 0; // time general table requests take
int vipTime = 0; // time vip table requests take

unsigned int extern vipCount;

//unsigned int produced[seatRqsts];

// Lock
pthread_mutex_t mutex;

// Wait Condition
pthread_cond_t condition_cond;

//sem_t semaphore;


void enqueue(int request){//, unsigned int produce[]){
    

    bool isEmpty = false; // Will this be the only item in the buffer?

    pthread_mutex_lock(&mutex); // Grab lock

    // Wait if buffer is full
    if (queueSize == MAX_QUEUE){
        pthread_cond_wait(&condition_cond, &mutex);
    }

    // Only item in buffer
    if (queueSize == 0){
        isEmpty = true;
    }

    // Insert item if there is seating requests left
    if (seatRqsts > 0){
        sharedQ[queueCount] = request;
        queueCount++;

        if (request == 0){
             produced[0]++;
             inRequestQueue[0]++;
        } else if (request == 1){
             produced[1]++;
             inRequestQueue[1]++;
        }


        output_request_added(request, produced, inRequestQueue);

        seatRqsts--;
        
        //printf("%d\n", seatRqsts); // Seat requests countdown tracker
    }

    // Queue will no longer be empty so consumer is woken up
    if (isEmpty){
        pthread_cond_signal(&condition_cond);
    }
    
    pthread_mutex_unlock(&mutex); // Release the lock

}

void dequeue(){

    sharedCount++;
    printf("bruh\n");

    bool isFull = false; // Is buffer at capacity?

    pthread_mutex_lock(&mutex); // Grab lock

    while (queueSize == 0){ // Sleep until signaled
        pthread_cond_wait(&condition_cond, &mutex);
    }

    // If full, there will be one space in the buffer afte we remove
    if (queueSize == MAX_QUEUE){
        isFull == true;
    }

    // Keep track of VIP requests
    // if (sharedQ[count - 1] == 1){
    //     vipCap++; // VIP spot opened up
    //     printf("%d", vipCap);
    // }


   

    

    
    

        // Grab the request to be removed (FIFO)
        sharedQ[0] = request;
        
        if (request == 0){
             produced[0]--;
             
        } else if (request == 1){
             produced[1]--;
             
        }

        

        // Remove item
        for (int i = 0; i < queueCount - 1; i++){
        sharedQ[i] = sharedQ[i + 1];
        queueCount--;
        }

        

    
   

    // Queue will no longer be full so producer is woken up
    if (isFull){
        pthread_cond_signal(&condition_cond);
    }

    pthread_mutex_unlock(&mutex); // Release the lock

}

void printQueue(){
    for (int i = 0; i < queueCount - 1; i++){
        
        printf("%d", sharedQ[i]);
    }
}