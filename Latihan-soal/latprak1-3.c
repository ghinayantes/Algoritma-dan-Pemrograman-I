/*Deskripsi: Program menerima input sebuah karakter C dan sebuah integer N. 
Program harus mencetak karakter tersebut sebanyak N baris, di mana baris 
ke-i berisi karakter tersebut sebanyak i kali.*/

#include <stdio.h>

int main() {
    char C;
    int N, i;

    printf("Masukkan karakter: ");
    scanf("%c", &C);
    printf("Masukkan jumlah baris: ");
    scanf("%d", &N);

    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= i; j++) {
            printf("%c", C);
        }
        printf("\n");
    }
    return 0;
}