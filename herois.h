/********************************************                                                                          
*  	@Arxiu: herois.h                                                                                                  
*	@Finalitat: Procediments/funcions i tipus sobre herois                                                             
*	@Autor: Àlex Cordón Vila                                                       
*	@Data:4/4/2013                                                                                                
********************************************/ 
#ifndef _HEROIS_H
#define _HEROIS_H 
//Sistema
#include <conio.h>
#include <stdio.h>
#include <string.h>
//Propies
#include "classe.h"
#include "enemics.h"
typedef struct {
	//Nom
	char cNom[100];
	Classe Classes;
	//Nivell
	int nLvl;
	//Experiencia
	int nXp;
	//Atac
	int nAr;
	//Mal
	int nDr;
	//Vida
	int nHp;
}Hero;
//funcio per al menu 1:Permet crear el personatge
Hero HERO_heroCreation (Classe *pastClasse, int nNumClasse, Hero stPlayer);
//funcio per al menu 1:Permet carregar un personatge guardat
Hero HERO_loadHero(Classe *pastClasse, int nNumClasse, Hero stPlayer, int *nError);
//procediment per al menu 2: Permet guardar un personatge
void HERO_guardarHeroi(Hero stPlayer);
//Hero HEORIS_destrueix();
void HERO_heroInfo(Hero stPlayer);
#endif
