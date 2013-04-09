#include<stdio.h>
#include<stdlib.h>
#include "queue.h"

struct queue_t{
};

/* create an empty queue */
queue queue_create(void){
  return NULL;
}

/* create an empty queue */
void queue_destroy(queue s){
}

/* return true if and only if the queue is empty */
int queue_empty(queue s){
  return 0;
}

/* push an object on the back of the queue */
void queue_push(queue s, void *object){
}


/* return the front element of the queue.
   The queue must not be empty (as reported by queue_empty()) */
void * queue_front(queue s){
  return NULL;
}

/* pop the front element off of the queue.
   The queue must not be empty (as reported by queue_empty()) */
void queue_pop(queue s){
}
