//Daia Gabriel Petru-311CB
#include "structures.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

t_db *INIT_DB(char *name)
{
	t_db *database=(t_db *)malloc(sizeof(t_db));
	if(database==NULL)//verificare 
	{
		printf("Alocare baza de date esuata\n");
		return NULL;
	}

	strcpy(database->name,name);
	database->tables=NULL;

	return database;
}

t_column *alocColumn(char *name)//alocare element de tip coloana
{
	t_column *aux=(t_column *)malloc(sizeof(t_column));
	char column_name[30];
	strcpy(column_name,name);

	if(aux)
	{
		if(column_name[strlen(column_name)-1]=='\n')
		{
			column_name[strlen(column_name)-1]='\0';
			strcpy(aux->name,column_name);
		}
		else
		{
			strcpy(aux->name,name);
		}
		
		aux->next=NULL;
	}
	return aux;	
}

int addColumn(t_column **column,char *name)//adaugare element de tip coloana la sfarsit
{
	
	t_column *aux;
	t_column *ultim=NULL;
	t_column *p;
	
	for(p=*column; p!=NULL; p=p->next)
	{
		ultim=p;
	}
	
	aux=alocColumn(name);
	if(!aux)
	{
		printf("Alocare esuata\n");
		return 0;
	}

	if(ultim)
	{
		ultim->next=aux;
	}
	else
	{
		*column=aux;
	}
	
	return 1;
}

t_stringCell *alocStringCell(char *name)//alocare element de tip string cell
{
	t_stringCell *aux=(t_stringCell *)malloc(sizeof(t_stringCell));

	char *cell_name=malloc(strlen(name)+2);
	strcpy(cell_name,name);

	if(!cell_name)
		return NULL;
	
	if(aux)
	{
		aux->value=malloc(strlen(name)+2);
		if(aux->value==NULL)
		{
			free(aux);
			return NULL;
		}
		if(cell_name[strlen(cell_name)-1]=='\n')
		{
			cell_name[strlen(cell_name)-1]='\0';
			strcpy(aux->value,cell_name);
		}
		else
		{
			strcpy(aux->value,name);
		}

		aux->next=NULL;
	}

	free(cell_name);

	return aux;
}

int addStringCell(t_stringCell **string_cell,char *name)//adugare element de tip string cell
{
	t_stringCell *aux;
	t_stringCell *ultim=NULL;
	t_stringCell *p;

	for(p=*string_cell; p!=NULL; p=p->next)
	{
		ultim=p;
	}

	aux=alocStringCell(name);
	if(!aux)
		return 0;
	
	if(ultim)
		ultim->next=aux;
	else
		*string_cell=aux;
	
	return 1;
}

t_floatCell *alocFloatCell(float value)
{
	t_floatCell *aux=(t_floatCell *)malloc(sizeof(t_floatCell));
	if(aux)
	{
		aux->value=value;
		aux->next=NULL;
	}
	return aux;
}

int addFloatCell(t_floatCell **float_cell,float value)
{
	t_floatCell *aux;
	t_floatCell *ultim=NULL;
	t_floatCell *p;

	for(p=*float_cell; p!=NULL; p=p->next)
	{
		ultim=p;
	}

	aux=alocFloatCell(value);
	if(!aux)
		return 0;

	if(ultim)
		ultim->next=aux;
	else
		*float_cell=aux;
	
	return 1;
}

t_intCell *alocIntCell(int value)
{
	t_intCell *aux=(t_intCell *)malloc(sizeof(t_intCell));
	if(aux)
	{
		aux->value=value;
		aux->next=NULL;
	}
	return aux;
}

int addIntCell(t_intCell **int_cell,int value)
{
	t_intCell *aux;
	t_intCell *ultim=NULL;
	t_intCell *p;

	for(p=*int_cell; p!=NULL; p=p->next)
	{
		ultim=p;
	}

	aux=alocIntCell(value);
	if(!aux)
		return 0;

	if(ultim)
		ultim->next=aux;
	else
		*int_cell=aux;
	
	return 1;
}

t_stringLine *alocStringLine()//daca intoarce NULL esueaza
{
	t_stringLine *aux=(t_stringLine *)malloc(sizeof(t_stringLine));
	if(aux)
	{
		aux->cells=NULL;
		aux->next=NULL;
	}
	return aux;
}

int addStringLine(void **string_line)
{
	t_stringLine *aux;
	t_stringLine *ultim=NULL;
	t_stringLine *p;

	for(p=(t_stringLine *)*string_line; p!=NULL; p=p->next)
	{
		ultim=p;
	}

	aux=alocStringLine();
	if(!aux)
		return 0;

	if(ultim)
		ultim->next=aux;
	else
		*string_line=aux;
	
	return 1;
}

t_floatLine *alocFloatLine()//daca intoarce NULL esueaza
{
	t_floatLine *aux=(t_floatLine *)malloc(sizeof(t_floatLine));
	if(aux)
	{
		aux->cells=NULL;
		aux->next=NULL;
	}
	return aux;
}

int addFloatLine(void **float_line)
{
	t_floatLine *aux;
	t_floatLine *ultim=NULL;
	t_floatLine *p;

	for(p=(t_floatLine *)*float_line; p!=NULL; p=p->next)
	{
		ultim=p;
	}

	aux=alocFloatLine();
	if(!aux)
		return 0;

	if(ultim)
		ultim->next=aux;
	else
		*float_line=aux;
	
	return 1;
}

t_intLine *alocIntLine()//daca intoarce NULL esueaza
{
	t_intLine *aux=(t_intLine *)malloc(sizeof(t_intLine));
	if(aux)
	{
		aux->cells=NULL;
		aux->next=NULL;
	}
	return aux;
}

int addIntLine(void **int_line)
{
	t_intLine *aux;
	t_intLine *ultim=NULL;
	t_intLine *p;

	for(p=(t_intLine *)*int_line; p!=NULL; p=p->next)
	{
		ultim=p;
	}
	
	aux=alocIntLine();
	if(!aux)
		return 0;

	if(ultim)
		ultim->next=aux;
	else
		*int_line=aux;
	
	return 1;
}

t_table *alocTable(char *name,t_cellType type)
{
	t_table *aux=(t_table *)malloc(sizeof(t_table));
	if(aux)
	{
		strcpy(aux->name,name);
		aux->type=type;
		aux->columns=NULL;
		aux->lines=NULL;
		aux->next=NULL;
	}
	return aux;
}

int addTable(t_table **table,char *name,t_cellType type)
{
	t_table *aux;
	t_table *ultim=NULL;
	t_table *p;

	for(p=*table; p!=NULL; p=p->next)
	{
		ultim=p;
	}
	
	aux=alocTable(name,type);
	if(!aux)
		return 0;
	
	if(ultim)
		ultim->next=aux;
	else
		*table=aux;
	
	return 1;
}

int CREATE(t_db *database,char *arguments)
{
	t_table *ultim=NULL;
	t_table *p;
	char *cut=strtok(arguments," ");//CREATE

	cut=strtok(NULL," ");//Numele tabelului
	char table_name[30];
	strcpy(table_name,cut);

	for(p=database->tables; p!=NULL; p=p->next)//verific daca numele mai exista
	{
		if(strcmp(p->name,table_name)==0)
			printf("Table \"%s\" already exists.\n",table_name);
	}

	cut=strtok(NULL," ");//Tipul tabelului
	char tip[10];
	strcpy(tip,cut);

	t_cellType type;
	if(strcmp(tip,"INT")==0)
		type=INT;
	else
		if(strcmp(tip,"FLOAT")==0)
			type=FLOAT;
		else
			if(strcmp(tip,"STRING")==0)
				type=STRING;
			else
			{
				printf("Unknown data type:\"%s\"\n",tip);
				return 0;
			}
	
	if(addTable(&(database->tables),table_name,type)==0)
	{
		printf("Adaugare tabel esuata\n");
		return 0;
	}
	
	for(p=database->tables; p!=NULL; p=p->next)//ma duc la ultimul tabel
	{
		ultim=p;
	}
	
	cut=strtok(NULL," ");//al treilea argument dupa CREATE
	
	while(cut!=NULL)
	{
		if(ultim)
		{
			addColumn(&ultim->columns,cut);
		}
		else
		{
			addColumn(&database->tables->columns,cut);
		}

		cut=strtok(NULL," ");//urmatoarele argumente
	}
	
	return 1;
}

void printColumns(t_table *table)
{
	int i;
	t_column *p;
	int column_number=0;
	int spaces_number;
	for(p=table->columns; p!=NULL; p=p->next)
	{
		spaces_number=30-strlen(p->name)+1;//1 spatiu
		printf("%s",p->name);
		
		for(i=0; i<spaces_number; i++)
		{
			printf(" ");
		}
		
		column_number++;
	}
	
	printf("\n");

	for(i=0; i<column_number; i++)
	{
		printf("------------------------------ ");
	}
	printf("\n");
}

void printLines(t_table *table)
{
	t_cellType type=table->type;
	
	if(type==INT)
	{
		t_intLine *p_1;
		t_intCell *p_2;
		for(p_1=(t_intLine *)table->lines; p_1!=NULL; p_1=p_1->next)
		{
			for(p_2=p_1->cells; p_2!=NULL; p_2=p_2->next)
			{
				printf("%-31d",p_2->value);
			}
			printf("\n");
		} 
	}

	if(type==STRING)
	{
		t_stringLine *p_1;
		t_stringCell *p_2;
		for(p_1=(t_stringLine *)table->lines; p_1!=NULL; p_1=p_1->next)
		{
			for(p_2=p_1->cells; p_2!=NULL; p_2=p_2->next)
			{
				printf("%-31s",p_2->value);
			}
			printf("\n");
		}
	}

	if(type==FLOAT)
	{
		t_floatLine *p_1;
		t_floatCell *p_2;
		for(p_1=(t_floatLine *)table->lines; p_1!=NULL; p_1=p_1->next)
		{
			for(p_2=p_1->cells; p_2!=NULL; p_2=p_2->next)
			{
				printf("%-31f",p_2->value);
			}
			printf("\n");
		}
	}

}

void printTable(t_table *table)
{
	printf("TABLE: %s\n",table->name);
	printColumns(table);
	printLines(table);
}

int printTheTable(t_db *database,char *table_name)
{
	t_table *p_table;
	for(p_table=database->tables; p_table!=NULL; p_table=p_table->next)
	{
		if(strcmp(p_table->name,table_name)==0)
		{
			printTable(p_table);
			printf("\n");
			return 1;
		}
	}

	printf("Table \"%s\" not found in database.\n",table_name);
	return 0;
}

void PRINT_DB(t_db *database)
{
	t_table *p;
	printf("DATABASE: %s",database->name);
	printf("\n");
	printf("\n");
	for(p=database->tables; p!=NULL; p=p->next)
	{
		printTable(p);
		printf("\n");
	}
}

void deleteColumn(t_column **column)
{
	t_column *p=*column;
	t_column *aux;

	while(p!=NULL)
	{
		aux=p;
		p=p->next;
		free(aux);
	}

	*column=NULL;
}

void deleteIntLine(void **int_line)
{
	t_intLine *p_int_line=(t_intLine *)*int_line;

	while(p_int_line!=NULL)
	{
		t_intCell *p_int_cell=p_int_line->cells;

		while(p_int_cell!=NULL)
		{
			t_intCell *aux_int_cell=p_int_cell;
			p_int_cell=p_int_cell->next;
			free(aux_int_cell);
		}

		t_intLine *aux_int_line=p_int_line;
		p_int_line=p_int_line->next;
		free(aux_int_line);
	}

	*int_line=NULL;
}

void deleteFloatLine(void **float_line)
{
	t_floatLine *p_float_line=(t_floatLine *)*float_line;

	while(p_float_line!=NULL)
	{
		t_floatCell *p_float_cell=p_float_line->cells;

		while(p_float_cell!=NULL)
		{
			t_floatCell *aux_float_cell=p_float_cell;
			p_float_cell=p_float_cell->next;
			free(aux_float_cell);
		}

		t_floatLine *aux_float_line=p_float_line;
		p_float_line=p_float_line->next;
		free(aux_float_line);
	}

	*float_line=NULL;
}

void deleteStringLine(void **string_line)
{
	t_stringLine *p_string_line=(t_stringLine *)*string_line;

	while(p_string_line!=NULL)
	{
		t_stringCell *p_string_cell=p_string_line->cells;

		while(p_string_cell!=NULL)
		{
			t_stringCell *aux_string_cell=p_string_cell;
			p_string_cell=p_string_cell->next;
			free(aux_string_cell->value);
			free(aux_string_cell);
		}

		t_stringLine *aux_string_line=p_string_line;
		p_string_line=p_string_line->next;
		free(aux_string_line);
	}

	*string_line=NULL;
}

void deleteTable(t_table **table)
{
	deleteColumn(&((*table)->columns));

	if((*table)->type==INT)
	{
		deleteIntLine(&((*table)->lines));
	}
	if((*table)->type==FLOAT)
	{
		deleteFloatLine(&((*table)->lines));
	}
	if((*table)->type==STRING)
	{
		deleteStringLine(&((*table)->lines));
	}

	free(*table);
	*table=NULL;
}

int deleteTheTable(t_db *database,char *table_name)
{
	t_table *p_table;
	t_table *ant=NULL;

	for(p_table=database->tables; p_table!=NULL; p_table=p_table->next)
	{
		if(strcmp(p_table->name,table_name)==0)
		{
			if(ant)
				ant->next=p_table->next;
			else
				database->tables=p_table->next;
			deleteTable(&p_table);
			return 1;
		}
		ant=p_table;
	}

	printf("Table \"%s\" not found in database.\n",table_name);
	return 0;
}

void DELETE_DB(t_db **database)
{
	t_table *p_table=(*database)->tables;
	t_table *aux;

	while(p_table!=NULL)
	{
		aux=p_table;
		p_table=p_table->next;
		deleteTable(&aux);
	}

	free(*database);
	*database=NULL;
}

int addLine(t_db *database,char *values)
{
	char *cut=strtok(values," ");//comanda
	t_table *p_table;
	cut=strtok(NULL," ");//numele tabelului
	
	for(p_table=database->tables; p_table!=NULL; p_table=p_table->next)
	{
		if(strcmp(p_table->name,cut)==0)
		{
			break;
		}
	}

	if(p_table==NULL)
	{
		printf("Table \"%s\" not found in database.\n",cut);
		return 0;
	}

	cut=strtok(NULL," ");//valoare pentru prima coloana
	
	if(p_table->type==INT)
	{
		addIntLine(&(p_table->lines));
		
		t_intLine *p_int_line;
		t_intLine *copie_linie=(t_intLine *)p_table->lines;
		t_intLine *ultim_int=NULL;

		for(p_int_line=(t_intLine *)p_table->lines; p_int_line!=NULL; 
			p_int_line=p_int_line->next)
		{
			ultim_int=p_int_line;
		}

		while(cut!=NULL)
		{
			if(ultim_int)
			{
				addIntCell(&(ultim_int->cells),atoi(cut));
			}
			else
			{
				addIntCell(&(copie_linie->cells),atoi(cut));
			}

			cut=strtok(NULL," ");//urmatoarele valorii
		}
	}

	if(p_table->type==FLOAT)
	{
		addFloatLine(&(p_table->lines));

		t_floatLine *p_float_line;
		t_floatLine *copie_linie=(t_floatLine *)p_table->lines;
		t_floatLine *ultim_float=NULL;

		for(p_float_line=(t_floatLine *)p_table->lines; p_float_line!=NULL; 
			p_float_line=p_float_line->next)
		{
			ultim_float=p_float_line;
		}

		while(cut!=NULL)
		{
			if(ultim_float)
			{
				addFloatCell(&(ultim_float->cells),atof(cut));
			}
			else
			{
				addFloatCell(&(copie_linie->cells),atof(cut));
			}

			cut=strtok(NULL," ");//urmatoarele valorii
		}
	}

	if(p_table->type==STRING)
	{
		addStringLine(&(p_table->lines));

		t_stringLine *p_string_line;
		t_stringLine *copie_linie=(t_stringLine *)p_table->lines;
		t_stringLine *ultim_string=NULL;
		
		for(p_string_line=(t_stringLine *)p_table->lines; p_string_line!=NULL; 
			p_string_line=p_string_line->next)
		{
			ultim_string=p_string_line;
		}

		while(cut!=NULL)
		{
			if(ultim_string)
			{
				addStringCell(&(ultim_string->cells),cut);
			}
			else
			{
				addStringCell(&(copie_linie->cells),cut);
			}

			cut=strtok(NULL," ");//urmatoarele valorii
		}
	}

	return 1;
}

void CLEAR(t_db *database,char *table_name)
{
	t_table *p_table;
	for(p_table=database->tables; p_table!=NULL; p_table=p_table->next)
	{
		if(strcmp(p_table->name,table_name)==0)
		{
			break;
		}
	}

	if(p_table==NULL)
	{
		printf("Table \"%s\" not found in database.\n",table_name);
	}
	else
	{
		if(p_table->type==INT)
			deleteIntLine(&(p_table->lines));
		if(p_table->type==FLOAT)
			deleteFloatLine(&(p_table->lines));
		if(p_table->type==STRING)
			deleteStringLine(&(p_table->lines));
	}
}

void printIntLine(t_intCell *int_cell)
{
	t_intCell *p_int_cell;
	
	for(p_int_cell=int_cell; p_int_cell!=NULL; p_int_cell=p_int_cell->next)
	{
		printf("%-31d",p_int_cell->value);
	}
}	

void printFloatLine(t_floatCell *float_cell)
{
	t_floatCell *p_float_cell;

	for(p_float_cell=float_cell; p_float_cell!=NULL; 
		p_float_cell=p_float_cell->next)
	{
		printf("%-31f",p_float_cell->value);
	}
}

void printStringLine(t_stringCell *string_cell)
{
	t_stringCell *p_string_cell;

	for(p_string_cell=string_cell; p_string_cell!=NULL; 
		p_string_cell=p_string_cell->next)
	{
		printf("%-31s",p_string_cell->value);
	}
}

void intEqual(t_table *table,int value,int i_column)
{
	int i_line;
	t_intLine *p_int_line;
	t_intCell *p_int_cell;

	for(p_int_line=(t_intLine *)table->lines; p_int_line!=NULL; 
		p_int_line=p_int_line->next)
	{
		i_line=0;
		for(p_int_cell=p_int_line->cells; p_int_cell!=NULL; 
			p_int_cell=p_int_cell->next)
		{
			if(p_int_cell->value==value && i_line==i_column)
			{
				printIntLine(p_int_line->cells);
				printf("\n");
			}
			i_line++;
		}
		
	}
}

void intGreater(t_table *table,int value,int i_column)
{
	int i_line;
	t_intLine *p_int_line;
	t_intCell *p_int_cell;
	for(p_int_line=(t_intLine *)table->lines; p_int_line!=NULL; 
		p_int_line=p_int_line->next)
	{
		i_line=0;
		for(p_int_cell=p_int_line->cells; p_int_cell!=NULL; 
			p_int_cell=p_int_cell->next)
		{
			if(p_int_cell->value>value && i_line==i_column)
			{
				printIntLine(p_int_line->cells);
				printf("\n");
			}
			i_line++;
		}
	}
}

void intLess(t_table *table,int value,int i_column)
{
	int i_line;
	t_intLine *p_int_line;
	t_intCell *p_int_cell;

	for(p_int_line=(t_intLine *)table->lines; p_int_line!=NULL; 
		p_int_line=p_int_line->next)
	{
		i_line=0;
		for(p_int_cell=p_int_line->cells; p_int_cell!=NULL; 
			p_int_cell=p_int_cell->next)
		{
			if(p_int_cell->value<value && i_line==i_column)
			{
				printIntLine(p_int_line->cells);
				printf("\n");
			}
			i_line++;
		}
	}
}

void intGreaterEqual(t_table *table,int value,int i_column)
{
	int i_line;
	t_intLine *p_int_line;
	t_intCell *p_int_cell;

	for(p_int_line=(t_intLine *)table->lines; p_int_line!=NULL; 
		p_int_line=p_int_line->next)
	{
		i_line=0;
		for(p_int_cell=p_int_line->cells; p_int_cell!=NULL; 
			p_int_cell=p_int_cell->next)
		{
			if(p_int_cell->value>=value && i_line==i_column)
			{
				printIntLine(p_int_line->cells);
				printf("\n");
			}
			i_line++;
		}
	}
}

void intLessEqual(t_table *table,int value,int i_column)
{
	int i_line;
	t_intLine *p_int_line;
	t_intCell *p_int_cell;

	for(p_int_line=(t_intLine *)table->lines; p_int_line!=NULL; 
		p_int_line=p_int_line->next)
	{
		i_line=0;
		for(p_int_cell=p_int_line->cells; p_int_cell!=NULL; 
			p_int_cell=p_int_cell->next)
		{
			if(p_int_cell->value<=value && i_line==i_column)
			{
				printIntLine(p_int_line->cells);
				printf("\n");
			}
			i_line++;
		}
	}
}

void intNotEqual(t_table *table,int value,int i_column)
{
	int i_line;
	t_intLine *p_int_line;
	t_intCell *p_int_cell;

	for(p_int_line=(t_intLine *)table->lines; p_int_line!=NULL; 
		p_int_line=p_int_line->next)
	{
		i_line=0;
		for(p_int_cell=p_int_line->cells; p_int_cell!=NULL; 
			p_int_cell=p_int_cell->next)
		{
			if(p_int_cell->value!=value && i_line==i_column)
			{
				printIntLine(p_int_line->cells);
				printf("\n");
			}
			i_line++;
		}
	}
}

void floatEqual(t_table *table,float value,int i_column)
{
	int i_line;
	t_floatLine *p_int_line;
	t_floatCell *p_int_cell;

	for(p_int_line=(t_floatLine *)table->lines; p_int_line!=NULL; 
		p_int_line=p_int_line->next)
	{
		i_line=0;
		for(p_int_cell=p_int_line->cells; p_int_cell!=NULL; 
			p_int_cell=p_int_cell->next)
		{
			if(p_int_cell->value==value && i_line==i_column)
			{
				printFloatLine(p_int_line->cells);
				printf("\n");
			}
			i_line++;
		}
	}
}

void floatGreater(t_table *table,float value,int i_column)
{
	int i_line;
	t_floatLine *p_int_line;
	t_floatCell *p_int_cell;

	for(p_int_line=(t_floatLine *)table->lines; p_int_line!=NULL; 
		p_int_line=p_int_line->next)
	{
		i_line=0;
		for(p_int_cell=p_int_line->cells; p_int_cell!=NULL; 
			p_int_cell=p_int_cell->next)
		{
			if(p_int_cell->value>value && i_line==i_column)
			{
				printFloatLine(p_int_line->cells);
				printf("\n");
			}
			i_line++;
		}
	}
}

void floatLess(t_table *table,float value,int i_column)
{
	int i_line;
	t_floatLine *p_int_line;
	t_floatCell *p_int_cell;

	for(p_int_line=(t_floatLine *)table->lines; p_int_line!=NULL; 
		p_int_line=p_int_line->next)
	{
		i_line=0;
		for(p_int_cell=p_int_line->cells; p_int_cell!=NULL; 
			p_int_cell=p_int_cell->next)
		{
			if(p_int_cell->value<value && i_line==i_column)
			{
				printFloatLine(p_int_line->cells);
				printf("\n");
			}
			i_line++;
		}
	}
}

void floatGreaterEqual(t_table *table,float value,int i_column)
{
	int i_line;
	t_floatLine *p_int_line;
	t_floatCell *p_int_cell;

	for(p_int_line=(t_floatLine *)table->lines; p_int_line!=NULL; 
		p_int_line=p_int_line->next)
	{
		i_line=0;
		for(p_int_cell=p_int_line->cells; p_int_cell!=NULL; 
			p_int_cell=p_int_cell->next)
		{
			if(p_int_cell->value>=value && i_line==i_column)
			{
				printFloatLine(p_int_line->cells);
				printf("\n");
			}
			i_line++;
		}
	}
}

void floatLessEqual(t_table *table,float value,int i_column)
{
	int i_line;
	t_floatLine *p_int_line;
	t_floatCell *p_int_cell;

	for(p_int_line=(t_floatLine *)table->lines; p_int_line!=NULL; 
		p_int_line=p_int_line->next)
	{
		i_line=0;
		for(p_int_cell=p_int_line->cells; p_int_cell!=NULL; 
			p_int_cell=p_int_cell->next)
		{
			if(p_int_cell->value<=value && i_line==i_column)
			{
				printFloatLine(p_int_line->cells);
				printf("\n");
			}
			i_line++;
		}
	}
}

void floatNotEqual(t_table *table,float value,int i_column)
{
	int i_line;
	t_floatLine *p_int_line;
	t_floatCell *p_int_cell;

	for(p_int_line=(t_floatLine *)table->lines; p_int_line!=NULL; 
		p_int_line=p_int_line->next)
	{
		i_line=0;
		for(p_int_cell=p_int_line->cells; p_int_cell!=NULL; 
			p_int_cell=p_int_cell->next)
		{
			if(p_int_cell->value!=value && i_line==i_column)
			{
				printFloatLine(p_int_line->cells);
				printf("\n");
			}
			i_line++;
		}
	}
}

void stringEqual(t_table *table,char *value,int i_column)
{
	int i_line;
	t_stringLine *p_int_line;
	t_stringCell *p_int_cell;

	for(p_int_line=(t_stringLine *)table->lines; p_int_line!=NULL; 
		p_int_line=p_int_line->next)
	{
		i_line=0;
		for(p_int_cell=p_int_line->cells; p_int_cell!=NULL; 
			p_int_cell=p_int_cell->next)
		{
			if(strcmp(p_int_cell->value,value)==0 && i_line==i_column)
			{
				printStringLine(p_int_line->cells);
				printf("\n");
			}
			i_line++;
		}
	}
}

void stringGreater(t_table *table,char *value,int i_column)
{
	int i_line;
	t_stringLine *p_int_line;
	t_stringCell *p_int_cell;

	for(p_int_line=(t_stringLine *)table->lines; p_int_line!=NULL; 
		p_int_line=p_int_line->next)
	{
		i_line=0;
		for(p_int_cell=p_int_line->cells; p_int_cell!=NULL; 
			p_int_cell=p_int_cell->next)
		{
			if(strcmp(p_int_cell->value,value)>0 && i_line==i_column)
			{
				printStringLine(p_int_line->cells);
				printf("\n");
			}
			i_line++;
		}
	}
}

void stringLess(t_table *table,char *value,int i_column)
{
	int i_line;
	t_stringLine *p_int_line;
	t_stringCell *p_int_cell;

	for(p_int_line=(t_stringLine *)table->lines; p_int_line!=NULL; 
		p_int_line=p_int_line->next)
	{
		i_line=0;
		for(p_int_cell=p_int_line->cells; p_int_cell!=NULL; 
			p_int_cell=p_int_cell->next)
		{
			if(strcmp(p_int_cell->value,value)<0 && i_line==i_column)
			{
				printStringLine(p_int_line->cells);
				printf("\n");
			}
			i_line++;
		}
	}
}

void stringGreaterEqual(t_table *table,char *value,int i_column)
{
	int i_line;
	t_stringLine *p_int_line;
	t_stringCell *p_int_cell;

	for(p_int_line=(t_stringLine *)table->lines; p_int_line!=NULL; 
		p_int_line=p_int_line->next)
	{
		i_line=0;
		for(p_int_cell=p_int_line->cells; p_int_cell!=NULL; 
			p_int_cell=p_int_cell->next)
		{
			if(strcmp(p_int_cell->value,value)>=0 && i_line==i_column)
			{
				printStringLine(p_int_line->cells);
				printf("\n");
			}
			i_line++;
		}
	}
}

void stringLessEqual(t_table *table,char *value,int i_column)
{
	int i_line;
	t_stringLine *p_int_line;
	t_stringCell *p_int_cell;

	for(p_int_line=(t_stringLine *)table->lines; p_int_line!=NULL; 
		p_int_line=p_int_line->next)
	{
		i_line=0;
		for(p_int_cell=p_int_line->cells; p_int_cell!=NULL; 
			p_int_cell=p_int_cell->next)
		{
			if(strcmp(p_int_cell->value,value)<=0 && i_line==i_column)
			{
				printStringLine(p_int_line->cells);
				printf("\n");
			}
			i_line++;
		}
	}
}

void stringNotEqual(t_table *table,char *value,int i_column)
{
	int i_line;
	t_stringLine *p_int_line;
	t_stringCell *p_int_cell;

	for(p_int_line=(t_stringLine *)table->lines; p_int_line!=NULL; 
		p_int_line=p_int_line->next)
	{
		i_line=0;
		for(p_int_cell=p_int_line->cells; p_int_cell!=NULL; 
			p_int_cell=p_int_cell->next)
		{
			if(strcmp(p_int_cell->value,value)!=0 && i_line==i_column)
			{
				printStringLine(p_int_line->cells);
				printf("\n");
			}
			i_line++;
		}
	}
}

void SEARCH(t_db *database,char *arguments)
{
	//extrage argumente
	//intra pe ramura corecta
	//cauta coloana si retine indice
	//itereaza prin tabel,iar atunci cand indicele celulei
	//este egal cu indicele de la coloana verifica relatia
	//afiseaza tabelu si linia

	char *cut=strtok(arguments," \n");//numele comenzii
	cut=strtok(NULL," \n");//numele tabelului
	
	t_table *p_table;

	int i_column=0;

	for(p_table=database->tables; p_table!=NULL; p_table=p_table->next)
	{
		if(strcmp(p_table->name,cut)==0)
		{
			break;
		}
	}

	if(p_table==NULL)
	{
		printf("Table \"%s\" not found in database.\n",cut);
	}
	else
	{
		if(p_table->type==INT)
		{
			cut=strtok(NULL," \n");//numele coloanei
			t_column *p_column;

			for(p_column=p_table->columns; p_column!=NULL; 
				p_column=p_column->next)
			{
				if(strcmp(p_column->name,cut)==0)
				{
					break;
				}
				i_column++;
			}

			if(p_column==NULL)
			{
				printf("Table \"%s\" does not contain column \"%s\".\n",p_table->name,cut);
			}
			else
			{
				cut=strtok(NULL," \n");//relatia

				if(strcmp(cut,"==")==0)
				{
					cut=strtok(NULL," \n");//valoarea
					int value=atoi(cut);
					printf("TABLE: %s\n",p_table->name);
					printColumns(p_table);
					intEqual(p_table,value,i_column);
					printf("\n");
				}

				if(strcmp(cut,"!=")==0)
				{
					cut=strtok(NULL," \n");//valoarea
					int value=atoi(cut);
					printf("TABLE: %s\n",p_table->name);
					printColumns(p_table);
					intNotEqual(p_table,value,i_column);
					printf("\n");
				}

				if(strcmp(cut,">")==0)
				{
					cut=strtok(NULL," \n");//valoarea
					int value=atoi(cut);
					printf("TABLE: %s\n",p_table->name);
					printColumns(p_table);
					intGreater(p_table,value,i_column);
					printf("\n");
				}

				if(strcmp(cut,"<")==0)
				{
					cut=strtok(NULL," \n");//valoarea
					int value=atoi(cut);
					printf("TABLE: %s\n",p_table->name);
					printColumns(p_table);
					intLess(p_table,value,i_column);
					printf("\n");
				}

				if(strcmp(cut,">=")==0)
				{
					cut=strtok(NULL," \n");//valoarea
					int value=atoi(cut);
					printf("TABLE: %s\n",p_table->name);
					printColumns(p_table);
					intGreaterEqual(p_table,value,i_column);
					printf("\n");
				}

				if(strcmp(cut,"<=")==0)
				{
					cut=strtok(NULL," \n");//valoarea
					int value=atoi(cut);
					printf("TABLE: %s\n",p_table->name);
					printColumns(p_table);
					intLessEqual(p_table,value,i_column);
					printf("\n");
				}
			}
		}
		if(p_table->type==FLOAT)
		{
			cut=strtok(NULL," \n");//numele coloanei
			t_column *p_column;

			for(p_column=p_table->columns; p_column!=NULL; 
				p_column=p_column->next)
			{
				if(strcmp(p_column->name,cut)==0)
				{
					break;
				}
				i_column++;
			}

			if(p_column==NULL)
			{
				printf("Table \"%s\" does not contain column \"%s\".\n",p_table->name,cut);
			}
			else
			{
				cut=strtok(NULL," \n");//relatia

				if(strcmp(cut,"==")==0)
				{
					cut=strtok(NULL," \n");//valoarea
					float value=atof(cut);
					printf("TABLE: %s\n",p_table->name);
					printColumns(p_table);
					floatEqual(p_table,value,i_column);
					printf("\n");
				}

				if(strcmp(cut,"!=")==0)
				{
					cut=strtok(NULL," \n");//valoarea
					float value=atof(cut);
					printf("TABLE: %s\n",p_table->name);
					printColumns(p_table);
					floatNotEqual(p_table,value,i_column);
					printf("\n");
				}

				if(strcmp(cut,">")==0)
				{
					cut=strtok(NULL," \n");//valoarea
					float value=atof(cut);
					printf("TABLE: %s\n",p_table->name);
					printColumns(p_table);
					floatGreater(p_table,value,i_column);
					printf("\n");
				}

				if(strcmp(cut,"<")==0)
				{
					cut=strtok(NULL," \n");//valoarea
					float value=atof(cut);
					printf("TABLE: %s\n",p_table->name);
					printColumns(p_table);
					floatLess(p_table,value,i_column);
					printf("\n");
				}

				if(strcmp(cut,">=")==0)
				{
					cut=strtok(NULL," \n");//valoarea
					float value=atof(cut);
					printf("TABLE: %s\n",p_table->name);
					printColumns(p_table);
					floatGreaterEqual(p_table,value,i_column);
					printf("\n");
				}

				if(strcmp(cut,"<=")==0)
				{
					cut=strtok(NULL," \n");//valoarea
					float value=atof(cut);
					printf("TABLE: %s\n",p_table->name);
					printColumns(p_table);
					floatLessEqual(p_table,value,i_column);
					printf("\n");
				}
			}
		}
		if(p_table->type==STRING)
		{
			cut=strtok(NULL," \n");//numele coloanei
			t_column *p_column;

			for(p_column=p_table->columns; p_column!=NULL; 
				p_column=p_column->next)
			{
				if(strcmp(p_column->name,cut)==0)
				{
					break;
				}
				i_column++;
			}

			if(p_column==NULL)
			{
				printf("Table \"%s\" does not contain column \"%s\".\n",p_table->name,cut);
			}
			else
			{
				cut=strtok(NULL," \n");//relatia

				if(strcmp(cut,"==")==0)
				{
					cut=strtok(NULL," \n");//valoarea
					printf("TABLE: %s\n",p_table->name);
					printColumns(p_table);
					stringEqual(p_table,cut,i_column);
					printf("\n");
				}

				if(strcmp(cut,"!=")==0)
				{
					cut=strtok(NULL," \n");//valoarea
					printf("TABLE: %s\n",p_table->name);
					printColumns(p_table);
					stringNotEqual(p_table,cut,i_column);
					printf("\n");
				}

				if(strcmp(cut,">")==0)
				{
					cut=strtok(NULL," \n");//valoarea
					printf("TABLE: %s\n",p_table->name);
					printColumns(p_table);
					stringGreater(p_table,cut,i_column);
					printf("\n");
				}

				if(strcmp(cut,"<")==0)
				{
					cut=strtok(NULL," \n");//valoarea
					printf("TABLE: %s\n",p_table->name);
					printColumns(p_table);
					stringLess(p_table,cut,i_column);
					printf("\n");
				}

				if(strcmp(cut,">=")==0)
				{
					cut=strtok(NULL," \n");//valoarea
					printf("TABLE: %s\n",p_table->name);
					printColumns(p_table);
					stringGreaterEqual(p_table,cut,i_column);
					printf("\n");
				}

				if(strcmp(cut,"<=")==0)
				{
					cut=strtok(NULL," \n");//valoarea
					printf("TABLE: %s\n",p_table->name);
					printColumns(p_table);
					stringLessEqual(p_table,cut,i_column);
					printf("\n");
				}
			}
		}
	}
}

void deleteIntCell(t_intCell **int_cell)
{
	t_intCell *p=*int_cell;

	while(p!=NULL)
	{
		t_intCell *aux=p;
		p=p->next;
		free(aux);
	}
	
	*int_cell=NULL;
}

void deleteFloatCell(t_floatCell **float_cell)
{
	t_floatCell *p=*float_cell;

	while(p!=NULL)
	{
		t_floatCell *aux=p;
		p=p->next;
		free(aux);
	}
	
	*float_cell=NULL;
}

void deleteStringCell(t_stringCell **string_cell)
{
	t_stringCell *p=*string_cell;

	while(p!=NULL)
	{
		t_stringCell *aux=p;
		p=p->next;
		free(aux->value);
		free(aux);
	}
	
	*string_cell=NULL;
}

void intEqualDelete(t_table *table,int value,int i_column)
{
	int i_line;
	int found;
	t_intLine *p_int_line;
	t_intCell *p_int_cell;
	t_intLine *ant=NULL;
	t_intLine *aux;

	for(p_int_line=(t_intLine *)table->lines; p_int_line!=NULL;)
	{
		found=0;
		i_line=0;
		for(p_int_cell=p_int_line->cells; p_int_cell!=NULL; 
			p_int_cell=p_int_cell->next)
		{
			if(p_int_cell->value==value && i_line==i_column)
			{
				found=1;
				deleteIntCell(&p_int_line->cells);
			}
			i_line++;
		}

		if(found==1)
		{
			aux=p_int_line;
			p_int_line=p_int_line->next;
			if(ant)
				ant->next=p_int_line;
			else
				table->lines=p_int_line;
			free(aux);
		}
		else
		{
			ant=p_int_line;
			p_int_line=p_int_line->next;
		}
	}
}

void intGreaterDelete(t_table *table,int value,int i_column)
{
	int i_line;
	int found;
	t_intLine *p_int_line;
	t_intCell *p_int_cell;
	t_intLine *ant=NULL;
	t_intLine *aux;

	for(p_int_line=(t_intLine *)table->lines; p_int_line!=NULL;)
	{
		found=0;
		i_line=0;
		for(p_int_cell=p_int_line->cells; p_int_cell!=NULL; 
			p_int_cell=p_int_cell->next)
		{
			if(p_int_cell->value>value && i_line==i_column)
			{
				found=1;
				deleteIntCell(&p_int_line->cells);
			}
			i_line++;
		}

		if(found==1)
		{
			aux=p_int_line;
			p_int_line=p_int_line->next;
			if(ant)
				ant->next=p_int_line;
			else
				table->lines=p_int_line;
			free(aux);
		}
		else
		{
			ant=p_int_line;
			p_int_line=p_int_line->next;
		}
	}
}


void intLessDelete(t_table *table,int value,int i_column)
{
	int i_line;
	int found;
	t_intLine *p_int_line;
	t_intCell *p_int_cell;
	t_intLine *ant=NULL;
	t_intLine *aux;

	for(p_int_line=(t_intLine *)table->lines; p_int_line!=NULL;)
	{
		found=0;
		i_line=0;
		for(p_int_cell=p_int_line->cells; p_int_cell!=NULL; 
			p_int_cell=p_int_cell->next)
		{
			if(p_int_cell->value<value && i_line==i_column)
			{
				found=1;
				deleteIntCell(&p_int_line->cells);
			}
			i_line++;
		}

		if(found==1)
		{
			aux=p_int_line;
			p_int_line=p_int_line->next;
			if(ant)
				ant->next=p_int_line;
			else
				table->lines=p_int_line;
			free(aux);
		}
		else
		{
			ant=p_int_line;
			p_int_line=p_int_line->next;
		}
	}
}


void intGreaterEqualDelete(t_table *table,int value,int i_column)
{
	int i_line;
	int found;
	t_intLine *p_int_line;
	t_intCell *p_int_cell;
	t_intLine *ant=NULL;
	t_intLine *aux;

	for(p_int_line=(t_intLine *)table->lines; p_int_line!=NULL;)
	{
		found=0;
		i_line=0;
		for(p_int_cell=p_int_line->cells; p_int_cell!=NULL; 
			p_int_cell=p_int_cell->next)
		{
			if(p_int_cell->value>=value && i_line==i_column)
			{
				found=1;
				deleteIntCell(&p_int_line->cells);
			}
			i_line++;
		}

		if(found==1)
		{
			aux=p_int_line;
			p_int_line=p_int_line->next;
			if(ant)
				ant->next=p_int_line;
			else
				table->lines=p_int_line;
			free(aux);
		}
		else
		{
			ant=p_int_line;
			p_int_line=p_int_line->next;
		}
	}
}


void intLessEqualDelete(t_table *table,int value,int i_column)
{
	int i_line;
	int found;
	t_intLine *p_int_line;
	t_intCell *p_int_cell;
	t_intLine *ant=NULL;
	t_intLine *aux;

	for(p_int_line=(t_intLine *)table->lines; p_int_line!=NULL;)
	{
		found=0;
		i_line=0;
		for(p_int_cell=p_int_line->cells; p_int_cell!=NULL; 
			p_int_cell=p_int_cell->next)
		{
			if(p_int_cell->value<=value && i_line==i_column)
			{
				found=1;
				deleteIntCell(&p_int_line->cells);
			}
			i_line++;
		}

		if(found==1)
		{
			aux=p_int_line;
			p_int_line=p_int_line->next;
			if(ant)
				ant->next=p_int_line;
			else
				table->lines=p_int_line;
			free(aux);
		}
		else
		{
			ant=p_int_line;
			p_int_line=p_int_line->next;
		}
	}
}


void intNotEqualDelete(t_table *table,int value,int i_column)
{
	int i_line;
	int found;
	t_intLine *p_int_line;
	t_intCell *p_int_cell;
	t_intLine *ant=NULL;
	t_intLine *aux;

	for(p_int_line=(t_intLine *)table->lines; p_int_line!=NULL;)
	{
		found=0;
		i_line=0;
		for(p_int_cell=p_int_line->cells; p_int_cell!=NULL; 
			p_int_cell=p_int_cell->next)
		{
			if(p_int_cell->value!=value && i_line==i_column)
			{
				found=1;
				deleteIntCell(&p_int_line->cells);
			}
			i_line++;
		}

		if(found==1)
		{
			aux=p_int_line;
			p_int_line=p_int_line->next;
			if(ant)
				ant->next=p_int_line;
			else
				table->lines=p_int_line;
			free(aux);
		}
		else
		{
			ant=p_int_line;
			p_int_line=p_int_line->next;
		}
	}
}


void floatEqualDelete(t_table *table,float value,int i_column)
{
	int i_line;
	int found;
	t_floatLine *p_int_line;
	t_floatCell *p_int_cell;
	t_floatLine *ant=NULL;
	t_floatLine *aux;

	for(p_int_line=(t_floatLine *)table->lines; p_int_line!=NULL;)
	{
		found=0;
		i_line=0;
		for(p_int_cell=p_int_line->cells; p_int_cell!=NULL; 
			p_int_cell=p_int_cell->next)
		{
			if(p_int_cell->value==value && i_line==i_column)
			{
				found=1;
				deleteFloatCell(&p_int_line->cells);
			}
			i_line++;
		}

		if(found==1)
		{
			aux=p_int_line;
			p_int_line=p_int_line->next;
			if(ant)
				ant->next=p_int_line;
			else
				table->lines=p_int_line;
			free(aux);
		}
		else
		{
			ant=p_int_line;
			p_int_line=p_int_line->next;
		}
	}
}

void floatGreaterDelete(t_table *table,float value,int i_column)
{
	int i_line;
	int found;
	t_floatLine *p_int_line;
	t_floatCell *p_int_cell;
	t_floatLine *ant=NULL;
	t_floatLine *aux;

	for(p_int_line=(t_floatLine *)table->lines; p_int_line!=NULL;)
	{
		found=0;
		i_line=0;
		for(p_int_cell=p_int_line->cells; p_int_cell!=NULL; 
			p_int_cell=p_int_cell->next)
		{
			if(p_int_cell->value>value && i_line==i_column)
			{
				found=1;
				deleteFloatCell(&p_int_line->cells);
			}
			i_line++;
		}

		if(found==1)
		{
			aux=p_int_line;
			p_int_line=p_int_line->next;
			if(ant)
				ant->next=p_int_line;
			else
				table->lines=p_int_line;
			free(aux);
		}
		else
		{
			ant=p_int_line;
			p_int_line=p_int_line->next;
		}
	}
}

void floatLessDelete(t_table *table,float value,int i_column)
{
	int i_line;
	int found;
	t_floatLine *p_int_line;
	t_floatCell *p_int_cell;
	t_floatLine *ant=NULL;
	t_floatLine *aux;

	for(p_int_line=(t_floatLine *)table->lines; p_int_line!=NULL;)
	{
		found=0;
		i_line=0;
		for(p_int_cell=p_int_line->cells; p_int_cell!=NULL; 
			p_int_cell=p_int_cell->next)
		{
			if(p_int_cell->value<value && i_line==i_column)
			{
				found=1;
				deleteFloatCell(&p_int_line->cells);
			}
			i_line++;
		}

		if(found==1)
		{
			aux=p_int_line;
			p_int_line=p_int_line->next;
			if(ant)
				ant->next=p_int_line;
			else
				table->lines=p_int_line;
			free(aux);
		}
		else
		{
			ant=p_int_line;
			p_int_line=p_int_line->next;
		}
	}
}

void floatGreaterEqualDelete(t_table *table,float value,int i_column)
{
	int i_line;
	int found;
	t_floatLine *p_int_line;
	t_floatCell *p_int_cell;
	t_floatLine *ant=NULL;
	t_floatLine *aux;

	for(p_int_line=(t_floatLine *)table->lines; p_int_line!=NULL;)
	{
		found=0;
		i_line=0;
		for(p_int_cell=p_int_line->cells; p_int_cell!=NULL; 
			p_int_cell=p_int_cell->next)
		{
			if(p_int_cell->value>=value && i_line==i_column)
			{
				found=1;
				deleteFloatCell(&p_int_line->cells);
			}
			i_line++;
		}

		if(found==1)
		{
			aux=p_int_line;
			p_int_line=p_int_line->next;
			if(ant)
				ant->next=p_int_line;
			else
				table->lines=p_int_line;
			free(aux);
		}
		else
		{
			ant=p_int_line;
			p_int_line=p_int_line->next;
		}
	}
}

void floatLessEqualDelete(t_table *table,float value,int i_column)
{
	int i_line;
	int found;
	t_floatLine *p_int_line;
	t_floatCell *p_int_cell;
	t_floatLine *ant=NULL;
	t_floatLine *aux;

	for(p_int_line=(t_floatLine *)table->lines; p_int_line!=NULL;)
	{
		found=0;
		i_line=0;
		for(p_int_cell=p_int_line->cells; p_int_cell!=NULL; 
			p_int_cell=p_int_cell->next)
		{
			if(p_int_cell->value<=value && i_line==i_column)
			{
				found=1;
				deleteFloatCell(&p_int_line->cells);
			}
			i_line++;
		}

		if(found==1)
		{
			aux=p_int_line;
			p_int_line=p_int_line->next;
			if(ant)
				ant->next=p_int_line;
			else
				table->lines=p_int_line;
			free(aux);
		}
		else
		{
			ant=p_int_line;
			p_int_line=p_int_line->next;
		}
	}
}

void floatNotEqualDelete(t_table *table,float value,int i_column)
{
	int i_line;
	int found;
	t_floatLine *p_int_line;
	t_floatCell *p_int_cell;
	t_floatLine *ant=NULL;
	t_floatLine *aux;

	for(p_int_line=(t_floatLine *)table->lines; p_int_line!=NULL;)
	{
		found=0;
		i_line=0;
		for(p_int_cell=p_int_line->cells; p_int_cell!=NULL; 
			p_int_cell=p_int_cell->next)
		{
			if(p_int_cell->value!=value && i_line==i_column)
			{
				found=1;
				deleteFloatCell(&p_int_line->cells);
			}
			i_line++;
		}

		if(found==1)
		{
			aux=p_int_line;
			p_int_line=p_int_line->next;
			if(ant)
				ant->next=p_int_line;
			else
				table->lines=p_int_line;
			free(aux);
		}
		else
		{
			ant=p_int_line;
			p_int_line=p_int_line->next;
		}
	}
}

void stringEqualDelete(t_table *table,char *value,int i_column)
{
	int i_line;
	int found;
	t_stringLine *p_int_line;
	t_stringCell *p_int_cell;
	t_stringLine *ant=NULL;
	t_stringLine *aux;

	for(p_int_line=(t_stringLine *)table->lines; p_int_line!=NULL;)
	{
		found=0;
		i_line=0;
		for(p_int_cell=p_int_line->cells; p_int_cell!=NULL; 
			p_int_cell=p_int_cell->next)
		{
			if(strcmp(p_int_cell->value,value)==0 && i_line==i_column)
			{
				found=1;
				deleteStringCell(&p_int_line->cells);
			}
			i_line++;
		}

		if(found==1)
		{
			aux=p_int_line;
			p_int_line=p_int_line->next;
			if(ant)
				ant->next=p_int_line;
			else
				table->lines=p_int_line;
			free(aux);
		}
		else
		{
			ant=p_int_line;
			p_int_line=p_int_line->next;
		}
	}
}

void stringGreaterDelete(t_table *table,char *value,int i_column)
{
	int i_line;
	int found;
	t_stringLine *p_int_line;
	t_stringCell *p_int_cell;
	t_stringLine *ant=NULL;
	t_stringLine *aux;

	for(p_int_line=(t_stringLine *)table->lines; p_int_line!=NULL;)
	{
		found=0;
		i_line=0;
		for(p_int_cell=p_int_line->cells; p_int_cell!=NULL; 
			p_int_cell=p_int_cell->next)
		{
			if(strcmp(p_int_cell->value,value)>0 && i_line==i_column)
			{
				found=1;
				deleteStringCell(&p_int_line->cells);
			}
			i_line++;
		}

		if(found==1)
		{
			aux=p_int_line;
			p_int_line=p_int_line->next;
			if(ant)
				ant->next=p_int_line;
			else
				table->lines=p_int_line;
			free(aux);
		}
		else
		{
			ant=p_int_line;
			p_int_line=p_int_line->next;
		}
	}
}

void stringLessDelete(t_table *table,char *value,int i_column)
{
	int i_line;
	int found;
	t_stringLine *p_int_line;
	t_stringCell *p_int_cell;
	t_stringLine *ant=NULL;
	t_stringLine *aux;

	for(p_int_line=(t_stringLine *)table->lines; p_int_line!=NULL;)
	{
		found=0;
		i_line=0;
		for(p_int_cell=p_int_line->cells; p_int_cell!=NULL; 
			p_int_cell=p_int_cell->next)
		{
			if(strcmp(p_int_cell->value,value)<0 && i_line==i_column)
			{
				found=1;
				deleteStringCell(&p_int_line->cells);
			}
			i_line++;
		}

		if(found==1)
		{
			aux=p_int_line;
			p_int_line=p_int_line->next;
			if(ant)
				ant->next=p_int_line;
			else
				table->lines=p_int_line;
			free(aux);
		}
		else
		{
			ant=p_int_line;
			p_int_line=p_int_line->next;
		}
	}
}

void stringGreaterEqualDelete(t_table *table,char *value,int i_column)
{
	int i_line;
	int found;
	t_stringLine *p_int_line;
	t_stringCell *p_int_cell;
	t_stringLine *ant=NULL;
	t_stringLine *aux;

	for(p_int_line=(t_stringLine *)table->lines; p_int_line!=NULL;)
	{
		found=0;
		i_line=0;
		for(p_int_cell=p_int_line->cells; p_int_cell!=NULL; 
			p_int_cell=p_int_cell->next)
		{
			if(strcmp(p_int_cell->value,value)>=0 && i_line==i_column)
			{
				found=1;
				deleteStringCell(&p_int_line->cells);
			}
			i_line++;
		}

		if(found==1)
		{
			aux=p_int_line;
			p_int_line=p_int_line->next;
			if(ant)
				ant->next=p_int_line;
			else
				table->lines=p_int_line;
			free(aux);
		}
		else
		{
			ant=p_int_line;
			p_int_line=p_int_line->next;
		}
	}
}

void stringLessEqualDelete(t_table *table,char *value,int i_column)
{
	int i_line;
	int found;
	t_stringLine *p_int_line;
	t_stringCell *p_int_cell;
	t_stringLine *ant=NULL;
	t_stringLine *aux;

	for(p_int_line=(t_stringLine *)table->lines; p_int_line!=NULL;)
	{
		found=0;
		i_line=0;
		for(p_int_cell=p_int_line->cells; p_int_cell!=NULL; 
			p_int_cell=p_int_cell->next)
		{
			if(strcmp(p_int_cell->value,value)<=0 && i_line==i_column)
			{
				found=1;
				deleteStringCell(&p_int_line->cells);
			}
			i_line++;
		}

		if(found==1)
		{
			aux=p_int_line;
			p_int_line=p_int_line->next;
			if(ant)
				ant->next=p_int_line;
			else
				table->lines=p_int_line;
			free(aux);
		}
		else
		{
			ant=p_int_line;
			p_int_line=p_int_line->next;
		}
	}
}

void stringNotEqualDelete(t_table *table,char *value,int i_column)
{
	int i_line;
	int found;
	t_stringLine *p_int_line;
	t_stringCell *p_int_cell;
	t_stringLine *ant=NULL;
	t_stringLine *aux;

	for(p_int_line=(t_stringLine *)table->lines; p_int_line!=NULL;)
	{
		found=0;
		i_line=0;
		for(p_int_cell=p_int_line->cells; p_int_cell!=NULL; 
			p_int_cell=p_int_cell->next)
		{
			if(strcmp(p_int_cell->value,value)!=0 && i_line==i_column)
			{
				found=1;
				deleteStringCell(&p_int_line->cells);
			}
			i_line++;
		}

		if(found==1)
		{
			aux=p_int_line;
			p_int_line=p_int_line->next;
			if(ant)
				ant->next=p_int_line;
			else
				table->lines=p_int_line;
			free(aux);
		}
		else
		{
			ant=p_int_line;
			p_int_line=p_int_line->next;
		}
	}
}

void DELETE(t_db *database,char *arguments)
{
	//extrage argumente
	//intra pe ramura corecta
	//cauta coloana si retine indice
	//itereaza prin tabel,iar atunci cand indicele celulei
	//este egal cu indicele de la coloana verifica relatia
	//sterge linia

	char *cut=strtok(arguments," \n");//numele comenzii
	cut=strtok(NULL," \n");//numele tabelului
	
	t_table *p_table;

	int i_column=0;

	for(p_table=database->tables; p_table!=NULL; p_table=p_table->next)
	{
		if(strcmp(p_table->name,cut)==0)
		{
			break;
		}
	}

	if(p_table==NULL)
	{
		printf("Table \"%s\" not found in database.\n",cut);
	}
	else
	{
		if(p_table->type==INT)
		{
			cut=strtok(NULL," \n");//numele coloanei
			t_column *p_column;

			for(p_column=p_table->columns; p_column!=NULL; 
				p_column=p_column->next)
			{
				if(strcmp(p_column->name,cut)==0)
				{
					break;
				}
				i_column++;
			}

			if(p_column==NULL)
			{
				printf("Table \"%s\" does not contain column \"%s\".\n",p_table->name,cut);
			}
			else
			{
				cut=strtok(NULL," \n");//relatia

				if(strcmp(cut,"==")==0)
				{
					cut=strtok(NULL," \n");//valoarea
					int value=atoi(cut);
					intEqualDelete(p_table,value,i_column);
				}

				if(strcmp(cut,"!=")==0)
				{
					cut=strtok(NULL," \n");//valoarea
					int value=atoi(cut);
					intNotEqualDelete(p_table,value,i_column);
				}

				if(strcmp(cut,">")==0)
				{
					cut=strtok(NULL," \n");//valoarea
					int value=atoi(cut);
					intGreaterDelete(p_table,value,i_column);
				}

				if(strcmp(cut,"<")==0)
				{
					cut=strtok(NULL," \n");//valoarea
					int value=atoi(cut);
					intLessDelete(p_table,value,i_column);
				}

				if(strcmp(cut,">=")==0)
				{
					cut=strtok(NULL," \n");//valoarea
					int value=atoi(cut);
					intGreaterEqualDelete(p_table,value,i_column);
				}

				if(strcmp(cut,"<=")==0)
				{
					cut=strtok(NULL," \n");//valoarea
					int value=atoi(cut);
					intLessEqualDelete(p_table,value,i_column);
				}
			}
		}
		if(p_table->type==FLOAT)
		{
			cut=strtok(NULL," \n");//numele coloanei
			t_column *p_column;

			for(p_column=p_table->columns; p_column!=NULL; 
				p_column=p_column->next)
			{
				if(strcmp(p_column->name,cut)==0)
				{
					break;
				}
				i_column++;
			}

			if(p_column==NULL)
			{
				printf("Table \"%s\" does not contain column \"%s\".\n",p_table->name,cut);
			}
			else
			{
				cut=strtok(NULL," \n");//relatia

				if(strcmp(cut,"==")==0)
				{
					cut=strtok(NULL," \n");//valoarea
					float value=atof(cut);
					floatEqualDelete(p_table,value,i_column);
				}

				if(strcmp(cut,"!=")==0)
				{
					cut=strtok(NULL," \n");//valoarea
					float value=atof(cut);
					floatNotEqualDelete(p_table,value,i_column);
				}

				if(strcmp(cut,">")==0)
				{
					cut=strtok(NULL," \n");//valoarea
					float value=atof(cut);
					floatGreaterDelete(p_table,value,i_column);
				}

				if(strcmp(cut,"<")==0)
				{
					cut=strtok(NULL," \n");//valoarea
					float value=atof(cut);
					floatLessDelete(p_table,value,i_column);
				}

				if(strcmp(cut,">=")==0)
				{
					cut=strtok(NULL," \n");//valoarea
					float value=atof(cut);
					floatGreaterEqualDelete(p_table,value,i_column);
				}

				if(strcmp(cut,"<=")==0)
				{
					cut=strtok(NULL," \n");//valoarea
					float value=atof(cut);
					floatLessEqualDelete(p_table,value,i_column);
				}
			}
		}
		if(p_table->type==STRING)
		{
			cut=strtok(NULL," \n");//numele coloanei
			t_column *p_column;

			for(p_column=p_table->columns; p_column!=NULL; 
				p_column=p_column->next)
			{
				if(strcmp(p_column->name,cut)==0)
				{
					break;
				}
				i_column++;
			}

			if(p_column==NULL)
			{
				printf("Table \"%s\" does not contain column \"%s\".\n",p_table->name,cut);
			}
			else
			{
				cut=strtok(NULL," \n");//relatia

				if(strcmp(cut,"==")==0)
				{
					cut=strtok(NULL," \n");//valoarea
					stringEqualDelete(p_table,cut,i_column);
				}

				if(strcmp(cut,"!=")==0)
				{
					cut=strtok(NULL," \n");//valoarea
					stringNotEqualDelete(p_table,cut,i_column);
				}

				if(strcmp(cut,">")==0)
				{
					cut=strtok(NULL," \n");//valoarea
					stringGreaterDelete(p_table,cut,i_column);
				}

				if(strcmp(cut,"<")==0)
				{
					cut=strtok(NULL," \n");//valoarea
					stringLessDelete(p_table,cut,i_column);
				}

				if(strcmp(cut,">=")==0)
				{
					cut=strtok(NULL," \n");//valoarea
					stringGreaterEqualDelete(p_table,cut,i_column);
				}

				if(strcmp(cut,"<=")==0)
				{
					cut=strtok(NULL," \n");//valoarea
					stringLessEqualDelete(p_table,cut,i_column);
				}
			}
		}
	}
}
