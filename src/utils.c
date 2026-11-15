#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
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

// tira os espacos do comeco e do fim do texto
static void tirarEspacos(char *texto) {
    int inicio = 0;
    while (texto[inicio] == ' ' || texto[inicio] == '\t')
        inicio++;

    int fim = strlen(texto);
    while (fim > inicio && (texto[fim - 1] == ' ' || texto[fim - 1] == '\t' || texto[fim - 1] == '\r'))
        fim--;

    memmove(texto, texto + inicio, fim - inicio);
    texto[fim - inicio] = '\0';
}

// le uma linha inteira, tira o \n e os espacos das pontas
// retorna 1 se deu certo e 0 se o texto era maior que o campo
// se a entrada acabar (Ctrl+D / Ctrl+Z) o programa fecha
static int lerLinha(char *destino, int tamanho) {
    if (fgets(destino, tamanho, stdin) == NULL) {
        printf("\nEntrada encerrada.\n");
        exit(0);
    }

    if (strchr(destino, '\n') == NULL) {
        limparBuffer();   // digitou mais do que cabe
        return 0;
    }
    destino[strcspn(destino, "\n")] = '\0';
    tirarEspacos(destino);
    return 1;
}

void lerTexto(char *msg, char *destino, int tamanho) {
    while (1) {
        printf("%s", msg);
        if (!lerLinha(destino, tamanho))
            printf("Texto muito grande! Maximo de %d caracteres.\n", tamanho - 2);
        else if (destino[0] == '\0')
            printf("Campo obrigatorio!\n");
        else
            return;
    }
}

// nome so pode ter letras e espacos (letras com acento tambem valem)
void lerNome(char *msg, char *destino, int tamanho) {
    while (1) {
        lerTexto(msg, destino, tamanho);

        int valido = 1;
        for (int i = 0; destino[i] != '\0'; i++) {
            unsigned char c = destino[i];
            if (!isalpha(c) && c != ' ' && c < 128)
                valido = 0;
        }
        if (valido)
            return;
        printf("Nome invalido! Use so letras.\n");
    }
}

// so aceita se o usuario digitar um numero inteiro
int lerInteiro(char *msg) {
    char buffer[32];
    char *fim;

    while (1) {
        printf("%s", msg);
        if (lerLinha(buffer, 32) && buffer[0] != '\0') {
            long valor = strtol(buffer, &fim, 10);
            if (*fim == '\0' && valor >= INT_MIN && valor <= INT_MAX)
                return (int)valor;
        }
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

// le um numero com virgula, aceita ponto ou virgula (12.5 ou 12,5)
float lerFloatIntervalo(char *msg, float min, float max) {
    char buffer[32];
    char *fim;

    while (1) {
        printf("%s", msg);
        if (lerLinha(buffer, 32) && buffer[0] != '\0') {
            char *virgula = strchr(buffer, ',');
            if (virgula != NULL)
                *virgula = '.';

            // so aceita digitos e um ponto (assim "inf", "1e5" etc nao passam)
            int valido = 1, pontos = 0;
            for (int i = 0; buffer[i] != '\0'; i++) {
                if (buffer[i] == '.')
                    pontos++;
                else if (!isdigit((unsigned char)buffer[i]))
                    valido = 0;
            }

            if (valido && pontos <= 1) {
                float valor = strtof(buffer, &fim);
                if (fim != buffer && *fim == '\0' && valor >= min && valor <= max)
                    return valor;
            }
        }
        printf("Digite um numero entre %.0f e %.0f.\n", min, max);
    }
}
