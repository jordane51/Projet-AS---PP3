%{
#include <stdio.h>
#include <stdlib.h>
#include "generator.h"
#include "list.h"


%}
%union{
  double dbl;
  int integer;
  int scalar;
  char str[256];
}
 
%token SEP
%token SEP_PLUS
%token <dbl>NUMBER
%token DRAW
%token FILL
%token SCALAR
%token ID
%token <str>NAME
%type <dbl>expr
%type <dbl>point
%type <dbl>scalar
%left '+'
%%

e : DRAW i 
  | FILL i
  | var e
  ;

i : suite
  ;

scalar : NAME { $$ = get_scalarValue( $1 ); }
       | NUMBER { $$ = $1; }
       | {$$ =  1;}
       ;

var : ID NAME '=' NUMBER {register_scalarVar( $2, $4 );}
       ;

suite : suite SEP point
      | suite SEP_PLUS point
      | point
      ;


point : scalar'(' expr ',' expr ')' { printCPoint( $3 * $1, $5 * $1); }
      | scalar'(' expr ':' expr ')' { printPPoint( $3 * $1, $5 * $1 ); }
      ; 

expr : '(' expr ')' { $$ = $2;}
     | NUMBER {$$ = $1;}
     | expr '+' expr {$$ = $1 + $3;}
     | expr '/' expr {$$ = $1 / $3;}
     | expr '*' expr {$$ = $1 * $3;}
     | expr '-' expr {$$ = $1 - $3;}
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
	  printEnd();
	  closeFile();
     }
}
