#include "draw.h"

void Init( void ){
     s = queue_create();
}

void AddPoint( double x, double y ){
     Point p = ( Point )malloc( sizeof( struct point2d_t ) );
     p->x = x;
     p->y = y;
     queue_push( s, p );
}
void DrawPoints( void ){

}
 
void Destroy()
{
     queue_destroy( s );
}
