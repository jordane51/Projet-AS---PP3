#include <stdio.h>
#include <stdlib.h>
#include "generator.h"
#include <math.h>
#include "list.h"

#define LINE_WIDTH 1.0

List l;

int wasMoved = 0;
int currentDrawMode = DRAW_MODE_NONE;
int currentPointMode = POINT_MODE_NONE;
point firstPoint =  NULL;

FILE *pfile = NULL;
FILE *hfile = NULL;

int openFile(){
    pfile = fopen("draw.gen.c","w");
    hfile = fopen("draw.gen.h","w");
    if(pfile == NULL || hfile == NULL){
        return 0;
    }
    l = create_list();
    return 1;
}

void setFirstPoint( double x, double y){
    if(!firstPoint){
        firstPoint = malloc(sizeof(struct point));
    }
    firstPoint->x = x;
    firstPoint->y = y;
}

void setPointMode( int mode ){
    currentPointMode = mode;
}

void setDrawMode( int mode ){
    currentDrawMode = mode;
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

void printEnd(){
    fprintf(pfile, "\tcairo_destroy( cr );\n\tcairo_surface_destroy( pdf_surface );\n\treturn 0;\n}");
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
         setFirstPoint(x,y);
         if(currentPointMode == POINT_MODE_NONE)
             fprintf( pfile, "\tcairo_move_to( cr, %0.2f, %0.2f );\n", x, y );
         else if(currentPointMode == POINT_MODE_ADD)
             fprintf( pfile, "\tcairo_rel_move_to( cr, %0.2f, %0.2f );\n", x, y );
	  wasMoved++;
     } else {
         if(currentPointMode == POINT_MODE_NONE)
             fprintf( pfile, "\tcairo_line_to( cr, %0.2f, %0.2f );\n", x, y );
         else if(currentPointMode == POINT_MODE_ADD)
            fprintf( pfile, "\tcairo_rel_line_to( cr, %0.2f, %0.2f );\n", x, y );
     }
    //reset currentPointMode for next point ! -TODO add a function to do this
    currentPointMode = POINT_MODE_NONE;
}

void printPPoint( double angle, double rayon )
{
     
     angle = angle > 360 ? 360 : angle;
     angle = angle < 0 ? 0 : angle;
     rayon = rayon < 0 ? 0 : rayon;

     double x = rayon * cos( angle );
     double y = rayon * sin( angle );
     if( !wasMoved ){
         setFirstPoint(x,y);
         if(currentPointMode == POINT_MODE_NONE)
             fprintf( pfile, "\tcairo_move_to( cr, %0.2f, %0.2f );\n", x, y );
         else if(currentPointMode == POINT_MODE_ADD)
             fprintf( pfile, "\tcairo_rel_move_to( cr, %0.2f, %0.2f );\n", x, y );
	  wasMoved++;
     } else {
         if(currentPointMode == POINT_MODE_NONE)
             fprintf( pfile, "\tcairo_line_to( cr, %0.2f, %0.2f );\n", x, y );
         else if(currentPointMode == POINT_MODE_ADD)
             fprintf( pfile, "\tcairo_rel_line_to( cr, %0.2f, %0.2f );\n", x, y );
     }

}

void printCycle(){
    if(currentPointMode == POINT_MODE_NONE)
        fprintf( pfile, "\tcairo_line_to( cr, %0.2f, %0.2f );\n", firstPoint->x, firstPoint->y );
    else if(currentPointMode == POINT_MODE_ADD)
        fprintf( pfile, "\tcairo_rel_line_to( cr, %0.2f, %0.2f );\n", firstPoint->x, firstPoint->y );
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
void printDraw( void ){
    if(currentDrawMode == 0){
        // DO NOTHING
    } else if(currentDrawMode == DRAW_MODE_STROKE){ // STROKE
        fprintf( pfile,"\tcairo_set_line_width( cr , %f );\n\tcairo_stroke( cr );\n",LINE_WIDTH );
    } else if(currentDrawMode == DRAW_MODE_FILL){ // FILL
        fprintf( pfile,"\tcairo_set_source_rgb( cr, 0, 0, 0 );//black\n\tcairo_fill( cr );\n" );
    }
    // Reset was_moved for next command !
    free(firstPoint);
    firstPoint = NULL;
    wasMoved = 0;
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
