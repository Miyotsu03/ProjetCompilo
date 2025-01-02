#ifndef AST_H
#define AST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define  TXT_RED    "\x1b[31m"
#define  TXT_GREEN  "\x1b[32m"
#define  TXT_BLUE   "\x1b[34m"
#define  TXT_BOLD   "\x1b[1m"
#define  TXT_NULL   "\x1b[0m"

#define INIT_NOEUD(p)   if ((p = malloc(sizeof(ast))) == NULL)	\
    ErrorAst("echec allocation mémoire");			\
  else {							\
    p->type = 0;								\
    p->type_str[0] = '\0';					\
    p->id[0] = '\0';							\
    p->valeur = 0;								\
    p->ope = 0;								\
	  p->noeud[0] = NULL;						\
    p->noeud[1] = NULL;          \
    p->noeud[2] = NULL;				\
    p->codelen = 0; \
  }								\

enum {AST_NB = 256, AST_OP, AST_ID,AST_INST, AST_LINST, AST_AFFECT, AST_TQ, AST_PRINT, AST_SI} ;

typedef struct ast{
  int  type;
  char type_str[32];
  char id[32];
  int valeur;
  int ope;
  struct ast *noeud[3];
  int codelen;
} ast;




ast * CreerFeuilleNB(int nb);
ast * CreerFeuilleID(char * s);
ast * CreerNoeudOP(int ope, ast *p1, ast *p2);
ast * CreerNoeudLINST(ast * p1, ast * p2);
ast * CreerNoeudAFFECT(char * id, ast * p1);
ast * CreerNoeudTQ(ast * exp, ast * linst);
ast * CreerNoeudSI (ast * p1, ast * p2, ast * p3);
ast * CreerNoeudPRINT( ast * p1);


void FreeAst(ast * p);

void PrintAst(ast * p);
void ErrorAst(const char * errmsg);


#endif
