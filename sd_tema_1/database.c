//Daia Gabriel Petru-311CB
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "structures.h"

int main()
{
	char cmd[1000];
	char cmd_2[1000];
	char eroare[1100];
	int lungime;
  	char *cut;
    char table_name[30];//table name for delete table
  	t_db *database;

	do
	{
    	fgets(cmd,1000, stdin);
    	strcpy(eroare,"Unknown command:\"");
    	strcpy(cmd_2,cmd);
    	strcat(eroare,cmd);
    	lungime=strlen(eroare);
    	eroare[lungime-1]='\"';
    	eroare[lungime]='.';
    	eroare[lungime+1]='\0';

    	cut=strtok(cmd," \n");
    	
    	if(strcmp(cut, "INIT_DB")==0)
    	{
            cut=strtok(NULL," \n");
        	database=INIT_DB(cut);
		}
		else
			if(strcmp(cut,"DELETE_DB")==0)
    		{
                DELETE_DB(&database);
                return 0;
    		}
    		else
    			if(strcmp(cut,"CREATE")==0)
    			{
                    CREATE(database,cmd_2);
    			}
    			else
    				if(strcmp(cut,"DELETE")==0)
    				{
                        cut=strtok(NULL," \n");
                        strcpy(table_name,cut);
                        
                        cut=strtok(NULL," \n");
                        
                        if(cut==NULL)
                        {
                            deleteTheTable(database,table_name);

                        }
                        else
                        {
                           DELETE(database,cmd_2);
                        }
    				}
    				else
    					if(strcmp(cut,"PRINT_DB")==0)
    					{
        					PRINT_DB(database);
    					}
    					else
    						if(strcmp(cut, "PRINT")== 0)
    						{
        						cut=strtok(NULL," \n");
                                strcpy(table_name,cut);
                                printTheTable(database,table_name);
    						}
    						else
    							if(strcmp(cut, "SEARCH")== 0)
    							{
        							SEARCH(database,cmd_2);
    							}
    							else
    								if(strcmp(cut, "ADD")== 0)
    								{
        								addLine(database,cmd_2);
    								}
    								else
    								    if(strcmp(cut, "CLEAR")== 0)
    									{ 
                                            cut=strtok(NULL," \n");
        									CLEAR(database,cut);
    									}
    									else
    										puts(eroare);
    	
    } while(1);
}