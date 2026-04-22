#ifndef LIST_MATKUL_H
#define LIST_MATKUL_H

#include "boolean.h"

#define MAX_CAPACITY 100
#define IDX_UNDEFINED -1

typedef int IdxType;
typedef struct {
    char* kode;
    int sks;
    int semester;
    char nilai;
} ElType;

typedef struct {
    ElType contents[MAX_CAPACITY];  /* memori tempat penyimpan elemen (container) */
    int Neff;                       /* banyaknya elemen efektif */
} ListMatkul;

/* Indeks yang digunakan [0..MAX_CAPACITY-1]
 * Jika L adalah ListMatkul, cara deklarasi dan akses:
 *
 * Deklarasi:  ListMatkul L;
 * 
 * Maka cara akses:
 * L.Neff untuk mengetahui banyaknya elemen
 * L.contents untuk mengakses seluruh nilai elemen tabel
 * L.contents[i] untuk mengakses elemen ke-i
 * 
 * Definisi :
 * Tabel kosong: L.Neff = 0
 * Definisi elemen pertama : L.contents[i] dengan i=1
 * Definisi elemen terakhir yang terdefinisi: L.contents[i] dengan i=L.Neff 
 **/

/* ********** KONSTRUKTOR ARRAY ********** */
/* Konstruktor : create tabel kosong */
void MakeEmpty (ListMatkul* L);
/* I.S. sembarang */
/* F.S. Terbentuk list L kosong dengan kapasitas MAX_CAPACITY */
/* Untuk membantu pengerjaan praktikum, silahkan gunakan kode berikut untuk fungsi ini */
// (*L).Neff = 0;

/* ********** SELEKTOR ********** */
/* *** Banyaknya elemen *** */
int NbElmt (ListMatkul L);
/* Mengirimkan banyaknya elemen efektif list */
/* Mengirimkan nol jika list kosong */
/* Untuk membantu pengerjaan praktikum, silahkan gunakan kode berikut untuk fungsi ini */
// return L.Neff;

/* *** Daya tampung container *** */
int MaxNbEl (ListMatkul L);
/* Mengirimkan maksimum elemen yang dapat ditampung oleh list */
/* Untuk membantu pengerjaan praktikum, silahkan gunakan kode berikut untuk fungsi ini */
// return MAX_CAPACITY;

/* *** Selektor INDEKS *** */
IdxType GetFirstIdx (ListMatkul L);
/* Prekondisi : List L tidak kosong */
/* Mengirimkan indeks elemen pertama */
/* Untuk membantu pengerjaan praktikum, silahkan gunakan kode berikut untuk fungsi ini */
// return 0;

IdxType GetLastIdx (ListMatkul L);
/* Prekondisi : List L tidak kosong */
/* Mengirimkan indeks elemen terakhir */
/* Untuk membantu pengerjaan praktikum, silahkan gunakan kode berikut untuk fungsi ini */
// return L.Neff-1;

/* *** Menghasilkan sebuah elemen *** */
ElType GetElmt (ListMatkul L, IdxType i);
/* Prekondisi : List tidak kosong, i antara FirstIdx(L)..LastIdx(L) */
/* Mengirimkan elemen list yang ke-i */
/* Untuk membantu pengerjaan praktikum, silahkan gunakan kode berikut untuk fungsi ini */
// return L.contents[i];

/* *** Selektor SET : Mengubah nilai list dan elemen list *** */
/* Untuk type private/limited private pada bahasa tertentu */
void SetTab (ListMatkul Lin, ListMatkul* Lout);
/* I.S. Lin terdefinisi, sembarang */
/* F.S. Lout berisi salinan Lin */
/* Assignment Lout = Lin */
/* Untuk membantu pengerjaan praktikum, silahkan gunakan kode berikut untuk fungsi ini */
// (*Lout).Neff = Lin.Neff;
// for(int i = 0; i < Lin.Neff; i++){
//     (*Lout).contents[i] = Lin.contents[i];
// }

void SetEl (ListMatkul* L, IdxType i, ElType v);
/* I.S. L terdefinisi, sembarang */
/* F.S. Elemen L yang ke-i bernilai v */
/* Mengeset nilai elemen list yang ke-i sehingga bernilai v */
/* Untuk membantu pengerjaan praktikum, silahkan gunakan kode berikut untuk fungsi ini */
// (*L).contents[i] = v;
// if ((*L).Neff < i+1){
//     (*L).Neff = i+1;
// }

void SetNeff (ListMatkul* L, IdxType N);
/* I.S. L terdefinisi, sembarang */
/* F.S. Nilai indeks efektif L bernilai N */
/* Mengeset nilai indeks elemen efektif sehingga bernilai N */
/* Untuk membantu pengerjaan praktikum, silahkan gunakan kode berikut untuk fungsi ini */
// (*L).Neff = N;

/* ********** Test Indeks yang valid ********** */
boolean IsIdxValid (ListMatkul L, IdxType i);
/* Prekondisi : i sembarang */
/* Mengirimkan true jika i adalah indeks yang valid utk ukuran list */
/* yaitu antara indeks yang terdefinisi utk container */
/* Untuk membantu pengerjaan praktikum, silahkan gunakan kode berikut untuk fungsi ini */
// return i >= GetFirstIdx(L) && i < MAX_CAPACITY;

boolean IsIdxEff (ListMatkul L, IdxType i);
/* Prekondisi : i sembarang*/
/* Mengirimkan true jika i adalah indeks yang terdefinisi utk list */
/* yaitu antara GetFirstIdx(L)..GetLastIdx(L) */
/* Untuk membantu pengerjaan praktikum, silahkan gunakan kode berikut untuk fungsi ini */
// return i >= GetFirstIdx(L) && i <= GetLastIdx(L);

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test tabel kosong *** */
boolean IsEmpty (ListMatkul L);
/* Mengirimkan true jika list L kosong, mengirimkan false jika tidak */
/* Untuk membantu pengerjaan praktikum, silahkan gunakan kode berikut untuk fungsi ini */
// return L.Neff == 0;

/* *** Test tabel penuh *** */
boolean IsFull (ListMatkul L);
/* Mengirimkan true jika tabel T penuh, mengirimkan false jika tidak */
/* Untuk membantu pengerjaan praktikum, silahkan gunakan kode berikut untuk fungsi ini */
// return L.Neff == MAX_CAPACITY;

/* ********** BACA dan TULIS dengan INPUT/OUTPUT device ********** */
void PrintIsi(ListMatkul L);
/* Proses : Menuliskan isi list dengan traversal */
/* I.S. L boleh kosong */
/* F.S. Jika L tidak kosong : elemen tabel ditulis berderet ke bawah dengan format */
/* Kode(SKS) - Semester: Nilai */
/* Contoh:
II2130(3) - 3: B
II2110(3) - 3: B
IF2111(3) - 3: A
IF2212(3) - 4: A
*/
/* Jika L kosong : Hanya menulis "List kosong" */

/* ********** KONSTRUKTOR MATA KULIAH ********** */
ElType MakeMatkul (char* kode, int sks, int semester, char nilai);
/* Membentuk sebuah Mahasiswa dari komponen-komponennya */
/* Prekondisi (tidak perlu dicek): */
/* Kode terdiri dari 6 karakter dengan 2 karakter pertama merupakan huruf kapital dan 4 karakter selanjutnya angka. Contoh: IF2111 */
/* Nilai hanya terdiri dari indeks A (4), B (3), C (2), D (1), dan E (0) */
/* I.S. kode, sks, semester, dan nilai terdefinisi */
/* F.S. Mata kuliah MK terbentuk dengan kode, sks, semester, dan nilai yang sesuai */

/* ********** OPERATOR STATISTIK MATA KULIAH ********** */
int SumNilai(ListMatkul L, int semester);
/* Prekondisi : List L tidak kosong */
/* Mengembalikan jumlah nilai dalam suatu semester, indeks huruf akan dikonversikan menjadi angka kemudian dikalikan dengan SKS
   konversi dilakukan dgn ketentuan berikut */
/* A: 4, B: 3, C: 2, D: 1, dan E: 0 */

int CountMatkul(ListMatkul L, int semester);
/* Prekondisi : List L tidak kosong */
/* Mengembalikan jumlah mata kuliah yang diambil dalam suatu semester */

int CountSKS(ListMatkul L, int semester);
/* Prekondisi : List L tidak kosong */
/* Mengembalikan jumlah SKS dari mata kuliah yang diambil dalam suatu semester */

int CountTotalSKS(ListMatkul L);
/* Prekondisi : List L tidak kosong */
/* Mengembalikan jumlah SKS dari mata kuliah yang diambil dari seluruh semester */

int MaxSemester(ListMatkul L);
/* Prekondisi : List L tidak kosong */
/* Mengembalikan semester terakhir yang dijalani dalam list */

float HitungIP(ListMatkul L, int semester);
/* Prekondisi : List L tidak kosong */
/* Menghitung indeks prestasi semester terakhir yang dijalani */

float HitungIPK(ListMatkul L);
/* Prekondisi : List L tidak kosong dan semester awal adalah semester 1 sampai MaxSemester() */
/* Menghitung indeks prestasi kumulatif dari seluruh semester dalam list */
/* Perhitungan IPK dilakukan dengan mencari rata-rata IP seluruh semester */

int CountMatkulLuar(ListMatkul L, char* kodeJur);
/* Prekondisi : List L tidak kosong dan kodeJur pasti terdiri dari 2 huruf kapital */
/* Menghitung jumlah mata kuliah luar yang sudah diambil, cara mengetahui mata kuliah luar */
/* adalah dengan mengecek apakah kode matkul berbeda dari kodeJur */
/* Contoh, kodeJur="II" maka IF3120 adalah matkul luar */

void DisplaySIX(ListMatkul L);
/* I.S. List L DIPASTIKAN tidak kosong */
/* F.S. Mencetak tampilan SIX ke layar, desimal dicetak dengan 2 angka di belakang koma dan perhitungan IP dan 
        daftar kuliah diambil dari semester terakhir yang dijalani */
/* Contoh: */
/*
IPK: 3.12
IP: 2.33
SKS: Sudah Diambil 119 SKS
Daftar Kuliah Semester 7:
II4130(4) - 7: C
II4110(2) - 7: B
*/

#endif