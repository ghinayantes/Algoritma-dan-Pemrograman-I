#ifndef SOAL2_KOFAKTOR_H
#define SOAL2_KOFAKTOR_H

/*
 * ============================================================
 *  SOAL 2 — MATRIKS MINOR DAN KOFAKTOR
 *  File   : soal2_kofaktor.h
 *  Depend : matriks.h, boolean.h
 * ============================================================
 *
 *  LATAR BELAKANG
 *  --------------
 *  Minor M[i][j] dari matriks A berukuran N x N adalah
 *  determinan submatriks (N-1)x(N-1) yang diperoleh dengan
 *  menghapus baris i dan kolom j dari A.
 *
 *  Kofaktor C[i][j] didefinisikan sebagai:
 *      C[i][j] = (-1)^(i+j) * M[i][j]
 *
 *  Tanda (-1)^(i+j) membentuk pola papan catur (0-indexed):
 *      + - + - ...
 *      - + - + ...
 *      + - + - ...
 *
 *  Matriks kofaktor (Cofactor Matrix) berisi semua C[i][j].
 *  Adjugat (Adjoint) adalah transpose dari matriks kofaktor.
 *  Invers: A^(-1) = Adjugat(A) / det(A)  (jika det != 0).
 *
 *  KETERGANTUNGAN
 *  --------------
 *    - BuatMatriks, HapusMatriks, SalinMatriks
 *    - DeterminanMatriks
 *    - TransposeMatriks
 * ============================================================
 */

#include "matriks.h"

/* ------------------------------------------------------------
 *  SUBMATRIKS
 * ------------------------------------------------------------ */

void SubMatriks (Matriks A, int baris, int kolom, Matriks *Sub);
/*
 * Menghasilkan submatriks (N-1)x(N-1) dari A dengan
 * menghapus baris ke-`baris` dan kolom ke-`kolom`.
 *
 * I.S. : A terdefinisi berukuran N x N  (N >= 2).
 *         0 <= baris < A.N, 0 <= kolom < A.N.
 *         *Sub sudah dialokasikan dengan Sub->N = A.N - 1.
 *
 * F.S. : Sub->M berisi elemen A tanpa baris ke-baris
 *         dan kolom ke-kolom, diindeks ulang dari 0.
 *
 * Algoritma:
 *   si = 0   <- indeks baris Sub
 *   untuk i = 0 hingga A.N-1:
 *     jika i == baris: lewati
 *     sj = 0   <- indeks kolom Sub
 *     untuk j = 0 hingga A.N-1:
 *       jika j == kolom: lewati
 *       Sub->M[si][sj] = A.M[i][j]
 *       sj++
 *     si++
 *
 * Kompleksitas waktu : O(N^2)
 */

/* ------------------------------------------------------------
 *  KOFAKTOR
 * ------------------------------------------------------------ */

ElMatriks KofaktorElemen (Matriks A, int i, int j);
/*
 * Mengembalikan kofaktor C[i][j] dari matriks A.
 *
 * I.S. : A terdefinisi, A.N >= 2.
 *         0 <= i, j < A.N.
 *
 * F.S. : Mengembalikan (-1)^(i+j) * det(SubMatriks(A, i, j)).
 *
 * Catatan:
 *   - Alokasikan Sub berukuran (A.N - 1), isi dengan SubMatriks,
 *     hitung DeterminanMatriks(Sub), lalu bebaskan Sub.
 *   - Tanda: gunakan ((i+j) % 2 == 0) ? 1.0 : -1.0
 */

void MatriksKofaktor (Matriks A, Matriks *C);
/*
 * Menghasilkan matriks kofaktor C di mana C[i][j] = KofaktorElemen(A,i,j).
 *
 * I.S. : A terdefinisi, A.N >= 2.
 *         *C sudah dialokasikan dengan C->N = A.N.
 *
 * F.S. : C->M[i][j] = KofaktorElemen(A, i, j) untuk semua i,j.
 *
 * Kompleksitas waktu : O(N^2 * (N-1)!) — ekspansi kofaktor naif
 */

/* ------------------------------------------------------------
 *  ADJUGAT DAN INVERS
 * ------------------------------------------------------------ */

void AdjugatMatriks (Matriks A, Matriks *Adj);
/*
 * Menghitung adjugat (adjoint) dari A:
 *     Adj(A) = Transpose(MatriksKofaktor(A))
 *
 * I.S. : A terdefinisi, A.N >= 2.
 *         *Adj sudah dialokasikan dengan Adj->N = A.N.
 *
 * F.S. : *Adj = transpose dari matriks kofaktor A.
 *
 * Petunjuk: hitung MatriksKofaktor dulu ke C sementara,
 *           lalu TransposeMatriks(C, Adj), terakhir HapusMatriks(C).
 */

boolean InversMatriks (Matriks A, Matriks *Inv);
/*
 * Menghitung invers A menggunakan rumus:
 *     A^(-1) = Adjugat(A) / det(A)
 *
 * I.S. : A terdefinisi.
 *         *Inv sudah dialokasikan dengan Inv->N = A.N.
 *
 * F.S. : Jika det(A) == 0 (< EPSILON): A singular, return false,
 *           *Inv tidak diubah.
 *         Jika det(A) != 0: *Inv = A^(-1), return true.
 *
 * Petunjuk:
 *   1. det = DeterminanMatriks(A)
 *   2. Jika |det| < EPSILON, return false.
 *   3. AdjugatMatriks(A, Inv)
 *   4. PerkalianSkalar(Inv, 1.0 / det)
 */

/* ------------------------------------------------------------
 *  VERIFIKASI
 * ------------------------------------------------------------ */

boolean VerifikasiInvers (Matriks A, Matriks AInv);
/*
 * Mengembalikan true jika A x AInv ≈ I (dalam batas EPSILON).
 *
 * I.S. : A dan AInv terdefinisi, berukuran sama.
 * F.S. : Hitung A x AInv, bandingkan dengan MatriksIdentitas.
 *         Gunakan MatriksSetara.
 *
 * Petunjuk: alokasikan matriks Hasil untuk A x AInv,
 *            buat matriks I, bandingkan, bebaskan keduanya.
 */

/* ============================================================
 *  SOAL LATIHAN
 * ============================================================
 *
 *  [1] Implementasikan SubMatriks.
 *      Uji: buat A 3x3 sembarang, cetak SubMatriks(A, 1, 1).
 *
 *  [2] Implementasikan KofaktorElemen.
 *      Hitung KofaktorElemen(A, 0, 1) untuk:
 *          | 3  1  2 |
 *      A = | 0  4  1 |
 *          | 2  0  5 |
 *
 *  [3] Implementasikan MatriksKofaktor dan AdjugatMatriks.
 *      Cetak Adj(A) untuk A di soal [2].
 *
 *  [4] Implementasikan InversMatriks.
 *      Hitung A^(-1) untuk A di soal [2].
 *      Verifikasi dengan VerifikasiInvers.
 *
 *  [5] Uji InversMatriks pada matriks singular:
 *          | 1  2 |
 *      A = | 2  4 |
 *      Apa yang seharusnya dikembalikan?
 *
 *  PETUNJUK DEBUGGING
 *  ------------------
 *  - Pastikan Sub dibebaskan setiap kali setelah KofaktorElemen.
 *  - Tanda kofaktor: i=0,j=0 → +; i=0,j=1 → -; i=1,j=0 → -
 *  - det(A) untuk soal [2] = 57. Cek dahulu dengan DeterminanMatriks.
 * ============================================================
 */

#endif /* SOAL2_KOFAKTOR_H */
