#include <stdlib.h>
#include <stdio.h>
#include "sequence.h"

struct sequence_t{
  void* data;
  sequence next;
  sequence head;
};

sequence sequence_create()
{
  sequence s = ( sequence )malloc( sizeof( struct sequence_t ) );
  if( s == NULL ){
    fprintf( stderr, "Malloc error in sequence_create()\n");
    exit(1);
  }
  s->data = NULL;
  s->next = NULL;
  s->head = s;
  return s;
}

void sequence_destroy( sequence s )
{
  while( s->next ){
    sequence tmp = s;
    s = s->next;
    free(tmp);
  }
  if( s->data )
    free(s);
    
  
  
}

void* sequence_find( sequence s, int pos )
{
  int i = 0;
  //sequence tmp = s;
  while( s->next && i != pos ){
    s = s->next;
    i++;
  }
  if( i == pos ){
    return s->data;
  }
  return NULL;
}

void sequence_insert( sequence s, void* object, int pos )
{
  int i = 0;
  //sequence tmp = s;
  sequence newElem = ( sequence )malloc( sizeof( struct sequence_t ) );
  newElem->data = object;
  newElem->next = NULL;
  newElem->head = s;

  while( s->next && i != pos ){
    s = s->next;
    i++;
  }
  if( i == pos ){
    newElem->next = s->next;
    s->next = newElem;
    s = s->head;
    return;
  }
  s->next = newElem;
  s = s->head;
}

void sequence_delete( sequence s, int pos )
{
  int i = 0;
  while( s->next && i != pos-1 ){
    s = s->next;
    i++;
  }
  if( i == pos-1 ){
    if( s->next->next ){
      s->next = s->next->next;
      return;
    }
    s->next = NULL;
    return;
  }
  s->data = NULL;
}

void sequence_dump( sequence s )
{
  printf ("[" );
  while( s->next ){
    s = s->next;
    printf( "%d, ", *( char* )( s->data ) );
  }
  printf( "]\n");
  s = s->head;
  
}

int sequence_length( sequence s )
{
  int length = 0;
  while( s->next ){
    s = s->next;
    length++;
  }
  return length;
}
