#include <stdio.h>
#include <stdlib.h>

enum comandos {
    PARAR,
    CADASTRAR,
    ADD_ATAQUE,
    CONSULTAR_POKEMON,
    CONSULTAR_ATAQUE,
};

typedef struct ataque {
    char nome[20];
    int poder_base;
    float acuracia;
    char classe;
} Ataque;

typedef struct atributo {
    int hp;
    int ataque;
    int defesa;
    int ataque_especial;
    int defesa_especial;
    int velocidade;
} Atributo;

typedef struct pokemon {
    char nome[50];
    char tipo_primario[20];
    char tipo_secundario[20];
    Atributo atributos;
    Ataque ataques[4];
} Pokemon;

typedef struct pokedex {
    Pokemon *pokemons;
    int n_pokemons;
} Pokedex;

void cadastrar(Pokedex *pokedex_);
void add_ataque(Pokedex *pokedex_);
void consultar_pokemon(Pokedex *pokedex_);
void consultar_ataque(Pokedex *pokedex_);
void limpar(Pokedex *pokedex_);

int main() {
    Pokedex pokedex;
    pokedex.pokemons = NULL;
    pokedex.n_pokemons = 0;

    int comando;
    
    do {
        scanf(" %d", &comando);

        switch (comando) {
            case CADASTRAR: cadastrar(&pokedex); break;
            case ADD_ATAQUE: add_ataque(&pokedex); break;
            case CONSULTAR_POKEMON: consultar_pokemon(&pokedex); break;
            case CONSULTAR_ATAQUE: consultar_ataque(&pokedex); break;
            case PARAR: limpar(&pokedex); break;
        }
    } while (comando != PARAR);

    return 0;
}

void cadastrar(Pokedex *pokedex_) {
    Pokemon novo_pokemon;
    
    scanf("%*[\r\n]s"); 
    scanf("%s", novo_pokemon.nome);
    scanf("%*[\r\n]s");
    scanf("%s", novo_pokemon.tipo_primario);
    scanf("%*[\r\n]s"); 
    scanf("%s", novo_pokemon.tipo_secundario);
    scanf(" %d", &novo_pokemon.atributos.hp);
    scanf(" %d", &novo_pokemon.atributos.ataque);
    scanf(" %d", &novo_pokemon.atributos.defesa);
    scanf(" %d", &novo_pokemon.atributos.ataque_especial);
    scanf(" %d", &novo_pokemon.atributos.defesa_especial);
    scanf(" %d", &novo_pokemon.atributos.velocidade);
    scanf("%*[\r\n]s"); 

    pokedex_->pokemons = (Pokemon *) realloc(pokedex_->pokemons, (++pokedex_->n_pokemons) * sizeof(Pokemon));
    pokedex_->pokemons[pokedex_->n_pokemons - 1] = novo_pokemon;
}

void add_ataque(Pokedex *pokedex_) {
    int pokeindex;
    int ataque_index;
    Ataque novo_ataque;
    
    scanf(" %d", &pokeindex);
    scanf(" %d", &ataque_index);
    scanf("%*[\r\n]s"); 
    scanf("%s", novo_ataque.nome);
    scanf(" %d", &novo_ataque.poder_base);
    scanf(" %f", &novo_ataque.acuracia);
    scanf(" %c", &novo_ataque.classe); 

    pokedex_->pokemons[pokeindex].ataques[ataque_index] = novo_ataque;
}

void consultar_pokemon(Pokedex *pokedex_) {
    int pokeindex;

    scanf(" %d", &pokeindex);

    printf("Nome do Pokemon: %s\n", pokedex_->pokemons[pokeindex].nome);
    printf("Tipo primario: %s\n", pokedex_->pokemons[pokeindex].tipo_primario);
    printf("Tipo secundario: %s\n", pokedex_->pokemons[pokeindex].tipo_secundario);
    printf("Status:\n");
    printf("\tHP: %d\n", pokedex_->pokemons[pokeindex].atributos.hp);
    printf("\tAtaque: %d\n", pokedex_->pokemons[pokeindex].atributos.ataque);
    printf("\tDefesa: %d\n", pokedex_->pokemons[pokeindex].atributos.defesa);
    printf("\tAtaque Especial: %d\n", pokedex_->pokemons[pokeindex].atributos.ataque_especial);
    printf("\tDefesa Especial: %d\n", pokedex_->pokemons[pokeindex].atributos.defesa_especial);
    printf("\tVelocidade: %d\n\n", pokedex_->pokemons[pokeindex].atributos.velocidade);   
}

void consultar_ataque(Pokedex *pokedex_) {
    int pokeindex;
    int ataque_index;

    scanf(" %d", &pokeindex);
    scanf(" %d", &ataque_index);
    scanf("%*[\r\n]s"); 

    printf("Nome do Ataque: %s\n", pokedex_->pokemons[pokeindex].ataques[ataque_index].nome);
    printf("Poder base: %d\n", pokedex_->pokemons[pokeindex].ataques[ataque_index].poder_base);
    printf("Acuracia: %f\n", pokedex_->pokemons[pokeindex].ataques[ataque_index].acuracia);
    printf("Classe: %c\n\n", pokedex_->pokemons[pokeindex].ataques[ataque_index].classe);
}

void limpar(Pokedex *pokedex_) {
    free(pokedex_->pokemons);
}