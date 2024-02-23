#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct sNodo {
    char *info;
    struct sNodo *next;
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

// int main() {
//     Lista *lista;
//     lista = inicializarLista();
//     Nodo* nodoRemovido;
//     int errorCode;

//     printf("\nPasso 1: \n");
//     nodoRemovido = lista->head;
//     if ((errorCode = removerNodo(lista, nodoRemovido)) != 0)
//         tratarException(errorCode);
//     else
//         free(nodoRemovido);
//     imprimirLista(lista);

//     printf("\nPasso 2:\n");
//     Nodo* nodoJoao = criarNodo("Joao");
//     adicionarNodo(lista, lista->tail, nodoJoao);
//     imprimirLista(lista);

//     printf("\nPasso 3:\n");
//     Nodo* nodoMaria = criarNodo("Maria");
//     adicionarNodo(lista, lista->head, nodoMaria);
//     imprimirLista(lista);

//     printf("\nPasso 4:\n");
//     Nodo* nodoLucas = criarNodo("Lucas");
//     adicionarNodo(lista, nodoMaria, nodoLucas);
//     imprimirLista(lista);

//     printf("\nPasso 5:\n");
//     nodoRemovido = nodoLucas;
//     if ((errorCode = removerNodo(lista, nodoRemovido)) != 0)
//         tratarException(errorCode);
//     else
//         free(nodoRemovido);
//     imprimirLista(lista);

//     printf("\nPasso 6:\n");
//     adicionarNodo(lista, NULL, criarNodo("Sandro"));
//     imprimirLista(lista);

//     printf("\nPasso 7:\n");
//     adicionarNodo(lista, NULL, criarNodo("Pedro"));
//     imprimirLista(lista);

//     printf("\nPasso 8:\n");
//     nodoRemovido = lista->tail;
//     if ((errorCode = removerNodo(lista, nodoRemovido)) != 0)
//         tratarException(errorCode);
//     else
//         free(nodoRemovido);
//     imprimirLista(lista);

//     printf("\nPasso 9:\n");
//     nodoRemovido = lista->head;
//     if ((errorCode = removerNodo(lista, nodoRemovido)) != 0)
//         tratarException(errorCode);
//     else
//         free(nodoRemovido);
//     imprimirLista(lista);

//     printf("\nPasso 10:\n");
//     nodoRemovido = lista->tail;
//     if ((errorCode = removerNodo(lista, nodoRemovido)) != 0)
//         tratarException(errorCode);
//     else
//         free(nodoRemovido);
//     imprimirLista(lista);

//     return 0;
// }

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
}

void adicionarNodo(Lista* lista, Nodo* pivo, Nodo* nodo) {
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
    lista->size++;
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
        // Se o nodo a ser removido for o primeiro da lista
        lista->head = nodo->next;
        lista->size --;
        return 0;
    } else {
        // Se não for o primeiro, percorre até encontrar o nodo anterior a ele
        Nodo* nodoTemp = lista->head;
        do {
            if (nodoTemp->next == nodo) {
                nodoTemp->next = nodo->next;
                if (nodo == lista->tail) {
                    lista->tail = nodoTemp;
                }
                lista->size--;
                return 0;
            }
        } while ((nodoTemp = nodoTemp->next) != NULL);
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