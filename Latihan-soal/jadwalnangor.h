#ifndef JADWALNANGOR_H
#define JADWALNANGOR_H

#include <stdio.h>

#define CAPACITY 100

typedef int ElType;
typedef struct {
    ElType contents[CAPACITY];
    int nEff;
} ListEkspedisi;

/* ********** KONSTRUKTOR ********** */
void CreateList(ListEkspedisi *L);
/* I.S. L sembarang */
/* F.S. Terbentuk List L kosong dengan nEff = 0 */

/* ********** SELEKTOR ********** */
int length(ListEkspedisi L);
/* Mengirimkan banyaknya elemen efektif list */

/* ********** OPERASI UJUNG LIST ********** */
void insertFirst(ListEkspedisi *L, ElType x);
/* I.S. L terdefinisi, mungkin kosong, tidak penuh. */
/* F.S. x disisipkan sebagai elemen pertama L. */
/* HINT: lakukan pergeseran */

void insertLast(ListEkspedisi *L, ElType x);
/* I.S. L terdefinisi, mungkin kosong, tidak penuh. */
/* F.S. x disisipkan sebagai elemen terakhir L. */

void deleteFirst(ListEkspedisi *L, ElType *e);
/* I.S. L terdefinisi, TIDAK kosong. */
/* F.S. Elemen pertama dihapus, nilainya disimpan ke *e. */
/* HINT: lakukan pergeseran */

void deleteLast(ListEkspedisi *L, ElType *e);
/* I.S. L terdefinisi, TIDAK kosong. */
/* F.S. Elemen terakhir dihapus dan nilainya disimpan ke *e. */

/* ********** OPERASI TAMBAHAN ********** */
int TotalJarak(ListEkspedisi L);
/* Mengembalikan jumlah total nilai semua elemen di dalam List. Kembalikan 0 jika kosong. */

void printList(ListEkspedisi L);
/* Mencetak isi list dengan format [x1,x2,...,xn] diakhiri newline (\n). */

#endif