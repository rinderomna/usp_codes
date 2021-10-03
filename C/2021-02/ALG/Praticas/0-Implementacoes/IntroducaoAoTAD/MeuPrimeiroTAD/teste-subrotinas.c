#include <stdio.h>

void d() {
    printf("D");
}

void c() {
    printf("C");
    d();
}

void b() {
    c();
    printf("B");
    d();
    c();
}

void a() {
    printf("A");
    c();
    b();
    d();
}

int main() {
    a();
    printf("\n");

    return 0;
}