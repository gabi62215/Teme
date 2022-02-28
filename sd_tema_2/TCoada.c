/*Daia Gabriel 311CB*/
#include "TCoada.h"

TCell *allocQCell(size_t dime,void *x)
{
	TCell *aux=(TCell *)malloc(sizeof(TCell));
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

TCoada *initC(size_t d)
{
	TCoada *c;
	c=(TCoada *)malloc(sizeof(TCoada));
	if(!c)
		return NULL;

	c->dime=d;
	c->ic=NULL;
	c->sc=NULL;

	return c;
}

int insC(TCoada *c,void *x)
{
	TCell *aux=allocQCell(c->dime,x);
	if(!aux)
		return 0;

	if(c->ic==NULL && c->sc==NULL)
	{
		c->ic=aux;
		c->sc=aux;
	}
	else
	{
		c->sc->urm=aux;
		c->sc=aux;
	}

	return 1;
}

int extrC(TCoada *c,void *x)
{
	TCell *aux;

	if(c->sc==NULL && c->ic==NULL)
		return 0;

	if(c->sc==c->ic)
	{
		aux=c->ic;
		c->ic=aux->urm;
		c->ic=NULL;
		c->sc=NULL;
	}
	else
	{
		aux=c->ic;
		c->ic=aux->urm;
	}

	memcpy(x,aux->info,c->dime);
	free(aux->info);
	free(aux);
	return 1;
}

void resetQ(TCoada *c)
{
	TCell *aux;

	while(c->ic!=NULL && c->sc!=NULL)
	{
		if(c->sc==c->ic)
		{
			aux=c->ic;
			c->ic=aux->urm;
			c->ic=NULL;
			c->sc=NULL;
		}
		else
		{
			aux=c->ic;
			c->ic=aux->urm;
		}
		free(aux->info);
		free(aux);
	}
}

void distrQ(TCoada **c)
{
	TCell *aux;

	while((*c)->ic!=NULL && (*c)->sc!=NULL)
	{
		if((*c)->sc==(*c)->ic)
		{
			aux=(*c)->ic;
			(*c)->ic=aux->urm;
			(*c)->ic=NULL;
			(*c)->sc=NULL;
		}
		else
		{
			aux=(*c)->ic;
			(*c)->ic=aux->urm;
		}
		free(aux->info);
		free(aux);
	}
	free(*c);
	*c=NULL;
}