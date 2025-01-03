%{
  #include <string.h>
  #include "parser.h"

  extern void yyerror(char *);

  char errmsg[256]="";
  const char charerr[] = "\x1b[1m\x1b[31m[erreur lexicale]\x1b[0m caractère \x1b[41m%c\x1b[0m inattendu";
  
  /* MACRO défini 
   * Action executee avant chaque action semantique (meme vide)  
   * et rempli la variable Bison `yylloc` avec la position du token
   */
#define YY_USER_ACTION                                             \
  yylloc.first_line = yylloc.last_line;                            \
  yylloc.first_column = yylloc.last_column;                        \
  if (yylloc.last_line == yylineno)                                \
    yylloc.last_column += yyleng;                                  \
  else {                                                           \
    yylloc.last_line = yylineno;                                   \
    yylloc.last_column = 1;					   \
  }


  

%}
  
%option nounput
%option noinput
%option yylineno

NOMBRE         ([1-9][0-9]*|0)
LETTRE			[_a-zA-Z]
CHIFFRE			[0-9]
ID				{LETTRE}({LETTRE}|{CHIFFRE})*

%%

"MAIN"		    {return MAIN;}
"VAR"       	{return VAR;}
"DEBUT"		    {return DEBUT;}
"<-"        	{printf("Reconnu FLECHE token\n"); return FLECHE; }
"<="        	{printf("Reconnu PPE token\n"); return PPE; }
">="        	{printf("Reconnu PGE token\n"); return PGE; }
"!="        	{printf("Reconnu PGE token\n"); return DIF; }
"FIN"		      {return FIN;}
"TQ"        	{return TQ;}
"FAIRE"     	{return FAIRE;}
"FTQ"       	{return FTQ;}
"SI"     	    {return SI;}
"SINON"       {return SINON;}
"ALORS"      	{return ALORS;}
"FSI"       	{return FSI;}
"PRINT"       {return PRINT;}
[-+*/%();<=>~]	{return yytext[0];}
{NOMBRE}        {yylval.nb = atoi(yytext); return NB;}
{ID}		{ strcpy(yylval.id, yytext); return ID;}
[ \t\n]		{}
.               {           
                  sprintf(errmsg,charerr, yytext[0]);
		  yyerror(errmsg);
		  return 1;
                }

%%
 