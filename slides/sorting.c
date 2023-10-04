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

void radixSortM(int* vet, int size) {
    int i, j, k, m, n, p, q, t;
    int* cnt = (int*)malloc(sizeof(int)*256);
    int* tmp = (int*)malloc(sizeof(int)*size);

    for (k = 31; k >= 0; k -= 8) {
        for (i = 0; i < 256; i++) {
            cnt[i] = 0;
        }
        for (i = 0; i < size; i++) {
            cnt[(vet[i] >> k) & 0xff]++;
        }
        for (i = 1; i < 256; i++) {
            cnt[i] += cnt[i - 1];
        }
        for (i = size - 1; i >= 0; i--) {
            j = (vet[i] >> k) & 0xff;
            tmp[--cnt[j]] = vet[i];
        }
        for (i = 0; i < size; i++) {
            vet[i] = tmp[i];
        }
    }

    free(cnt);
    free(tmp);
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