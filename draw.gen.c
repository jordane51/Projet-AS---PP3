#include <cairo.h>
#include <cairo-pdf.h>
	int main( void ){
	cairo_surface_t *surface;
	cairo_t *cr;
	cairo_surface_t *pdf_surface = cairo_pdf_surface_create("res.pdf",50,50);
	cr = cairo_create( pdf_surface );
	cairo_move_to( cr, 10.00, 10.00 );
	cairo_line_to( cr, 20.000000, 10.000000 );
	cairo_line_to( cr, 20.000000, 20.000000 );

}