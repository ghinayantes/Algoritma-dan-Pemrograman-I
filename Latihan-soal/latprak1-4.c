/*Deskripsi: Baca sebuah integer N. 
Validasi harus N > 1. Tentukan apakah N adalah bilangan prima.*/

#include <stdio.h>

int main() {
    int N, i;

    printf("Masukkan bilangan: ");
    scanf("%d", &N);

    while (N <= 1) {
        printf("Bilangan harus lebih besar dari 1!\n");
        scanf("%d", &N);
    }
    for(i = 1; i <= N )
}