#include <stdio.h>

int main() {
    int x, i, j, k, out;
    int count; 
    int countk;
    int total_width;

    if (scanf("%d", &x) != 1) return 0;

    total_width = 2 * (x - 1) + 1;

    // Bagian Daun/Segitiga 
    for (i = 1; i <= x - 1; i++) {
        for (out = i; out <= x; out++) {
            
            // 1. Hitung jumlah bintang: 2 * baris_saat_ini - 1
            count = 2 * out - 1;
            
            // 2. Hitung jumlah spasi agar center (total_width - bintang) / 2
            countk = (total_width - count) / 2;

            // Cetak spasi
            for (k = 1; k <= countk; k++) {
                printf(" ");
            }

            // Cetak bintang
            for (j = 1; j <= count; j++) {
                printf("*");
            }
            printf("\n");
        }
    }

    // Bagian Batang 
    int trunk_spaces = (total_width - 3) / 2;
    for (i = 0; i < x; i++) {
        for (k = 1; k <= trunk_spaces; k++) {
            printf(" ");
        }
        printf("***\n");
    }

    return 0;
}

