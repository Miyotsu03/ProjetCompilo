#include "ts.h"
#include <stdio.h>

int main(void){
    ts tablesymb;
    ajouter_id(tablesymb, "toto");
    ajouter_id(tablesymb, "titi");
    //ajouter_id(tablesymb, "tata");
    ajouter_id(tablesymb, "tutu");
    Print_ts(tablesymb);
    printf("chercher toto : %d", chercher_id(tablesymb, "tutu"));
    return 0;
}