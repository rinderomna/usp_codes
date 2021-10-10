/* ______________________________________________________
 *|    SCC0202 - Algoritmos e Estruturas de Dados I      |
 *|             [Segundo Semestre de 2021]               |
 *|                                                      |
 *|--------| Exercicio 05: Sequencia Balanceada |--------|
 *|                                                      |
 *| Codigo por: Helio Nogueira Cardoso - N°USP: 10310227 |
 *|______________________________________________________|
 */

#include <stdio.h>
#include <stdlib.h>

#include "pilha.h"

#define FALSE 0
#define TRUE 1
typedef int bool_t;

typedef enum tipo_delimitador {
    ABERTURA,
    FECHAMENTO,
    ASPAS,
    OUTRO
} tipo_delimitador_t;

tipo_delimitador_t tipo_de_delimitador(char delimitador);

int main() {
    pilha_t *pilha_de_delimitadores = criar_pilha();

    char delimitador = 0;

    bool_t balanceado = TRUE;

    do {
        delimitador = getchar();

        if (delimitador == '\n' || delimitador == EOF) {
            if (balanceado && get_tamanho_da_pilha(pilha_de_delimitadores) == 0) {
                printf("BALANCEADO");
            } else {
                printf("NÃO BALANCEADO");
                balanceado = TRUE;
            }

            if (delimitador != EOF) {
                printf("\n");
            }

            esvaziar_pilha(pilha_de_delimitadores);
        } else if (delimitador != ' ') {
            int tipo_do_delimitador = tipo_de_delimitador(delimitador);

            if (tipo_do_delimitador == ABERTURA) {
                push(pilha_de_delimitadores, delimitador);
            } else if (tipo_do_delimitador == FECHAMENTO) {
                elem_t ultimo_delimitador = ' ';
                int status_da_retirada = pop(pilha_de_delimitadores, &ultimo_delimitador);
                if (status_da_retirada == FAIL ||
                    (ultimo_delimitador != '[' || delimitador != ']') &&
                        (ultimo_delimitador != '(' || delimitador != ')') &&
                        (ultimo_delimitador != '{' || delimitador != '}')) {
                    balanceado = FALSE;
                    scanf("%*[^\r\n]s");  // Ignora ate o final da linha
                }
            } else if (tipo_do_delimitador == ASPAS) {
                elem_t ultimo_delimitador = ' ';
                int status_da_consulta = top(pilha_de_delimitadores, &ultimo_delimitador);

                if (status_da_consulta == FAIL || ultimo_delimitador != delimitador) {
                    push(pilha_de_delimitadores, delimitador);
                } else {
                    pop(pilha_de_delimitadores, &ultimo_delimitador);
                }
            }
        }
    } while (delimitador != EOF);

    destruir_pilha(&pilha_de_delimitadores);

    return EXIT_SUCCESS;
}

tipo_delimitador_t tipo_de_delimitador(char delimitador) {
    if (
        delimitador == '[' ||
        delimitador == '(' ||
        delimitador == '{') {
        return ABERTURA;
    } else if (
        delimitador == ']' ||
        delimitador == ')' ||
        delimitador == '}') {
        return FECHAMENTO;
    } else if (delimitador == '"') {
        return ASPAS;
    } else {
        return OUTRO;
    }
}