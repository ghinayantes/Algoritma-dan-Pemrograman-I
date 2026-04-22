#include <stdio.h>
#include "hiddenface.h"

/* ********** KONSTRUKTOR ********** */
void CreateFaces(HiddenFaces *f) {
    IdxType i;

    for(i = IDX_MIN; i < CAPACITY; i++) {
        ELMT(*f, i) = MARK;
    }
}
/* I.S. f sembarang */
/* F.S. Terbentuk list f kosong dengan semua elemen bernilai MARK */

/* ********** TEST KOSONG / PENUH ********** */
boolean isEmpty(HiddenFaces f) {
    IdxType i;
    int count = 0;
    for(i = IDX_MIN; i < CAPACITY; i++) {
        if(ELMT(f, i) != MARK) count++;
    }
    
    if(count > 0) return false;
    return true;
}
/* Mengirimkan true jika list kosong */

boolean isFull(HiddenFaces f) {
    IdxType i;
    int count = 0;
    if(ELMT(f, IDX_MIN) != MARK) {
        for(i = IDX_MIN + 1; i < CAPACITY; i++) {
            if(ELMT(f, i) == MARK) count++;
        }
    }
    else count++;

    return (count == 0);
}
/* Mengirimkan true jika list penuh */

/* ********** SELEKTOR ********** */
int length(HiddenFaces f) {
    IdxType i;
    int count = 0;

    for(i = IDX_MIN; i < CAPACITY; i++) {
        if(ELMT(f, i) != MARK) count++;
    }

    return count;
}
/* Mengirimkan banyaknya elemen efektif list */
/* Jika list kosong, mengembalikan 0 */

IdxType getFirstIdx(HiddenFaces f) {
     IdxType i;
    for (i = IDX_MIN; i < CAPACITY; i++) {
        if (ELMT(f, i) != MARK) return i;
    }
    return IDX_UNDEF;
}
/* Prekondisi : f tidak kosong */
/* Mengirimkan indeks elemen pertama */

IdxType getLastIdx(HiddenFaces f) {
    IdxType i;
    for(i = CAPACITY - 1 ; i >= IDX_MIN; i--) {
        if(ELMT(f,i) != MARK) return i;
    }

    return IDX_UNDEF;
}
/* Prekondisi : f tidak kosong */
/* Mengirimkan indeks elemen terakhir */

ElType getElmt(HiddenFaces f, IdxType i) {
    return ELMT(f, i);
}
/* Prekondisi : f tidak kosong */
/* Mengirimkan elemen list f yang ke-i */

void setElmt(HiddenFaces *f, IdxType i, ElType val) {
    ELMT(*f, i) = val;
}
/* Prekondisi : f tidak kosong */
/* Mengeset nilai elemen list yang ke-i sehingga bernilai val */

/* ********** TEST INDEKS ********** */
boolean isIdxValid(HiddenFaces f, IdxType i) {
    return (i >= IDX_MIN && i < CAPACITY);
}
/* Prekondisi : f tidak kosong */
/* Mengirimkan true jika i adalah indeks valid untuk container */

boolean isIdxEff(HiddenFaces f, IdxType i) {
    if(!isIdxValid(f,i)) return false;
    return (getElmt(f, i) != MARK);
}
/* Prekondisi : f tidak kosong */
/* Mengirimkan true jika i adalah indeks efektif dalam list */

/* ********** OPERASI PENAMBAHAN ELEMEN ********** */
void insertFirst(HiddenFaces *f, ElType val) {
    setElmt(f, getFirstIdx(*f)-1, val);
}
/* Prekondisi : f, val terdefinisi */
/* Menambahkan val sebagai elemen pertama */
/* Note: Dapat dipastikan ada ruang kosong sebelum elemen pertama */

void insertAt(HiddenFaces *f, ElType val, IdxType i) {
    IdxType last = getLastIdx(*f), j;

    for(j = last; j >= i; j--) {
        setElmt(*f, j+1, getElmt(*f,j));
    }
    setElmt(*f, i, val);
}
/* Prekondisi : f, val terdefinisi */
/* Menambahkan val di indeks tertentu */
/* Note: Dapat dipastikan ada ruang kosong sebelum elemen pertama dan setelah elemen terakhir */

void insertLast(HiddenFaces *f, ElType val) {
    IdxType last = getLastIdx(*f);
    setElmt(*f, last + 1, val);
}
/* Prekondisi : f, val terdefinisi */
/* Menambahkan val sebagai elemen terakhir */
/* Note: Dapat dipastikan ada ruang kosong setelah elemen terakhir */

/* ********** OPERASI PENGHAPUSAN ELEMEN ********** */
void deleteFirst(HiddenFaces *f, ElType *val) {
    *val = getElmt(*f, getFirstIdx(*f));
    IdxType first = getFirstIdx(*f);
    setElmt(*f, first, MARK);
}
/* Prekondisi : f tidak kosong */
/* Menghapus elemen pertama */

void deleteAt(HiddenFaces *f, ElType *val, IdxType i) {
    *val = getElmt(*f, i);
    IdxType j, last = getLastIdx(*f);
    for(j = i; j < getLastIdx(*f); j++) {
        setElmt(*f, j, getElmt(*f, j+1));
    }
    setElmt(*f, last, MARK);
}
/* Prekondisi : f tidak kosong */
/* Menghapus elemen di indeks tertentu */

void deleteLast(HiddenFaces *f, ElType *val) {
    *val = getElmt(*f, getLastIdx(*f));
    setElmt(*f, getLastIdx(*f), MARK);
}
/* Prekondisi : f tidak kosong */
/* Menghapus elemen terakhir */

/* ********** FUNGSI ANALISIS ********** */
void printAll(HiddenFaces f) {
    IdxType i;
    boolean first = true;
    printf("[");
    for(i = IDX_MIN; i < CAPACITY; i++) {
        if(ELMT(f, i) != MARK) {
            if(!first) printf(",");
            printf("'%c'", ELMT(f, i)); // Pakai %c untuk char
            first = false;
        }
    }
    printf("]\n");
}
/* Prekondisi : f terdefinisi */
/* Menampilkan semua elemen efektif dari list dalam format [x1,x2,...,xn] */
/* Contoh : */
/* ['a','b','c'] */
/* Jika kosong : []*/
/* Pastikan ada newline setelah list ditampilkan */

HiddenFaces concat(HiddenFaces f1, HiddenFaces f2) {
    HiddenFaces r;
    CreateFaces(&r);
    IdxType i, ir = 0;

    // Rata kiri f1
    for(i = IDX_MIN; i < CAPACITY; i++) {
        if(ELMT(f1, i) != MARK) {
            ELMT(r, ir) = ELMT(f1, i);
            ir++;
        }
    }
    // Lanjut rata kiri f2
    for(i = IDX_MIN; i < CAPACITY; i++) {
        if(ELMT(f2, i) != MARK) {
            if(ir < CAPACITY) {
                ELMT(r, ir) = ELMT(f2, i);
                ir++;
            }
        }
    }

    return r;
}
/* Prekondisi: f1 dan f2 terdefinisi, mungkin kosong. */
/* Mengembalikan hasil Konkatenasi dua buah list yang rata kiri, f2 ditaruh di belakang f1 */
