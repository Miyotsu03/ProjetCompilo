PROJET COMPILATEUR ALGO - RAM
2024 - 2025
GOMIS Julien
FRASQUET Alex


Ce README permet la compréhension du projet. Il explique ses fonctionnalités,
l'utilité de chaque ficihier, et la manière de le compiler/éxecuter.



COMPILATION ET EXECUTION
pour compiler ce programme, il suffit dans un premier d'utiliser la commande "make" sous Linux.
Ensuite, il faut utiliser la ligne de commande suivante:
	./bin/arc <chemin_programme_test>
 (Il y a quelques exemples dans le dossier "test" de base)



Tout d'abord, il faut définir le langage reconnu par le compilateur. Il est implicitement défini dans le fichier src/parser.y, 
mais explicitement ça donne comme suit:

PROGRAMME est l'axiome
Mots clés : MAIN DEBUT FIN TQ FAIRE FTQ SI ALORS SINON FSI PRINT
le separateur d'instructions est ';'

PROGRAMME:
	MAIN '(' ')'
  DECLA
	DEBUT
		LINST	        
	FIN


EXP : NB 			    
| ID				      
| EXP '+' EXP			
| EXP '-' EXP			
| EXP '*' EXP			
| EXP '/' EXP			
| EXP '%' EXP			
| '(' EXP ')'			
| EXP '<' EXP			
| EXP '=' EXP			
| EXP '>' EXP			
| EXP "!=" EXP		
| EXP "<=" EXP    
| EXP ">=" EXP    


DECLA : %empty
| VAR ID ';' DECLA  


AFFECT : ID "<-" EXP ';'	
| ID "<-" AFFECT ';'      	


INST : EXP ';'    		
| AFFECT          		
| STRUCT_TQ          
| STRUCT_SI           
| STRUCT_PRINT        


LINST : INST    		
| INST LINST    		


STRUCT_TQ : TQ EXP FAIRE
              LINST
            FTQ     


STRUCT_SI : SI EXP ALORS
              LINST
            SINON
              LINST
            FSI       		


STRUCT_PRINT : PRINT '(' EXP ')'';'  

GESTION DE LA MEMOIRE
Les registres 1 à 8 reservés.
Les registre suivants sont alloués comme suit:
  - les n suivants correspondent aux identifiants de la table de symbole (n étant le # d'identifiants de la table)
  - ensuite arrivent les différentes variables du programme



ANALYSE LEXICALE
L'analyse lexicale est gérée par le fichier src/lexer.lex qui permet de reconnaître les unités lexicales de notre langage
(NB, ID, MOTS CLES, OP)


ANALYSE SYNTAXIQUE
L'analyse syntaxique est gérée par les fichiers src/parser.y et src/ast.c
Cela permet dans un premier temps de reconnaître les différentes productions du langage pour ensuite en créer l'arbre syntaxique associé


GENERATION DE CODE
La génération de code se retrouve dans le fichier src/codegen.c et permet de générer chaque bout de code lors du parcours de l'AST en profondeur inversé


ANALYSE SEMANTIQUE
L'analyse semantique concerne le fichier src/semantic.c et permet seulement de calculer la taille des bouts de code générés


CARACTERISTSIQUES DU COMPILATEUR

Gestion de l'analyse lexicale jusqu'à la génération de code des éléments suivants:
    - Nombres (NB)
    - Identificateur (ID)
    - Affectations (<-)
    - Listes d'instruction (LINST)
    - Boucle Tant Que (TQ)
    - Structure Conditionnelle SI ALORS SINON
    - L'instruction PRINT

