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

typedef enum comparator_type {
    COMPLEX,
    INDEX
} comparator_type_t;

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
 * @param fname (char *): name of/path to the wav file to be read.
 * @param dataSize (int *): reference to an integer variable that will store the
 * number of samples in the audio file read. 
 * @return (unsigned char *): pointer to the first byte of a dinamically allocated
 * vector of audio samples, which are unsigned 8 bits integers, from 0 to 255.
 */
unsigned char *read_wav_data(char *fname, int *dataSize);

/* |DFT|
 * Performs a Discrete Fourrier Transform in the audio samples vector. outputting
 * a dinamically allocated vector of complex coefficients.
 * 
 * @param audio (unsigned char *): audio samples vector.
 * @param length (int): number of samples in the audio samples vector. 
 * @return (c_coefficients_t *): pointer to the first byte of a dinamically allocated
 * vector of complex coefficients.
 */
c_coefficient_t *DFT(unsigned char *audio, int length);

/* |inverse_DFT|
 * Performs an Inverse Discrete Fourrier Transform in a complex coeffiecients vector,
 * outputting an audio samples vector.
 * 
 * @param complex_coefficients (c_coefficients_t *): complex coefficients vector.
 * @param length (int): number of samples in the complex coefficients vector. 
 * @return (unsigned char *): pointer to the first byte of a dinamically allocated
 * vector of audio samples.
 */
unsigned char *inverse_DFT(c_coefficient_t *complex_coefficients, int length);

/* |magnitude|
 * Evaluates the magnitude of a complex number.
 * 
 * @param z (double complex): complex number whose magnitude will be evaluated.
 * @return (double): complex number magnitude.
 */
double magnitude(double complex z);

/* |count_negatives|
 * Counts the number os complex coefficients with both real and imaginary parts
 * less than or equal to zero.
 * 
 * @param complex_coefficients (c_coefficients_t *): complex coefficients vector.
 * @param length (int): number of samples in the complex coefficients vector. 
 * @return (int): number of complex coefficients with both real and imaginary parts 
 * less than or equal to zero.
 */
int count_negatives(c_coefficient_t *complex_coefficients, int length);

/* |complex_comparator|
 * Compares 2 complex coefficients by their complex values, returning true if the first
 * is greater than the second.
 *
 * @param z1 (c_coefficient_t): first complex coefficient.
 * @param z2 (c_coefficient_t): second complex coefficient.
 * @return (bool_t): true if the first complex coefficient value is greater than the 
 * second's..
 */
bool_t complex_comparator(c_coefficient_t z1, c_coefficient_t z2);

/* |index_comparator|
 * Compares 2 complex coefficients by their original indexes, returning true if the first
 * is less than the second.
 *
 * @param z1 (c_coefficient_t): first complex coefficient.
 * @param z2 (c_coefficient_t): second complex coefficient.
 * @return (bool_t): true if the first complex coefficient original index is less than the 
 * second's.
 */
bool_t index_comparator(c_coefficient_t z1, c_coefficient_t z2);

/* |merge|
 * Performs the merge step of a mergesort algorithm using the passed comparator type.
 * 
 * @param v (c_coefficient_t *): complex cofficients vector.
 * @param start (int): first index of merge region.
 * @param end (int): last index of merge region.
 * @param ctype (comparator_type_t): comparator type used to merge.
 * 
 */
void merge(c_coefficient_t *v, int start, int end, comparator_type_t ctype);

void mergesort(c_coefficient_t *v, int start, int end, comparator_type_t ctype);

int main() {
    string_t audio_file_name = read_line(stdin);

    int T = 0;
    scanf(" %d", &T);

    int data_size = 0;
    unsigned char *samples = read_wav_data((char *)audio_file_name, &data_size);

    c_coefficient_t *complex_coefficients = DFT(samples, data_size);

    int n_negatives = count_negatives(complex_coefficients, data_size);

    mergesort(complex_coefficients, 0, data_size - 1);

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

void merge(c_coefficient_t *v, int start, int end, comparator_type_t ctype) {
    c_coefficient_t *aux = (c_coefficient_t *)malloc((end - start + 1) * sizeof(c_coefficient_t));

    int c = (start + end) / 2;

    int i = start;
    int j = c + 1;
    int k = 0;

    while (i <= c && j <= end) {
        if (complex_comparator(v[i], v[j]) && ctype == COMPLEX ||
            index_comparator(v[i], v[j]) && ctype == INDEX) {
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

void mergesort(c_coefficient_t *v, int start, int end, comparator_type_t ctype) {
    if (start == end) {
        return;
    }

    int c = (start + end) / 2;

    mergesort(v, start, c, ctype);
    mergesort(v, c + 1, end, ctype);

    merge(v, start, end, ctype);
}