#ifndef _GENERATOR_H_
#define _GENERATOR_H_

enum{
    DRAW_MODE_NONE, //"Default" value
    DRAW_MODE_STROKE,
    DRAW_MODE_FILL,
    POINT_MODE_NONE,//"Default" value
    POINT_MODE_ADD
};

struct point{
    double x;
    double y;
};

typedef struct point *point;

// Used to open the generated text file (draw.gen.c)
int openFile();

// Sets the current drawing mode to whatever is specified
void setDrawMode( int );

// Sets the current point type
void setPointMode( int );

// Prints the necessary code to initialize the surface
void printInit();
// Prints the code usef to close the surface and return 0 if there was no error
void printEnd();

void printFile(char *);

void printDouble(double);
void printPPoint( double, double );
void printCPoint( double, double );
void printMove( double, double );
void printLine( double, double );
void printEnd();
void printDraw( void );

// Closes the file
void closeFile();

void register_scalarVar( char* name, double value );
double get_scalarValue( char* name );
double get_pointXValue( char* name );
double get_pointYValue( char* name );
char* get_pointType( char* name );

#endif
