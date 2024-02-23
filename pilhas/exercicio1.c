#include "../fundamentos/lista-dupla-string.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define BUFFER_SIZE 4096

bool validar(char*, char*);
void push(Lista*, char*);
void pop(Lista*);

char* getLn();

int main() {
    char* entrada = (char*) malloc(sizeof(char) * 100);
    char* erro = (char*) malloc(sizeof(char) * 500);
    printf("Digite uma expressão para ser validada: ");
    entrada = getLn();

    if (!validar(entrada, erro)) {
        printf("Expressão inválida: %s", erro);
    } else {
        printf("Expressão válida");
    }

    return 0;
}

char* getLn() {
    char *buffer = malloc(BUFFER_SIZE * sizeof(char));
    int length = 0;

    // Lê a linha
    fgets(buffer, BUFFER_SIZE, stdin);
    length = strlen(buffer);
    // Remove a quebra de linha e substitui por \0
    buffer[length - 1] = '\0';
    return buffer;
}

bool validar(char* entrada, char* erro) {
    int tamanho = strlen(entrada);
    Lista* pilha = inicializarLista();

    for (int i = 0; i < tamanho; i++) {
        switch (entrada[i]) {
            case '(':
            case '[':
            case '{':
                push(pilha, &entrada[i]);
                break;
            case ')':
            case ']':
            case '}':
                if (pilha->size == 0) {
                    liberarLista(pilha);
                    strcpy(erro, "underflow");
                    return false;
                }

                if (((entrada[i] == ')') && (pilha->tail->info[0] == '(')) ||
                    ((entrada[i] == ']') && (pilha->tail->info[0] == '[')) ||
                    ((entrada[i] == '}') && (pilha->tail->info[0] == '{'))) {
                        pop(pilha);
                    } else {

                    liberarLista(pilha);
                    strcpy(erro, "Erro de sintaxe.");
                    return false;
                    }
                break;
        }
    }
    if (pilha->size > 0) {
        liberarLista(pilha);
        strcpy(erro, "Há escopos abertos.");
        return false;
    } else {
        liberarLista(pilha);
        return true;
    }
}

void push(Lista* pilha, char* caractere) {
    adicionarNodo(pilha, pilha->tail, criarNodo(caractere));
}

void pop(Lista* pilha) {
    removerNodo(pilha, pilha->tail);
}