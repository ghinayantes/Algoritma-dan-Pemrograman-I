/*
 * ============================================================
 *  SOAL 1 - LINEAR SEARCH
 *  Cari nilai pertama dalam array integer
 * ============================================================
 *  Deskripsi:
 *    Mencari sebuah nilai integer dalam array menggunakan
 *    linear search. Mencetak indeks pertama ditemukan,
 *    atau pesan "tidak ditemukan" jika tidak ada.
 * ============================================================
 */

#include <stdio.h>

/* Fungsi linear search — mengembalikan indeks pertama nilai
   ditemukan, atau -1 jika tidak ada */
int linearSearch(int arr[], int n, int target) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == target) {
            return i;   /* langsung kembalikan indeks pertama */
        }
    }
    return -1;          /* nilai tidak ditemukan */
}

int main() {
    int arr[] = {10, 25, 3, 47, 8, 25, 99};
    int n     = sizeof(arr) / sizeof(arr[0]);
    int target = 25;

    printf("Array  : ");
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) printf(", ");
    }
    printf("\n");
    printf("Dicari : %d\n\n", target);

    int hasil = linearSearch(arr, n, target);

    if (hasil != -1) {
        printf("Nilai %d ditemukan di indeks ke-%d\n", target, hasil);
    } else {
        printf("Nilai %d tidak ditemukan dalam array\n", target);
    }

    return 0;
}

/*
 * OUTPUT:
 *   Array  : 10, 25, 3, 47, 8, 25, 99
 *   Dicari : 25
 *
 *   Nilai 25 ditemukan di indeks ke-1
 */