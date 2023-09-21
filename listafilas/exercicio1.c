#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define TAM_ESTACIONAMENTO 10

typedef struct sNodo {
    char placa[8];

    struct sNodo *next;
} Nodo;

typedef struct {
    Nodo *head;
    Nodo *tail;
    int size;
} Lista;

void inicializarLista(Lista*);
void tratarErro(int);
int movimentar(Lista*, Lista*, char*, char);
void imprimirLista(Lista*);
void adicionarVeiculo(Lista*, char*);
void removerVeiculo(Lista*, char*, bool, bool);
void *adicionarNodo(Lista *, Nodo*);
int removerNodo(Lista* lista, bool liberarMemoria);

int main() {
    Lista *lista = malloc(sizeof(Lista));
    inicializarLista(lista);

    Lista *listaEspera = malloc(sizeof(Lista));
    inicializarLista(listaEspera);

    tratarErro(movimentar(lista, listaEspera, "ABC-0001", 'C'));
    tratarErro(movimentar(lista, listaEspera, "ABC-0001", 'C'));
    tratarErro(movimentar(lista, listaEspera, "ABC-0002", 'C'));
    tratarErro(movimentar(lista, listaEspera, "ABC-0003", 'C'));
    tratarErro(movimentar(lista, listaEspera, "ABC-0004", 'C'));    
    tratarErro(movimentar(lista, listaEspera, "ABC-0005", 'C'));
    tratarErro(movimentar(lista, listaEspera, "ABC-0006", 'C'));
    tratarErro(movimentar(lista, listaEspera, "ABC-0007", 'C'));
    tratarErro(movimentar(lista, listaEspera, "ABC-0008", 'C'));
    tratarErro(movimentar(lista, listaEspera, "ABC-0009", 'C'));
    tratarErro(movimentar(lista, listaEspera, "ABC-0010", 'C'));
    tratarErro(movimentar(lista, listaEspera, "ABC-0011", 'C'));
    tratarErro(movimentar(lista, listaEspera, "ABC-0012", 'C'));
    tratarErro(movimentar(lista, listaEspera, "ABC-0013", 'C'));    
    tratarErro(movimentar(lista, listaEspera, "ABC-0014", 'C'));

    printf("Estacionamento: \n");
    imprimirLista(lista);

    printf("Fila de espera: \n");
    imprimirLista(listaEspera);
}

void inicializarLista(Lista *lista) {
    lista->head = NULL;
    lista->tail = NULL;
    lista->size = 0;
}

void inicializarNodo(Nodo *nodo, char *placa) {
    nodo->next = NULL;
    strcpy(nodo->placa, placa);
}

void tratarErro(int codigo) {
    if (codigo != 0) {
        switch (codigo)
        {
        case 1:
            printf("Comando invalido.");
            break;
        
        case 2:
            printf("O veiculo ja esta no estacionamento.");
            break;

        case 3:
            printf("O veiculo nao esta no estacionamento.");

        case 4:
            printf("O estacionamento esta vazio.");
            break;

        default:
            break;
        }
    }
}

int movimentar(Lista *lista, Lista *listaEspera, char* placa, char tipoMovimento) {
    Nodo *carro;
    carro = buscar(lista, placa);
    if (tipoMovimento == 'C') {
        if (carro != NULL) {
            return 2;
        }
        if (lista->size < 10) {
            adicionarVeiculo(lista, placa);
        } else {
            adicionarVeiculo(listaEspera, placa);
        }
        
    } else if (tipoMovimento == 'P') {
        if (carro == NULL) {
            carro = buscar(listaEspera, placa);
            if (carro == NULL)
                return 3;
            
            removerVeiculo(listaEspera, carro, true, false);
        } else {
            removerVeiculo(lista, carro, true, true);
            adicionarVeiculo(lista, listaEspera->head);
            removerVeiculo(listaEspera, listaEspera->head, false, false);
        }
    } else
        return 1;

    return 0;
}

void imprimirLista(Lista *lista) {
    Nodo *carro = lista->head;
    int i = 1;
    if (lista->size > 0) {
        do {
            printf("[%d] => %s\n ()", i, carro->placa);
        } while ((carro = carro->next) != NULL);
    }
}

void adicionarVeiculo(Lista *lista, char *placa) {
    Nodo *nodo = malloc(sizeof(Nodo));
    inicializarNodo(nodo, placa);
    adicionarNodo(lista, nodo);
}

void removerVeiculo(Lista *lista, Nodo *nodo, bool liberarMemoria, bool contabilizarGiro) {
    while (lista->head != nodo) {
        adicionarVeiculo(lista, lista->head);
        removerNodo(lista, false);
    }
    
}

void *adicionarNodo(Lista *lista, Nodo *nodo) {
    lista->tail->next = nodo;
    lista->tail = nodo;
}

int removerNodo(Lista* lista, bool liberarMemoria) {
    Nodo *nodoTemp;
    if (lista->size == 0)
        return 4;

    nodoTemp = lista->head;
    lista->head = lista->head->next;

    lista->size--;
    if (liberarMemoria)
        free(nodoTemp);

    return 0;
}