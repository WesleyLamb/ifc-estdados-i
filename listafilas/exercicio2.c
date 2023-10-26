#include "../fundamentos/lista-dupla-int.c"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void pqinsert(Lista*, int);
Nodo* pqmindelete(Lista*);
bool isempty(Lista*);

int main() {
    Lista* fila = inicializarLista();
    Nodo* nodo;
    pqinsert(fila, 20);
    pqinsert(fila, 13);
    pqinsert(fila, 4);
    pqinsert(fila, 2);
    pqinsert(fila, 18);
    pqinsert(fila, 40);
    pqinsert(fila, 2);
    pqinsert(fila, 19);
    pqinsert(fila, 1);

    while (!isempty(fila)) {
        nodo = pqmindelete(fila);
        printf("%i\n", nodo->info);
        free(nodo);
    }
    return 0;
}

void pqinsert(Lista* fila, int valor) {
    adicionarNodo(fila, fila->tail, criarNodo(valor));
}

Nodo* pqmindelete(Lista* fila) {
    Nodo* nodo = procurarMenorNodo(fila);
    removerNodo(fila, nodo);
    return nodo;
}

bool isempty(Lista* fila) {
    return fila->size == 0;
}

