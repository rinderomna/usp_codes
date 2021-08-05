#include <stdio.h>

int main(int argc, char *argv[]) {
    int num_station;

    char *stations[10] = {
        "Morumbi",
        "Butanta",
        "Pinheiros",
        "Faria Lima",
        "Fradique Coutinho",
        "Oscar Freire",
        "Paulista",
        "Higienopolis-Mackenzie",
        "Republica",
        "Luz",
    };

    scanf("%i", &num_station);

    if(num_station <= 5) {
        for (int i = num_station; i <= 5; i++) {
            printf("* %s\n", stations[i]);
            if (i != 5) {
                printf("|\n");
            }
        }
    } else {
        for (int i = num_station; i <= 9; i++) {
            printf("* %s\n", stations[i]);
            if (i != 9) {
                printf("|\n");
            }
        }
    }

    return 0;
}
