#include "sorting.h"

void shellSort(int* vet, int size) {
    int i, j, value;

    int h = 1;
    while(h < size) {
        h = 3*h+1;
    }
    while (h > 0) {
        for(i = h; i < size; i++) {
            value = vet[i];
            j = i;
            while (j > h-1 && value <= vet[j - h]) {
                vet[j] = vet[j - h];
                j = j - h;
            }
            vet[j] = value;
        }
        h = h/3;
    }
}


void radixSortL(int* vet, int size) {
    int i, j, k;
    int B[size];
    int maior = vet[0];
    int exp = 1;

    for (i = 0; i < size; i++) {
        if (vet[i] > maior)
    	    maior = vet[i];
    }

    while (maior/exp > 0) {
        int bucket[10] = { 0 };
        for (i = 0; i < size; i++)
    	    bucket[vet[i] / exp % 10]++;
        for (i = 1; i < 10; i++)
    	    bucket[i] += bucket[i - 1];
        for (i = size - 1; i >= 0; i--)
    	    B[--bucket[vet[i] / exp % 10]] = vet[i];
        for (i = 0; i < size; i++)
    	    vet[i] = B[i];
        exp *= 10;
    }
}