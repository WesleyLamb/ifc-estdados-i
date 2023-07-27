#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define M 10
#define N 10

void popularMatriz(int**, int, int);
void escreverMatriz(int**, int, int);
void escreverVetor(int*, int);
int somaImparesLinha(int**, int, int);
int mediaParesColuna(int**, int, int);


int main() {
    int **ma, *sl, *mc;
    srand(time(NULL));
    ma = malloc(sizeof(int*) * N);
    for (int i = 0; i < N; i++) {
        ma[i] = (int*) malloc(sizeof(int) * M);
    }
    popularMatriz(ma, N, M);

    sl = malloc(sizeof(int*) * N);
    mc = malloc(sizeof(int*) * M);

    for (int i = 0; i < N; i++) {
        sl[i] = somaImparesLinha(ma, i, M);
    }

    for (int j = 0; j < M; j++) {
        mc[j] = mediaParesColuna(ma, N, j);
    }

    printf("ma = \n");
    escreverMatriz(ma, N, M);

    printf("\nsl = \n");
    escreverVetor(sl, N);

    printf("\nmc = \n");
    escreverVetor(mc, M);
    for (int i = 0; i < N; i++) {
        free(ma[i]);
    }
    free(ma);
    free(sl);
    free(mc);

    return 0;
}

void popularMatriz(int **matriz, int contLinhas, int contColunas) {
    for (int i = 0; i < contLinhas; i++) {
        for (int j = 0; j < contColunas; j++) {
            matriz[i][j] = (rand() % 99) + 1;
        }
    }
}

int somaImparesLinha(int **matriz, int linha, int contColunas) {
    int soma = 0;
    for (int j = 0; j < contColunas; j++) {
        if (matriz[linha][j] % 2 == 1) {
            soma += matriz[linha][j];
        }
    }
    return soma;
}

int mediaParesColuna(int **matriz, int contLinhas, int coluna) {
    int somaMedia = 0, contMedia = 0;
    for (int i = 0; i < contLinhas; i++) {
        if (matriz[i][coluna] % 2 == 0) {
            somaMedia += matriz[i][coluna];
            contMedia++;
        }
    }
    if (contMedia > 0)
        return somaMedia / contMedia;
    return 0;
}

void escreverMatriz(int **matriz, int contLinhas, int contColunas) {
    for (int i = 0; i < contLinhas; i++) {
        for (int j = 0; j< contColunas; j++) {
            printf("%02d ", matriz[i][j]);
        }
        printf("\n");
    }
}

void escreverVetor(int *vetor, int contLinhas) {
    for (int i = 0; i < contLinhas; i++) {
        printf("%02d ", vetor[i]);
    }
}