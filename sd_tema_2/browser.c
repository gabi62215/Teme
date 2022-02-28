/*Daia Gabriel 311CB*/
#include "TStiva.h"
#include "TCoada.h"
#include "utils.h"
#include "browser.h"

int main(int argc,char *argv[])
{
	TBrowser *browser=initBrowser();
	FILE *in=fopen(argv[1],"rt");
	if(!in)
		return 0;
	FILE *out=fopen(argv[2],"wt");
	if(!out)
		return 0;
	char s[50];
	char *p;

	while(fgets(s,50,in)!=NULL)
	{
		p=strtok(s," \n");
		
		if(strcmp(p,"set_band")==0)
		{
			p=strtok(NULL," \n");
			setBandwidth(p,browser);
		}
		if(strcmp(p,"newtab")==0)
		{
			newTab(browser);
		}
		if(strcmp(p,"deltab")==0)
		{
			deleteTabList(browser);
		}
		if(strcmp(p,"change_tab")==0)
		{
			p=strtok(NULL," \n");
			changeTab(browser,atoi(p));
		}
		if(strcmp(p,"print_open_tabs")==0)
		{
			printTabs(browser,out);
		}
		if(strcmp(p,"goto")==0)
		{
			p=strtok(NULL," \n");
			goToUrl(browser,p);
		}
		if(strcmp(p,"back")==0)
		{
			pageBack(browser->current_tab,out);
		}
		if(strcmp(p,"forward")==0)
		{
			pageForward(browser->current_tab,out);
		}
		if(strcmp(p,"history")==0)
		{
			printHistory(browser,out);
		}
		if(strcmp(p,"del_history")==0)
		{
			p=strtok(NULL," \n");
			delHistory(browser->global_history,atoi(p));
		}
		if(strcmp(p,"list_dl")==0)
		{
			printResources(browser->current_tab->current_page,out);
		}
		if(strcmp(p,"downloads")==0)
		{
			printDownloads(&(browser->downloads),&(browser->downloaded),out);
		}
		if(strcmp(p,"download")==0)
		{
			p=strtok(NULL," \n");
			download(browser,p);
		}
		if(strcmp(p,"wait")==0)
		{
			p=strtok(NULL," \n");
			wait(atoi(p),browser);
		}
	}

	deleteBrowser(&browser);

	fclose(in);
	fclose(out);

	return 0;
}
