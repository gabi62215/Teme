/*Daia Gabriel 311CB*/
#include "TStiva.h"

TCellSt *allocSCell(size_t dime,void *x)
{
	TCellSt *aux=(TCellSt *)malloc(sizeof(TCellSt));
	if(!aux)
		return NULL;
	aux->info=malloc(dime);
	if(!aux->info)
	{
		free(aux);
		return NULL;
	}
	memcpy(aux->info,x,dime);
	aux->urm=NULL;

	return aux;
}

TStiva *initS(size_t d)
{
	TStiva *s;
	s = (TStiva *)malloc(sizeof(TStiva));
	if(!s) 
		return NULL;

	s->dime = d;
	s->vf = NULL;
	return s;
}

int push(TStiva *s,void *x)
{
	TCellSt *aux=allocSCell(s->dime,x);
	if(!aux)
		return 0;
	aux->urm=s->vf;
	s->vf=aux;
	return 1;
}

int pop(TStiva *s,void *x)
{
	if(s->vf==NULL)
		return 0;

	memcpy(x,s->vf->info,s->dime);
	TCellSt *aux=s->vf;
	s->vf=aux->urm;
	free(aux->info);
	free(aux);
	return 1;
}

void distrS(TStiva **s)
{
	while((*s)->vf!=NULL)
	{
		TCellSt *aux=(*s)->vf;
		(*s)->vf=aux->urm;
		free(aux->info);
		free(aux);
	}

	free(*s);
	*s=NULL;
}

void resetS(TStiva *s)
{
	while(s->vf!=NULL)
	{
		TCellSt *aux=s->vf;
		s->vf=aux->urm;
		free(aux->info);
		free(aux);
	}
}



