#include <stdio.h>
#include <string.h>
#include "aulas.h"
#include "alunos.h"
#include "utils.h"

static Aula aulas[TOTAL_AULAS];

static Aula *escolherAula(void) {
    int n = lerInteiroIntervalo("Numero da aula: ", 1, TOTAL_AULAS);
    return &aulas[n - 1];
}

void inicializarAulas(void) {
    char *nomes[TOTAL_AULAS] = {"Spinning", "Funcional", "Pilates"};
    char *horarios[TOTAL_AULAS] = {"07:00", "18:00", "19:30"};
    int vagas[TOTAL_AULAS] = {5, 6, 4};

    for (int i = 0; i < TOTAL_AULAS; i++) {
        aulas[i].id = i + 1;
        strcpy(aulas[i].nome, nomes[i]);
        strcpy(aulas[i].horario, horarios[i]);
        aulas[i].vagas = vagas[i];
        inicializarFila(&aulas[i].inscritos);
    }
}

void liberarAulas(void) {
    for (int i = 0; i < TOTAL_AULAS; i++)
        liberarFila(&aulas[i].inscritos);
}

void menuAulas(void) {
    int op;
    do {
        limparTela();
        printf("\n--- AULAS COLETIVAS ---\n");
        printf("1. Ver aulas\n");
        printf("2. Inscrever aluno\n");
        printf("3. Ver inscritos\n");
        printf("4. Realizar aula\n");
        printf("0. Voltar\n");
        op = lerInteiro("Opcao: ");

        switch (op) {
            case 1: listarAulas(); break;
            case 2: inscreverEmAula(); break;
            case 3: verInscritos(); break;
            case 4: realizarAula(); break;
            case 0: break;
            default: printf("Opcao invalida!\n");
        }
        if (op != 0)
            pausar();
    } while (op != 0);
}

void listarAulas(void) {
    printf("\n");
    for (int i = 0; i < TOTAL_AULAS; i++) {
        Aula *au = &aulas[i];
        int naTurma = au->inscritos.tamanho;
        if (naTurma > au->vagas)
            naTurma = au->vagas;
        int esperando = au->inscritos.tamanho - naTurma;

        printf("%d. %-10s %s - vagas: %d/%d - espera: %d\n",
               au->id, au->nome, au->horario, naTurma, au->vagas, esperando);
    }
}

// usada so nos dados de exemplo
void inscreverAlunoDireto(int idAula, int idAluno, char *nome) {
    Aula *au = &aulas[idAula - 1];
    if (posicaoNaFila(&au->inscritos, idAluno) == 0)
        enfileirar(&au->inscritos, idAluno, nome);
}

void inscreverEmAula(void) {
    Aluno *a = selecionarAluno();
    if (a == NULL)
        return;

    listarAulas();
    Aula *au = escolherAula();

    int pos = posicaoNaFila(&au->inscritos, a->id);
    if (pos > 0) {
        printf("%s ja esta inscrito(a) nessa aula (posicao %d).\n", a->nome, pos);
        return;
    }

    if (!enfileirar(&au->inscritos, a->id, a->nome))
        return;

    pos = au->inscritos.tamanho;
    if (pos <= au->vagas)
        printf("%s inscrito(a) em %s! Vaga garantida.\n", a->nome, au->nome);
    else
        printf("Turma lotada. %s esta na lista de espera (posicao %d).\n", a->nome, pos - au->vagas);
}

void verInscritos(void) {
    listarAulas();
    Aula *au = escolherAula();

    printf("\n%s - %s\n", au->nome, au->horario);
    if (filaVazia(&au->inscritos)) {
        printf("Nenhum inscrito.\n");
        return;
    }

    NoFila *aux = au->inscritos.inicio;
    int pos = 1;
    printf("Turma:\n");
    while (aux != NULL) {
        if (pos == au->vagas + 1)
            printf("Lista de espera:\n");
        printf("  %d. %s (ID %d)\n", pos, aux->nome, aux->idAluno);
        aux = aux->proximo;
        pos++;
    }
}

// tira os primeiros da fila (ate encher as vagas), cada um ganha +1 treino
// quem estava esperando vira o inicio da fila pra proxima turma
void realizarAula(void) {
    listarAulas();
    Aula *au = escolherAula();

    if (filaVazia(&au->inscritos)) {
        printf("Ninguem inscrito nessa aula.\n");
        return;
    }

    printf("\nAula de %s comecando! Participantes:\n", au->nome);

    int participantes = 0;
    int id;
    char nome[50];
    while (participantes < au->vagas && desenfileirar(&au->inscritos, &id, nome)) {
        Aluno *a = buscarAlunoPorId(id);
        if (a != NULL)
            a->treinos++;
        participantes++;
        printf("  %d. %s\n", participantes, nome);
    }

    printf("%d aluno(s) fizeram a aula.\n", participantes);
    if (!filaVazia(&au->inscritos))
        printf("Quem estava na espera ja esta na proxima turma.\n");
}

// tira o aluno de todas as aulas (quando ele e removido do cadastro)
void sairDasAulas(int idAluno) {
    for (int i = 0; i < TOTAL_AULAS; i++)
        removerDaFila(&aulas[i].inscritos, idAluno);
}
