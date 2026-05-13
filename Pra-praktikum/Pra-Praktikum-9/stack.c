#include <stdio.h>
#include "stack.h"

/*** Konstruktor/Kreator ***/
void CreateStack(Stack *s) {
    IDX_TOP(*s) = IDX_UNDEF;
}
/* I.S. Sembarang */
/* F.S. Membuat sebuah Stack s yang kosong berkapasitas CAPACITY */
/* jadi indeksnya antara 0..CAPACITY-1 */

/* Ciri stack kosong: idxTop bernilai IDX_UNDEF */
/********** Predikat Untuk test keadaan KOLEKSI **********/
boolean isEmpty(Stack s) {
    return IDX_TOP(s) == IDX_UNDEF;
}
/* Mengirim true jika Stack kosong: lihat definisi di atas */

boolean isFull(Stack s) {
    return IDX_TOP(s) == CAPACITY-1;
}
/* Mengirim true jika Stack penuh */

int length(Stack s) {
    return IDX_TOP(s) + 1;
}
/* Mengirim ukuran Stack s saat ini */

/*********** Menambahkan sebuah elemen ke Stack **********/
void push(Stack *s, ElType val) {
    if(isEmpty(*s)) {
        IDX_TOP(*s) = 0;
        TOP(*s) = val;
    }
    else if (isFull(*s)) return;
    else {
        IDX_TOP(*s)++;
        TOP(*s) = val;
    }
}
/* Menambahkan val sebagai elemen Stack s.
I.S. s mungkin kosong, tidak penuh
F.S. val menjadi TOP yang baru, TOP bertambah 1 */

/*********** Menghapus sebuah elemen Stack **********/
void pop(Stack *s, ElType *val) {
    *val = TOP(*s);
    IDX_TOP(*s)--;
}
/* Menghapus X dari Stack S.
I.S. S tidak mungkin kosong
F.S. X adalah nilai elemen TOP yang lama, TOP berkurang 1 */