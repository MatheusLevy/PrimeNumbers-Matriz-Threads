#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

#define TRUE 1
#define FALSE 0
#define nThreads 4
#define m 5
#define n 5
#define Biggest_Rand_Number 29999
#define seed 58896532

int matrix[n*m];
int PrimesCounter = 0;
int Block_number=0;
int block_size = (n*m/nThreads);

pthread_t threads[nThreads];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void FillMatrix();
void ShowMatrix();
void* ProcessSubMatrix(void *args);
void ProcessMatrix();
int isPrime(int numero);
void CreateThreads();
void JoinThreads();

pthread_t threads[nThreads];

int main(void){
    FillMatrix(matrix);
    ShowMatrix(matrix);
    ProcessMatrix();
    printf("\nThere are %d Prime Numbers\n", PrimesCounter);
    return 0;
}

void CreatePthreads(){
    int i;
    for(i=0; i<nThreads; i++)
        pthread_create(&threads[i], NULL, ProcessSubMatrix, NULL);
}

void JoinPthreads(){
    int i;
    for(i=0; i<nThreads; i++)
        pthread_join(threads[i], NULL);
}

void ProcessMatrix(){
    int k=0;
    CreatePthreads();
    JoinPthreads();
}

int RandomNumber(){
    return rand() % Biggest_Rand_Number;
}
void FillMatrix(){
    int i;
    int j;
    srand(seed);
    for(i=0; i< m; i++){
        for(j = 0; j<n; j++)
            matrix[i*n + j] = RandomNumber();
    }
}

void ShowMatrix(){
    int i;
    int j;
    for(i=0;i<m;i++){
        for(j = 0; j<n;j++)
            printf("%d \t", matrix[i*n + j]);
        printf("\n");
    }
    printf("\n\n");
}

int endOfBlock(int block_number){
    return (block_number+1) * block_size;
}

int startOfBlock(int block_number){
    return block_number * block_size;
}

void* ProcessSubMatrix(void* args){
    int local_primes_counter=0;
    int i;
    pthread_mutex_lock(&mutex);
    int start_index = startOfBlock(Block_number);
    int end_index = endOfBlock(Block_number);
    Block_number++;
    pthread_mutex_unlock(&mutex);
    
    for(i = start_index; i < end_index; i++){
        if(isPrime(matrix[i]))
            local_primes_counter++;
    }

    pthread_mutex_lock(&mutex);
    PrimesCounter+=local_primes_counter;
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

int isZero(int number){
    return number == 0;
}

int isOne(int number){
    return number == 1;
}

int isPrime(int number){
    int i;
    if (isZero(number) || isOne(number))
        return FALSE;
    for (i = 2; i < number/2; i++){
        if(number % i == 0)
            return FALSE;
	}
	return TRUE;
}