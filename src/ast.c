#include "ast.h"

static void PrintNB(ast *p, char * indent);
static void PrintOP(ast *p, char * indent);
static void PrintID(ast *p, char * indent);
static void PrintLINST(ast *p, char * indent);
static void PrintAFFECT(ast *p, char * indent);
static void PrintTQ(ast *p, char * indent);


ast * CreerFeuilleNB(int nb){
  ast * p;
  INIT_NOEUD(p);
  p->type = AST_NB;
  strcpy(p->type_str,"NB");
  p->valeur = nb;
  return p;
}

ast * CreerNoeudOP(int ope, ast *p1, ast *p2){
	ast * p;
	INIT_NOEUD(p);
	p->type = AST_OP;
  char operateur[4] = "OP  ";     
  operateur[3] = ope;             //Afficher l operateur correspondant
	strcpy(p->type_str, operateur);
	p->ope = ope;
	p->noeud[0] = p1;
	p->noeud[1] = p2;
	return p;
}

ast * CreerNoeudLINST(ast * p1, ast * p2){
  ast * p;
  INIT_NOEUD(p);
  p->type = AST_LINST;
  strcpy(p->type_str, "LINST");
  p->noeud[0] = p1;
  p->noeud[1] = p2;
  return p;
}

ast * CreerNoeudAFFECT(char * identifiant, ast * p1){
  ast * p;
  INIT_NOEUD(p);
  p->type = AST_AFFECT;
  strcpy(p->type_str, "<-");
  strcpy(p->id, identifiant);
  p->noeud[0] = p1;
  return p;
}

ast * CreerNoeudTQ(ast * exp, ast * linst){
  ast * p;
  INIT_NOEUD(p);
  p->type = AST_TQ;
  strcpy(p->type_str, "TQ");
  p->noeud[0] = exp;
  p->noeud[1] = linst;
  return p;
}

ast * CreerFeuilleID(char * s){
	ast * p;
	INIT_NOEUD(p);
	p->type = AST_ID;
	strcpy(p->type_str, "ID");
	strcpy(p->id, s);
	return p;
}

void FreeAst(ast * p){
  if (p == NULL) return;
  FreeAst(p->noeud[0]);
  FreeAst(p->noeud[1]);
  free(p);
}

int profondeur = 0;
void PrintAst(ast * p){
  if (p == NULL) return;
  char indent[32] ="";	//Indentation pour l'affichage de l'arbre
  int i;
  for(i=0; i < profondeur; i++)
  	indent[i] = '\t';
  indent[i] = '\0';
  switch(p->type){
  case AST_NB:
    PrintNB(p,indent);
    break;
  case AST_OP:
  	PrintOP(p,indent);
    break;
  case AST_ID:
  	PrintID(p, indent);
  	break;
  case AST_LINST:
  	PrintLINST(p, indent);
  	break;
  case AST_AFFECT:
  	PrintAFFECT(p, indent);
  	break;
  case AST_TQ:
    PrintTQ(p, indent);
  break;
  default:
    fprintf(stderr,"[Erreur] type <%d>: %s non reconnu\n",p->type,p->type_str);
    break;
  }
}

void ErrorAst(const char * errmsg){
  fprintf(stderr,"[AST error] %s\n",errmsg);
  exit(1);
}

static void PrintNB(ast *p, char *indent){
  printf("%s" TXT_BOLD TXT_BLUE "Noeud:  " TXT_NULL "%p\n",indent, p);
  printf("%s" TXT_BOLD "Type:   " TXT_NULL "%s\n",indent, p->type_str);
  printf("%s" TXT_BOLD "Valeur: " TXT_NULL "%d\n",indent, p->valeur);
}

static void PrintOP(ast *p, char * indent){
  printf("%s" TXT_BOLD TXT_BLUE "Noeud:  " TXT_NULL "%p\n",indent, p);
  printf("%s" TXT_BOLD "Type:   " TXT_NULL "%s\n",indent, p->type_str);
  profondeur++;
  PrintAst(p->noeud[0]);
  PrintAst(p->noeud[1]);
  profondeur--;
}

static void PrintID(ast *p, char * indent){
	printf("%s" TXT_BOLD TXT_BLUE "Noeud:  " TXT_NULL "%p\n",indent, p);
	printf("%s" TXT_BOLD "Type:   " TXT_NULL "%s\n",indent, p->type_str);
	printf("%s" TXT_BOLD "ID:   " TXT_NULL "%s\n",indent, p->id);
	
	
}

static void PrintLINST(ast *p, char * indent){
  printf("%s" TXT_BOLD TXT_BLUE "Noeud:  " TXT_NULL "%p\n", indent, p);
  printf("%s" TXT_BOLD "Type:   " TXT_NULL "%s\n", indent, p->type_str);
  
  profondeur++;
  if (p->noeud[0] != NULL){
    PrintAst(p->noeud[0]);
  }
  
  if (p->noeud[1] != NULL){
    PrintAst(p->noeud[1]);
  }
  profondeur--;
}

static void PrintAFFECT(ast *p, char * indent){
  printf("%s" TXT_BOLD TXT_BLUE "Noeud:  " TXT_NULL "%p\n",indent, p);
  printf("%s" TXT_BOLD "Type:   " TXT_NULL "%s\n",indent, p->type_str);
  
  printf("%s" TXT_BOLD "ID:   " TXT_NULL "%s\n",indent, p->id);
  profondeur++;
  PrintAst(p->noeud[0]);
  profondeur--;
}

static void PrintTQ(ast *p, char * indent){
  printf("%s" TXT_BOLD TXT_BLUE "Noeud:  " TXT_NULL "%p\n",indent, p);
  printf("%s" TXT_BOLD "Type:   " TXT_NULL "%s\n",indent, p->type_str);
  printf("%s" TXT_BOLD "Condition de boucle:   " TXT_NULL "%p\n",indent, p->noeud[0]);
  printf("%s" TXT_BOLD "Instructions:   " TXT_NULL "%p\n",indent, p->noeud[1]);
  
  profondeur++;
  PrintAst(p->noeud[0]);
  PrintAst(p->noeud[1]);
  profondeur--;
}
