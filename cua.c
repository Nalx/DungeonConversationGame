/**************************************
*
* @Arxiu: cua.c 
* @Finalitat: Implementacions de les funcions basiques del modul Cua
* @Autor/s: Alex Cordon Vila
* @Data: 19/5/2013
*
***************************************/
//Propia
#include "cua.h"
/********************************* 
* @Nom: CUA_crea                                                                                              
* @Finalitat: Demana memòria de forma dinàmica per poder treballar amb la cua
* @Arguments: In:-                        
*             Out: -                                                                
* @Retorn: Retorna c de tipus Cua, retorna la cua creada                          
**********************************/  
Cua CUA_crea( ){
	Cua c;
	c.cap = (Node*)malloc(sizeof(Node));
	if(c.cap == NULL){
		printf("Error\n");
	}else{
		c.ult = c.cap;
		c.cap->seg = NULL;
	}
	return c;
}
/********************************* 
* @Nom: CUA_encua                                                                                              
* @Finalitat: Afegeix un element de tipus Enemic a la cua
* @Arguments: In: *c,e                       
*             Out: *c                                                                 
* @Retorn: No hi ha retorn, és void                                   
**********************************/  
void CUA_encua(Cua *c, Enemic e){
	Node *aux;
	aux = (Node*) malloc (sizeof(Node));
	//control de malloc
	if (aux == NULL){
		printf("Error!\n");
	}
	else{
		aux->e = e;
		aux->seg = NULL;
		c->ult->seg = aux;
		c->ult = aux;
	}
}
/********************************* 
* @Nom: CUA_desencua                                                                                               
* @Finalitat: Elimina el primer element introduït a la cua
* @Arguments: In: *c                       
*             Out: *c                                                              
* @Retorn: No hi ha retorn, és void                                 
**********************************/  
void CUA_desencua(Cua *c){
	Node *aux;
	if(c->cap == c->ult){
		printf("Error! Cua buida\n");
	}else{
		aux = c->cap->seg;
		c->cap->seg = aux->seg;
		free(aux);
		if(c->cap->seg == NULL){
			c->ult = c->cap;
		}
	}
}
/********************************* 
* @Nom: CUA_destrueix                                                                                               
* @Finalitat: Allibera la memòria demanada al crear la cua
* @Arguments: In: c                        
*             Out: -                                                                
* @Retorn: Retorna c de tipus Cua                                   
**********************************/  
Cua CUA_destrueix(Cua c){
	Node *aux;
	while (c.cap != NULL){
		aux=c.cap;
		c.cap = aux->seg;
		free(aux);
	}
	c.ult = NULL;
	return c;
}
/********************************* 
* @Nom: CUA_primer                                                                                               
* @Finalitat:Consulta el primer element de la cua         
* @Arguments: In: c                         
*             Out: -                                                                 
* @Retorn: Retorna e de tipus Enemic                                   
**********************************/  
Enemic CUA_primer (Cua c){
	Enemic e;
	//Com definim l'element indefinit?
	//e=NULL;
	if(c.cap->seg != NULL){
		e = c.cap->seg->e;
	}
	return e;
}
/********************************* 
* @Nom:CUA_buida                                                                                               
* @Finalitat: Retorna cert si la cua és buida             
* @Arguments: In: c                         
*             Out:                                                                  
* @Retorn: Retorna un booleà                                  
**********************************/  
int CUA_buida(Cua c){
	//retorna el resultat de comparar cap amb ult
	return c.cap == c.ult; 
}
/********************************* 
* @Nom: CUA_plena                                                                                               
* @Finalitat: Retorna cert si la cua és plena             
* @Arguments: In: c                         
*             Out:-                                                               
* @Retorn: Retorna 0 si la cua és plena                           
**********************************/  
int CUA_plena(Cua c){
    return c.cap != c.ult;
}

