#ifndef SOAL1_PANGKAT_H
#define SOAL1_PANGKAT_H

/*
 * ============================================================
 *  SOAL 1 — PANGKAT MATRIKS (Matrix Power)
 *  File   : soal1_pangkat.h
 *  Depend : matriks.h, boolean.h
 * ============================================================
 *
 *  LATAR BELAKANG
 *  --------------
 *  Pangkat matriks A^p didefinisikan sebagai perkalian A
 *  dengan dirinya sendiri sebanyak p kali:
 *
 *      A^0 = I   (matriks identitas)
 *      A^1 = A
 *      A^p = A^(p-1) x A   untuk p >= 2
 *
 *  Operasi ini banyak digunakan pada:
 *    - Komputasi barisan Fibonacci secara efisien
 *    - Rantai Markov (Markov chains)
 *    - Graf — jumlah jalur panjang-k antar simpul
 *
 *  KETERGANTUNGAN
 *  --------------
 *  Modul ini menggunakan fungsi-fungsi yang telah ada di
 *  matriks.h:
 *    - BuatMatriks, HapusMatriks, SalinMatriks
 *    - MatriksIdentitas
 *    - PerkalianMatriks
 * ============================================================
 */

#include "matriks.h"

/* ------------------------------------------------------------
 *  PANGKAT MATRIKS — ITERATIF
 * ------------------------------------------------------------ */

void PangkatMatriks (Matriks A, int p, Matriks *Hasil) {
    /* Menghitung A^p secara iteratif dan menyimpan hasilnya ke *Hasil */
    
    // 1. Inisialisasi Hasil menjadi matriks Identitas (Basis: A^0 = I)
    MatriksIdentitas(Hasil);
    
    if (p > 0) {
        // 2. Alokasikan matriks sementara Temp berukuran N x N
        Matriks Temp;
        BuatMatriks(&Temp, A.N);
        
        // 3. Untuk k = 1 hingga p:
        for (int k = 1; k <= p; k++) {
            /* PerkalianMatriks tidak boleh menerima Hasil sebagai 
               parameter ketiga sekaligus pertama/kedua (aliasing) */
            PerkalianMatriks(*Hasil, A, &Temp);
            
            // Salin isi matriks sementara kembali ke matriks Hasil
            SalinMatriks(Temp, Hasil);
        }
        
        // 4. Bebaskan memori matriks sementara
        HapusMatriks(&Temp);
    }
}
/*
 * Menghitung A^p secara iteratif dan menyimpan hasilnya ke *Hasil.
 *
 * I.S. : A terdefinisi dan berukuran N x N.
 *         p >= 0 (bilangan bulat non-negatif).
 *         *Hasil sudah dialokasikan dengan Hasil->N = A.N.
 *
 * F.S. : *Hasil = A^p, di mana:
 *           - p = 0  →  *Hasil adalah matriks identitas N x N
 *           - p = 1  →  *Hasil = A
 *           - p > 1  →  *Hasil = A x A x ... x A  (p kali)
 *
 * Algoritma (pseudocode):
 *   1. Inisialisasi Hasil ← I  (gunakan MatriksIdentitas)
 *   2. Alokasikan matriks sementara Temp berukuran N x N
 *   3. Untuk k = 1 hingga p:
 *        PerkalianMatriks(Hasil, A, &Temp)
 *        SalinMatriks(Temp, &Hasil)
 *   4. Bebaskan Temp
 *
 * Catatan implementasi:
 *   - Gunakan matriks sementara (Temp) agar tidak terjadi
 *     aliasing saat memanggil PerkalianMatriks.
 *   - PerkalianMatriks tidak boleh menerima Hasil sebagai
 *     parameter ketiga sekaligus pertama/kedua.
 *
 * Kompleksitas waktu : O(p * N^3)
 * Kompleksitas ruang : O(N^2) — satu matriks sementara
 */

/* ------------------------------------------------------------
 *  PANGKAT MATRIKS — REKURSIF (fast exponentiation)
 * ------------------------------------------------------------ */

void PangkatMatriksRekursif (Matriks A, int p, Matriks *Hasil) {
    /* Menghitung A^p menggunakan eksponensiasi cepat (fast power)  */
    
    // Basis 1: A^0 = I (Matriks Identitas) 
    if (p == 0) {
        MatriksIdentitas(Hasil);
    }
    // Basis 2: A^1 = A 
    else if (p == 1) {
        SalinMatriks(A, Hasil);
    }
    else {
        Matriks Temp, Temp2;
        BuatMatriks(&Temp, A.N);
        BuatMatriks(&Temp2, A.N);

        // Rekursi: Hitung A^(p/2) 
        PangkatMatriksRekursif(A, p / 2, &Temp);

        // Langkah p genap: A^p = (A^(p/2))^2 
        if (p % 2 == 0) {
            PerkalianMatriks(Temp, Temp, Hasil);
        }
        // Langkah p ganjil: A^p = A x (A^(p/2))^2 
        else {
            PerkalianMatriks(Temp, Temp, &Temp2);
            PerkalianMatriks(A, Temp2, Hasil);
        }

        HapusMatriks(&Temp);
        HapusMatriks(&Temp2);
    }
}
/*
 * Menghitung A^p menggunakan eksponensiasi cepat (fast power):
 *
 *   A^p = I                      jika p = 0
 *   A^p = A                      jika p = 1
 *   A^p = (A^(p/2))^2            jika p genap
 *   A^p = A x (A^(p/2))^2       jika p ganjil
 *
 * I.S. : Sama dengan PangkatMatriks.
 * F.S. : *Hasil = A^p.
 *
 * Kompleksitas waktu : O(log(p) * N^3)
 * Kompleksitas ruang : O(log(p) * N^2) — tumpukan rekursi
 *
 * Pertanyaan refleksi:
 *   Mengapa versi rekursif lebih efisien untuk p besar?
 */

/* ------------------------------------------------------------
 *  PREDIKAT & UTILITAS
 * ------------------------------------------------------------ */

boolean MatriksIdempoten (Matriks A) {
    
    return PerkalianMatriks(A, A)
}
/*
 * Mengembalikan true jika A^2 = A  (matriks idempoten).
 *
 * I.S. : A terdefinisi.
 * F.S. : Nilai kebenaran idempoten dikembalikan.
 *         Gunakan PangkatMatriks(A, 2, &A2) lalu MatriksSetara.
 *
 * Catatan: Matriks proyeksi ortogonal bersifat idempoten.
 */

boolean MatriksNilpoten (Matriks A, int k);
/*
 * Mengembalikan true jika A^k = 0  (matriks nilpoten orde k).
 *
 * I.S. : A terdefinisi, k >= 1.
 * F.S. : true jika A^k adalah matriks nol (semua elemen < EPSILON).
 *
 * Petunjuk: hitung A^k, lalu periksa setiap elemen apakah
 *           |elemen| < EPSILON.
 */

/* ============================================================
 *  SOAL LATIHAN
 * ============================================================
 *
 *  [1] Implementasikan PangkatMatriks secara iteratif.
 *      Hitung jumlah pemanggilan PerkalianMatriks untuk p=5.
 *
 *  [2] Implementasikan PangkatMatriksRekursif.
 *      Hitung jumlah pemanggilan PerkalianMatriks untuk p=5.
 *      Bandingkan hasilnya dengan [1].
 *
 *  [3] Tunjukkan dengan perhitungan tangan bahwa A^0 = I
 *      untuk A = | 3  7 |
 *                | 0  2 |
 *
 *  [4] Hitung A^2 dan A^3 untuk:
 *      A = | 1  2 |
 *          | 0  1 |
 *      Apakah A bersifat nilpoten? Apakah A bersifat idempoten?
 *
 *  [5] Buktikan: jika A simetris, apakah A^p juga selalu simetris?
 *      Uji dengan A = | 2  1 |  dan p = 3.
 *                     | 1  3 |
 *
 *  PETUNJUK DEBUGGING
 *  ------------------
 *  - Cetak Hasil setelah setiap iterasi menggunakan CetakMatriks.
 *  - Periksa apakah PangkatMatriks(A, 0, &H) menghasilkan I.
 *  - Pastikan Temp dibebaskan setelah digunakan (HapusMatriks).
 * ============================================================
 */

#endif /* SOAL1_PANGKAT_H */
