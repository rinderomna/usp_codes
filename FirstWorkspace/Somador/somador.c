#include <stdio.h>
int main() {
    int n1, n2, n3, n4, soma;
    printf("Entre 4 numeros a serem somados:\n");
    scanf("%d %d %d %d%*c",&n1,&n2,&n3,&n4);
    soma = n1 + n2 + n3 + n4;
    printf("soma = %d\n",soma);
    return 0;
} 