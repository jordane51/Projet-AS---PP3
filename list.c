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
  if( e ){
    if( !strcmp( e->name, name ) ){
      return *( double* )( e->value );
    }
    while( e->next != NULL ){
      if( !strcmp( e->name, name ) ){
	return *( ( double* )e->value );
      }
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

void add_pointInPath( List l, char** point )
{
  Elem e = l->first;
  if( e ){
    Elem pt = ( Elem )malloc( sizeof( struct elem_t ) );
    sprintf( pt->type, "Cpoint" );
    double* xy = malloc( sizeof( double ) * 2 );
    xy[0] = atof( point[0] );
    xy[1] = atof( point[1] );
    pt->value = xy;

    List ll = ( List )e->value;
    pt->next = ll->first;
    ll->first = pt;
  }
  
}

void add_path( List l, char* name )
{
  printf(" add_path\n");
  List ll = ( List )malloc( sizeof( struct list_t ) );
  ll->first = NULL;
  Elem path = ( Elem )malloc( sizeof( struct elem_t ) );
  sprintf( path->type, "path" );
  sprintf( path->name, "%s", name );
  path->value = ll;
  path->next = l->first;
  l->first = path;
}

List get_path( List l, char* name )
{
  Elem e = l->first;
  if( e ){
    while( e != NULL ){
      if( !strcmp( e->name, name ) ){
	return ( List )e->value;
      } else {
	e = e->next;
      }
    }
  }
  return NULL;
}

void delete_first( List l )
{
  Elem tmp = l->first;
  l->first = l->first->next;
  free( tmp );
}

Elem get_firstElem( List l )
{
  return l->first;
}

void* get_value( Elem e )
{
  return e->value;
}
