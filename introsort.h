#ifndef INTROSORT_H
#define INTROSORT_H

/*
 struct pra facilitar guardar os dados referentes a performance de cada caso de ordenação
 como numero de trocas e comparações
 */
typedef struct benchData{
    long long int cmp[5][4];
    long long int mCmp[5];
    int trocas[5][4];
    int mTrocas[5];
}benchData;

void selection(int *vetor, benchData *benchData, int indDado, int tam);
void insertion(int *vetor, benchData *benchData, int indDado, int tam);
int particiona(int *vetor, int inicio, int fim, benchData *benchData, int indDado);
void quickSort(int *vetor, int inicio, int fim, benchData *benchData, int indDado);
int merge(int *vetor, int inicio, int meio, int fim, benchData *benchData, int indDado);
void mergeSort(int *vetor, int inicio, int fim, benchData *benchData, int indDado);
void criaHeap(int *vetor, int ini, int fim, benchData *benchData, int indDado);
void heapSort(int *vetor, int tam, benchData *benchData, int indDado);
void insertionIntro(int* vetor, int ini, int fim, benchData *benchData, int indDado);
void introSort(int *vetor, int ini, int fim, int maxDp, benchData *benchData, int indDado);
int* geraVetRandom(int tam, int seed);
#endif //INTROSORT_H
