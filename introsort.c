#include "introsort.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

void selection(int *vetor, benchData *benchData, int indDado, int tam){
    int menor, aux, i;
    int cursor=0;

    while(cursor<tam-1){
        menor=cursor; // seta o menor como o primeiro elemento a ser varrido
        for(i=cursor+1;i<tam;i++){ // varre a parte desordenada do vetor e busca o menor elemento
            benchData->mCmp[indDado]++;
            if(vetor[i]<vetor[menor]){
                menor = i;
            }
        }
        benchData->mCmp[indDado]++;
        if(menor!=cursor){   //se o menor nao for o cursor, troca as posições
            aux =vetor[cursor];
            vetor[cursor] = vetor[menor];
            vetor[menor] = aux;
            benchData->mTrocas[indDado]++;
        }
        cursor++;
    }
    return;
}

void insertion(int *vetor, benchData *benchData, int indDado, int tam){
    int cursor, aux, pos;

    for(cursor = 1;cursor<tam;cursor++){
        aux = vetor[cursor];
        pos = cursor-1;

        while(pos>=0 && aux <vetor[pos]){
            vetor[pos+1] = vetor[pos];
            benchData->mCmp[indDado]++;
            pos--;
        }
        if(vetor[pos+1]!=aux){
            vetor[pos+1] = aux;
            benchData->mTrocas[indDado]++;
        }
        benchData->mCmp[indDado]++;
    }
    return;
}


int particiona(int *vetor, int inicio, int fim, benchData *benchData, int indDado){
    int pivo = vetor[fim];
    int i = inicio - 1;

    for (int index = inicio; index < fim; index++) {
        if (vetor[index] < pivo) {
            i++;
            int temp = vetor[i];   // troca v[i] com v[index]
            vetor[i] = vetor[index];
            vetor[index] = temp;
            benchData->mTrocas[indDado]++;
        }
        benchData->mCmp[indDado]++;
    }

    // coloca o pivô na posição correta
    int temp = vetor[i + 1];
    vetor[i + 1] = vetor[fim];
    vetor[fim] = temp;
    benchData->mTrocas[indDado]++;

    return i + 1;
}

void quickSort(int *vetor, int inicio, int fim, benchData *benchData, int indDado){
    if (inicio < fim) {
        int p = particiona(vetor, inicio, fim, benchData, indDado);
        quickSort(vetor, inicio, p - 1, benchData, indDado);
        quickSort(vetor, p + 1, fim, benchData, indDado);
    }
    return;
}

int merge(int *vetor, int inicio, int meio, int fim, benchData *benchData, int indDado){
    int inicio1, inicio2, tam, final1 = 0, final2 = 0;
    int *vetAux;

    tam = fim - inicio +1;
    inicio1=inicio;
    inicio2=meio+1;

    vetAux = (int *)malloc(sizeof(int) * tam);
    if(!vetAux){
        return -1;  //retorno dessa função serve apenas para checar se houve erro ou não
    }

    for(int i=0;i<tam;i++){
        if(!final1 && !final2){
            if(vetor[inicio1] < vetor[inicio2]){
                vetAux[i] = vetor[inicio1];
                inicio1++;
            }
            else{
                vetAux[i] = vetor[inicio2];
                inicio2++;
                benchData->mTrocas[indDado]++;
            }
            if(inicio1>meio){
                final1 = 1;
            }
            if(inicio2>fim){
                final2=1;
            }
            benchData->mCmp[indDado]++;
        }
        else{
            if(!final1){
                vetAux[i]=vetor[inicio1];
                inicio1++;
            }
            else{
                vetAux[i]=vetor[inicio2];
                inicio2++;
            }
        }
    }

    int l = inicio;
    int k=0;

    for(k=0; k<tam; k++){
        vetor[l] = vetAux[k];
        l++;
    }

    free(vetAux);
    return 1;
}

void mergeSort(int *vetor, int inicio, int fim, benchData *benchData, int indDado){
    int meio;
    meio = (inicio + fim) / 2;

    if(inicio < fim){
        mergeSort(vetor, inicio, meio, benchData, indDado);
        mergeSort(vetor, meio + 1, fim, benchData, indDado);
        merge(vetor, inicio, meio, fim, benchData, indDado);
    }
    return;
}

void criaHeap(int *vetor, int ini, int fim, benchData *benchData, int indDado){
    int raiz = ini;
    int filho;
    int aux = vetor[raiz];

    while ((filho = 2 * raiz + 1) <= fim) { // Se tem filho na direita e ele é maior que o da esquerda
        if (filho + 1 <= fim) {
            benchData->mCmp[indDado]++;
            if (vetor[filho] < vetor[filho + 1]) // filho aponta p maior
                filho++;
        }

        benchData->mCmp[indDado]++;
        if (aux < vetor[filho]) {
            vetor[raiz] = vetor[filho];  // sobe o maior filho p pai
            raiz = filho;
            benchData->mTrocas[indDado]++;
        } else {
            filho=fim+1;  // heap ja está ajustado entao quebra o loop do while
        }
    }

    vetor[raiz] = aux;  //seta o valor original de volta
    return;
}


void heapSort(int *vetor, int tam, benchData *benchData, int indDado){
    int aux;

    for (int i = (tam - 1) / 2; i >= 0; i--) { // heapify a partir do vetor
        criaHeap(vetor, i, tam - 1, benchData, indDado);
    }

    for (int i = tam - 1; i >= 1; i--) { // pega raiz e reorganiza o heap
        aux = vetor[0]; // Troca o maior elemento(0) com o último elemento não ordenado
        vetor[0] = vetor[i];
        vetor[i] = aux;
        benchData->mTrocas[indDado]++;

        criaHeap(vetor, 0, i - 1, benchData, indDado); // Reajusta o heap

    }
    return;
}

void insertionIntro(int* vetor, int ini, int fim, benchData *benchData, int indDado){
    int aux, pos;

    for (int marcador = ini + 1; marcador <= fim; marcador++) {
        aux = vetor[marcador];
        pos = marcador - 1;

        while (pos >= ini && aux < vetor[pos]) {
            vetor[pos + 1] = vetor[pos];
            pos--;
            benchData->mCmp[indDado]++;
        }

        benchData->mCmp[indDado]++;  // conta a comparação que falhou

        if (vetor[pos + 1] != aux) {
            benchData->mTrocas[indDado]++;
        }
        vetor[pos + 1] = aux;
    }
    return;
}

void introSort(int *vetor, int ini, int fim, int maxDp, benchData *benchData, int indDado){
    int tam = fim - ini + 1;

    if (tam <= 16) { // se for menor q 16
        insertionIntro(vetor, ini, fim, benchData, indDado);
        return;
    }

    if (maxDp == 0) { // se a pilha atingir a profundidade maxima usa o heapsort
        heapSort(vetor + ini, tam, benchData, indDado);
        return;
    }

    // ordena pelo quicksort
    int pivo = particiona(vetor, ini, fim, benchData, indDado);
    introSort(vetor, ini, pivo - 1, maxDp - 1, benchData, indDado);
    introSort(vetor, pivo + 1, fim, maxDp - 1, benchData, indDado);
    return;
}

int* geraVetRandom(int tam, int seed){
    int *vetor;

    vetor = (int*) malloc(tam * sizeof(int));
    if(!vetor){
        return NULL;
    }
    srand(seed); // alimenta o srand com a semente

    for(int i = 0; i < tam; i++) // gera o vetor c numeros aleatorios
        vetor[i] = rand()%100;

    return vetor;
}
