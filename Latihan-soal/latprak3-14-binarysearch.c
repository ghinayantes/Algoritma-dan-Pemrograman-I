/*
 * ============================================================
 *  SOAL 2 - BINARY SEARCH
 *  Binary search rekursif + jejak setiap pemanggilan
 * ============================================================
 *  Deskripsi:
 *    Implementasi binary search secara rekursif.
 *    Setiap pemanggilan rekursif mencetak nilai low, high,
 *    dan mid untuk melacak proses pencarian secara detail.
 *
 *  Syarat: array HARUS sudah terurut ascending sebelum dicari.
 * ============================================================
 */

#include <stdio.h>

/* Binary search rekursif.
   Mengembalikan indeks jika ditemukan, -1 jika tidak. */
int binarySearchRekursif(int arr[], int low, int high,
                         int target, int *langkah) {
    /* base case: rentang habis, nilai tidak ada */
    if (low > high) {
        return -1;
    }

    int mid = low + (high - low) / 2;
    (*langkah)++;

    printf("  Langkah %d: low=%d, high=%d, mid=%d → arr[%d]=%d\n",
           *langkah, low, high, mid, mid, arr[mid]);

    if (arr[mid] == target) {
        return mid;                 /* nilai ditemukan */
    } else if (arr[mid] < target) {
        /* nilai ada di sebelah kanan mid */
        return binarySearchRekursif(arr, mid + 1, high, target, langkah);
    } else {
        /* nilai ada di sebelah kiri mid */
        return binarySearchRekursif(arr, low, mid - 1, target, langkah);
    }
}

int main() {
    int arr[] = {1, 3, 7, 14, 21, 35, 50, 68};
    int n     = sizeof(arr) / sizeof(arr[0]);
    int target = 14;

    printf("Array  : ");
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) printf(", ");
    }
    printf("\n");
    printf("Dicari : %d\n\n", target);
    printf("Proses rekursif:\n");

    int langkah = 0;
    int hasil   = binarySearchRekursif(arr, 0, n - 1, target, &langkah);

    printf("\n");
    if (hasil != -1) {
        printf("Nilai %d ditemukan di indeks ke-%d\n", target, hasil);
        printf("Jumlah pemanggilan rekursif: %d\n", langkah);
    } else {
        printf("Nilai %d tidak ditemukan dalam array\n", target);
        printf("Jumlah pemanggilan rekursif: %d\n", langkah);
    }

    return 0;
}

/*
 * OUTPUT:
 *   Array  : 1, 3, 7, 14, 21, 35, 50, 68
 *   Dicari : 14
 *
 *   Proses rekursif:
 *     Langkah 1: low=0, high=7, mid=3 → arr[3]=14
 *
 *   Nilai 14 ditemukan di indeks ke-3
 *   Jumlah pemanggilan rekursif: 1
 */