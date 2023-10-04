#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct sNodo {
    char *info;
    struct sNodo *next;
    struct sNodo *prev;
} Nodo;

typedef struct {
    Nodo *head;
    Nodo *tail;
    int size;
} Lista;

Lista* inicializarLista();
Nodo* inicializarNodo();
void adicionarNodo(Lista*, Nodo*, Nodo*);
int removerNodo(Lista*, Nodo*);
void imprimirLista(Lista*);
void tratarException(int);
void liberarNodo(Nodo*);
void liberarLista(Lista*);
Nodo* procurarNodo(Lista*, char*);
Nodo* criarNodo(char*);

Lista* inicializarLista() {
    Lista* lista = (Lista*) malloc(sizeof(Lista));

    lista->head = NULL;
    lista->tail = NULL;
    lista->size = 0;

    return lista;
}

Nodo* inicializarNodo() {
    Nodo* nodo = (Nodo*) malloc(sizeof(Nodo));
    nodo->next = NULL;
    nodo->prev = NULL;
}

void adicionarNodo(Lista* lista, Nodo* pivo, Nodo* nodo) {
    if (pivo == NULL) {
        if (lista->head != NULL) {
            nodo->next = lista->head;
            lista->head->prev = nodo;
            lista->head = nodo;
        } else {
            lista->head = nodo;
            lista->tail = nodo;
        }
    } else {
        nodo->next = pivo->next;
        nodo->prev = pivo;
        if (nodo->next != NULL) {
            nodo->next->prev = nodo;
        } else {
            lista->tail = nodo;
        }
    }
    lista->size++;
    return 0;
}

void imprimirLista(Lista* lista) {
    Nodo* el;
    el = lista->head;
    while (el != NULL) {
        printf("|%s|", el->info);
        el = el->next;
    };
    printf(": [%d]\n", lista->size);
}

int removerNodo(Lista* lista, Nodo* nodo) {
    if (lista->size == 0) {
        return 1;
    }
    if (nodo == lista->head) {
        lista->head = nodo->next;
    }
    if (nodo == lista->tail) {
        lista->tail = nodo->prev;
    }
    if (nodo->next != NULL) {
        nodo->next->prev = nodo->prev;
    }
    if (nodo->prev != NULL) {

    }

    return 4;
}

void tratarException(int errorCode) {
    switch (errorCode) {
    case 1:
        printf("Lista esta vazia.\n");
        break;
    case 2:
        printf("O nodo informado e o ultimo da lista.\n");
        break;
    case 3:
        printf("O nodo informado ja esta na lista.\n");
        break;
    case 4:
        printf("O nodo informado nao esta na lista.\n");
        break;
    case 5:
        printf("So e possivel inserir com pivo NULL em listas vazias.\n");
        break;
    default:
        return;
    }
};

void liberarNodo(Nodo* nodo){
    free(nodo->info);
    free(nodo);
}

void liberarLista(Lista* lista) {
    Nodo* nodo = lista->head;
    Nodo* nodoTemp;
    while (nodo != NULL) {
        nodoTemp = nodo;
        nodo = nodo->next;
        liberarNodo(nodoTemp);
    }
    free(lista);
}

Nodo* procurarNodo(Lista* lista, char* info) {
    Nodo* ref = lista->head;
    while (ref != NULL) {
        if (strcmp(info, ref->info) == 0)
            return ref;

        ref = ref->next;
    }
    return NULL;
}

Nodo* criarNodo(char* info) {
    Nodo* nodo = inicializarNodo();
    nodo->info = (char*) malloc(sizeof(char) * (strlen(info) + 1));
    strcpy(nodo->info, info);
    return nodo;
}