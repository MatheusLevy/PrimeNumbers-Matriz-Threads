#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// int posi = i*n+j;

void PreencherMatrizPadrao(int* matriz, int m, int n){
    int i;
    int j;
    for(i=0;i<m;i++){
        for(j = 0; j<n;j++){
            matriz[i*n+j] = i*n+j; 
        }
    }
}

void ExibirMatriz(int* matriz, int m, int n){
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
    }
   printf("\n");
}

void Pthread(int *matriz, int inicio, int fim);

int main(void){

    int m = 5;
    int n = 5;

    int TotalElms = n*m;
    int QThreads = 2;
    int BPT = floor(n/QThreads); //Blocos por thread
    int resto = n % QThreads;

    int *matriz = (int *)malloc(sizeof(int)*TotalElms);
    PreencherMatrizPadrao(matriz,m,n);
    ExibirMatriz(matriz,m,n);
    int inicio = 0;
    int fim = n-1;
    int i;
    int k;
    
    printf("BPT: %d", BPT);

    for(k=0;k<QThreads;k++){

        for(i=0;i<BPT;i++){
            Join1(matriz,inicio,fim);
            inicio=fim+1;
            fim+=n;
        }

        for(i=0;i<BPT;i++){
            Join2(matriz,inicio,fim);
            inicio=fim+1;
            fim+=n;
        }   

        while(resto > 0){
            Join1(matriz,inicio,fim);
            inicio = fim+1;
            fim+=n;
            resto--;

            if(resto>0){
                Join2(matriz,inicio,fim);
                fim+=n;
                resto--;
            }
        } 


        
    }
    

    /*
    for(i=0;i<QThreads;inicio=fim+1, fim+=TPE, i++){
        if(resto>0){
            SubMatriz(matriz,inicio,++fim);
            resto--;
        }else{
            SubMatriz(matriz,inicio,fim);
        }   
    }
    */


    return 0;
}