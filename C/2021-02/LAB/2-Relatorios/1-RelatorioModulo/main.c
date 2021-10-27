#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void bubble_sort();
void insertion_sort();
void mergesort();

int main() {
    clock_t c1, c2, c3, c4, c5, c6;

    c1 = clock();
    bubble_sort();
    c2 = clock();

    c3 = clock();
    insertion_sort();
    c4 = clock();

    c5 = clock();
    mergesort();
    c6 = clock();

    double bubble_sort_time, insertion_sort_time, merge_sort_time;

    bubble_sort_time = (c2 - c1) / (double) CLOCKS_PER_SEC;
    insertion_sort_time = (c4 - c3) / (double) CLOCKS_PER_SEC;
    merge_sort_time = (c6 - c5) / (double) CLOCKS_PER_SEC;

    printf("\nBubble Sort Time: %lf\n", bubble_sort_time);
    printf("Insertion Sort Time: %lf\n", insertion_sort_time);
    printf("Mergesort Time: %lf\n", merge_sort_time);

    return EXIT_SUCCESS;
}
