#include "list.h"
#include <stdlib.h>
#include <stdio.h>

struct elem_t{
  char type[7];
  char name[256];
  void* value;
  Elem next;
};

struct list_t{
  Elem first;
};

List create_list()
{
  List l = ( List )malloc( sizeof( struct list_t ) );
  l->first = NULL;
  return l;
}

void add_scalar(List l, char* name, double* value )
{
  Elem e = ( Elem )malloc( sizeof( struct elem_t ) );
  sprintf( e->type, "scalar" );
  sprintf( e->name, "%s", name );
  e->value = value;
  e->next = l->first;
  l->first = e;
}

void add_Cpoint( List l, char* name, double* values )
{
  Elem e = ( Elem )malloc( sizeof( struct elem_t ) );
  sprintf( e->type, "Cpoint" );
  sprintf( e->name, "%s" , name );
  e->value = values;
  e->next = l->first;
  l->first = e;
}

double get_scalar( List l, char* name )
{
  Elem e = l->first;
  if( !strcmp( e->name, name ) ){
    return *( double* )( e->value );
  }
  while( e->next != NULL ){
    if( !strcmp( e->name, name ) ){
      return *( ( double* )e->value );
    }
  }
  return 1.0;
}

char* get_type( List l, char* name )
{
  Elem e = l->first;
  while( e != NULL ){
    if( !strcmp( name, e->name ) ){
      return e->type;
    }
    e = e->next;
  }
  return "NULL";
}

// TODO : Cette fonction puis la meme pour point y !!!!!
double get_pointValueX( List l, char* name )
{
  Elem e = l->first;
  while( e != NULL ){
    if( !strcmp( e->name, name ) ){
      double* d = e->value;
      return d[0];
    }
    e = e->next;
  }
  return -1.0;
}

double get_pointValueY( List l, char* name )
{
  Elem e = l->first;
  while( e != NULL ){
    if( !strcmp( e->name, name ) ){
      double* d = e->value;
      return d[1];
    }
    e = e->next;
  }
  return -1.0;
}

void destroy_rec( Elem e )
{
  if( e->next == NULL ){
    free( e->value );
    free( e );
    return;
  }
  destroy_rec( e->next );
  return;
}

void destroy( List l )
{
  if( l->first ){
    destroy_rec( l->first );
  }
  
  free( l );
}
