#include <stdio.h>
#include <stdlib.h>

#include "pilha.h"

int main() {
    pilha_t *p = create();

    for (int i = 0; i <= 1234; i++) {
        push(p, i);
    }

    int x;
    while (pop(p, &x) != FAIL) {
        printf("%d\n", x);
    }

    destroy(&p);

    return 0;
}