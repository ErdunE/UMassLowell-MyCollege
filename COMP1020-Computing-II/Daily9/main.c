/**********************************************************************
 Program: Daily 9
 Author: Erdun E
 Date: April 10
 Time spent: 8 hours
 Purpose: Practice the implementation of priority queues
 ***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "priority_queue.h"


int main(int argc, char* argv[]){
    
    PRIORITY_QUEUE hQueue = NULL;
    hQueue = priority_queue_init_default();
   
    if (hQueue == NULL){
        printf("failed to creat new queue\n");
        exit(1);
    }
    priority_queue_insert(hQueue, 10, 5);
    priority_queue_insert(hQueue, 16, 2);
    priority_queue_insert(hQueue, 56, 4);
    priority_queue_insert(hQueue, 63, 8);
    priority_queue_insert(hQueue, 22, 1);
    priority_queue_insert(hQueue, 51, 7);
 
    while (priority_queue_is_empty(hQueue) != TRUE){
        printf("%d\n", priority_queue_front(hQueue, NULL));
        priority_queue_service(hQueue);
    }
    priority_queue_destroy(&hQueue);
}
