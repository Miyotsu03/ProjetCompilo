#ifndef TABSYMB_H
#define TABSYMB_H
#define LEN_TAB 128

#define INIT_TS(p)					\
    for(int i=0; i<32; i++){                 \
        strcpy(p[i].id, "");                     \
        p[i].adresse = -1;	    \
    }						\

struct tabsymb{
    char id[32];
    int adresse;
};

typedef struct tabsymb ts[LEN_TAB];

int chercher_id(ts table_symb, char *id);
int ajouter_id(ts tablesymb, char *id);

void Print_ts(ts tablesymb);
void ErrorTS(const char * errmsg);

#endif