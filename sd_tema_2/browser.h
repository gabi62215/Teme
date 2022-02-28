/*Daia Gabriel 311CB*/
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "utils.h"
#include "TStiva.h"
#include "TCoada.h"
#include <time.h>
#include <unistd.h>

#ifndef _BROWSER_
#define _BROWSER_

typedef struct page
{
	char url[21];
	int num_res;
	Resource *resources;
}TPage;

typedef struct tab
{
	int index;
	TPage *current_page;
	TStiva *back_stack;
	TStiva *forward_stack;
}TTab;

typedef struct tabList 
{ 
	struct tabList *urm;
	TTab *info;
} TTabList;

typedef struct browser
{
	TTabList *tabs;
	TCoada *downloaded;
	TCoada *global_history;
	TTab *current_tab;
	TCoada *downloads;
	long bandwidth;
}TBrowser;

//Functii
//Aloca o pagina cu url primit
TPage *initPage(char *url);

//Aloca un tab gol
TTab *initTab();

//Aloca o celula pentru lista de taburi
TTabList *allocTabCell(TTab *tab);

//Aloca o structura browser
TBrowser *initBrowser();

//Sterge o structura pagina
void deletePage(TPage **page);

//Sterge o structura tab
void deleteTab(TTab **tab);

//Sterge o celula 
void deleteCell(TTabList **cell);

//Seteaza bandwidth-ul browserului la value
void setBandwidth(char *value,TBrowser *browser);

//Adauga un tab la lista de taburi cu indexul corect
int newTab(TBrowser *browser);

//Sterge ultimul tab din lista
//Daca tabul curent este ultimul din lista,seteaza tabul curent la cel anterior
void deleteTabList(TBrowser *browser);

//Cauta tabul dupa index si seteaza tabul curent la cel gasit
int changeTab(TBrowser *browser,int index);

//Afiseaza toate taburile
//Daca taburile sunt goale afiseaza empty
void printTabs(TBrowser *browser,FILE *out);

//Acceseaza pagina cu url-ul dat 
int goToUrl(TBrowser *browser,char *url);

//Merge la pagina din varful stivei back_stack si trece pagina curenta in stiva 
//forward_stack
void pageBack(TTab *current_tab,FILE *out);

//Merge la pagina din varful stivei forward_stack si trece pagina curenta in
//stiva back_stack
void pageForward(TTab *current_tab,FILE *out);

//Afiseaza istoricul global
void printHistory(TBrowser *browser,FILE *out);

//Sterge primele n pagini accesate din istoric sau toate daca n=0
void delHistory(TCoada *global_history,int n);

//Afiseaa resursele descarcabile de pe pagina curenta
void printResources(TPage *page,FILE *out);

//Simuleaza treceres seconds secunde
void wait(int seconds,TBrowser *browser);

//Adauga resursa cu indexul index in coada de descarcari
void download(TBrowser *browser,char *index);

//Afiseaza toate descarcarile,cele in curs urmate de cele complete
void printDownloads(TCoada **downloads,TCoada **downloaded,FILE *out);

//Elibereaza lista de taburi
void freeTabs(TTabList **tabs);

//Elibereaza memoria
void deleteBrowser(TBrowser **browser);
#endif