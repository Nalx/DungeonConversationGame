/********************************************
*	@Arxiu:logica.h                                                                                                      
*	@Finalitat: Procediments/funcions de logica                                                                
*   @Autor: Àlex Cordón Vila                                                            
*	@Data:4/4/2013                                                                                               
********************************************/                                                                   
#ifndef _LOGICA_H                                                                                            
#define _LOGICA_H
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include "herois.h"
#include "classe.h"
#include "enemics.h"
#include "cua.h"
//Estructura definida per poder guardar els noms dels enemics que el jugador va escollint
typedef struct{
	char nom[100];
}NomEnemic;
//MENU 1: Permet escollir entre 2 opcions
void LOGICA_CallMenu ( int *nOp, Classe *pastClasse, Enemic *pastEnemic, int nNumClasse, int nNumEnemics); 
//OPCIO 1: Permet iniciar una partida  
Hero LOGICA_iniciaAventura( Enemic *pastEnemic, int nNumEnemics, Hero stPlayer);
//Fase 1: GENERACIO
Cua LOGICA_faseGeneracio( Enemic *pastEnemic, int nNumEnemics); 
//FASE 2: REALITZACIO
int LOGICA_faseRealitzacio( Cua *pCuaEnemics, Hero stPlayer);
//Fase 3: FINALITZACIO
void LOGICA_fiAventura( int nExpTotal, Hero *stPlayer);
//Procediment per calcular el dany que fa l'heroi a l'enemic
void LOGICA_atacaHeroi( Hero atacant, Enemic *defensor);
//procediment per calcular el dany que fa l'enemic sobre l'heroi
void LOGICA_atacaEnemic( Hero defensor, Enemic *atacant, int *nVida);
//simulació d'una tirada d'un dau de 20 cares
int LOGICA_dau();
//MENU 2: Permet escollir d'entre 4 opcions
void LOGICA_heroMenu( int *nOp, Hero stPlayer, Enemic *pastEnemic, int nNumEnemics); 
#endif   
