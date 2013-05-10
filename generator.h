#ifndef _GENERATOR_H_
#define _GENERATOR_H_
#include "list.h"

enum{
    PRINT_MODE_NONE, //"Default" value
    PRINT_MODE_IMAGE,
    DRAW_MODE_NONE, //"Default" value
    DRAW_MODE_STROKE,
    DRAW_MODE_FILL,
    POINT_MODE_NONE,//"Default" value
    POINT_MODE_ADD,
    VAR_TYPE_IMAGE,
    VAR_TYPE_SCALAR,
    VAR_TYPE_POINT,
    VAR_TYPE_PATH,
    TRANSFORM_MODE_NONE,
    TRANSFORM_MODE_ROTATE,
    TRANSFORM_MODE_TRANSLATE
};

struct variable{
    int type;
    char *name;
    void *var;
};

struct point{
    double x;
    double y;
};

struct image{
    char *instructions;
    List variables;
};

typedef struct variable *variable;
typedef struct image *image;
typedef struct point *point;


variable variable_create(char *,void *,int);



image image_create();

// Used to open the generated text file (draw.gen.c)
int openFile();

// Sets the current drawing mode to whatever is specified
void setDrawMode( int );

// Sets the current point type
void setPointMode( int );

void setTransformMode( int );

void settAngle( double );

void setTx( double );

void setTy( double );

// Prints the necessary code to initialize the surface
void printInit();
// Prints the code usef to close the surface and return 0 if there was no error
void printEnd();

void printFile(char *);

void printChemin( char* name );
void printDouble(double);
void printPPoint( double, double );
void printCPoint( double, double );
void printMove( double, double );
void printLine( double, double );
void printDraw( void );
void printTranslate(double, double);
void printRotate(double);

//Images
void pushImage( char* );
void popImage();
image topImage();

//Functions
void printFunctionStart( char* );
void printFunctionEnd( void );
void printFunctionCall( char* );
void swapBuffers( void );

// Closes the file
void closeFile();

void register_scalarVar( char* name, double value );
void register_path( char* name );
void register_pointInPath( char** point );
double get_scalarValue( char* name );
double get_pointXValue( char* name );
double get_pointYValue( char* name );
char* get_pointType( char* name );


#endif
