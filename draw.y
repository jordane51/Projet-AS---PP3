%{
#include <stdio.h>
#include <stdlib.h>
#include "generator.h"
%}
%union{
  double dbl;
  int integer;
 }

%token <dbl>NUMBER
%token DRAW
%token FILL
%type <dbl> expr
%type <dbl> point
%%

e : DRAW i 
  | FILL i
  |
  ;

i : suite
  ;


suite : suite "--" point
      | point
      ;

point : '(' expr ',' expr ')'
      ; 

expr : '(' expr ')' 
     | NUMBER
     | expr '+' expr 
     ;

%%
int yyerror(char *s){
  exit(1);
}
int main(){
    printInit();
     if( yyparse() == 0 ) 
	  printf( "Syntaxe correcte\n" );
     else
	  printf( "Syntaxe incorrecte\n" );
}
