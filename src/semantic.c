#include "semantic.h"

void semantic (ast * p){
    switch(p->type){
        case AST_NB:
            p->codelen = 2;
        break;
        case AST_ID:
            p->codelen = 2;
        break;
        case AST_OP:
            semantic(p->noeud[0]);
            semantic(p->noeud[1]);
            p->codelen = p->noeud[0]->codelen + 
                p->noeud[1]->codelen +
                2 * NB_INST_EMPILER + NB_INST_DEPILER + 2;
        break;
        case AST_AFFECT:
            semantic(p->noeud[0]);
            p->codelen = p->noeud[0]->codelen + 3;
        break;
    }
}