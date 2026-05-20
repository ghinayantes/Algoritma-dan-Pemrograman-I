#include <stdio.h>
#include "listberkait.h"
#include "listberkait.c"
#include "boolean.h"
/* linked list sorting*/

void findMax(List *l, ElType *val) {
    int idx = 0, idxMax = 0;
    Address p = *l;
    ElType max = INFO(*l);
    while(p != NULL) {
        if(max < INFO(p)) {
            max = INFO(p);
            idxMax = idx;
        }
        p = NEXT(p);
        idx++;
    }
    deleteAt(l, idxMax, &max);
    *val = max;
}

void sortList(List *l, boolean ascending) {
    int idx = 0, N = length(*l);
    ElType val;
    List hasil;
    CreateList(&hasil);
    while(idx < N) {
        findMax(l, &val);
        if(ascending) insertFirst(&hasil, val);
        else insertLast(&hasil, val);
        idx++;
    }
    *l = hasil;
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