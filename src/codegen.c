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
static void codegenPRINT(ast * p);
static void codegenSI(ast * p);



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
        break;
        case AST_LINST:
            codegenLINST(p);
        break;
        case AST_TQ:
            codegenTQ(p);
        break;
        case AST_SI:
            codegenSI(p);
        break;
        case AST_PRINT:
            codegenPRINT(p);
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
        case '>':
            fprintf(out, "SUB %d\n", __REG_TMP__);
            
            __NUM__INST__++;
            fprintf(out, "JUMZ %d\n", __NUM__INST__ + 3); // Jump si resulta = 0 
            __NUM__INST__++;
            fprintf(out, "JUML %d\n", __NUM__INST__ + 2); // Jump si resultat < 0
            
            // Cas 1 : gauche (noeud[0]) > droite (noeud[1])
            __NUM__INST__++;
            fprintf(out, "LOAD #1\n"); //return 1 si gauche > droite
            __NUM__INST__++;
            fprintf(out, "STORE %d\n", __REG_RESULT__); // Stocke le resultat (1)
            
            // Jump a la fin de la comparaison
            __NUM__INST__++;
            fprintf(out, "JUMP %d\n", __NUM__INST__ + 2); // Jump to the end

            // Cas 2 : (gauche <= droite) retourner la valeur(0)
            __NUM__INST__++;
            fprintf(out, "LOAD #0\n"); // Load false (0)
            __NUM__INST__++;
            fprintf(out, "STORE %d\n", __REG_RESULT__); // Stocke le resultat (0)
        break;
        case '<':
            fprintf(out, "SUB %d\n", __REG_TMP__);

           // Jump a la fin de la comparaison
            __NUM__INST__++;
            fprintf(out, "JUMZ %d\n", __NUM__INST__ + 3); // Jump si le resultat = 0
            __NUM__INST__++;
            fprintf(out, "JUMG %d\n", __NUM__INST__ + 2); // Jump si le resultat est > 0

            // Ici gauche (noeud[0]) < droite (noeud[1])
            __NUM__INST__++;
            fprintf(out, "LOAD #1\n"); //retourne 1 si gauche < droite
            __NUM__INST__++;
            fprintf(out, "STORE %d\n", __REG_RESULT__); // Stocke le resultat (1)

             // Jump a la fin de la comparaison
            __NUM__INST__++;
            fprintf(out, "JUMP %d\n", __NUM__INST__ + 2); // Jump to the end

            // Fin de comparaison (gauche >= droite) retourner la valeur(0)
            __NUM__INST__++;
            fprintf(out, "LOAD #0\n"); // retourne 0 car gauche >= droite 
            __NUM__INST__++;
            fprintf(out, "STORE %d\n", __REG_RESULT__); // Stocke le resultat (0)
        break;
        case 'd':
            fprintf(out, "SUB %d\n", __REG_TMP__);   // gauche - droite

            // Comparaison
            __NUM__INST__++;
            fprintf(out, "JUMZ %d\n", __NUM__INST__ + 2); // Jump si resultat = 0 (égal)

            // Ici gauche != droite
            __NUM__INST__++;
            fprintf(out, "LOAD #1\n"); // Load TRUE (1)

            __NUM__INST__++;
            fprintf(out, "STORE %d\n", __REG_RESULT__); // Stocke le resulat (1)

            // Jump à la fin de la comparaison
            __NUM__INST__++;
            fprintf(out, "JUMP %d\n", __NUM__INST__ + 1); // Jump à la fin

            // Si on jump ici, on doit load False (0)
            __NUM__INST__++;
            fprintf(out, "LOAD #0\n"); // Load false (0)

            __NUM__INST__++;
            fprintf(out, "STORE %d\n", __REG_RESULT__); // Stocke le resultat (0)

        break;
        case '=':
            fprintf(out, "SUB %d\n", __REG_TMP__);   // gauche - droite

            // Comparaison
            __NUM__INST__++;
            fprintf(out, "JUMZ %d\n", __NUM__INST__ + 2); // Jump si resultat = 0 (égal)

            // Ici gauche != droite
            __NUM__INST__++;
            fprintf(out, "LOAD #0\n"); // Load FAUX (0)

            __NUM__INST__++;
            fprintf(out, "STORE %d\n", __REG_RESULT__); // Stocke le resultat (0)

            // Jump à la fin de la comparaison
            __NUM__INST__++;
            fprintf(out, "JUMP %d\n", __NUM__INST__ + 1);

            // Si on jump ici, on doit load True (1)
            __NUM__INST__++;
            fprintf(out, "LOAD #1\n");

            __NUM__INST__++;
            fprintf(out, "STORE %d\n", __REG_RESULT__); // Stocke le resultat (1)

        break;
        case 'p':
            fprintf(out, "SUB %d\n", __REG_TMP__);

           // Jump a la fin de la comparaison
            __NUM__INST__++;
            fprintf(out, "JUMG %d\n", __NUM__INST__ + 2); // Jump si le resultat est > 0

            // Ici gauche (noeud[0]) < droite (noeud[1])
            __NUM__INST__++;
            fprintf(out, "LOAD #1\n"); //retourne 1 si gauche < droite
            __NUM__INST__++;
            fprintf(out, "STORE %d\n", __REG_RESULT__); // Stocke le resultat (1)

             // Jump a la fin de la comparaison
            __NUM__INST__++;
            fprintf(out, "JUMP %d\n", __NUM__INST__ + 2); // Jump to the end

            __NUM__INST__++;
            fprintf(out, "LOAD #0\n"); // retourne 0 car gauche > droite 
            __NUM__INST__++;
            fprintf(out, "STORE %d\n", __REG_RESULT__); // Stocke le resultat (0)
        break;
        case 'g':
            fprintf(out, "SUB %d\n", __REG_TMP__);

           // Jump a la fin de la comparaison
            __NUM__INST__++;
            fprintf(out, "JUML %d\n", __NUM__INST__ + 2); // Jump si le resultat est < 0

            // Ici gauche (noeud[0]) >= droite (noeud[1])
            __NUM__INST__++;
            fprintf(out, "LOAD #1\n"); //retourne 1 si gauche < droite
            __NUM__INST__++;
            fprintf(out, "STORE %d\n", __REG_RESULT__); // Stocke le resultat (1)

             // Jump a la fin de la comparaison
            __NUM__INST__++;
            fprintf(out, "JUMP %d\n", __NUM__INST__ + 2); // Jump to the end

            __NUM__INST__++;
            fprintf(out, "LOAD #0\n"); // retourne 0 car gauche < droite 
            __NUM__INST__++;
            fprintf(out, "STORE %d\n", __REG_RESULT__); // Stocke le resultat (0)
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
}

static void codegenLINST(ast * p){
    codegen(p->noeud[0]);
    codegen(p->noeud[1]);
}

static void codegenTQ(ast * p){
    int adr1 = __NUM__INST__;
    codegen(p->noeud[0]);
    __NUM__INST__++;
    fprintf(out, "LOAD %d\n", __REG_RESULT__); //Registre resultat de comparaisons
    __NUM__INST__++;
    fprintf(out, "JUMZ %d\n", __NUM__INST__ + p->noeud[1]->codelen + 1);
    codegen(p->noeud[1]);
    __NUM__INST__++;
    fprintf(out, "JUMP %d\n", adr1);
    __NUM__INST__++;
    fprintf(out, "NOP \n");
}

static void codegenSI(ast * p){
    codegen(p->noeud[0]);
    __NUM__INST__++;
    fprintf(out, "LOAD %d\n", __REG_RESULT__); //Registre resultat de comparaisons
    __NUM__INST__++;
    fprintf(out, "JUMZ %d\n", __NUM__INST__ + p->noeud[1]->codelen + p->noeud[2]->codelen);
    codegen(p->noeud[1]);
    __NUM__INST__++;
    fprintf(out, "JUMP %d\n", __NUM__INST__ + p->noeud[2]->codelen);
    codegen(p->noeud[2]);
    fprintf(out, "NOP\n");
}


static void codegenPRINT(ast * p){
    if (p->noeud[0]->type == AST_NB){
        __NUM__INST__++;
        fprintf(out, "LOAD %d#", p->valeur);
    }
    if (p->noeud[0]->type == AST_ID){
        int adr = chercher_id(TABLE_SYMB, p->id);
        __NUM__INST__++;
        fprintf(out, "LOAD %d\n", adr + __PREMIER_ADR__);
    }
    __NUM__INST__++;
    fprintf(out, "WRITE\n");

    __NUM__INST__++;
    fprintf(out, "NOP \n");
}

