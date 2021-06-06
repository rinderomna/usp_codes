#include <stdio.h>

int main(int argc, char *argv[]) {
    int n, m, p;
    int rep = 1;
    int rodada = 0;
    int tipo = 0;

    scanf("%i %i %i", &n, &m, &p);

    while (rodada < n) {
        for (int i = 1; i <= rep; i++) {
            if (rodada % m == p - 1 && rodada < n) {
                switch (tipo%3) {
                    case 0: 
                        if (rep == 1) {
                            printf("1 pinguim\n");
                        } else {
                            printf("%i pinguins\n", rep);
                        }
                        break;
                    case 1:
                        printf("no gelo\n");
                        break;
                    case 2:
                        printf("uhuu!\n");
                        break;
                } 
            }   
            rodada++; 
        }
        tipo++;

        if (tipo%3 == 0) {
            rep++;
        }
    }

    return 0;
}