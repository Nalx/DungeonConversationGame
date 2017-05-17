/********************************************
* @Arxiu: enemics.h
* @Finalitat: Procediments/funcions i tipus sobre enemics  
* @Autor/s: Àlex Cordón Vila
* @Data:4/4/2013
*
********************************************/
#ifndef _ENEMICS_H
#define _ENEMICS_H
//Sistema  
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
	char cNom[100];
	int nAtac;
	int nDefensa;
	int nVida;
	int nExperiencia;
}Enemic;
//Capçalera de la lectura del fitxer d'enemics
Enemic* ENEMIC_lecturaFitxer( FILE *g, int *nNumEnemics );
#endif
