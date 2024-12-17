#include "semantic.h"
FILE * out;
ts TABLE_SYMB;

int main(void){
    out = stdout;
    ast * p1 = CreerFeuilleNB(45);
    ast * p2 = CreerFeuilleNB(70);
    /*ast * p3 = CreerFeuilleNB(26);
    ast * p4 = CreerNoeudOP('%', p1, p2);
    ast * p5 = CreerNoeudOP('+', p3, p4);
    */
    ast * p6 = CreerFeuilleID("toto");
    ast * p7 = CreerNoeudOP('+', p1, p2);
    ast * p8 = CreerNoeudAFFECT("toto", p7);
    ast * p9 = CreerNoeudTQ(p6, p1);
    
    semantic(p9);
    PrintAst(p9);

    codegenINIT();
    codegen(p9);
    printf("Codelen = %d", p9->codelen);

    return 0;
}