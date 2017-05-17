/*********************************************
*
* @Arxiu: classe.c 
* @Finalitat: Codi dedicat a la implementacio de funcions sobre Classe
* @Autor/s: Àlex Cordón Vila
* @Data:19-5-2013 
*
*********************************************/ 
//Propia
#include "classe.h"
/********************************* 
* @Nom: CLASSE_lecturaFitxer                                                                                               
* @Finalitat: Llegeix el fitxer de classes i retorna la informació llegida 
* @Arguments: In: *f, *nClasses                      
*             Out: *f,*nClasses                                                                 
* @Retorn: Retorna pastClasse de tipus Classe*                                
**********************************/  
Classe* CLASSE_lecturaFitxer( FILE *f, int *nClasses ){
	int nNumClasses;
	int i = 0;
	Classe *pastClasse;
	fscanf( f, "%d" , &nNumClasses ); 
	pastClasse = (Classe*)malloc( sizeof(Classe) * nNumClasses); 
	//Prelectura
	fscanf( f, "%s", pastClasse[i].cNom );
	fscanf( f, "%d", &pastClasse[i].nAtac ); 
	fscanf( f, "%d", &pastClasse[i].nDefensa );
	fscanf( f, "%d", &pastClasse[i].nVida ); 
	for( i = 1; i < nNumClasses; i++ ){
		fscanf( f, "%s", pastClasse[i].cNom ); 
		fscanf( f, "%d", &pastClasse[i].nAtac );    
		fscanf( f, "%d", &pastClasse[i].nDefensa);  
		fscanf( f, "%d", &pastClasse[i].nVida);  
	}
	//Retorna el nombre de classes llegides dins al fitxer
	*nClasses = nNumClasses;
	return pastClasse;
}
