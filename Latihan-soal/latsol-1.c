#include <stdio.h>

typedef struct {
    char nama[50]; // PAKAI ARRAY biar ada tempatnya
    int umur;
} orang;

int main() {
    orang user; // Variabel biasa

    printf("Nama: ");
    // PAKAI %s untuk kata, dan pakai TITIK (.)
    // Untuk array nama, tidak butuh & di depannya
    scanf("%s", user.nama); 

    printf("Umur: ");
    // PAKAI TITIK (.) dan tetap pakai & karena umur itu int
    scanf("%d", &user.umur);

    // Cetak dengan %s untuk nama
    printf("%s berumur %d tahun\n", user.nama, user.umur);

    return 0;
}