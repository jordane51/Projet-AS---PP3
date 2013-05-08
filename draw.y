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
%token SEP_PLUS
%token <dbl>NUMBER
%token DRAW
%token FILL
%type <dbl>expr
%type <dbl>point
%left '+'
%left '*'
%left '/'
%left '-'
%%

s : s e
  |
  ;

e : DRAW i {setDrawMode(DRAW_MODE_STROKE); printDraw();}
| FILL i {setDrawMode(DRAW_MODE_FILL); printDraw();}
  ;

i : suite
  ;

suite : suite SEP point
      | suite SEP_PLUS point
      | point
      ;

/*point : '(' expr ',' expr ')' { if( !wasMoved ){ printMove( $2, $4 );  wasMoved = 1;} 
                                else{ printLine( $2, $4 );} $$ = $2;}*/
point : '(' expr ',' expr ')' { printCPoint( $2, $4 ); }
      | '(' expr ':' expr ')' { printPPoint( $2, $4 ); }
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
