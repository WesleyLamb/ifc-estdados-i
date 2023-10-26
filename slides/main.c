#include "sorting.c"
#include <stdlib.h>
#include <time.h>

#define VET_SIZE 20

int main() {
    // int* vet = malloc(VET_SIZE * sizeof(int));
    srand(time(NULL));
    int vet[] = {10,9,8,7,6,5,4,3,2,1,0,-1,-2,-3,-4,-5,-6,-7,-8,-9} ;
    // for(int i = 0; i < VET_SIZE; i++) {
    //     vet[i] = rand() % VET_SIZE;
    // }

    int* shellSortVet = malloc(VET_SIZE * sizeof(int));
    int* radixSortLVet = malloc(VET_SIZE * sizeof(int));

    for(int i = 0; i < VET_SIZE; i++) {
        shellSortVet[i] = vet[i];
        radixSortLVet[i] = vet[i];
    }

    clock_t start = clock();
    shellSort(shellSortVet, VET_SIZE);
    clock_t end = clock();
    // for (int i =0; i < VET_SIZE; i++) {
    //     printf("%d ", shellSortVet[i]);
    // }
    printf("\n\nShell Sort: %fs\n", (double)(end - start) / CLOCKS_PER_SEC);

    start = clock();
    radixSortL(radixSortLVet, VET_SIZE);
    end = clock();
    // for (int i =0; i < VET_SIZE; i++) {
    //     printf("%d ", radixSortLVet[i]);
    // }
    printf("\n\nRadix Sort (Least Significant Digit): %fs\n", (double)(end - start) / CLOCKS_PER_SEC);

    return 0;
}