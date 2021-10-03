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

#include "pilha.h"

enum {
    ABERTURA,
    FECHAMENTO,
    ASPAS,
    OUTRO
};

int tipo_de_clausura(char clausura);

int main() {
    pilha_t *pilha_de_clausuras = criar_pilha();

    char clausura = 0;

    int balanceado = 1;
    
    do {
        clausura = getchar();

        if (clausura == '\n' || clausura == EOF) {
            if (balanceado && get_tamanho_da_pilha(pilha_de_clausuras) == 0) {
                printf("BALANCEADO");
            } else {   
                printf("NÃO BALANCEADO");
                balanceado = 1;
            }

            if (clausura != EOF) {
                printf("\n");
            }

            esvaziar_pilha(pilha_de_clausuras);
        } else if (clausura != ' ') {
            int tipo_da_clausura = tipo_de_clausura(clausura);

            if (tipo_da_clausura == ABERTURA) {
                push(pilha_de_clausuras, clausura);
            } else if (tipo_da_clausura == FECHAMENTO) {
                elem_t ultima_clausura = ' ';
                int status_da_retirada = pop(pilha_de_clausuras, &ultima_clausura);   
                if (status_da_retirada == FAIL ||
                    (ultima_clausura != '[' || clausura != ']') &&
                    (ultima_clausura != '(' || clausura != ')') &&
                    (ultima_clausura != '{' || clausura != '}')
                ) {
                    balanceado = 0;
                }
            } else if (tipo_da_clausura == ASPAS) {
                char ultima_clausura = ' ';
                int status_da_consulta = top(pilha_de_clausuras, &ultima_clausura);

                if (status_da_consulta == FAIL || ultima_clausura != clausura) {
                    push(pilha_de_clausuras, clausura);
                } else {
                    pop(pilha_de_clausuras, &ultima_clausura);
                }
            }
        }
    } while (clausura != EOF);

    destruir_pilha(&pilha_de_clausuras);

    return 0;
}

int tipo_de_clausura(char clausura) {
    if (
        clausura == '[' ||
        clausura == '(' ||
        clausura == '{'
    ) {
        return ABERTURA;
    } else if (
        clausura == ']' ||
        clausura == ')' ||
        clausura == '}'
    ) {
        return FECHAMENTO;
    } else if (clausura == '"') {
        return ASPAS;
    } else {
        return OUTRO;
    }
}