#ifndef SOAL5_JACOBI_H
#define SOAL5_JACOBI_H

/*
 * ============================================================
 *  SOAL 5 — METODE ITERASI JACOBI DAN GAUSS-SEIDEL
 *  File   : soal5_jacobi.h
 *  Depend : matriks.h, boolean.h, <math.h>, <stdlib.h>
 * ============================================================
 *
 *  LATAR BELAKANG
 *  --------------
 *  Sistem persamaan linear Ax = b dapat diselesaikan secara
 *  iteratif. Dua metode klasik:
 *
 *  1. METODE JACOBI
 *     Setiap iterasi menggunakan nilai x dari iterasi SEBELUMNYA:
 *
 *         x[i]^(k+1) = ( b[i] - sigma_{j≠i} A[i][j]*x[j]^(k) )
 *                      / A[i][i]
 *
 *     Semua x[i] baru dihitung berdasarkan x lama, lalu
 *     seluruhnya diperbarui sekaligus.
 *
 *  2. METODE GAUSS-SEIDEL
 *     Setiap iterasi langsung menggunakan nilai x yang BARU
 *     begitu tersedia:
 *
 *         x[i]^(k+1) = ( b[i] - sigma_{j<i} A[i][j]*x[j]^(k+1)
 *                               - sigma_{j>i} A[i][j]*x[j]^(k) )
 *                      / A[i][i]
 *
 *     Gauss-Seidel umumnya konvergen 2x lebih cepat dari Jacobi.
 *
 *  SYARAT KONVERGENSI
 *  ------------------
 *  Keduanya dijamin konvergen jika A diagonal dominan:
 *      |A[i][i]| > sigma_{j≠i} |A[i][j]|  untuk semua i
 *
 *  REPRESENTASI VEKTOR
 *  -------------------
 *  Vektor diwakili sebagai array 1D bertipe double:
 *      typedef double* Vektor;
 *
 *  Vektor harus dialokasikan dengan malloc/calloc dan
 *  dibebaskan dengan free setelah selesai digunakan.
 *
 *  KETERGANTUNGAN
 *  --------------
 *    - matriks.h (MatriksDiagonalDominan, Matriks, ElMatriks)
 *    - <stdlib.h> (malloc, free)
 *    - <math.h> (fabs)
 * ============================================================
 */

#include "matriks.h"
#include <stdlib.h>
#include <math.h>

/* Tipe vektor: array 1D dinamis */
typedef double* Vektor;

/* ------------------------------------------------------------
 *  OPERASI VEKTOR DASAR
 * ------------------------------------------------------------ */

Vektor BuatVektor (int n);
/*
 * Mengalokasikan vektor berukuran n dengan semua elemen = 0.0.
 *
 * I.S. : n > 0.
 * F.S. : Mengembalikan pointer ke array double[n] yang sudah
 *         dinol-kan, atau NULL jika alokasi gagal.
 *
 * Petunjuk: gunakan calloc(n, sizeof(double)).
 */

void HapusVektor (Vektor *v);
/*
 * Membebaskan memori vektor.
 *
 * I.S. : *v terdefinisi (bisa NULL).
 * F.S. : free(*v), *v = NULL.
 */

void SalinVektor (Vektor src, Vektor *dst, int n);
/*
 * Menyalin isi src ke dst (sudah dialokasikan ukuran n).
 *
 * I.S. : src dan *dst teralokasi ukuran n.
 * F.S. : (*dst)[i] = src[i] untuk i=0..n-1.
 */

void CetakVektor (Vektor v, int n);
/*
 * Mencetak vektor dengan format: [v[0]  v[1]  ...  v[n-1]]
 * setiap elemen dengan format "%.6f", diakhiri newline.
 */

double NormaVektor (Vektor v, int n);
/*
 * Mengembalikan norma tak-hingga (L∞) vektor v:
 *     ||v||_inf = max_i |v[i]|
 *
 * I.S. : v teralokasi ukuran n.
 * F.S. : Nilai norma dikembalikan.
 */

/* ------------------------------------------------------------
 *  METODE JACOBI
 * ------------------------------------------------------------ */

boolean MetodeJacobi (Matriks A, Vektor b, Vektor x,
                      int maks_iter, double toleransi);
/*
 * Menyelesaikan Ax = b menggunakan metode Jacobi.
 *
 * I.S. : A adalah matriks N x N (sebaiknya diagonal dominan).
 *         b = vektor ruas kanan, ukuran N.
 *         x = tebakan awal (initial guess), ukuran N.
 *             Akan diisi dengan solusi aproksimasi.
 *         maks_iter > 0  (batas iterasi maksimum).
 *         toleransi > 0  (batas error untuk konvergensi).
 *
 * F.S. : x diisi dengan solusi aproksimasi Ax ≈ b.
 *         return true jika konvergen dalam maks_iter iterasi.
 *         return false jika tidak konvergen.
 *
 * Algoritma lengkap:
 *   x_baru = BuatVektor(N)
 *   untuk iter = 1 hingga maks_iter:
 *     untuk i = 0 hingga N-1:
 *       sigma = b[i]
 *       untuk j = 0 hingga N-1:
 *         jika j != i: sigma -= A.M[i][j] * x[j]
 *       x_baru[i] = sigma / A.M[i][i]
 *     error = NormaVektor(x_baru - x, N)   ← hitung maks |x_baru[i]-x[i]|
 *     SalinVektor(x_baru, &x, N)
 *     jika error < toleransi: HapusVektor(x_baru), return true
 *   HapusVektor(x_baru)
 *   return false
 *
 * Catatan: Gunakan array x_baru terpisah agar semua x[j] lama
 *           masih tersedia saat menghitung x_baru[i].
 *
 * Kompleksitas waktu per iterasi : O(N^2)
 */

/* ------------------------------------------------------------
 *  METODE GAUSS-SEIDEL
 * ------------------------------------------------------------ */

boolean MetodeGaussSeidel (Matriks A, Vektor b, Vektor x,
                           int maks_iter, double toleransi);
/*
 * Menyelesaikan Ax = b menggunakan metode Gauss-Seidel.
 *
 * I.S. : Sama dengan MetodeJacobi.
 * F.S. : x diisi dengan solusi aproksimasi.
 *         return true jika konvergen, false jika tidak.
 *
 * Perbedaan dari Jacobi:
 *   - Tidak memerlukan x_baru terpisah.
 *   - Update x[i] langsung menggunakan x[j] terbaru (j < i).
 *
 * Algoritma:
 *   untuk iter = 1 hingga maks_iter:
 *     error_maks = 0
 *     untuk i = 0 hingga N-1:
 *       sigma = b[i]
 *       untuk j = 0 hingga N-1:
 *         jika j != i: sigma -= A.M[i][j] * x[j]   ← x[j<i] sudah baru!
 *       x_baru_i = sigma / A.M[i][i]
 *       error_maks = max(error_maks, |x_baru_i - x[i]|)
 *       x[i] = x_baru_i
 *     jika error_maks < toleransi: return true
 *   return false
 *
 * Kompleksitas waktu per iterasi : O(N^2) — sama dengan Jacobi
 *   tetapi konvergensi biasanya 2x lebih cepat.
 */

/* ------------------------------------------------------------
 *  UTILITAS
 * ------------------------------------------------------------ */

double HitungResidual (Matriks A, Vektor b, Vektor x, int n);
/*
 * Menghitung residual r = ||Ax - b||_inf.
 *
 * I.S. : A, b, x terdefinisi; n = A.N.
 * F.S. : Mengembalikan max_i |( sigma_j A[i][j]*x[j] ) - b[i]|.
 *
 * Interpretasi: semakin kecil residual, semakin akurat solusi.
 * Residual = 0.0 berarti solusi eksak.
 *
 * Gunakan ini untuk memverifikasi hasil MetodeJacobi/GaussSeidel.
 */

void CetakIterasiJacobi (Matriks A, Vektor b, Vektor x_awal,
                         int jumlah_iter);
/*
 * Mencetak proses iterasi Jacobi sebanyak jumlah_iter langkah
 * (terlepas dari konvergensi) untuk keperluan debugging dan
 * pemahaman.
 *
 * Format keluaran setiap iterasi k:
 *   Iterasi k: x = [x[0]  x[1]  ...  x[N-1]]  residual = r
 *
 * I.S. : A, b, x_awal terdefinisi; jumlah_iter > 0.
 * F.S. : Mencetak proses iterasi tanpa mengubah x_awal.
 *
 * Catatan: Buat salinan x_awal secara internal agar tidak
 *           memodifikasi vektor asli.
 */

/* ============================================================
 *  SOAL LATIHAN
 * ============================================================
 *
 *  [1] Implementasikan MetodeJacobi.
 *      Uji dengan sistem berikut (tebakan awal x = [0,0,0]):
 *
 *       4x + y  + z  = 7     →  x = ?
 *       x  + 5y + z  = 10    →  y = ?
 *       x  + y  + 6z = 11    →  z = ?
 *
 *      Solusi eksak: x=1, y=1, z=1.5  (approx).
 *      Verifikasi dengan HitungResidual < 1e-6.
 *
 *  [2] Lakukan 2 iterasi Jacobi secara manual (tangan) untuk
 *      sistem di soal [1] dengan x^(0) = [0, 0, 0]:
 *        Iterasi 1: x^(1)[i] = ?
 *        Iterasi 2: x^(2)[i] = ?
 *      Bandingkan dengan keluaran CetakIterasiJacobi.
 *
 *  [3] Implementasikan MetodeGaussSeidel.
 *      Uji dengan sistem yang sama di soal [1].
 *      Bandingkan: berapa iterasi yang dibutuhkan Jacobi vs
 *      Gauss-Seidel untuk mencapai toleransi = 1e-6?
 *
 *  [4] Uji MetodeJacobi pada matriks TIDAK diagonal dominan:
 *          | 1  4 |        | 5 |
 *      A = | 3  1 |   b =  | 4 |
 *      Apa yang terjadi? Mengapa?
 *
 *  [5] Apa risiko jika A[i][i] = 0 untuk beberapa baris i?
 *      Bagaimana cara mencegahnya sebelum memanggil Jacobi?
 *      (Petunjuk: periksa MatriksDiagonalDominan terlebih dahulu,
 *       atau tambahkan pengecekan di dalam fungsi.)
 *
 *  PETUNJUK DEBUGGING
 *  ------------------
 *  - Gunakan CetakIterasiJacobi untuk memantau konvergensi.
 *  - Residual harus menurun setiap iterasi jika A diag. dominan.
 *  - Jika residual membesar: A tidak diagonal dominan.
 *  - Pastikan x_baru dibebaskan di semua jalur return (konvergen
 *    maupun tidak konvergen) untuk menghindari memory leak.
 *
 *  PERBANDINGAN METODE
 *  -------------------
 *  | Aspek              | Jacobi        | Gauss-Seidel    |
 *  |--------------------|---------------|-----------------|
 *  | Memori tambahan    | O(N)          | O(1)            |
 *  | Kecepatan konvergen| Lebih lambat  | ~2x lebih cepat |
 *  | Paralelisasi       | Mudah         | Sulit           |
 *  | Implementasi       | Lebih mudah   | Sedikit lebih   |
 *  |                    |               | kompleks        |
 * ============================================================
 */

#endif /* SOAL5_JACOBI_H */