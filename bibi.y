%{
#include <stdio.h>
#include <stdlib.h>
#include <cairo.h>
#include <cairo-pdf.h>
  cairo_surface_t * pdf_surface ;
  cairo_t *cr ;
  /*struct point2d_t{
    double x;
    double y;
  };*/
  //typedef struct point2d_t *Point2D;
  //Point2D listPoints[2];
  int hasStarted = 0;
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

i : point suite
  ;


suite : "--" point suite
      |
      ;

point : '(' expr ',' expr ')'
      | 
      ; 

expr : '(' expr ')' 
     | NUMBER
     | expr '+' expr
     | 
     ;

%%
int yyerror(char *s){
  fprintf(stderr,"%s\n",s);
  exit(1);
}
int main(){
  pdf_surface = cairo_pdf_surface_create ( "ex1.pdf" ,50 ,50 );
  cr = cairo_create ( pdf_surface );
  listPoints = (struct point2d_t*)malloc(sizeof(struct point2d_t) * 500);
  if( yyparse() == 0 ) 
    printf( "Syntaxe correcte\n" );
  else
    printf( "Syntaxe incorrecte\n" );
}

/*

i : p suite

p : '(' expr ',' expr ')'

suite : -- p suite
      |
      ;
