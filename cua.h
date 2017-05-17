/*************************************
*
* @Arxiu: cua.h
* @Finalitat: .h del modul Cua. 
* @Autor/s: Alex Cordon Vila
* @Data: 26/4/2013
*
*************************************/
#ifndef _CUA_H
#define _CUA_H 
#include <stdio.h>
#include <stdlib.h>
#include "enemics.h" 
typedef struct n {
	Enemic e;
	struct n* seg;
}Node;
typedef struct{
	Node *cap;
	Node *ult;
}Cua;
Cua CUA_crea();
void CUA_encua(Cua*c,Enemic e);
void CUA_desencua(Cua *c);
Cua CUA_destrueix(Cua c);
Enemic CUA_primer (Cua c);
int CUA_buida(Cua c);
int CUA_plena(Cua c);
#endif 
