#include<stdlib.h>
#include"stack.h"

struct list_t;
typedef struct list_t *list;

struct list_t{
  list next;
  void * object;
};

struct stack_t{
  list l;
};

/* create an empty stack */
stack stack_create(void){
  stack s= malloc(sizeof(*s));
  s->l=NULL;

  return s;
}


/* push an object on a stack */
void stack_push(stack s, void *object){
  if(s == NULL)
    return;

  list new=malloc(sizeof(*new));

  new->next = s->l;
  new->object=object;
  s->l=new;
}

/* return true if and only if the stack is empty */
int stack_empty(stack s){
  if(s == NULL)
    return 0;

  return(s->l == NULL);
}

/* return the top element of the stack.
   The stack must not be empty (as reported by stack_empty()) */
void * stack_top(stack s){
  if(s == NULL)
    return NULL;

  if(stack_empty(s))
    return NULL;

  return s->l->object;
}

/* pop an element off of the stack.
   The stack must not be empty (as reported by stack_empty()) */
void stack_pop(stack s){
  if(s == NULL)
    return;

  if(stack_empty(s))
    return;

  list tmp=s->l;
  s->l=tmp->next;
  free(tmp);
}
