#ifndef ALUNOS_H
#define ALUNOS_H

#include "pilha.h"

// cadastro de alunos feito com lista encadeada
// cada aluno tem a sua propria pilha de historico

typedef struct Aluno {
    int id;
    char nome[50];
    char cpf[15];
    int idade;
    char plano[20];
    int frequencia;   // quantas vezes entrou na academia
    int treinos;      // exercicios registrados + aulas feitas
    int presente;     // 1 se esta na academia agora
    Pilha historico;
    struct Aluno *proximo;
} Aluno;

void menuAlunos(void);
void cadastrarAluno(void);
void listarAlunos(void);
void buscarAluno(void);
void editarAluno(void);
void removerAluno(void);
void registrarEntradaSaida(void);

// usadas pelos outros arquivos
Aluno *buscarAlunoPorId(int id);
Aluno *selecionarAluno(void);
Aluno *primeiroAluno(void);
int quantidadeAlunos(void);
Aluno *inserirAluno(char *nome, char *cpf, int idade, char *plano);
void liberarAlunos(void);

#endif
