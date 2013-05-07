%{

#include "draw.tab.h"

  //extern int number;
%}
%option noyywrap
%%
"--"          {return SEP;}
"draw"        {return DRAW;}
"fill"        {return FILL;}
"("           {return '(';}
")"           {return ')';}
[[:digit:]]+  {yylval.dbl = atof(yytext); return NUMBER;}
"."           {return '.';}
","           {return ',';}
\+            {return '+';}
\*            {return '*';}
\/            {return '/';}

