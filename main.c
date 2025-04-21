#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "introsort.h"
#include "windows.h"

int printMenu(){
    int escolha;

    printf("------------------- Escolha a Opcao de Ordenacao Desejada -------------------\n");
    printf("1. Selection\n2.Insertion\n3.Mergesort\n4.Quicksort,\n5.Introsort\n");
    scanf("%d", &escolha);

    return escolha;
}

int main(){
    benchData dados;
    int escolha;
    int *vetorTeste;
    vetorTeste = geraVetRandom(10, time(NULL));
    for(int i=0; i<10;i++){
        printf("%d ", vetorTeste[i]);
    }

    escolha = printMenu();
    switch(escolha) {
        case 1:
            selection(vetorTeste, &dados, 1, 10);
            break;
        case 2:
            insertion(vetorTeste, &dados, 2, 10);
            break;
        case 3:
            mergeSort(vetorTeste, 0, 9, &dados, 3);
            break;
        case 4:
            quickSort(vetorTeste, 0, 9, &dados, 4);
            break;
        case 5:
            int maxDepth = log2(10)*2;
            introSort(vetorTeste, 0, 9, maxDepth, &dados, 5);
            break;
    }

    for(int i=0; i<10;i++){
        printf("%d ", vetorTeste[i]);
    }
    return 0;
}

