#include <cairo.h>
#include <cairo-pdf.h>
int main( void ){
cairo_surface_t *surface;
cairo_t *cr;
cairo_surface_t *pdf_surface = cairo_pdf_surface_create("res.pdf",50,50);
cr = cairo_create( pdf_surface );
}