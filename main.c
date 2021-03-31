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
int BPT;
int inicio;
int fim;
int TotalPrimos = 0;


// int posi = i*n+j;
void PreencherMatrizPadrao();
void ExibirMatriz();
void SubMatriz(int inicio, int fim);
int EhPrimo(int number);



int main(void){

    //int TotalElms = n*m;
    BPT = floor(m/QThreads); //Blocos por thread
    resto = m % QThreads;

    PreencherMatrizPadrao(matriz);
    ExibirMatriz(matriz);
    inicio = 0;
    fim = n-1;
    printf("BPT: %d", BPT);
    ProcessarMatriz();
   
    return 0;
}

void ProcessarMatriz(){
     int i;

   // printf("\n------Thread 1------");
    for(i=0;i<BPT;i++){
        SubMatriz(inicio,fim);
        inicio=fim+1;
        fim+=n;
    }

   // printf("\n------Thread 2------");
    for(i=0;i<BPT;i++){
        SubMatriz(inicio,fim);
        inicio=fim+1;
        fim+=n;
    }   

    while(resto > 0){
      //  printf("\n------Thread 1------");
        SubMatriz(inicio,fim);
        inicio = fim+1;
        fim+=n;
        resto--;

        if(resto>0){
        //    printf("\n------Thread 2------");
            SubMatriz(inicio,fim);
            fim+=n;
            resto--;
        }
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

void SubMatriz(int inicio, int fim){
    int i;
    printf("\n-----Sub MAtriz ------\n");
    for(i = inicio;i<=fim;i++){
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