#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TRUE 1
#define FALSE 0

#define QThreads 2
#define m 5
#define n 5
#define RAND_MAX 29999
#define seed 12345

int matriz[n*m];
int resto;
int TotalPrimos = 0;

int inicio =0;

// int posi = i*n+j;
void PreencherMatrizPadrao();
void ExibirMatriz();
void SubMatriz(int inicio);
int EhPrimo(int number);
void ProcessarMatriz();


int main(void){

    //int TotalElms = n*m;
    resto = m % QThreads;
    PreencherMatrizPadrao(matriz);
    ExibirMatriz(matriz);
    ProcessarMatriz();
   
    return 0;
}

void ProcessarMatriz(){

    while (inicio<n*m)
    {
        while (resto>0)
        {
            if(resto == 1){
                printf("\n-----Thread 1-----\n");
                SubMatriz(inicio);
                inicio = (inicio+n);
                resto--;
            }else{
                printf("\n-----Thread 1-----\n");
                SubMatriz(inicio);
                inicio= (inicio+n);
                resto--;

                printf("\n-----Thread 2-----\n");
                SubMatriz(inicio);
                inicio= inicio+n;
                resto--;
            }
        }
        
        printf("\n-----Thread 1-----\n");
        SubMatriz(inicio);
        inicio = inicio+n;

        printf("\n-----Thread 2-----\n");
        SubMatriz(inicio);
        inicio = inicio+n;


    }

    printf("\nExistem %d Primos", TotalPrimos);
}

void PreencherMatrizPadrao(){
    int i;
    int j;
    srand(seed);
    for(i=0;i<m;i++){
        for(j = 0; j<n;j++){
            matriz[i*n+j] = rand() % RAND_MAX; 
        }
    }
}


void ExibirMatriz(){
    int i;
    int j;
    for(i=0;i<m;i++){
        for(j = 0; j<n;j++){
            printf("%d \t", matriz[i*n+j]);
        }
        
        printf("\n");
    }
}

void SubMatriz(int inicio){
    int i;
    printf("\n-----Sub MAtriz ------\n");
    for(i = inicio;i<=(inicio+n)-1;i++){
        printf("%d \t", matriz[i]);
        if(EhPrimo(matriz[i])){
            TotalPrimos++;
        }
            

    }
   printf("\n");
}

int EhPrimo(int number){
    int divisores=0;
    int i;
    for (i = 2; i < number; i++)
    {
        if(number%i == 0){
            divisores++;
            break;
        }
    }
    if(divisores == 0 && number != 0 && number != 1)
        return TRUE;
    else
        return FALSE;
    
}