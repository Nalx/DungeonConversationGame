/*******************************************
*
* @Arxiu: Logica.c
* @Finalitat: Implementacións de funcions i procediments del modul de logica
* @Autor/s: Alex Cordon Vila
* @Data:19/5/2013
*
********************************************/
//Propia
#include "logica.h"
/********************************* 
* @Nom: LOGICA_CallMenu                                                                                             
* @Finalitat: Permet mostrar i fer interactiu el primer menú del programa                                               
* @Arguments: In: *nOp,*pastClasse,pastEnemic,nNumClasse,nNumEnemics                       
*             Out: *nOp,*pastClasse                                                               
* @Retorn: No hi ha retorn, és void                                   
**********************************/  
void LOGICA_CallMenu ( int *nOp, Classe *pastClasse, Enemic *pastEnemic, int nNumClasse, int nNumEnemics){
	//Hi guardem la info. per a un jugador 
	Hero stPlayer; 
	//Flag per controlar la sortida (case 3)
	int nSortir = 0;
	//Variable per gestionar el "tornar a mostrar el menu principal"
	int nOp2 = 0;
	//Variable de control d'errors
	int nError = 0;
	//Mostrem el menu al inici de programa 
	do{
		clrscr();
		fflushnou();
		gotoxy ( 39, 9 );
		printf (" __________________________________ \n");
		gotoxy ( 39, 10 );
		printf ("|       -- Menu Principal --       | \n");
		gotoxy ( 39, 11 );
		printf ("|__________________________________|\n");
		gotoxy ( 39, 12 );
		printf ("|  1-Crear personatge nou          |\n");
		gotoxy ( 39, 13 );
		printf ("|  2-Carregar personatge           |\n");
		gotoxy ( 39, 14 );
		printf ("|  3-Sortir                        |\n");
		gotoxy ( 39, 15 );
		printf ("|__________________________________| \n");
		gotoxy ( 39, 16 );
		printf (" -Opcio? :   ");
		fflushnou();
 		nSortir = 0;
		scanf ( "%d", nOp );
		switch ( *nOp ){
			case 1:
				stPlayer = HERO_heroCreation ( pastClasse, nNumClasse, stPlayer );
				LOGICA_heroMenu( &nOp2, stPlayer, pastEnemic, nNumEnemics );
			break;
			case 2:
				stPlayer = HERO_loadHero ( pastClasse, nNumClasse, stPlayer, &nError);
				fflushnou();
				getchar();
				if( nError == 0 ){
					LOGICA_heroMenu( &nOp2, stPlayer, pastEnemic, nNumEnemics );
				}
			break;
			case 3:
				clrscr();
				gotoxy ( 39, 9 ); 
				printf ("Fins aviat...! t'estarem esperant... \n");
				nSortir = 1;
			break;
			default:
				clrscr();
				gotoxy ( 39, 9 );
				printf( "Opció incorrecte.\n" );
				gotoxy ( 39, 10 );
				printf("Prem ENTER per continuar:");
				fflushnou();
				getchar();
			break;
		}
	}while( nSortir == 0 );
}
/********************************* 
* @Nom: LOGICA_heroMenu                                                                                              
* @Finalitat: Permet mostrar i fer interactiu el segon menú del programa:                                               
* @Arguments: In: *nOp,stPlayer,*pastEnemic,nNumEnemics                          
*             Out: *nOp,*pastEnemic                                                               
* @Retorn: No hi ha retorn, és void                                   
**********************************/  
void LOGICA_heroMenu( int *nOp, Hero stPlayer, Enemic *pastEnemic, int nNumEnemics ){
	int GoToMenu = 0;
	do{
		clrscr();
		fflushnou();
		gotoxy ( 39, 9 );
		printf ("       *** MENU DE PERSONATGE ***        ");
		gotoxy ( 39, 10 );
		printf (" _____________________________________");
		gotoxy ( 39, 11 );
		printf ("|  1-Anar d'aventura                  |");
		gotoxy ( 39, 12 );
		printf ("|  2-Veure informacio del personatge  |");  
		gotoxy ( 39, 13 );
		printf ("|  3-Guardar personatge               |");
		gotoxy ( 39, 14 );
		printf ("|  4-Tornar al menu principal         |"); 
		gotoxy ( 39 ,15 );
		printf ("|_____________________________________| "); 
		gotoxy ( 39, 16 );
		printf (" -Opcio? :   ");
		scanf ( "%d", nOp ); 
		switch ( *nOp ){
			case 1:
				getchar();
				stPlayer = LOGICA_iniciaAventura( pastEnemic, nNumEnemics, stPlayer);
			break;
			case 2:
				getchar();
				HERO_heroInfo( stPlayer );
			break;
			case 3:
				getchar();
				HERO_guardarHeroi( stPlayer );
			
			break;
			case 4:
				GoToMenu = 1;
			break;
			default:
				clrscr();  
				gotoxy ( 39, 9 ); 
				printf( "Opció incorrecte.\n" );
				gotoxy ( 39, 10 ); 
				printf("Prem ENTER per continuar:"); 
				fflushnou();
				getchar();
			break;
		
		}
	}while( GoToMenu == 0 );
}
/********************************* 
* @Nom: LOGICA_iniciaAventura                                                                                     
* @Finalitat:Inicia el sistema de selecció d'enemics, la fase de realització, la fase de generació i la fi de l'aventura
* @Arguments: In:*pastEnemic, nNumEnemics,stPlayer                         
*             Out: *pastEnemic                                                                 
* @Retorn: Retorna stJugador per poder guardar la informació despres de les lluites                                   
**********************************/  
Hero LOGICA_iniciaAventura( Enemic *pastEnemic, int nNumEnemics, Hero stPlayer){ 
	Hero stJugador;
	//Hi guardem la cua creada per l'usuari
	Cua pCuaEnemics;
	//Experiencia del jugador al guanyar tots els enemic de la cua:
	int nExpTotal = 0;
	//Fase de Generacio (Retorna la cua creada per l'usuari)
	pCuaEnemics = LOGICA_faseGeneracio( pastEnemic, nNumEnemics );  
	//Generem la sequencia de combats
	nExpTotal = LOGICA_faseRealitzacio( &pCuaEnemics, stPlayer );
	//Assignem totes les puntuacións del jugador (EXP,VIDA,ATAC,NIVELL/S,DEFENSA)
	LOGICA_fiAventura( nExpTotal, &stPlayer );
	stJugador = stPlayer;
	//Destruim tota la memoria creada per generar la cua
	CUA_destrueix( pCuaEnemics );
	return stJugador;
}
/********************************* 
* @Nom: LOGICA_fiAventura                                                                                              
* @Finalitat: Assigna les puntuacions corresponents a tots els camps del jugador (EXP,VIDA,ATAC,NIVELL/S,DEFENSA) 
* @Arguments: In: nExp,*stPlayer                         
*             Out: *stPlayer                                                                 
* @Retorn: No hi ha retorn, es void                                   
**********************************/  
void LOGICA_fiAventura( int nExp, Hero *stPlayer ){
	int nNivells = 0;
	int i = 1;
	int nNivellsAux = 0;
	//Suma de l'experiència 
	(*stPlayer).nXp = (*stPlayer).nXp + nExp;
	//Augment de nivell (si la divisio entera entre l'experiencia i 1000 és igual o major a 1 hi ha augment de Lvl)
	nNivells = (*stPlayer).nXp / 1000;
	//Nivell a augmentar+nivell actual:
	nNivellsAux = nNivells + (*stPlayer).nLvl;
	//Augmentem les caracteristiques de l'heroi
	(*stPlayer).nXp = (*stPlayer).nXp - (nNivells*1000);
	(*stPlayer).nAr = (*stPlayer).nAr + (nNivells*10);
	(*stPlayer).nDr = (*stPlayer).nDr + (nNivells*5);
	(*stPlayer).nHp = (*stPlayer).nHp + (nNivells*50);
	//Augmentem el camp nivell de l'heroi
	if( nNivells >= 1 ){
		while( (*stPlayer).nLvl < nNivellsAux ){
			((*stPlayer).nLvl)=((*stPlayer).nLvl)+1;
			printf("%s ha pujat de nivell, nivell actual %d!\n", (*stPlayer).cNom, (*stPlayer).nLvl );
			i++;
		}
	}
	printf("Prem ENTER per continuar...\n");
	fflushnou();
	getchar();
}
/********************************* 
* @Nom: LOGICA_faseRealitzacio                                                                                           
* @Finalitat: Genera tot el sistema de lluites i ho mostra per pantalla.La funcio retorna l'experiencia acumulada.
* @Arguments: In: *pCuaEnemics, stPlayer                        
*             Out: *pCuaEnemics                                                                
* @Retorn: Retorna l'enter nExperiencia per poder guardar l'experiència guanyada al final dels enfrontaments      
**********************************/   
int LOGICA_faseRealitzacio( Cua *pCuaEnemics, Hero stPlayer ){
	//Variable de retorn
	int nExperiencia = 0;
	//Acomulador d'experiencia de l'enemic
	int nExpAux = 0;
	//vida auxiliar per al combat (inicialment a 1 per evitar la condicio del while al primer cop)
	int nVida = 1;
	//Flag per controlar si s'ha omplert o no la cadena amb enemics
	int nCadenaOk=0;
	//Declaracio de la variable de tipus Enemic per guardar-hi el primer de la cua
	Enemic Enemic;  
	//Atura la sequencia de combats al quedar la cua buida o al morir l'heroi
	while( !CUA_buida(*pCuaEnemics) && nVida > 0){
		//Posem a 1 el flag per saber que la cua és plena
		nCadenaOk = 1;
		//Cada vegada li asignem la vida maxima inicial
		nVida = stPlayer.nHp;
		//Guardem el primer enemic de la cua cada vegada que iterem al "while" general
		Enemic = CUA_primer(*pCuaEnemics);
		clrscr();
		printf("Combat entre %s i %s \n", stPlayer.cNom, Enemic.cNom);
		printf("Prem ENTER per continuar:\n\n");  
		fflushnou();
		getchar();
		do{	
			//Calculs per l'atac de l'heroi (Dau i atac)
			LOGICA_atacaHeroi( stPlayer, &Enemic);
			//Calculs per l'atac de l'enemic (Dau i atac)
			LOGICA_atacaEnemic( stPlayer, &Enemic, &nVida);
			printf("\nPrem ENTER per continuar.\n"); 
			printf("---------------------------------------------\n");
			fflushnou(); 
			getchar();
			//Missatges de control al usuari quan el seu heroi ha mort o be ha guanyat
			if(Enemic.nVida <= 0){
				//Sumem l'experiencia guanyada a la que ja te l'heroi si la cua és buida i nVida>0
				nExpAux = nExpAux+Enemic.nExperiencia;
				if(CUA_buida(*pCuaEnemics) == 0){
					nExperiencia = nExpAux;
				}
				printf("%s ha guanyat el combat!\n", stPlayer.cNom);
				printf("prem ENTER per continuar.\n"); 
				fflushnou();
				getchar();
			}
			if(nVida <= 0){ 
				printf("%s ha mort!\n",stPlayer.cNom);
				printf("prem ENTER per continuar.\n");
				fflushnou();
				getchar();
			}
		
		}while(nVida > 0 && Enemic.nVida > 0);
		//Un cop mort l'enemic el desencuem per generar un nou enemic contra qui lluitar
		CUA_desencua( pCuaEnemics );
	}
	//Missatge d'error al no haver escollit cap enemic
	if( nCadenaOk == 0 ){
		printf("No has escollit cap enemic!\n");
		printf("prem ENTER per continuar.\n");
		fflushnou(); 
		getchar();
	}
	printf("%s ha guanyat %d d'experiència i ara te %d d'experiencia.\n", stPlayer.cNom, nExperiencia, stPlayer.nXp + nExperiencia); 
	return nExperiencia;
}
/********************************* 
* @Nom: LOGICA_atacaHeroi                                                                                            
* @Finalitat: En funció del valor de dau escull si l'heroi falla, si fa un atac critic o un atac normal
* @Arguments: In: atacant,*defensor                          
*             Out: *defensor                                                                
* @Retorn: No hi ha retorn, és void                  
**********************************/  
void LOGICA_atacaHeroi( Hero atacant, Enemic *defensor){
	//Variables per operar amb el valor dels daus. inicialment a 0 i es retorna info amb LOGICA_dau();
	int nDau = 0;
	int nMal = 0;
	//Calcul del valor de la tirada d'un dau de 20 cares
	nDau = LOGICA_dau();  
	printf("%s ataca i...(%d) ", atacant.cNom, nDau);
	switch ( nDau ){
		case 1:
			printf("FALLA!\n");
			printf("Vida de %s es de %d", (*defensor).cNom, (*defensor).nVida);
		break;
		case 20:
			printf("ATAC CRITIC!\n");
			nMal = ( 2 * (atacant.nAr)) - ((*defensor).nDefensa);
			if(nMal < 0){
				nMal = 0;
			}
			(*defensor).nVida = ((*defensor).nVida) - nMal;
			//Si la vida és inferior a zero la mantenim a zero per mostrar-la per pantalla
			if ((*defensor).nVida < 0){
				(*defensor).nVida = 0;
			}
				printf("Fa %d de mal a %s\n", nMal, (*defensor).cNom);
				printf("Vida de %s es de %d\n",(*defensor).cNom, (*defensor).nVida);
			
		break;
		default:
			printf("ATAC NORMAL!\n");
			nMal = (atacant.nAr) - ((*defensor).nDefensa);
			if(nMal < 0){
				nMal = 0;
			}
			(*defensor).nVida = (*defensor).nVida - nMal; 
			if ((*defensor).nVida < 0){
				(*defensor).nVida = 0;
			}
			printf("Fa %d de mal a %s\n", nMal, (*defensor).cNom);
			printf("Vida de %s es de %d\n", (*defensor).cNom, (*defensor).nVida);
		break;
	}
}
/********************************* 
* @Nom: LOGICA_atacaEnemic                                                                                              
* @Finalitat: En funció del valor de dau escull si l'enemic falla, fa un atac critic o un atac normal 
* @Arguments: In: defensor,*atacant ,*nVida                        
*             Out: *atacant,*nVida                                                              
* @Retorn: No hi ha retorn, és void           
**********************************/  
void LOGICA_atacaEnemic( Hero defensor, Enemic *atacant, int *nVida){
	int nDau = 0;
	int nMal = 0; 
	nDau = LOGICA_dau();  
	printf("\n%s ataca i...(%d) ", (*atacant).cNom, nDau);
	switch ( nDau ){
		case 1: 
			printf("FALLA!\n");
			printf("Vida de %s es de %d\n", defensor.cNom, *nVida); 
		break; 
		case 20:
			printf("ATAC CRITIC!\n");
			nMal = (2 * ((*atacant).nAtac)) - (defensor.nDr);
			if(nMal < 0){
				nMal = 0;
			}
			*nVida = *nVida - nMal;
			if (*nVida < 0){
				*nVida = 0;
			}
			printf( "Fa %d de mal a %s\n", nMal, defensor.cNom); 
			printf("Vida de %s es de %d\n", defensor.cNom, *nVida); 
		break;
		default:
			printf("ATAC NORMAL!\n");
			nMal = ((*atacant).nAtac) - (defensor.nDr);
			if(nMal < 0){                                                                                     
				nMal = 0;                                                                                                 
			}
			*nVida = *nVida - nMal;
			if (*nVida < 0){ 
				*nVida = 0;
			}
			printf("Fa %d de mal a %s\n",nMal,defensor.cNom); 
			printf("Vida de %s es de %d\n",defensor.cNom,*nVida);
		break;
	}
}
/********************************* 
* @Nom: LOGICA_dau                                                                                               
* @Finalitat: Calcular un valor aleatori entre 1 i 20         
* @Arguments: In: -                         
*             Out: -                                                               
* @Retorn: Retorna l'enter nDau amb un valor entre 1 i 20                                  
**********************************/  
int LOGICA_dau(){
	int nDau = 0;
        //Calcul del valor aleatori acotat entre 1 i 20
	nDau = ( rand() % 20 ) + 1;
	return nDau;
}
/********************************* 
* @Nom: LOGICA_faseGeneracio                                                                                              
* @Finalitat: Mostrar tots els enemics fins que l'usuari entra -1
* @Arguments: In: *pastEnemic, nNumEnemics                          
*             Out: *pastEnemic                                                                
* @Retorn: Retorna pCuaEnemics on hi ha la info dels enemics escollits pel jugador                                   
**********************************/  
Cua LOGICA_faseGeneracio( Enemic *pastEnemic, int nNumEnemics){ 
	//Comptador pel bucle for
	int i = 0;                                   
	//Comptador per mostrar per pantalla el nom dels enemics
	int y = 0;
	//Comptadors per mostrar la llista d'enemics
	int j = 0;
	int k = 0;
	int x = 0;
	//Array de tipus NomEnemic per guardar tots els noms escollits
	NomEnemic astNoms[1000];
	//Numero entrat per teclat.
	int nUserNum = 0; 
	//Declaració de la variable de tipus cua
	Cua pCuaEnemics; 
	pCuaEnemics = CUA_crea();
	clrscr();
	do{ 
		gotoxy( 0, 0 );
		printf("Enemics disponibles:                         ");
		gotoxy( 10 , 2 ); 
		printf("Nom");
		gotoxy( 30, 2 );
		printf("Atac");
		gotoxy( 40, 2 ); 
		printf("Defensa");
		gotoxy( 50, 2 ); 
		printf("Vida");
		gotoxy( 60, 2 );
		printf("Experiencia"); 
		gotoxy( 100, 2 );
		gotoxy( 85, 2 ); 
		printf("Enemics en cua:"); 
		//Mostrem els enemics que el jugador va escollint
		k = 0;
		while( k <= j ){
			gotoxy( 85+x, 3+k );
			printf("%s", astNoms[k-1].nom);
			k++;
		}
		y = 0;
		//Mostrem la llista d'informació per a cada nom en columnes
		for( i = 0; i < nNumEnemics; i++ ){
			gotoxy( 0, 3 + y );
			printf( "%d-", i + 1 );
			gotoxy( 10, 3 + y );
			printf( "%s", pastEnemic[i].cNom ); 
			gotoxy( 30, 3 + y ); 
			printf( "%d", pastEnemic[i].nAtac ); 
			gotoxy( 40, 3 + y );
			printf( "%d",pastEnemic[i].nDefensa );
			gotoxy( 50, 3 + y );
			printf( "%d", pastEnemic[i].nVida ); 
			gotoxy( 60, 3 + y ); 
			printf( "%d", pastEnemic[i].nExperiencia ); 
			y++; 
		}
		gotoxy( 0, 3 + y );
		printf("Introdueix el numero de l'enemic a seleccionar o -1 per finalitzar:\n");
		scanf( "%d", &nUserNum ); 
		clrscr();
		if( nUserNum < -1 || nUserNum > nNumEnemics || nUserNum == 0 ){   
			clrscr();
			printf("No hi ha cap enemic amb aquest numero.\n"); 
			printf("Prem ENTER per continuar: ");
			fflushnou();
			getchar();
		} 
		else{
			//Afegim a la cua l'enemic que escull el jugador  
			if( nUserNum != -1 ){  
				CUA_encua( &pCuaEnemics, pastEnemic[nUserNum-1] );  
				strcpy( astNoms[j].nom, pastEnemic[nUserNum-1].cNom );
				j++;
			}
		}
		
	}while( nUserNum != -1 ); 
	return pCuaEnemics;
}
