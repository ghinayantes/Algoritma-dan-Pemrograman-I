#include <stdio.h>
#include <stdlib.h>
#include "listberkait.h"
#include "boolean.h"

/****************** MANAJEMEN MEMORI ******************/
Address newNode(ElType val) {
    Address p = (Address)malloc(sizeof(Node));
    if(p != NULL) {
        INFO(p) = val;
        NEXT(p) = NULL;
    }
    return p;
}
/* Mengembalikan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak NULL, dan misalnya */
/* menghasilkan p, maka INFO(p)=val, NEXT(p)=NULL */
/* Jika alokasi gagal, mengirimkan NULL (alokasi gagal jika malloc mengembalikan null) */
/* Catatan: Praktikan WAJIB mengimplementasikan fungsi ini. */

/* PROTOTYPE */
/****************** PEMBUATAN LIST KOSONG ******************/
void CreateList(List *l) {
    FIRST(*l) = NULL;
}
/* I.S. sembarang             */
/* F.S. Terbentuk list kosong */

/****************** TEST LIST KOSONG ******************/
boolean isEmpty(List l) {
    return FIRST(l) == NULL;
}
/* Mengembalikan true jika list kosong */

/****************** GETTER SETTER ******************/
ElType getElmt(List l, int idx) {
    int ctr = 0;
    Address p = l;
    while(ctr < idx) {
        p = NEXT(p);
        ctr++;
    }
    return INFO(p);
}
/* I.S. l terdefinisi, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. Mengembalikan nilai elemen l pada indeks idx */

void setElmt(List *l, int idx, ElType val) {
    int ctr = 0;
    Address p = *l;
    while(ctr < idx) {
        p = NEXT(p);
        ctr++;
    }
    INFO(p) = val;
}
/* I.S. l terdefinisi, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. Mengubah elemen l pada indeks ke-idx menjadi val */

int indexOf(List l, ElType val) {
    boolean found = false;
    int idx = 0;
    Address p = l;
    while(p != NULL && !found) {
        if(INFO(p) == val) found = true;
        else {
            p = NEXT(p);
            idx++;
        }
    }
    if(!found) return IDX_UNDEF;
    return idx;
}
/* I.S. l, val terdefinisi */
/* F.S. Mencari apakah ada elemen list l yang bernilai val */
/* Jika ada, mengembalikan indeks elemen pertama l yang bernilai val */
/* Mengembalikan IDX_UNDEF jika tidak ditemukan */

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void insertFirst(List *l, ElType val) {
    Address p = newNode(val);
    if(p != NULL) { 
        NEXT(p) = *l; 
        *l = p;       
    }
}
/* I.S. l mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai val. */

void insertLast(List *l, ElType val) {
    if(isEmpty(*l)) insertFirst(l, val);
    else {
        Address last = newNode(val);
        if (last != NULL) {
            Address p = *l;
            while (NEXT(p) != NULL) p = NEXT(p);
            NEXT(p) = last;
        }
    }
}
/* I.S. l mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai val. */

void insertAt(List *l, ElType val, int idx) {
    if(idx == 0) insertFirst(l, val);
    else if(idx == length(*l)) insertLast(l, val);
    else {
        Address elmt = newNode(val);
        if(elmt != NULL) {
            int ctr = 0;
            Address p = *l;
            while(ctr < idx-1) {
                p = NEXT(p);
                ctr++;
            }
            Address sambungan = NEXT(p);
            NEXT(p) = elmt;
            NEXT(elmt) = sambungan;
        }
    }
}
/* I.S. l tidak mungkin kosong, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menyisipkan elemen dalam list pada indeks ke-idx (bukan menimpa elemen di i) */
/* yang bernilai val. */

/*** PENGHAPUSAN ELEMEN ***/
void deleteFirst(List *l, ElType *val) {
    Address p = *l;
    *val = INFO(p);
    *l = NEXT(p); 
    free(p);
}
/* I.S. List l tidak kosong  */
/* F.S. Elemen pertama list dihapus: nilai info disimpan pada val */
/* dan alamat elemen pertama di-dealokasi */

void deleteLast(List *l, ElType *val) {
    if(NEXT(*l) == NULL) deleteFirst(l, val);
    else {
        Address p = *l;
        Address loc = NULL;
        while(NEXT(p) != NULL) {
            loc = p;
            p = NEXT(p);
        }
        *val = INFO(p);
        NEXT(loc) = NULL;
        free(p);
    }
}
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai info disimpan pada val */
/* dan alamat elemen terakhir di-dealokasi */

void deleteAt(List *l, int idx, ElType *val) {
    int ctr = 0;
    if(idx == 0) deleteFirst(l, val);
    else {
        Address p = *l;
        while(ctr < idx-1) {
            p = NEXT(p); 
            ctr++;       
        }
        Address target = NEXT(p); 
        *val = INFO(target); 
        NEXT(p) = NEXT(target); 
        free(target); 
    }
}
/* I.S. list tidak kosong, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. val diset dengan elemen l pada indeks ke-idx. */
/* Elemen l pada indeks ke-idx dihapus dari l */

/****************** PROSES SEMUA ELEMEN LIST ******************/
void displayList(List l) {
    if(isEmpty(l)) printf("[]");
    else {
        Address p = NEXT(l);
        printf("[%d", INFO(l));
        while(p != NULL) {
            printf(",%d", INFO(p));
            p = NEXT(p);
        }
        printf("]");
    }
}
/* I.S. List mungkin kosong */
/* F.S. Jika list tidak kosong, isi list dicetak ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika list kosong : [] */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */

int length(List l) {
    int ctr = 0;
    Address p = l;
    while(p != NULL) {
        ctr++;
        p = NEXT(p);
    }
    return ctr;
}
/* Mengembalikan banyaknya elemen list; mengembalikan 0 jika list kosong */

/****************** PROSES TERHADAP LIST ******************/
List concat(List l1, List l2) {
    List l3;
    CreateList(&l3); 
    Address p = l1; 
    while (p != NULL) {
        insertLast(&l3, INFO(p)); 
        p = NEXT(p);              
    }
    p = l2; 
    while (p != NULL) {
        insertLast(&l3, INFO(p)); 
        p = NEXT(p);              
    }
    l1 = NULL;
    l2 = NULL;

    return l3;
}
/* I.S. l1 dan l2 sembarang */
/* F.S. l1 dan l2 kosong, l3 adalah hasil konkatenasi l1 & l2 */
/* Konkatenasi dua buah list : l1 dan l2    */
/* menghasilkan l3 yang baru (dengan elemen list l1 dan l2 secara beurutan). */