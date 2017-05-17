/********************************************
*
* @Arxiu: herois.c
* @Finalitat: Implementacións de funcions i procediments del modul herois
* @Data: 19/5/2013
*
********************************************/
#include "herois.h"
/********************************* 
* @Nom: HERO_heroCreation                                                                                             
* @Finalitat:s'encarrega del procés de creació del personatge al primer menu 
* @Arguments: In: *pastClasse, nNumClasse, stPlayer                            
*             Out: *pastClasse                                                                
* @Retorn: Retorna stPlayer on hi ha tota la info del personatge creada pel jugador                                 
**********************************/  
Hero HERO_heroCreation (Classe *pastClasse, int nNumClasse, Hero stPlayer){
	//Variable per afegir paraules d'error als "printf"
	char cMissatge[10] = "";
	//Flag per controlar si s'ha trobat o no una classe igual a la demanada per l'usuari (trobat==1)
	int nTrobat = 0;
	//Variable per fer de comptador
	int i = 0;
	//Hi guardem la posició del gotoxy final
	int y = 13;
	//Hi guardem el nom de la classe entrat per l'usuari 
	char cNomClasse[50];
	//Variable de tipus heroi on hi guardem la informació del personatge creat  
	clrscr();
	gotoxy (39, 9);  
	printf("Benvingut al menu de creacio de personatges\n");
	gotoxy (39, 10);  
	printf("Escull un nom per al nou personatge.\n");
	gotoxy (39, 11);
	printf("Nom: ");
	fflushnou();
	gets(stPlayer.cNom);
	gotoxy (39, 12);  
	printf("Classes disponibles:");
	gotoxy (39, 13); 
	printf("Nom");
	gotoxy (55, 13);
	printf("Atac");
	gotoxy (65, 13); 
	printf("Defensa");
	gotoxy (75, 13); 
	printf("Vida"); 
	//Utilitzem els seguents bucles per pintar el menu en forma de columnes
	for (i=0; i<nNumClasse; i++){
		y++;
		gotoxy (39, 14 + i);  
		printf("%s", pastClasse[i].cNom);
		gotoxy (55, 14 + i);
		printf("%d", pastClasse[i].nAtac);
		gotoxy (65, 14 + i);
		printf("%d", pastClasse[i].nDefensa);
		gotoxy (75, 14 + i);
		printf("%d", pastClasse[i].nVida);
	}
	
	//incrementem la y per pintar despres del menu a y=14
	y = y + 1;
	//Control per si no hi han classes coincidents amb la de l'usuari
	do{
		i = 0;
		gotoxy (39, y + 3);
		printf("Escull una %s classe per el teu personatge:", cMissatge);
		gotoxy (39, y + 4); 
		gets(cNomClasse);
		while(i <= nNumClasse && nTrobat == 0){
			if(strcmp(cNomClasse, pastClasse[i].cNom) == 0){
				nTrobat = 1;
				clrscr();
				gotoxy (39, 9);
				printf("El personatge %s s'ha creat correctament", stPlayer.cNom);
				gotoxy (39, 10);
				printf("Prem ENTER per continuar: ");
				getchar();
			}
			i++;
		
		}
		if(nTrobat == 0){
			strcpy(cMissatge, "nova");
			y++;
		}
	}while(nTrobat == 0);
	//Inicialitzem totes les dades del personatge en funció de la classe
	stPlayer.nLvl = 0;
	stPlayer.nXp = 0;
	//La posició i-1 és l'equivalent a la classe coincident amb l'escollida per l'usuari
	stPlayer.nAr = pastClasse[i-1].nAtac;
	stPlayer.nDr = pastClasse[i-1].nDefensa; 
	stPlayer.nHp = pastClasse[i-1].nVida;
	strcpy(stPlayer.Classes.cNom, cNomClasse); 
	stPlayer.Classes.nAtac = pastClasse[i-1].nAtac;
	stPlayer.Classes.nDefensa = pastClasse[i-1].nDefensa; 
	stPlayer.Classes.nVida = pastClasse[i-1].nVida;
	return stPlayer;
}
/********************************* 
* @Nom: HERO_loadHero                                                                                               
* @Finalitat: Permet carregar les dades d'un jugador guardat en una partida anterior
* @Arguments: In: *pastClasse, nNumClasse, stPlayer, *nError                            
*             Out: *pastClasse,*nError                                                                
* @Retorn: Retorna stPlayer on hi ha tota la info del personatge donada pel fitxer                                    
**********************************/  
Hero HERO_loadHero(Classe *pastClasse, int nNumClasse, Hero stPlayer, int *nError){
	FILE *f;
	int i = 0;
	int nTrobat = 0;
	char kk;
	char cHname[50];
	clrscr();
	gotoxy (39, 9);
	printf("Introdueix el nom del fitxer de personatge a carregar:");
	scanf("%s", cHname);
	f=fopen(cHname, "r");
	//Comprovacions per saber si el fitxer existeix
	if ( f == NULL ){ 
		clrscr();
		gotoxy (39, 9); 
		printf("Error! Aquest personatge no existeix!\n");
		*nError = 1;
		gotoxy (39, 10);
		printf("Prem ENTER per continuar: ");
		fflushnou();
	}
	else{
		//agafem l'informació que necessitem del fitxer
		fgets( stPlayer.cNom, sizeof(Hero), f );
		fscanf(f, "%s", stPlayer.Classes.cNom);
		fscanf( f, "%c", &kk); 
		fscanf( f, "%d", &stPlayer.nLvl );
		//Saltem en \n
		fscanf( f, "%c", &kk);
		fscanf( f, "%d", &stPlayer.nXp );
		//fem les operacions per determinar atac, defensa i vida del personatge
		do {
			if (strcmp(stPlayer.Classes.cNom, pastClasse[i].cNom) == 0 ) {
				nTrobat = 1;
				stPlayer.nAr = (pastClasse[i].nAtac) + (stPlayer.nLvl * 50);
				stPlayer.nDr = (pastClasse[i].nDefensa) + (stPlayer.nLvl * 10);
				stPlayer.nHp = (pastClasse[i].nVida) + (stPlayer.nLvl * 5);
			}
			i++;
		}while (( i <= nNumClasse )&&( nTrobat == 0 ));
		
		if ( nTrobat == 0 ) {
			clrscr();
			gotoxy(39, 9); 
			//Misstage en el cas de que la classe del personatge no existeixi
			printf ("Error! El personatge no s'ha carregat correctament degut a que no s'ha trobat la seva classe!");
			gotoxy(39, 10);
			printf("Prem ENTER per continuar: "); 
			getchar();
		}
		else{
			clrscr();
			gotoxy(39, 9);
			printf ("El personatge ha sigut carregat correctament.");
			gotoxy(39, 10); 
			printf("Prem ENTER per continuar: ");
			getchar();
		}
	
	fclose( f ); 
	}
	//Treiem el \n final de stPlayer.cNom
	stPlayer.cNom[strlen(stPlayer.cNom)-1] = '\0';
	return stPlayer;
}
/********************************* 
* @Nom: HERO_heroInfo                                                                                             
* @Finalitat: Mostra per pantalla tota la informació referent al personatge.        
* @Arguments: In: stPlayer                         
*             Out:-                                                        
* @Retorn: No hi ha retorn, és void                           
**********************************/  
void HERO_heroInfo(Hero stPlayer){
	clrscr();
	gotoxy (39, 9);
	printf("Informacio del personatge:");
	gotoxy (39, 10);
	printf("__________________________");
	gotoxy (39, 11);
	printf("Nom:            %s", stPlayer.cNom);
	gotoxy (39, 12);
	printf("Classe:         %s", stPlayer.Classes.cNom);
	gotoxy (39, 13);
	printf("Nivell:         %d", stPlayer.nLvl);
	gotoxy (39, 14);
	printf("Experiencia:    %d",stPlayer.nXp);
	gotoxy (39, 15); 
	printf("Atac:           %d",stPlayer.nAr); 
	gotoxy (39, 16);
	printf("Defensa:        %d",stPlayer.nDr); 
	gotoxy (39, 17);
	printf("Vida:           %d",stPlayer.nHp);  
	gotoxy (39, 20);
	printf("Prem ENTER per tornar al menu de personatge. "); 
	getchar();

}
/********************************* 
* @Nom: HERO_guardarHeroi                                                                                               
* @Finalitat: Permet guardar totes les dades del personatge de la partida dins d'un fitxer
* @Arguments: In: stPlayer                        
*             Out: -                                                                 
* @Retorn: No hi ha retorn, és void                                   
**********************************/  
void HERO_guardarHeroi(Hero stPlayer){
	FILE *h;
	char cNomAux[100];
	//Afegim el .txt al nom del fitxer
	strcpy(cNomAux, stPlayer.cNom); 
	strcat(stPlayer.cNom, ".txt");
	clrscr();
	//Obertura de fitxer per escriptura
	h=fopen(stPlayer.cNom, "w"); 
	if(fopen == NULL){
		gotoxy (39, 9);
		printf("Error de fitxer\n");
	}else{
		//Escriptura de tota la informacio necesaria 
		fprintf(h, "%s", cNomAux);
		fprintf(h, "%c", '\n');
		fprintf(h, "%s", stPlayer.Classes.cNom);
		fprintf(h, "%c", '\n'); 
		fprintf(h, "%d", stPlayer.nLvl);
		fprintf(h, "%c", '\n'); 
		fprintf(h, "%d", stPlayer.nXp);
		gotoxy (39, 9); 
		//Missatges d'informacio a l'usuari:
		printf("El personatge %s s'ha guardat correctament", cNomAux);
		gotoxy (39, 10); 
		printf("Prem ENTER per tornar al menu de personatge. ");
	}
	getchar();
	fclose(h);
}
