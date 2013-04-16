#include <stdio.h>
#include <stdlib.h>
#include "generator.h"

FILE *pfile = NULL;

int openFile(){
 pfile = fopen("draw.gen.c","w+");
 if(pfile == NULL){
   exit(EXIT_FAILURE);
 }
}

void printInit(){
  printFile("#include <cairo.h>\n#include <cairo-pdf.h>\nint main( void ){\ncairo_surface_t *surface;\ncairo_t *cr;\ncairo_surface_t *pdf_surface = cairo_pdf_surface_create(\"res.pdf\",50,50);\ncr = cairo_create( pdf_surface );\n}");
}

void printFile(char *text){
  if(pfile == NULL){
    openFile(); 
  }
  fprintf(pfile,text);
  fclose(pfile);
}