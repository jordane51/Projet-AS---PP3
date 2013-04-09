#include "draw.h"
#include <stdlib.h>

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
     Point object = NULL;
     int firstDraw = 1;
     
     cairo_surface_t *pdf_surface = cairo_pdf_surface_create("test.pdf",50,50);
     cairo_t cr;
     cr = cairo_create(pdf_surface);
     while(queue_front(s) != NULL){
	  object = (Point)queue_front(s);
	  
	  if(firstDraw){
	       cairo_move_to( cr, object->x,object->y );
	       firstDraw = 0;
	  } else {
	       cairo_line_to( cr, object->x,object->y );
	       cairo_set_line_width(cr, 10.0);

	       //firstDraw = 1;
	  }
   
	  queue_pop(s);
     
     }
     cairo_stroke(cr);
     cairo_destroy(cr);
     cairo_surface_destroy(pdf_surface);
}
 
void Destroy()
{
     queue_destroy( s );
}
