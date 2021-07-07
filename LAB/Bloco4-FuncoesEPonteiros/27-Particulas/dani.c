// Danielle Modesti
// No USP: 12543544

#include <stdio.h>
#include <stdlib.h>

#define MATRIX_ROWS 32
#define MATRIX_COLUMNS 64

#define CEMENT '@'
#define AIR ' '
#define WATER '~'
#define SAND '#'

char simulation_state[MATRIX_ROWS][MATRIX_COLUMNS]; // Representa o estado da simulacao.
// Pode ser declarada globalmente para que nao tenha que ser usada como parametro
// como eh global, as funcoes tem acesso a essa matriz

void apply_physics();
void show_particle(char particle); // corzinha na particula

int main() {
    int frame_amount, current_frame, x_coordinate, y_coordinate;
    char new_particle;

    // Inicializar a matriz com ar em todas as posicoes
    for (int i = 0; i < MATRIX_ROWS; i++) {
        for (int j = 0; j < MATRIX_COLUMNS; j++) {
            simulation_state[i][j] = AIR;
        }
    }

    scanf("%d", &frame_amount); // Quantidade de vezes que imprimimos a matriz do estado da simulacao de particulas

    int count = 0;
    system("clear && echo \"\033[1,1H\"");
    while (count < frame_amount) { // Quando o contador chegar no numero total de frames, termina o loop

        /* Leia uma linha no formato
        <numero do frame NO QUAL A PARTICULA NOVA SERA ADICIONADA> <posicao x onde a particula eh adicionada> <posicao y onde a part eh adicionada> <tipo de part>
        `scanf` retorna EOF quando chega ao fim da entrada.*/
        int read_input = scanf(" %d: %d %d %c", &current_frame, &x_coordinate, &y_coordinate, &new_particle);

        /* Verificacao de fim de leitura do scanf: Se não há mais partículas a serem criadas (nao ha mais leituras no .in),
        continue a simulacao com as particulas q tenho, ate o final da simulacao - ate que contador de frames lidos 
        seja = numero max de frames da simulação.*/
        // Quando o scanf terminar de ler o .in, retorna EOF, pois nao conseguiu ler os argumentos, ja que nao tem mais nenhum
        if (read_input == EOF) { 
            // Congele com as particulas que tenho do ultimo scanf e continue com o comportamento delas de alterar a posicao
            current_frame = frame_amount; 
        }
        /* Calcula todos os frames ate o proximo frame onde queremos criar uma particula.
        Queremos parar neste frame current_frame e mudar a matriz, adicionando a nova particula
        Roda um determinado numero de frames ate chegar no frame em que quero adicionar a particula*/
        while (count < current_frame) {
            printf("frame: %d\n", count + 1);
            for (int i = 0; i < MATRIX_COLUMNS + 2; i++)
                show_particle(CEMENT);
            printf("\n");
            // Imprimir a matriz
            for (int i = 0; i < MATRIX_ROWS; i++) {
                show_particle(CEMENT);
                for (int j = 0; j < MATRIX_COLUMNS; j++) 
                    show_particle(simulation_state[i][j]);
                show_particle(CEMENT);
                printf("\n");
            }
            for (int i = 0; i < MATRIX_COLUMNS + 2; i++) 
                show_particle(CEMENT);
            printf("\n");
            // Calcular a física:
            apply_physics();
            system("echo \"\033[1;1H\" && sleep .150");
            count++;
        }
        // Se achamos no scanf uma particula a ser criada, crie ela.
        if (read_input != EOF) {   // Scanf ainda acha leituras no .in
            simulation_state[y_coordinate][x_coordinate] = new_particle;
        }
}

    return 0;
}

/* A atualizacao de fisica deve ser feita em 1 loop. Verificamos as regras da areia e da agua dentro dele
Alterar apenas a matriz de copia
Verificar apenas na matriz original -> isso eh necessario para nao verificar coisas ja atualizadas. Essa matriz esta em 'previous state'*/
void apply_physics() {
    // Receba a copia da matriz. Tenha uma copia de seu conteudo nesse momento, no seu 'previous state'
    char copy_previous_frame[MATRIX_ROWS][MATRIX_COLUMNS];
        
    for (int i = 0; i < MATRIX_ROWS; i++) {
        for (int j = 0; j < MATRIX_COLUMNS; j++) {
            copy_previous_frame[i][j] = simulation_state[i][j];
        }
    }

    // Nesse momento, simulation_state = copia

    /* Percorra a matriz de copia do topo para baixo apenas uma vez, da esquerda para a direita. Atualize de uma vez todas as part.
    Tem que atualizar as regras das particulas na matriz de copia
    Para o proximo frame, atualize a matriz simulation_state com o conteudo de copia :)*/
    for (int i = 0; i < MATRIX_ROWS; i++) {
        for (int j = 0; j < MATRIX_COLUMNS; j++) {
            // Verificacao sempre feita no estado atual do simulador de particulas original. O estado atual atualiza o prox., que esta em copia
            if (simulation_state[i][j] == SAND) { 
                // Atualize regras da areia, com trocas diretas
                if (simulation_state[i + 1][j] == WATER || simulation_state[i + 1][j] == AIR) {
                    // Testar bordas
                    if (i + 1 < MATRIX_ROWS) {
                        char tmp = copy_previous_frame[i][j]; 
                        copy_previous_frame[i][j] = copy_previous_frame[i + 1][j];
                        copy_previous_frame[i + 1][j] = tmp;
                    }
                }
                else if (simulation_state[i + 1][j - 1] == WATER || simulation_state[i + 1][j - 1] == AIR) {
                    if (i + 1 < MATRIX_ROWS && j - 1 >= 0) {
                        char tmp = copy_previous_frame[i][j]; 
                        copy_previous_frame[i][j] = copy_previous_frame[i + 1][j - 1];
                        copy_previous_frame[i + 1][j - 1] = tmp;
                    }
                }
                else if (simulation_state[i + 1][j + 1] == WATER || simulation_state[i + 1][j + 1] == AIR) {
                    if (i + 1 < MATRIX_ROWS && j + 1 < MATRIX_COLUMNS) {
                        char tmp = copy_previous_frame[i][j]; 
                        copy_previous_frame[i][j] = copy_previous_frame[i + 1][j + 1];
                        copy_previous_frame[i + 1][j + 1] = tmp;
                    }
                }
            }
            else if (simulation_state[i][j] == WATER) {
                // Atualize regras da agua, com trocas diretas
                if (i + 1 < MATRIX_ROWS && simulation_state[i + 1][j] == AIR) {
                    char tmp = copy_previous_frame[i][j]; 
                    copy_previous_frame[i][j] = copy_previous_frame[i + 1][j];
                    copy_previous_frame[i + 1][j] = tmp;
                }
                else if (i + 1 < MATRIX_ROWS && j - 1 >= 0 && simulation_state[i + 1][j - 1] == AIR) {
                    char tmp = copy_previous_frame[i][j]; 
                    copy_previous_frame[i][j] = copy_previous_frame[i + 1][j - 1];
                    copy_previous_frame[i + 1][j - 1] = tmp;
                }
                else if (i + 1 < MATRIX_ROWS && j + 1 < MATRIX_COLUMNS && simulation_state[i + 1][j + 1] == AIR) {
                    char tmp = copy_previous_frame[i][j]; 
                    copy_previous_frame[i][j] = copy_previous_frame[i + 1][j + 1];
                    copy_previous_frame[i + 1][j + 1] = tmp;
                }
                else if (j - 1 >= 0 && simulation_state[i][j - 1] == AIR) {
                    char tmp = copy_previous_frame[i][j]; 
                    copy_previous_frame[i][j] = copy_previous_frame[i][j - 1];
                    copy_previous_frame[i][j - 1] = tmp;
                }
                else if (j + 1 < MATRIX_COLUMNS && simulation_state[i][j + 1] == AIR) {
                    char tmp = copy_previous_frame[i][j]; 
                    copy_previous_frame[i][j] = copy_previous_frame[i][j + 1];
                    copy_previous_frame[i][j + 1] = tmp;
                }
            }
        }
    }
    // Copie o conteudo da matriz de copia de volta para a matriz do estado de simulacao
    for (int i = 0; i < MATRIX_ROWS; i++) {
        for (int j = 0; j < MATRIX_COLUMNS; j++) 
            simulation_state[i][j] = copy_previous_frame[i][j];
    }
}

void show_particle(char particle) {
    switch (particle) {
        case CEMENT:
            printf("\033[1;31m");
            break;
        case SAND:
            printf("\033[0;33m");
            break;
        case AIR:
            printf("\033[2;34m");
            break;
        case WATER:
            printf("\033[0;34m");
            break;
    }
    printf("%c\033[0m", particle);
}
