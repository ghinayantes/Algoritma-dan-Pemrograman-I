#ifndef SOAL4_SIMETRIS_H
#define SOAL4_SIMETRIS_H

/*
 * ============================================================
 *  SOAL 4 — MATRIKS SIMETRIS, DEKOMPOSISI, DAN NORMA
 *  File   : soal4_simetris.h
 *  Depend : matriks.h, boolean.h, <math.h>
 * ============================================================
 *
 *  LATAR BELAKANG
 *  --------------
 *  Setiap matriks persegi A dapat didekomposisi menjadi bagian
 *  simetris dan anti-simetris (skew-symmetric):
 *
 *      A = S + K
 *
 *  di mana:
 *      S = (A + A^T) / 2   ← matriks simetris (S^T = S)
 *      K = (A - A^T) / 2   ← matriks anti-simetris (K^T = -K)
 *
 *  Dekomposisi ini unik dan berlaku untuk sembarang matriks.
 *
 *  MATRIKS DEFINIT POSITIF
 *  -----------------------
 *  Matriks simetris A disebut definit positif (positive definite)
 *  jika untuk setiap vektor x ≠ 0:
 *      x^T A x > 0
 *
 *  Syarat perlu dan cukup (kriteria Sylvester):
 *  Semua minor utama (leading principal minor) harus positif:
 *      det(A[0..0][0..0]) > 0
 *      det(A[0..1][0..1]) > 0
 *      det(A[0..2][0..2]) > 0
 *      ...
 *      det(A) > 0
 *
 *  MATRIKS ORTOGONAL
 *  -----------------
 *  Matriks A disebut ortogonal jika:
 *      A^T x A = I   ↔   A^T = A^(-1)
 *
 *  Properti: det(A) = ±1, semua nilai eigen bernilai ±1.
 *
 *  KETERGANTUNGAN
 *  --------------
 *    - BuatMatriks, HapusMatriks, SalinMatriks
 *    - TransposeMatriks, PenjumlahanMatriks, PerkalianMatriks
 *    - PerkalianSkalar, MatriksSetara, MatriksSimetris
 *    - DeterminanMatriks, MatriksIdentitas
 * ============================================================
 */

#include "matriks.h"

/* ------------------------------------------------------------
 *  DEKOMPOSISI SIMETRIS / ANTI-SIMETRIS
 * ------------------------------------------------------------ */

void BuatMatriksSimetris (Matriks A, Matriks *S);
/*
 * Menghasilkan bagian simetris dari A: S = (A + A^T) / 2.
 *
 * I.S. : A terdefinisi.
 *         *S sudah dialokasikan dengan S->N = A.N.
 *
 * F.S. : S->M[i][j] = (A.M[i][j] + A.M[j][i]) / 2
 *         untuk semua 0 <= i,j < A.N.
 *
 * Algoritma menggunakan fungsi yang ada:
 *   1. TransposeMatriks(A, &AT)          — hitung A^T
 *   2. PenjumlahanMatriks(A, AT, S)      — S = A + A^T
 *   3. PerkalianSkalar(S, 0.5)           — S = (A + A^T) / 2
 *   4. HapusMatriks(&AT)
 *
 * Verifikasi: MatriksSimetris(*S) harus mengembalikan true.
 * Kompleksitas waktu : O(N^2)
 */

void BuatMatriksAntiSimetris (Matriks A, Matriks *K);
/*
 * Menghasilkan bagian anti-simetris dari A: K = (A - A^T) / 2.
 *
 * I.S. : A terdefinisi.
 *         *K sudah dialokasikan dengan K->N = A.N.
 *
 * F.S. : K->M[i][j] = (A.M[i][j] - A.M[j][i]) / 2.
 *         K^T = -K  (anti-simetris/skew-symmetric).
 *
 * Properti: elemen diagonal K selalu bernilai 0.
 *
 * Catatan: Tidak ada fungsi pengurangan matriks di matriks.h.
 *           Hitung secara langsung: K->M[i][j] = (A.M[i][j] - A.M[j][i])*0.5
 */

void VerifikasiDekomposisi (Matriks A, Matriks S, Matriks K, boolean *ok);
/*
 * Memverifikasi bahwa A = S + K (dalam batas EPSILON).
 *
 * I.S. : A, S, K terdefinisi berukuran sama.
 * F.S. : *ok = true jika MatriksSetara(A, S+K).
 *
 * Petunjuk: Alokasikan Temp, PenjumlahanMatriks(S, K, &Temp),
 *            *ok = MatriksSetara(A, Temp), HapusMatriks(&Temp).
 */

/* ------------------------------------------------------------
 *  SIFAT DEFINIT POSITIF
 * ------------------------------------------------------------ */

void SubMatriksUtama (Matriks A, int k, Matriks *Sub);
/*
 * Mengekstrak minor utama ke-k (leading principal minor).
 * Sub adalah submatriks k x k dari pojok kiri atas A.
 *
 * I.S. : A terdefinisi, 1 <= k <= A.N.
 *         *Sub sudah dialokasikan dengan Sub->N = k.
 *
 * F.S. : Sub->M[i][j] = A.M[i][j] untuk 0 <= i,j < k.
 *
 * Kompleksitas waktu : O(k^2)
 */

boolean MatriksDefinitPositif (Matriks A);
/*
 * Mengembalikan true jika A simetris DAN definit positif.
 *
 * I.S. : A terdefinisi.
 * F.S. : true jika:
 *   (a) MatriksSimetris(A), DAN
 *   (b) det(SubMatriksUtama(A, k)) > EPSILON untuk k = 1..N
 *
 * Algoritma (kriteria Sylvester):
 *   Jika tidak simetris: return false.
 *   Untuk k = 1 hingga A.N:
 *     Alokasikan Sub berukuran k.
 *     SubMatriksUtama(A, k, &Sub).
 *     Jika DeterminanMatriks(Sub) <= EPSILON: HapusMatriks, return false.
 *     HapusMatriks(&Sub).
 *   return true.
 *
 * Kompleksitas waktu : O(N * N!) — karena DeterminanMatriks
 */

/* ------------------------------------------------------------
 *  MATRIKS ORTOGONAL
 * ------------------------------------------------------------ */

boolean MatriksOrtogonal (Matriks A);
/*
 * Mengembalikan true jika A^T x A = I (dalam batas EPSILON).
 *
 * I.S. : A terdefinisi.
 * F.S. : Hitung A^T, lalu A^T x A, bandingkan dengan I.
 *         return MatriksSetara(AT_A, I).
 *
 * Catatan: Matriks ortogonal mempertahankan panjang vektor
 *           (rotasi, refleksi). Secara numerik, cek dengan EPSILON.
 *
 * Petunjuk implementasi:
 *   1. TransposeMatriks(A, &AT)
 *   2. PerkalianMatriks(AT, A, &Hasil)
 *   3. MatriksIdentitas(&I)
 *   4. bool ok = MatriksSetara(Hasil, I)
 *   5. HapusMatriks(&AT), HapusMatriks(&Hasil), HapusMatriks(&I)
 *   6. return ok
 */

/* ------------------------------------------------------------
 *  NORMA FROBENIUS
 * ------------------------------------------------------------ */

ElMatriks FrobeniusNorm (Matriks A);
/*
 * Menghitung norma Frobenius: ||A||_F = sqrt( sigma sigma A[i][j]^2 ).
 *
 * I.S. : A terdefinisi.
 * F.S. : Nilai norma Frobenius dikembalikan.
 *
 * Properti penting:
 *   ||I_N||_F  = sqrt(N)
 *   ||A||_F    = ||A^T||_F
 *   ||kA||_F   = |k| * ||A||_F
 *   ||AB||_F  <= ||A||_F * ||B||_F  (sub-multiplicativity)
 *
 * Kompleksitas waktu : O(N^2)
 */

ElMatriks JarakMatriks (Matriks A, Matriks B);
/*
 * Mengembalikan "jarak" antara dua matriks menggunakan norma Frobenius:
 *     d(A, B) = ||A - B||_F
 *
 * I.S. : A dan B terdefinisi dan berukuran sama.
 * F.S. : Mengembalikan sqrt( sigma sigma (A[i][j] - B[i][j])^2 ).
 *
 * Catatan: Hitung langsung tanpa mengalokasikan matriks baru.
 */

/* ============================================================
 *  SOAL LATIHAN
 * ============================================================
 *
 *  [1] Implementasikan BuatMatriksSimetris dan BuatMatriksAntiSimetris.
 *      Uji dengan A = | 4  2 |  — hasilnya:
 *                     | 6  8 |
 *      S = | 4  4 |    K = | 0  -2 |
 *          | 4  8 |        | 2   0 |
 *
 *  [2] Implementasikan VerifikasiDekomposisi.
 *      Verifikasi bahwa S + K = A untuk A di soal [1].
 *
 *  [3] Implementasikan MatriksDefinitPositif.
 *      Uji dengan:
 *      (a) A = | 2  1 |  → harus true  (minor: 2>0, det=5>0)
 *              | 1  3 |
 *      (b) B = | 1  2 |  → harus false (det=1*3-2*2=-1<0)
 *              | 2  3 |
 *
 *  [4] Implementasikan MatriksOrtogonal.
 *      Uji dengan matriks rotasi 2D (θ = 90°):
 *      R = |  0  -1 |  → R^T x R harus = I
 *          |  1   0 |
 *
 *  [5] Buktikan secara matematis bahwa S = (A + A^T)/2 selalu simetris
 *      untuk sembarang A. (Tunjukkan S^T = S langkah per langkah.)
 *
 *  PETUNJUK DEBUGGING
 *  ------------------
 *  - Untuk soal [3]: cetak det minor utama ke-1, ke-2, ..., ke-N.
 *  - Untuk soal [4]: gunakan JarakMatriks(R^T x R, I) < EPSILON.
 *  - Elemen diagonal K harus selalu 0 — ini adalah cara cek cepat.
 * ============================================================
 */

#endif /* SOAL4_SIMETRIS_H */
