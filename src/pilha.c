#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilha.h"

void inicializarPilha(Pilha *p) {
    p->topo = NULL;
    p->tamanho = 0;
}

int pilhaVazia(Pilha *p) {
    return p->topo == NULL;
}

// coloca no topo
int empilhar(Pilha *p, char *nome, int series, int repeticoes, float carga) {
    Exercicio *novo = malloc(sizeof(Exercicio));
    if (novo == NULL) {
        printf("Erro ao alocar memoria\n");
        return 0;
    }
    strcpy(novo->nome, nome);
    novo->series = series;
    novo->repeticoes = repeticoes;
    novo->carga = carga;

    novo->proximo = p->topo;
    p->topo = novo;
    p->tamanho++;
    return 1;
}

// tira do topo; se removido nao for NULL, copia os dados pra ele
int desempilhar(Pilha *p, Exercicio *removido) {
    if (pilhaVazia(p))
        return 0;

    Exercicio *aux = p->topo;
    if (removido != NULL)
        *removido = *aux;

    p->topo = aux->proximo;
    free(aux);
    p->tamanho--;
    return 1;
}

// mostra do topo (mais recente) ate a base
void imprimirPilha(Pilha *p) {
    Exercicio *aux = p->topo;
    int i = 1;
    while (aux != NULL) {
        printf("%d) %s - %d x %d - %.1f kg", i, aux->nome, aux->series, aux->repeticoes, aux->carga);
        if (i == 1)
            printf("  (mais recente)");
        printf("\n");
        aux = aux->proximo;
        i++;
    }
}

void liberarPilha(Pilha *p) {
    while (desempilhar(p, NULL));
}
