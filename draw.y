%{
#include <stdio.h>
#include <stdlib.h>
#include "generator.h"

int wasMoved = 0;
%}
%union{
  double dbl;
  int integer;
 }
 
%token SEP
%token <dbl>NUMBER
%token DRAW
%token FILL
%type <dbl>expr
%type <dbl>point
%left '+'
%%

e : DRAW i 
  | FILL i
  |
  ;

i : suite
  ;

suite : suite SEP point
      | point
      ;

point : '(' expr ',' expr ')' { if( !wasMoved ){ printMove( $2, $4 );  wasMoved = 1;} 
                                else{ printLine( $2, $4 );} $$ = $2;}
      ; 

expr : '(' expr ')' { $$ = $2;}
     | NUMBER {$$ = $1;}
     | expr '+' expr
     ;

%%
int yyerror(char *s){
  exit(1);
}
int main(){
     int success = openFile();
     if( success ){
	  printInit();
	  if( yyparse() == 0 ) 
	       printf( "Syntaxe correcte\n" );
	  else
	       printf( "Syntaxe incorrecte\n" );
	  printFile("\n}");
	  closeFile();
     }
     fprintf( stderr, "Error : cannot open/generate draw.gen.c\n" );
}
