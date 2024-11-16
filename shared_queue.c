// Name: Juan Cota
// Date: 11/15/2024
// RedID: 827272362

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include "seating.h"
#include "shared_queue.h"
#include "producer.h"
#include "consumer.h"
#include "log.h"

#define MAX_QUEUE 18 // Max size of queue

// Shared Buffer
unsigned int sharedQ[MAX_QUEUE];

// Tracks Requests produced
unsigned int producedLog[2] = {0, 0};

// Tracks Requests consumed
unsigned int consumedLog[2] = {0, 0};

// Requests TX consumed
unsigned int txConsumed[2] = {0, 0};

// Requests R9 consumed
unsigned int r9Consumed[2] = {0, 0};

// Tracks Requests in queue
unsigned int inRequestQueue[2] = {0, 0};

// Current size of the queue
int queueSize = 0;

// total seating requests
int totalRqsts = 120;

// current seating requests
int seatRqsts = 120;

// total requests consumed
int consumed = 0;

RequestType toConsume;

// current count of the queue
int queueCount = 0;

int txZZZ = 0; // time tx sleeps
int r9ZZZ = 0; // time r9 sleeps
int ggTime = 0; // time general table requests take
int vipTime = 0; // time vip table requests take

unsigned int vipCurr = 0; // # of vip requests in queue

//unsigned int produced[seatRqsts];

// Lock
pthread_mutex_t mutex;

// Wait Condition
pthread_cond_t cond;

//sem_t semaphore;

// Inserts requests into queue
void enqueue (RequestType request){//, unsigned int produce[]){
    

    bool isEmpty = false; // Will this be the only item in the buffer?

    pthread_mutex_lock(&mutex); // Grab lock

    // Wait if buffer is full
    while (queueSize == MAX_QUEUE){
        pthread_cond_wait(&cond, &mutex);
    }

    // Only item in buffer
    if (queueSize == 0){
        isEmpty = true;
    }

    // Insert item if there is seating requests left
    if (seatRqsts > 0){
        sharedQ[queueCount] = request;
        queueCount++;

        // printQueue();

        // Keeps track of how many current items in queue (MAX of 18)
        queueSize++;

        // Updates Log
        if (request == 0){
             producedLog[0]++;
             inRequestQueue[0]++;
        } else if (request == 1){
            // VIP Increments
            vipCurr++;
            producedLog[1]++;
            inRequestQueue[1]++;
        }


        output_request_added(request, producedLog, inRequestQueue);

        // One less seating request
        seatRqsts--;
        
        //printf("%d\n", seatRqsts); // Seat requests countdown tracker
    }

    // Queue will no longer be empty so consumer is woken up
    if (isEmpty){
        pthread_cond_broadcast(&cond);
    }
    
    pthread_mutex_unlock(&mutex); // Release the lock

}

// Removes requests from queue
void dequeue(ConsumerType consumer){
    bool isFull = false; // Is buffer at capacity?
    pthread_mutex_lock(&mutex); // Grab lock
    while (queueSize == 0 && consumed < totalRqsts){ // Sleep if buffer is empty, until signaled
        pthread_cond_wait(&cond, &mutex);
    }

    

    // If full, there will be one space in the buffer afte we remove
    if (queueSize == MAX_QUEUE){
        isFull = true;
    }
    // Keep track of VIP requests
    // if (sharedQ[count - 1] == 1){
    //     vipCap++; // VIP spot opened up
    //     printf("%d", vipCap);
    // }
        // Grab the request to be removed (FIFO)

    toConsume = (RequestType)sharedQ[0];

    //printf("Queue Size: %d", queueSize);

    //printf("Finna remove an item");

    // Remove item
    for (int i = 0; i < queueCount - 1; i++){
    sharedQ[i] = sharedQ[i + 1];
    }

    //printQueue();

    //printf("Removed an item fam");

    
    if (consumed <= totalRqsts){
        queueSize--;
        queueCount--;
        consumed++;
    }

    if (toConsume == 1){
        vipCurr--;
    }
    
        
    // If TX
    if (consumer == 0){
        txConsumed[toConsume]++; // Increments Requests TX consumed
        consumedLog[toConsume]++; // Total Requests Consumed Log
        inRequestQueue[toConsume]--; // Updates Request Queue Log
    // If R9  
    } else if (consumer == 1){
        r9Consumed[toConsume]++; // Increments Requests R9 consumed
        consumedLog[toConsume]++; // Total Requests Consumed Log
        inRequestQueue[toConsume]--; // Updates Request Queue Log
    }

        output_request_removed(consumer, toConsume, consumedLog, inRequestQueue);
        
    // Queue will no longer be full so producer is woken up
    if (isFull){
        pthread_cond_broadcast(&cond);
    }

    pthread_mutex_unlock(&mutex); // Release the lock

}

// Prints the queue (For testing)
void printQueue(){
    for (int i = 0; i < queueCount; i++){
        
        printf("%d", sharedQ[i]);
    }
}