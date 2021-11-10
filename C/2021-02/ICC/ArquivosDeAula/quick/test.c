#include <stdio.h>
#include <stdlib.h>
#include "busca_e_ordenacao.h"

// caso patologio = ordenado
// 
int pivo_inicio(int i, int f) {
	return i; // retorna inicio
}

// caso patologico = ordenado até o centro e depois
//                   ordenado de forma invertida
// 0 1 5 6 9 4 2 1 0
// 9 7 4 3 1 2 5 8 9
int pivo_central(int i, int f) {
	return (int) ((i+f)/2.0); // retorna posicao central
}

// caso patologico = pivo aleatorio
// 		    é um valor proximo do min ou max
int pivo_aleatorio(int i, int f) {
	return (int)(rand()%(f-i))+i ; // retorna posicao aleatoria [i,f]
}


int main (int argc, char* argv[]) {

	if (argc < 2) {
		printf("Informe tamanho do vetor\n");
		return 1;
	}
	int n = atoi(argv[1]);

	clock_t c1, c2;
	double qs_time, ms_time;

	srand(1);
	int* vet = gera_vetor(n, 1, (int)(n*3));
	if (n <= 20) imprime_vetor(vet, n);
	printf("Quicksort...\n");	
	c1 = clock();
	quicksort(vet, 0, n-1, pivo_aleatorio);
	c2 = clock();
	qs_time = (c2-c1)/(double)CLOCKS_PER_SEC;
	if (n <= 20) imprime_vetor(vet, n);

	free(vet);

	srand(1);
	vet = gera_vetor(n, 1, (int)(n*3));
	if (n <= 20) imprime_vetor(vet, n);
	
	printf("Mergesort...\n");	
	c1 = clock();
	mergesort(vet, 0, n-1);
	c2 = clock();
	ms_time = (c2-c1)/(double)CLOCKS_PER_SEC;
	if (n <= 20) imprime_vetor(vet, n);

	printf("Tempo de execução:\n");
	printf("Quicksort = %lf s.\n", qs_time);
	printf("Mergesort = %lf s.\n", ms_time);


	return 0;
}
