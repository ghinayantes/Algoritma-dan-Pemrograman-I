#include <stdio.h>
#include "listberkait.h"
#include "listberkait.c"
#include "boolean.h"

void reverseList(List *l) {
    if(isEmpty(*l) || NEXT(*l) == NULL) return;
    else {
        Address back = NULL;
        Address current = *l;
        Address front = NULL;
        while (current != NULL) {
            front = NEXT(current);  
            NEXT(current) = back;  
            back = current;
            current = front;
        }
        *l = back;
    }
}

int main() {
    List l;
    int n, i;
    ElType val;

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

    // 4. Menampilkan list sebelum di-reverse
    printf("\n=== SEBELUM REVERSE ===\n");
    displayList(l); //

    // 5. Memanggil prosedur reverse yang akan kamu uji
    reverseList(&l);

    // 6. Menampilkan list setelah di-reverse
    printf("\n=== SETELAH REVERSE ===\n");
    displayList(l); //

    return 0;
}