%{
  #include <stdio.h>
  #include <ctype.h>
  #include <string.h>
  
  #include "ast.h"
  #include "ts.h"
  #include "codegen.h"
  #include "semantic.h"
    
  extern int yylex();
  static void print_file_error(char * s, char *errmsg);

  struct ast * ARBRE_ABSTRAIT = NULL;
  ts TABLE_SYMB;
  FILE * out;

  void yyerror(const char * s);

  char srcname[64];
  char exename[64] = "a.out";
  FILE * exefile;
%}



%union{
  int nb;
  char id[32];
  struct ast * arbre;
 };

%type <arbre> EXP
%type <arbre> INST
%type <arbre> LINST
%type <arbre> AFFECT
%type <arbre> STRUCT_TQ
%type <arbre> STRUCT_SI
%type <arbre> STRUCT_PRINT


%define parse.error detailed
%locations

%token <nb> NB
%token <id> ID 
%token FLECHE "<-"
%token VAR
%token MAIN DEBUT FIN TQ FAIRE FTQ SI SINON ALORS FSI PRINT
%left '='
%left '<' '>' '!'
%left '+' '-'
%left '*' '/' '%'
%right "<-"
%start PROGRAMME

%%

PROGRAMME:
	MAIN '(' ')'
  DECLA
	DEBUT
		LINST	        {ARBRE_ABSTRAIT = $6;}
	FIN
;

EXP : NB 			    {$$ = CreerFeuilleNB($1); }
| ID				      {$$ = CreerFeuilleID($1); }
| EXP '+' EXP			{$$ = CreerNoeudOP('+', $1, $3); }
| EXP '-' EXP			{$$ = CreerNoeudOP('-', $1, $3); }
| EXP '*' EXP			{$$ = CreerNoeudOP('*', $1, $3); }
| EXP '/' EXP			{$$ = CreerNoeudOP('/', $1, $3); }
| EXP '%' EXP			{$$ = CreerNoeudOP('%', $1, $3); }
| '(' EXP ')'			{$$ = $2; }
| EXP '<' EXP			{$$ = CreerNoeudOP('<', $1, $3); }
| EXP '=' EXP			{$$ = CreerNoeudOP('=', $1, $3); }
| EXP '>' EXP			{$$ = CreerNoeudOP('>', $1, $3); }
| EXP '!' EXP			{$$ = CreerNoeudOP('!', $1, $3); }
;

DECLA : %empty
| VAR ID ';' DECLA  {ajouter_id(TABLE_SYMB, $2); }
;

AFFECT : ID "<-" EXP ';'	{$$ = CreerNoeudAFFECT($1, $3); }
| ID "<-" AFFECT ';'      	{$$ = CreerNoeudAFFECT($1, $3); }
;

INST : EXP ';'    		{$$ = $1; }
| AFFECT          		{$$ = $1; }
| STRUCT_TQ           {$$ = $1; }
| STRUCT_SI           {$$ = $1; }
| STRUCT_PRINT        {$$ = $1; }
;

LINST : INST    		{$$ = CreerNoeudLINST($1, NULL); }
| INST LINST    		{$$ = CreerNoeudLINST($1, $2); }
;

STRUCT_TQ : TQ EXP FAIRE
              LINST
            FTQ       		{$$ = CreerNoeudTQ($2, $4); }
;

STRUCT_SI : SI EXP ALORS
              LINST
            SINON
              LINST
            FSI       		{$$ = CreerNoeudSI($2, $4, $6); }
;

STRUCT_PRINT : PRINT '(' EXP ')'';'  {$$ = CreerNoeudPRINT($3);}
;


%%

int main( int argc, char * argv[] ) {
  extern FILE *yyin;
  
  if (argc > 1){
    strcpy(srcname, argv[1]);
    if ( (yyin = fopen(srcname,"r"))==NULL ){
      char errmsg[256];
      sprintf(errmsg,"fichier \x1b[1m\x1b[33m' %s '\x1b[0m introuvable",srcname);
      print_file_error(argv[0],errmsg);
      exit(1);
    }
  }  else {
    print_file_error(argv[0],"aucun fichier en entree");
    exit(1);
  }
  if (argc == 3){
    strcpy(exename, argv[2]);
  }
  exefile = fopen(exename,"w");
  INIT_TS(TABLE_SYMB);
  yyparse();
  Print_ts(TABLE_SYMB);
  PrintAst(ARBRE_ABSTRAIT);
  out = stdout;
  semantic(ARBRE_ABSTRAIT);
  codegenINIT();
  codegen(ARBRE_ABSTRAIT);
  fclose(yyin);
}



static void print_file_error(char * prog, char *errmsg){
  fprintf(stderr,
	  "\x1b[1m%s:\x1b[0m \x1b[31m\x1b[1merreur fatale:\x1b[0m %s\nechec de la compilation\n",
	  prog, errmsg);
}

void yyerror(const char * s)
{
  fprintf(stderr, "\x1b[1m%s:%d:%d:\x1b[0m %s\n", srcname, yylloc.first_line, yylloc.first_column, s);
  exit(0);
}