#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "alunos.h"
#include "aparelhos.h"
#include "aulas.h"
#include "utils.h"

static Aluno *lista = NULL;
static int proximoId = 1;
static int totalAlunos = 0;

static void mostrarAluno(Aluno *a) {
    printf("\nID: %d\n", a->id);
    printf("Nome: %s\n", a->nome);
    printf("CPF: %s\n", a->cpf);
    printf("Idade: %d\n", a->idade);
    printf("Plano: %s\n", a->plano);
    printf("Frequencia: %d\n", a->frequencia);
    printf("Treinos: %d\n", a->treinos);
    if (a->presente)
        printf("Status: na academia\n");
    else
        printf("Status: fora da academia\n");
}

static Aluno *buscarPorCpf(char *cpf) {
    Aluno *aux = lista;
    while (aux != NULL) {
        if (strcmp(aux->cpf, cpf) == 0)
            return aux;
        aux = aux->proximo;
    }
    return NULL;
}

// ve se 'busca' aparece dentro do nome, sem ligar pra maiuscula/minuscula
static int contemTexto(char *nome, char *busca) {
    char a[50], b[50];
    int i;

    for (i = 0; nome[i] != '\0'; i++)
        a[i] = tolower(nome[i]);
    a[i] = '\0';

    for (i = 0; busca[i] != '\0'; i++)
        b[i] = tolower(busca[i]);
    b[i] = '\0';

    return strstr(a, b) != NULL;
}

void menuAlunos(void) {
    int op;
    do {
        limparTela();
        printf("\n--- ALUNOS ---\n");
        printf("1. Cadastrar aluno\n");
        printf("2. Listar alunos\n");
        printf("3. Buscar aluno\n");
        printf("4. Editar aluno\n");
        printf("5. Remover aluno\n");
        printf("6. Registrar entrada/saida\n");
        printf("0. Voltar\n");
        op = lerInteiro("Opcao: ");

        switch (op) {
            case 1: cadastrarAluno(); break;
            case 2: listarAlunos(); break;
            case 3: buscarAluno(); break;
            case 4: editarAluno(); break;
            case 5: removerAluno(); break;
            case 6: registrarEntradaSaida(); break;
            case 0: break;
            default: printf("Opcao invalida!\n");
        }
        if (op != 0)
            pausar();
    } while (op != 0);
}

// insere no fim da lista
Aluno *inserirAluno(char *nome, char *cpf, int idade, char *plano) {
    Aluno *novo = malloc(sizeof(Aluno));
    if (novo == NULL) {
        printf("Erro ao alocar memoria\n");
        return NULL;
    }

    novo->id = proximoId;
    proximoId++;
    strcpy(novo->nome, nome);
    strcpy(novo->cpf, cpf);
    strcpy(novo->plano, plano);
    novo->idade = idade;
    novo->frequencia = 0;
    novo->treinos = 0;
    novo->presente = 0;
    inicializarPilha(&novo->historico);
    novo->proximo = NULL;

    if (lista == NULL) {
        lista = novo;
    } else {
        Aluno *aux = lista;
        while (aux->proximo != NULL)
            aux = aux->proximo;
        aux->proximo = novo;
    }
    totalAlunos++;
    return novo;
}

void cadastrarAluno(void) {
    char nome[50], cpf[15], plano[20];
    int idade;

    printf("\n--- Novo aluno ---\n");
    lerTexto("Nome: ", nome, 50);
    lerTexto("CPF (so numeros): ", cpf, 15);

    if (buscarPorCpf(cpf) != NULL) {
        printf("Ja tem um aluno com esse CPF.\n");
        return;
    }

    idade = lerInteiroIntervalo("Idade: ", 10, 120);
    lerTexto("Plano (Mensal, Trimestral, Anual): ", plano, 20);

    Aluno *novo = inserirAluno(nome, cpf, idade, plano);
    if (novo != NULL)
        printf("\nAluno cadastrado! ID: %d\n", novo->id);
}

void listarAlunos(void) {
    if (lista == NULL) {
        printf("\nNenhum aluno cadastrado.\n");
        return;
    }

    printf("\nAlunos cadastrados: %d\n\n", totalAlunos);
    printf("%-4s %-25s %-12s %-6s %-8s %s\n", "ID", "Nome", "Plano", "Freq", "Treinos", "Status");

    Aluno *aux = lista;
    while (aux != NULL) {
        printf("%-4d %-25s %-12s %-6d %-8d %s\n", aux->id, aux->nome, aux->plano,
               aux->frequencia, aux->treinos, aux->presente ? "Na academia" : "Fora");
        aux = aux->proximo;
    }
}

void buscarAluno(void) {
    if (lista == NULL) {
        printf("\nNenhum aluno cadastrado.\n");
        return;
    }

    printf("\n1. Buscar por ID\n2. Buscar por nome\n");
    int tipo = lerInteiroIntervalo("Opcao: ", 1, 2);

    if (tipo == 1) {
        int id = lerInteiro("ID: ");
        Aluno *a = buscarAlunoPorId(id);
        if (a == NULL)
            printf("Aluno nao encontrado.\n");
        else
            mostrarAluno(a);
    } else {
        char busca[50];
        int achou = 0;
        lerTexto("Nome (ou parte): ", busca, 50);

        Aluno *aux = lista;
        while (aux != NULL) {
            if (contemTexto(aux->nome, busca)) {
                mostrarAluno(aux);
                achou = 1;
            }
            aux = aux->proximo;
        }
        if (!achou)
            printf("Nenhum aluno encontrado.\n");
    }
}

void editarAluno(void) {
    Aluno *a = selecionarAluno();
    if (a == NULL)
        return;

    int op;
    do {
        mostrarAluno(a);
        printf("\n1. Editar nome\n2. Editar idade\n3. Editar plano\n0. Terminar\n");
        op = lerInteiro("Opcao: ");

        switch (op) {
            case 1: lerTexto("Novo nome: ", a->nome, 50); break;
            case 2: a->idade = lerInteiroIntervalo("Nova idade: ", 10, 120); break;
            case 3: lerTexto("Novo plano: ", a->plano, 20); break;
            case 0: break;
            default: printf("Opcao invalida!\n");
        }
    } while (op != 0);
}

void removerAluno(void) {
    if (lista == NULL) {
        printf("\nNenhum aluno cadastrado.\n");
        return;
    }

    int id = lerInteiro("ID do aluno: ");
    Aluno *atual = lista;
    Aluno *anterior = NULL;

    while (atual != NULL && atual->id != id) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Aluno nao encontrado.\n");
        return;
    }

    // antes de apagar, tira o aluno dos aparelhos e das aulas
    sairDosAparelhos(atual->id);
    sairDasAulas(atual->id);

    if (anterior == NULL)
        lista = atual->proximo;
    else
        anterior->proximo = atual->proximo;

    printf("Aluno %s removido.\n", atual->nome);
    liberarPilha(&atual->historico);
    free(atual);
    totalAlunos--;
}

// se o aluno estava fora, registra entrada (+1 na frequencia)
// se estava dentro, registra saida e libera o aparelho que ele estava usando
void registrarEntradaSaida(void) {
    Aluno *a = selecionarAluno();
    if (a == NULL)
        return;

    if (a->presente) {
        a->presente = 0;
        printf("Saida registrada: %s saiu da academia.\n", a->nome);
        sairDosAparelhos(a->id);
    } else {
        a->presente = 1;
        a->frequencia++;
        printf("Entrada registrada: bem-vindo(a), %s! Frequencia: %d\n", a->nome, a->frequencia);
    }
}

Aluno *buscarAlunoPorId(int id) {
    Aluno *aux = lista;
    while (aux != NULL) {
        if (aux->id == id)
            return aux;
        aux = aux->proximo;
    }
    return NULL;
}

// pede o ID e devolve o aluno (ou NULL se nao achar)
Aluno *selecionarAluno(void) {
    if (lista == NULL) {
        printf("\nNenhum aluno cadastrado.\n");
        return NULL;
    }
    int id = lerInteiro("ID do aluno: ");
    Aluno *a = buscarAlunoPorId(id);
    if (a == NULL)
        printf("Aluno nao encontrado.\n");
    return a;
}

Aluno *primeiroAluno(void) {
    return lista;
}

int quantidadeAlunos(void) {
    return totalAlunos;
}

void liberarAlunos(void) {
    Aluno *aux = lista;
    while (aux != NULL) {
        Aluno *prox = aux->proximo;
        liberarPilha(&aux->historico);
        free(aux);
        aux = prox;
    }
    lista = NULL;
    totalAlunos = 0;
}
