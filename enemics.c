/******************************************* 
*
* @Arxiu: enemics.c
* @Finalitat: Implementacions de les funcions/procediments del modul enemics
* @Autor/s: Àlex Cordón Vila
* @Data:19/5/2013 
*
********************************************/
//Propia
#include "enemics.h" 
/********************************* 
* @Nom: ENEMIC_lecturaFitxer                                                                                              
* @Finalitat: Llegeix el fitxer d'enemics i passa la informacio al programa 
* @Arguments: In: *g = variable del fitxer, *nNUmEnemics = nombre enter de la quantitat d'enemics                         
*             Out: nNumEnemics = Es retorna per referencia                                                                 
* @Retorn: Es retorna una variable de tipus Enemic* amb la info. dels enemics del fitxer
**********************************/  
Enemic* ENEMIC_lecturaFitxer( FILE *g, int *nNumEnemics ){ 
	int i = 0;
	char KK = ' ';
	Enemic *pastEnemic;
	//Lectura del nombre d'enemics que hi ha dins el fitxer
	fscanf (g, "%d", nNumEnemics);
	fscanf (g, "%c", &KK);
	printf("NumEnemics: %d\n", *nNumEnemics);
	//Crea memoria per a nNumEnemics
	pastEnemic = (Enemic*)malloc( (sizeof(Enemic)) * (*nNumEnemics)); 
	//Bucle per poder llegir tota la info. que hi ha al fitxer
	while(i < *nNumEnemics){
		fgets(pastEnemic[i].cNom, sizeof(Enemic), g);
		pastEnemic[i].cNom[strlen(pastEnemic[i].cNom)-1] = ' ';
		fscanf(g, "%d", &pastEnemic[i].nAtac);
		fscanf (g, "%c", &KK);
		fscanf(g, "%d", &pastEnemic[i].nDefensa);
		fscanf (g, "%c", &KK);
		fscanf(g, "%d", &pastEnemic[i].nVida);
		fscanf (g, "%c", &KK);
		fscanf(g, "%d", &pastEnemic[i].nExperiencia);
		fscanf (g, "%c", &KK);
		i++;
	}
	return pastEnemic;
}
