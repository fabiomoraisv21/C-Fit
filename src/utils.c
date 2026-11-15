#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

void limparBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void limparTela(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pausar(void) {
    printf("\nAperte Enter para continuar...");
    limparBuffer();
}

// le uma linha inteira e tira o \n do final
// retorna 0 se a entrada acabou (Ctrl+D / Ctrl+Z)
static int lerLinha(char *destino, int tamanho) {
    if (fgets(destino, tamanho, stdin) == NULL)
        return 0;

    if (strchr(destino, '\n') == NULL)
        limparBuffer();   // digitou mais do que cabe
    destino[strcspn(destino, "\n")] = '\0';
    return 1;
}

void lerTexto(char *msg, char *destino, int tamanho) {
    do {
        printf("%s", msg);
        if (!lerLinha(destino, tamanho))
            exit(0);
        if (destino[0] == '\0')
            printf("Campo obrigatorio!\n");
    } while (destino[0] == '\0');
}

// so aceita se o usuario digitar um numero inteiro
int lerInteiro(char *msg) {
    char buffer[32];
    char *fim;

    while (1) {
        printf("%s", msg);
        if (!lerLinha(buffer, 32))
            exit(0);

        long valor = strtol(buffer, &fim, 10);
        if (fim != buffer && *fim == '\0')
            return (int)valor;

        printf("Digite um numero inteiro.\n");
    }
}

int lerInteiroIntervalo(char *msg, int min, int max) {
    int valor = lerInteiro(msg);
    while (valor < min || valor > max) {
        printf("Digite um valor entre %d e %d.\n", min, max);
        valor = lerInteiro(msg);
    }
    return valor;
}

// aceita ponto ou virgula (12.5 ou 12,5)
float lerFloat(char *msg) {
    char buffer[32];
    char *fim;

    while (1) {
        printf("%s", msg);
        if (!lerLinha(buffer, 32))
            exit(0);

        char *virgula = strchr(buffer, ',');
        if (virgula != NULL)
            *virgula = '.';

        float valor = strtof(buffer, &fim);
        if (fim != buffer && *fim == '\0' && valor >= 0)
            return valor;

        printf("Valor invalido.\n");
    }
}
