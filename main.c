#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TRUE 1
#define FALSE 0

#define QThreads 2
#define m 5
#define n 6

int TotalPrimos = 0;

// int posi = i*n+j;
void PreencherMatrizPadrao(int* matriz);
void ExibirMatriz(int* matriz);
void SubMatriz(int* matriz, int inicio, int fim);
int EhPrimo(int number);

int main(void){

    int TotalElms = n*m;
    int BPT = floor(m/QThreads); //Blocos por thread
    int resto = m % QThreads;

    int *matriz = (int *)malloc(sizeof(int)*TotalElms);
    PreencherMatrizPadrao(matriz);
    ExibirMatriz(matriz);
    int inicio = 0;
    int fim = n-1;
    int i;
    int k;
    
    printf("BPT: %d", BPT);

    printf("\n------Thread 1------");
    for(i=0;i<BPT;i++){
        SubMatriz(matriz,inicio,fim);
        inicio=fim+1;
        fim+=n;
    }

    printf("\n------Thread 2------");
    for(i=0;i<BPT;i++){
        SubMatriz(matriz,inicio,fim);
        inicio=fim+1;
        fim+=n;
    }   

    while(resto > 0){
        printf("\n------Thread 1------");
        SubMatriz(matriz,inicio,fim);
        inicio = fim+1;
        fim+=n;
        resto--;

        if(resto>0){
            printf("\n------Thread 2------");
            SubMatriz(matriz,inicio,fim);
            fim+=n;
            resto--;
        }
    }

    printf("\nExistem %d Primos", TotalPrimos);
    return 0;
}



void PreencherMatrizPadrao(int* matriz){
    int i;
    int j;
    for(i=0;i<m;i++){
        for(j = 0; j<n;j++){
            matriz[i*n+j] = i*n+j; 
        }
    }
}


void ExibirMatriz(int* matriz){
    int i;
    int j;
    for(i=0;i<m;i++){
        for(j = 0; j<n;j++){
            printf("%d \t", matriz[i*n+j]);
        }
        
        printf("\n");
    }
}

void SubMatriz(int* matriz, int inicio, int fim){
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