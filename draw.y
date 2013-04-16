%{
#include <stdio.h>
#include <stdlib.h>
#include "generator.h"
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

e : DRAW i {printFile("cairo_move_to(cr, ");}
  | FILL i
  |
  ;

i : suite
  ;

suite : suite SEP point
      | point
      ;

point : '(' expr ',' expr ')' {$$ = $2;}
      ; 

expr : '(' expr ')' {$$ = $2;}
     | NUMBER {printDouble($1);}
     | expr '+' expr
     ;

%%
int yyerror(char *s){
  exit(1);
}
int main(){
    openFile();
    printInit();
     if( yyparse() == 0 ) 
	  printf( "Syntaxe correcte\n" );
     else
	  printf( "Syntaxe incorrecte\n" );
    printFile("\n}");
    closeFile();
}
