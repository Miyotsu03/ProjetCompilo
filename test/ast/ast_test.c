#include "ast.h"

int main(void){/*
  ast * p1 = CreerFeuilleNB(1);
  ast * p2 = CreerFeuilleNB(2);
  ast * p3 = CreerNoeudOP('+', p1, p2);
    
  PrintAst(p3);

  FreeAst(p3);
*/
	ast * p4 = CreerFeuilleID("toto");
	PrintAst(p4);
	FreeAst(p4);
  return 0;
}


