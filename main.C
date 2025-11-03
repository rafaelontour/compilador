#include "analex.h"
#include <locale.h>
#include <cstdio>

int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");

    FILE *fd;
    TOKEN token;

    if ((fd = fopen("arquivo.txt", "r")) == NULL) {
        printf("Erro ao abrir o arquivo");
    }

    while (true) {
        token = Analex(fd);

        switch(token.categoria) {
            case ID:
                printf("ID: %s\n", token.lexema);
                break;
            case SINAL:
                if (token.codigo == ATRIB) {
                    printf("ATRIB: =\n");
                    break;
                }

                if (token.codigo == ADICAO) {
                    printf("OPERADOR: +\n");
                    break;
                }
                
                if (token.codigo == SUB) {
                    printf("OPERADOR: -\n");
                    break;
                }

                if (token.codigo == MULT) {
                    printf("OPERADOR: *\n");
                    break;
                }

                if (token.codigo == DIV) {
                    printf("OPERADOR: /\n");
                    break;
                }

                if (token.codigo == IGUAL) {
                    printf("OPERADOR: ==\n");
                    break;
                }

                if (token.codigo == DIFERENTE) {
                    printf("OPERADOR: !=\n");
                    break;
                }

                if (token.codigo == E) {
                    printf("OPERADOR: &&\n");
                    break;
                }

                if (token.codigo == OU) {
                    printf("OPERADOR: ||\n");
                    break;
                }

                if (token.codigo == NEGACAO) {
                    printf("OPERADOR: !\n");
                    break;
                }

                if (token.codigo == MAIOR) {
                    printf("OPERADOR: >\n");
                    break;
                }

                if (token.codigo == MENOR) {
                    printf("OPERADOR: <\n");
                    break;
                }

                if (token.codigo == MAIOR_IGUAL) {
                    printf("OPERADOR: >=\n");
                    break;
                }

                if (token.codigo == MENOR_IGUAL) {
                    printf("OPERADOR: <=\n");
                    break;
                }

                if (token.codigo == ABRE_PAR) {
                    printf("ABRE_PAR\n");
                    break;
                }

                if (token.codigo == FECHA_PAR) {
                    printf("FECHA_PAR\n");
                    break;
                }

                if (token.codigo == ABRE_CHAVE) {
                    printf("ABRE_CHAVE\n");
                    break;
                }

                if (token.codigo == FECHA_CHAVE) {
                    printf("FECHA_CHAVE\n");
                    break;
                }

                if (token.codigo == ABRE_COL) {
                    printf("ABRE_COL\n");
                    break;
                }

                if (token.codigo == FECHA_COL) {
                    printf("FECHA_COL\n");
                    break;
                }
                break;
            case STRING:
                printf("STRING: %s\n", token.lexema);
                break;
            case CT_I:
                printf("CT_I: %d\n", token.valInt);
                break;
            case CT_PF:
                printf("CT_PF: %f\n", token.valPF);
                break;
            case CHAR:
                printf("CHAR: %c\n", token.lexema[0]);
                break;
            case COMENTARIO:
                printf("COMENTARIO: %s\n", token.lexema);
                break;
            case FIM_EXPR:
                printf("FIM_EXPR\n");
                break;
            case FIM_ARQ:
                printf("FIM_ARQ\n");
                break;
            default:
                printf("TOKEN: %s\n", token.lexema);
                break;
                
            }

        if (token.categoria == FIM_ARQ) {
            break;
        }

    }

        
    fclose(fd);
    return 0;
}