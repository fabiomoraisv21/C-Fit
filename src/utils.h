#ifndef UTILS_H
#define UTILS_H

// funcoes de leitura e de tela usadas em todo o programa

void limparBuffer(void);
void limparTela(void);
void pausar(void);

void lerTexto(char *msg, char *destino, int tamanho);
int lerInteiro(char *msg);
int lerInteiroIntervalo(char *msg, int min, int max);
float lerFloat(char *msg);

#endif
