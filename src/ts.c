#include "ts.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
int chercher_id(ts table_symb, char *id)
    retourne la case ou se trouve id
    -1 si absent
*/
int chercher_id(ts tablesymb, char *id){
    for(int i=0; i<LEN_TAB; i++){
        if (strcmp(tablesymb[i].id, id) == 0)
            return tablesymb[i].adresse;
    }

    return -1;
}

/*int ajouter_id(ts tablesymb, char *id)
    ajoute l'id a la table de symboles si absent
    et renvoie la case en question
    -1 si table pleine

*/
int ajouter_id(ts tablesymb, char *id){
    int res = chercher_id(tablesymb, id);
    if(res >= 0)
        return res;
    else{
        for(int i=0; i<LEN_TAB; i++)
            if (strcmp(tablesymb[i].id, "") == 0){
                struct tabsymb tmp;
                strcpy(tmp.id, id);
                tmp.adresse = i;
                tablesymb[i] = tmp;
                return tmp.adresse;
            }  
    }
    return -1;
}

void Print_ts(ts tablesymb){
    for(int i=0; i<LEN_TAB; i++){
        if(strcmp(tablesymb[i].id, "") == 0)
            break;
        printf("%s |", tablesymb[i].id);
    }
    printf("\n");
}

void ErrorTS(const char * errmsg){
  fprintf(stderr,"[TS error] %s\n",errmsg);
  exit(1);
}