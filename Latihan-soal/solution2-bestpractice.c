#include <stdio.h>
#include "listberkait.h"
#include "listberkait.c"
#include "boolean.h"
/* linked list sorting*/

int findmax(List l) {
  int max = INFO(l);
  l = NEXT(l);
  while (l) {
    if (max < INFO(l)) max = INFO(l);
    l = NEXT(l);
  }
  return max;
}

int findmin(List l) {
  int min = INFO(l);
  l = NEXT(l);
  while (l) {
    if (min > INFO(l)) min = INFO(l);
    l = NEXT(l);
  }
  return min;
}

void sortList(List *l, boolean ascending) {
  List tmp;
  List curr = *l;
  int t;
  CreateList(&tmp);
  while (*l) {
    if (ascending) {
      int m = findmin(*l);
      deleteAt(l, indexOf(*l, m), &t);
      insertLast(&tmp, m);
    }
    else
    {
      int m = findmax(*l);
      deleteAt(l, indexOf(*l, m), &t);
      insertLast(&tmp, m);
    }
  }
  *l = tmp;
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