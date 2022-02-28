#include <stdio.h>
//Daia Gabriel Petru 311CB

void print_most_significant_byte(unsigned int ip_addr) //functie luata din checker
{
    printf("%u", ip_addr >> 24);
}

int is_set(long byte, int i) //functie luata din laborator
{
    int mask = (1 << i);
    return (byte & mask) != 0;
}

long reset(long byte, int i) //functie luata din laborator
{
    int mask = ~(1 << i);
    return (byte & mask);
}

int verificareMasca(long a)
{
    int inceput_succesiune=0;
    int presupunere=1;//presupunem ca este corecta
    for(int i=0; i<32; i++)
    {
        if(is_set(a,i))
            inceput_succesiune=1;
        if(inceput_succesiune==1)
            if(is_set(a,i)==0)
            {
                presupunere=0;
                break;            
            }
    }
    return presupunere;
}

int celMaiSemnificativBit0(long a)
{
    int semnificativ;
    int inceput_succesiune=0;
    int presupunere=1;
    for(int i=0; i<32; i++)
    {
        if(is_set(a,i))
            inceput_succesiune=1;
        if(inceput_succesiune==1)
            if(is_set(a,i)==0)
            {
                presupunere=0;
                semnificativ=i;
            }
    }
    return semnificativ;
}

void corectareMasca(long a)
{
    int bit=celMaiSemnificativBit0(a);
    for(int i=0; i<bit; i++)
        a=reset(a,i);
    printAdrese(a);
}

void print_most_significant_byte_baza_16(unsigned int ip_addr) 
{
    printf("%X", ip_addr >> 24);
}

void print_most_significant_byte_baza_8(unsigned int ip_addr) 
{
    printf("%o", ip_addr >> 24);
}

void printAdrese(unsigned long adresa)
{
    unsigned int x=255;//valoare ajutatoare
    print_most_significant_byte(adresa);
    printf(".");
    printf("%ld",(x & (adresa>>16)) );
    printf(".");
    printf("%ld",(x & (adresa>>8)) );
    printf(".");
    printf("%ld",(x & adresa) );
}

void printAdreseBinar(unsigned long adresa)
{
    for(int i=31; i>=0; i--)
    {
        if(is_set(adresa,i))
            printf("1");
        else
            printf("0");
        if(i==24 || i==16 || i==8)
            printf(".");
    }
}

void printAdreseBaza16(unsigned long adresa)
{
    unsigned int x=255;
    print_most_significant_byte_baza_16(adresa);
    printf(".");
    printf("%X",(x & (adresa>>16)) );
    printf(".");
    printf("%X",(x & (adresa>>8)) );
    printf(".");
    printf("%X",(x & adresa) );
}

void printAdreseBaza8(unsigned long adresa)
{
    unsigned int x=255;
    print_most_significant_byte_baza_8(adresa);
    printf(".");
    printf("%o",(x & (adresa>>16)) );
    printf(".");
    printf("%o",(x & (adresa>>8)) );
    printf(".");
    printf("%o",(x & adresa) );
}

unsigned long conversieMasca(unsigned int n)
{
    int numar=0;
    unsigned masca;
    for(int putere=0; putere<=n; putere++)
    {
        numar=numar+(1<<putere);
    }
    masca=numar;
    return (masca<<(32-n));
}

unsigned long conversieInBiti(unsigned int a,unsigned int b,unsigned int c,unsigned int d)
{
    unsigned long ip=0;
    ip=(a | ip);
    ip=(ip<<8);
    ip=(b | ip);
    ip=(ip<<8);
    ip=(c | ip);
    ip=(ip<<8);
    ip=(d | ip);
    return ip;
}

int main()
{
    int nr_set_date;
    unsigned int msk0a,msk0b,msk0c,msk0d;
    unsigned int msk1;
    unsigned int ip0a,ip0b,ip0c,ip0d;
    unsigned int ip1a,ip1b,ip1c,ip1d;
    unsigned int n;
    unsigned long ip=0;

    scanf("%d",&nr_set_date);
    

    for(int j=1; j<=nr_set_date; j++)
    {
        scanf("%d%*c%d%*c%d%*c%d ", &msk0a,&msk0b,&msk0c,&msk0d);
        scanf("%d ", &msk1);//nr de biti de 1
        scanf("%d%*c%d%*c%d%*c%d ", &ip0a,&ip0b,&ip0c,&ip0d);
        scanf("%d%*c%d%*c%d%*c%d ", &ip1a,&ip1b,&ip1c,&ip1d);
    
        scanf("%d ", &n);//nr de adrese de retea
        int net[1000][1000];
        for(int i=0; i<n; i++)
        {
            scanf("%d%*c%d%*c%d%*c%d/%d", &net[i][0], &net[i][1], &net[i][2], &net[i][3], &net[i][4]);
            
        }
        printf("%d\n",j );
        printf("-0 "); // Task 0
        ip=conversieInBiti(ip0a,ip0b,ip0c,ip0d);//ip1
        printAdrese(ip);
        printf("/%u\n",msk1);
        printf("-1 "); // Task 1
        unsigned long masca=conversieMasca(msk1);//msk1
        printAdrese(masca);
        printf("\n");
        printf("-2 ");// Task 2
        int masca0=conversieInBiti(msk0a,msk0b,msk0c,msk0d);//msk0
        printAdreseBaza8(masca0);
        printf(" ");
        printAdreseBaza16(masca0);
        printf("\n");
        printf("-3 ");// Task 3
        int adresa_retea1=(ip & masca);
        printAdrese(adresa_retea1);
        printf("\n");
        printf("-4 ");// Task 4
        int adresa_brodcast1=(ip | (~masca));
        printAdrese(adresa_brodcast1);
        printf("\n");
        printf("-5 ");// Task 5
        unsigned long ip2=conversieInBiti(ip1a,ip1b,ip1c,ip1d);//ip2
        int adresa_retea2=(ip2 & masca);
        if(adresa_retea2==adresa_retea1)
            printf("DA\n");
        else
            printf("NU\n");
        printf("-6 ");// Task 6
        if(verificareMasca(masca0))
            printf("DA\n");
        else
            printf("NU\n");
        printf("-7 ");// Task 7
        if(verificareMasca(masca0))
        {
            printAdrese(masca0);
            printf("\n");
        }
        else
        {
            corectareMasca(masca0);
            printf("\n");
        }
        printf("-8 ");// Task 8
        printAdreseBinar(ip);
        printf("\n");
        printf("-9 ");// Task 9
        long masti[1000]={0};
        long adrese_de_retea_citite[1000];
        for(int k=0; k<n; k++)
        {
            masti[k]=conversieMasca(net[k][4]);
            adrese_de_retea_citite[k]=conversieInBiti(net[k][0],net[k][1],net[k][2],net[k][3]);
            if((masti[k] & ip2)==(adrese_de_retea_citite[k] & masti[k]))
                printf("%d ",k);
        }
        printf("\n");
    }
    // 255.237.0.0 20 192.168.25.87 192.168.26.1 3 192.168.0.0/16 192.0.26.0/16 192.168.26.0/24
} 
