#include <stdio.h>
#include <stdlib.h>
#include "generator.h"
#include <math.h>
#include "list.h"

struct point_t{
     double x;
     double y;
};

List l;

int wasMoved = 0;

FILE *pfile = NULL;

int openFile(){
     pfile = fopen("draw.gen.c","w");
     if(pfile == NULL){
	  return 0;
     }
     l = create_list();
     return 1;
}

void printInit(){
     fprintf(pfile, "#include <cairo.h>\n" \
	     "#include <cairo-pdf.h>\n" \
	     "\tint main( void ){\n" \
	     "\tcairo_surface_t *surface;\n" \
	     "\tcairo_t *cr;\n" \
	     "\tcairo_surface_t *pdf_surface = cairo_pdf_surface_create(\"res.pdf\",50,50);\n" \
	     "\tcr = cairo_create( pdf_surface );\n");

     /*printFile("#include <cairo.h>\n" \ 
       "#include <cairo-pdf.h>\n" \ 
       "\tint main( void ){\n" \
       "\tcairo_surface_t *surface;\ncairo_t *cr;\n" \
       "\tcairo_surface_t *pdf_surface = cairo_pdf_surface_create(\"res.pdf\",50,50);\n" \
       "\tcr = cairo_create( pdf_surface );\n");*/
}

void printFile(char *text){
     printf("Printing...\n");
     fprintf(pfile,text);
}

void printMove( double n1, double n2 )
{
     fprintf( pfile, "\tcairo_move_to( cr, %0.2f, %0.2f );\n", n1, n2 ); 
}

void printLine( double n1, double n2 )
{
     fprintf( pfile, "\tcairo_line_to( cr, %0.2f, %0.2f );\n", n1, n2 );
}

void printCPoint( double x, double y )
{
     if( !wasMoved ){
	  fprintf( pfile, "\tcairo_move_to( cr, %0.2f, %0.2f );\n", x, y ); 
	  wasMoved++;
     } else {
	  fprintf( pfile, "\tcairo_line_to( cr, %0.2f, %0.2f );\n", x, y );
     }
}

void printPPoint( double angle, double rayon )
{
     
     angle = angle > 360 ? 360 : angle;
     angle = angle < 0 ? 0 : angle;
     rayon = rayon < 0 ? 0 : rayon;

     double x = rayon * cos( angle );
     double y = rayon * sin( angle );
     if( !wasMoved ){
	  fprintf( pfile, "\tcairo_move_to( cr, %0.2f, %0.2f );\n", x, y ); 
	  wasMoved++;
     } else {
	  fprintf( pfile, "\tcairo_line_to( cr, %0.2f, %0.2f );\n", x, y );
     }

}

void printDouble(double d){
     fprintf(pfile,"%f",d); 
}



void printEnd()
{
  fprintf( pfile, "\tcairo_set_line_width( cr, 5.0);\n"	\
	   "\tcairo_stroke(cr);\n" \
	   "\tcairo_destroy(cr);\n" \
	   "\tcairo_surface_destroy(pdf_surface);\n" \
	   "\treturn 0;\n" \
	   "}");
  destroy( l );
}

void closeFile(){
     fclose(pfile);
}


void register_scalarVar( char* name, double value )
{
  double* v = malloc( sizeof( double ) );
  *v = value;
  add_scalar( l, name, v);
}

double get_scalarValue( char* name )
{
  return get_scalar( l, name );
}
