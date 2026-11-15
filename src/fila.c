#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila.h"

void inicializarFila(Fila *f) {
    f->inicio = NULL;
    f->fim = NULL;
    f->tamanho = 0;
}

int filaVazia(Fila *f) {
    return f->inicio == NULL;
}

// coloca no fim da fila
int enfileirar(Fila *f, int idAluno, char *nome) {
    NoFila *novo = malloc(sizeof(NoFila));
    if (novo == NULL) {
        printf("Erro ao alocar memoria\n");
        return 0;
    }
    novo->idAluno = idAluno;
    strcpy(novo->nome, nome);
    novo->proximo = NULL;

    if (f->fim == NULL)
        f->inicio = novo;
    else
        f->fim->proximo = novo;
    f->fim = novo;
    f->tamanho++;
    return 1;
}

// tira do inicio da fila e devolve o id e o nome de quem saiu
int desenfileirar(Fila *f, int *idAluno, char *nome) {
    if (filaVazia(f))
        return 0;

    NoFila *aux = f->inicio;
    if (idAluno != NULL)
        *idAluno = aux->idAluno;
    if (nome != NULL)
        strcpy(nome, aux->nome);

    f->inicio = aux->proximo;
    if (f->inicio == NULL)
        f->fim = NULL;

    free(aux);
    f->tamanho--;
    return 1;
}

// retorna a posicao do aluno na fila (1, 2, 3...) ou 0 se ele nao estiver nela
int posicaoNaFila(Fila *f, int idAluno) {
    NoFila *aux = f->inicio;
    int pos = 1;
    while (aux != NULL) {
        if (aux->idAluno == idAluno)
            return pos;
        aux = aux->proximo;
        pos++;
    }
    return 0;
}

// tira um aluno de qualquer lugar da fila
// (usado quando ele sai da academia ou e removido do cadastro)
int removerDaFila(Fila *f, int idAluno) {
    NoFila *atual = f->inicio;
    NoFila *anterior = NULL;

    while (atual != NULL && atual->idAluno != idAluno) {
        anterior = atual;
        atual = atual->proximo;
    }
    if (atual == NULL)
        return 0;

    if (anterior == NULL)
        f->inicio = atual->proximo;
    else
        anterior->proximo = atual->proximo;

    if (atual == f->fim)
        f->fim = anterior;

    free(atual);
    f->tamanho--;
    return 1;
}

void liberarFila(Fila *f) {
    while (desenfileirar(f, NULL, NULL));
}
