#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

#define TRUE 1
#define FALSE 0

#define QThreads 2
#define m 1000
#define n 1000
#define M_RAND 29999

#define seed 58896532

int matriz[n*m];
int resto;
int TotalPrimos = 0;
pthread_t threads[QThreads];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
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
    int inicio=0;
    pthread_t threads_id[QThreads];
    int j;
    
    for(j=0;j<QThreads;j++)
        pthread_create(&(threads_id[j]), NULL, (void *)SubMatriz, &inicio);


    while (inicio<n*m)
    {
        while (resto>0)
        {
            if(resto == 1){
                pthread_join(threads_id[0], NULL);
                inicio= (inicio+n);
                resto--;
            }else{
                pthread_join(threads_id[0], NULL);
                inicio= (inicio+n);
                resto--;

                pthread_join(threads_id[1], NULL);
                inicio= (inicio+n);
                resto--;
            }
        }
        
        pthread_join(threads_id[0], NULL);
        inicio= (inicio+n);

        pthread_join(threads_id[1], NULL);
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
    pthread_mutex_lock(&mutex);
    int *inicio_pt = (int*) inicio;
    int ini = *inicio_pt;
    pthread_mutex_unlock(&mutex);
    int i;
    //printf("\n-----Sub MAtriz ------\n");
    for(i = ini;i<=(ini+n)-1;i++){
        //printf("%d \t", matriz[i]);
        if(EhPrimo(matriz[i])){
            soma_local++;
        }
            

    }
    //printf("\n");
    
    pthread_mutex_lock(&mutex);
    TotalPrimos+=soma_local;
    pthread_mutex_unlock(&mutex);
    
    pthread_exit(NULL);
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