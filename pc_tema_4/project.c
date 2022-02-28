#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "include/project.h"



int *arrayProduct(int *array, int arrayLength) 
{
    int i=0;
    int j=0;
    int *p;
    p=(int*)calloc(arrayLength,sizeof(int));
    
    if(p==NULL)
        return NULL;
    
    for(i=0; i<arrayLength; i++)
    {
        p[i]=1;
        for(j=0; j<i; j++)
            p[i]=p[i]*array[j];
        for(j=arrayLength-1; j>i; j--)
            p[i]=p[i]*array[j];
    }

    
    return p;
}

int **rotateMatrix(int **matrix, int matrixSize) 
{
    int i=0;
    int j=0;
    int **p;
    
    p=calloc(matrixSize,sizeof(int *));
    for(i=0; i<matrixSize; i++)
        p[i]=calloc(matrixSize,sizeof(int));

    if(p==NULL)
        return NULL;
    
    for(i=0; i<matrixSize/2; i++)
    {
        for(j=i; j<matrixSize-i-1; j++)
        {
            p[matrixSize-1-j][i]=matrix[i][j];
            p[i][j]=matrix[j][matrixSize-1-i]; 
            p[j][matrixSize-1-i]=matrix[matrixSize-1-i][matrixSize-1-j]; 
            p[matrixSize-1-i][matrixSize-1-j]=matrix[matrixSize-1-j][i];
        }
    }

    if(matrixSize%2!=0)
        p[matrixSize/2][matrixSize/2]=matrix[matrixSize/2][matrixSize/2];

    return p;
}

int *subMatrixesSums(int **matrix, int queriesNo, int *queries) 
{
    int *p;
    p=calloc(queriesNo,sizeof(int));
    if(p==NULL)
        return NULL;
    int k=0; 
    int i,x,y;
    for(i=0; i<queriesNo*4; i=i+4)
    {
        for(x=queries[i]; x<=queries[i+2]; x++)
        {
            for(y=queries[i+1]; y<=queries[i+3]; y++)
            {
                p[k]=p[k]+matrix[x][y];
            }
        }
        k++;
    }

    return p;
}

TDriver *allocDriver(int ridesNo) 
{
    TDriver *p;
    p=calloc(1,sizeof(TDriver));
    if(p==NULL)
        return NULL;
    p->curse_efectuate=calloc(ridesNo,sizeof(TRide));
    return p;
}

TDriver **allocDrivers(int driversNo, int *driversRidesNo) 
{
    int i=0;
    TDriver **soferi;
    soferi=calloc(driversNo,sizeof(TDriver *));
    if(soferi==NULL)
        return NULL;
    for(i=0; i<driversNo; i++)
    {
        soferi[i]=allocDriver(driversRidesNo[i]);
    }
    return soferi;
}

TDriver **readDrivers(FILE *inputFile, int *driversNo) 
{
    
    
    int i,j;
    TDriver **soferi;

    
    fread(driversNo,sizeof(int),1,inputFile);
    
    
   
    int *p;
    p=calloc(*driversNo,sizeof(int));
    fread(p,sizeof(int),*driversNo,inputFile);
    
    soferi=allocDrivers(*driversNo,p);
     if(*soferi==NULL)
        return NULL;

    for(i=0; i<*driversNo; i++)
    {
        
        fread(soferi[i]->nume,sizeof(char),20,inputFile);
        
        fread(soferi[i]->numar_masina,sizeof(char),8,inputFile);
        
        fread(&(soferi[i]->x),sizeof(double),1,inputFile);
        
        fread(&(soferi[i]->y),sizeof(double),1,inputFile);
        
        soferi[i]->numar_curse=p[i];
        
        for(j=0; j<soferi[i]->numar_curse; j++)
        {
            fread(&(soferi[i]->curse_efectuate[j].x),sizeof(double),1,inputFile);
            fread(&(soferi[i]->curse_efectuate[j].y),sizeof(double),1,inputFile);
            fread(&(soferi[i]->curse_efectuate[j].starea_cursei),sizeof(char),1,inputFile);
        }
    }
    free(p);
    
    return soferi;
}

void printDrivers(FILE *outputFile, TDriver **drivers, int driversNo) 
{
    
    int i,j;
    for(i=0; i<driversNo; i++)
    {
        fwrite((drivers[i]->nume),sizeof(char),20,outputFile);
        fwrite((drivers[i]->numar_masina),sizeof(char),8,outputFile);
        fwrite(&(drivers[i]->x),sizeof(double),1,outputFile);
        fwrite(&(drivers[i]->y),sizeof(double),1,outputFile);
        
        for(j=0; j<drivers[i]->numar_curse; j++)
        {
            fwrite(&(drivers[i]->curse_efectuate[j].x),sizeof(double),1,outputFile);
            fwrite(&(drivers[i]->curse_efectuate[j].y),sizeof(double),1,outputFile);
            fwrite(&(drivers[i]->curse_efectuate[j].starea_cursei),sizeof(char),1,outputFile);
        }
    }
    
    
}

char *maxRatingDriverName(TDriver **drivers, int driversNo) 
{
    double maxim=-99999;
    int pozitie;
    int i,j;
    double suma_stele;
    double anulate;
    double desfasurare;
    double *rating;
    rating=calloc(driversNo,sizeof(double));
    if(rating==NULL)
        return NULL;
    for(i=0; i<driversNo; i++)
    {
        anulate=0;
        desfasurare=0;
        suma_stele=0;
        for(j=0; j<drivers[i]->numar_curse; j++)
        {
            suma_stele=suma_stele+((drivers[i]->curse_efectuate[j].starea_cursei)&7);
            if(((drivers[i]->curse_efectuate[j].starea_cursei)&8)==8)
                anulate++;
            if(((drivers[i]->curse_efectuate[j].starea_cursei)&16)==16)
                desfasurare++;

        }
        rating[i]=suma_stele/(drivers[i]->numar_curse-anulate-desfasurare);
        
    }

    for(i=0; i<driversNo; i++)
    {
        if(rating[i]>maxim)
        {
            maxim=rating[i];
            pozitie=i;
        }
        
    }
    free(rating);
    
    return drivers[pozitie]->nume;
}

void swapNumbers(double *a,double *b)
{
    double temp=*a;
    *a=*b;
    *b=temp;
}

void swapDrivers(TDriver *a,TDriver *b)
{
    TDriver temp=*a;
    *a=*b;
    *b=temp;
}

void bubbleSortDrivers(double *arr,int n,TDriver **soferi) 
{ 
   int i,j; 
   for (i=0; i<n-1; i++)       
        for(j=0; j<n-i-1; j++)  
           if(arr[j]>arr[j+1])
           {
                swapDrivers(soferi[j],soferi[j+1]);
                swapNumbers(&arr[j],&arr[j+1]); 
           }
}

TDriver **getClosestDrivers(TDriver **drivers, int driversNo, double desiredX,
    double desiredY, int resultsNo) 
{
    int i;
    double *p;
    TDriver **soferi;
    int a[resultsNo];
    soferi=allocDrivers(resultsNo,a);
    p=calloc(driversNo,sizeof(double));
    if(p==NULL)
        return NULL;
    for(i=0; i<driversNo; i++)
    {
        p[i]=sqrt(pow((desiredX-(drivers[i]->x)),2)+pow((desiredY-(drivers[i]->y)),2));
    }
    
    bubbleSortDrivers(p,driversNo,drivers);
    for(i=0; i<driversNo-1; i++)
    {
        if(p[i]==p[i+1] && strcmp(drivers[i],drivers[i+1])>0)
            swapDrivers(drivers[i],drivers[i+1]);
    }
    
    for(i=0; i<resultsNo; i++)
    {
        soferi[i]=drivers[i];
        
    }



    free(p);

    return soferi;
}

void freeDriver(TDriver *driver) 
{
    free(driver->curse_efectuate);
    free(driver);
}

void freeDrivers(TDriver **drivers, int driversNo) 
{
    int i;
    for(i=0; i<driversNo; i++)
        freeDriver(drivers[i]);
}

