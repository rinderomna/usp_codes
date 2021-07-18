#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

enum {POWER, TYPE};

int main() {
  int n_types;

  scanf(" %d", &n_types);

  float **Types_Relation;

  Types_Relation = (float **) malloc(n_types * sizeof(float *));
  for (int i = 0; i < n_types; i++)
    Types_Relation[i] = (float *) malloc(n_types * sizeof(float));

  for (int i = 0; i < n_types; i++)
    for (int j = 0; j < n_types; j++)
      scanf(" %f", &Types_Relation[i][j]);

  int n_attacks = 0;
  int attack_power, attack_type;
  int **attacks = NULL;

  while(true) {
    scanf(" %d", &attack_power);

    if (attack_power == -1)
      break;
   
    scanf(" %d", &attack_type);

    n_attacks++;

    attacks = (int **) realloc(attacks, n_attacks * sizeof(int *));
    attacks[n_attacks - 1] = (int *) malloc(2 * sizeof(int));

    *(*(attacks + n_attacks - 1) + POWER) = attack_power;
    *(*(attacks + n_attacks - 1) + TYPE) = attack_type;
  }

  int opponents_type;

  scanf(" %d", &opponents_type);

  int best_attack_index = 0;
  float best_damage;

  for (int i = 1; i < n_attacks; i++) {
    int *this_attack = attacks[i];
    int *best_attack = attacks[best_attack_index];
    
    float this_damage = Types_Relation[this_attack[TYPE]][opponents_type] * (float) this_attack[POWER];
    best_damage = Types_Relation[best_attack[TYPE]][opponents_type] * (float) best_attack[POWER];

    if(this_damage > best_damage) {
      best_attack_index = i;
      best_damage = this_damage;
    }
  }

  for(int i = 0; i < n_attacks; i++)
    free(attacks[i]);
  free(attacks);

  for (int i = 0; i < n_types; i++)
    free(Types_Relation[i]);
  free(Types_Relation);

  printf("O melhor ataque possui indice %d e dano %.2f\n", best_attack_index, best_damage);

  return 0;
}