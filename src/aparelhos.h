#ifndef APARELHOS_H
#define APARELHOS_H

#include "fila.h"

// cada aparelho tem a sua fila de espera

#define TOTAL_APARELHOS 5

typedef struct {
    int id;
    char nome[30];
    int idAlunoUsando;   // 0 = livre
    Fila espera;
} Aparelho;

void inicializarAparelhos(void);
void liberarAparelhos(void);

void menuAparelhos(void);
void listarAparelhos(void);
void usarAparelho(void);
void liberarAparelho(void);
void verFilaAparelho(void);

void sairDosAparelhos(int idAluno);

#endif
