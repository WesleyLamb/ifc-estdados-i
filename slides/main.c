#include "sorting.c"
#include <stdlib.h>
#include <time.h>

#define VET_SIZE 10000

int main() {
    int* vet = malloc(VET_SIZE * sizeof(int));
    srand(time(NULL));

    for(int i = 0; i < VET_SIZE; i++) {
        vet[i] = rand() % VET_SIZE;
    }

    int* shellSortVet = malloc(VET_SIZE * sizeof(int));
    int* radixSortMVet = malloc(VET_SIZE * sizeof(int));
    int* radixSortLVet = malloc(VET_SIZE * sizeof(int));

    for(int i = 0; i < VET_SIZE; i++) {
        shellSortVet[i] = vet[i];
        radixSortMVet[i] = vet[i];
        radixSortLVet[i] = vet[i];
    }

    clock_t start = clock();
    shellSort(shellSortVet, VET_SIZE);
    clock_t end = clock();
    for (int i =0; i < VET_SIZE; i++) {
        printf("%d ", shellSortVet[i]);
    }
    printf("Shell Sort: %fs\n", (double)(end - start) / CLOCKS_PER_SEC);

    start = clock();
    radixSortM(radixSortMVet, VET_SIZE);
    end = clock();
    for (int i =0; i < VET_SIZE; i++) {
        printf("%d ", radixSortMVet[i]);
    }
    printf("Radix Sort (Most Significant Digit): %fs\n", (double)(end - start) / CLOCKS_PER_SEC);

    start = clock();
    radixSortL(radixSortLVet, VET_SIZE);
    end = clock();
    for (int i =0; i < VET_SIZE; i++) {
        printf("%d ", radixSortLVet[i]);
    }
    printf("Radix Sort (Least Significant Digit): %fs\n", (double)(end - start) / CLOCKS_PER_SEC);

    return 0;
}