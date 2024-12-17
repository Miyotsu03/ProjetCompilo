#include "codegen.h"
FILE * out;
ts TABLE_SYMB;

int main(void){
    out = stdout;
    ast * p1 = CreerFeuilleNB(12);
    //ast * p2 = CreerFeuilleID("toto");
    //ast * p3 = CreerNoeudOP('%', p1, p2);
    //codegen(p1);
    //codegen(p2);
    //codegen(p3);

    
    ajouter_id(TABLE_SYMB, "toto");
    ajouter_id(TABLE_SYMB, "tutu");
    ajouter_id(TABLE_SYMB, "titi");
    ast * p4 = CreerNoeudAFFECT("toto", p1);
    codegenINIT();
    codegen(p4);
/*
    ajouter_id(TABSYMB, "toto");
    printf("tabsymb[0] : %s\n", TABSYMB[0].id );
*/    return 0;
}