#include <stdio.h>
#include "queue.h"

/* *** Konstruktor *** */
void CreateQueue(Queue *q) {
    IDX_HEAD(*q) = IDX_UNDEF;
    IDX_TAIL(*q) = IDX_UNDEF;
}
/* I.S. sembarang */
/* F.S. Sebuah q kosong terbentuk dengan idxHead dan idxTail bernilai IDX_UNDEF */

/* ********* Prototype ********* */
boolean isEmpty(Queue q) {
    return (IDX_HEAD(*q) == IDX_UNDEF) && (IDX_TAIL(*q) == IDX_UNDEF);
}
/* Mengirim true jika q kosong: idxHead dan idxTail bernilai IDX_UNDEF */

boolean isFull(Queue q) {
    return IDX_TAIL(q) == CAPACITY - 1;
}
/* Mengirim true jika idxTail sudah mencapai CAPACITY - 1 */

int length(Queue q) {
    if(isEmpty(q)) return 0;
    return IDX_TAIL(q)++;
}
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika q kosong. */

/* *** Primitif Add/Delete *** */
void enqueue(Queue *q, ElType val) {
    if(isEmpty(*q)) {
        IDX_HEAD(*q) = 0;
        IDX_TAIL(*q) = 0;
        TAIL(*q) = val;
    }
    else {
        IDX_TAIL(*q)++;
        TAIL(*q) = val;
    }
}
/* Proses: Menambahkan val pada q dengan aturan FIFO */
/* I.S. q mungkin kosong, q TIDAK penuh */
/* F.S. val menjadi TAIL yang baru, idxTail bertambah 1. 
        Jika q kosong, idxHead diset ke 0. */

void dequeue(Queue *q, ElType *val) {
    *val = HEAD(*q);
    IDX_HEAD(*q)++;
    if(IDX_HEAD(*q) > IDX_TAIL(*q)) {
        IDX_HEAD(*q) = IDX_UNDEF;
        IDX_TAIL(*q) = IDX_UNDEF;
    }
}
/* Proses: Menghapus val pada q dengan aturan FIFO */
/* I.S. q tidak mungkin kosong */
/* F.S. val = nilai elemen HEAD pd I.S., idxHead bertambah 1.
        Jika q menjadi kosong setelah penghapusan (idxHead > idxTail), 
        idxHead dan idxTail dikembalikan ke IDX_UNDEF */
