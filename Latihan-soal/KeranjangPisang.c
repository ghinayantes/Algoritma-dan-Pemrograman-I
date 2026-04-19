#include <stdio.h>
#include "KeranjangPisang.h"

/* ********** KONSTRUKTOR ********** */
void CreateKeranjang(KeranjangPisang *k) {
    IdxType i;
    for(i = IDX_MIN; i < CAPACITY; i++) {
        ELMT(*k, i) = MARK;
    }
}
/* I.S. k sembarang */
/* F.S. Terbentuk keranjang kosong dengan semua elemen bernilai MARK */

/* ********** SELEKTOR TAMBAHAN ********** */
int lengthKeranjang(KeranjangPisang k) {
    IdxType i = IDX_MIN;
    int count = 0; 

    while (i < CAPACITY && ELMT(k, i) != MARK) {
        count++;
        i++;
    }
    return count;
}
/* Mengirimkan banyaknya elemen efektif keranjang */

IdxType getFirstIdx(KeranjangPisang k) {
    return IDX_MIN;
}
/* Prekondisi : k tidak kosong */
/* Mengirimkan indeks elemen pertama */

IdxType getLastIdx(KeranjangPisang k) {
    return lengthKeranjang(k) - 1;
}
/* Prekondisi : k tidak kosong */
/* Mengirimkan indeks elemen terakhir */

boolean isIdxValid(KeranjangPisang k, IdxType i) {
    return i >= 0 && i < CAPACITY;
}
/* Mengirimkan true jika i adalah indeks valid untuk container */

boolean isIdxEff(KeranjangPisang k, IdxType i) {
    return isIdxValid(k, i) && ELMT(k, i) != MARK;
}
/* Mengirimkan true jika i adalah indeks efektif dalam keranjang */

boolean isEmpty(KeranjangPisang k) {
    return ELMT(k, IDX_MIN) == MARK;
}
/* Mengirimkan true jika keranjang kosong */

boolean isFull(KeranjangPisang k) {
    return ELMT(k, CAPACITY - 1) != MARK;
}
/* Mengirimkan true jika keranjang penuh */

/* ********** BACA / TULIS ********** */
void readKeranjang(KeranjangPisang *k) {
    int n;
    IdxType i;
    ElType val; // Gunakan ElType sesuai typedef di header

    // 1. Bersihkan dulu keranjangnya biar ga ada sampah memori
    CreateKeranjang(k);

    // 2. Input jumlah elemen (n)
    do {
        scanf("%d", &n);
    } while (n < 0 || n > CAPACITY);

    // 3. Input elemen-elemennya
    for (i = IDX_MIN; i < n; i++) {
        scanf("%d", &val);
        ELMT(*k, i) = val; // Masukkan nilai ke ADT
    }
}
/* I.S. Sembarang */
/* F.S. Keranjang berisi n elemen hasil input (0 <= n <= CAPACITY) */
/* Format input: n diikuti n buah elemen */
/* Contoh: 3 10 20 30*/
/* n = 3 dengan elemen keranjang adalah 10,20,dan 30*/

void printKeranjang(KeranjangPisang k) {
    printf("[");
    
    // Cek dulu, kalau kosong langsung tutup kurung saja
    if (lengthKeranjang(k) > 0) {
        IdxType i;
        IdxType last = getLastIdx(k); // Ambil indeks terakhir
        
        for (i = IDX_MIN; i <= last; i++) {
            printf("%d", ELMT(k, i));
            
            // CETAK KOMA: Hanya jika ini BUKAN elemen terakhir
            if (i < last) {
                printf(",");
            }
        }
    }
    
    printf("]");
}
/* Menampilkan isi keranjang dalam format [x1,x2,...,xn] */
/* Contoh : */
/* [10,20,30] */
/* Jika kosong : []*/

/* ********** OPERASI PENAMBAHAN ELEMEN ********** */
void insertFirst(KeranjangPisang *k, ElType val) {
    if(!isFull(*k)) { 
        IdxType i, last;
        last = getLastIdx(*k);

        for (i = last; i >= IDX_MIN; i--) {
            ELMT(*k, i + 1) = ELMT(*k, i);
        }
        ELMT(*k, IDX_MIN) = val;
    }
    else if(lengthKeranjang(*k) == 0) {
        ELMT(*k, IDX_MIN) = val;
    }
}
/* Menambahkan val sebagai elemen pertama */

void insertAt(KeranjangPisang *k, ElType val, IdxType idx) {
    if(!isFull(*k)) { 
        IdxType i, last;
        last = getLastIdx(*k);

        for (i = last; i >= idx; i--) {
            ELMT(*k, i + 1) = ELMT(*k, i);
        }
        ELMT(*k, idx) = val;
    }
}
/* Menambahkan val di indeks tertentu */

void insertLast(KeranjangPisang *k, ElType val) {
    if(!isFull(*k)) {
        IdxType last = getLastIdx(*k);
        ELMT(*k, last+1) = val;
    }
}
/* Menambahkan val sebagai elemen terakhir */

/* ********** OPERASI PENGHAPUSAN ELEMEN ********** */
void deleteFirst(KeranjangPisang *k, ElType *val) {
    int length = lengthKeranjang(*k);

    if (!isEmpty(*k)) {
        *val = ELMT(*k, IDX_MIN);

        for (IdxType i = IDX_MIN; i < length - 1; i++)
        {
            ELMT(*k, i) = ELMT(*k, i + 1);
        }
        ELMT(*k, length - 1) = MARK;
    }
}
/* Menghapus elemen pertama */

void deleteAt(KeranjangPisang *k, ElType *val, IdxType idx) {
    int length = lengthKeranjang(*k);
    IdxType i;

    if (!isEmpty(*k) && isIdxEff(*k, idx)) {
        *val = ELMT(*k, idx);

        for (i = idx; i < length - 1; i++)
        {
            ELMT(*k, i) = ELMT(*k, i + 1);
        }
        ELMT(*k, length - 1) = MARK;
    }
}
/* Menghapus elemen di indeks tertentu */

void deleteLast(KeranjangPisang *k, ElType *val) {
    IdxType last = getLastIdx(*k);

    if (!isEmpty(*k)) {
        *val = ELMT(*k, last);
        ELMT(*k, last) = MARK;
    }
}
/* Menghapus elemen terakhir */
