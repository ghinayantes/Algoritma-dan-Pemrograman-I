/*
 * ============================================================
 *  SOAL 3 - BINARY SEARCH
 *  Input pengguna + bubble sort otomatis + binary search
 * ============================================================
 *  Deskripsi:
 *    Program interaktif: pengguna memasukkan sejumlah angka
 *    sembarang (belum terurut). Program otomatis mengurutkan
 *    dengan bubble sort, lalu menerapkan binary search untuk
 *    nilai yang dicari pengguna.
 *    Menampilkan array sebelum dan sesudah pengurutan.
 * ============================================================
 */

#include <stdio.h>

#define MAKS 100

/* Urutkan array secara ascending menggunakan bubble sort */
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                /* tukar posisi dua elemen yang terbalik */
                int tmp    = arr[j];
                arr[j]     = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
}

/* Binary search iteratif pada array terurut.
   Mengembalikan indeks jika ditemukan, -1 jika tidak. */
int binarySearch(int arr[], int n, int target) {
    int low  = 0;
    int high = n - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

/* Cetak seluruh isi array ke layar */
void cetakArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) printf(", ");
    }
    printf("\n");
}

int main() {
    int arr[MAKS];
    int n;

    printf("Masukkan jumlah elemen (maks %d): ", MAKS);
    scanf("%d", &n);

    if (n <= 0 || n > MAKS) {
        printf("Jumlah elemen tidak valid.\n");
        return 1;
    }

    printf("Masukkan %d angka:\n", n);
    for (int i = 0; i < n; i++) {
        printf("  arr[%d] = ", i);
        scanf("%d", &arr[i]);
    }

    printf("\nArray asli    : ");
    cetakArray(arr, n);

    /* Urutkan dengan bubble sort sebelum binary search */
    bubbleSort(arr, n);

    printf("Array terurut : ");
    cetakArray(arr, n);

    int target;
    printf("\nMasukkan nilai yang dicari: ");
    scanf("%d", &target);

    int hasil = binarySearch(arr, n, target);

    printf("\n");
    if (hasil != -1) {
        printf("Nilai %d ditemukan di indeks ke-%d (array terurut)\n",
               target, hasil);
    } else {
        printf("Nilai %d tidak ditemukan dalam array\n", target);
    }

    printf("\nCatatan: indeks yang ditampilkan merujuk pada\n");
    printf("posisi di array yang SUDAH diurutkan.\n");

    return 0;
}

/*
 * CONTOH OUTPUT (input: 45 12 78 3 29 60, cari 29):
 *
 *   Masukkan jumlah elemen (maks 100): 6
 *   Masukkan 6 angka:
 *     arr[0] = 45
 *     arr[1] = 12
 *     arr[2] = 78
 *     arr[3] = 3
 *     arr[4] = 29
 *     arr[5] = 60
 *
 *   Array asli    : 45, 12, 78, 3, 29, 60
 *   Array terurut : 3, 12, 29, 45, 60, 78
 *
 *   Masukkan nilai yang dicari: 29
 *
 *   Nilai 29 ditemukan di indeks ke-2 (array terurut)
 *
 *   Catatan: indeks yang ditampilkan merujuk pada
 *   posisi di array yang SUDAH diurutkan.
 */