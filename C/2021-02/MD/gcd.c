/* |Algoritmo de Euclides Estendido|
 * 
 * [TRABALHO 5 - 2° SEMESTRE DE 2021]
 * SMA0180 - Matemática Discreta I (2021)
 * Professor: Eugenio Tommaso Massa
 * 
 * Por: Hélio Nogueira Cardoso
 * N°USP: 10310227
 *
 *  Algoritmo para o cálculo do Máximo Divisor Comum (GCD - Greatest Common Divisor)
 * entre dois números inteiros a e b, sendo a > b >= 0.
 * 
 *  Retorna a devida combinação linear do tipo GCD(a, b) = m * a + n * b
 * 
 *  Se GCD(a, b) = 1, [b] é invertível em Z_a (e tal inverso é mostrado).
 * Caso contrário, [b] não é invertível em Z_a.
 * 
 *  O código foi feito baseado na execução numa tabela que organiza:
 *   - Resto R (na divisão inteira dos dois restos anteriores)
 *   - Quociente Q (na divisão inteira dos dois restos anteriores)
 *   - m e n tais que R = m * a + n * b para cada linha.
 * 
 * As duas primeiras linhas são preenchidas da seguinte forma:
 * 
 * ____________________________________________________
 *    R      |      Q      |      m      |      n    
 * ____________________________________________________
 *      a    |          *  |          1  |          0
 *      b    |          *  |          0  |          1
 * ____________________________________________________
 * 
 *  Pois:
 *   a = 1 * a + 0 * b
 *   b = 0 * a + 1 * b
 * 
 *  Para tais linhas, não há quociente. Mas, a partir delas, podemos preencher
 * as próximas linhas seguindo a seguinte regra (que pode ser provada):
 * 
 *  m_{i+1} = m_{i-1} - q_{i+1} * m_i
 *  n_{i+1} = n_{i-1} - q_{i+1} * n_i
 * 
 *  Fazemos isso até que o resto da linha seguinte seja 0. 
 * O GCD será o último resto, com a devida combinação linear escrita em tal linha.
 * 
 *  Como dito, se o GCD for 1, [b] é invertível em Z_a, e seu inverso é [n] na linha.
 * (que é o número que o multiplica: GCD(a, b) = 1 = m * a + n * b)
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct euclides_table {
    long long int *R;
    long long int *Q;
    long long int *m;
    long long int *n;
    long long int n_lines;
} euclides_table_t;

int main(int argc, char *argv[]) {
    // Testando se a quantidade mínima de argumentos não foi passada:

    if (argc < 3) {
        printf("\nInput errado! Entre 2 números inteiros a e b tais que (a > b >= 0)\n");

        return EXIT_FAILURE;
    }

    long long int a = atoll(argv[1]);
    long long int b = atoll(argv[2]);

    // Testando se a condição (a > b >= 0) não é atendida:

    if (a <= b || a <= 0 || b < 0) {
        printf("\nInput errado! Condição: (a > b >= 0) \n");

        return EXIT_FAILURE;
    }

    euclides_table_t table;

    // Alocando e preenchendo as primeiras 2 linhas com os valores-base:

    table.n_lines = 2;

    table.R = (long long int *)malloc(table.n_lines * sizeof(long long int));
    table.Q = (long long int *)malloc(table.n_lines * sizeof(long long int));
    table.m = (long long int *)malloc(table.n_lines * sizeof(long long int));
    table.n = (long long int *)malloc(table.n_lines * sizeof(long long int));

    table.R[0] = a;
    table.m[0] = 1;
    table.n[0] = 0;

    table.R[1] = b;
    table.m[1] = 0;
    table.n[1] = 1;

    // Realocando mais linhas e preenchendo com todos o valores até a linha com o GCD:

    int i = 1;

    while (table.R[i] != 0) {
        table.n_lines++;

        table.R = (long long int *)realloc(table.R, table.n_lines * sizeof(long long int));
        table.Q = (long long int *)realloc(table.Q, table.n_lines * sizeof(long long int));
        table.m = (long long int *)realloc(table.m, table.n_lines * sizeof(long long int));
        table.n = (long long int *)realloc(table.n, table.n_lines * sizeof(long long int));

        table.R[i + 1] = table.R[i - 1] % table.R[i];
        table.Q[i + 1] = table.R[i - 1] / table.R[i];
        table.m[i + 1] = table.m[i - 1] - (table.Q[i + 1] * table.m[i]);
        table.n[i + 1] = table.n[i - 1] - (table.Q[i + 1] * table.n[i]);

        i++;
    }

    // Imprimindo toda a tabela:

    printf("___________________________________________________\n");
    printf("    R      |      Q      |      m      |      n    \n");
    printf("___________________________________________________\n");

    for (int j = 0; j < table.n_lines - 1; j++) {
        if (j < 2) {
            printf("%9lld  |  %9s  |  %9lld  |  %9lld\n", table.R[j], "*", table.m[j], table.n[j]);
        } else {
            printf("%9lld  |  %9lld  |  %9lld  |  %9lld\n", table.R[j], table.Q[j], table.m[j], table.n[j]);
        }
    }

    printf("___________________________________________________\n");

    // Imprimindo resultados e conclusões:

    printf("\nGCD(%lld, %lld) = %lld", a, b, table.R[i - 1]);
    printf(" = (%lld) * %lld + (%lld) * %lld", table.m[i - 1], a, table.n[i - 1], b);

    if (table.R[i - 1] != 1) {
        printf("\nPortanto, [%lld] não é invertível em Z_%lld.\n\n", b, a);
    } else {
        // Mudando [n] para um equilavente tal que (0 <= n < a):

        long long int n = table.n[i - 1];

        if (n < 0) {
            while(n < 0) {
                n += a;
            }
        } else if (n >= a) {
            while(n >= a) {
                n -= a;
            }
        }

        if (table.n[i - 1] == n) {
            printf("\nPortanto, o inverso de [%lld] em Z_%lld é [%lld].\n\n", b, a, n);
        } else {
            printf("\nPortanto, o inverso de [%lld] em Z_%lld é [%lld] = [%lld].\n\n", b, a, table.n[i - 1], n);
        }
    }

    // Liberando a memória alocada:

    free(table.R);
    free(table.Q);
    free(table.m);
    free(table.n);

    return EXIT_SUCCESS;
}