#include <stdio.h>
#include <stdlib.h>

typedef struct sNodo {
    struct sNodo *prev;
    struct sNodo *next;
    char info[10]
} Nodo;

typedef struct {
    Nodo *head;
    Nodo *tail;
    int size;
} Lista;

Lista *inicializarLista();
void inicializarNodo(Nodo*);
int adicionarNodo(Lista*, Nodo*, char[10]);
void tratarException(int);
int removerNodo(Lista*, Nodo*);
void imprimirLista(Lista*);

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
    Lista *lista = malloc(sizeof(Lista));
    lista->head = NULL;
    lista->tail = NULL;
    lista->size = 0;

    return lista;
}

void inicializarNodo(Nodo *nodo) {
    nodo->next = NULL;
    nodo->prev = NULL;

    return nodo;
}

int adicionarNodo(Lista *lista, Nodo *pivo, char info[10]) {
    Nodo *novoEl = 0;
    novoEl = malloc(sizeof(Nodo));
    inicializarNodo(novoEl);
    printf("%x", *novoEl);
    if ((pivo == NULL) && (lista->size > 0)) {
        return 1;
    }
    if (lista->size == 0) {
        lista->head = novoEl;
        lista->tail = novoEl;
    } else {
        novoEl->next = pivo->next;
        novoEl->prev = pivo;

        if (pivo->next == NULL)
            lista->tail = novoEl;
        else
            pivo->next->prev = novoEl;

        pivo->next = novoEl;
    }
    lista->size++;

    return 0;
}

void tratarException(int errorCode) {
    switch (errorCode)
    {
    case 1:
        printf("Pivo so pode ser nulo caso a lista esteja vazia");
        break;
    case 2:
        printf("A lista esta vazia");
        break;
    default:
        break;
    }
}

int removerNodo(Lista *lista, Nodo *nodo) {
    if ((nodo != NULL) && (lista->size > 0)) {
        if (nodo == lista->head) {
            lista->head = nodo->next;
            if (lista->head == NULL)
                lista->tail = NULL;
            else
                nodo->next->prev = NULL;
        } else {
            nodo->prev->next = nodo->next;
            if (nodo->next == NULL)
                lista->tail = nodo->prev;
            else
                nodo->next->prev = nodo->prev;
        }
    }
    free(nodo);
    lista->size--;

    return 0;
}

void imprimirLista(Lista* lista) {
    Nodo *el;
    el = lista->head;
    int i = 0;
    while (el != NULL) {
        printf("[%d] => %s\n", i, el->info);
        i++;
        el = el->next;
    };
}