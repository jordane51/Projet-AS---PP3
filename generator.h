#ifndef _GENERATOR_H_
#define _GENERATOR_H_

enum{
    DRAW_MODE_NONE = 0,
    DRAW_MODE_STROKE = 1,
    DRAW_MODE_FILL = 2
};

// Used to open the generated text file (draw.gen.c)
int openFile();

// Sets the current drawing mode to whatever is specified
void setDrawMode( int );

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
void printDraw( void );

// Closes the file
void closeFile();

#endif
