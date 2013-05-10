#include <stdio.h>
#include <stdlib.h>
#include "generator.h"
#include <math.h>
#include <string.h>

#include "stack.h"

#define LINE_WIDTH 1.0

List l;
stack s;

int wasMoved = 0;
int currentDrawMode = DRAW_MODE_NONE;
int currentPointMode = POINT_MODE_NONE;
int currentPrintMode = PRINT_MODE_NONE;
int currentTransformMode = TRANSFORM_MODE_NONE;
double tAngle = 0.0;
double tTranslatex = 0.0;
double tTranslatey = 0.0;
point firstPoint =  NULL;

FILE *pfile = NULL;
FILE *hfile = NULL;

int openFile(){
    hfile = fopen("draw.funcs.c","w");
    pfile = fopen("draw.gen.c","w");
    if(pfile == NULL || hfile == NULL){
        return 0;
    }
    l = create_list();
    s = stack_create();
    return 1;
}

void settAngle( double a ){
    tAngle = a;
}

void setTx( double tx ){
    tTranslatex = tx;
}

void setTy( double ty ){
    tTranslatey = ty;
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

void setTransformMode( int mode ){
    currentTransformMode = mode;
}

void setDrawMode( int mode ){
    currentDrawMode = mode;
}

void setPrintMode( int mode ){
    currentPrintMode = mode;
}

void printInit(){
     fprintf(pfile, "#include <cairo.h>\n" \
	     "#include <cairo-pdf.h>\n" \
        "#include \"draw.funcs.c\"\n" \
             "cairo_surface_t *surface;\n" \
             "cairo_t *cr;\n" \
             "cairo_surface_t *pdf_surface;\n" \
	     "int main( void ){\n" \
             "\tpdf_surface = cairo_pdf_surface_create(\"res.pdf\",50,50);\n" \
	     "\tcr = cairo_create( pdf_surface );\n");

    //fprintf(hfile, "#include \"draw.gen.c\"\n");
     /*printFile("#include <cairo.h>\n" \ 
       "#include <cairo-pdf.h>\n" \ 
       "\tint main( void ){\n" \
       "\tcairo_surface_t *surface;\ncairo_t *cr;\n" \
       "\tcairo_surface_t *pdf_surface = cairo_pdf_surface_create(\"res.pdf\",50,50);\n" \
       "\tcr = cairo_create( pdf_surface );\n");*/
}

void printEnd(){
    fprintf(pfile, "\tcairo_destroy( cr );\n" \
				   "\tcairo_surface_destroy( pdf_surface );\n" \
				   "\treturn 0;\n}");
	destroy( l );
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
    // Si on est en mode transformation, on imprime la transformation nécessaire
    if(currentTransformMode == TRANSFORM_MODE_TRANSLATE)
        printTranslate(tTranslatex, tTranslatey);
    if(currentTransformMode == TRANSFORM_MODE_ROTATE)
        printRotate(tAngle);
    // Tout d'abord, si le point est le premier, on doit générer move_to plutot que line_to
     if( !wasMoved ){
         // C'est le premier point, on le stocke donc pour cycle
         setFirstPoint(x,y);
         // Si on est en mode image, il va falloir ajouter l'instruction aux instructions de l'image en haut de la pile
         if(currentPrintMode == PRINT_MODE_IMAGE){
             // Si on est en mode coordonnées absolues, on appelle cairo_move_to
             if(currentPointMode == POINT_MODE_NONE){
                 char *cc = topImage()->instructions;
                 char *tmp = malloc(sizeof(char) * 1024);
                 sprintf(tmp, "\tcairo_move_to( cr, %0.2f, %0.2f );\n" ,x,y);
                 strcat(cc, tmp);
                 //sprintf(cc, "\tcairo_move_to( cr, %0.2f, %0.2f );\n" ,x,y);
             }
             // Sinon, en mode coordonnées absolues, cairo_rel_move_to
             else if(currentPointMode == POINT_MODE_ADD){
                 char *cc = topImage()->instructions;
                 char *tmp = malloc(sizeof(char) * 1024);
                 sprintf(tmp,  "\tcairo_rel_move_to( cr, %0.2f, %0.2f );\n" ,x,y);
                 strcat(cc, tmp);
                 //sprintf( topImage()->instructions, "\tcairo_rel_move_to( cr, %0.2f, %0.2f );\n", x, y );
             }
         } else { // Si ce n'est pas le mode image, on fait pareil mais en écrivant dans le fichier
         if(currentPointMode == POINT_MODE_NONE)
             fprintf( pfile, "\tcairo_move_to( cr, %0.2f, %0.2f );\n", x, y );
         else if(currentPointMode == POINT_MODE_ADD)
             fprintf( pfile, "\tcairo_rel_move_to( cr, %0.2f, %0.2f );\n", x, y );
         }
	  wasMoved++;
     } else { // Si ce n'est pas le premier point, meme principe mais avec line_to
         if(currentPrintMode == PRINT_MODE_IMAGE){
             if(currentPointMode == POINT_MODE_NONE){
                 char *cc = topImage()->instructions;
                 char *tmp = malloc(sizeof(char) * 1024);
                 sprintf(tmp, "\tcairo_line_to( cr, %0.2f, %0.2f );\n" ,x,y);
                 strcat(cc, tmp);
                 //sprintf( topImage()->instructions, "\tcairo_line_to( cr, %0.2f, %0.2f );\n", x, y );
                 
             }
             else if(currentPointMode == POINT_MODE_ADD){
                 //sprintf( topImage()->instructions, "\tcairo_rel_line_to( cr, %0.2f, %0.2f );\n", x, y );
                 char *cc = topImage()->instructions;
                 char *tmp = malloc(sizeof(char) * 1024);
                 sprintf(tmp, "\tcairo_rel_line_to( cr, %0.2f, %0.2f );\n" ,x,y);
                 strcat(cc, tmp);
                 
             }
         } else {
         if(currentPointMode == POINT_MODE_NONE)
             fprintf( pfile, "\tcairo_line_to( cr, %0.2f, %0.2f );\n", x, y );
         else if(currentPointMode == POINT_MODE_ADD)
            fprintf( pfile, "\tcairo_rel_line_to( cr, %0.2f, %0.2f );\n", x, y );
         }
     }
    //reset currentPointMode for next point ! -TODO add a function to do this
    currentPointMode = POINT_MODE_NONE;
    //printf("Top: %s\n",topImage()->instructions);
}

void printPPoint( double angle, double rayon )
{
     
     angle = angle > 360 ? 360 : angle;
     angle = angle < 0 ? 0 : angle;
     rayon = rayon < 0 ? 0 : rayon;

     double x = rayon * cos( angle );
     double y = rayon * sin( angle );
    
    if(currentTransformMode == TRANSFORM_MODE_TRANSLATE)
        printTranslate(tTranslatex, tTranslatey);
    if(currentTransformMode == TRANSFORM_MODE_ROTATE)
        printRotate(tAngle);
    
    // Meme principe que printCPoint
     if( !wasMoved ){
         setFirstPoint(x,y);
         if(currentPrintMode == PRINT_MODE_IMAGE){
             if(currentPointMode == POINT_MODE_NONE)
                 sprintf(topImage()->instructions, "\tcairo_move_to( cr, %0.2f, %0.2f );\n", x, y );
             else if(currentPointMode == POINT_MODE_ADD)
                 sprintf(topImage()->instructions, "\tcairo_rel_move_to( cr, %0.2f, %0.2f );\n", x, y );
         } else {
         if(currentPointMode == POINT_MODE_NONE)
             fprintf( pfile, "\tcairo_move_to( cr, %0.2f, %0.2f );\n", x, y );
         else if(currentPointMode == POINT_MODE_ADD)
             fprintf( pfile, "\tcairo_rel_move_to( cr, %0.2f, %0.2f );\n", x, y );
         }
	  wasMoved++;
     } else {
         if(currentPrintMode == PRINT_MODE_IMAGE){
             if(currentPointMode == POINT_MODE_NONE)
                 sprintf( topImage()->instructions, "\tcairo_line_to( cr, %0.2f, %0.2f );\n", x, y );
             else if(currentPointMode == POINT_MODE_ADD)
                 sprintf( topImage()->instructions, "\tcairo_rel_line_to( cr, %0.2f, %0.2f );\n", x, y );
         } else {
         if(currentPointMode == POINT_MODE_NONE)
             fprintf( pfile, "\tcairo_line_to( cr, %0.2f, %0.2f );\n", x, y );
         else if(currentPointMode == POINT_MODE_ADD)
             fprintf( pfile, "\tcairo_rel_line_to( cr, %0.2f, %0.2f );\n", x, y );
         }
     }

}

void printCycle(){
    // Récupère la valeur du premier point de l'imprime
    if(currentPointMode == POINT_MODE_NONE)
        fprintf( pfile, "\tcairo_line_to( cr, %0.2f, %0.2f );\n", firstPoint->x, firstPoint->y );
    else if(currentPointMode == POINT_MODE_ADD)
        fprintf( pfile, "\tcairo_rel_line_to( cr, %0.2f, %0.2f );\n", firstPoint->x, firstPoint->y );
}

void printTranslate(double ix, double iy){
    fprintf( pfile, "\tcairo_translate( cr, %0.2f, %0.2f );\n", ix, iy );
}

void printRotate(double angle){
    fprintf( pfile, "\tcairo_rotate( cr, %f );\n", angle );
}

void printDouble(double d){
     fprintf(pfile,"%f",d); 
}

void printDraw( void ){
    // En fonction du mode de dessin courant, imprime les appels nécessaires
    if(currentDrawMode == DRAW_MODE_NONE){
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

variable variable_create(char *name, void *var, int type){
    variable va = malloc(sizeof(struct variable));
    va->name = name;
    va->var = var;
    va->type = type;
    return va;
}

image image_create(){
    image i = malloc(sizeof(struct image));
    i->instructions = malloc(sizeof(char *)*4096);
    i->variables = create_list();
    return i;
}

image topImage(){
    variable v = (variable)stack_top(s);
    image i = (image)v->var;
    return i;
}

void pushImage( char* name ){
    // Empile une image
    setPrintMode(PRINT_MODE_IMAGE);
    image i = image_create();
    variable v = variable_create(name,i, VAR_TYPE_IMAGE);
    stack_push(s, v);
}

void popImage(){
    // Pop image
    fprintf(pfile, topImage()->instructions);
    stack_pop(s);
    setPrintMode(PRINT_MODE_NONE);
}

void swapBuffers( void ){
    // Fonction utilitaire
    void* tmp = pfile;
    pfile = hfile;
    hfile = tmp;
}

void printFunctionStart( char* name ){
    fprintf( hfile, "void %s( void ){\n",name);
}

void printFunctionEnd( void ){
    fprintf( hfile, "}\n");
}

void printFunctionCall( char* name ){
    fprintf( pfile, "\t%s();\n",name );
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

void register_CPointVar( char* name, double v1, double v2 )
{
  double* v = malloc( sizeof( double ) * 2 );
  v[0] = v1;
  v[1] = v2;
  add_Cpoint( l, name, v );
}

double get_scalarValue( char* name )
{
  return get_scalar( l, name );
}

char* get_pointType( char* name )
{
  return get_type( l, name );
}

double get_pointXValue( char* name )
{
  return get_pointValueX( l, name );
}

double get_pointYValue( char* name )
{
  return get_pointValueY( l, name );
}

void register_path( char* name )
{
  add_path( l, name );
}

void register_pointInPath( char** point )
{
  add_pointInPath( l, point );
}

void printChemin( char* name )
{
  List path = get_path( l, name );
  Elem e = get_firstElem( path );
  //Elem e = path->first;
  while( e != NULL ){
    double* point = (double*)get_value( e );
    double x = point[0];
    double y = point[1];
    printCPoint( x, y );
    delete_first( path );
    e = get_firstElem( path );
  }
}
