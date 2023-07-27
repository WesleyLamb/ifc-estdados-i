#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10
#define M 15

typedef struct {
    int r;
    int g;
    int b;
} RGB;

void popularMatriz(RGB**, int, int);
void popularGrayScale(int**, RGB**, int, int);
void escreverMatriz(RGB**, int, int);
void escreverGrayScale(int**, int, int);
int rgbToGray(RGB);


int main() {
    srand(time(NULL));

    RGB **matriz;
    int **grayScale;
    matriz = malloc(sizeof(RGB*) * N);
    for (int i = 0; i < N; i++) {
        matriz[i] = malloc(sizeof(RGB) * M);
    }

    grayScale = malloc(sizeof(int*) * N);
    for (int i = 0; i < N; i++) {
        grayScale[i] = malloc(sizeof(int) * M);
    }

    popularMatriz(matriz, N, M);
    popularGrayScale(grayScale, matriz, N, M);

    escreverMatriz(matriz, N, M);
    escreverGrayScale(grayScale, N, M);

    for (int i = 0; i < N; i++) {
        free(matriz[i]);
        free(grayScale[i]);
    }
    free(matriz);
    free(grayScale);

    return 0;
}

void popularMatriz(RGB **matriz, int contLinhas, int contColunas) {
    for (int i = 0; i < contLinhas; i++) {
        for (int j = 0; j < contColunas; j++) {
            matriz[i][j].r = rand() % 256;
            matriz[i][j].g = rand() % 256;
            matriz[i][j].b = rand() % 256;
        }
    }
}

void popularGrayScale(int **grayScale, RGB **matriz, int contLinhas, int contColunas) {
    for (int i = 0; i < contLinhas; i++) {
        for (int j = 0; j < contColunas; j++) {
            grayScale[i][j] = rgbToGray(matriz[i][j]);
        }
    }
}

int rgbToGray(RGB rgb) {
    return (rgb.r * 0.3) + (rgb.g * 0.59) + (rgb.b * 0.11);
}

void escreverMatriz(RGB **matriz, int contLinhas, int contColunas) {
    for (int i = 0; i < contLinhas; i++) {
        for (int j = 0; j < contColunas; j++) {
            printf("%03d-%03d-%03d ", matriz[i][j].r, matriz[i][j].g, matriz[i][j].b);
        }
        printf("\n");
    }
}

void escreverGrayScale(int **grayScale, int contLinhas, int contColunas) {
    for (int i = 0; i < contLinhas; i++) {
        for (int j = 0; j < contColunas; j++) {
            printf("%d ", grayScale[i][j]);
        }
        printf("\n");
    }
}