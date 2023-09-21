#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define TAM_ESTACIONAMENTO 10

typedef struct sNodo {
    char placa[8];
    int movimentos;
    struct sNodo *next;
} Nodo;

typedef struct {
    Nodo *head;
    Nodo *tail;
    int size;
} Lista;

void inicializarLista(Lista*);
void inicializarNodo(Nodo*);
void tratarErro(int);
int movimentar(Lista*, Lista*, char*, char);
void adicionarVeiculo(Lista*, Nodo*);
Nodo *removerVeiculo(Lista*);
void imprimirLista(Lista*);
Nodo *buscar(Lista*, char*);

int main() {
    Lista *lista = malloc(sizeof(Lista));
    inicializarLista(lista);

    Lista *listaEspera = malloc(sizeof(Lista));
    inicializarLista(listaEspera);

    tratarErro(movimentar(lista, listaEspera, "ABC-0001", 'C'));
    // tratarErro(movimentar(lista, listaEspera, "ABC-0001", 'C'));
    // tratarErro(movimentar(lista, listaEspera, "ABC-0002", 'C'));
    // tratarErro(movimentar(lista, listaEspera, "ABC-0003", 'C'));
    // tratarErro(movimentar(lista, listaEspera, "ABC-0004", 'C'));    
    // tratarErro(movimentar(lista, listaEspera, "ABC-0005", 'C'));
    // tratarErro(movimentar(lista, listaEspera, "ABC-0006", 'C'));
    // tratarErro(movimentar(lista, listaEspera, "ABC-0007", 'C'));
    // tratarErro(movimentar(lista, listaEspera, "ABC-0008", 'C'));
    // tratarErro(movimentar(lista, listaEspera, "ABC-0009", 'C'));
    // tratarErro(movimentar(lista, listaEspera, "ABC-0010", 'C'));
    // tratarErro(movimentar(lista, listaEspera, "ABC-0011", 'C'));
    // tratarErro(movimentar(lista, listaEspera, "ABC-0012", 'C'));
    // tratarErro(movimentar(lista, listaEspera, "ABC-0013", 'C'));    
    // tratarErro(movimentar(lista, listaEspera, "ABC-0014", 'C'));

    return 0;
}

void inicializarLista(Lista *lista) {
    lista->head = NULL;
    lista->tail = NULL;
    lista->size = 0;
}

void inicializarNodo(Nodo *nodo) {
    nodo->next = NULL;
    nodo->movimentos = 0;
}

void tratarErro(int erro) {
    if (erro != 0) {
        switch (erro)
        {
        case 1:
            printf("Acao invalida.\n");
            break;
        case 2:
            printf("Veiculo ja esta no estacionamento/fila de espera.\n");
            break;
        case 3:
            printf("Veiculo nao esta no estacionamento/fila de espera.\n");
            break;
        default:
            break;
        }
    }
}

int movimentar(Lista *lista, Lista *listaEspera, char *placa, char acao) {
    Nodo *carro = buscar(lista, placa);
    if (acao == 'C') {
        if (carro == NULL)
            carro = buscar(listaEspera, placa);
        if (carro != NULL)
            return 2;
        
        carro = malloc(sizeof(Nodo));
        inicializarNodo(carro);
        strcpy(carro->placa, placa);

        if (lista->size < TAM_ESTACIONAMENTO) {
            adicionarVeiculo(lista, carro);
        } else {
            adicionarVeiculo(listaEspera, carro);
        }
        imprimirLista(lista);
    } else if (acao == 'P') {
        if (carro != NULL) {
            Nodo *nodoTemp = lista->head;
            Nodo *head = lista->head;
            do {
                nodoTemp = removerVeiculo(lista);
                if (nodoTemp != carro) {
                    adicionarVeiculo(lista, nodoTemp);
                }
                nodoTemp->movimentos++;
            } while ((nodoTemp = lista->head) != head);
            free(carro);
            adicionarVeiculo(lista, removerVeiculo(listaEspera));
            imprimirLista(lista);
        } else {
            carro = buscar(listaEspera, placa);
            if (carro == NULL)
                return 3;
            Nodo *nodoTemp = listaEspera->head;
            Nodo *head = listaEspera->head;
            do {
                nodoTemp = removerVeiculo(listaEspera);
                if (nodoTemp != carro) {
                    adicionarVeiculo(listaEspera, nodoTemp);
                }
            } while ((nodoTemp = listaEspera->head) != head);
            free(carro);
            imprimirLista(listaEspera);
        }
    } else {
        return 1;
    }
}

void adicionarVeiculo(Lista *lista, Nodo *nodo) {
    if (lista->tail != NULL)
        lista->tail->next = nodo;
    lista->tail = nodo;
}

Nodo *removerVeiculo(Lista *lista) {
    Nodo *nodo = lista->head;
    lista->head = lista->head->next;
    return nodo;
}

void imprimirLista(Lista *lista) {
    if (lista->size > 0) {
        Nodo *nodo = lista->head;
        do {
            printf("|%s(%d)", nodo->placa, nodo->movimentos);
        } while ((nodo = nodo->next) != NULL);
        printf("\n");
    }
}
Nodo *buscar(Lista *lista, char *placa) {
    Nodo *nodo = lista->head;
    do {
        if (nodo == NULL)
            return NULL;
        if (strcmp(nodo->placa, placa) == 0)
            return nodo;
    } while ((nodo = nodo->next) != NULL);
    return NULL;
}