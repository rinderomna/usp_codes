/* ______________________________________________________
 *|    SCC0202 - Algoritmos e Estruturas de Dados I      |
 *|             [Segundo Semestre de 2021]               |
 *|                                                      |
 *|--------| Exercicio 04: Lista de Prioridade |---------|
 *|                                                      |
 *| Codigo por: Helio Nogueira Cardoso - N°USP: 10310227 |
 *|______________________________________________________|
 */

#include <stdio.h>
#include <stdlib.h>

#include "priority_queue.h"
#include "str.h"

typedef int bool_t;

typedef struct person {
    symbol_t name[100];
    int age;
    bool_t has_health_condition;
} person_t;

/* |read_person|
 * Fills the passed person with information read from stdin in specified format.
 */
void read_person(person_t *person);

/* |print_person|
 * Prints passed person information in specified format.
 */
void print_person(person_t *person);

/* |add_person_to_priority_queue|
 * Adds specified person to priority queue, considering its priority:
 *    1 * (is under 60?) + 2 * (has no health condition?) + 1
 *
 *    # Priority 1: The highest. Person is 60 or over 60 and has aggravating health condition. 
 *    # Priority 2: Person is under 60 and has aggravating health condition. 
 *    # Priority 3: Person is 60 or over 60 and has no aggravating health condition. 
 *    # Priority 4: The lowest. Person is under 60 and has no aggravating health condition.
 */
void add_person_to_priority_queue(p_queue_t *q, person_t *person);

int main() {
    p_queue_t *q = create_priority_queue(sizeof(person_t));

    int n_commands = 0;

    scanf(" %d", &n_commands);
    
    for (int i = 0; i < n_commands; i++) {
        string_t command = read_until(stdin, ' ');

        person_t person;

        if (compare_strings(command, "ENTRA") == 0) {
            read_person(&person);
            add_person_to_priority_queue(q, &person);
        } else if (compare_strings(command, "SAI") == 0) {
            if (get_priority_queue_size(q) == 0) {
                printf("FILA VAZIA");
                if (i < n_commands - 1) new_line();
            } else {
                remove_from_priority_queue(q, &person);
                print_person(&person);
                if (i < n_commands - 1) new_line();
            }
        }

        destroy_string(command);
    }

    destroy_priority_queue(&q);

    return EXIT_SUCCESS;
}

void read_person(person_t *person) {
    scanf(" %s %d %d", person->name, &person->age, &person->has_health_condition);
}

void print_person(person_t *person) {
    printf("%s %d %d", person->name, person->age, person->has_health_condition);
}

void add_person_to_priority_queue(p_queue_t *q, person_t *person) {
    int priority = 1 * (person->age < 60) + 2 * !(person->has_health_condition) + 1;

    add_to_priority_queue(q, person, priority);
}