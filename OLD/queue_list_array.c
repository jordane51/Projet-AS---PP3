
#include<stdio.h>
#include<stdlib.h>
#include "queue.h"
#include <assert.h>

#define MAX_SIZE 2

struct queue_t{
     void** data;
     queue nextData;
     queue lastData;
     int back;
     int front;
};

queue queue_create(void){
     queue q = (queue)malloc(sizeof(struct queue_t));
     q->data = (void**)malloc(sizeof(void*) * MAX_SIZE);
     q->front = 0;
     q->back = 0;
     q->nextData = NULL;
     q->lastData = q;
     return q;
}

void queue_destroy(queue s){
     while(!queue_empty(s)){
	  queue_pop(s);
     }
     free(s->data);
     free(s);
}

int queue_empty(queue s){
     return (s->back==s->front);
}

void queue_push(queue s, void *object){
     if(s->front >= MAX_SIZE){
	  if(s->lastData->front >= MAX_SIZE){
	       queue q = malloc(sizeof(struct queue_t));
	       q->nextData = NULL;
	       q->lastData = NULL;
	       q->data = (void**)malloc(sizeof(void*) * MAX_SIZE);
	       q->front = 0;
	       q->back = 0;
	       
	       s->lastData->nextData = q;
	       s->lastData = q;
	       s->lastData->back = 0;
	       s->lastData->front = 0;
	  }
	  s->lastData->data[s->lastData->front++] = object;
	  return;
     }
     s->data[s->front++] = object;
}


void * queue_front(queue s){
     if(s->data != NULL){
	  return s->data[s->back];
     }
     return NULL;
}

void queue_pop(queue s){
     if(!queue_empty(s)){
	  s->back++;
	  if(queue_empty(s)){
	       if(s->nextData!=NULL){
		    free(s->data);
		    s->data = s->nextData->data;
		    s->back = s->nextData->back;
		    s->front = s->nextData->front;
		    queue q = s->nextData->nextData;
		    free(s->nextData);
		    s->nextData = q;
	       }
	  }
     }
     
}
