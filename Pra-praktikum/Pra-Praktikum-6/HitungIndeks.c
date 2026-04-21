#include <stdio.h>
#include "HitungIndeks.h"

void BuatTranskrip (Transkrip *T) {
    T->NEff = 0;
}
/* Membuat transkrip kosong
 I.S. T sembarang
 F.S. Terbentuk transkrip T kosong */

int AmbilJumlahMatkul (Transkrip T) {
    return T.NEff;
}
/* Mengembalikan banyaknya mata kuliah pada transkrip */

void AmbilMatkul (Transkrip *T, char *nama, float nilai, int sks, int kehadiran) {
    if (T->NEff >= MAX_NUM_MATKUL) return;
    if (strlen(nama) == 0) return;
    if (nilai < 0 || nilai > 100) return;
    if (sks < 1 || sks > 4) return;
    if (kehadiran < 0 || kehadiran > 100) return;
 
    strcpy(T->NamaMatkul[T->NEff], nama);
    T->Nilai[T->NEff] = nilai;
    T->SKS[T->NEff] = sks;
    T->Kehadiran[T->NEff] = kehadiran;
    T->Indeks[T->NEff] = '-';
    T->NEff++;
}
/* Menambahkan matkul pada transkrip jika masih ada kapasitas mata kuliah pada transkrip dan data mata kuliah valid.
   Nilai dan kehadiran berada pada range 0-100, sks berada pada range 1-4, dan nama tidak boleh kosong. */

float HitungNilai (Transkrip T, int i) {
    if(i >= 0 && i < T.NEff) return (0.95 * T.Nilai[i]) + (0.05 * T.Kehadiran[i]);
    return -1.0;
}
/* Mengembalikan nilai mata kuliah pada indeks ke-i yang sudah memperhitungkan nilai mentah sebesar 95% dan nilai kehadiran sebesar 5%.
 Jika mata kuliah tidak ditemukan pada transkrip, kembalikan -1 */

char HitungIndeks (Transkrip T, int i) {
    if(i < 0 || i >= T.NEff) return '-';
    else {
        float nilai = HitungNilai(T, i);
        if (nilai >= 80.0 && nilai <= 100.0) return 'A';
        else if (nilai >= 70.0) return 'B';
        else if (nilai >= 60.0) return 'C';
        else if (nilai >= 50.0) return 'D';
        else if(nilai >= 0.0) return 'E';
        else return '-';
    }
}
/* Mengembalikan nilai mata kuliah pada indeks ke-i yang sudah diterjemahkan ke dalam indeks
    Dengan ketentuan indeks sebagai berikut:
    A: 100.0 >= nilai >= 80.0
    B: nilai >= 70.0
    C: nilai >= 60.0
    D: nilai >= 50.0
    E: 0 =< nilai < 50.0
Jika mata kuliah tidak ditemukan pada transkrip atau nilainya tidak valid, kembalikan '-' */

void SimpanIndeks (Transkrip *T) {
    int i;
    for(i = 0; i < T->NEff; i++) {
        T->Indeks[i] = HitungIndeks(*T, i);
    }
}
/* Memasukkan data indeks tiap matkul pada transkrip */

char HitungIndeksTotal (Transkrip T) {
    int i;
    float total = 0.0, rerata, skstot = 0.0;
    float epsilon = 0.00001;
    if (T.NEff == 0) return '-';
    SimpanIndeks(&T);

    for(i = 0; i < T.NEff; i++) {
        skstot += (float)T.SKS[i];
        if(T.Indeks[i] == 'A') total += ((float)T.SKS[i] * 4.0);
        else if(T.Indeks[i] == 'B') total += ((float)T.SKS[i] * 3.0);
        else if(T.Indeks[i] == 'C') total += ((float)T.SKS[i] * 2.0);
        else if(T.Indeks[i] == 'D') total += ((float)T.SKS[i] * 1.0);
    }
    if (skstot == 0) return '-';
    rerata = (total / skstot) + epsilon;
    if(rerata >= 3.5) return 'A';
    else if(rerata >= 2.5) return 'B';
    else if(rerata >= 1.5) return 'C';
    else if(rerata >= 0.5) return 'D';
    else if(rerata >= 0.0) return 'E';
    else return '-';
}
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

bool CekKelulusan (Transkrip T) {
    char indeks = HitungIndeksTotal(T);
    return (indeks == 'A' || indeks == 'B' || indeks == 'C');
}
/* Mengembalikan nilai true jika pemilik transkrip ini lulus (indeks total >= C) */

void CetakTranskrip (Transkrip T) {
    int i;
    if(T.NEff == 0) {
        printf("Transkrip masih kosong\n");
        return;
    }

    SimpanIndeks(&T);
    
    for(i = 0; i < T.NEff; i++) {
        printf("Mata Kuliah: %s\n", T.NamaMatkul[i]);
        printf("Nilai: %.2f\n", HitungNilai(T, i));
        printf("Indeks: %c\n", T.Indeks[i]);
        printf("\n");
    }

    printf("Indeks Akhir: %c\n", HitungIndeksTotal(T));
    printf("Status Kelulusan: ");
    if(CekKelulusan(T)) printf("LULUS\n");
    else printf("TIDAK LULUS\n");
}
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
