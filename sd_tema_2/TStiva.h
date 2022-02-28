/*Daia Gabriel 311CB*/
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#ifndef _STIVA_
#define _STIVA_

typedef struct cellst
{
	struct cellst *urm;
	void *info;
}TCellSt;

typedef struct stiva
{ 
	size_t dime; /* dim.element */
	TCellSt *vf; /* adresa celulei din varf */
} TStiva;

/* FUNCTII STIVA */

//aloca o celula pentru stiva
//dime este dimensiunea pentru info,iar x este zona de memomerie
//returneaza NULL in caz de esec
TCellSt *allocSCell(size_t dime,void *x);

//initializa o stiva cu varful la NULL
//returneaza NULL in caz de esec
TStiva *initS(size_t d);

//adauga un element in stiva
//s este stiva in care se insereaza,iar x este zona de memomerie de inserat
//1-succes 0-esec
int push(TStiva *s,void *x);

//elimina un element din stiva
//s este stiva in care se insereaza,iar x este zona de memomerie unde se extrage
//1-succes 0-esec
int pop(TStiva *s,void *x);

//elibereaza toata memoria din stiva si sterge stiva
//s stiva ce va fi distrusa
void distrS(TStiva **s);

//elibereaza toata memoria din stiva
//s stiva care se goleste
void resetS(TStiva *s);

#endif