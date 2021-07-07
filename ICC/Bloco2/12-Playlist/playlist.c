#include <stdio.h>
#include <stdlib.h>

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
  Musica *musicas;
  Musica *musica_atual_;
} Playlist;

char *read_line(void);
void adicionar(Playlist *playlist_);
void listar(Playlist *playlist_);
void avancar(Playlist *playlist_);
void retroceder(Playlist *playlist_);
void limpar(Playlist *playlist_);

int main() {
  Playlist minha_playlist;

  minha_playlist.nome = read_line();
  minha_playlist.n_musicas = 0;
  minha_playlist.musicas = NULL;
  minha_playlist.musica_atual_ = NULL;

  char comando;

  do {
    comando = getchar();

    switch (comando) {
      case ADICIONAR: adicionar(&minha_playlist); break;
      case LISTAR: listar(&minha_playlist); break;
      case AVANCAR: avancar(&minha_playlist); break;
      case RETROCEDER: retroceder(&minha_playlist); break;
      case FINALIZAR: limpar(&minha_playlist); break;
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
  if (playlist_->n_musicas == 15) {
    printf("Playlist cheia!\n");
  } else {
    Musica nova_musica;

    nova_musica.nome = read_line();
    nova_musica.artista = read_line();
    scanf("%d", &nova_musica.duracao);


    // Buscando index da música atual, para que na realocação
    // não corra o risco de perder a referência da música atual.
    int index_musica_atual;

    for (int i = 0; i < playlist_->n_musicas; i++) {
      if (playlist_->musica_atual_ == &playlist_->musicas[i]) {
        index_musica_atual = i;
        break;
      }
    }

    playlist_->musicas = (Musica *) realloc(playlist_->musicas, (playlist_->n_musicas + 1) * sizeof(Musica));

    playlist_->musica_atual_ = &playlist_->musicas[index_musica_atual];

    playlist_->musicas[playlist_->n_musicas] = nova_musica;
    
    playlist_->n_musicas++;

    if (playlist_->n_musicas == 1)
      playlist_->musica_atual_ = &(playlist_->musicas[0]);

    printf("Musica %s de %s adicionada com sucesso.\n", nova_musica.nome, nova_musica.artista);
  }
}

void listar(Playlist *playlist_) {
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
  for (int i = 0; i < playlist_->n_musicas; i++) {
    if (playlist_->musica_atual_ == &playlist_->musicas[i]) {
      // A playlist sera circular
      playlist_->musica_atual_ = &playlist_->musicas[(i + 1) % playlist_->n_musicas];
      break;
    }
  }
}

void retroceder(Playlist *playlist_) {
  for (int i = 0; i < playlist_->n_musicas; i++) {
    if (playlist_->musica_atual_ == &playlist_->musicas[i]) {
      // A playlist sera circular
      playlist_->musica_atual_ = &playlist_->musicas[(playlist_->n_musicas + i - 1) % playlist_->n_musicas];
      break;
    }
  }
}

void limpar(Playlist *playlist_) {
  for(int i = 0; i < playlist_->n_musicas; i++) {
    free(playlist_->musicas[i].nome);
    free(playlist_->musicas[i].artista);
  }
  free(playlist_->nome);
  free(playlist_->musicas);
} 