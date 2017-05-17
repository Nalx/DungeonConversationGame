/*******************************************
*
* @Arxiu: main.c
* @Finalitat: procediment principal de la practica 3
* @Autor: Alex Cordon Vila  
* @Data:19/5/2013
*
********************************************/ 
//Sistema
#include <stdio.h>
//Poropies
#include "logica.h"
/********************************* 
* @Nom: main                                                                                              
* @Finalitat: Es el procediment principal del programa
* @Arguments: In: argc= , argv[]=                       
*             Out: -                                                                
* @Retorn: es retorna un enter=0                                 
**********************************/    
int main( int argc, char* argv[] ){
	//punter a un array dinamic de tipus Enemic
	Enemic *pastEnemic;
	//Punter a un array dinamic de tipus Classe
	Classe *pastClasse; 
	//Enter on hi guardem el nombre de classes que hi ha al fitxer
	int nNumClasse = 0;
	//Enter on hi guardem el nombre d'enemics que hi ha al fitxer
	int nNumEnemics = 0;
	//Variables de fitxers per a classes(f),enemics(g),personatge(h).
	FILE *f, *g;
	//Variable per controlar la selecció de la opció al menu
	int nOp = 0;
	//Control d'error de format al pas d'arguments del main
	srand( time( NULL ) ); 
	if ( argc != 3 ){
		printf( "Error de nombre d'arguments.\n" );
		printf( "Format d'exemple: ./practica3 fitxer_classes fitxer_enemics\n" );
	}else{
		//Obrim el primer fitxer 
		f = fopen( argv[1], "r" );	
		if ( f == NULL ){
			printf ( "Error! El ficher 1 no existeix.\n" );
		}else{
			//Obrim el segon fitxer
			g = fopen( argv[2], "r" );
			if ( g == NULL ) {
				printf ( "Error! El ficher 2 no existeix.\n" );
				fclose( f );
			}else{
				//Lectura de fitxer d'enemics
				pastEnemic = ENEMIC_lecturaFitxer( g, &nNumEnemics );
				//Lectura de fitxer de classes
				pastClasse = CLASSE_lecturaFitxer( f, &nNumClasse ); 
				//El 3 és la opció de "sortir" del menu 
				do{ 
					LOGICA_CallMenu( &nOp, pastClasse, pastEnemic, nNumClasse, nNumEnemics );
				}while( nOp != 3 );
			}
		}
	}
	return 0;
}

