/*
 * ============================================================
 *  SOAL 2 - LINEAR SEARCH
 *  Hitung frekuensi kemunculan nilai dalam array
 * ============================================================
 *  Deskripsi:
 *    Linear search yang tidak berhenti di penemuan pertama.
 *    Menelusuri seluruh array, mengumpulkan semua indeks
 *    kemunculan nilai, lalu mencetak indeks dan total frekuensi.
 * ============================================================
 */

#include <stdio.h>

#define MAX 100

/* Fungsi mencari semua kemunculan target.
   Menyimpan indeks ke array 'hasil', mengembalikan jumlah kemunculan. */
int linearSearchSemua(int arr[], int n, int target,
                      int hasil[], int maxHasil) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] == target && count < maxHasil) {
            hasil[count] = i;   /* simpan indeks ke array hasil */
            count++;
        }
    }
    return count;   /* total kemunculan */
}

int main() {
    int arr[]  = {4, 7, 2, 7, 9, 7, 1};
    int n      = sizeof(arr) / sizeof(arr[0]);
    int target = 7;

    int indeks[MAX];    /* tampung semua indeks kemunculan */

    printf("Array  : ");
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) printf(", ");
    }
    printf("\n");
    printf("Dicari : %d\n\n", target);

    int total = linearSearchSemua(arr, n, target, indeks, MAX);

    if (total > 0) {
        printf("Nilai %d ditemukan di indeks: ", target);
        for (int i = 0; i < total; i++) {
            printf("%d", indeks[i]);
            if (i < total - 1) printf(", ");
        }
        printf("\n");
        printf("Total kemunculan: %d\n", total);
    } else {
        printf("Nilai %d tidak ditemukan dalam array\n", target);
    }

    return 0;
}

/*
 * OUTPUT:
 *   Array  : 4, 7, 2, 7, 9, 7, 1
 *   Dicari : 7
 *
 *   Nilai 7 ditemukan di indeks: 1, 3, 5
 *   Total kemunculan: 3
 */