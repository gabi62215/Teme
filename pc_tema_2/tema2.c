#include <stdio.h>
#include "util/task_helper.h"
#include <string.h>
#include <stdlib.h>

void uppercase(char* poezie,int lungime)
{
	int i;
	if(poezie[0]>='a' && poezie[0]<='z')
		poezie[0]=poezie[0]-32;
	for(i=1; i<lungime; i++)
	{
		if(poezie[i]!=' ')
			if(poezie[i]>='A' && poezie[i]<='Z')
		 		poezie[i]=poezie[i]+32;
		if(poezie[i]>='a' && poezie[i]<='z' && poezie[i-1]=='\n')
			poezie[i]=poezie[i]-32;
	}
}

void spaces(char *poezie)
{
	char nou[1000];
	int c=0;
	int d=0;
	while(poezie[c]!='\0')
	{
		if(poezie[c]==' ')
		{
			int temp=c+1;
			if(poezie[temp]!='\0')
			{
				while(poezie[temp]==' ' && poezie[temp] != '\0')
				{
					if(poezie[temp]==' ')
						c++;
					temp++;
				}
			}
		}
		nou[d]=poezie[c];
		c++;
		d++;
	}
	strcpy(poezie,nou);
}

void trimming(char *poezie)
{
	int i,j;
	int c=0;
	for(i=0; poezie[i]!='\0'; i++)
    {
        while (!((poezie[i]>='a' && poezie[i]<='z') || (poezie[i]>='A' && poezie[i]<='Z') || poezie[i]=='\0') && poezie[i]!=' ' && poezie[i]!='\n')
        {
            for(j=i; poezie[j]!='\0'; j++)
            {
                poezie[j]=poezie[j+1];
            }
            poezie[j]='\0';
        }
    }
    spaces(poezie);
}

void silly(char *poezie,int lungime,float p)
{
	int i=0;
	float sample;
	for(i=0; i<lungime; i++)
	{
		if((poezie[i]>='a' && poezie[i]<='z') || (poezie[i]>='A' && poezie[i]<='Z'))
        {
            sample=rand() % 100 / 99.0;
            if(p>sample)
            {
                if(poezie[i]>='A' && poezie[i]<='Z')
                {
                    poezie[i]=poezie[i]+32;
                }
                else
                {   
                    if(poezie[i]>='a' && poezie[i]<='z')
                    {
                        poezie[i]=poezie[i]-32;
                    }
                }
            }
        }
	}
}

void rhimy()
{
	return;
}

void friendly()
{
	return;
}

void print()
{
	return;
}

int main()
{
	srand(42);
	char poezie[1000];
	char optiune[50];
	int continua=1;
	int lungime;
	scanf("%s",optiune);
	while(continua==1)
	{
		if(strcmp(optiune,"quit")==0)
			return 0;
		if(strcmp(optiune,"print")==0)
		{
			puts(poezie);
			scanf("%s",optiune);
		}
		if(strncmp(optiune,"load",3)==0)
		{
			char path[100];
			scanf("%s",path);
			load_file(path,poezie);
			lungime=strlen(poezie);
			scanf("%s",optiune);
		}
		if(strcmp(optiune,"uppercase")==0)
		{
			uppercase(poezie,lungime);
			scanf("%s",optiune);
		}
		if(strcmp(optiune,"trimming")==0)
		{
			trimming(poezie);
			lungime=strlen(poezie);
			scanf("%s",optiune);
		}
		if(strcmp(optiune,"make_it_silly")==0)
		{
			float p;
			scanf("%f",&p);
			silly(poezie,lungime,p);
			scanf("%s",optiune);
		}
		if(strcmp(optiune,"make_it_friendlier")==0)
		{
			scanf("%s",optiune);
		}
		if(strcmp(optiune,"make_it_rhyme")==0)
		{
			char rima[50];
			scanf("%s",rima);
			scanf("%s",optiune);
		}
	}
	return 0;
}