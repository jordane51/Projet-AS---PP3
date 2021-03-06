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
  char points[2][256];
}
 
%token SEP
%token SEP_PLUS
%token CYCLE
%token IMAGE
%token TRANSLATE
%token ROTATE
%token FUNCTION
%token <dbl>NUMBER
%token DRAW
%token FILL
%token SCALAR
%token ID
%token <str>NAME
%type <dbl>expr
%type <points>point
%type <dbl>scalar
%left '+'
%left '*'
%left '/'
%left '-'
%%
  
s : s e
  |
  ;

e : DRAW suite {setDrawMode(DRAW_MODE_STROKE); printDraw();}
  | DRAW IMAGE '{' e '}' {}
  | FILL suite {setDrawMode(DRAW_MODE_FILL); printDraw();}
  | DRAW NAME {popImage();printDraw();}
  | NAME '(' ')' {}
  | var
  | IMAGE NAME { pushImage($2); } '=' IMAGE '{' e '}' { }
  | FUNCTION NAME{} '{' e '}' {}
  | ROTATE {setTransformMode(TRANSFORM_MODE_ROTATE);} NUMBER {settAngle($3);} suite
  | TRANSLATE {setTransformMode(TRANSFORM_MODE_ROTATE);} NUMBER NUMBER {setTx($3); setTy($4);} suite
  ;



scalar : NAME { $$ = get_scalarValue( $1 ); }
       | NUMBER { $$ = $1; }
       | {$$ =  1;}
       ;

var : ID NAME '=' NUMBER {register_scalarVar( $2, $4 );}
    | ID NAME '=' '(' expr ',' expr ')' {register_CPointVar( $2, $5, $7 );}
    | ID NAME '=' path {register_path( $2 );}
    ;

path : path SEP point {register_pointInPath( $3 );}
     | point {register_pointInPath( $1 );}
     ;

suite : suite SEP point {printf("test\n");}
      | suite SEP '+' {setPointMode(POINT_MODE_ADD);} point
      | NAME { printChemin( $1 ); }
      | suite SEP CYCLE {printCycle();}
      | point
      ;


point : scalar'(' expr ',' expr ')' { printCPoint( $3 * $1, $5 * $1); sprintf( $$[0], "%g", $3); sprintf( $$[1], "%g", $5);}
      | scalar'(' expr ':' expr ')' { printPPoint( $3 * $1, $5 * $1 ); sprintf( $$[0], "%g", $3); sprintf( $$[1], "%g", $5);}
      | NAME {if(!strcmp( get_pointType( $1 ), "Cpoint" )){printCPoint( get_pointXValue( $1 ), get_pointYValue( $1 ));} else {printPPoint( get_pointXValue( $1 ), get_pointYValue( $1 ));}}
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
