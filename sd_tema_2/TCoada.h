/*Daia Gabriel 311CB*/
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#ifndef _COADA_
#define _COADA_

typedef struct cell /* dimensiune variabila */
{ 
	struct cell *urm;
	void* info;
} TCell;

typedef struct coada
{ 
	size_t dime; /* dim.element */
	TCell *ic;
	TCell *sc; /* adr.prima, ultima celula */
} TCoada;

/* FUNCTII COADA */

//aloca o celula pentru coada
//dime este dimensiunea pentru info,iar x este zona de memomerie
//returneaza NULL in caz de esec
TCell *allocQCell(size_t dime,void *x);

//initializeaza o coada cu inceputul si sfarsitul la NULL
//returneaza NULL in caz de esec
TCoada *initC(size_t d);

//adauga un element in coada
//c este coada in care se insereaza,iar x este zona de memomerie de inserat
//1-succes 0-esec
int insC(TCoada *c,void *x);

//elimina un element din coada
//c este coada in care se insereaza,iar x este zona de memomerie unde se extrage
//1-succes 0-esec
int extrC(TCoada *c,void *x);

//elibereaza toata memoria din coada si sterge coada
//c coada ce va fi distrusa
void resetQ(TCoada *c);

//elibereaza toata memoria din coada
//c coada care se goleste
void distrQ(TCoada **c);

#endif


