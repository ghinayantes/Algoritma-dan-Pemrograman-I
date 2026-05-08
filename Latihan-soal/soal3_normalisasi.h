#ifndef SOAL3_NORMALISASI_H
#define SOAL3_NORMALISASI_H

/*
 * ============================================================
 *  SOAL 3 — NORMALISASI BARIS DAN NORMA MATRIKS
 *  File   : soal3_normalisasi.h
 *  Depend : matriks.h, boolean.h, <math.h>
 * ============================================================
 *
 *  LATAR BELAKANG
 *  --------------
 *  Norma adalah ukuran "panjang" suatu vektor atau matriks.
 *
 *  Norma Euclidean (L2) sebuah baris:
 *      ||v||_2 = sqrt(v[0]^2 + v[1]^2 + ... + v[N-1]^2)
 *
 *  Normalisasi baris: membagi setiap elemen baris dengan norma
 *  sehingga baris tersebut menjadi vektor satuan (unit vector):
 *      ||v_normalized||_2 = 1.0
 *
 *  Norma Frobenius matriks A:
 *      ||A||_F = sqrt( sigma sigma A[i][j]^2 )
 *                      i     j
 *    = sqrt( trace(A^T x A) )
 *
 *  Norma-1 matriks (column sum norm):
 *      ||A||_1 = max_j ( sigma |A[i][j]| )
 *                              i
 *
 *  Norma-tak-hingga matriks (row sum norm):
 *      ||A||_inf = max_i ( sigma |A[i][j]| )
 *                               j
 *
 *  KETERGANTUNGAN
 *  --------------
 *    - BuatMatriks, HapusMatriks
 *    - PerkalianSkalar  (untuk normalisasi in-place)
 *    - <math.h>: sqrt, fabs
 * ============================================================
 */

#include "matriks.h"
#include <math.h>

/* ------------------------------------------------------------
 *  NORMA BARIS
 * ------------------------------------------------------------ */

ElMatriks NormaBaris (Matriks A, int i);
/*
 * Mengembalikan norma Euclidean (L2) baris ke-i dari A.
 *
 * I.S. : A terdefinisi, 0 <= i < A.N.
 * F.S. : Mengembalikan sqrt( sigma A.M[i][j]^2 ) untuk j=0..N-1.
 *
 * Contoh:
 *   A = | 3  4 |  →  NormaBaris(A, 0) = sqrt(9+16) = 5.0
 *       | 0  0 |  →  NormaBaris(A, 1) = 0.0
 */

ElMatriks NormaKolom (Matriks A, int j);
/*
 * Mengembalikan norma Euclidean kolom ke-j dari A.
 *
 * I.S. : A terdefinisi, 0 <= j < A.N.
 * F.S. : Mengembalikan sqrt( sigma A.M[i][j]^2 ) untuk i=0..N-1.
 */

/* ------------------------------------------------------------
 *  NORMALISASI
 * ------------------------------------------------------------ */

boolean NormalisasiBaris (Matriks *A);
/*
 * Menormalisasi setiap baris A secara in-place.
 *
 * I.S. : A terdefinisi.
 * F.S. : Untuk setiap baris i:
 *           - Jika NormaBaris(A,i) > EPSILON:
 *               A.M[i][j] = A.M[i][j] / NormaBaris(A,i)
 *           - Jika ada baris nol (norma <= EPSILON):
 *               A tidak diubah sama sekali, return false.
 *         Jika semua baris berhasil dinormalisasi: return true.
 *
 * Catatan: Periksa semua norma terlebih dahulu sebelum mengubah
 *           elemen manapun (untuk atomisitas operasi).
 *
 * Kompleksitas waktu : O(N^2)
 */

boolean NormalisasiKolom (Matriks *A);
/*
 * Menormalisasi setiap kolom A secara in-place.
 * Serupa dengan NormalisasiBaris, tetapi per kolom.
 *
 * I.S. : A terdefinisi.
 * F.S. : Setiap kolom j memiliki norma = 1.0, atau return false
 *         jika ada kolom nol.
 */

/* ------------------------------------------------------------
 *  NORMA MATRIKS
 * ------------------------------------------------------------ */

ElMatriks FrobeniusNorm (Matriks A);
/*
 * Menghitung norma Frobenius dari A.
 *
 * I.S. : A terdefinisi.
 * F.S. : Mengembalikan sqrt( sigma sigma A.M[i][j]^2 ).
 *                              i     j
 *
 * Properti:
 *   - ||I||_F = sqrt(N)  (matriks identitas NxN)
 *   - ||A||_F = ||A^T||_F  (invarian transpose)
 *   - ||kA||_F = |k| * ||A||_F  (homogenitas)
 *
 * Kompleksitas waktu : O(N^2)
 */

ElMatriks NormaSatu (Matriks A);
/*
 * Menghitung norma-1 (column sum norm) dari A.
 *
 * I.S. : A terdefinisi.
 * F.S. : Mengembalikan max_j ( sigma |A.M[i][j]| )
 *                                    i
 *
 * Algoritma:
 *   Untuk setiap kolom j, hitung jumlah |A[i][j]|.
 *   Kembalikan nilai maksimum di antara semua kolom.
 */

ElMatriks NormaTakHingga (Matriks A);
/*
 * Menghitung norma-tak-hingga (row sum norm) dari A.
 *
 * I.S. : A terdefinisi.
 * F.S. : Mengembalikan max_i ( sigma |A.M[i][j]| )
 *                                    j
 *
 * Algoritma:
 *   Untuk setiap baris i, hitung jumlah |A[i][j]|.
 *   Kembalikan nilai maksimum di antara semua baris.
 */

/* ------------------------------------------------------------
 *  KONDISI BILANGAN (CONDITION NUMBER)
 * ------------------------------------------------------------ */

ElMatriks NomorKondisi (Matriks A, Matriks AInv);
/*
 * Menghitung condition number menggunakan norma Frobenius:
 *     cond(A) = ||A||_F * ||A^(-1)||_F
 *
 * I.S. : A dan AInv terdefinisi (AInv adalah invers A).
 * F.S. : Mengembalikan FrobeniusNorm(A) * FrobeniusNorm(AInv).
 *
 * Interpretasi:
 *   - cond(A) ≈ 1    : matriks terkondisi baik (well-conditioned)
 *   - cond(A) >> 1   : matriks terkondisi buruk (ill-conditioned)
 *   - cond(I) = 1    : kondisi terbaik
 */

/* ============================================================
 *  SOAL LATIHAN
 * ============================================================
 *
 *  [1] Implementasikan NormaBaris dan NormaKolom.
 *      Hitung NormaBaris untuk setiap baris:
 *          | 1   0   0 |
 *      A = | 3   4   0 |
 *          | 0   0   5 |
 *
 *  [2] Implementasikan NormalisasiBaris.
 *      Mengapa perlu memeriksa semua norma sebelum mengubah
 *      elemen manapun? Apa konsekuensinya jika tidak?
 *
 *  [3] Implementasikan FrobeniusNorm.
 *      Verifikasi: FrobeniusNorm(I_3) = sqrt(3) ≈ 1.732.
 *
 *  [4] Implementasikan NormaSatu dan NormaTakHingga.
 *      Hitung keduanya untuk:
 *          | 1  -2   3 |
 *      A = | 4   5  -6 |
 *          | 7  -8   9 |
 *      (Petunjuk: norma-tak-hingga = max baris = 7+8+9 = 24)
 *
 *  [5] Setelah NormalisasiBaris(A) dipanggil, apa yang terjadi
 *      jika dipanggil lagi? Apakah hasilnya sama? Mengapa?
 *
 *  PETUNJUK DEBUGGING
 *  ------------------
 *  - Gunakan printf("%.6f\n", NormaBaris(A, i)) untuk validasi.
 *  - Setelah NormalisasiBaris: NormaBaris(A, i) harus = 1.0
 *    (dalam toleransi EPSILON).
 *  - Baris nol: norma = 0.0, pembagian akan menghasilkan NaN.
 *    Itulah mengapa perlu pengecekan SEBELUM pembagian.
 * ============================================================
 */

#endif /* SOAL3_NORMALISASI_H */
