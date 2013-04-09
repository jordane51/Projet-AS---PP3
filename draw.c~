#include "draw.h"

void Init( void ){
  s = sequence_create();
}

void AddPoint( double x, double y ){
  
}

void DrawPoints( void ){
  Point object = NULL;
  int firstDraw = 1;
  while(queue_front(s) != NULL){
   object = queue_front(s);
   cairo_surface_t *surface;
   cairo_t cr;
   cairo_surface_t *pdf_surface = cairo_pdf_surface_create("test.pdf",50,50);
   cr = cairo_create(pdf_surface);
   if(firstDraw){
     cairo_move_to( cr, object->x,object->y );
     firstDraw = 0;
   } else {
     cairo_line_to( cr, object->x,object->y );
     cairo_set_line_width(cr, 10.0);
     cairo_stroke(cr);

     firstDraw = 1;
   }
   
   cairo_destroy(cr);
   cairo_surface_destroy(pdf_surface);
   
   
   
   
   
   
   queue_pop(s);
  }
}
 
