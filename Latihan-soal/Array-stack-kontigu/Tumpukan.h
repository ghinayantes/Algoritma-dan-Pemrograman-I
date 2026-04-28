#ifndef TUMPUKAN_H
#define TUMPUKAN_H

#include "boolean.h"

/* Kamus Umum */
#define MAX_TUMPUKAN 50
#define IDX_TOP      -1  /* penanda tumpukan kosong */

typedef int ElType;

typedef struct {
    ElType T[MAX_TUMPUKAN]; /* T[0..NEffElmt-1], T[NEffElmt-1] adalah TOP */
    int    NEffElmt;        /* banyak elemen efektif, 0 jika kosong         */
} Tumpukan;


/* ===================== KONSTRUKTOR ===================== */

void BuatTumpukan (Tumpukan *T);
/* Membuat tumpukan kosong.
   I.S. T sembarang.
   F.S. Terbentuk tumpukan T kosong: NEffElmt = 0. */


/* ===================== PREDIKAT ======================== */

boolean TumpukanKosong (Tumpukan T);
/* Mengembalikan true jika tumpukan T kosong (NEffElmt = 0). */

boolean TumpukanPenuh (Tumpukan T);
/* Mengembalikan true jika tumpukan T sudah mencapai kapasitas maksimum. */


/* ===================== SELEKTOR ======================== */

ElType TopOf (Tumpukan T);
/* Mengembalikan elemen teratas tumpukan T.
   Prekondisi: tumpukan T tidak kosong. */

ElType BottomOf (Tumpukan T);
/* Mengembalikan elemen terbawah tumpukan T.
   Prekondisi: tumpukan T tidak kosong. */

int NbElmt (Tumpukan T);
/* Mengembalikan banyak elemen efektif pada tumpukan T. */


/* ===================== OPERASI DASAR ================== */

void Push (Tumpukan *T, ElType e);
/* Menambahkan elemen e ke atas tumpukan T.
   I.S. T terdefinisi dan tidak penuh.
   F.S. e menjadi elemen teratas baru; NEffElmt bertambah 1. */

void Pop (Tumpukan *T, ElType *e);
/* Mengambil elemen teratas tumpukan T ke e.
   I.S. T tidak kosong.
   F.S. e bernilai elemen teratas lama; elemen teratas dihapus;
        NEffElmt berkurang 1. */


/* ===================== OPERASI LANJUTAN ================ */

void PushBottom (Tumpukan *T, ElType e);
/* Menyisipkan elemen e ke BAWAH tumpukan (posisi terbawah),
   tanpa mengubah urutan elemen yang sudah ada.
   I.S. T terdefinisi dan tidak penuh.
   F.S. e menjadi elemen terbawah; semua elemen lama bergeser
        satu posisi ke atas; NEffElmt bertambah 1.
   Catatan: HANYA boleh menggunakan Push dan Pop sebagai primitif pembantu.
            Tidak boleh mengakses array T.T secara langsung. */

void BalikTumpukan (Tumpukan *T);
/* Membalik urutan elemen pada tumpukan T (in-place).
   I.S. T terdefinisi.
   F.S. Urutan elemen tumpukan T dibalik: elemen teratas menjadi
        terbawah dan sebaliknya.
   Contoh: T = [1,2,3] (3 di atas) -> T = [3,2,1] (1 di atas).
   Catatan: HANYA boleh menggunakan Push, Pop, dan PushBottom. */

boolean ElmtAdaDiTumpukan (Tumpukan T, ElType e);
/* Mengembalikan true jika e terdapat di dalam tumpukan T.
   Tumpukan T tidak berubah setelah pemanggilan fungsi ini. */

void HapusDuplikat (Tumpukan *T);
/* Menghapus semua elemen duplikat pada tumpukan T, menyisakan
   hanya kemunculan PERTAMA dari bawah untuk setiap nilai.
   I.S. T terdefinisi.
   F.S. T tidak memiliki elemen dengan nilai yang sama.
   Contoh: T = [1,3,1,2,3] (3 di atas) -> T = [1,3,2] (2 di atas). */


/* ===================== OUTPUT ========================== */

void CetakTumpukan (Tumpukan T);
/* Mencetak isi tumpukan dari ATAS ke BAWAH, dipisahkan ' | ',
   diawali '[TOP] ' dan diakhiri ' [BOT]\n'.
   Jika kosong, cetak: TUMPUKAN KOSONG\n
   Contoh (3 elemen, 9 di atas): [TOP] 9 | 4 | 1 [BOT]
   Tumpukan T tidak berubah setelah pemanggilan. */

#endif
