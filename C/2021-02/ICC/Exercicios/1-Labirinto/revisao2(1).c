//Aluna: Maria J�lia Soares De Grandi
//N USP: 12542501

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define FREE '.'
#define PASSED '*'
#define DANGER '#'

typedef struct
{
	char** labyrinth;
	int x;
	int y;
	int maxLine;
	int maxCol;
} LABYRINTH;

typedef struct
{
	int people;
	int freePath;
	int pathTaken;
	double expPercentage;
} ESCAPE_DATA;

char* readLine();
void readingFile(LABYRINTH* labyrinth, FILE* flabyrinth);
char** fileToMatrix(FILE* flabyrinth, int maxLine, int maxCol);
int counting(LABYRINTH* labyrinth, char object);
void runningLabyrinth(LABYRINTH* labyrinth, int i, int j);
void solvingLabyrinth(LABYRINTH* labyrinth, ESCAPE_DATA* escape);
void printEscapeData(LABYRINTH* labyrinth, ESCAPE_DATA* escape);

int main() {
	// Inicializacao e leitura
	LABYRINTH labyrinth;
	ESCAPE_DATA escape;
	
	char* fileName = readLine();
	FILE* flabyrinth = fopen(fileName, "r");

	readingFile(&labyrinth, flabyrinth);

	// Percorrer o labirinto e realizar as contagens
	solvingLabyrinth(&labyrinth, &escape);

	// Impressao dos dados contados e do labirinto final
	printEscapeData(&labyrinth, &escape);

	// Fechar arquivo e desalocar
	fclose(flabyrinth);
	free(fileName);
	for (int i = 0; i < labyrinth.maxLine; i++)
	{
			free(labyrinth.labyrinth[i]);
	}
	free(labyrinth.labyrinth);

	return 0;
}

// Le string de tamanho desconhecido
char* readLine()
{
	char* line = NULL;

	int i = 0;
	do
	{
		line = realloc(line, (i + 1) * sizeof(char));
		line[i] = getchar();

		if (line[i] == '\n' || line[i] == EOF)
		{
			line[i] = '\0';
		}

		i++;
	} while (line[i - 1] != '\0');

	return line;
}

// Transforma o arquivo em matriz de char
char** fileToMatrix(FILE* flabyrinth, int maxLine, int maxCol)
{
	char** labyrinth = NULL;

	labyrinth = malloc(maxLine * sizeof(char*));
	for (int i = 0; i < maxLine; i++)
	{
		labyrinth[i] = malloc(maxCol * sizeof(char));
	}

	for (int i = 0; i < maxLine; i++)
	{
		for (int j = 0; j < maxCol; j++)
		{
			char caractere = fgetc(flabyrinth);
			if (caractere == EOF)
			{
				labyrinth[i][j] = '\0';
				break;
			}
			else if (caractere == '\n')
			{
				labyrinth[i][j] = '\0';
			}
			else
			{
				labyrinth[i][j] = caractere;
			}
		}
	}
	
	return labyrinth;
}

// Le as informa��es do arquivo txt
void readingFile(LABYRINTH* labyrinth, FILE* flabyrinth)
{
	fread(&labyrinth->maxLine, sizeof(int), 1, flabyrinth);
	fgetc(flabyrinth); // pegar o espaco
	fread(&labyrinth->maxCol, sizeof(int), 1, flabyrinth);
	fgetc(flabyrinth); // pegar o '\n'

	labyrinth->maxLine += 1;
	labyrinth->maxCol += 1;

	fread(&labyrinth->x, sizeof(int), 1, flabyrinth);
	fgetc(flabyrinth); // pegar o espaco
	fread(&labyrinth->y, sizeof(int), 1, flabyrinth);
	fgetc(flabyrinth); // pegar o '\n'

	labyrinth->labyrinth = fileToMatrix(flabyrinth, labyrinth->maxLine, labyrinth->maxCol);
}

// Conta quantas vezes o elemento indicado aparece no labirinto naquele momento
int counting(LABYRINTH* labyrinth, char object)
{
	int count = 0;
	for (int i = 0; i < labyrinth->maxLine; i++)
	{
		for (int j = 0; j < labyrinth->maxCol; j++)
		{
			if (labyrinth->labyrinth[i][j] == object)
				count++;
		}
	}

	return count;
}

// Percorre o labirinto de acordo com a ordem de busca
//(Cima, Direita, Baixo, Esquerda)
void runningLabyrinth(LABYRINTH* labyrinth, int i, int j)
{
	// confere se e extremo da matriz
	if (i < 0 || i >= labyrinth->maxLine || j < 0 || j >= labyrinth->maxCol) return;

	if (labyrinth->labyrinth[i][j] == FREE)
	{
		labyrinth->labyrinth[i][j] = PASSED;

		if (labyrinth->labyrinth[i + 1][j] == FREE)
			runningLabyrinth(labyrinth, i + 1, j);

		if (labyrinth->labyrinth[i][j + 1] == FREE)
			runningLabyrinth(labyrinth, i, j + 1);

		if (labyrinth->labyrinth[i - 1][j] == FREE)
			runningLabyrinth(labyrinth, i - 1, j);

		if (labyrinth->labyrinth[i][j - 1] == FREE)
			runningLabyrinth(labyrinth, i, j - 1);
	}
}

// Resolve o labirinto e faz as contagens
void solvingLabyrinth(LABYRINTH* labyrinth, ESCAPE_DATA* escape)
{
	// contar quantos caminhos livres ha
	escape->freePath = counting(labyrinth, FREE);

	// contar quantas pessoas procurando ha
	escape->people = counting(labyrinth, DANGER);

	// percorrer o labirinto
	runningLabyrinth(labyrinth, labyrinth->x, labyrinth->y);
	
	// contar por quantos caminhos passou
	escape->pathTaken = counting(labyrinth, PASSED);

	// calcular a porcentagem percorrida
	escape->expPercentage = escape->pathTaken / escape->freePath * 100;
}

// Imprime os dados da fuga e o labirinto final
void printEscapeData(LABYRINTH* labyrinth, ESCAPE_DATA* escape)
{
	printf("\nVoce escapou de todos! Ninguem conseguiu te segurar!\n");
	printf("Veja abaixo os detalhes da sua fuga:\n");
	printf("----Pessoas te procurando: %d\n", escape->people);
	printf("----Numero total de caminhos validos: %d\n", escape->freePath);
	printf("----Numero total de caminhos visitados: %d\n", escape->pathTaken);
	printf("----Exploracao total do labirinto: %.1lf%%\n", escape->expPercentage);
}
