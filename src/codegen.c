#include "codegen.h"

int PILE = __PREMIER_ADR__;
int __NUM__INST__ = 1;
extern FILE * out;
extern ts TABLE_SYMB;
static void codegenNB(ast * p);
static void codegenOP(ast * p);
static void codegenID(ast * p);
static void codegenAFFECT(ast * p);
static void codegenLINST(ast * p);
static void codegenTQ(ast * p);

void codegenINIT(){ 
    int i;
    for (i=0; strcmp(TABLE_SYMB[i].id, "") != 0; i++);
    PILE += i;
}

void codegen(ast * p){
    if(p == NULL)return;

    switch(p->type){
        case AST_NB:
            codegenNB(p);
        break;
        case AST_OP:
            codegenOP(p);
        break;
        case AST_ID:
            codegenID(p);
        break;
    case AST_AFFECT:
        codegenAFFECT(p);
    case AST_LINST:
        codegenLINST(p);
    break;
    case AST_TQ:
        codegenTQ(p);
    break;
    }
}

static void codegenNB(ast * p){
    __NUM__INST__++;
    fprintf(out, "LOAD #%d\n", p->valeur);
    EMPILER();
}

static void codegenOP(ast * p){
    codegen(p->noeud[0]);   //Generation du code des feuilles du noeud
    codegen(p->noeud[1]);

    DEPILER();      //Generation du code de l'operation
    __NUM__INST__++;
    fprintf(out, "STORE %d\n", __REG_TMP__);
    DEPILER();
    __NUM__INST__++;
    switch(p->ope){
        case '+':
            fprintf(out, "ADD %d\n", __REG_TMP__);
        break;
        case '-':
            fprintf(out, "SUB %d\n", __REG_TMP__);
        break;
        case '*':
            fprintf(out, "MUL %d\n", __REG_TMP__);
        break;
        case '/':
            fprintf(out, "DIV %d\n", __REG_TMP__);
        break;
        case '%':
            fprintf(out, "MOD %d\n", __REG_TMP__);
        break;

    }
    EMPILER();    
}

static void codegenID(ast * p){
    int adr = chercher_id(TABLE_SYMB, p->id);
    __NUM__INST__++;
    fprintf(out, "LOAD %d\n", adr + __PREMIER_ADR__);
    EMPILER()
}

static void codegenAFFECT(ast * p){
    codegen(p->noeud[0]);
    DEPILER();

    int adr = chercher_id(TABLE_SYMB, p->id);
    __NUM__INST__++;
    fprintf(out, "STORE %d\n", adr + __PREMIER_ADR__);
    EMPILER();

}

static void codegenLINST(ast * p){
    codegen(p->noeud[0]);
    codegen(p->noeud[1]);
    EMPILER();
}

static void codegenTQ(ast * p){
    int adr1 = __NUM__INST__;
    codegen(p->noeud[0]);
    __NUM__INST__++;
    fprintf(out, "JUMZ %d\n", __NUM__INST__ + p->noeud[1]->codelen + 1);
    codegen(p->noeud[1]);
    __NUM__INST__++;
    fprintf(out, "JUMP %d\n", adr1);
}