/* ______________________________________________________
 *|  SCC0201 — Introducao a Ciencias da Computacao II    |
 *|             [Segundo Semestre de 2021]               |
 *|                                                      |
 *|--------| Trabalho 02: Compressao de Audio |----------|
 *|                                                      |
 *| Codigo por: Helio Nogueira Cardoso - N°USP: 10310227 |
 *|______________________________________________________|
 */

#include <complex.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "str.h"

typedef int bool_t;
#define FALSE 0
#define TRUE 1

/* |c_coefficient_t|
 * Complex Coefficient type carries not only the its complex value, but also
 * its original index, which is the index before the sorting by magnitude. This
 * is so in order to be able to return each element to its original position 
 * after the nullification step.
 */
typedef struct c_coefficient {
    int original_index;
    double complex value;
} c_coefficient_t;

/* |read_wav_data|
 * Reads a wav file and stores its information in an unsigned char verctor,
 * dinamically allocated.
 * 
 * @param fname (char *): name of/path to thewav file to be read.
 * @param dataSize (int *): reference to an integer variable that will store the
 * number of samples in the audio file read. 
 * @return (unsigned char *): pointer to the first byte of a dinamically allocated
 * vector of audio samples
 */
unsigned char *read_wav_data(char *fname, int *dataSize);

c_coefficient_t *DFT(unsigned char *audio, int length);

unsigned char *inverse_DFT(c_coefficient_t *complex_coefficients, int length);

double magnitude(double complex z);

int count_negatives(c_coefficient_t *complex_coefficients, int length);

bool_t complex_comparator(c_coefficient_t z1, c_coefficient_t z2);

bool_t index_comparator(c_coefficient_t z1, c_coefficient_t z2);

void complex_merge(c_coefficient_t *v, int start, int end);

void complex_mergesort(c_coefficient_t *v, int start, int end);

void index_merge(c_coefficient_t *v, int start, int end);

void index_mergesort(c_coefficient_t *v, int start, int end);

int main() {
    string_t audio_file_name = read_line(stdin);

    int T = 0;
    scanf(" %d", &T);

    int data_size = 0;
    unsigned char *samples = read_wav_data((char *)audio_file_name, &data_size);

    c_coefficient_t *complex_coefficients = DFT(samples, data_size);

    int n_negatives = count_negatives(complex_coefficients, data_size);

    complex_mergesort(complex_coefficients, 0, data_size - 1);

    printf("%d\n", data_size);
    printf("%d\n", n_negatives);

    for (int i = 0; i < T; i++) {
        printf("%d", (int)magnitude(complex_coefficients[i].value));

        if (i < T - 1) new_line();
    }

    for (int i = T; i < data_size; i++) {
        complex_coefficients[i].value = 0;
    }

    index_mergesort(complex_coefficients, 0, data_size - 1);

    unsigned char *compressed_samples = inverse_DFT(complex_coefficients, data_size);

    FILE *compressed_audio = NULL;
    FILE *original_audio = NULL;

    original_audio = fopen((char *)audio_file_name, "rb");
    compressed_audio = fopen("compressed_audio.wav", "wb");

    void *cur_byte = malloc(44);

    fread(cur_byte, 44, 1, original_audio);
    fwrite(cur_byte, 44, 1, compressed_audio);

    free(cur_byte);

    for (int i = 0; i < data_size; i++) {
        fwrite(&compressed_samples[i], sizeof(unsigned char), 1, compressed_audio);
    }

    fclose(compressed_audio);
    fclose(original_audio);

    free(complex_coefficients);
    free(samples);
    free(compressed_samples);
    destroy_string(audio_file_name);

    return EXIT_SUCCESS;
}

unsigned char *read_wav_data(char *fname, int *dataSize) {
    FILE *fp = fopen(fname, "rb");
    unsigned char buf4[4];

    fseek(fp, 40, SEEK_SET);
    fread(buf4, sizeof(buf4), 1, fp);
    *dataSize = buf4[0] | buf4[1] << 8 | buf4[2] << 16 | buf4[3] << 24;

    unsigned char *data = (unsigned char *)malloc(sizeof(*data) * (*dataSize));

    int i = 0;
    while (i < *dataSize) {
        fread(&data[i++], sizeof(unsigned char), 1, fp);
    }
    
    fclose(fp);
    
    return data;
}

c_coefficient_t *DFT(unsigned char *audio, int length) {
    c_coefficient_t *coef = (c_coefficient_t *)calloc(length, sizeof(c_coefficient_t));

    for (int k = 0; k < length; k++) {
        for (int n = 0; n < length; n++) {
            coef[k].value += audio[n] * cexp((-2.0 * M_PI * (((k + 1) * n * 1.0) / (length * 1.0))) * _Complex_I);
        }
        coef[k].original_index = k;
    }

    return coef;
}

unsigned char *inverse_DFT(c_coefficient_t *complex_coefficients, int length) {
    unsigned char *audio = (unsigned char *)calloc(length, sizeof(unsigned char));

    for (int n = 0; n < length; n++) {
        double complex c_x_n = 0;
        for (int k = 0; k < length; k++) {
            c_x_n += complex_coefficients[k].value * cexp((2.0 * M_PI * (((k + 1) * n * 1.0) / (length * 1.0))) * _Complex_I);
        }

        c_x_n /= (double)length;

        audio[n] = (int)creal(c_x_n);
    }

    return audio;
}

double magnitude(double complex z) {
    return sqrt(pow(creal(z), 2) + pow(cimag(z), 2));
}

int count_negatives(c_coefficient_t *complex_coefficients, int length) {
    int counter = 0;

    for (int i = 0; i < length; i++) {
        if (creal(complex_coefficients[i].value) <= 0 && cimag(complex_coefficients[i].value) <= 0) {
            counter++;
        }
    }

    return counter;
}

bool_t complex_comparator(c_coefficient_t z1, c_coefficient_t z2) {
    return magnitude(z1.value) > magnitude(z2.value);
}

bool_t index_comparator(c_coefficient_t z1, c_coefficient_t z2) {
    return z1.original_index < z2.original_index;
}

void complex_merge(c_coefficient_t *v, int start, int end) {
    c_coefficient_t *aux = (c_coefficient_t *)malloc((end - start + 1) * sizeof(c_coefficient_t));

    int c = (start + end) / 2;

    int i = start;
    int j = c + 1;
    int k = 0;

    while (i <= c && j <= end) {
        if (complex_comparator(v[i], v[j])) {
            aux[k].value = v[i].value;
            aux[k].original_index = v[i].original_index;

            i++;
        } else {
            aux[k].value = v[j].value;
            aux[k].original_index = v[j].original_index;

            j++;
        }

        k++;
    }

    while (i <= c) {
        aux[k].value = v[i].value;
        aux[k].original_index = v[i].original_index;

        i++;
        k++;
    }

    while (j <= end) {
        aux[k].value = v[j].value;
        aux[k].original_index = v[j].original_index;

        j++;
        k++;
    }

    for (i = start, k = 0; i <= end; i++, k++) {
        v[i].value = aux[k].value;
        v[i].original_index = aux[k].original_index;
    }

    free(aux);
}

void complex_mergesort(c_coefficient_t *v, int start, int end) {
    if (start == end) {
        return;
    }

    int c = (start + end) / 2;

    complex_mergesort(v, start, c);
    complex_mergesort(v, c + 1, end);

    complex_merge(v, start, end);
}

void index_merge(c_coefficient_t *v, int start, int end) {
    c_coefficient_t *aux = (c_coefficient_t *)malloc((end - start + 1) * sizeof(c_coefficient_t));

    int c = (start + end) / 2;

    int i = start;
    int j = c + 1;
    int k = 0;

    while (i <= c && j <= end) {
        if (index_comparator(v[i], v[j])) {
            aux[k].value = v[i].value;
            aux[k].original_index = v[i].original_index;

            i++;
        } else {
            aux[k].value = v[j].value;
            aux[k].original_index = v[j].original_index;

            j++;
        }

        k++;
    }

    while (i <= c) {
        aux[k].value = v[i].value;
        aux[k].original_index = v[i].original_index;

        i++;
        k++;
    }

    while (j <= end) {
        aux[k].value = v[j].value;
        aux[k].original_index = v[j].original_index;

        j++;
        k++;
    }

    for (i = start, k = 0; i <= end; i++, k++) {
        v[i].value = aux[k].value;
        v[i].original_index = aux[k].original_index;
    }

    free(aux);
}

void index_mergesort(c_coefficient_t *v, int start, int end) {
    if (start == end) {
        return;
    }

    int c = (start + end) / 2;

    index_mergesort(v, start, c);
    index_mergesort(v, c + 1, end);

    index_merge(v, start, end);
}
