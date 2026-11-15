#ifndef AULAS_H
#define AULAS_H

#include "fila.h"

// aulas coletivas: os primeiros 'vagas' da fila fazem a aula,
// o resto fica esperando a proxima turma

#define TOTAL_AULAS 3

typedef struct {
    int id;
    char nome[30];
    char horario[10];
    int vagas;
    Fila inscritos;
} Aula;

void inicializarAulas(void);
void liberarAulas(void);

void menuAulas(void);
void listarAulas(void);
void inscreverEmAula(void);
void verInscritos(void);
void realizarAula(void);

void inscreverAlunoDireto(int idAula, int idAluno, char *nome);
void sairDasAulas(int idAluno);

#endif
