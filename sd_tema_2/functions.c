/*Daia Gabriel 311CB*/
#include "browser.h"

TPage *initPage(char *url)
{
	int n;
	TPage *aux=malloc(sizeof(TPage));
	if(!aux)
		return NULL;

	strcpy(aux->url,url);
	aux->resources=get_page_resources(url,&n);
	if(!aux->resources)
	{
		free(aux);
		return NULL;
	}
	aux->num_res=n;

	return aux;
}

TTab *initTab()
{
	TTab *aux=malloc(sizeof(TTab));
	if(!aux)
		return NULL;

	aux->index=0;
	aux->current_page=NULL;

	TStiva *b=initS(sizeof(TPage));
	if(!b)
	{
		free(aux);
		return NULL;
	}

	TStiva *f=initS(sizeof(TPage));
	if(!f)
	{
		free(b);
		free(aux);
		return NULL;
	}

	aux->back_stack=b;
	aux->forward_stack=f;

	return aux;
}

TTabList *allocTabCell(TTab *tab)
{
	TTabList *aux=malloc(sizeof(TTabList));
	if(!aux)
		return NULL;

	aux->urm=NULL;
	aux->info=tab;

	return aux;
}

void deletePage(TPage **page)
{
	//ar trebui free la resurse
	free(*page);

	*page=NULL;
}

void deleteTab(TTab **tab)
{
	distrS(&((*tab)->back_stack));
	distrS(&((*tab)->forward_stack));
	if((*tab)->current_page!=NULL)
		deletePage(&((*tab)->current_page));
	free(*tab);

	*tab=NULL;
}

void deleteCell(TTabList **cell)
{
	deleteTab(&((*cell)->info));
	free(*cell);

	*cell=NULL;
}

TBrowser *initBrowser()
{
	TBrowser *aux=malloc(sizeof(TBrowser));
	if(!aux)
		return NULL;

	TTab *tab=initTab();
	if(!tab)
	{
		free(aux);
		return NULL;
	}

	TTabList *cell=allocTabCell(tab);
	if(!cell)
	{
		free(aux);
		deleteTab(&tab);
		return NULL;
	}

	TCoada *global_history=initC(21);
	if(!global_history)
	{
		free(aux);
		deleteTab(&tab);
		deleteCell(&cell);
		return NULL;
	}

	TCoada *downloads=initC(sizeof(Resource));
	if(!downloads)
	{
		free(aux);
		deleteTab(&tab);
		deleteCell(&cell);
		distrQ(&global_history);
		return NULL;
	}

	TCoada *downloaded=initC(sizeof(Resource));
	if(!downloaded)
	{
		free(aux);
		deleteTab(&tab);
		deleteCell(&cell);
		distrQ(&global_history);
		distrQ(&downloads);
		return NULL;
	}

	aux->tabs=cell;
	aux->global_history=global_history;
	aux->downloads=downloads;
	aux->bandwidth=1024;
	aux->current_tab=cell->info;
	aux->downloaded=downloaded;

	return aux;
}

void setBandwidth(char *value,TBrowser *browser)
{	
	int n=atoi(value);
	browser->bandwidth=n;
}

int newTab(TBrowser *browser)
{
	TTabList *aux;
	TTabList *ultim=NULL;
	TTabList *p;
	
	TTab *tab=initTab();
	if(!tab)
		return 0;

	for(p=browser->tabs; p!=NULL; p=p->urm)
		ultim=p;

	tab->index=ultim->info->index+1;

	aux=allocTabCell(tab);
	if(!aux)
	{
		deleteTab(&tab);
		return 0;
	}

	if(ultim)
		ultim->urm=aux;
	else
		browser->tabs=aux;

	browser->current_tab=tab;

	return 1;
}

void deleteTabList(TBrowser *browser)
{
	TTabList *ultim=NULL;
	TTabList *p;

	for(p=browser->tabs; p->urm!=NULL; p=p->urm)
		ultim=p;

	if(browser->current_tab->index==p->info->index)
		browser->current_tab=ultim->info;

	if(ultim)
		ultim->urm=p->urm;//NULL
	else
		browser->tabs=p->urm;//NULL

	deleteCell(&p);
}

int changeTab(TBrowser *browser,int index)
{
	TTabList *p;

	for(p=browser->tabs; p!=NULL; p=p->urm)
		if(index==p->info->index)
		{
			browser->current_tab=p->info;
			return 1;
		}

	return 0;
}

void printTabs(TBrowser *browser,FILE *out)
{
	TTabList *p;

	for(p=browser->tabs; p!=NULL; p=p->urm)
	{
		if(p->info->current_page==NULL)
			fprintf(out,"(%d: empty)\n",p->info->index);
		else
			fprintf(out,"(%d: %s)\n",p->info->index,p->info->current_page->url);
	}
}

void wait(int seconds,TBrowser *browser)
{
	long downloaded;
	long remaining;
	downloaded=seconds*browser->bandwidth;
	Resource *aux;
	Resource *aux_2=malloc(sizeof(Resource));

	while(downloaded!=0)
	{

		if(browser->downloads->ic==NULL && browser->downloads->sc==NULL)
			break;
		
		aux=(Resource *)browser->downloads->ic->info;
		remaining=aux->dimension-aux->currently_downloaded;

		if(remaining>downloaded)
		{
			aux->currently_downloaded=aux->currently_downloaded+downloaded;
			downloaded=0;
		}
		else
		{
			aux->currently_downloaded=aux->dimension;
			extrC(browser->downloads,aux_2);
			insC(browser->downloaded,aux_2);
			downloaded=downloaded-remaining;
		}
	}

	free(aux_2);
}

int goToUrl(TBrowser *browser,char *url)
{
	TPage *page=initPage(url);
	if(!page)
		return 0;

	if(browser->current_tab->current_page!=NULL)
	{
		push(browser->current_tab->back_stack,browser->current_tab->current_page);
		deletePage(&(browser->current_tab->current_page));
	}

	resetS(browser->current_tab->forward_stack);

	browser->current_tab->current_page=page;

	insC(browser->global_history,page->url);

	wait(1,browser);
	
	return 1;
}

void pageBack(TTab *current_tab,FILE *out)
{
	if(current_tab->back_stack->vf==NULL)
		fprintf(out,"can't go back, no pages in stack");
	else
	{
		push(current_tab->forward_stack,current_tab->current_page);
		pop(current_tab->back_stack,current_tab->current_page);
	}
}

void pageForward(TTab *current_tab,FILE *out)
{
	if(current_tab->forward_stack->vf==NULL)
		fprintf(out,"can't go forward, no pages in stack");
	else
	{
		push(current_tab->back_stack,current_tab->current_page);
		pop(current_tab->forward_stack,current_tab->current_page);
	}
}

void printHistory(TBrowser *browser,FILE *out)
{
	TCoada *aux=initC(21);
	char *url=malloc(21);
	int p=0;

	while(browser->global_history->ic!=NULL && 
		browser->global_history->sc!=NULL)
	{
		p=1;
		extrC(browser->global_history,url);
		fprintf(out,"%s\n",url);
		insC(aux,url);
	}

	if(p==1)
		browser->global_history=aux;
	else
		distrQ(&aux);

	free(url);
}

void delHistory(TCoada *global_history,int n)
{
	int i;
	char *url=malloc(21);

	if(n==0)
		resetQ(global_history);
	else
	{
		for(i=0; i<n; i++)
			extrC(global_history,url);
	}

	free(url);
}

void printResources(TPage *page,FILE *out)
{
	int i;

	if(page==NULL)
		return;

	for(i=0; i<page->num_res; i++)
	{
		fprintf(out,"[%d - \"%s\" : %ld]\n",i,page->resources[i].name
		,page->resources[i].dimension);
	}
}

void download(TBrowser *browser,char *index)
{
	if(browser->current_tab->current_page==NULL)
		return;
	
	int i=atoi(index);
	Resource *aux;
	aux=&(browser->current_tab->current_page->resources[i]);
	Resource *aux_2=malloc(sizeof(Resource));
	TCoada *aux_3=initC(sizeof(Resource));
	long remaining_1;
	long remaining_2;
	int p=0;
	int p_1=0;

	remaining_1=aux->dimension-aux->currently_downloaded;

	while(browser->downloads->ic!=NULL && browser->downloads->sc!=NULL)
	{
		p_1=1;
		extrC(browser->downloads,aux_2);
		remaining_2=aux_2->dimension-aux_2->currently_downloaded;

		if(p==0 && remaining_1<=remaining_2)
		{
			insC(aux_3,aux);
			p=1;
		}

		insC(aux_3,aux_2);	
	}

	if(p_1==1)
		browser->downloads=aux_3;
	else
		insC(browser->downloads,aux);

	if(p==0 && p_1==1)
		insC(browser->downloads,aux);

	free(aux_2);
}

void printDownloads(TCoada **downloads,TCoada **downloaded,FILE *out)
{
	TCoada *aux=initC(sizeof(Resource));
	TCoada *aux_3=initC(sizeof(Resource));
	Resource *aux_2=malloc(sizeof(Resource));
	int p=0;
	int p_2=0;
	long remaining;

	while((*downloads)->ic!=NULL && (*downloads)->sc!=NULL)
	{
		p=1;
		extrC((*downloads),aux_2);
		remaining=aux_2->dimension-aux_2->currently_downloaded;
		fprintf(out,"[\"%s\" : %ld/%ld]\n",aux_2->name,remaining,aux_2->dimension);
		insC(aux,aux_2);
	}

	if(p==1)
		*downloads=aux;
	else
		distrQ(&aux);

	while((*downloaded)->ic!=NULL && (*downloaded)->sc!=NULL)
	{

		p_2=1;
		extrC((*downloaded),aux_2);
		fprintf(out,"[\"%s\" : completed]\n",aux_2->name);
		insC(aux_3,aux_2);
	}

	if(p_2==1)
		*downloaded=aux_3;
	else
		distrQ(&aux_3);

	free(aux_2);
}

void freeTabs(TTabList **tabs)
{
	TTabList *p=*tabs;
	TTabList *aux;

	while(p!=NULL)
	{	
		aux=p;
		p=p->urm;
		deleteTab(&aux->info);
		free(aux);
	}

	*tabs=NULL;
}

void deleteBrowser(TBrowser **browser)
{
	freeTabs(&((*browser)->tabs));
	distrQ(&((*browser)->downloaded));
	distrQ(&((*browser)->global_history));
	distrQ(&((*browser)->downloads));
	free(*browser);

	*browser=NULL;
}