/*
 * ============================================================
 *  SOAL 3 - LINEAR SEARCH
 *  Cari nama dalam array string (case-insensitive)
 * ============================================================
 *  Deskripsi:
 *    Menyimpan daftar nama dalam array of string, lalu
 *    mencari nama menggunakan linear search tanpa
 *    membedakan huruf besar/kecil (case-insensitive).
 * ============================================================
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAKS_NAMA   50
#define MAKS_DATA   10

/* Ubah seluruh karakter string menjadi huruf kecil (lowercase).
   Hasil disimpan ke buffer 'out'. */
void toLowerStr(const char *src, char *out) {
    int i = 0;
    while (src[i] != '\0') {
        out[i] = (char)tolower((unsigned char)src[i]);
        i++;
    }
    out[i] = '\0';
}

/* Mencari nama secara case-insensitive.
   Mengembalikan indeks jika ditemukan, -1 jika tidak. */
int cariNama(char daftar[][MAKS_NAMA], int n, const char *target) {
    char targetKecil[MAKS_NAMA];
    char itemKecil[MAKS_NAMA];

    toLowerStr(target, targetKecil);

    for (int i = 0; i < n; i++) {
        toLowerStr(daftar[i], itemKecil);
        if (strcmp(itemKecil, targetKecil) == 0) {
            return i;   /* nama ditemukan */
        }
    }
    return -1;
}

int main() {
    char daftar[MAKS_DATA][MAKS_NAMA] = {
        "Andi", "Budi", "Citra", "Dian", "Eko"
    };
    int n = 5;
    char target[] = "citra";

    printf("Daftar nama : ");
    for (int i = 0; i < n; i++) {
        printf("%s", daftar[i]);
        if (i < n - 1) printf(", ");
    }
    printf("\n");
    printf("Dicari      : \"%s\"\n\n", target);

    int hasil = cariNama(daftar, n, target);

    if (hasil != -1) {
        printf("Nama \"%s\" ditemukan: %s (indeks ke-%d)\n",
               target, daftar[hasil], hasil);
    } else {
        printf("Nama \"%s\" tidak ditemukan dalam daftar\n", target);
    }

    return 0;
}

/*
 * OUTPUT:
 *   Daftar nama : Andi, Budi, Citra, Dian, Eko
 *   Dicari      : "citra"
 *
 *   Nama "citra" ditemukan: Citra (indeks ke-2)
 */