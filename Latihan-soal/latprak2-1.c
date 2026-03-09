#include <stdio.h>

int pangkat(int basis, int eksponen) {
    int hasil = 1;
    int exp = 1;

    while(exp <= eksponen) {
        hasil *= basis;
        exp++;
    }
    return hasil;
}

int main() {
    int a, b;

    printf("Masukkan basis: ");
    scanf("%d", &a);

    printf("Masukkan eksponen: ");
    scanf("%d", &b);

    printf("%d", pangkat(a, b));

    return 0;
}