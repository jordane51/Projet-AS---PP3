#ifndef _LIST_H_
#define _LIST_H_

typedef struct list_t* List;
typedef struct elem_t* Elem;

List create_list();
void add_scalar( List l, char* name, double* value );
double get_scalar( List l, char* name );
void destroy( List l );

#endif
