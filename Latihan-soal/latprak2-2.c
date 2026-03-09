#include <stdio.h>

void tukar(int *a, int *b) {
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void putar3(int *a, int *b, int *c) {
    tukar(a, c);
    tukar(a, b);
}

int main() {
    int a, b, c;

    printf("Masukkan nilai a, b, c: ");
    scanf("%d %d %d", &a, &b, &c);

    printf("Sebelum ditukar: %d %d %d\n", a, b, c);

    putar3(&a, &b, &c);

    printf("Setelah ditukar: %d %d %d\n", a, b, c);

    return 0;
}