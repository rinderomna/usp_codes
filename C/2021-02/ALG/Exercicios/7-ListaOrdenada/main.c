/* ______________________________________________________
 *|    SCC0202 - Algoritmos e Estruturas de Dados I      |
 *|             [Segundo Semestre de 2021]               |
 *|                                                      |
 *|----------| Exercicio 07: Lista Ordenada |------------|
 *|                                                      |
 *| Codigo por: Helio Nogueira Cardoso - N°USP: 10310227 |
 *|______________________________________________________|
 */

#include <stdio.h>

#include "priority_queue.h"
#include "str.h"

typedef struct person_ {
    char name[51];
    int id_code;
} person_t;

/* |read_person|
 * Reads person information from stdin in specified format
 */
void read_person(person_t *person);

/* |index_by_id|
 * Returns the index of the person with the passed id code.
 * If there is no person with that id, than -1 is returned.
 */
int index_by_id(p_queue_t *q, int id_code);

/* |print_db|
 * Prints all persons information in specified format.
 */
void print_db(p_queue_t *q);

int main() {
    // A priotiry queue was used in order to insert the persons in order.
    // That was made by assigning the priority to be the id_code of each person.
    p_queue_t *data_bank = create_priority_queue((int)sizeof(person_t));

    string_t command;

    // move_on is a boolean that indicates to the program whether it should keep reading from stdin.
    // When it is false, the program proceeds to termination.
    int move_on = 1;

    while (move_on) {
        command = read_until(stdin, ' ');

        if (compare_strings(command, "INSERE") == 0) {
            person_t person;

            read_person(&person);

            // If the id_code does not exist, then insert the person in the priority queue.
            // id_code is the priority, such that the list will always be in ascending order of codes.
            if (index_by_id(data_bank, person.id_code) == -1) {
                add_to_priority_queue(data_bank, &person, person.id_code);
            } else {
                printf("INVALIDO\n");
            }
        } else if (compare_strings(command, "REMOVE") == 0) {
            int id_code_to_remove;

            scanf(" %d", &id_code_to_remove);

            int index_to_remove = index_by_id(data_bank, id_code_to_remove);

            // If the id_code exists, then remove the person with that code.
            if (index_to_remove != -1) {
                person_t person;
                remove_element_in_priority_queue(data_bank, index_to_remove, &person);
            } else {
                printf("INVALIDO\n"); 
            }
        } else if (compare_strings(command, "IMPRIMIR") == 0) { 
            print_db(data_bank);
        } else if (compare_strings(command, "") == 0) {
            // If the line is empty, then the program should terminate.

            move_on = 0;
        } else {
            printf("INVALIDO\n");
        }

        destroy_string(command);
    }

    destroy_priority_queue(&data_bank);

    return 0;
}

void read_person(person_t *person) {
    scanf(" %d", &person->id_code);

    string_t name = read_line(stdin);

    int n = (int)string_length(name);
    
    copy_memory(person->name, name, n + 1);

    destroy_string(name);
}

int index_by_id(p_queue_t *q, int id_code) {
    int element_index = -1;

    int n = get_priority_queue_size(q);

    for (int i = 0; i < n; i++) {
        person_t person;
        access_element_in_priority_queue(q, i,&person);

        if (person.id_code == id_code) {
            element_index = i;
        }
    }

    return element_index;
}

void print_db(p_queue_t *q) {
    int n = get_priority_queue_size(q);

    if (n == 0) {
        printf("VAZIA\n");
    } else {
        for (int i = 0; i < n; i++) {
            person_t cur_person;

            access_element_in_priority_queue(q, i,&cur_person);

            printf("%d,%s", cur_person.id_code, cur_person.name);

            if (i < n - 1) {
                printf("; ");
            } else {
                printf(";\n");
            }
        }
    }
}
