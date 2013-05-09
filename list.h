#ifndef _LIST_H_
#define _LIST_H_

typedef struct list_t* List;
typedef struct elem_t* Elem;

List create_list();
void add_scalar( List l, char* name, double* value );
void add_Cpoint( List l, char* name, double* values );
double get_scalar( List l, char* name );
char* get_type( List l, char* name );
double get_pointValueX( List l, char* name );
double get_pointValueY( List l, char* name );
void destroy( List l );

#endif
