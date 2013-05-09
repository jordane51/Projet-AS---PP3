#ifndef _GENERATOR_H_
#define _GENERATOR_H_


int openFile();

void printInit();

void printFile(char *);

void printDouble(double);
void printPPoint( double, double );
void printCPoint( double, double );
void printMove( double, double );
void printLine( double, double );
void printEnd();
void closeFile();

void register_scalarVar( char* name, double value );
  double get_scalarValue( char* name );

#endif
