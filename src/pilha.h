#ifndef PILHA_H
#define PILHA_H

// Pilha (o ultimo que entra e o primeiro que sai)
// usada no historico de exercicios: o mais recente fica no topo

typedef struct Exercicio {
    char nome[50];
    int series;
    int repeticoes;
    float carga;
    struct Exercicio *proximo;
} Exercicio;

typedef struct {
    Exercicio *topo;
    int tamanho;
} Pilha;

void inicializarPilha(Pilha *p);
int pilhaVazia(Pilha *p);
int empilhar(Pilha *p, char *nome, int series, int repeticoes, float carga);
int desempilhar(Pilha *p, Exercicio *removido);
void imprimirPilha(Pilha *p);
void liberarPilha(Pilha *p);

#endif
