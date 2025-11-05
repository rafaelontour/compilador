#ifndef ANALEX
#define ANALEX
#include <stdio.h>
#define TAM_MAX_LEXEMA 31

enum TOKEN_CAT {ID = 1, SINAL, PR, CT_I, CT_PF, CHAR, FIM_EXPR, FIM_ARQ, STRING, FIM_DE_LINHA};
// CT_I = Constante Inteira, CHAR = Caractere, STRING = Sequência de caracteres
// CT_PF = Constante Ponto Flutuante

enum SINAIS {
    ATRIB = 1,
    ADICAO,
    SUB,
    MULT,
    DIV,
    IGUAL,
    DIFERENTE,
    E,
    OU,
    NEGACAO,
    MAIOR,
    MENOR,
    MAIOR_IGUAL,
    MENOR_IGUAL,
    ABRE_PAR,
    FECHA_PAR,
    ABRE_CHAVE,
    FECHA_CHAVE,
    ABRE_COL,
    FECHA_COL
};

extern const char *palavrasReservadas[];
extern int contadorLinha;

typedef struct {
    enum TOKEN_CAT categoria;
    union {
        int codigo;
        char lexema[TAM_MAX_LEXEMA];
        int valInt; // Valor da constante inteira em tokens da categoria CT_I
        float valPF; // Valor da constante ponto flutuante em tokens da categoria CT_PF
    };
} TOKEN;

TOKEN Analex(FILE *fd);

#endif