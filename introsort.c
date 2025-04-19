#include "introsort.h"
#include <stdlib.h>
#include <stdio.h>

/*
 struct pra facilitar guardar os dados referentes a performance de cada caso de ordenação
 como numero de trocas e comparações
 */
struct dados{
    long long int cmp[5][4];
    long long int mCmp[5];
    int trocas[5][4];
    int mTrocas[5];
};


int printMenu(){
    int escolha;

    printf("------------------- Escolha a Opcao de Ordenacao Desejada -------------------\n");
    printf("1. Selection\n2.Insertion\n3.Mergesort\n4.Quicksort,\n5.Introsort\n");
    scanf("%d", &escolha);

    return escolha;
}

void selection(int *vetor, int tam, dados *dados, int j){
    int menor, aux, i;
    int cursor=0;

    while(cursor<tam-1){
        menor=cursor; // seta o menor como o primeiro elemento a ser varrido
        for(i=cursor+1;i<tam;i++){ // varre a parte desordenada do vetor e busca o menor elemento
            dados->mCmp[j]++;
            if(vetor[i]<vetor[menor]){
                menor = i;
            }
        }
        dados->mCmp[j]++;
        if(menor!=cursor){   //se o menor nao for o cursor, troca as posições
            aux =vetor[cursor];
            vetor[cursor] = vetor[menor];
            vetor[menor] = aux;
            dados->mTrocas[j]++;
        }
        cursor++;
    }
}

void insertion(int *vetor, int tam, dados *dados, int j){
    int cursor, aux, pos;

    for(cursor = 1;cursor<tam;cursor++){
        aux = vetor[cursor];
        pos = cursor-1;

        while(pos>=0 && aux <vetor[pos]){
            vetor[pos+1] = vetor[pos];
            dados->mCmp[j]++;
            pos--;
        }
        if(vetor[pos+1]!=aux){
            vetor[pos+1] = aux;
            dados->mTrocas[j]++;
        }
        dados->mCmp[j]++;
    }
}