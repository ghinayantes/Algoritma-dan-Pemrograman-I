/*
 * ============================================================
 *  op05_determinan.c — DETERMINAN MATRIKS
 * ============================================================
 *  Determinan adalah skalar yang dihitung dari matriks persegi.
 *
 *  Basis:
 *    N=1 : det([[a]])      = a
 *    N=2 : det([[a,b],     = a*d - b*c
 *               [c,d]])
 *
 *  Rekursi (ekspansi kofaktor sepanjang baris 0):
 *    det(A) = Σ_{j=0}^{N-1}  A[0][j] * (-1)^j * det(Minor(0,j))
 *
 *  Minor(i,j) = submatriks (N-1)x(N-1) tanpa baris i & kolom j.
 *
 *  Sifat:
 *    det(I)    = 1
 *    det(AB)   = det(A) * det(B)
 *    det(A^T)  = det(A)
 *    det(kA)   = k^N * det(A)
 *    det ≠ 0   ↔ A invertible (non-singular)
 *
 *  Kompilasi : gcc -o op05_determinan op05_determinan.c -lm
 *  Jalankan  : ./op05_determinan
 * ============================================================
 */

#include <stdio.h>
#include <math.h>

#define MAKS 8    /* cukup untuk demo; ekspansi kofaktor O(N!) */
#define EPS  1e-9

typedef double Mat[MAKS][MAKS];

void cetakMatriks(const char *nama, Mat A, int N) {
    printf("  %s (%dx%d):\n", nama, N, N);
    for (int i = 0; i < N; i++) {
        printf("  |");
        for (int j = 0; j < N; j++) {
            if (fabs(A[i][j] - (int)A[i][j]) < EPS)
                printf(" %6.0f", A[i][j]);
            else
                printf(" %6.2f", A[i][j]);
        }
        printf(" |\n");
    }
}

/* ── BANGUN SUBMATRIKS MINOR ─────────────────────────────── */
/*
 * SubMatriks:
 * I.S. : A[N][N] terdefinisi; Sub[N-1][N-1] siap diisi.
 *         0 <= baris,kolom < N.
 * F.S. : Sub berisi A tanpa baris ke-baris dan kolom ke-kolom,
 *         diindeks ulang mulai dari 0.
 *
 * Algoritma:
 *   si = 0
 *   untuk i = 0..N-1:
 *     jika i == baris: lewati
 *     sj = 0
 *     untuk j = 0..N-1:
 *       jika j == kolom: lewati
 *       Sub[si][sj] = A[i][j]
 *       sj++
 *     si++
 *
 * Kompleksitas: O(N^2)
 */
void subMatriks(Mat A, Mat Sub, int N, int baris, int kolom) {
    int si = 0;
    for (int i = 0; i < N; i++) {
        if (i == baris) continue;
        int sj = 0;
        for (int j = 0; j < N; j++) {
            if (j == kolom) continue;
            Sub[si][sj++] = A[i][j];
        }
        si++;
    }
}

/* ── DETERMINAN REKURSIF ─────────────────────────────────── */
/*
 * Determinan:
 * I.S. : A[N][N] terdefinisi, N >= 1.
 * F.S. : Mengembalikan det(A).
 *
 * Kasus basis:
 *   N=1 : return A[0][0]
 *   N=2 : return A[0][0]*A[1][1] - A[0][1]*A[1][0]
 *
 * Rekursi (ekspansi sepanjang baris 0):
 *   det = 0
 *   untuk j = 0..N-1:
 *     bangun Sub = subMatriks(A, 0, j)
 *     tanda = (-1)^j
 *     det += tanda * A[0][j] * determinan(Sub, N-1)
 *
 * Kompleksitas: O(N!)  — sangat mahal untuk N besar
 *   N=4: 24 operasi basis
 *   N=8: 40320 operasi basis
 */
double determinan(Mat A, int N) {
    if (N == 1) return A[0][0];
    if (N == 2) return A[0][0]*A[1][1] - A[0][1]*A[1][0];

    double det = 0.0;
    Mat Sub;
    for (int j = 0; j < N; j++) {
        subMatriks(A, Sub, N, 0, j);
        double tanda = (j % 2 == 0) ? 1.0 : -1.0;
        det += tanda * A[0][j] * determinan(Sub, N - 1);
    }
    return det;
}

/* ── Verifikasi det(AB) = det(A)*det(B) ─────────────────── */
void kaliMat(Mat A, Mat B, Mat C, int N) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
}

int main(void) {
    printf("╔══════════════════════════════════════╗\n");
    printf("║       OPERASI 5 — DETERMINAN         ║\n");
    printf("╚══════════════════════════════════════╝\n\n");

    /* --- 1x1 --- */
    printf("── N = 1 ──\n");
    Mat A1 = {{7}};
    printf("  A = [7],  det = %.0f\n\n", determinan(A1, 1));

    /* --- 2x2 --- */
    printf("── N = 2 ──\n");
    Mat A2 = {{4, 3}, {2, 1}};
    cetakMatriks("A", A2, 2);
    printf("  det = 4*1 - 3*2 = %.0f\n\n", determinan(A2, 2));

    /* --- 3x3 --- */
    printf("── N = 3 ──\n");
    Mat A3 = {{4, 3, 2}, {1, 5, 7}, {8, 6, 9}};
    cetakMatriks("A", A3, 3);
    printf("  det(A) = %.4f\n\n", determinan(A3, 3));

    /* --- 4x4 --- */
    printf("── N = 4 ──\n");
    Mat A4 = {
        { 1,  2,  3,  4},
        { 5,  6,  7,  8},
        { 9, 10, 11, 12},
        {13, 14, 15, 16}
    };
    cetakMatriks("A (hampir singular)", A4, 4);
    printf("  det(A) = %.4f  (≈0 → hampir singular)\n\n",
           determinan(A4, 4));

    /* --- Matriks singular --- */
    printf("── Matriks singular ──\n");
    Mat Sing = {{1, 2}, {2, 4}};
    cetakMatriks("Sing", Sing, 2);
    double ds = determinan(Sing, 2);
    printf("  det = %.4f  →  %s\n\n", ds,
           fabs(ds) < EPS ? "SINGULAR (tidak punya invers)" : "non-singular");

    /* --- Verifikasi det(AB) = det(A)*det(B) --- */
    printf("── Verifikasi det(AB) = det(A)*det(B) ──\n");
    Mat B3 = {{1, 0, 2}, {3, 1, 4}, {0, 2, 1}};
    Mat AB;
    kaliMat(A3, B3, AB, 3);
    double dA  = determinan(A3, 3);
    double dB  = determinan(B3, 3);
    double dAB = determinan(AB,  3);
    printf("  det(A)      = %.4f\n", dA);
    printf("  det(B)      = %.4f\n", dB);
    printf("  det(A)*det(B)= %.4f\n", dA * dB);
    printf("  det(AB)     = %.4f\n",  dAB);
    printf("  Setara?     : %s\n\n",
           fabs(dA * dB - dAB) < 1e-6 ? "BENAR ✓" : "SALAH ✗");

    /* --- Verifikasi det(A^T) = det(A) --- */
    printf("── Verifikasi det(A^T) = det(A) ──\n");
    Mat AT;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            AT[j][i] = A3[i][j];
    printf("  det(A)   = %.4f\n", determinan(A3, 3));
    printf("  det(A^T) = %.4f\n", determinan(AT, 3));
    printf("  Setara?  : %s\n\n",
           fabs(determinan(A3,3) - determinan(AT,3)) < EPS
           ? "BENAR ✓" : "SALAH ✗");

    printf("  Metode    : Ekspansi kofaktor (rekursif)\n");
    printf("  Kompleksitas: O(N!)  — untuk N besar, gunakan eliminasi Gauss\n");
    return 0;
}
