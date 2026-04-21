#include "boolean.h"

#ifndef LIST_ANOMALI_H
#define LIST_ANOMALI_H

/* Kamus Umum */
#define MAX_CAPACITY 100 /* Kapasitas maksimum list */
#define IDX_MIN 0        /* Index tak terdefinisi   */
#define IDX_UNDEF -1     /* Index tak terdefinisi   */
#define ELEM_UNDEF -999  /* Elemen tak terdefinisi  */

/* Definisi elemen dan koleksi objek */
typedef int IdxType;
typedef int ElType;

typedef struct {

		/* memori tempat penyimpan elemen (buffer) */
		ElType buffer [MAX_CAPACITY];
		/* banyaknya elemen efektif */
		int nEff;

} ListAnomali;

/* Indeks yang digunakan [IDX_MIN..MAX_CAPACITY - 1] */
/* Jika T adalah ListAnomali, */
/* Maka cara akses:
 * T.nEff untuk mengetahui banyaknya elemen saat ini
 * T.buffer untuk mengakses seluruh nilai elemen list
 * T.buffer[i] untuk mengakses elemen ke-i */
/* Definisi :
 * list kosong: T.nEff = 0
 * list penuh: T.nEff = MAX_CAPACITY
 * Definisi elemen pertama : T.buffer[i] dengan i=IDX_MIN
 * Definisi elemen terakhir yang terdefinisi: T.buffer[i] dengan i=(T.nEff - 1)*/

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create list kosong */
void CreateListAnomali(ListAnomali *T);
/* I.S. T sembarang */
/* F.S. Terbentuk list T kosong dengan kapasitas MAX_CAPACITY */

/* ********** SELEKTOR ********** */
/* *** Banyaknya elemen *** */
int countAnomaly(ListAnomali T);
/* Mengirimkan banyaknya anomali efektif list */
/* Mengirimkan nol jika list kosong */

/* *** Daya tampung anomali list *** */
int maxNbAnomaly(ListAnomali T);
/* Mengirimkan maksimum elemen yang dapat ditampung oleh list (MAX_CAPACITY) */

/* ********** Test Indeks yang valid ********** */
boolean isIdxEff(ListAnomali T, IdxType i);
/* Prekondisi : List T sembarang (bisa kosong atau bisa terisi), i sembarang */
/* Mengirimkan true jika i adalah indeks yang terdefinisi utk list yaitu antara indeks pertama dan indeks nEff */

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test list kosong *** */
boolean isEmpty(ListAnomali T);
/* Mengirimkan true jika list T kosong, mengirimkan false jika tidak */

/* *** Test list penuh *** */
boolean isFull(ListAnomali T);
/* Mengirimkan true jika list T penuh, mengirimkan false jika tidak */

/* ********** Selektor INDEKS ********** */
IdxType getFirstIdx(ListAnomali T);
/* Prekondisi : List T sembarang (bisa kosong atau bisa terisi) */
/* Mengirimkan indeks elemen pertama yaitu IDX_MIN */
/* Jika list kosong, return IDX_UNDEF */

IdxType getLastIndex(ListAnomali T);
/* Prekondisi : List T sembarang (bisa kosong atau bisa terisi) */
/* Mengirimkan indeks elemen efektif terakhir */
/* Jika list kosong, return IDX_UNDEF */

/* *** Menghasilkan sebuah elemen *** */
ElType getAnomalyAtIdx(ListAnomali T, IdxType i);
/* Prekondisi : list T sembarang (bisa kosong atau bisa terisi), i antara getFirstIdx() sampai getLastIdx() */
/* Mengirimkan elemen list yang ke-i */
/* Jika list kosong, return ELEM_UNDEF */

/* ********** INPUT/OUTPUT ********** */
void printAnomalies(ListAnomali T);
/* Prekondisi: T boleh kosong */
/* Menuliskan isi list dengan traversal */
/* Tampilkan list dalam kurung siku dalam bentuk [<Elemen-1>,<Elemen-2>,<Elemen-3>,..<Elemen-nEff>], seperti [1,2,3], dan diakhiri newline */
/* Perhatikan bahwa tidak ada spasi dalam output */
/* Jika T kosong : Hanya menulis "LIST KOSONG" dan diakhiri newline */

/* ********** Operasi Dasar ********** */
void setAt(ListAnomali *T, ElType v, IdxType i);
/* Prekondisi : list T terisi, indeks i bisa tidak valid */
/* Mengganti elemen T pada indeks i menjadi v */

void insertAt(ListAnomali *T, ElType v, IdxType i);
/* Prekondisi : list T sembarang (bisa kosong atau bisa terisi) dan TIDAK PENUH, indeks i bisa tidak valid */
/* Menyelipkan elemen v ke T di indeks i */
/* Semua elemen setelah indeks digeser ke kanan */

void deleteAt(ListAnomali *T, IdxType i, ElType *v);
/* Prekondisi : list T sembarang (bisa kosong atau bisa terisi) dan indeks i bisa tidak valid */
/* Menghapus ElType pada indeks i */
/* Semua elemen setelahnya DIGESER ke kiri */
/* Elemen yang dihapus disimpan pada v */

/* ********** Anomaly Operations ********** */
ElType highestAnomaly(ListAnomali T);
/* Prekondisi : list T tidak kosong */
/* Mengirimkan nilai anomali tertinggi di list */

ElType lowestAnomaly(ListAnomali T);
/* Prekondisi : list T tidak kosong */
/* Mengirimkan nilai anomali terendah di list */

void shiftRightByK(ListAnomali *T, int K);
/* Prekondisi : list T tidak kosong dan (last_idx + K) < max_anomaly_count */
/* Menggeser seluruh elemen ke kanan sebanyak K kali */
/* Gunakan ELEM_UNDEF sebagai elemen baru di kiri */
/* Contoh, untuk K = 2, maka [1,2,3] menjadi [ELEM_UNDEF,ELEM_UNDEF,1,2,3]*/

void reverseList(ListAnomali *T);
/* Prekondisi : list T tidak kosong */
/* Membalikkan list T */
/* Contoh, untuk untuk list [1,2,3], maka menjadi [3,2,1] */

void reverseList(ListAnomali *T);
/* Prekondisi : list T tidak kosong */
/* Membalikkan list T */
/* Contoh, untuk untuk list [1,2,3], maka menjadi [3,2,1] */

void extractExtremeAnomalies(ListAnomali *T_src, ListAnomali *T_dst);
/* Prekondisi : list T_src dan T_dst sembarang (bisa kosong atau bisa terisi) */
/* MEMINDAHKAN elemen anomali ekstrim dari T_src ke T_dst secara urut dari kiri ke kanan */
/* Anomali ekstrem didefinisikan sebagai anomali dengan nilai <= -100 dan >= 100*/
/* Contoh: */
/* untuk untuk list T_src [0, 100, -200], maka h:*/
/*     T_src akan berisi [0]  */
/*     T_dst akan berisi [100, -200]  */
/* Jika T_dst tidak kosong dan ada elemen yang bisa diekstrak : semua nilai T_dst dihilangkan (List di overwrite) */
/* Jika T_dst tidak kosong dan tidak ada elemen yang bisa diekstrak : jangan ubah T_dst */

#endif