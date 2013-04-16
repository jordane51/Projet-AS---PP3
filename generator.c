#include <stdio.h>
#include "generator.h"

void openFile(){
  
}

void printInit(){
  FILE *pfile = fopen("draw.gen.c","w+");
  fprintf(pfile,"#include <cairo.h>\n#include <cairo-pdf.h>\nint main( void ){\ncairo_surface_t *surface;\ncairo_t *cr;\ncairo_surface_t *pdf_surface = cairo_pdf_surface_create(\"res.pdf\",50,50);\ncr = cairo_create( pdf_surface );\n}");
  fclose(pfile);
}

void printFile(char *text){
  FILE *pfile = fopen("draw.gen.c","r+");
  fprintf(pfile,text);
  fclose(pfile);
}