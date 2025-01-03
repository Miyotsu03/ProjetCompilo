#include "semantic.h"

void semantic (ast * p){
    switch(p->type){
        case AST_NB:
            p->codelen = 1 + NB_INST_EMPILER;
            printf("AST_NB: codelen = %d\n", p->codelen);
        break;
        case AST_ID:
            p->codelen = 1 + NB_INST_EMPILER;
            printf("AST_ID: codelen = %d\n", p->codelen);
        break;
        case AST_OP:
            semantic(p->noeud[0]);
            if (p->ope != '~')
                semantic(p->noeud[1]);
            
            switch (p->ope){
                case '+':
                    p->codelen = p->noeud[0]->codelen +
                        NB_INST_EMPILER + NB_INST_DEPILER + 4;
                    printf("AST_OP: codelen = %d\n", p->codelen);        
                break;
                case '-':
                    p->codelen = p->noeud[0]->codelen + 
                        p->noeud[1]->codelen +
                        NB_INST_EMPILER + 2 * NB_INST_DEPILER + 2;
                    printf("AST_OP: codelen = %d\n", p->codelen);        
                break;
                case '*':
                    p->codelen = p->noeud[0]->codelen + 
                        p->noeud[1]->codelen +
                        NB_INST_EMPILER + 2 * NB_INST_DEPILER + 2;
                    printf("AST_OP: codelen = %d\n", p->codelen);        
                break;
                case '/':
                    p->codelen = p->noeud[0]->codelen + 
                        p->noeud[1]->codelen +
                        NB_INST_EMPILER + 2 * NB_INST_DEPILER + 2;
                    printf("AST_OP '/': codelen = %d\n", p->codelen);        
                break;
                case '%':
                    p->codelen = p->noeud[0]->codelen + 
                        p->noeud[1]->codelen +
                        NB_INST_EMPILER + 2 * NB_INST_DEPILER + 2;
                    printf("AST_OP 'mod': codelen = %d\n", p->codelen);        
                break;
                case '>':
                    p->codelen = p->noeud[0]->codelen + 
                        p->noeud[1]->codelen +
                        NB_INST_EMPILER + 2 * NB_INST_DEPILER + 9;
                    printf("AST_OP '>': codelen = %d\n", p->codelen);        
                break;
                case '<':
                    p->codelen = p->noeud[0]->codelen + 
                        p->noeud[1]->codelen +
                        NB_INST_EMPILER + 2 * NB_INST_DEPILER + 9;
                    printf("AST_OP '<': codelen = %d\n", p->codelen);        
                break;
                case '!':
                    p->codelen = p->noeud[0]->codelen + 
                        p->noeud[1]->codelen +
                        NB_INST_EMPILER + 2 * NB_INST_DEPILER + 8;
                    printf("AST_OP '!': codelen = %d\n", p->codelen);        
                break;
                case 'p':
                    p->codelen = p->noeud[0]->codelen + 
                        p->noeud[1]->codelen +
                        NB_INST_EMPILER + 2 * NB_INST_DEPILER + 8;
                    printf("AST_OP '<=': codelen = %d\n", p->codelen);        
                break;
                case '~':
                    p->codelen = p->noeud[0]->codelen + 
                        NB_INST_EMPILER + 2 * NB_INST_DEPILER + 5;
                    printf("AST_OP '~': codelen = %d\n", p->codelen);        
                break;
            }
        break;
        case AST_LINST:
            semantic(p->noeud[0]);
            if(p->noeud[1] != NULL){
                semantic(p->noeud[1]);
                p->codelen = p->noeud[0]->codelen + 
                    p->noeud[1]->codelen;
            }
            else p->codelen = p->noeud[0]->codelen;
            printf("AST_LINST: codelen = %d\n", p->codelen);
        break;
        case AST_AFFECT:
            semantic(p->noeud[0]);
            p->codelen = p->noeud[0]->codelen + NB_INST_DEPILER + 1;
            printf("AST_AFFECT: codelen = %d\n", p->codelen);
        break;
        case AST_TQ:
            semantic(p->noeud[0]);
            semantic(p->noeud[1]);
            p->codelen = p->noeud[0]->codelen + 
                p->noeud[1]->codelen + 3;
            printf("AST_TQ: codelen = %d\n", p->codelen);
        break;
        case AST_PRINT:
            p->codelen = 3;
    }
}