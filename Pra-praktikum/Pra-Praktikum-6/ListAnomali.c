#include <stdio.h>
#include "ListAnomali.h"

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create list kosong */
void CreateListAnomali(ListAnomali *T) {
    T->nEff = 0;
}
/* I.S. T sembarang */
/* F.S. Terbentuk list T kosong dengan kapasitas MAX_CAPACITY */

/* ********** SELEKTOR ********** */
/* *** Banyaknya elemen *** */
int countAnomaly(ListAnomali T) {
    return T.nEff;
}
/* Mengirimkan banyaknya anomali efektif list */
/* Mengirimkan nol jika list kosong */

/* *** Daya tampung anomali list *** */
int maxNbAnomaly(ListAnomali T) {
    return MAX_CAPACITY;
}
/* Mengirimkan maksimum elemen yang dapat ditampung oleh list (MAX_CAPACITY) */

/* ********** Test Indeks yang valid ********** */
boolean isIdxEff(ListAnomali T, IdxType i) {
    if(countAnomaly(T) == 0) return false;
    return (i >= IDX_MIN) && (i < T.nEff);
}
/* Prekondisi : List T sembarang (bisa kosong atau bisa terisi), i sembarang */
/* Mengirimkan true jika i adalah indeks yang terdefinisi utk list yaitu antara indeks pertama dan indeks nEff */

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test list kosong *** */
boolean isEmpty(ListAnomali T) {
    return countAnomaly(T) == 0;
}
/* Mengirimkan true jika list T kosong, mengirimkan false jika tidak */

/* *** Test list penuh *** */
boolean isFull(ListAnomali T) {
    return countAnomaly(T) == MAX_CAPACITY;
}
/* Mengirimkan true jika list T penuh, mengirimkan false jika tidak */

/* ********** Selektor INDEKS ********** */
IdxType getFirstIdx(ListAnomali T) {
    if(countAnomaly(T) == 0) return IDX_UNDEF;
    return IDX_MIN;
}
/* Prekondisi : List T sembarang (bisa kosong atau bisa terisi) */
/* Mengirimkan indeks elemen pertama yaitu IDX_MIN */
/* Jika list kosong, return IDX_UNDEF */

IdxType getLastIndex(ListAnomali T) {
    if(countAnomaly(T) == 0) return IDX_UNDEF;
    return countAnomaly(T) - 1;
}
/* Prekondisi : List T sembarang (bisa kosong atau bisa terisi) */
/* Mengirimkan indeks elemen efektif terakhir */
/* Jika list kosong, return IDX_UNDEF */

/* *** Menghasilkan sebuah elemen *** */
ElType getAnomalyAtIdx(ListAnomali T, IdxType i) {
    if(countAnomaly(T) == 0) return ELEM_UNDEF;
    return T.buffer[i];

}
/* Prekondisi : list T sembarang (bisa kosong atau bisa terisi), i antara getFirstIdx() sampai getLastIdx() */
/* Mengirimkan elemen list yang ke-i */
/* Jika list kosong, return ELEM_UNDEF */

/* ********** INPUT/OUTPUT ********** */
void printAnomalies(ListAnomali T) {
    IdxType i;
    if(countAnomaly(T) == 0) printf("LIST KOSONG\n");
    else {
        printf("[");
        for(i = getFirstIdx(T); i <= getLastIndex(T); i++) {
            printf("%d", T.buffer[i]);
            if(i != getLastIndex(T)) printf(",");
        }
        printf("]\n");
    }
}
/* Prekondisi: T boleh kosong */
/* Menuliskan isi list dengan traversal */
/* Tampilkan list dalam kurung siku dalam bentuk [<Elemen-1>,<Elemen-2>,<Elemen-3>,..<Elemen-nEff>], seperti [1,2,3], dan diakhiri newline */
/* Perhatikan bahwa tidak ada spasi dalam output */
/* Jika T kosong : Hanya menulis "LIST KOSONG" dan diakhiri newline */

/* ********** Operasi Dasar ********** */
void setAt(ListAnomali *T, ElType v, IdxType i) {
    if(isIdxEff(*T, i)) {
        T->buffer[i] = v;
    }
}
/* Prekondisi : list T terisi, indeks i bisa tidak valid */
/* Mengganti elemen T pada indeks i menjadi v */

void insertAt(ListAnomali *T, ElType v, IdxType i) {
    IdxType ir;
    if (!isFull(*T) && i >= IDX_MIN && i <= T->nEff) {
        for (ir = T->nEff - 1; ir >= i; ir--) {
            T->buffer[ir + 1] = T->buffer[ir];
        }
        T->buffer[i] = v;
        T->nEff++;
    }
}
/* Prekondisi : list T sembarang (bisa kosong atau bisa terisi) dan TIDAK PENUH, indeks i bisa tidak valid */
/* Menyelipkan elemen v ke T di indeks i */
/* Semua elemen setelah indeks digeser ke kanan */

void deleteAt(ListAnomali *T, IdxType i, ElType *v) {
    IdxType ir;
    if(isIdxEff(*T, i)) {
        *v = getAnomalyAtIdx(*T, i);
        for(ir = i; ir < getLastIndex(*T); ir++) {
            T->buffer[ir] = T->buffer[ir+1];
        }
        T->buffer[getLastIndex(*T)] = ELEM_UNDEF;
        T->nEff--;
    }
}
/* Prekondisi : list T sembarang (bisa kosong atau bisa terisi) dan indeks i bisa tidak valid */
/* Menghapus ElType pada indeks i */
/* Semua elemen setelahnya DIGESER ke kiri */
/* Elemen yang dihapus disimpan pada v */

/* ********** Anomaly Operations ********** */
ElType highestAnomaly(ListAnomali T) {
    IdxType i;
    ElType max = T.buffer[getFirstIdx(T)];
    for(i = getFirstIdx(T); i <= getLastIndex(T); i++) {
        if(max < T.buffer[i]) max = T.buffer[i];
    }
    return max;
}
/* Prekondisi : list T tidak kosong */
/* Mengirimkan nilai anomali tertinggi di list */

ElType lowestAnomaly(ListAnomali T) {
    IdxType i;
    ElType min = T.buffer[getFirstIdx(T)];
    for(i = getFirstIdx(T); i <= getLastIndex(T); i++) {
        if(min > T.buffer[i]) min = T.buffer[i];
    }
    return min;
}
/* Prekondisi : list T tidak kosong */
/* Mengirimkan nilai anomali terendah di list */

void shiftRightByK(ListAnomali *T, int K) {
    IdxType i;
    if (isEmpty(*T) || K <= 0) return;
    

    for (i = T->nEff - 1; i >= 0; i--) {
        T->buffer[i + K] = T->buffer[i];
    }

    for (i = 0; i < K; i++) {
        T->buffer[i] = ELEM_UNDEF;
    }
    T->nEff += K;
}
/* Prekondisi : list T tidak kosong dan (last_idx + K) < max_anomaly_count */
/* Menggeser seluruh elemen ke kanan sebanyak K kali */
/* Gunakan ELEM_UNDEF sebagai elemen baru di kiri */
/* Contoh, untuk K = 2, maka [1,2,3] menjadi [ELEM_UNDEF,ELEM_UNDEF,1,2,3]*/

void reverseList(ListAnomali *T) {
    IdxType i, j;
    ElType tmp;
    i = getFirstIdx(*T);
    j = getLastIndex(*T);
    while (i < j) {
        tmp = T->buffer[i];
        T->buffer[i] = T->buffer[j];
        T->buffer[j] = tmp;
        i++;
        j--;
    }
}
/* Prekondisi : list T tidak kosong */
/* Membalikkan list T */
/* Contoh, untuk untuk list [1,2,3], maka menjadi [3,2,1] */

void extractExtremeAnomalies(ListAnomali *T_src, ListAnomali *T_dst) {
    IdxType i;
    ElType v;
    boolean ada = false;
    if(countAnomaly(*T_src) > 0) {
        for(i = getFirstIdx(*T_src); i <= getLastIndex(*T_src); i++) {
            if(T_src->buffer[i] <= -100 || T_src->buffer[i] >= 100) {
                ada = true;
                break;
            }
        }
    }

    if(ada) {
        CreateListAnomali(T_dst);
        i = 0;
        while (i < T_src->nEff) {
            if(T_src->buffer[i] <= -100 || T_src->buffer[i] >= 100) {
                T_dst->buffer[T_dst->nEff] = T_src->buffer[i];
                T_dst->nEff++;
                deleteAt(T_src, i, &v);
            } 
            else {
                i++;
            }
        }
    }
}
/* Prekondisi : list T_src dan T_dst sembarang (bisa kosong atau bisa terisi) */
/* MEMINDAHKAN elemen anomali ekstrim dari T_src ke T_dst secara urut dari kiri ke kanan */
/* Anomali ekstrem didefinisikan sebagai anomali dengan nilai <= -100 dan >= 100*/
/* Contoh: */
/* untuk untuk list T_src [0, 100, -200], maka h:*/
/*     T_src akan berisi [0]  */
/*     T_dst akan berisi [100, -200]  */
/* Jika T_dst tidak kosong dan ada elemen yang bisa diekstrak : semua nilai T_dst dihilangkan (List di overwrite) */
/* Jika T_dst tidak kosong dan tidak ada elemen yang bisa diekstrak : jangan ubah T_dst */




