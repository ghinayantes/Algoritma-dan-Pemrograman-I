#ifndef QUEUE_H
#define QUEUE_H
#include "boolean.h"

#define IDX_UNDEF -1
#define CAPACITY 100

typedef int ElType;

typedef struct {
    ElType buffer[CAPACITY];
    int idxHead;
    int idxTail;
} Queue;

/* ********* AKSESOR ********* */
#define IDX_HEAD(q) (q).idxHead
#define IDX_TAIL(q) (q).idxTail
#define     HEAD(q) (q).buffer[(q).idxHead]
#define     TAIL(q) (q).buffer[(q).idxTail]

/* *** Konstruktor *** */
void CreateQueue(Queue *q);
/* I.S. sembarang */
/* F.S. Sebuah q kosong terbentuk dengan idxHead dan idxTail bernilai IDX_UNDEF */

/* ********* Prototype ********* */
boolean isEmpty(Queue q);
/* Mengirim true jika q kosong: idxHead dan idxTail bernilai IDX_UNDEF */

boolean isFull(Queue q);
/* Mengirim true jika idxTail sudah mencapai CAPACITY - 1 */

int length(Queue q);
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika q kosong. */

/* *** Primitif Add/Delete *** */
void enqueue(Queue *q, ElType val);
/* Proses: Menambahkan val pada q dengan aturan FIFO */
/* I.S. q mungkin kosong, q TIDAK penuh */
/* F.S. val menjadi TAIL yang baru, idxTail bertambah 1. 
        Jika q kosong, idxHead diset ke 0. */

void dequeue(Queue *q, ElType *val);
/* Proses: Menghapus val pada q dengan aturan FIFO */
/* I.S. q tidak mungkin kosong */
/* F.S. val = nilai elemen HEAD pd I.S., idxHead bertambah 1.
        Jika q menjadi kosong setelah penghapusan (idxHead > idxTail), 
        idxHead dan idxTail dikembalikan ke IDX_UNDEF */

#endif