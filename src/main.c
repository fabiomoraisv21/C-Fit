#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "alunos.h"
#include "aparelhos.h"
#include "historico.h"
#include "aulas.h"
#include "ranking.h"

// coloca alguns alunos no sistema pra facilitar os testes
void carregarExemplo(void) {
    Aluno *ana = inserirAluno("Ana Souza", "11111111111", 24, "Mensal");
    Aluno *bruno = inserirAluno("Bruno Lima", "22222222222", 31, "Anual");
    Aluno *carla = inserirAluno("Carla Mendes", "33333333333", 19, "Trimestral");
    Aluno *diego = inserirAluno("Diego Rocha", "44444444444", 45, "Mensal");
    Aluno *elisa = inserirAluno("Elisa Martins", "55555555555", 28, "Anual");
    if (ana == NULL || bruno == NULL || carla == NULL || diego == NULL || elisa == NULL)
        return;

    ana->frequencia = 12;
    bruno->frequencia = 20;
    carla->frequencia = 7;
    diego->frequencia = 15;
    elisa->frequencia = 20;

    // Ana, Bruno e Carla estao na academia
    ana->presente = 1;
    bruno->presente = 1;
    carla->presente = 1;

    empilhar(&ana->historico, "Esteira", 1, 20, 0);
    empilhar(&ana->historico, "Agachamento", 4, 12, 30);
    empilhar(&ana->historico, "Leg Press", 4, 10, 120);
    ana->treinos = 3;

    empilhar(&bruno->historico, "Supino reto", 4, 10, 60);
    empilhar(&bruno->historico, "Puxador", 4, 12, 50);
    bruno->treinos = 2;

    empilhar(&elisa->historico, "Remada", 3, 12, 35);
    elisa->treinos = 1;

    inscreverAlunoDireto(1, carla->id, carla->nome);
    inscreverAlunoDireto(1, ana->id, ana->nome);
    inscreverAlunoDireto(3, elisa->id, elisa->nome);

    printf("\nDados de exemplo carregados (5 alunos).\n");
    printf("Ana, Bruno e Carla ja estao na academia.\n");
}

int main(void) {
    int op;
    int exemploCarregado = 0;

    inicializarAparelhos();
    inicializarAulas();

    do {
        limparTela();
        printf("\n===== C-FIT - ACADEMIA =====\n");
        printf("1. Alunos\n");
        printf("2. Aparelhos\n");
        printf("3. Historico de exercicios\n");
        printf("4. Aulas coletivas\n");
        printf("5. Ranking\n");
        printf("9. Carregar dados de exemplo\n");
        printf("0. Sair\n");
        printf("Alunos cadastrados: %d\n", quantidadeAlunos());
        op = lerInteiro("Opcao: ");

        switch (op) {
            case 1: menuAlunos(); break;
            case 2: menuAparelhos(); break;
            case 3: menuHistorico(); break;
            case 4: menuAulas(); break;
            case 5: menuRanking(); break;
            case 9:
                if (exemploCarregado) {
                    printf("\nOs dados de exemplo ja foram carregados.\n");
                } else {
                    carregarExemplo();
                    exemploCarregado = 1;
                }
                pausar();
                break;
            case 0:
                printf("\nSaindo... Bom treino!\n");
                break;
            default:
                printf("\nOpcao invalida!\n");
                pausar();
        }
    } while (op != 0);

    liberarAlunos();
    liberarAparelhos();
    liberarAulas();
    return 0;
}
