#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct sNodo {
    char info[10];
    struct sNodo *next;
} Nodo;

typedef struct {
    Nodo *head;
    Nodo *tail;
    int size;
} Lista;

Lista *inicializarLista();
void inicializarNodo(Nodo*);
Nodo *adicionarNodo(Lista*, Nodo*, char[10]);
void imprimirLista(Lista*);
int removerNodo(Lista*, Nodo*);
void tratarException(int);
void liberarLista(Lista*);
Nodo *procurarNodo(Lista*, char[10]);

int main() {
    Lista *lista;
    lista = inicializarLista();

    printf("\nPasso 1: \n");
    int retorno = removerNodo(lista, lista->head);
    tratarException(retorno);
    imprimirLista(lista);

    printf("\nPasso 2:\n");
    adicionarNodo(lista, lista->tail, "Joao");
    imprimirLista(lista);

    printf("\nPasso 3:\n");
    Nodo *nodoMaria = adicionarNodo(lista, lista->head, "Maria");
    imprimirLista(lista);

    // procurarNodo(&lista, "Maria");
    printf("\nPasso 4:\n");
    Nodo *nodoLucas =  adicionarNodo(lista, nodoMaria, "Lucas");
    imprimirLista(lista);

    printf("\nPasso 5:\n");
    removerNodo(lista, nodoLucas);
    imprimirLista(lista);

    printf("\nPasso 6:\n");
    adicionarNodo(lista, NULL, "Sandro");
    imprimirLista(lista);

    printf("\nPasso 7:\n");
    adicionarNodo(lista, NULL, "Pedro");
    imprimirLista(lista);

    printf("\nPasso 8:\n");
    removerNodo(lista, lista->tail);
    imprimirLista(lista);

    printf("\nPasso 9:\n");
    removerNodo(lista, lista->head);
    imprimirLista(lista);

    printf("\nPasso 10:\n");
    removerNodo(lista, NULL);
    imprimirLista(lista);

    return 0;
}

Lista *inicializarLista() {
    Lista *lista = (Lista*) malloc(sizeof(Lista));

    lista->head = NULL;
    lista->tail = NULL;
    lista->size = 0;

    return lista;
}

void inicializarNodo(Nodo *nodo) {
    nodo->next = NULL;
}

Nodo *adicionarNodo(Lista *lista, Nodo *pivo, char info[10]) {
    Nodo *nodo = 0;
    nodo = malloc(sizeof(Nodo));
    inicializarNodo(nodo);
    strcpy(nodo->info, info);

    if (pivo == NULL) {
        if (lista->size == 0) 
            lista->tail = nodo;

        nodo->next = lista->head;
        lista->head = nodo;
    } else {
        if (pivo->next == NULL)
            lista->tail = nodo;

        nodo->next = pivo->next;
        pivo->next = nodo;
    }
    return nodo;
}

void imprimirLista(Lista *lista) {
    Nodo *el;
    el = lista->head;
    int i = 0;
    while (el != NULL) {
        printf("[%d] => %s\n", i, el->info);
        i++;
        el = el->next;
    };
}

int removerNodo(Lista* lista, Nodo* pivo) {
    Nodo *nodoTemp;
    if (lista->size == 0)
        return 1;

    if (pivo == NULL) {
        nodoTemp = lista->head;
        if (lista->head == lista->tail)
            lista->tail = NULL;

        lista->head = nodoTemp->next;
    } else {
        if (pivo->next == NULL) 
            return 2;
        
        nodoTemp = pivo->next;
        pivo->next = nodoTemp->next;

        if (pivo->next == NULL)
            lista->tail = pivo;
    }

    lista->size--;
    free(nodoTemp);

    return 0;
}

void tratarException(int errorCode) {
    switch (errorCode) {
    case 1:
        printf("Lista esta vazia.\n");
        break;
    case 2:
        printf("O nodo informado e o ultimo da lista.\n");
        break;
    default:
        return;
    }
};

void liberarLista(Lista *lista) {
    Nodo *nodo = lista->head;
    while (nodo != NULL) {
        nodo = lista->head;
        removerNodo(lista, nodo);
    }
    removerNodo(lista, NULL);
    free(lista);
}

Nodo *procurarNodo(Lista *lista, char info[10]) {
    Nodo *ref = lista->head;
    while (ref != NULL) {
        if (strcmp(info, ref->info) == 0) 
            return ref;
        
        ref = ref->next;
    }
    return NULL;
}