//
//  queue.c
//  Program 2
//
//  Created by 额尔敦 on 3/14/19.
//  Copyright © 2019 额尔敦. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct car
{
    int length;
    struct car *next;
};

struct queue
{
    struct car *front, *rear;
};

struct car* new_node(int l)
{
    struct car *temp = (struct car*)malloc(sizeof(struct car));
    temp->length = l;
    temp->next = NULL;
    return temp;
}

struct queue *init_queue()
{
    struct queue *q = (struct queue*)malloc(sizeof(struct queue));
    q->front = q->rear = NULL;
    return q;
}

void queue_insert(struct queue *q, int l)
{
    struct car *temp = new_node(l);
    
    if (q->rear == NULL)
    {
        q->front = q->rear = temp;
        return;
    }
    
    q->rear->next = temp;
    q->rear = temp;
}

int check(struct queue *l, struct queue *r)
{
    if( l->front == NULL && r->front == NULL)
        return 1;
    return 0;
}

void queue_service(struct queue *q, int l)
{
    int sum=0;
    if(q->front == NULL)
        return;
    while(q->front!=NULL)
    {
        sum = sum + q->front->length;
        if(sum>l*100)
            break;
        q->front = q->front->next;
    }
    if (q->front == NULL)
        q->rear = NULL;
    
}

