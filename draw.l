%{

#include "draw.tab.h"

  //extern int number;
%}
%option noyywrap
%%
"--"          {return SEP;}
"draw"        {return DRAW;}
"fill"        {return FILL;}
"cycle"       {return CYCLE;}
"scalar"      {return ID;}
"point"       {return ID;}
"path"      {return ID;}
"("           {return '(';}
")"           {return ')';}
[[:digit:]]+  {yylval.dbl = atof(yytext); return NUMBER;}
"."           {return '.';}
","           {return ',';}
":"           {return ':';}
"+"           {return '+';}
"*"           {return '*';}
"/"           {return '/';}
"-"           {return '-';}
"=" 	      {return '=';}
"image"       {return IMAGE;}
"function"    {return FUNCTION;}
"{"           {return '{';}
"}"           {return '}';}
[[:alnum:]]+  {sprintf(yylval.str, "%s", yytext);return NAME;}

