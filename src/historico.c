#include <stdio.h>
#include "historico.h"
#include "alunos.h"
#include "pilha.h"
#include "utils.h"

void menuHistorico(void) {
    int op;
    do {
        limparTela();
        printf("\n--- HISTORICO DE EXERCICIOS ---\n");
        printf("1. Registrar exercicio\n");
        printf("2. Ver ultimo exercicio\n");
        printf("3. Desfazer ultimo registro\n");
        printf("4. Ver historico completo\n");
        printf("0. Voltar\n");
        op = lerInteiro("Opcao: ");

        switch (op) {
            case 1: registrarExercicio(); break;
            case 2: verUltimoExercicio(); break;
            case 3: desfazerUltimoExercicio(); break;
            case 4: verHistoricoCompleto(); break;
            case 0: break;
            default: printf("Opcao invalida!\n");
        }
        if (op != 0)
            pausar();
    } while (op != 0);
}

void registrarExercicio(void) {
    Aluno *a = selecionarAluno();
    if (a == NULL)
        return;

    char nome[50];
    printf("\nNovo exercicio para %s\n", a->nome);
    lerTexto("Exercicio: ", nome, 50);
    int series = lerInteiroIntervalo("Series: ", 1, 20);
    int reps = lerInteiroIntervalo("Repeticoes: ", 1, 200);
    float carga = lerFloatIntervalo("Carga em kg (0 se nao tiver): ", 0, 500);

    if (empilhar(&a->historico, nome, series, reps, carga)) {
        a->treinos++;
        printf("Exercicio registrado!\n");
    }
}

void verUltimoExercicio(void) {
    Aluno *a = selecionarAluno();
    if (a == NULL)
        return;

    if (pilhaVazia(&a->historico)) {
        printf("%s ainda nao tem exercicios registrados.\n", a->nome);
        return;
    }

    Exercicio *e = a->historico.topo;
    printf("\nUltimo exercicio de %s: %s - %d x %d - %.1f kg\n",
           a->nome, e->nome, e->series, e->repeticoes, e->carga);
}

// tira o exercicio do topo (caso tenha sido registrado errado)
void desfazerUltimoExercicio(void) {
    Aluno *a = selecionarAluno();
    if (a == NULL)
        return;

    Exercicio removido;
    if (!desempilhar(&a->historico, &removido)) {
        printf("%s nao tem exercicios pra remover.\n", a->nome);
        return;
    }

    if (a->treinos > 0)
        a->treinos--;
    printf("Removido: %s - %d x %d - %.1f kg\n",
           removido.nome, removido.series, removido.repeticoes, removido.carga);
}

void verHistoricoCompleto(void) {
    Aluno *a = selecionarAluno();
    if (a == NULL)
        return;

    if (pilhaVazia(&a->historico)) {
        printf("%s ainda nao tem exercicios registrados.\n", a->nome);
        return;
    }

    printf("\nHistorico de %s (%d exercicios):\n", a->nome, a->historico.tamanho);
    imprimirPilha(&a->historico);
}
