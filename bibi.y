%{
#include <stdio.h>
#include <stdlib.h>
#include <cairo.h>
#include <cairo-pdf.h>
#include "draw.h"
  cairo_surface_t * pdf_surface ;
  cairo_t *cr ;
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

i : suite {DrawPoints();}
  ;


suite : suite "--" point
      | point
      ;

point : '(' expr ',' expr ')' {AddPoint( $2, $4 );}
      | 
      ; 

expr : '(' expr ')' 
     | NUMBER {$$ = $1;}
     | expr '+' expr { $$ = $1 + $3;}
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
     FILE* f = fopen("test.c", "w");
     PrintMain(f);
     
     

     // Intialize the queue
     Init();

     if( yyparse() == 0 ) 
	  printf( "Syntaxe correcte\n" );
     else
	  printf( "Syntaxe incorrecte\n" );
}

void PrintMain(FILE* f)
{
     fprintf(f, "#include \"draw.h\"\n" \
	     "#include <cairo.h>\n" \
	     "#include <cairo-pdf.h>" \
	     "\nint main()\n{\n");
}

