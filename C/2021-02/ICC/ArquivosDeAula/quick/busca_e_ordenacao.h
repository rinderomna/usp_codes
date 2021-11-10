#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FAIL -1
#define DEBUG 0

int* gera_vetor (int tam, int min, int max);

int* gera_vetor_ordenado(int tam, int min, int max);

void mergesort (int* v, int ini, int fim);

void quicksort(int* v, int ini, int fim, int (*eep)());

void imprime_vetor(int*v, int N);

void max_heapify(int* v, int p, int N);

void build_maxheap(int* v, int N);

void heapsort(int* v, int N);
