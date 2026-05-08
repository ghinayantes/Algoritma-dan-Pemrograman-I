/*
 * ============================================================
 *  matriks_operasi.c
 *  Demo lengkap 12 operasi matriks dalam satu file C.
 *
 *  Operasi yang diimplementasikan:
 *   1.  Transpose
 *   2.  Penjumlahan
 *   3.  Pengurangan
 *   4.  Perkalian Matriks (Matrix Multiplication)
 *   5.  Perkalian Skalar
 *   6.  Determinan (rekursif, ekspansi kofaktor)
 *   7.  Jejak / Trace
 *   8.  Invers (via adjugat)
 *   9.  Pangkat Matriks
 *  10.  Normalisasi Baris
 *  11.  Cek Simetris
 *  12.  Cek Diagonal Dominan
 *
 *  Kompilasi : gcc -o matriks_operasi matriks_operasi.c -lm
 *  Jalankan  : ./matriks_operasi
 * ============================================================
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define MAX  10          /* ukuran matriks maksimum */
#define EPS  1e-9        /* toleransi bilangan floating-point */

/* ============================================================
 *  TIPE DAN UTILITAS
 * ============================================================ */

typedef double Mat[MAX][MAX];

/* Mencetak judul bagian */
void judul(const char *teks) {
    printf("\n");
    printf("╔══════════════════════════════════════╗\n");
    printf("║  %-36s║\n", teks);
    printf("╚══════════════════════════════════════╝\n");
}

/* Mencetak matriks N x M */
void cetak(const char *nama, Mat A, int N, int M) {
    printf("  %s (%dx%d):\n", nama, N, M);
    for (int i = 0; i < N; i++) {
        printf("  │");
        for (int j = 0; j < M; j++) {
            /* cetak tanpa desimal jika bilangan bulat */
            if (fabs(A[i][j] - (int)A[i][j]) < EPS)
                printf(" %6.0f", A[i][j]);
            else
                printf(" %6.2f", A[i][j]);
        }
        printf(" │\n");
    }
}

/* Menyalin A ke B */
void salin(Mat A, Mat B, int N, int M) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            B[i][j] = A[i][j];
}

/* Membuat matriks identitas */
void identitas(Mat I, int N) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            I[i][j] = (i == j) ? 1.0 : 0.0;
}

/* ============================================================
 *  OPERASI 1 — TRANSPOSE
 *  Rumus: B[j][i] = A[i][j]
 * ============================================================ */
void op_transpose(Mat A, Mat B, int N, int M) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            B[j][i] = A[i][j];
    /* hasil: B berukuran M x N */
}

/* ============================================================
 *  OPERASI 2 — PENJUMLAHAN
 *  Rumus: C[i][j] = A[i][j] + B[i][j]
 * ============================================================ */
void op_tambah(Mat A, Mat B, Mat C, int N, int M) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            C[i][j] = A[i][j] + B[i][j];
}

/* ============================================================
 *  OPERASI 3 — PENGURANGAN
 *  Rumus: C[i][j] = A[i][j] - B[i][j]
 * ============================================================ */
void op_kurang(Mat A, Mat B, Mat C, int N, int M) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            C[i][j] = A[i][j] - B[i][j];
}

/* ============================================================
 *  OPERASI 4 — PERKALIAN MATRIKS
 *  Rumus: C[i][j] = sigma_k A[i][k] * B[k][j]
 *  Syarat: kolom A == baris B  (N x K) x (K x P) = (N x P)
 * ============================================================ */
void op_kali(Mat A, Mat B, Mat C, int N, int K, int P) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < P; j++) {
            C[i][j] = 0.0;
            for (int k = 0; k < K; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
}

/* ============================================================
 *  OPERASI 5 — PERKALIAN SKALAR
 *  Rumus: B[i][j] = k * A[i][j]
 * ============================================================ */
void op_skalar(Mat A, Mat B, int N, int M, double k) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            B[i][j] = k * A[i][j];
}

/* ============================================================
 *  OPERASI 6 — DETERMINAN (ekspansi kofaktor, rekursif)
 *  Rumus: det(A) = sigma_j A[0][j] * (-1)^j * det(minor(0,j))
 *  Basis: det([[a]]) = a  ;  det([[a,b],[c,d]]) = ad - bc
 * ============================================================ */
double op_determinan(Mat A, int N) {
    if (N == 1) return A[0][0];
    if (N == 2) return A[0][0]*A[1][1] - A[0][1]*A[1][0];

    double det = 0.0;
    Mat Sub;

    for (int col = 0; col < N; col++) {
        /* Bangun submatriks dengan menghapus baris 0 dan kolom col */
        int si = 0;
        for (int i = 1; i < N; i++) {
            int sj = 0;
            for (int j = 0; j < N; j++) {
                if (j == col) continue;
                Sub[si][sj++] = A[i][j];
            }
            si++;
        }
        double tanda = (col % 2 == 0) ? 1.0 : -1.0;
        det += tanda * A[0][col] * op_determinan(Sub, N - 1);
    }
    return det;
}

/* ============================================================
 *  OPERASI 7 — JEJAK / TRACE
 *  Rumus: trace(A) = sigma_i A[i][i]
 *  Hanya berlaku untuk matriks persegi.
 * ============================================================ */
double op_trace(Mat A, int N) {
    double tr = 0.0;
    for (int i = 0; i < N; i++)
        tr += A[i][i];
    return tr;
}

/* ============================================================
 *  OPERASI 8 — INVERS (via matriks adjugat)
 *  Rumus: A^(-1) = Adjugat(A) / det(A)
 *  Adjugat(A)[i][j] = (-1)^(i+j) * det(minor(j,i))
 *  Syarat: det(A) != 0
 * ============================================================ */
int op_invers(Mat A, Mat Inv, int N) {
    double det = op_determinan(A, N);
    if (fabs(det) < EPS) {
        printf("  [!] Matriks singular — invers tidak ada (det = 0)\n");
        return 0; /* gagal */
    }

    if (N == 1) {
        Inv[0][0] = 1.0 / A[0][0];
        return 1;
    }

    Mat Adj;
    Mat Sub;

    /* Hitung matriks adjugat */
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            /* Bangun submatriks minor(i,j): hapus baris i, kolom j */
            int si = 0;
            for (int r = 0; r < N; r++) {
                if (r == i) continue;
                int sj = 0;
                for (int c = 0; c < N; c++) {
                    if (c == j) continue;
                    Sub[si][sj++] = A[r][c];
                }
                si++;
            }
            double kofaktor = op_determinan(Sub, N - 1);
            double tanda    = ((i + j) % 2 == 0) ? 1.0 : -1.0;
            /* Adj adalah transpose dari matriks kofaktor: Adj[j][i] */
            Adj[j][i] = tanda * kofaktor;
        }
    }

    /* Inv = Adj / det */
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            Inv[i][j] = Adj[i][j] / det;

    return 1; /* berhasil */
}

/* ============================================================
 *  OPERASI 9 — PANGKAT MATRIKS
 *  Rumus: A^0 = I  ;  A^p = A^(p-1) x A
 *  Implementasi: iteratif, A dikali dengan dirinya p kali.
 * ============================================================ */
void op_pangkat(Mat A, Mat Hasil, int N, int p) {
    Mat Temp;
    identitas(Hasil, N);          /* Mulai dari I */

    for (int iter = 0; iter < p; iter++) {
        op_kali(Hasil, A, Temp, N, N, N);
        salin(Temp, Hasil, N, N);
    }
}

/* ============================================================
 *  OPERASI 10 — NORMALISASI BARIS
 *  Setiap baris dibagi dengan norma Euclidean-nya:
 *      ||baris_i||_2 = sqrt( sigma_j A[i][j]^2 )
 *  Sehingga setiap baris menjadi vektor satuan (norma = 1).
 * ============================================================ */
int op_normalisasi_baris(Mat A, Mat B, int N, int M) {
    salin(A, B, N, M);

    for (int i = 0; i < N; i++) {
        double norma = 0.0;
        for (int j = 0; j < M; j++)
            norma += B[i][j] * B[i][j];
        norma = sqrt(norma);

        if (norma < EPS) {
            printf("  [!] Baris %d adalah baris nol — normalisasi dibatalkan\n", i);
            return 0;
        }
        for (int j = 0; j < M; j++)
            B[i][j] /= norma;
    }
    return 1;
}

/* ============================================================
 *  OPERASI 11 — CEK SIMETRIS
 *  A simetris jika A[i][j] == A[j][i] untuk semua i,j.
 *  Hanya berlaku untuk matriks persegi.
 * ============================================================ */
int op_cek_simetris(Mat A, int N) {
    for (int i = 0; i < N; i++)
        for (int j = i + 1; j < N; j++)
            if (fabs(A[i][j] - A[j][i]) >= EPS)
                return 0; /* tidak simetris */
    return 1;
}

/* ============================================================
 *  OPERASI 12 — CEK DIAGONAL DOMINAN
 *  Baris i diagonal dominan jika:
 *      |A[i][i]| >= sigma_{j != i} |A[i][j]|
 *  Matriks diagonal dominan jika berlaku untuk SEMUA baris.
 * ============================================================ */
int op_cek_diag_dominan(Mat A, int N) {
    for (int i = 0; i < N; i++) {
        double sigma = 0.0;
        for (int j = 0; j < N; j++)
            if (j != i) sigma += fabs(A[i][j]);

        printf("  Baris %d: |A[%d][%d]| = %.2f, sigma off-diag = %.2f  →  %s\n",
               i, i, i, fabs(A[i][i]), sigma,
               fabs(A[i][i]) >= sigma - EPS ? "dominan ✓" : "TIDAK dominan ✗");

        if (fabs(A[i][i]) < sigma - EPS) return 0;
    }
    return 1;
}

void Rotasi90(Matriks A, Matriks *Hasil) {
    /* Langkah 1: Transpose A ke Hasil */
    TransposeMatriks(A, Hasil);
    
    /* Langkah 2: Balikkan elemen di setiap baris */
    int i, j;
    ElMatriks temp;
    for (i = 0; i < Hasil->N; i++) {
        for (j = 0; j < Hasil->N / 2; j++) {
            // Tukar elemen Hasil->M[i][j] dengan Hasil->M[i][Hasil->N - 1 - j]
            temp = Hasil->M[i][j];
            Hasil->M[i][j] = Hasil->M[i][Hasil->N - 1 - j];
            Hasil->M[i][Hasil->N - 1 - j] = temp;
        }
    }
}

void Rotasi180(Matriks A, Matriks *Hasil) {
    int i, j;
    for (i = 0; i < A.N; i++) {
        for (j = 0; j < A.N; j++) {
            // Baris i menjadi N-1-i, Kolom j menjadi N-1-j
            Hasil->M[i][j] = A.M[A.N - 1 - i][A.N - 1 - j];
        }
    }
}

void Rotasi270(Matriks A, Matriks *Hasil) {
    /* Langkah 1: Transpose A ke Hasil */
    TransposeMatriks(A, Hasil);
    
    /* Langkah 2: Balikkan urutan baris */
    int i, j;
    ElMatriks *tempRow;
    for (i = 0; i < Hasil->N / 2; i++) {
        // Tukar pointer baris i dengan baris N-1-i
        tempRow = Hasil->M[i];
        Hasil->M[i] = Hasil->M[Hasil->N - 1 - i];
        Hasil->M[Hasil->N - 1 - i] = tempRow;
    }
}

void RotasiMatriks(Matriks A, int derajat, Matriks *Hasil) {
    /* Derajat harus kelipatan 90 */
    int k = (derajat % 360) / 90;
    
    if (k == 1) Rotasi90(A, Hasil);
    else if (k == 2) Rotasi180(A, Hasil);
    else if (k == 3) Rotasi270(A, Hasil);
    else SalinMatriks(A, Hasil); // 0 atau 360 derajat
}

/* ============================================================
 *  MAIN — DEMO SEMUA OPERASI
 * ============================================================ */
int main(void) {

    printf("╔══════════════════════════════════════╗\n");
    printf("║    DEMO 12 OPERASI MATRIKS  (C)      ║\n");
    printf("╚══════════════════════════════════════╝\n");

    /* --- Matriks-matriks yang dipakai sepanjang demo --- */

    /* A dan B: matriks 3x3 untuk operasi aritmatik */
    Mat A = {
        { 4, 3, 2},
        { 1, 5, 7},
        { 8, 6, 9}
    };
    Mat B = {
        { 1, 0, 2},
        { 3, 1, 4},
        { 0, 2, 1}
    };

    /* Sym: matriks simetris */
    Mat Sym = {
        { 4, 2, 1},
        { 2, 5, 3},
        { 1, 3, 6}
    };

    /* D: matriks diagonal dominan (untuk Jacobi-like check) */
    Mat D = {
        { 7, 1, 2},
        { 1, 8, 1},
        { 2, 1, 9}
    };

    /* Matriks hasil sementara */
    Mat Hasil, Hasil2;

    /* ---- 1. TRANSPOSE ---- */
    judul("1. TRANSPOSE");
    cetak("A", A, 3, 3);
    op_transpose(A, Hasil, 3, 3);
    cetak("A^T", Hasil, 3, 3);
    printf("  Rumus: B[j][i] = A[i][j]\n");

    /* ---- 2. PENJUMLAHAN ---- */
    judul("2. PENJUMLAHAN  A + B");
    cetak("A", A, 3, 3);
    cetak("B", B, 3, 3);
    op_tambah(A, B, Hasil, 3, 3);
    cetak("A + B", Hasil, 3, 3);

    /* ---- 3. PENGURANGAN ---- */
    judul("3. PENGURANGAN  A - B");
    op_kurang(A, B, Hasil, 3, 3);
    cetak("A - B", Hasil, 3, 3);

    /* ---- 4. PERKALIAN MATRIKS ---- */
    judul("4. PERKALIAN MATRIKS  A x B");
    cetak("A", A, 3, 3);
    cetak("B", B, 3, 3);
    op_kali(A, B, Hasil, 3, 3, 3);
    cetak("A x B", Hasil, 3, 3);
    printf("  Rumus: C[i][j] = sigma_k  A[i][k] * B[k][j]\n");

    /* ---- 5. PERKALIAN SKALAR ---- */
    judul("5. PERKALIAN SKALAR  3 * A");
    op_skalar(A, Hasil, 3, 3, 3.0);
    cetak("3 * A", Hasil, 3, 3);
    printf("  Rumus: B[i][j] = k * A[i][j],  k = 3\n");

    /* ---- 6. DETERMINAN ---- */
    judul("6. DETERMINAN");
    cetak("A", A, 3, 3);
    double det_A = op_determinan(A, 3);
    printf("  det(A) = %.4f\n", det_A);
    printf("  Metode: Ekspansi kofaktor sepanjang baris-0\n");
    printf("  det([[4,3],[1,5]]) = 4*5 - 3*1 = 17  (submasalah contoh)\n");

    /* ---- 7. TRACE ---- */
    judul("7. TRACE (JEJAK)");
    cetak("A", A, 3, 3);
    double tr = op_trace(A, 3);
    printf("  trace(A) = A[0][0]+A[1][1]+A[2][2] = %.0f+%.0f+%.0f = %.4f\n",
           A[0][0], A[1][1], A[2][2], tr);

    /* ---- 8. INVERS ---- */
    judul("8. INVERS  A^(-1)");
    cetak("A", A, 3, 3);
    printf("  det(A) = %.4f\n", det_A);
    if (op_invers(A, Hasil, 3)) {
        cetak("A^(-1)", Hasil, 3, 3);

        /* Verifikasi: A x A^(-1) harus = I */
        op_kali(A, Hasil, Hasil2, 3, 3, 3);
        cetak("A x A^(-1)  (harus = I)", Hasil2, 3, 3);
    }

    /* Uji matriks singular */
    printf("\n  Uji matriks singular:\n");
    Mat Sing = {{1, 2}, {2, 4}};   /* baris 2 = 2 * baris 1 */
    cetak("Singular 2x2", Sing, 2, 2);
    op_invers(Sing, Hasil, 2);

    /* ---- 9. PANGKAT MATRIKS ---- */
    judul("9. PANGKAT MATRIKS  A^3");
    Mat Ap = {{1, 2}, {0, 1}};
    cetak("A (2x2)", Ap, 2, 2);
    op_pangkat(Ap, Hasil, 2, 0);
    cetak("A^0  (harus = I)", Hasil, 2, 2);
    op_pangkat(Ap, Hasil, 2, 1);
    cetak("A^1", Hasil, 2, 2);
    op_pangkat(Ap, Hasil, 2, 3);
    cetak("A^3", Hasil, 2, 2);
    printf("  Rumus: A^0=I, A^p = A^(p-1) x A\n");

    /* ---- 10. NORMALISASI BARIS ---- */
    judul("10. NORMALISASI BARIS");
    cetak("A", A, 3, 3);
    if (op_normalisasi_baris(A, Hasil, 3, 3)) {
        cetak("A (baris ternormalisasi)", Hasil, 3, 3);
        printf("  Verifikasi norma baris:\n");
        for (int i = 0; i < 3; i++) {
            double norma = 0.0;
            for (int j = 0; j < 3; j++) norma += Hasil[i][j]*Hasil[i][j];
            printf("    ||baris_%d|| = %.6f  %s\n", i, sqrt(norma),
                   fabs(sqrt(norma) - 1.0) < 1e-6 ? "✓" : "✗");
        }
    }

    /* Uji baris nol */
    printf("\n  Uji baris nol:\n");
    Mat BaZe = {{3, 4}, {0, 0}};
    cetak("Ada baris nol", BaZe, 2, 2);
    op_normalisasi_baris(BaZe, Hasil, 2, 2);

    /* ---- 11. CEK SIMETRIS ---- */
    judul("11. CEK SIMETRIS");
    cetak("Sym", Sym, 3, 3);
    printf("  Sym simetris? → %s\n", op_cek_simetris(Sym, 3) ? "YA ✓" : "TIDAK ✗");
    cetak("A (tidak simetris)", A, 3, 3);
    printf("  A simetris? → %s\n", op_cek_simetris(A, 3) ? "YA ✓" : "TIDAK ✗");
    printf("  Syarat: A[i][j] == A[j][i] untuk semua i,j\n");

    /* ---- 12. CEK DIAGONAL DOMINAN ---- */
    judul("12. CEK DIAGONAL DOMINAN");
    cetak("D (diagonal dominan)", D, 3, 3);
    int dom_D = op_cek_diag_dominan(D, 3);
    printf("  D diagonal dominan? → %s\n\n", dom_D ? "YA ✓" : "TIDAK ✗");

    cetak("A (bukan diagonal dominan)", A, 3, 3);
    int dom_A = op_cek_diag_dominan(A, 3);
    printf("  A diagonal dominan? → %s\n", dom_A ? "YA ✓" : "TIDAK ✗");
    printf("  Syarat: |A[i][i]| >= sigma_{j!=i} |A[i][j]|  untuk setiap i\n");

    printf("\n");
    printf("╔══════════════════════════════════════╗\n");
    printf("║  Selesai — semua operasi selesai.    ║\n");
    printf("╚══════════════════════════════════════╝\n\n");

    return 0;
}