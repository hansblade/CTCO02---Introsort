#ifndef INTROSORT_H
#define INTROSORT_H
#include <time.h>
#include <windows.h>

// struct para guardar os dados do benchmark
typedef struct benchData{
    int mTrocas[5];
    long long int mCmp[5];
    long int trocas[5][4];
    long long int cmp[5][4];
} benchData;

void insertion(int *vetor, benchData *benchData, int indDado, int tam);
void selection(int *vetor, benchData *benchData, int indDado, int tam);
void mergeSort(int *vetor, int inicio, int fim, benchData *benchData, int indDado);
void quickSort(int *vetor, int inicio, int fim, benchData *benchData, int indDado);
int particiona(int *vetor, int inicio, int fim, benchData *benchData, int indDado);
int merge(int *vetor, int inicio, int meio, int fim, benchData *benchData, int indDado);
void heapSort(int *vet, int tam, benchData *benchDat, int indDado);
void criaHeap(int *vet, int ini, int fim, benchData *benchDat, int indDado);
void insertionIntro(int* vet, int ini, int fim, benchData *benchDat, int indDado);
void introSort(int *vet, int ini, int fim, int prof_max, benchData *benchDat, int indDado);
int* geraVetRandom(int tam, int seed);
int* geraQuaseOrdenados(int tam, int porcentagem);
int* geraOrdenados(int tam, int ordem);
double calculaTempo(LARGE_INTEGER tempoIni, LARGE_INTEGER tempoFim, LARGE_INTEGER freq);
double calculaMediaTempo(const double vetorTempo[]);
int calculaMediaTrocas(benchData *benchData);
long long int calculaMediaComparacoes(benchData *benchData);
void iniciaBenchData(benchData *benchData);
int menuBench();
void printTempo(int opcao);
void comps(benchData benchData, int tam);
void trocas(benchData benchData, int tam);
void printTempos(int teste, double tempoAlt, double tempoCresc, double tempoDecresc, double tempoQseOrd, int tam);
void printCmp(benchData benchData, int tam);
void printTrocas(benchData benchData, int tam);
#endif //INTROSORT_H
