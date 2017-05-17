/*******************************************
*
* @Arxiu: classe.h
* @Finalitat: fitxer .h amb funcions i tipus sobre Classe
* @Autor/s: Àlex Cordón Vila i Sergio Gonzalez Mendoza
* @Data:4-4-2013
*
********************************************/
#ifndef _CLASSES_H
#define _CLASSES_H
#include <stdio.h>
#include <stdlib.h> 
typedef struct{
	char cNom[50];
	int nAtac;
	int nDefensa;
	int nVida;
}Classe;
//LLegeix el fitxer de classes que es passa des del main
Classe* CLASSE_lecturaFitxer ( FILE *f, int *nClasse ); 
#endif
