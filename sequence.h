#ifndef SEQUENCE_H
#define SEQUENCE_H
/* Header file for the sequence abstract data type (sequence.h) */

struct sequence_t;

typedef struct sequence_t *sequence;

/* create an empty sequence */
sequence sequence_create();

/* destroy the whole sequence (not objects)*/
void sequence_destroy(sequence s);

/* find the object at position pos and return it or NULL if not
   found */
void * sequence_find(sequence s, int pos);

/* insert an object between objects at position pos-1 and pos */
void sequence_insert(sequence s, void * object, int pos);

/* delete the object at position pos */
void sequence_delete(sequence s, int pos);

/* dump the sequence as integer object */
void sequence_dump(sequence s);

/* return the sequence length */
int sequence_length(sequence s);

#endif
