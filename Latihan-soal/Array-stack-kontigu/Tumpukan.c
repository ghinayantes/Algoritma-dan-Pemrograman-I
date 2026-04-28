#include <stdio.h>
#include "Tumpukan.h"

/* ===================== KONSTRUKTOR ===================== */

void BuatTumpukan (Tumpukan *T) {
    T->NEffElmt = 0;
}
/* Membuat tumpukan kosong.
   I.S. T sembarang.
   F.S. Terbentuk tumpukan T kosong: NEffElmt = 0. */


/* ===================== PREDIKAT ======================== */

boolean TumpukanKosong (Tumpukan T) {
    return T.NEffElmt == 0;
}
/* Mengembalikan true jika tumpukan T kosong (NEffElmt = 0). */

boolean TumpukanPenuh (Tumpukan T) {
    return T.NEffElmt == MAX_TUMPUKAN;
}
/* Mengembalikan true jika tumpukan T sudah mencapai kapasitas maksimum. */


/* ===================== SELEKTOR ======================== */

ElType TopOf (Tumpukan T) {
    return T.T[T.NEffElmt-1];
}
/* Mengembalikan elemen teratas tumpukan T.
   Prekondisi: tumpukan T tidak kosong. */

ElType BottomOf (Tumpukan T) {
    return T.T[0];
}
/* Mengembalikan elemen terbawah tumpukan T.
   Prekondisi: tumpukan T tidak kosong. */

int NbElmt (Tumpukan T) {
    return T.NEffElmt;
}
/* Mengembalikan banyak elemen efektif pada tumpukan T. */


/* ===================== OPERASI DASAR ================== */

void Push (Tumpukan *T, ElType e) {
    T->T[T->NEffElmt] = e;
    T->NEffElmt++;
}
/* Menambahkan elemen e ke atas tumpukan T.
   I.S. T terdefinisi dan tidak penuh.
   F.S. e menjadi elemen teratas baru; NEffElmt bertambah 1. */

void Pop (Tumpukan *T, ElType *e) {
    *e = T->T[T->NEffElmt-1];
    T->T[T->NEffElmt-1] = IDX_TOP;
    T->NEffElmt--;
}
/* Mengambil elemen teratas tumpukan T ke e.
   I.S. T tidak kosong.
   F.S. e bernilai elemen teratas lama; elemen teratas dihapus;
        NEffElmt berkurang 1. */


/* ===================== OPERASI LANJUTAN ================ */

void PushBottom (Tumpukan *T, ElType e) {
    if (TumpukanKosong(*T)) {
        Push(T, e);
    } 
    else {
        ElType temp;
        Pop(T, &temp);
        PushBottom(T, e);
        Push(T, temp);
    }
}
/* Menyisipkan elemen e ke BAWAH tumpukan (posisi terbawah),
   tanpa mengubah urutan elemen yang sudah ada.
   I.S. T terdefinisi dan tidak penuh.
   F.S. e menjadi elemen terbawah; semua elemen lama bergeser
        satu posisi ke atas; NEffElmt bertambah 1.
   Catatan: HANYA boleh menggunakan Push dan Pop sebagai primitif pembantu.
            Tidak boleh mengakses array T.T secara langsung. */

void BalikTumpukan (Tumpukan *T) {
    int i;
    ElType temp;
    for(i = 1; i < NbElmt(*T); i++) {
        PushBottom(T, T->T[i]);
        Pop(T, &temp);
    }
}
/* Membalik urutan elemen pada tumpukan T (in-place).
   I.S. T terdefinisi.
   F.S. Urutan elemen tumpukan T dibalik: elemen teratas menjadi
        terbawah dan sebaliknya.
   Contoh: T = [1,2,3] (3 di atas) -> T = [3,2,1] (1 di atas).
   Catatan: HANYA boleh menggunakan Push, Pop, dan PushBottom. */

boolean ElmtAdaDiTumpukan (Tumpukan T, ElType e) {
    int i;
    for(i = 0; i < NbElmt(T); i++) {
        if(T.T[i] == e) return TRUE;
    }
    return FALSE;
}
/* Mengembalikan true jika e terdapat di dalam tumpukan T.
   Tumpukan T tidak berubah setelah pemanggilan fungsi ini. */

void HapusDuplikat (Tumpukan *T) {
    int i, j, k;
    for(i = 0, i < NbElmt(*T); i++) {
        for(j = i; j < NbElmt(*T); j++) {
            if(T->T[i] == T->T[j] && i != j) {
                for(k = j; k < NbElmt(*T)-1; k++) {
                    T->T[k] = T->T[k+1];
                    T->T[NbElmt(*T)-1] = IDX_TOP;
                }
            }
        }
    }
}
/* Menghapus semua elemen duplikat pada tumpukan T, menyisakan
   hanya kemunculan PERTAMA dari bawah untuk setiap nilai.
   I.S. T terdefinisi.
   F.S. T tidak memiliki elemen dengan nilai yang sama.
   Contoh: T = [1,3,1,2,3] (3 di atas) -> T = [1,3,2] (2 di atas). */


/* ===================== OUTPUT ========================== */

void CetakTumpukan (Tumpukan T) {
    int i;
    if(NbElmt(T) == 0) printf("TUMPUKAN KOSONG\n");
    else {
        printf("[TOP] ");
        for(i = 0; i < NbElmt(T); i++) {
            printf("%d ", T.T[i]);
            if(i != NbElmt(T)-2) printf("| ");
        }
        printf("[BOT]\n");
    }
}
/* Mencetak isi tumpukan dari ATAS ke BAWAH, dipisahkan ' | ',
   diawali '[TOP] ' dan diakhiri ' [BOT]\n'.
   Jika kosong, cetak: TUMPUKAN KOSONG\n
   Contoh (3 elemen, 9 di atas): [TOP] 9 | 4 | 1 [BOT]
   Tumpukan T tidak berubah setelah pemanggilan. */
