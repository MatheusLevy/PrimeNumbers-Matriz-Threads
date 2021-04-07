#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

#define TRUE 1
#define FALSE 0

#define QThreads 2
#define m 3
#define n 3
#define M_RAND 29999

#define seed 58896532

int matriz[n*m];
int resto;
int TotalPrimos = 0;
int inicio=0;
pthread_t threads[QThreads];

// int posi = i*n+j;
void PreencherMatrizPadrao();
void ExibirMatriz();
void* SubMatriz(void* inicio);
int EhPrimo(int number);
void ProcessarMatriz();



int main(void){

    //int TotalElms = n*m;
    resto = m % QThreads;
    PreencherMatrizPadrao(matriz);
    ExibirMatriz(matriz);
    ProcessarMatriz();
    printf("\nExistem %d Primos", TotalPrimos);
    return 0;
}


void ProcessarMatriz(){
    int i;

    pthread_t threads_id[QThreads];
    int j;
    
    for(j=0;j<QThreads;j++)
        pthread_create(&(threads_id[j]), NULL, (void *)SubMatriz, &inicio);


    while (inicio<n*m)
    {
        while (resto>0)
        {
            if(resto == 1){
                //printf("\n-----Thread 1-----\n");
                pthread_join(threads_id[0], NULL);
                //SubMatriz(inicio,fim);
                inicio= (inicio+n);
                resto--;
            }else{
                //printf("\n-----Thread 1-----\n");
                pthread_join(threads_id[0], NULL);
                //SubMatriz(inicio,fim);
                inicio= (inicio+n);
                resto--;

                //printf("\n-----Thread 2-----\n");
                pthread_join(threads_id[1], NULL);
                //SubMatriz(inicio,fim);
                inicio= (inicio+n);
                resto--;
            }
        }
        
        //printf("\n-----Thread 1-----\n");
        pthread_join(threads_id[0], NULL);
        //SubMatriz(inicio,fim);
        inicio= (inicio+n);

        //printf("\n-----Thread 2-----\n");
        pthread_join(threads_id[1], NULL);
        //SubMatriz(inicio,fim);
        inicio= (inicio+n);
    }

    printf("\nQuantidade de Primos: %d\n", TotalPrimos);
}

void PreencherMatrizPadrao(){
    int i;
    int j;
    srand(seed);
    for(i=0;i<m;i++){
        for(j = 0; j<n;j++){
            matriz[i*n+j] = rand() % M_RAND; 
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

//Função da Thread
void* SubMatriz(void* inicio){
    int soma_local=0;

    int *inicio_pt = (int*) inicio;
    int ini = *inicio_pt;

    int i;
    //printf("\n-----Sub MAtriz ------\n");
    for(i = ini;i<=(ini+n)-1;i++){
        //printf("%d \t", matriz[i]);
        if(EhPrimo(matriz[i])){
            soma_local++;
        }
            

    }
   //printf("\n");
    TotalPrimos+=soma_local;
    pthread_exit(0);
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