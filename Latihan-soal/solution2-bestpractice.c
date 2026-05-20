#include <stdio.h>
#include "listberkait.h"
#include "listberkait.c"
#include "boolean.h"
/* linked list sorting*/

void trueInPlaceSort(List l) {
    Address p = l;
    
    // Loop pertama berjalan dari depan ke belakang
    while (p != NULL) {
        Address q = NEXT(p);
        Address minMaxNode = p;
        
        // Loop kedua mencari nilai terkecil/terbesar di sisa list
        while (q != NULL) {
            if (INFO(q) < INFO(minMaxNode)) { // Tinggal ganti arah tanda untuk ascending/descending
                minMaxNode = q;
            }
            q = NEXT(q);
        }
        
        // JIKA ditemukan node yang lebih kecil, CUMA TUKAR INFO-NYA SAJA
        if (minMaxNode != p) {
            ElType temp = INFO(p);
            INFO(p) = INFO(minMaxNode);
            INFO(minMaxNode) = temp;
        }
        
        p = NEXT(p); // Maju ke gerbong berikutnya
    }
}

int main() {
    List l;
    int n, i;
    ElType val;
    int opt;
    boolean ascending;

    // 1. Inisialisasi list kosong
    CreateList(&l);

    // 2. Menerima input jumlah elemen
    printf("Masukkan jumlah elemen list: ");
    if (scanf("%d", &n) != 1 || n < 0) {
        printf("Jumlah elemen tidak valid.\n");
        return 0;
    }

    // 3. Menerima input data elemen list
    if (n > 0) {
        printf("Masukkan %d elemen list (pisahkan dengan spasi/enter):\n", n);
        for (i = 0; i < n; i++) {
            scanf("%d", &val);
            insertLast(&l, val); // Memasukkan data ke akhir list
        }
    }

    // 4. Menerima input pilihan mode sorting
    printf("Pilih mode pengurutan (1: Ascending [Menaik], 0: Descending [Menurun]): ");
    scanf("%d", &opt);
    ascending = (opt == 1) ? true : false;

    // 5. Menampilkan list sebelum di-sort
    printf("\n=== SEBELUM SORT ===\n");
    displayList(l);

    // 6. Memanggil prosedur sortList yang kamu buat
    sortList(&l, ascending);

    // 7. Menampilkan list setelah di-sort
    printf("\n=== SETELAH SORT ===\n");
    displayList(l);

    return 0;
}