#ifndef CODE_H
#define CODE_H

#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "ts.h"
#define __PREMIER_ADR__ 9
#define __REG_TMP__ 1
#define __REG_RESULT__ 8



#define EMPILER(){ \
    fprintf(out, "STORE %d\n", PILE++); \
    __NUM__INST__++; \
}

#define DEPILER(){ \
    fprintf(out, "LOAD %d\n", --PILE); \
    __NUM__INST__++;    \
}



void codegenINIT();

#define NB_INST_EMPILER 1
#define NB_INST_DEPILER 1







void codegen(ast * p);

#endif