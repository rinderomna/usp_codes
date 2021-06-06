#include <stdio.h>

int main(int argc, char *argv[]) {
    int dia;

    scanf("%d", &dia);

    printf("         Abril 2021         \n");
    printf(" Do  Se  Te  Qu  Qu  Se  Sa \n");
    printf("                ");
            
    for (int i = 1; i <= 30; i++) {
        if (i == dia) {
            printf("(%2d)", i);
        } else {
            printf(" %2d ", i);
        }

        if (i == 3 || i == 10 || i == 17 || i == 24 || i == 30) {
            printf("\n");
        }
    }

    return 0;
}
