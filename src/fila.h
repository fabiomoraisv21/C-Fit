#ifndef FILA_H
#define FILA_H

// Fila (o primeiro que entra e o primeiro que sai)
// usada na espera dos aparelhos e nas inscricoes das aulas

typedef struct NoFila {
    int idAluno;
    char nome[50];
    struct NoFila *proximo;
} NoFila;

typedef struct {
    NoFila *inicio;
    NoFila *fim;
    int tamanho;
} Fila;

void inicializarFila(Fila *f);
int filaVazia(Fila *f);
int enfileirar(Fila *f, int idAluno, char *nome);
int desenfileirar(Fila *f, int *idAluno, char *nome);
int posicaoNaFila(Fila *f, int idAluno);
int removerDaFila(Fila *f, int idAluno);
void liberarFila(Fila *f);

#endif
