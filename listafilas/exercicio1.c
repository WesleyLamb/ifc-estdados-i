#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../fundamentos/lista-simples.c"

#define TAM_ESTACIONAMENTO 10

void movimentar(Lista*, Lista*, char*, char);
void imprimirListas(Lista*, Lista*);
void adicionarVeiculo(Lista*, Nodo*);
void adicionarVeiculo(Lista*, Nodo*);
Nodo* removerVeiculo(Lista*);

int main() {
    Lista* lista = inicializarLista();
    Lista* listaEspera = inicializarLista();

    printf("\nPasso 1:\n");
    movimentar(lista, listaEspera, "ABC-0001", 'C');
    printf("\nPasso 2:\n");
    movimentar(lista, listaEspera, "ABC-0001", 'C');
    printf("\nPasso 3:\n");
    movimentar(lista, listaEspera, "ABC-0002", 'C');
    printf("\nPasso 4:\n");
    movimentar(lista, listaEspera, "ABC-0003", 'C');
    printf("\nPasso 5:\n");
    movimentar(lista, listaEspera, "ABC-0004", 'C');
    printf("\nPasso 6:\n");
    movimentar(lista, listaEspera, "ABC-0005", 'C');
    printf("\nPasso 7:\n");
    movimentar(lista, listaEspera, "ABC-0006", 'C');
    printf("\nPasso 8:\n");
    movimentar(lista, listaEspera, "ABC-0007", 'C');
    printf("\nPasso 9:\n");
    movimentar(lista, listaEspera, "ABC-0008", 'C');
    printf("\nPasso 10:\n");
    movimentar(lista, listaEspera, "ABC-0009", 'C');
    printf("\nPasso 11:\n");
    movimentar(lista, listaEspera, "ABC-0010", 'C');
    printf("\nPasso 12:\n");
    movimentar(lista, listaEspera, "ABC-0011", 'C');
    printf("\nPasso 13:\n");
    movimentar(lista, listaEspera, "ABC-0012", 'C');
    printf("\nPasso 14:\n");
    movimentar(lista, listaEspera, "ABC-0013", 'C');
    printf("\nPasso 15:\n");
    movimentar(lista, listaEspera, "ABC-0002", 'P');
    printf("\nPasso 16:\n");
    movimentar(lista, listaEspera, "ABC-0012", 'P');

}

void movimentar(Lista* lista, Lista* listaEspera, char* placa, char acao) {
    Nodo* carro;
    int movimentacoes = 0;
    switch (acao)
    {
    case 'C':
        carro = procurarNodo(lista, placa);
        if (carro == NULL)
            carro = procurarNodo(listaEspera, placa);
        if (carro != NULL) {
            printf("Veiculo ja esta no estacionamento/fila de espera!\n");
            return;
        }

        if (lista->size < TAM_ESTACIONAMENTO) {
            adicionarVeiculo(lista, criarNodo(placa));
        } else {
            adicionarVeiculo(listaEspera, criarNodo(placa));
        }
        break;
    case 'P':
        carro = procurarNodo(lista, placa);
        if (carro != NULL) {
            if (carro == lista->head) {
                carro = removerVeiculo(lista);
                free(carro);
            } else {
                Nodo* head = lista->head;
                Nodo* carroRemovido;
                int i = 0;
                do {
                    carroRemovido = removerVeiculo(lista);
                    if (carroRemovido == carro) {
                        free(carroRemovido);
                        movimentacoes = i;
                    } else {
                        adicionarVeiculo(lista, carroRemovido);
                    }
                    i++;
                } while (lista->head != head);
            }
            adicionarVeiculo(lista, removerVeiculo(listaEspera));
        } else {
            carro = procurarNodo(listaEspera, placa);
            if (carro == NULL) {
                printf("Veiculo nao esta no estacionamento/fila de espera!\n");
                return;
            }
            if (carro == listaEspera->head) {
                carro = removerVeiculo(listaEspera);
                free(carro);
            } else {
                Nodo* head = listaEspera->head;
                Nodo* carroRemovido;
                do {
                    carroRemovido = removerVeiculo(listaEspera);
                    if (carroRemovido == carro) {
                        free(carroRemovido);
                    } else {
                        adicionarVeiculo(listaEspera, carroRemovido);
                    }
                } while (listaEspera->head != head);
            }
        }
        break;
    default:
        printf("Acao invalida!\n");
        return;
    }
    imprimirListas(lista, listaEspera);
    printf("Movimentacoes: %d\n", movimentacoes);
}

void imprimirListas(Lista* lista, Lista* listaEspera) {
    printf("\nLista de estacionamento:\n");
    imprimirLista(lista);
    printf("\nLista de espera:\n");
    imprimirLista(listaEspera);
}

void adicionarVeiculo(Lista* lista, Nodo* nodo) {
    adicionarNodo(lista, lista->tail, nodo);
}

Nodo* removerVeiculo(Lista* lista) {
    Nodo* nodo = lista->head;
    removerNodo(lista, nodo);
    return nodo;
}