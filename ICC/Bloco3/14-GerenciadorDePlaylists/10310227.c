// Helio Nogueira Cardoso
// N°USP: 10310227

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
  ADICIONAR = '1',
  LISTAR = '2',
  AVANCAR = '3',
  RETROCEDER = '4',
  SALVAR = '5',
  CARREGAR = '6',
  FINALIZAR = '7'
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
void binaryToNum(char *binFilename);
void salvar(Playlist *playlist_);
void carregar(Playlist *playlist_);
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
      case SALVAR: salvar(&minha_playlist); break;
      case CARREGAR: carregar(&minha_playlist); break;
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

    // Buscando index da musica atual, para que na realocacao
    // nao corra o risco de perder a referencia da musica atual.
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

void binaryToNum(char *binFilename) {
    FILE *fp = fopen(binFilename, "rb");

    double binValue = 0;
    double accumulator = 0.01;
    char ch;
    while (fread(&ch, sizeof(char), 1, fp)) {
        binValue += (double) ch * accumulator;
        accumulator += 0.01;
    }

    fclose(fp);
    printf("%lf\n", binValue);
}

void limpar(Playlist *playlist_) {
  for(int i = 0; i < playlist_->n_musicas; i++) {
    free(playlist_->musicas[i].nome);
    free(playlist_->musicas[i].artista);
  }
  
  free(playlist_->nome);
  free(playlist_->musicas);
} 

void salvar(Playlist *playlist_) {
  FILE *output_file;
  char *nome_output_file;

  nome_output_file = read_line();
  output_file = fopen(nome_output_file, "wb"); 

  int tamanho_nome_playlist = strlen(playlist_->nome);

  fwrite(&tamanho_nome_playlist, sizeof(int), 1, output_file);
  fwrite(playlist_->nome, sizeof(char), tamanho_nome_playlist, output_file);
  fwrite(&playlist_->n_musicas, sizeof(int), 1, output_file);

  for (int i = 0; i < playlist_->n_musicas; i++) {
    int tamanho_nome_musica = strlen(playlist_->musicas[i].nome);
    int tamanho_nome_artista = strlen(playlist_->musicas[i].artista);

    fwrite(&tamanho_nome_musica, sizeof(int), 1, output_file);
    fwrite(playlist_->musicas[i].nome, sizeof(char), tamanho_nome_musica, output_file);
    fwrite(&tamanho_nome_artista, sizeof(int), 1, output_file);
    fwrite(playlist_->musicas[i].artista, sizeof(char), tamanho_nome_artista, output_file);
    fwrite(&playlist_->musicas[i].duracao, sizeof(int), 1, output_file);
  }

  printf("Playlist %s salva com sucesso.\n", nome_output_file);

  fclose(output_file);
  binaryToNum(nome_output_file);
  free(nome_output_file); 
}

void carregar(Playlist *playlist_) {
  FILE *input_file;
  char *nome_input_file;

  nome_input_file = read_line();
  input_file = fopen(nome_input_file, "rb");

  if (input_file == NULL) {
    printf("Arquivo %s nao existe.\n", nome_input_file);
    free(nome_input_file);
    limpar(playlist_);
    exit(0);
  }

  limpar(playlist_);

  // Nome Playlist
  int tamanho_nome_playlist;
  fread(&tamanho_nome_playlist, sizeof(int), 1, input_file);
  
  playlist_->nome = (char *) malloc((tamanho_nome_playlist + 1) * sizeof(char));

  fread(playlist_->nome, sizeof(char), tamanho_nome_playlist, input_file);
  playlist_->nome[tamanho_nome_playlist] = '\0';

  // Numero de Musicas
  fread(&playlist_->n_musicas, sizeof(int), 1, input_file);
  
  // Musicas
  playlist_->musicas = (Musica *) malloc(playlist_->n_musicas * sizeof(Musica));

  for (int i = 0; i < playlist_->n_musicas; i++) {
    // Nome da Musica
    int tamanho_nome_musica;
    fread(&tamanho_nome_musica, sizeof(int), 1, input_file);

    playlist_->musicas[i].nome = (char *) malloc((tamanho_nome_musica + 1) * sizeof(char));

    fread(playlist_->musicas[i].nome, sizeof(char), tamanho_nome_musica, input_file);
    playlist_->musicas[i].nome[tamanho_nome_musica] = '\0';
    
    // Nome do Artista
    int tamanho_nome_artista;
    fread(&tamanho_nome_artista, sizeof(int), 1, input_file);

    playlist_->musicas[i].artista = (char *) malloc((tamanho_nome_artista + 1) * sizeof(char));

    fread(playlist_->musicas[i].artista, sizeof(char), tamanho_nome_artista, input_file);
    playlist_->musicas[i].artista[tamanho_nome_artista] = '\0';

    // Duracao da Musica
    fread(&playlist_->musicas[i].duracao, sizeof(int), 1, input_file);
  }

  // Reatribuicao do Ponteiro de Musica Atual
  playlist_->musica_atual_ = &playlist_->musicas[0];

  printf("Playlist %s carregada com sucesso.\n", nome_input_file);
  binaryToNum(nome_input_file);

  fclose(input_file);
  free(nome_input_file);
}