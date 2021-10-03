#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

enum {
  ADICIONAR = '1',
  LISTAR = '2',
  AVANCAR = '3',
  RETROCEDER = '4',
  FINALIZAR = '5'
};

typedef struct musica {
  char *nome;
  char *artista;
  int duracao;
} Musica;

typedef struct playlist {
  char *nome;
  int n_musicas;
  Musica musicas[15];
  Musica *musica_atual_;
} Playlist;

char *read_line(void);
void adicionar(Playlist *playlist_);
void listar(Playlist *playlist_);
void avancar(Playlist *playlist_);
void retroceder(Playlist *playlist_);
void limpar(Playlist *playlist_);

int main() {
  bool eh_invalido = false;
  Playlist minha_playlist;

  system("clear");
  printf("Nome da sua Playlist: ");

  minha_playlist.nome = read_line();
  minha_playlist.n_musicas = 0;
  minha_playlist.musica_atual_ = NULL;

  system("clear");
  printf("Playlist '%s' criada com sucesso!\n", minha_playlist.nome);

  char comando = '\n';

  do {
    if (comando == '\n') {
      if (eh_invalido) {
        system("clear");
        printf("Comando Invalido\n");
        eh_invalido = false;
      }
      printf("\n-- COMANDOS --\n\n1 => ADICIONAR\n2 => LISTAR\n3 => AVANCAR\n4 => RETROCEDER\n5 => FINALIZAR\n");
      printf("\nEntre um comando: ");
    }
    
    comando = getchar();

    switch (comando) {
      case ADICIONAR: {
        adicionar(&minha_playlist); 
        eh_invalido = false;
        break;
      }
      case LISTAR: {
        listar(&minha_playlist); 
        eh_invalido = false;
        break;
      }
      case AVANCAR: {
        avancar(&minha_playlist);
        eh_invalido = false;
        break;
      }
      case RETROCEDER: {
        retroceder(&minha_playlist);
        eh_invalido = false;
        break;
      }
      case FINALIZAR: {
        limpar(&minha_playlist);
        eh_invalido = false;
        break;
      }
      default: {
        if (comando != '\n') eh_invalido = true;
      }
    }

  } while (comando != FINALIZAR);
  
  return 0;
}

char *read_line(void) {
  char *line = NULL;
  char c;
  int n_chars = 0;

  while ((c = getchar()) == '\n' || (c == '\r'));

  if (c != EOF) ungetc(c, stdin);
  
  do {
    c = getchar();
    
    n_chars++;
    line = (char *) realloc(line, n_chars);

    if (c != '\n')
      *(line + n_chars - 1) = c;
    else
      *(line + n_chars - 1) = '\0';

  } while (c != '\n');

  return line;
}

void adicionar(Playlist *playlist_) {
  system("clear");
  if (playlist_->n_musicas == 15) {
    printf("Playlist cheia!\n");
  } else {
    printf("Adicionando música:\n");
    Musica nova_musica;

    printf("\nNome da Música: ");
    nova_musica.nome = read_line();
    printf("\nArtista: ");
    nova_musica.artista = read_line();
    printf("\nDuracao em segundos: ");
    scanf("%d", &nova_musica.duracao);

    playlist_->musicas[playlist_->n_musicas] = nova_musica;
    
    playlist_->n_musicas++;

    if (playlist_->n_musicas == 1)
      playlist_->musica_atual_ = &(playlist_->musicas[0]);

    system("clear");

    printf("Musica '%s' de '%s' adicionada com sucesso.\n", nova_musica.nome, nova_musica.artista);
  }
}

void listar(Playlist *playlist_) {
  system("clear");
  printf("---- Playlist: %s ----\n", playlist_->nome);
  printf("Total de musicas: %d\n", playlist_->n_musicas);

  for (int i = 0; i < playlist_->n_musicas; i++) {
    if (playlist_->musica_atual_ == &playlist_->musicas[i])
      printf("\n=== NOW PLAYING ===\n");
    else
      printf("\n");
    printf("(%d). '%s'\n", i + 1, playlist_->musicas[i].nome);
    printf("Artista: %s\n", playlist_->musicas[i].artista);
    printf("Duracao: %d segundos\n", playlist_->musicas[i].duracao);
  }

  printf("\n");
}

void avancar(Playlist *playlist_) {
  system("clear");
  printf("Avancando\n");
  for (int i = 0; i < playlist_->n_musicas; i++) {
    if (playlist_->musica_atual_ == &playlist_->musicas[i]) {
      // A playlist sera circular
      playlist_->musica_atual_ = &playlist_->musicas[(i + 1) % playlist_->n_musicas];
      break;
    }
  }
}

void retroceder(Playlist *playlist_) {
  system("clear");
  printf("Retrocedendo\n");
  for (int i = 0; i < playlist_->n_musicas; i++) {
    if (playlist_->musica_atual_ == &playlist_->musicas[i]) {
      // A playlist sera circular
      playlist_->musica_atual_ = &playlist_->musicas[(playlist_->n_musicas + i - 1) % playlist_->n_musicas];
      break;
    }
  }
}

void limpar(Playlist *playlist_) {
  system("clear");
  for(int i = 0; i < playlist_->n_musicas; i++) {
    free(playlist_->musicas[i].nome);
    free(playlist_->musicas[i].artista);
  }
  free(playlist_->nome);
} 