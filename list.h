#ifndef _LIST_H_
#define _LIST_H_

typedef struct list_t* List;
typedef struct elem_t* Elem;

List create_list();

void add_scalar( List l, char* name, double* value );
void add_Cpoint( List l, char* name, double* values );
void add_pointInPath( List l, char** point );
void add_path( List l, char* name );

double get_scalar( List l, char* name );
char* get_type( List l, char* name );
double get_pointValueX( List l, char* name );
double get_pointValueY( List l, char* name );
List get_path( List l, char* name );

void destroy( List l );
void delete_first( List l );

Elem get_firstElem( List l );
void* get_value( Elem e );

#endif
