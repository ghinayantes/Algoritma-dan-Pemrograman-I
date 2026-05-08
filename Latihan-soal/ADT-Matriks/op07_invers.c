/*
 * ============================================================
 *  op07_invers.c — INVERS MATRIKS
 * ============================================================
 *  Invers matriks A adalah matriks A^(-1) sehingga:
 *    A * A^(-1) = A^(-1) * A = I
 *
 *  Syarat: det(A) ≠ 0  (A non-singular / invertible)
 *
 *  DUA METODE:
 *  ──────────
 *  1. Metode Adjugat (Cramer):
 *       A^(-1) = Adj(A) / det(A)
 *       Adj(A)[i][j] = (-1)^(i+j) * det(Minor(j,i))
 *       Kompleksitas: O(N! * N^2) — sangat mahal
 *
 *  2. Eliminasi Gauss-Jordan (augmented matrix [A | I]):
 *       Transformasi [A | I] → [I | A^(-1)]
 *       Kompleksitas: O(N^3) — jauh lebih efisien
 *
 *  Kompilasi : gcc -o op07_invers op07_invers.c -lm
 *  Jalankan  : ./op07_invers
 * ============================================================
 */

#include <stdio.h>
#include <math.h>
#include <string.h>

#define MAKS 8
#define EPS  1e-9

typedef double Mat[MAKS][MAKS];

void cetakMatriks(const char *nama, Mat A, int N) {
    printf("  %s (%dx%d):\n", nama, N, N);
    for (int i = 0; i < N; i++) {
        printf("  |");
        for (int j = 0; j < N; j++)
            printf(" %8.4f", A[i][j]);
        printf(" |\n");
    }
}

void salinMat(Mat src, Mat dst, int N) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            dst[i][j] = src[i][j];
}

/* ── SUBMATRIKS MINOR ─────────────────────────────────────── */
void subMatriks(Mat A, Mat Sub, int N, int br, int kl) {
    int si = 0;
    for (int i = 0; i < N; i++) {
        if (i == br) continue;
        int sj = 0;
        for (int j = 0; j < N; j++) {
            if (j == kl) continue;
            Sub[si][sj++] = A[i][j];
        }
        si++;
    }
}

/* ── DETERMINAN REKURSIF ─────────────────────────────────── */
double det(Mat A, int N) {
    if (N == 1) return A[0][0];
    if (N == 2) return A[0][0]*A[1][1] - A[0][1]*A[1][0];
    double d = 0.0; Mat Sub;
    for (int j = 0; j < N; j++) {
        subMatriks(A, Sub, N, 0, j);
        d += (j%2==0?1:-1) * A[0][j] * det(Sub, N-1);
    }
    return d;
}

/* ── METODE 1: INVERS VIA ADJUGAT ────────────────────────── */
/*
 * InversAdjugat:
 * I.S. : A[N][N] terdefinisi; Inv[N][N] siap diisi.
 * F.S. : Jika det(A) == 0 → return 0 (gagal).
 *         Jika det(A) != 0 → Inv = A^(-1), return 1.
 *
 * Algoritma:
 *   1. Hitung d = det(A)
 *   2. Jika |d| < EPS: return 0
 *   3. Untuk setiap (i,j):
 *        Bangun Sub = minor(j,i)  ← perhatikan j,i (bukan i,j)
 *        Adj[i][j]  = (-1)^(i+j) * det(Sub)
 *   4. Inv[i][j] = Adj[i][j] / d
 *
 * Kompleksitas: O(N^2 * N!) — hanya cocok untuk N kecil (≤5)
 */
int inversAdjugat(Mat A, Mat Inv, int N) {
    double d = det(A, N);
    if (fabs(d) < EPS) return 0;
    if (N == 1) { Inv[0][0] = 1.0 / A[0][0]; return 1; }

    Mat Sub;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            subMatriks(A, Sub, N, j, i); /* minor(j,i) untuk adjugat */
            Inv[i][j] = ((i+j)%2==0?1:-1) * det(Sub, N-1) / d;
        }
    return 1;
}

/* ── METODE 2: INVERS VIA GAUSS-JORDAN ───────────────────── */
/*
 * InversGaussJordan:
 * Menggunakan matriks augmentasi [A | I] → [I | A^(-1)].
 *
 * I.S. : A[N][N] terdefinisi; Inv[N][N] siap diisi.
 * F.S. : Inv = A^(-1), return 1. Jika singular, return 0.
 *
 * Algoritma (eliminasi baris dasar):
 *   Buat aug[i][0..N-1]   = A[i][*]   (salin A)
 *   Buat aug[i][N..2N-1]  = I[i][*]   (identitas di kanan)
 *
 *   Untuk kolom pivot p = 0..N-1:
 *     1. Partial pivoting: tukar baris agar |aug[p][p]| maksimum
 *     2. Jika aug[p][p] ≈ 0: singular, return 0
 *     3. Normalisasi baris p: bagi seluruh baris dengan aug[p][p]
 *     4. Eliminasi: untuk setiap baris i ≠ p:
 *          faktor = aug[i][p]
 *          aug[i][*] -= faktor * aug[p][*]
 *
 *   Setelah selesai: Inv[i][j] = aug[i][N+j]
 *
 * Kompleksitas: O(N^3)
 */
int inversGaussJordan(Mat A, Mat Inv, int N) {
    /* Buat augmented matrix [A | I] berukuran N x 2N */
    double aug[MAKS][MAKS*2];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            aug[i][j] = A[i][j];
        for (int j = 0; j < N; j++)
            aug[i][N+j] = (i == j) ? 1.0 : 0.0;
    }

    for (int p = 0; p < N; p++) {
        /* Partial pivoting: cari baris dengan |aug[i][p]| terbesar */
        int maxBaris = p;
        for (int i = p+1; i < N; i++)
            if (fabs(aug[i][p]) > fabs(aug[maxBaris][p]))
                maxBaris = i;
        /* Tukar baris p dan maxBaris */
        for (int j = 0; j < 2*N; j++) {
            double tmp = aug[p][j];
            aug[p][j] = aug[maxBaris][j];
            aug[maxBaris][j] = tmp;
        }

        if (fabs(aug[p][p]) < EPS) return 0; /* singular */

        /* Normalisasi baris pivot */
        double pivot = aug[p][p];
        for (int j = 0; j < 2*N; j++)
            aug[p][j] /= pivot;

        /* Eliminasi semua baris selain p */
        for (int i = 0; i < N; i++) {
            if (i == p) continue;
            double faktor = aug[i][p];
            for (int j = 0; j < 2*N; j++)
                aug[i][j] -= faktor * aug[p][j];
        }
    }

    /* Ekstrak bagian kanan sebagai Inv */
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            Inv[i][j] = aug[i][N+j];
    return 1;
}

/* ── Verifikasi: A * Inv ≈ I ─────────────────────────────── */
void kaliMat(Mat A, Mat B, Mat C, int N) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
}

int dekatIdentitas(Mat A, int N) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            double harap = (i==j) ? 1.0 : 0.0;
            if (fabs(A[i][j] - harap) > 1e-6) return 0;
        }
    return 1;
}

int main(void) {
    printf("╔══════════════════════════════════════╗\n");
    printf("║         OPERASI 7 — INVERS           ║\n");
    printf("╚══════════════════════════════════════╝\n\n");

    Mat A = {{4, 3, 2}, {1, 5, 7}, {8, 6, 9}};
    Mat Inv1, Inv2, Check;
    int N = 3;

    cetakMatriks("A", A, N);
    printf("  det(A) = %.4f\n\n", det(A, N));

    /* --- Metode 1: Adjugat --- */
    printf("── Metode 1: Adjugat ──\n");
    if (inversAdjugat(A, Inv1, N)) {
        cetakMatriks("A^(-1) via Adjugat", Inv1, N);
        kaliMat(A, Inv1, Check, N);
        cetakMatriks("A × A^(-1)  (harus ≈ I)", Check, N);
        printf("  A × A^(-1) ≈ I ? : %s\n\n",
               dekatIdentitas(Check, N) ? "BENAR ✓" : "SALAH ✗");
    }

    /* --- Metode 2: Gauss-Jordan --- */
    printf("── Metode 2: Eliminasi Gauss-Jordan ──\n");
    if (inversGaussJordan(A, Inv2, N)) {
        cetakMatriks("A^(-1) via Gauss-Jordan", Inv2, N);
        kaliMat(A, Inv2, Check, N);
        cetakMatriks("A × A^(-1)  (harus ≈ I)", Check, N);
        printf("  A × A^(-1) ≈ I ? : %s\n\n",
               dekatIdentitas(Check, N) ? "BENAR ✓" : "SALAH ✗");
    }

    /* --- Uji matriks singular --- */
    printf("── Uji Matriks Singular ──\n");
    Mat Sing = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    cetakMatriks("Sing (baris 2 = baris1+baris0)", Sing, N);
    printf("  det(Sing) = %.6f\n", det(Sing, N));
    printf("  inversGaussJordan: %s\n\n",
           inversGaussJordan(Sing, Inv1, N) ? "berhasil" : "GAGAL — singular ✓");

    /* --- Bandingkan kedua metode --- */
    printf("── Perbandingan Kedua Metode ──\n");
    printf("  %-28s %-28s\n", "Adjugat", "Gauss-Jordan");
    printf("  %-28s %-28s\n", "O(N! × N^2)", "O(N^3)");
    printf("  %-28s %-28s\n", "Cocok untuk N ≤ 4", "Cocok untuk semua N");
    printf("  %-28s %-28s\n", "Berguna secara teoritis", "Dipakai di praktik");

    return 0;
}
