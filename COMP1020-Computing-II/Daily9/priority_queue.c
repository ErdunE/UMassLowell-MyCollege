//
//  priority_queue.c
//  Quiz 9
//
//  Created by 额尔敦 on 4/10/19.
//  Copyright © 2019 额尔敦. All rights reserved.
//

#include <stdlib.h>
#include "priority_queue.h"

typedef struct pair{
    int priority;
    int value;
}stu;
typedef struct pair Pair;

struct Queue{
    int size;
    int capacity;
    Pair* data;
};
typedef struct Queue Queue;

void upward(Pair heap[], int index);
void downward(Pair heap[], int index, int size);
void heapify(Pair numbers[], int size);
void heap_sort(Pair numbers[], int size);

void upward(Pair heap[], int index){
    int index_of_parent;
    index_of_parent = (index - 1)/2;
    Pair temp;
    if (index >= 1 && heap[index].priority > heap[index_of_parent].priority){
        temp = heap[index];
        heap[index] = heap[index_of_parent];
        heap[index_of_parent] = temp;
        upward(heap, index_of_parent);
    }
}

void downward(Pair heap[], int index, int size)
{
    int index_of_left_child;
    int index_of_right_child;
    index_of_left_child = index * 2 + 1;
    index_of_right_child = index * 2 + 2;
    int index_of_larger_child = size;
    Pair temp;
    
    if (index_of_right_child < size){
        if (heap[index_of_left_child].priority > heap[index_of_right_child].priority){
            index_of_larger_child = index_of_left_child;}
        else{
            index_of_larger_child = index_of_right_child;}
    }
    else if (index_of_left_child < size){
        index_of_larger_child = index_of_left_child;}
    if (index_of_larger_child < size && heap[index_of_larger_child].priority > heap[index].priority){
        temp = heap[index];
        heap[index] = heap[index_of_larger_child];
        heap[index_of_larger_child] = temp;
        downward(heap, index_of_larger_child, size);
    }
}

void heapify(Pair numbers[], int size){
    for (int i = (size - 2) / 2; i >= 0; i--){
        downward(numbers, i, size);}
}

void heap_sort(Pair numbers[], int size){
    int temp_size = size;
    Pair temp;
    heapify(numbers, size);
    for (int i = 0; i < size; i++){
        temp = numbers[0];
        numbers[0] = numbers[temp_size - 1];
        numbers[temp_size - 1] = temp;
        temp_size--;
        downward(numbers, 0, temp_size);}
}

PRIORITY_QUEUE priority_queue_init_default(void){
    Queue* pQueue;
    pQueue = (Queue*)malloc(sizeof(Queue));
    if (pQueue != NULL)
    {
        pQueue->size = 0;
        pQueue->capacity = 1;
        pQueue->data = (Pair*)malloc(sizeof(Pair) * pQueue->capacity);
        if (pQueue->data == NULL){
            free(pQueue);
            pQueue = NULL;
            
        }
    }
    return (PRIORITY_QUEUE)pQueue;
}

Status priority_queue_insert(PRIORITY_QUEUE hQueue, int priority_level, int data_item){
    Queue* pQueue = (Queue*)hQueue;
    Pair* temp,temp2;
    int index_of_parent;
    int i;
    if (pQueue->size >= pQueue->capacity){
        temp = (Pair*)malloc(sizeof(Pair) * 2 * pQueue->capacity);
        if (temp == NULL){
            return FAILURE;
        }
        for (i = 0; i < pQueue->size; i++){
            temp[i] = pQueue->data[i];
        }
        pQueue->capacity *= 2;
        free(pQueue->data);
        pQueue->data = temp;
    }
    i = pQueue->size;
    (pQueue->data[i]).priority = priority_level;
    (pQueue->data[i]).value = data_item;
    index_of_parent = (i - 1) / 2;
    while (i >= 1 && ((pQueue->data[i]).priority > (pQueue->data[index_of_parent]).priority))
    {
        temp2 = pQueue->data[index_of_parent];
        pQueue->data[index_of_parent] = pQueue->data[i];
        pQueue->data[i] = temp2;
        i = index_of_parent;
        index_of_parent = (i - 1) / 2;
    }
    pQueue->size++;
    heapify(pQueue->data,pQueue->size);
    return SUCCESS;
}

Status priority_queue_service(PRIORITY_QUEUE hQueue){
    Queue* pQueue = (Queue*)hQueue;
    Pair temp;
    if (pQueue->size == 0){
        return FAILURE;}
    temp = pQueue->data[0];
    pQueue->data[0] = pQueue->data[pQueue->size - 1];
    pQueue->data[pQueue->size - 1] = temp;
    pQueue->size--;
    heapify(pQueue->data, pQueue->size);
    return SUCCESS;
}

int priority_queue_front(PRIORITY_QUEUE hQueue, Status* pstatus){
    Queue* pQueue = (Queue*)hQueue;
    if (priority_queue_is_empty(hQueue)){
        if (pstatus != NULL){
            *pstatus = FAILURE;}
        return -1337;}
    if (pstatus != NULL){
        *pstatus = SUCCESS;}
    return pQueue->data[0].value;
}

Boolean priority_queue_is_empty(PRIORITY_QUEUE hQueue){
    Queue* pQueue = (Queue*)hQueue;
    return (Boolean)(pQueue->size == 0);}

void priority_queue_destroy(PRIORITY_QUEUE* phQueue){
    Queue* pQueue = (Queue*)*phQueue;
    free(pQueue->data);
    free(pQueue);
    *phQueue = NULL;
}


