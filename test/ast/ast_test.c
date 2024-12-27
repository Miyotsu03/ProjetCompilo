#include "ast.h"

int main(void){
  ast * p1 = CreerFeuilleNB(1);
  /*ast * p2 = CreerFeuilleNB(2);
  ast * p3 = CreerNoeudOP('+', p1, p2);
    
  PrintAst(p3);

  FreeAst(p3);

	ast * p4 = CreerFeuilleID("toto");
*/
  ast * p5 = CreerFeuilleNB(30);
	ast * p6 = CreerNoeudOP('<', p1, p5);
  PrintAst(p6);
	FreeAst(p6);
  return 0;
}


