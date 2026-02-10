#include <stdio.h>

int v, t, hasil;

void jarak() {
    hasil = v * t;
}

int main() {
    printf("Masukkan kecepatan (km/jam): ");
    scanf("%d", &v);

    printf("Masukkan waktu (jam): ");
    scanf("%d", &t);

    jarak();

    printf("Besar jarak yang ditempuh: %d km", hasil); 
}