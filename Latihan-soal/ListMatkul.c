#include <stdio.h>
#include <stdlib.h>
#include "ListMatkul.h"
#include <string.h>

/* ********** KONSTRUKTOR ARRAY ********** */
/* Konstruktor : create tabel kosong */
void MakeEmpty (ListMatkul* L) {
    L->Neff = 0;
}
/* I.S. sembarang */
/* F.S. Terbentuk list L kosong dengan kapasitas MAX_CAPACITY */
/* Untuk membantu pengerjaan praktikum, silahkan gunakan kode berikut untuk fungsi ini */
// (*L).Neff = 0;

/* ********** SELEKTOR ********** */
/* *** Banyaknya elemen *** */
int NbElmt (ListMatkul L) {
    return L.Neff;
}
/* Mengirimkan banyaknya elemen efektif list */
/* Mengirimkan nol jika list kosong */
/* Untuk membantu pengerjaan praktikum, silahkan gunakan kode berikut untuk fungsi ini */
// return L.Neff;

/* *** Daya tampung container *** */
int MaxNbEl (ListMatkul L) {
    return MAX_CAPACITY;
}
/* Mengirimkan maksimum elemen yang dapat ditampung oleh list */
/* Untuk membantu pengerjaan praktikum, silahkan gunakan kode berikut untuk fungsi ini */
// return MAX_CAPACITY;

/* *** Selektor INDEKS *** */
IdxType GetFirstIdx (ListMatkul L) {
    return 0;
}
/* Prekondisi : List L tidak kosong */
/* Mengirimkan indeks elemen pertama */
/* Untuk membantu pengerjaan praktikum, silahkan gunakan kode berikut untuk fungsi ini */
// return 0;

IdxType GetLastIdx (ListMatkul L) {
    return L.Neff-1;
}
/* Prekondisi : List L tidak kosong */
/* Mengirimkan indeks elemen terakhir */
/* Untuk membantu pengerjaan praktikum, silahkan gunakan kode berikut untuk fungsi ini */
// return L.Neff-1;

/* *** Menghasilkan sebuah elemen *** */
ElType GetElmt (ListMatkul L, IdxType i) {
    return L.contents[i];
}
/* Prekondisi : List tidak kosong, i antara FirstIdx(L)..LastIdx(L) */
/* Mengirimkan elemen list yang ke-i */
/* Untuk membantu pengerjaan praktikum, silahkan gunakan kode berikut untuk fungsi ini */
// return L.contents[i];

/* *** Selektor SET : Mengubah nilai list dan elemen list *** */
/* Untuk type private/limited private pada bahasa tertentu */
void SetTab (ListMatkul Lin, ListMatkul* Lout) {
    IdxType i;
    Lout->Neff = Lin.Neff;
    for(i = 0; i < Lin.Neff; i++) {
        Lout->contents[i] = Lin.contents[i];
    }
}
/* I.S. Lin terdefinisi, sembarang */
/* F.S. Lout berisi salinan Lin */
/* Assignment Lout = Lin */
/* Untuk membantu pengerjaan praktikum, silahkan gunakan kode berikut untuk fungsi ini */
// (*Lout).Neff = Lin.Neff;
// for(int i = 0; i < Lin.Neff; i++){
//     (*Lout).contents[i] = Lin.contents[i];
// }

void SetEl (ListMatkul* L, IdxType i, ElType v) {
    L->contents[i] = v;
    if (L->Neff < i+1) L->Neff = i+1;
}
/* I.S. L terdefinisi, sembarang */
/* F.S. Elemen L yang ke-i bernilai v */
/* Mengeset nilai elemen list yang ke-i sehingga bernilai v */
/* Untuk membantu pengerjaan praktikum, silahkan gunakan kode berikut untuk fungsi ini */
// (*L).contents[i] = v;
// if ((*L).Neff < i+1){
//     (*L).Neff = i+1;
// }

void SetNeff (ListMatkul* L, IdxType N) {
    L->Neff = N;
}
/* I.S. L terdefinisi, sembarang */
/* F.S. Nilai indeks efektif L bernilai N */
/* Mengeset nilai indeks elemen efektif sehingga bernilai N */
/* Untuk membantu pengerjaan praktikum, silahkan gunakan kode berikut untuk fungsi ini */
// (*L).Neff = N;

/* ********** Test Indeks yang valid ********** */
boolean IsIdxValid (ListMatkul L, IdxType i) {
    return i >= GetFirstIdx(L) && i < MAX_CAPACITY;
}
/* Prekondisi : i sembarang */
/* Mengirimkan true jika i adalah indeks yang valid utk ukuran list */
/* yaitu antara indeks yang terdefinisi utk container */
/* Untuk membantu pengerjaan praktikum, silahkan gunakan kode berikut untuk fungsi ini */
// return i >= GetFirstIdx(L) && i < MAX_CAPACITY;

boolean IsIdxEff (ListMatkul L, IdxType i) {
    return i >= GetFirstIdx(L) && i <= GetLastIdx(L);
}
/* Prekondisi : i sembarang*/
/* Mengirimkan true jika i adalah indeks yang terdefinisi utk list */
/* yaitu antara GetFirstIdx(L)..GetLastIdx(L) */
/* Untuk membantu pengerjaan praktikum, silahkan gunakan kode berikut untuk fungsi ini */
// return i >= GetFirstIdx(L) && i <= GetLastIdx(L);

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test tabel kosong *** */
boolean IsEmpty (ListMatkul L) {
    return L.Neff == 0;
}
/* Mengirimkan true jika list L kosong, mengirimkan false jika tidak */
/* Untuk membantu pengerjaan praktikum, silahkan gunakan kode berikut untuk fungsi ini */
// return L.Neff == 0;

/* *** Test tabel penuh *** */
boolean IsFull (ListMatkul L) {
    return L.Neff == MAX_CAPACITY;
}
/* Mengirimkan true jika tabel T penuh, mengirimkan false jika tidak */
/* Untuk membantu pengerjaan praktikum, silahkan gunakan kode berikut untuk fungsi ini */
// return L.Neff == MAX_CAPACITY;

/* ********** BACA dan TULIS dengan INPUT/OUTPUT device ********** */
void PrintIsi(ListMatkul L) {
    IdxType i;
    if(L.Neff == 0) printf("List kosong\n");
    
    for(i = 0; i < L.Neff; i++) {
        printf("%s(%d) - %d: %c\n", L.contents[i].kode, L.contents[i].sks, L.contents[i].semester, L.contents[i].nilai);
    }
}
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
ElType MakeMatkul (char* kode, int sks, int semester, char nilai) {
    ElType r;
    r.kode = kode;
    r.sks = sks;
    r.semester = semester;
    r.nilai = nilai;

    return r;
}
/* Membentuk sebuah Mahasiswa dari komponen-komponennya */
/* Prekondisi (tidak perlu dicek): */
/* Kode terdiri dari 6 karakter dengan 2 karakter pertama merupakan huruf kapital dan 4 karakter selanjutnya angka. Contoh: IF2111 */
/* Nilai hanya terdiri dari indeks A (4), B (3), C (2), D (1), dan E (0) */
/* I.S. kode, sks, semester, dan nilai terdefinisi */
/* F.S. Mata kuliah MK terbentuk dengan kode, sks, semester, dan nilai yang sesuai */

/* ********** OPERATOR STATISTIK MATA KULIAH ********** */
int SumNilai(ListMatkul L, int semester) {
    IdxType i;
    int nilai = 0;
    if(L.Neff != 0) {
        for(i = 0; i < L.Neff; i++) {
            if(L.contents[i].semester == semester) {
                char n = L.contents[i].nilai;
                if(n == 'A') nilai += (4 * L.contents[i].sks);
                else if(n == 'B') nilai += (3 * L.contents[i].sks);
                else if(n == 'C') nilai += (2 * L.contents[i].sks);
                else if(n == 'D') nilai += (1 * L.contents[i].sks);
            }
        }

    }
    return nilai;
}
/* Prekondisi : List L tidak kosong */
/* Mengembalikan jumlah nilai dalam suatu semester, indeks huruf akan dikonversikan menjadi angka kemudian dikalikan dengan SKS
   konversi dilakukan dgn ketentuan berikut */
/* A: 4, B: 3, C: 2, D: 1, dan E: 0 */

int CountMatkul(ListMatkul L, int semester) {
    IdxType i;
    int count = 0;
    if(L.Neff != 0) {
        for(i = 0; i < L.Neff; i++) {
            if(L.contents[i].semester == semester) count++;
        }
    }
    return count;
}
/* Prekondisi : List L tidak kosong */
/* Mengembalikan jumlah mata kuliah yang diambil dalam suatu semester */

int CountSKS(ListMatkul L, int semester) {
    IdxType i;
    int count = 0;
    if(L.Neff != 0) {
        for(i = 0; i < L.Neff; i++) {
            if(L.contents[i].semester == semester) count += L.contents[i].sks;
        }
    }
    return count;
}
/* Prekondisi : List L tidak kosong */
/* Mengembalikan jumlah SKS dari mata kuliah yang diambil dalam suatu semester */

int CountTotalSKS(ListMatkul L) {
    IdxType i;
    int count = 0;
    if(L.Neff != 0) {
        for(i = 0; i < L.Neff; i++) {
            count += L.contents[i].sks;
        }
    }
    return count;
}
/* Prekondisi : List L tidak kosong */
/* Mengembalikan jumlah SKS dari mata kuliah yang diambil dari seluruh semester */

int MaxSemester(ListMatkul L) {
    IdxType i;
    if(L.Neff != 0) {
        int max = L.contents[0].semester;
        for(i = 0; i < L.Neff; i++) {
            if(max < L.contents[i].semester) max = L.contents[i].semester;
        }

        return max;
    }
    return 0;
}
/* Prekondisi : List L tidak kosong */
/* Mengembalikan semester terakhir yang dijalani dalam list */

float HitungIP(ListMatkul L, int semester) {
    IdxType i;
    float bobot = CountSKS(L, semester), nilai = SumNilai(L, semester);
    if(bobot == 0) return 0;
    return nilai / bobot;
}
/* Prekondisi : List L tidak kosong */
/* Menghitung indeks prestasi semester terakhir yang dijalani */

float HitungIPK(ListMatkul L) {
    IdxType i;
    float smt =  MaxSemester(L);
    float ip = 0.0;
    if(L.Neff == 0) return 0;

    for(i = 1; i <= smt; i++) {
        ip += HitungIP(L, i);
    }

    return ip / smt;
}
/* Prekondisi : List L tidak kosong dan semester awal adalah semester 1 sampai MaxSemester() */
/* Menghitung indeks prestasi kumulatif dari seluruh semester dalam list */
/* Perhitungan IPK dilakukan dengan mencari rata-rata IP seluruh semester */

int CountMatkulLuar(ListMatkul L, char* kodeJur) {
    IdxType i;
    int count = 0;
    if(L.Neff != 0) {
        for (i = 0; i < L.Neff; i++) {
            char* kode = L.contents[i].kode;
            if(kode[0] != kodeJur[0] || kode[1] != kodeJur[1]) count++;
        }
    }
    return count;
}
/* Prekondisi : List L tidak kosong dan kodeJur pasti terdiri dari 2 huruf kapital */
/* Menghitung jumlah mata kuliah luar yang sudah diambil, cara mengetahui mata kuliah luar */
/* adalah dengan mengecek apakah kode matkul berbeda dari kodeJur */
/* Contoh, kodeJur="II" maka IF3120 adalah matkul luar */

void DisplaySIX(ListMatkul L) {
    IdxType i;
    if(L.Neff != 0) {
        printf("IPK: %.2f\n", HitungIPK(L));
        printf("IP: %.2f\n", HitungIP(L, MaxSemester(L)));
        printf("SKS: Sudah Diambil %d SKS\n", CountTotalSKS(L));
        printf("Daftar Kuliah Semester %d:\n", MaxSemester(L));
        for(i = 0; i < L.Neff; i++) {
            if(L.contents[i].semester == MaxSemester(L)) printf("%s(%d) - %d: %c\n", L.contents[i].kode, L.contents[i].sks, L.contents[i].semester, L.contents[i].nilai);
        }
    }
}
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

void test(char *nama, boolean ok) {
    printf("[%s] %s\n", ok ? "PASS" : "FAIL", nama);
}
 
int main() {
    ListMatkul L, L2;
 
    /* ===== MakeEmpty ===== */
    printf("=== MakeEmpty ===\n");
    MakeEmpty(&L);
    test("MakeEmpty - Neff=0", NbElmt(L) == 0);
    test("MakeEmpty - IsEmpty", IsEmpty(L));
    test("MakeEmpty - tidak penuh", !IsFull(L));
    test("MaxNbEl = MAX_CAPACITY", MaxNbEl(L) == MAX_CAPACITY);
 
    /* ===== MakeMatkul + SetEl ===== */
    printf("\n=== MakeMatkul & SetEl ===\n");
    MakeEmpty(&L);
    ElType mk1 = MakeMatkul("IF2111", 3, 3, 'A');
    ElType mk2 = MakeMatkul("IF2212", 3, 4, 'A');
    ElType mk3 = MakeMatkul("II2130", 3, 3, 'B');
    ElType mk4 = MakeMatkul("II2110", 3, 3, 'B');
    SetEl(&L, 0, mk1);
    SetEl(&L, 1, mk2);
    SetEl(&L, 2, mk3);
    SetEl(&L, 3, mk4);
    test("SetEl - Neff=4", NbElmt(L) == 4);
    test("SetEl - GetElmt idx 0 kode IF2111", strcmp(GetElmt(L, 0).kode, "IF2111") == 0);
    test("SetEl - GetElmt idx 0 sks=3", GetElmt(L, 0).sks == 3);
    test("SetEl - GetElmt idx 0 nilai=A", GetElmt(L, 0).nilai == 'A');
 
    /* ===== GetFirstIdx / GetLastIdx ===== */
    printf("\n=== Selektor Indeks ===\n");
    test("GetFirstIdx = 0", GetFirstIdx(L) == 0);
    test("GetLastIdx = 3", GetLastIdx(L) == 3);
 
    /* ===== IsIdxValid / IsIdxEff ===== */
    test("IsIdxValid 0 = true", IsIdxValid(L, 0));
    test("IsIdxValid 99 = true", IsIdxValid(L, 99));
    test("IsIdxValid -1 = false", !IsIdxValid(L, -1));
    test("IsIdxValid 100 = false", !IsIdxValid(L, 100));
    test("IsIdxEff 3 = true", IsIdxEff(L, 3));
    test("IsIdxEff 4 = false (di luar Neff)", !IsIdxEff(L, 4));
 
    /* ===== SetNeff ===== */
    SetNeff(&L, 4);
    test("SetNeff - Neff=4", NbElmt(L) == 4);
 
    /* ===== SetTab ===== */
    printf("\n=== SetTab ===\n");
    SetTab(L, &L2);
    test("SetTab - Neff sama", NbElmt(L2) == NbElmt(L));
    test("SetTab - isi sama", strcmp(GetElmt(L2, 0).kode, "IF2111") == 0);
 
    /* ===== PrintIsi ===== */
    printf("\n=== PrintIsi ===\n");
    printf("Expected:\nIF2111(3) - 3: A\nIF2212(3) - 4: A\nII2130(3) - 3: B\nII2110(3) - 3: B\n");
    printf("Got:\n");
    PrintIsi(L);
 
    MakeEmpty(&L2);
    printf("List kosong test: ");
    PrintIsi(L2);
 
    /* ===== Setup data lebih lengkap untuk statistik ===== */
    /* Semester 1: IF1210(3,A), IF1110(3,B), MA1101(4,B) */
    /* Semester 2: IF2110(3,A), IF2120(3,B), MA2111(3,C) */
    /* Semester 3: IF2111(3,A), II2130(3,B), II2110(3,B) */
    MakeEmpty(&L);
    SetEl(&L, 0, MakeMatkul("IF1210", 3, 1, 'A')); /* sem1: 3*4=12 */
    SetEl(&L, 1, MakeMatkul("IF1110", 3, 1, 'B')); /* sem1: 3*3=9  */
    SetEl(&L, 2, MakeMatkul("MA1101", 4, 1, 'B')); /* sem1: 4*3=12 */
    SetEl(&L, 3, MakeMatkul("IF2110", 3, 2, 'A')); /* sem2: 3*4=12 */
    SetEl(&L, 4, MakeMatkul("IF2120", 3, 2, 'B')); /* sem2: 3*3=9  */
    SetEl(&L, 5, MakeMatkul("MA2111", 3, 2, 'C')); /* sem2: 3*2=6  */
    SetEl(&L, 6, MakeMatkul("IF2111", 3, 3, 'A')); /* sem3: 3*4=12 */
    SetEl(&L, 7, MakeMatkul("II2130", 3, 3, 'B')); /* sem3: 3*3=9  */
    SetEl(&L, 8, MakeMatkul("II2110", 3, 3, 'B')); /* sem3: 3*3=9  */
 
    /* ===== CountMatkul ===== */
    printf("\n=== CountMatkul ===\n");
    test("CountMatkul sem1 = 3", CountMatkul(L, 1) == 3);
    test("CountMatkul sem2 = 3", CountMatkul(L, 2) == 3);
    test("CountMatkul sem3 = 3", CountMatkul(L, 3) == 3);
    test("CountMatkul sem4 = 0 (tidak ada)", CountMatkul(L, 4) == 0);
 
    /* ===== CountSKS ===== */
    printf("\n=== CountSKS ===\n");
    /* sem1: 3+3+4=10, sem2: 3+3+3=9, sem3: 3+3+3=9 */
    test("CountSKS sem1 = 10", CountSKS(L, 1) == 10);
    test("CountSKS sem2 = 9", CountSKS(L, 2) == 9);
    test("CountSKS sem3 = 9", CountSKS(L, 3) == 9);
 
    /* ===== CountTotalSKS ===== */
    printf("\n=== CountTotalSKS ===\n");
    test("CountTotalSKS = 28", CountTotalSKS(L) == 28);
 
    /* ===== SumNilai ===== */
    printf("\n=== SumNilai ===\n");
    /* sem1: 12+9+12=33, sem2: 12+9+6=27, sem3: 12+9+9=30 */
    test("SumNilai sem1 = 33", SumNilai(L, 1) == 33);
    test("SumNilai sem2 = 27", SumNilai(L, 2) == 27);
    test("SumNilai sem3 = 30", SumNilai(L, 3) == 30);
 
    /* ===== MaxSemester ===== */
    printf("\n=== MaxSemester ===\n");
    test("MaxSemester = 3", MaxSemester(L) == 3);
 
    /* ===== HitungIP ===== */
    printf("\n=== HitungIP ===\n");
    /* IP sem1 = 33/10 = 3.30, sem2 = 27/9 = 3.00, sem3 = 30/9 = 3.33 */
    float ip1 = HitungIP(L, 1);
    float ip2 = HitungIP(L, 2);
    float ip3 = HitungIP(L, 3);
    printf("IP sem1 = %.2f (expected 3.30)\n", ip1);
    printf("IP sem2 = %.2f (expected 3.00)\n", ip2);
    printf("IP sem3 = %.2f (expected 3.33)\n", ip3);
    test("HitungIP sem1 = 3.30", ip1 > 3.29f && ip1 < 3.31f);
    test("HitungIP sem2 = 3.00", ip2 > 2.99f && ip2 < 3.01f);
    test("HitungIP sem3 = 3.33", ip3 > 3.32f && ip3 < 3.34f);
 
    /* ===== HitungIPK ===== */
    printf("\n=== HitungIPK ===\n");
    /* IPK = (3.30 + 3.00 + 3.33) / 3 = 3.21 */
    float ipk = HitungIPK(L);
    printf("IPK = %.2f (expected 3.21)\n", ipk);
    test("HitungIPK ~= 3.21", ipk > 3.20f && ipk < 3.22f);
 
    /* ===== CountMatkulLuar ===== */
    printf("\n=== CountMatkulLuar ===\n");
    /* kodeJur="IF": II2130, II2110, MA1101, MA2111 = 4 matkul luar */
    test("CountMatkulLuar IF = 4", CountMatkulLuar(L, "IF") == 4);
    /* kodeJur="II": IF1210,IF1110,MA1101,IF2110,IF2120,MA2111,IF2111 = 7 luar */
    test("CountMatkulLuar II = 7", CountMatkulLuar(L, "II") == 7);
    /* kodeJur="MA": semua non-MA = 7 */
    test("CountMatkulLuar MA = 7", CountMatkulLuar(L, "MA") == 7);
 
    /* ===== DisplaySIX ===== */
    printf("\n=== DisplaySIX ===\n");
    printf("Expected:\nIPK: 3.21\nIP: 3.33\nSKS: Sudah Diambil 28 SKS\nDaftar Kuliah Semester 3:\nIF2111(3) - 3: A\nII2130(3) - 3: B\nII2110(3) - 3: B\n");
    printf("Got:\n");
    DisplaySIX(L);
 
    printf("\n===== SELESAI =====\n");
    return 0;
}
 