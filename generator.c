#include <stdio.h>
#include <stdlib.h>
#include "generator.h"

FILE *pfile = NULL;

int openFile(){
     pfile = fopen("draw.gen.c","w");
     if(pfile == NULL){
	  return 0;
     }
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
     fprintf( pfile, "\tcairo_line_to( cr, %f, %f );\n", n1, n2 );
}

void printDouble(double d){
     fprintf(pfile,"%f",d); 
}

void closeFile(){
     fclose(pfile);
}
