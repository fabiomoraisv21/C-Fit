#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ranking.h"
#include "alunos.h"
#include "utils.h"

// o no so aponta pro aluno, nao copia os dados dele
typedef struct NoRanking {
    Aluno *aluno;
    int pontos;
    struct NoRanking *proximo;
} NoRanking;

// insere mantendo a ordem do maior pro menor
// se empatar, quem tem o nome menor (ordem alfabetica) fica na frente
static NoRanking *inserirOrdenado(NoRanking *inicio, Aluno *aluno, int pontos) {
    NoRanking *novo = malloc(sizeof(NoRanking));
    if (novo == NULL) {
        printf("Erro ao alocar memoria\n");
        return inicio;
    }
    novo->aluno = aluno;
    novo->pontos = pontos;

    NoRanking *atual = inicio;
    NoRanking *anterior = NULL;

    while (atual != NULL) {
        if (atual->pontos < pontos)
            break;
        if (atual->pontos == pontos && strcmp(atual->aluno->nome, aluno->nome) > 0)
            break;
        anterior = atual;
        atual = atual->proximo;
    }

    novo->proximo = atual;
    if (anterior == NULL)
        return novo;
    anterior->proximo = novo;
    return inicio;
}

// tipo 1 = frequencia, tipo 2 = treinos
static void mostrarRanking(int tipo) {
    NoRanking *ranking = NULL;
    Aluno *a = primeiroAluno();

    if (a == NULL) {
        printf("\nNenhum aluno cadastrado.\n");
        return;
    }

    while (a != NULL) {
        if (tipo == 1)
            ranking = inserirOrdenado(ranking, a, a->frequencia);
        else
            ranking = inserirOrdenado(ranking, a, a->treinos);
        a = a->proximo;
    }

    if (tipo == 1)
        printf("\nRanking por frequencia:\n\n");
    else
        printf("\nRanking por treinos:\n\n");

    // quem empata fica na mesma posicao
    int pos = 0, cont = 0, ultimo = -1;
    NoRanking *aux = ranking;
    while (aux != NULL) {
        cont++;
        if (aux->pontos != ultimo) {
            pos = cont;
            ultimo = aux->pontos;
        }
        printf("%do - %-25s %d\n", pos, aux->aluno->nome, aux->pontos);
        aux = aux->proximo;
    }

    // libera so os nos do ranking, os alunos continuam no cadastro
    while (ranking != NULL) {
        NoRanking *prox = ranking->proximo;
        free(ranking);
        ranking = prox;
    }
}

void menuRanking(void) {
    int op;
    do {
        limparTela();
        printf("\n--- RANKING ---\n");
        printf("1. Por frequencia\n");
        printf("2. Por treinos\n");
        printf("0. Voltar\n");
        op = lerInteiro("Opcao: ");

        if (op == 1 || op == 2)
            mostrarRanking(op);
        else if (op != 0)
            printf("Opcao invalida!\n");

        if (op != 0)
            pausar();
    } while (op != 0);
}
