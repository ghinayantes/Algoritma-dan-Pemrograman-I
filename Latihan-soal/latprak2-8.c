#include <stdio.h>

int isSegitigaValid(int a, int b, int c) {
    if((a + b > c) && (b + c > a) && (a + c > b)) return 1;
    else return 0;
}

int jenisSegitiga(int a, int b, int c) {
    int jenis = 2;
    if(a == b && b == c) jenis = 0;
    else if (a == b || b == c || a == c) jenis = 1;
    return jenis;
}

void bacaSisi(int *a, int *b, int *c) {
    do {
        printf("Masukkan sisi segitiga (a b c): ");
        scanf("%d %d %d", a, b, c);
        if(!(isSegitigaValid(*a, *b, *c)) || *a <= 0 || *b <= 0 || *c <= 0) printf("Sisi tidak valid, coba lagi!\n");
    } while(!(isSegitigaValid(*a, *b, *c)) || (*a <= 0 || *b <= 0 || *c <= 0));
}

void cetakJenis(int jenis) {
    if(jenis == 0) printf("Segitiga tersebut sama sisi");
    else if (jenis == 1) printf("Segitiga tersebut sama kaki");
    else printf("Segitiga tersebut sembarang");
}

int main() {
    int a, b, c;
    bacaSisi(&a, &b, &c);
    cetakJenis(jenisSegitiga(a, b, c));

    return 0;
}