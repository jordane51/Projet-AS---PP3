#include<stdio.h>
#include<stdlib.h>
#include "queue.h"

struct queue_t{
     void* data;
     struct queue_t* nextData;
     struct queue_t* lastElem;
};

queue queue_create(void)
{
     queue q = (queue)malloc(sizeof(struct queue_t));
     q->data = NULL;
     q->nextData = NULL;
     q->lastElem = q;

     return q;
}

void queue_destroy(queue s){
     while(!queue_empty(s)){
	  queue_pop(s);
     }
     free(s);
}

int queue_empty(queue s){
     return (s->nextData == NULL);
}

void queue_push(queue s, void *object){
     queue q = (queue)malloc(sizeof(struct queue_t));
     q->nextData = NULL;
     q->data = object;
     q->lastElem = NULL;
     s->lastElem->nextData = q;
     s->lastElem = q;
}


void * queue_front(queue s){
     if(!queue_empty(s))     
	  return s->nextData->data;
     return NULL;
}

void queue_pop(queue s){
     s->nextData->lastElem = s->lastElem;
     if(s->nextData->nextData != NULL)
	  s->nextData->data = s->nextData->nextData->data;
     queue qq = s->nextData;
     s->nextData = s->nextData->nextData;
     free(qq);
}
