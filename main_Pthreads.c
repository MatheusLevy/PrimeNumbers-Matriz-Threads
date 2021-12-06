#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

//Macros
#define TRUE 1
#define FALSE 0
//Quantidade de Threads
#define QThreads 2
//Matriz m x n
#define m 5
#define n 5
//Maior numero aleatorio
#define M_RAND 29999

//Seed para geração aleatória
#define seed 58896532
//Definindo variaveis globais
long long Tamanho_Matriz = n*m;
int matriz[n*m];
int TotalPrimos = 0;
int Bloco=0;
//Definindo Threads e Mutex
pthread_t threads[QThreads];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

//Definindo Funções
void PreencherMatrizPadrao();
void ExibirMatriz();
void* SubMatriz(void *args);
void ProcessarMatriz();
int EhPrimo(int numero);

//Uso de threads
int main(void){

    PreencherMatrizPadrao(matriz);
    ExibirMatriz(matriz);
    ProcessarMatriz();
    printf("\nExistem %d Primos", TotalPrimos);
    return 0;
}


void ProcessarMatriz(){

    pthread_t threads_id[QThreads];

    int k=0;
    for(k=0;k<QThreads;k++)
        pthread_create(&(threads_id[k]), NULL, SubMatriz, NULL);

    for(k=0;k<QThreads;k++){
        pthread_join(threads_id[k], NULL);
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
    printf("\n\n");
}

//Função da Thread
void* SubMatriz(void* args){

    int soma_local=0;
    int i;
    int j;
    int divisores;
    pthread_mutex_lock(&mutex);
    int Bloco_Thread = Bloco++;
    pthread_mutex_unlock(&mutex);
    int Tam_Bloco = n;
    


    for(i = Bloco_Thread*(Tamanho_Matriz/QThreads);i < ((Bloco_Thread+1) * (Tamanho_Matriz/QThreads));i++){
        divisores=0;

        printf("%d\n", matriz[i]);
        if(EhPrimo(matriz[i]))
            soma_local++;
    }
    pthread_mutex_lock(&mutex);
    TotalPrimos+=soma_local;
    pthread_mutex_unlock(&mutex);
    
    pthread_exit(NULL);
}

//Função que verifica se é primo
int EhPrimo(int numero){
    int divisores = 0;
    int j;
    for (j = 2; j < numero; j++){
        if(numero%j == 0){
            divisores++;
            break;
        }
	}
    if(divisores == 0 && numero != 0 && numero != 1)
        return TRUE;
    else
        return FALSE;
}