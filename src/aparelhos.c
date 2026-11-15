#include <stdio.h>
#include <string.h>
#include "aparelhos.h"
#include "alunos.h"
#include "utils.h"

static Aparelho aparelhos[TOTAL_APARELHOS];

static Aparelho *escolherAparelho(void) {
    int n = lerInteiroIntervalo("Numero do aparelho: ", 1, TOTAL_APARELHOS);
    return &aparelhos[n - 1];
}

static char *nomeDoAluno(int id) {
    Aluno *a = buscarAlunoPorId(id);
    if (a == NULL)
        return "?";
    return a->nome;
}

// passa o aparelho pro primeiro da fila, ou deixa livre se nao tiver ninguem
static void chamarProximo(Aparelho *ap) {
    int id;
    char nome[50];

    if (desenfileirar(&ap->espera, &id, nome)) {
        ap->idAlunoUsando = id;
        printf("Proximo da fila: %s agora esta usando o aparelho %s.\n", nome, ap->nome);
    } else {
        ap->idAlunoUsando = 0;
        printf("Ninguem na fila, o aparelho %s ficou livre.\n", ap->nome);
    }
}

void inicializarAparelhos(void) {
    char *nomes[TOTAL_APARELHOS] = {"Esteira", "Bicicleta", "Supino", "Leg Press", "Puxador"};

    for (int i = 0; i < TOTAL_APARELHOS; i++) {
        aparelhos[i].id = i + 1;
        strcpy(aparelhos[i].nome, nomes[i]);
        aparelhos[i].idAlunoUsando = 0;
        inicializarFila(&aparelhos[i].espera);
    }
}

void liberarAparelhos(void) {
    for (int i = 0; i < TOTAL_APARELHOS; i++)
        liberarFila(&aparelhos[i].espera);
}

void menuAparelhos(void) {
    int op;
    do {
        limparTela();
        printf("\n--- APARELHOS ---\n");
        printf("1. Ver aparelhos\n");
        printf("2. Usar aparelho / entrar na fila\n");
        printf("3. Liberar aparelho\n");
        printf("4. Ver fila de um aparelho\n");
        printf("0. Voltar\n");
        op = lerInteiro("Opcao: ");

        switch (op) {
            case 1: listarAparelhos(); break;
            case 2: usarAparelho(); break;
            case 3: liberarAparelho(); break;
            case 4: verFilaAparelho(); break;
            case 0: break;
            default: printf("Opcao invalida!\n");
        }
        if (op != 0)
            pausar();
    } while (op != 0);
}

void listarAparelhos(void) {
    printf("\n");
    for (int i = 0; i < TOTAL_APARELHOS; i++) {
        Aparelho *ap = &aparelhos[i];
        printf("%d. %-12s ", ap->id, ap->nome);
        if (ap->idAlunoUsando == 0)
            printf("LIVRE");
        else
            printf("OCUPADO (%s)", nomeDoAluno(ap->idAlunoUsando));
        printf(" - fila: %d\n", ap->espera.tamanho);
    }
}

// se estiver livre o aluno ja usa, se estiver ocupado ele vai pro fim da fila
void usarAparelho(void) {
    Aluno *a = selecionarAluno();
    if (a == NULL)
        return;

    if (!a->presente) {
        printf("%s nao registrou entrada na academia.\n", a->nome);
        return;
    }

    // o aluno so pode usar ou esperar um aparelho de cada vez
    for (int i = 0; i < TOTAL_APARELHOS; i++) {
        if (aparelhos[i].idAlunoUsando == a->id) {
            printf("%s ja esta usando o aparelho %s.\n", a->nome, aparelhos[i].nome);
            return;
        }
        int pos = posicaoNaFila(&aparelhos[i].espera, a->id);
        if (pos > 0) {
            printf("%s ja esta na fila do aparelho %s (posicao %d).\n", a->nome, aparelhos[i].nome, pos);
            return;
        }
    }

    listarAparelhos();
    Aparelho *ap = escolherAparelho();

    if (ap->idAlunoUsando == 0) {
        ap->idAlunoUsando = a->id;
        printf("%s esta usando o aparelho %s.\n", a->nome, ap->nome);
    } else if (enfileirar(&ap->espera, a->id, a->nome)) {
        printf("Aparelho ocupado. %s entrou na fila na posicao %d.\n", a->nome, ap->espera.tamanho);
    }
}

void liberarAparelho(void) {
    listarAparelhos();
    Aparelho *ap = escolherAparelho();

    if (ap->idAlunoUsando == 0) {
        printf("Esse aparelho ja esta livre.\n");
        return;
    }

    printf("%s terminou de usar o aparelho %s.\n", nomeDoAluno(ap->idAlunoUsando), ap->nome);
    chamarProximo(ap);
}

void verFilaAparelho(void) {
    listarAparelhos();
    Aparelho *ap = escolherAparelho();

    printf("\nFila do aparelho %s:\n", ap->nome);
    if (ap->idAlunoUsando != 0)
        printf("Usando agora: %s\n", nomeDoAluno(ap->idAlunoUsando));

    if (filaVazia(&ap->espera)) {
        printf("Fila vazia.\n");
        return;
    }

    NoFila *aux = ap->espera.inicio;
    int pos = 1;
    while (aux != NULL) {
        printf("%d. %s (ID %d)\n", pos, aux->nome, aux->idAluno);
        aux = aux->proximo;
        pos++;
    }
}

// chamada quando o aluno sai da academia ou e removido:
// tira ele das filas e, se estava usando algum aparelho, passa pro proximo
void sairDosAparelhos(int idAluno) {
    for (int i = 0; i < TOTAL_APARELHOS; i++) {
        removerDaFila(&aparelhos[i].espera, idAluno);

        if (aparelhos[i].idAlunoUsando == idAluno) {
            printf("O aparelho %s foi liberado.\n", aparelhos[i].nome);
            chamarProximo(&aparelhos[i]);
        }
    }
}
