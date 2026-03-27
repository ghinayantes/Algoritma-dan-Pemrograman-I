/*
 * ============================================================
 *  SOAL 1 - BINARY SEARCH
 *  Binary search iteratif + hitung jumlah langkah
 * ============================================================
 *  Deskripsi:
 *    Binary search pada array integer yang sudah terurut
 *    secara ascending. Mencetak indeks ditemukan dan
 *    jumlah langkah perbandingan yang dilakukan.
 *
 *  Syarat: array HARUS sudah terurut ascending sebelum dicari.
 * ============================================================
 */

#include <stdio.h>

/* Binary search iteratif.
   Mengembalikan indeks nilai, atau -1 jika tidak ditemukan.
   Nilai 'langkah' diisi dengan jumlah perbandingan. */
int binarySearch(int arr[], int n, int target, int *langkah) {
    int low  = 0;
    int high = n - 1;
    *langkah = 0;

    while (low <= high) {
        int mid = low + (high - low) / 2;   /* hindari overflow */
        (*langkah)++;

        printf("  Langkah %d: low=%d, high=%d, mid=%d → arr[%d]=%d\n",
               *langkah, low, high, mid, mid, arr[mid]);

        if (arr[mid] == target) {
            return mid;             /* ditemukan */
        } else if (arr[mid] < target) {
            low = mid + 1;          /* cari di setengah kanan */
        } else {
            high = mid - 1;         /* cari di setengah kiri */
        }
    }
    return -1;  /* tidak ditemukan */
}

int main() {
    int arr[] = {2, 5, 8, 12, 16, 23, 38, 56, 72, 91};
    int n     = sizeof(arr) / sizeof(arr[0]);
    int target = 23;

    printf("Array  : ");
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) printf(", ");
    }
    printf("\n");
    printf("Dicari : %d\n\n", target);
    printf("Proses pencarian:\n");

    int langkah;
    int hasil = binarySearch(arr, n, target, &langkah);

    printf("\n");
    if (hasil != -1) {
        printf("Nilai %d ditemukan di indeks ke-%d\n", target, hasil);
        printf("Jumlah langkah perbandingan: %d\n", langkah);
    } else {
        printf("Nilai %d tidak ditemukan dalam array\n", target);
        printf("Jumlah langkah perbandingan: %d\n", langkah);
    }

    return 0;
}

/*
 * OUTPUT:
 *   Array  : 2, 5, 8, 12, 16, 23, 38, 56, 72, 91
 *   Dicari : 23
 *
 *   Proses pencarian:
 *     Langkah 1: low=0, high=9, mid=4 → arr[4]=16
 *     Langkah 2: low=5, high=9, mid=7 → arr[7]=56
 *     Langkah 3: low=5, high=6, mid=5 → arr[5]=23
 *
 *   Nilai 23 ditemukan di indeks ke-5
 *   Jumlah langkah perbandingan: 3
 */