#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "introsort.h"

int main() {
    clock_t t_ini, t_fim;
    int opcao, i, j, tam = 5, semente, *vetor, profMax;
    double tempo[5], tAleatorio, tCrescente, tDecrescente, tQuaseOrdenado;
    benchData bench;

    opcao = menuBench();

    if (opcao < 1 || opcao > 5) {
        printf("\ninvalida.\n");
        return 1;
    }

    printTempo(opcao);

    for (i = 0; i < 5; i++) {

        for (int tipo = 0; tipo < 4; tipo++) {
            iniciaBenchData(&bench);
            if (tipo == 0 || tipo == 3) { // aleatório ou quase ordenado
                for (j = 0; j < 4; j++) {
                    vetor = tipo == 0 ? geraVetRandom(tam, rand()) : geraQuaseOrdenados(tam, 10);
                    t_ini = clock();
                    profMax = 2 * log2(tam);
                    switch (opcao) {
                        case 1: insertion(vetor, &bench, j, tam); break;
                        case 2: selection(vetor, &bench, j, tam); break;
                        case 3: mergeSort(vetor, 0, tam - 1, &bench, j); break;
                        case 4: quickSort(vetor, 0, tam - 1, &bench, j); break;
                        case 5: introSort(vetor, 0, tam - 1, profMax, &bench, j); break;
                    }
                    t_fim = clock();
                    tempo[j] = ((double)(t_fim - t_ini)) * 1000.0 / CLOCKS_PER_SEC;
                    free(vetor);
                }
                if (tipo == 0) {
                    tAleatorio = calculaMediaTempo(tempo);
                    bench.trocas[i][0] = calculaMediaTrocas(&bench);
                    bench.cmp[i][0] = calculaMediaComparacoes(&bench);
                } else {
                    tQuaseOrdenado = calculaMediaTempo(tempo);
                    bench.trocas[i][3] = calculaMediaTrocas(&bench);
                    bench.cmp[i][3] = calculaMediaComparacoes(&bench);
                }
            } else {
                vetor = geraOrdenados(tam, tipo - 1);
                t_ini = clock();
                profMax = 2 * log2(tam);
                switch (opcao) {
                    case 1: insertion(vetor, &bench, tipo, tam); break;
                    case 2: selection(vetor, &bench, tipo, tam); break;
                    //void selection(int *vetor, benchData *benchData, int indDado, int tam);
                    case 3: mergeSort(vetor, 0, tam - 1, &bench, tipo); break;
                    case 4: quickSort(vetor, 0, tam - 1, &bench, tipo); break;
                    case 5: introSort(vetor, 0, tam - 1, profMax, &bench, tipo); break;
                }
                t_fim = clock();
                if (tipo == 1) {
                    tCrescente = ((double)(t_fim - t_ini)) * 1000.0 / CLOCKS_PER_SEC;
                    bench.trocas[i][1] = bench.mTrocas[1];
                    bench.cmp[i][1] = bench.mCmp[1];
                } else {
                    tDecrescente = ((double)(t_fim - t_ini)) * 1000.0 / CLOCKS_PER_SEC;
                    bench.trocas[i][2] = bench.mTrocas[2];
                    bench.cmp[i][2] = bench.mCmp[2];
                }
                free(vetor);
            }
        }

        printTempos(i + 1, tAleatorio, tCrescente, tDecrescente, tQuaseOrdenado, tam);
        tam = tam * 10;
    }


    comps(bench,5);
    trocas(bench, 5);

    return 0;
}
