#include <stdio.h>

int faktorial(int n) {
    if(n > 1) return n * faktorial(n - 1);
    else return 1;
}

int kombinasi(int n, int r) {
    return faktorial(n) / (faktorial(r) * faktorial(n - r));
}

int permutasi(int n, int r) {
    return faktorial(n) / faktorial(n - r);
}

int main() {
    int n, r;

    printf("Masukkan nilai n: ");
    scanf("%d", &n);
    printf("Masukkan nilai r: ");
    scanf("%d", &r);

    printf("Hasil kombinasi: %d\n", kombinasi(n, r));
    printf("Hasil permutasi: %d\n", permutasi(n, r));

    return 0;
}