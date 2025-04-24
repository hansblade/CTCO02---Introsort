#include "introsort.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <windows.h>

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


void heapSort(int *vetor, int tam, benchData *benchData, int indDado){
    int i, aux;

    for (i = (tam - 1) / 2; i >= 0; i--)  // heapify a partir do vetor
        criaHeap(vetor, i, tam - 1, benchData, indDado);

    for (i = tam - 1; i >= 1; i--){ // pega raiz e reorganiza o heap

        aux = vetor[0]; // Troca o maior elemento(0) com o último elemento não ordenado
        vetor[0] = vetor[i];
        vetor[i] = aux;
        benchData->mTrocas[indDado]++;
        criaHeap(vetor, 0, i - 1, benchData, indDado); // Reajusta o heap
    }
}

void criaHeap(int *vetor, int ini, int fim, benchData *benchData, int indDad){
    int aux, i;

    aux = vetor[ini];
    i = ini * 2 + 1;

    while(i <= fim){ // Se tem filho na direita e ele é maior que o da esquerda
        if(i < fim) {
            benchData->mCmp[indDad]++;
            if (vetor[i] < vetor[i + 1]) // filho aponta p maior
                i++;
        }
        benchData->mCmp[indDad]++;
        if(aux < vetor[i]){
            vetor[ini] = vetor[i]; // sobe o maior filho p pai
            ini = i;
            i = 2 * ini + 1;
            benchData->mTrocas[indDad]++;
        }
        else
            i = fim + 1; // heap ja está ajustado entao quebra o loop do while
    }
    vetor[ini] = aux; //seta o valor original de volta
}

void insertionIntro(int* vetor, int ini, int fim, benchData *benchData, int indDad){
    int marcador, aux, pos;

    // varre o vetor a partir de ini+1 até fim
    for(marcador = ini + 1; marcador <= fim; marcador++) {
        aux = vetor[marcador];
        pos = marcador - 1;

        // 'empurra' os elementos maiores que aux pra frente
        while(pos >= 0 && aux < vetor[pos]){
            vetor[pos + 1] = vetor[pos];
            pos --;
        }
        // se deslocou conta a troca
        if(vetor[pos + 1] != aux) {
            benchData->mTrocas[indDad]++;
        }
        vetor[pos + 1] = aux; // coloca o elemento na posicao correta
        benchData->mCmp[indDad]++; // conta a comparacao de falha do while
    }
}

void introSort(int *vetor, int ini, int fim, int maxDp, benchData *benchData, int indDad){
    int pivo, tam;

    tam = (fim - ini) + 1;

    if(tam <= 16) { // se for menor q 16, convencao empirica, geralmente variam de 16 a 32
        insertionIntro(vetor, ini, fim, benchData, indDad);
        return;
    }

    if(maxDp == 0) { // se a pilha atingir a profundidade maxima usa o heapsort
        heapSort(vetor, tam, benchData, indDad);
        return;
    }

    else{ // ordena pelo quicksort
        pivo = particiona(vetor, ini, fim, benchData, indDad);
        introSort(vetor, ini, pivo - 1, maxDp - 1, benchData, indDad);
        introSort(vetor, pivo + 1, fim, maxDp - 1, benchData, indDad);
    }
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

int* geraQuaseOrdenados(int tam, int porcentagem){
    int *vetor, i, qtdDesordenados, pos1, pos2, aux;
    vetor = (int*) malloc(tam * sizeof(int));
    if(!vetor){
        printf("\nErro ao alocar memória");
        return NULL;
    }
    for(i = 0; i < tam; i++)
        vetor[i] = i;
    qtdDesordenados = (tam * porcentagem) / 100;
    srand(time(NULL));
    for (i = 0; i < qtdDesordenados; i++) {
        pos1 = rand() % tam;
        pos2 = rand() % tam;
        aux = vetor[pos1];
        vetor[pos1] = vetor[pos2];
        vetor[pos2] = aux;
    }
    return vetor;
}

int* geraOrdenados(int tam, int ordem) {
    int *vetor;
    vetor = (int*)malloc(tam * sizeof(int));
    if (vetor == NULL) {
        printf("\nErro ao alocar memória");
        return NULL;
    }
    if (ordem == 0) {
        for (int i = 0; i < tam; i++)
            vetor[i] = i;
    } else if (ordem == 1) {
        for (int i = 0; i < tam; i++)
            vetor[i] = tam - 1 - i;
    } else {
        printf("Erro: Valor de ordem inválido.\n");
        free(vetor);
        return NULL;
    }
    return vetor;
}

double calculaMediaTempo(const double vetorTempo[]) {
    double soma = 0.0;
    for (int i = 0; i < 5; i++)
        soma += vetorTempo[i];
    return soma / 5;
}

long long int calculaMediaComparacoes(benchData *benchData) {
    long long int soma = 0;
    for (int i = 0; i < 5; i++)
        soma += benchData->mCmp[i];
    return soma / 5;
}

int calculaMediaTrocas(benchData *benchData) {
    int soma = 0;
    for (int i = 0; i < 5; i++)
        soma += benchData->mTrocas[i];
    return soma / 5;
}

void iniciaBenchData(benchData *benchData) {
    for (int i = 0; i < 5; i++) {
        benchData->mTrocas[i] = 0;
        benchData->mCmp[i] = 0;
    }
}

int menuBench() {
    int opcao;
    printf("\t\tSELECIONE O METODO DE ORDENACAO");
    printf("\n1 - Insertion\n2 - Selection\n3 - MergeSort\n4 - QuickSort\n5 - IntroSort\n"
           "\n> ");
    scanf("%d", &opcao);
    return opcao;
}

void printTempo(int opcao) {
    int i;
    switch(opcao) {
        case 1:
            printf(  "\t\t\tINSERTION SORT - Tempo de Execucao (ms)\n");
            break;
        case 2:
            printf( "\t\t\tSELECTION SORT - Tempo de Execucao (ms)\n");
            break;
        case 3:
            printf("\t\t\tMERGESORT - Tempo de Execucao (ms)\n");
            break;
        case 4:
            printf("\t\t\tQUICKSORT - Tempo de Execucao (ms)\n");
            break;
        case 5:
            printf("\t\t\tINTROSORT - Tempo de Execucao (ms)\n");
            break;
        default:
            return;
    }
    printf("================================================================================");
    printf("\nTeste\tTam. Entrada\tAleatorio\tCrescente\tDecrescente\tQuase Ordenado\n");
    printf("================================================================================");

    printf("\n");
}

void comps(benchData benchData, int tam) {
    int i;
    printf("\n\t\t\t\tComparacoes\n");
    printf("================================================================================");
    printf("\nTeste\tTam. Entrada\tAleatorio\tCrescente\tDecrescente\tQuase Ordenado\n");
    printf("================================================================================");
    printf("\n");
    printCmp(benchData, 5);
}

void trocas(benchData benchData, int tam) {
    int i;
    printf("\n\t\t\t\tTrocas\n");
    printf("================================================================================");
    printf("\nTeste\tTam. Entrada\tAleatorio\tCrescente\tDecrescente\tQuase Ordenado\n");
    printf("================================================================================");
    printf("\n");
    printTrocas(benchData, 5);
}

void printTempos(int teste, double tempoAlt, double tempoCresc, double tempoDecresc, double tempoQseOrd, int tam) {
    printf("%d\t%-16d%-16.5f%-16.5f%-16.5f%-16.5f\n", teste, tam, tempoAlt, tempoCresc, tempoDecresc, tempoQseOrd);
}

void printTrocas(benchData benchData, int tam) {
    int entrada = tam;
    for(int i = 0; i < 5; i++) {
        printf("%d\t%-16d", i + 1, entrada);
        for(int j = 0; j < 4; j++) {
            printf("%-16d", benchData.trocas[i][j]);
        }
        printf("\n");
        entrada = entrada*10;
    }
}

void printCmp(benchData benchData, int tam) {
    int entrada = tam;
    for(int i = 0; i < 5; i++) {
        printf("%d\t%-16d", i + 1, entrada);
        for(int j = 0; j < 4; j++) {
            printf("%-16lld", benchData.cmp[i][j]);
        }
        printf("\n");
        entrada = entrada*10;
    }
}


