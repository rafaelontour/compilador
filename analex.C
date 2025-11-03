#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "Analex.h"

#define TAM_LEXEMA 50
#define TAM_NUM 20

void erro(const char *msg) {
    printf("Erro na linha %d: %s\n", contadorLinha, msg);
    exit(1);
}

int verificarPalavraReservada(char *lexema) {
    int tamanhoListaPL = sizeof(palavrasReservadas) / sizeof(palavrasReservadas[0]);

    for (int i = 0; i < tamanhoListaPL; i++) {
        if (strcmp(lexema, palavrasReservadas[i]) == 0) {
            return i + 1;
        }
    }

    return 0; // 0 = não é palavra reservada
}

TOKEN Analex(FILE *fd) {

    int estado;

    char lexema[TAM_LEXEMA];
    int tamL = 0;

    char digitos[TAM_NUM];
    int tamD = 0;

    TOKEN token = {};

    estado = 0;

    while (true) {
        char c = fgetc(fd);

        if (c == '\n') contadorLinha++;

        switch(estado) {
            case 0:  // ESTADO INICIAL


                if (c == EOF) {
                    token.categoria = FIM_ARQ;
                    return token;
                }


                if (c == ' ' || c == '\t') {
                    estado = 0;
                    break;
                }

                if (c == '\'') {  // TRANSIÇÃO PARA CARACTERE
                    estado = 1;
                    lexema[tamL] = c;
                    lexema[++tamL] = '\0';
                    break;
                }

                if (c == '_' || isalpha(c)) {  // TRANSIÇÃO PARA IDENTIFICADOR
                    estado = 12;
                    lexema[tamL] = c;
                    lexema[++tamL] = '\0';
                    break;
                }

                if (isdigit(c)) {  // TRANSIÇÃO PARA DÍGITO
                    estado = 9;
                    lexema[tamD] = c;
                    lexema[++tamD] = '\0';
                    break;
                }

                if (c == '\"') {  // TRANSIÇÃO PARA STRING
                    estado = 10;
                    lexema[tamL] = c;
                    lexema[++tamL] = '\0';
                    break;
                }

                if (c == '&') {  // TRANSIÇÃO PARA E
                    estado = 17;
                    lexema[tamL] = c;
                    lexema[++tamL] = '\0';
                    break;
                }

                if (c == '|') {  // TRANSIÇÃO PARA OU
                    estado = 19;
                    lexema[tamL] = c;
                    lexema[++tamL] = '\0';
                    break;
                }

                if (c == '+') {  // RECONHECEU O SINAL DE ADICAO
                    estado = 21;
                    lexema[tamL] = c;
                    lexema[++tamL] = '\0';
                    token.categoria = SINAL;
                    token.codigo = ADICAO;
                    return token;
                }

                if (c == '-') {  // RECONHECEU O SINAL DE SUBTRACAO
                    estado = 22;
                    lexema[tamL] = c;
                    lexema[++tamL] = '\0';
                    token.categoria = SINAL;
                    token.codigo = SUB;
                    return token;
                }
                
                if (c == '*') {  // RECONHECEU O SINAL DE MULTIPLICACAO
                    estado = 28;
                    lexema[tamL] = c;
                    lexema[++tamL] = '\0';
                    token.categoria = SINAL;
                    token.codigo = MULT;
                    return token;
                }

                if (c == '/') {  // TRANSIÇÃO PARA DIVISÃO OU COMENTÁRIO
                    estado = 33;
                    lexema[tamL] = c;
                    lexema[++tamL] = '\0';
                    break;
                }

                if (c == '>') {  // TRANSIÇÃO PARA MAIOR OU MAIOR QUE
                    estado = 23;
                    lexema[tamL] = c;
                    lexema[++tamL] = '\0';
                    break;
                }

                if (c == '<') {  // TRANSIÇÃO PARA MENOR OU MENOR QUE
                    estado = 24;
                    lexema[tamL] = c;
                    lexema[++tamL] = '\0';
                    break;
                }

                if (c == '&') {  // TRANSIÇÃO O SINAL DE E
                    estado = 17;
                    lexema[tamL] = c;
                    lexema[++tamL] = '\0';
                    break;
                }
                
                if (c == '!') {  // TRANSIÇÃO O SINAL DE NEGACAO OU DIFERENTE
                    estado = 31;
                    lexema[tamL] = c;
                    lexema[++tamL] = '\0';
                    break;
                }

                if (c == '=') {  // TRANSIÇÃO O SINAL DE ATRIBUIÇÃO OU COMPARAÇÃO (IGUALDADE)
                    estado = 29;
                    lexema[tamL] = c;
                    lexema[++tamL] = '\0';
                    break;
                }

                if (c == '(') {  // RECONHECEU ABERTURA DE PARENTESES
                    estado = 40;
                    lexema[tamL] = c;
                    lexema[++tamL] = '\0';
                    token.categoria = SINAL;
                    token.codigo = ABRE_PAR;
                    return token;
                }

                if (c == ')') {  // RECONHECEU FECHAMENTO DE PARENTESES
                    estado = 41;
                    lexema[tamL] = c;
                    lexema[++tamL] = '\0';
                    token.categoria = SINAL;
                    token.codigo = FECHA_PAR;
                    return token;
                }

                if (c == '{') {  // RECONHECEU ABERTURA DE CHAVES
                    estado = 42;
                    lexema[tamL] = c;
                    lexema[++tamL] = '\0';
                    token.categoria = SINAL;
                    token.codigo = ABRE_CHAVE;
                    return token;
                }

                if (c == '}') {  // RECONHECEU FECHAMENTO DE CHAVES
                    estado = 43;
                    lexema[tamL] = c;
                    lexema[++tamL] = '\0';
                    token.categoria = SINAL;
                    token.codigo = FECHA_CHAVE;
                    return token;
                }

                if (c == '[') {  // RECONHECEU ABERTURA DE COLCHETES
                    estado = 44;
                    lexema[tamL] = c;
                    lexema[++tamL] = '\0';
                    token.categoria = SINAL;
                    token.codigo = ABRE_COL;
                    return token;
                }

                if (c == ']') {  // RECONHECEU FECHAMENTO DE COLCHETES
                    estado = 45;
                    lexema[tamL] = c;
                    lexema[++tamL] = '\0';
                    token.categoria = SINAL;
                    token.codigo = FECHA_COL;
                    return token;
                }

                break;

            case 1:  // ESTADO DE LEITURA DE CARACTERE
                if (isalpha(c) || isdigit(c) || c == '_') {
                    estado = 2;
                    lexema[tamL] = c;
                    lexema[++tamL] = '\0';
                    break;
                }

            case 2:
                if (c == '\'') {  // TRANSIÇÃO PARA OUTRO, RECONHECEU UM CARACTERE
                    estado = 3;
                    token.categoria = CHAR;
                    token.lexema[0] = lexema[1];
                    token.lexema[1] = '\0';
                    return token;
                }
                
                erro("Estrutura inválida para CHAR!");

            case 9:  // ESTADO DE LEITURA DE DÍGITO
                if (isdigit(c)) {
                    estado = 9;
                    lexema[tamD] = c;
                    lexema[++tamD] = '\0';
                    break;
                }

                if (c == '.') {  // TRANSIÇÃO PARA PONTO FLUTUANTE
                    estado = 15;
                    lexema[tamD] = c;
                    lexema[++tamD] = '\0';
                    break;
                } else {  // TRANSIÇÃO PARA OUTRO, RECONHECEU UM NÚMERO INTEIRO
                    estado = 16;
                    lexema[tamD] = '\0';
                    token.categoria = CT_I; // 
                    token.valInt = atoi(lexema);
                    ungetc(c, fd);
                    return token;
                }
                break;

            case 10:

                if (c == '\n' || c == EOF) {
                    contadorLinha--;
                    lexema[tamL] = '\0';
                    token.categoria = COMENTARIO;
                    strcpy(token.lexema, lexema);
                    return token;
                }

                if (c == '\"') {  // TRANSIÇÃO PARA OUTRO, RECONHECEU UMA STRING
                    estado = 11;
                    lexema[tamL] = c;
                    lexema[++tamL] = '\0';
                    strcpy(token.lexema, lexema);
                    token.categoria = STRING;
                    return token;
                }

                if (isalpha(c) || isdigit(c) || c == ' ' || (!isalpha(c) && !isdigit(c))) {
                    estado = 10;
                    lexema[tamL] = c;
                    lexema[++tamL] = '\0';
                    break;
                }

                break;
            case 12:  // ESTADO DE LEITURA DE IDENTIFICADOR
                if (c == '_' || isalpha(c) || isdigit(c)) {
                    estado = 13;
                    lexema[tamL] = c;
                    lexema[++tamL] = '\0';
                    break;
                }

                if (isalpha(c)) {
                    estado = 13;
                    lexema[tamL] = c;
                    lexema[++tamL] = '\0';
                    break;
                }

            case 13:  // ESTADO DE LEITURA DE IDENTIFICADOR
                if (c == '_' || isalpha(c) || isdigit(c)) {  
                    estado = 13;
                    lexema[tamL] = c;
                    lexema[++tamL] = '\0';
                } else {  // TRANSIÇÃO PARA OUTRO, RECONHECEU IDENTIFICADOR
                    if (c != '\n') ungetc(c, fd);
                    estado = 0;
                    lexema[tamL] = c;
                    lexema[++tamL] = '\0';
                    token.categoria = ID;
                    strcpy(token.lexema, lexema);

                    int palavraReservada = verificarPalavraReservada(token.lexema);
                    if (palavraReservada != 0) erro("Uso de palavra reservada como identificador!");

                    return token;
                }

                break;

            case 15:  // ESTADO DE LEITURA DE PONTO FLUTUANTE
            
                if (c >= '0' && c <= '9') {
                    estado = 16;
                    lexema[tamD] = c;
                    lexema[++tamD] = '\0';
                    break;
                }
                
                if (!isdigit(c)) {
                    erro("Estrutura inválida para CT_PF!");
                }

                estado = 16;
                break;

            case 16:
                if (isdigit(c)) {
                    estado = 16;
                    lexema[tamD] = c;
                    lexema[++tamD] = '\0';
                    break;
                } 

                ungetc(c, fd);
                estado = 0;
                lexema[tamD] = '\0';
                token.categoria = CT_PF;
                token.valPF = atof(lexema);
                return token;

            case 17:
                if (c == '&') {  // RECONHECEU E
                    estado = 18;
                    lexema[tamL] = c;
                    lexema[++tamL] = '\0';
                    token.categoria = SINAL;
                    token.codigo = E;
                    return token;
                }

                erro("Estrutura inválida para E!");

            case 19:
                if (c == '|') {  // TRANSIÇÃO PARA OUTRO
                    estado = 20;
                    lexema[tamL] = c;
                    lexema[++tamL] = '\0';
                    token.categoria = SINAL;
                    token.codigo = OU;
                    return token;
                }

                erro("Estrutura inválida para OU!");

            case 20:
            case 23:
                if (c == '=') {
                    estado = 0;
                    lexema[tamL] = c;
                    lexema[++tamL] = '\0';
                    token.categoria = SINAL;
                    token.codigo = MAIOR_IGUAL;
                    return token;
                }

                ungetc(c, fd);
                estado = 0;
                token.categoria = SINAL;
                token.codigo = MAIOR;
                return token;

            case 24:
                if (c == '=') {
                    estado = 0;
                    lexema[tamL] = c;
                    lexema[++tamL] = '\0';
                    token.categoria = SINAL;
                    token.codigo = MENOR_IGUAL;
                    return token;
                }

                ungetc(c, fd);
                estado = 0;
                token.categoria = SINAL;
                token.codigo = MENOR;
                return token;

            case 26:
                if (c == '=') {
                    estado = 0;
                    lexema[tamL] = c;
                    lexema[++tamL] = '\0';
                    token.categoria = SINAL;
                    token.codigo = DIFERENTE;
                    return token;   
                }

                break;
                
            case 29:
                if (c == '=') {
                    estado = 0;
                    lexema[tamL] = c;
                    lexema[++tamL] = '\0';
                    token.categoria = SINAL;
                    token.codigo = IGUAL;
                    return token;
                }

                ungetc(c, fd);
                estado = 0;
                lexema[tamL] = c;
                lexema[++tamL] = '\0';
                token.categoria = SINAL;
                token.codigo = ATRIB;
                return token;

            case 31:
                if (c == '=') {
                    estado = 32;
                    lexema[tamL] = c;
                    lexema[++tamL] = '\0';
                    token.categoria = SINAL;
                    token.codigo = DIFERENTE;
                    return token;
                }

                if (c == '!') {
                    ungetc(c, fd);
                    estado = 26;
                    lexema[tamL] = c;
                    lexema[++tamL] = '\0';
                    token.categoria = SINAL;
                    token.codigo = NEGACAO;
                    return token;
                }

                ungetc(c, fd);
                estado = 26;
                lexema[tamL] = c;
                lexema[++tamL] = '\0';
                token.categoria = SINAL;
                token.codigo = NEGACAO;
                return token;

            case 32:
                estado = 0;
                break;

            case 33:
                if (c == '/') {
                    estado = 34;
                    lexema[tamL] = c;
                    lexema[++tamL] = '\0';

                } else {  // RECONHECEU DIVISÃO
                    estado = 34;
                    ungetc(c, fd);
                    token.categoria = SINAL;
                    token.codigo = DIV;
                    return token;
                }

            case 34:
                if (c == '\n') {  // RECONHECEU COMENTARIO
                    
                    token.categoria = COMENTARIO;
                    strcpy(token.lexema, lexema);
                    return token;
                }

                if (c == EOF) {
                    token.categoria = FIM_ARQ;
                    return token;
                }

                if (isalpha(c) || isdigit(c) || (!isalpha(c) && !isdigit(c))) {
                    estado = 34;
                    lexema[tamL] = c;
                    lexema[++tamL] = '\0';
                    break;
                }
            
        }
    }
}