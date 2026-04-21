#ifndef HITUNG_INDEKS_H
#define HITUNG_INDEKS_H

#include <stdbool.h>
#include <string.h>

/* Kamus Umum */
#define MAX_NUM_MATKUL 100
#define MAX_NAME_LEN 50

typedef struct {
    char NamaMatkul[MAX_NUM_MATKUL][MAX_NAME_LEN];
    float Nilai[MAX_NUM_MATKUL];
    int SKS[MAX_NUM_MATKUL];
    int Kehadiran[MAX_NUM_MATKUL];
    char Indeks[MAX_NUM_MATKUL];
    int NEff;
} Transkrip;


void BuatTranskrip (Transkrip *T);
/* Membuat transkrip kosong
 I.S. T sembarang
 F.S. Terbentuk transkrip T kosong */

int AmbilJumlahMatkul (Transkrip T);
/* Mengembalikan banyaknya mata kuliah pada transkrip */

void AmbilMatkul (Transkrip *T, char *nama, float nilai, int sks, int kehadiran);
/* Menambahkan matkul pada transkrip jika masih ada kapasitas mata kuliah pada transkrip dan data mata kuliah valid.
   Nilai dan kehadiran berada pada range 0-100, sks berada pada range 1-4, dan nama tidak boleh kosong. */

float HitungNilai (Transkrip T, int i);
/* Mengembalikan nilai mata kuliah pada indeks ke-i yang sudah memperhitungkan nilai mentah sebesar 95% dan nilai kehadiran sebesar 5%.
 Jika mata kuliah tidak ditemukan pada transkrip, kembalikan -1 */

char HitungIndeks (Transkrip T, int i);
/* Mengembalikan nilai mata kuliah pada indeks ke-i yang sudah diterjemahkan ke dalam indeks
    Dengan ketentuan indeks sebagai berikut:
    A: 100.0 >= nilai >= 80.0
    B: nilai >= 70.0
    C: nilai >= 60.0
    D: nilai >= 50.0
    E: 0 =< nilai < 50.0
Jika mata kuliah tidak ditemukan pada transkrip atau nilainya tidak valid, kembalikan '-' */

void SimpanIndeks (Transkrip *T);
/* Memasukkan data indeks tiap matkul pada transkrip */

char HitungIndeksTotal (Transkrip T);
/* Mengembalikan indeks keseluruhan mata kuliah berdasarkan transkrip.
   Fungsi ini akan memanggil SimpanIndeks secara internal sebelum menghitung.
    1. Konversi indeks tiap matkul ke poin, jika ada indeks yang tidak valid, maka poinnya dianggap 0.0
        A = 4.0, B = 3.0, C = 2.0, D = 1.0, E = 0.0
    2. Hitung rata-rata:
        (Total (SKS * poin)) / Total SKS
    3. Tentukan indeks total berdasarkan range IP berikut:
        A: 3.5 <= IP <= 4.0
        B: 2.5 <= IP < 3.5
        C: 1.5 <= IP < 2.5
        D: 0.5 <= IP < 1.5
        E: 0.0 <= IP < 0.5
Jika tidak ada mata kuliah pada transkrip atau hasil tidak valid, kembalikan '-' */

bool CekKelulusan (Transkrip T);
/* Mengembalikan nilai true jika pemilik transkrip ini lulus (indeks total >= C) */

void CetakTranskrip (Transkrip T);
/* Mencetak data transkrip dengan format (akhiri dengan newline):
    Mata Kuliah: <Nama Mata Kuliah ke-1>
    Nilai: <Nilai Mata Kuliah ke-1>
    Indeks: <Indeks Mata Kuliah ke-1>

    Mata Kuliah: <Nama Mata Kuliah ke-2>
    Nilai: <Nilai Mata Kuliah ke-2>
    Indeks: <Indeks Mata Kuliah ke-2>

    ...

    Mata Kuliah: <Nama Mata Kuliah ke-N>
    Nilai: <Nilai Mata Kuliah ke-N>
    Indeks: <Indeks Mata Kuliah ke-N>

    Indeks Akhir: <Indeks Akhir pada Transkrip>
    Status Kelulusan: <"LULUS" / "TIDAK LULUS">
Perhatikan bahwa nilai disini adalah nilai yang MEMPERHITUNGKAN KEHADIRAN dan ambil dua angka dibelakang koma.
Jika transkrip tidak memiliki mata kuliah, cetak "Transkrip masih kosong" */

#endif