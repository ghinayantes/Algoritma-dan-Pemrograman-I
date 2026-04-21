#include "jadwalnangor.h"

/* ********** KONSTRUKTOR ********** */
void CreateList(ListEkspedisi *L) {
    int i;
    L->nEff = 0;
    for(i = 0; i < CAPACITY; i++) {
        L->contents[i] = 0;
    }
}
/* I.S. L sembarang */
/* F.S. Terbentuk List L kosong dengan nEff = 0 */

/* ********** SELEKTOR ********** */
int length(ListEkspedisi L) {
    return L.nEff;
}
/* Mengirimkan banyaknya elemen efektif list */

/* ********** OPERASI UJUNG LIST ********** */
void insertFirst(ListEkspedisi *L, ElType x) {
    int i;
    for(i = length(*L); i > 0; i--) {
        L->contents[i] = L->contents[i-1];
    }
    L->contents[0] = x;
    L->nEff++;
}
/* I.S. L terdefinisi, mungkin kosong, tidak penuh. */
/* F.S. x disisipkan sebagai elemen pertama L. */
/* HINT: lakukan pergeseran */

void insertLast(ListEkspedisi *L, ElType x) {
    L->contents[length(*L)] = x;

    L->nEff++;
}
/* I.S. L terdefinisi, mungkin kosong, tidak penuh. */
/* F.S. x disisipkan sebagai elemen terakhir L. */

void deleteFirst(ListEkspedisi *L, ElType *e) {
    int i;
    *e = L->contents[0];
    for(i = 0; i < length(*L) - 1; i++) {
        L->contents[i] = L->contents[i+1];
    }
    L->contents[length(*L)] = 0;
    L->nEff--;
}
/* I.S. L terdefinisi, TIDAK kosong. */
/* F.S. Elemen pertama dihapus, nilainya disimpan ke *e. */
/* HINT: lakukan pergeseran */

void deleteLast(ListEkspedisi *L, ElType *e) {
    L->contents[length(*L)] = 0;
    L->nEff--;
}
/* I.S. L terdefinisi, TIDAK kosong. */
/* F.S. Elemen terakhir dihapus dan nilainya disimpan ke *e. */

/* ********** OPERASI TAMBAHAN ********** */
int TotalJarak(ListEkspedisi L) {
    int sum = 0, i;
    for(i = 0; i < length(L); i++) {
        sum += L.contents[i];
    }

    return sum;
}
/* Mengembalikan jumlah total nilai semua elemen di dalam List. Kembalikan 0 jika kosong. */


void printList(ListEkspedisi L) {
    int i;
    printf("[");
    for(i = 0; i < length(L)-1; i++) {
        printf("%d ", L.contents[i]);
    }
    printf("%d", L.contents[length(L)]);
    printf("]\n");
}
/* Mencetak isi list dengan format [x1,x2,...,xn] diakhiri newline (\n). */


/*int main() {
    ListEkspedisi L;
    ElType e;
    CreateList(&L);
    insertFirst(&L, 5);
    deleteFirst(&L, &e);
    L.nEff = 7;
    insertLast(&L, 100);

    printList(L);
} */