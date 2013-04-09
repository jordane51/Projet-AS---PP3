#include<stdio.h>
#include<stdlib.h>
#include "queue.h"

#define MAX_SIZE 100

struct queue_t{
     int back;
     int front;
     void** data;
};

queue queue_create(void){
     queue q = (queue)malloc(sizeof(struct queue_t));
     q->front = 0;
     q->back = 0;
     q->data = (void**)malloc(sizeof(void*) * MAX_SIZE);
     return q;
}

void queue_destroy(queue s){
     free(s->data);
     free(s);
}

int queue_empty(queue s){
     return (s->front == s->back);
}

void queue_push(queue s, void *object){
     s->data[s->back++%MAX_SIZE] = object;
}


void * queue_front(queue s){
     if(!queue_empty(s))
	  return s->data[s->front];
     return NULL;
}

void queue_pop(queue s){
     s->front = (s->front+1)%MAX_SIZE;
}
