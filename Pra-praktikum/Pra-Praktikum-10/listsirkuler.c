#include <stdio.h>
#include <stdlib.h>
#include "listsirkuler.h"
#include "boolean.h"

/* PROTOTYPE */
/****************** TEST LIST KOSONG ******************/
boolean isEmpty(List l) {
    return FIRST(l) == NULL;
}
/* Mengirim true jika list kosong. Lihat definisi di atas. */

/****************** PEMBUATAN LIST KOSONG ******************/
void CreateList(List *l) {
    FIRST(*l) = NULL;
}
/* I.S. l sembarang             */
/* F.S. Terbentuk list kosong. Lihat definisi di atas. */

/****************** Manajemen Memori ******************/
Address allocate(ElType val) {
    Address p = (Address)malloc(sizeof(ElmtList));
    if(p != NULL) {
        INFO(p) = val;
        NEXT(p) = NULL;
    }
    return p;
}
/* Mengirimkan Address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka Address tidak NULL, dan misalnya */
/* menghasilkan P, maka INFO(P)=val, NEXT(P)=NULL */
/* Jika alokasi gagal, mengirimkan NULL */

void deallocate(Address P) {
    NEXT(P) = NULL;
    free(P);
}
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian Address P */

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void insertFirst(List *l, ElType val) {
    Address p = allocate(val);
    if(p != NULL) {
        if(isEmpty(*l)) {
            NEXT(p) = p; 
            FIRST(*l) = p;
        }
        else {
            NEXT(p) = FIRST(*l);
            Address last = FIRST(*l);
            while(NEXT(last) != FIRST(*l)) {
            last = NEXT(last);
            }
            NEXT(last) = p;
            FIRST(*l) = p;
        }
    }
}
/* I.S. l mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai val jika alokasi berhasil */

void insertLast(List *l, ElType val) {
    if(FIRST(*l) == NULL) insertFirst(l, val);
    else {
        Address p = allocate(val);
        if(p != NULL) {
            Address elmt = FIRST(*l);
            while(NEXT(elmt) != FIRST(*l)) elmt = NEXT(elmt);
            NEXT(elmt) = p;
            NEXT(p) = FIRST(*l);
        }
    }
}
/* I.S. l mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai val jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */

/*** PENGHAPUSAN ELEMEN ***/
void deleteFirst(List *l, ElType *val) {
    Address p = FIRST(*l);
    *val = INFO(p);
    if(NEXT(p) == FIRST(*l)) {
        FIRST(*l) = NULL;
        deallocate(p);
    }
    else {
        Address sambungan = p;
        while(NEXT(sambungan) != p) {
            sambungan = NEXT(sambungan);
        }
        FIRST(*l) = NEXT(p);
        NEXT(sambungan) = FIRST(*l);
        deallocate(p);
    }
}
/* I.S. List l tidak kosong  */
/* F.S. val adalah elemen pertama list l sebelum penghapusan */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/*      First element yg baru adalah suksesor elemen pertama yang lama */
/*      Alamat elemen terakhir di-dealokasi */

/****************** PROSES SEMUA ELEMEN LIST ******************/
void displayList(List l) {
    if(isEmpty(l)) printf("[]");
    else {
        Address p = FIRST(l);
        printf("[");
        do {
            printf("%d", INFO(p));
            p = NEXT(p);
            if(p != FIRST(l)) {
                printf(",");
            }
        } while(p != FIRST(l));
        printf("]");
    }
}
/* I.S. List mungkin kosong */
/* F.S. Jika list tidak kosong, iai list dicetak ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika list kosong : menulis [] */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */
