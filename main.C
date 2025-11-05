#include <stdio.h>
#include <stdlib.h>
#include "analex.h"
#include <locale.h>

int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");
    int contadorLinha = 0;

    FILE *fd;
    TOKEN token;

    if ((fd = fopen("arquivo.txt", "r")) == NULL) {
        printf("Erro ao abrir o arquivo");
    }

    printf("LINHA 1: ");

    while (1) {
        token = Analex(fd);

        switch(token.categoria) {
            case ID:
                printf("<ID,  %s> | %s", token.lexema);
                break;
            case SINAL:
                if (token.codigo == ATRIB) {
                    printf("<SINAL, => | ");
                    break;
                }

                if (token.codigo == ADICAO) {
                    printf("<SINAL, +> | ");
                    break;
                }
                
                if (token.codigo == SUB) {
                    printf("<SINAL: -> | ");
                    break;
                }

                if (token.codigo == MULT) {
                    printf("<SINAL: *> | ");
                    break;
                }

                if (token.codigo == DIV) {
                    printf("<SINAL: /> | ");
                    break;
                }

                if (token.codigo == IGUAL) {
                    printf("<SINAL: ==> | ");
                    break;
                }

                if (token.codigo == DIFERENTE) {
                    printf("<SINAL: !=> | ");
                    break;
                }

                if (token.codigo == E) {
                    printf("<SINAL: &&> | ");
                    break;
                }

                if (token.codigo == OU) {
                    printf("<SINAL: ||> | ");
                    break;
                }

                if (token.codigo == NEGACAO) {
                    printf("<SINAL: !> | ");
                    break;
                }

                if (token.codigo == MAIOR) {
                    printf("<SINAL: >> | ");
                    break;
                }

                if (token.codigo == MENOR) {
                    printf("<SINAL: <> | ");
                    break;
                }

                if (token.codigo == MAIOR_IGUAL) {
                    printf("<SINAL: >=> | ");
                    break;
                }

                if (token.codigo == MENOR_IGUAL) {
                    printf("<SINAL: <=> | ");
                    break;
                }

                if (token.codigo == ABRE_PAR) {
                    printf("<SINAL: (> | ");
                    break;
                }

                if (token.codigo == FECHA_PAR) {
                    printf("<SINAL: )> | ");
                    break;
                }

                if (token.codigo == ABRE_CHAVE) {
                    printf("<SINAL: {> | ");
                    break;
                }

                if (token.codigo == FECHA_CHAVE) {
                    printf("<SINAL: }> | ");
                    break;
                }

                if (token.codigo == ABRE_COL) {
                    printf("<SINAL: [> | ");
                    break;
                }

                if (token.codigo == FECHA_COL) {
                    printf("<SINAL: ]> | ");
                    break;
                }
                break;

            case STRING:
                printf("<STRING: %s> | ", token.lexema);
                break;
            case CT_I:
                printf("<CT_I: %d> | ", token.valInt);
                break;
            case CT_PF:
                printf("<CT_PF: %f> | ", token.valPF);
                break;
            case CHAR:
                printf("<CHAR: %c> | ", token.lexema[0]);
                break;
            case PR:
                printf("<PR: %s> | ", token.lexema);
                break;
            case FIM_DE_LINHA:
                printf("\nLINHA %d: ", token.valInt);
                break;
            case FIM_EXPR:
                printf("FIM_EXPR");
                break;
            case FIM_ARQ:
                printf("FIM_ARQ");
                break;
            default:
                printf("\n%s", token.lexema);
                break;
        }
        
        if (token.categoria == FIM_ARQ) {
            break;
        }
    }

    fclose(fd);
    return 0;
}