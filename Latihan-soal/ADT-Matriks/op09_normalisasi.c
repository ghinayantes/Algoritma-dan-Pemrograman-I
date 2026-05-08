/*
 * ============================================================
 *  op09_normalisasi.c — NORMALISASI & NORMA MATRIKS
 * ============================================================
 *  Normalisasi baris: membagi setiap baris dengan norma-nya
 *  sehingga setiap baris menjadi vektor satuan.
 *
 *  JENIS NORMA VEKTOR:
 *    L1  (Manhattan) : ||v||_1   = Σ |v[i]|
 *    L2  (Euclidean) : ||v||_2   = sqrt(Σ v[i]^2)
 *    L∞  (Maximum)  : ||v||_inf = max |v[i]|
 *
 *  JENIS NORMA MATRIKS:
 *    Frobenius : ||A||_F   = sqrt(Σ Σ A[i][j]^2)
 *    Norma-1   : ||A||_1   = max_j Σ_i |A[i][j]|  (max column sum)
 *    Norma-∞   : ||A||_inf = max_i Σ_j |A[i][j]|  (max row sum)
 *
 *  Kompilasi : gcc -o op09_normalisasi op09_normalisasi.c -lm
 *  Jalankan  : ./op09_normalisasi
 * ============================================================
 */

#include <stdio.h>
#include <math.h>
#include <string.h>

#define MAKS 10
#define EPS  1e-9

void cetakMatriks(const char *nama, double A[][MAKS], int N, int M) {
    printf("  %s (%dx%d):\n", nama, N, M);
    for (int i = 0; i < N; i++) {
        printf("  |");
        for (int j = 0; j < M; j++)
            printf(" %8.4f", A[i][j]);
        printf(" |\n");
    }
}

/* ── NORMA VEKTOR ────────────────────────────────────────── */

/* Norma L1 (Manhattan) baris i */
double normaL1(double A[][MAKS], int i, int M) {
    double s = 0.0;
    for (int j = 0; j < M; j++)
        s += fabs(A[i][j]);
    return s;
}

/* Norma L2 (Euclidean) baris i */
double normaL2(double A[][MAKS], int i, int M) {
    double s = 0.0;
    for (int j = 0; j < M; j++)
        s += A[i][j] * A[i][j];
    return sqrt(s);
}

/* Norma L∞ (Maksimum) baris i */
double normaLinf(double A[][MAKS], int i, int M) {
    double mx = 0.0;
    for (int j = 0; j < M; j++)
        if (fabs(A[i][j]) > mx) mx = fabs(A[i][j]);
    return mx;
}

/* ── NORMALISASI BARIS ───────────────────────────────────── */
/*
 * NormalisasiBaris:
 * I.S. : A[N][M] terdefinisi.
 * F.S. : Setiap baris A dibagi normaL2-nya (in-place).
 *         Jika ada baris nol: tidak diubah, return 0.
 *
 * Algoritma:
 *   1. Cek semua norma terlebih dahulu (atomisitas).
 *   2. Bagi setiap baris dengan norma-nya.
 *
 * Kompleksitas: O(N * M)
 */
int normalisasiBaris(double A[][MAKS], int N, int M) {
    /* Tahap 1: validasi semua norma */
    for (int i = 0; i < N; i++)
        if (normaL2(A, i, M) < EPS) {
            printf("  [!] Baris %d nol — normalisasi dibatalkan\n", i);
            return 0;
        }
    /* Tahap 2: normalisasi */
    for (int i = 0; i < N; i++) {
        double n = normaL2(A, i, M);
        for (int j = 0; j < M; j++)
            A[i][j] /= n;
    }
    return 1;
}

/* ── NORMA MATRIKS FROBENIUS ─────────────────────────────── */
/*
 * NormaFrobenius:
 * ||A||_F = sqrt(Σ_i Σ_j A[i][j]^2)
 *
 * Sifat:
 *   ||I_N||_F  = sqrt(N)
 *   ||A^T||_F  = ||A||_F
 *   ||kA||_F   = |k| * ||A||_F
 *
 * Kompleksitas: O(N * M)
 */
double normaFrobenius(double A[][MAKS], int N, int M) {
    double s = 0.0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            s += A[i][j] * A[i][j];
    return sqrt(s);
}

/* ── NORMA MATRIKS-1  (max column sum) ──────────────────── */
double normaMat1(double A[][MAKS], int N, int M) {
    double mx = 0.0;
    for (int j = 0; j < M; j++) {
        double cs = 0.0;
        for (int i = 0; i < N; i++) cs += fabs(A[i][j]);
        if (cs > mx) mx = cs;
    }
    return mx;
}

/* ── NORMA MATRIKS-∞  (max row sum) ─────────────────────── */
double normaMatInf(double A[][MAKS], int N, int M) {
    double mx = 0.0;
    for (int i = 0; i < N; i++) {
        double rs = 0.0;
        for (int j = 0; j < M; j++) rs += fabs(A[i][j]);
        if (rs > mx) mx = rs;
    }
    return mx;
}

int main(void) {
    printf("╔══════════════════════════════════════╗\n");
    printf("║    OPERASI 9 — NORMALISASI & NORMA   ║\n");
    printf("╚══════════════════════════════════════╝\n\n");

    double A[MAKS][MAKS] = {
        {3, 4,  0},
        {1, 0,  0},
        {2, 1,  2}
    };
    int N = 3, M = 3;

    cetakMatriks("A (asli)", A, N, M);

    /* --- Norma tiap baris --- */
    printf("── Norma Setiap Baris ──\n");
    for (int i = 0; i < N; i++) {
        printf("  Baris %d → L1=%.4f  L2=%.4f  L∞=%.4f\n",
               i,
               normaL1(A, i, M),
               normaL2(A, i, M),
               normaLinf(A, i, M));
    }

    /* --- Normalisasi L2 --- */
    printf("\n── Normalisasi Baris (L2) ──\n");
    double B[MAKS][MAKS];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            B[i][j] = A[i][j];  /* salin */

    if (normalisasiBaris(B, N, M)) {
        cetakMatriks("A ternormalisasi", B, N, M);
        printf("  Verifikasi norma setelah normalisasi:\n");
        for (int i = 0; i < N; i++)
            printf("    ||baris_%d||_2 = %.8f  %s\n",
                   i, normaL2(B, i, M),
                   fabs(normaL2(B, i, M) - 1.0) < 1e-6 ? "✓" : "✗");
    }

    /* --- Uji baris nol --- */
    printf("\n── Uji Baris Nol ──\n");
    double Z[MAKS][MAKS] = {{3, 4}, {0, 0}};
    cetakMatriks("Ada baris nol", Z, 2, 2);
    normalisasiBaris(Z, 2, 2);

    /* --- Norma matriks --- */
    printf("\n── Norma Matriks ──\n");
    cetakMatriks("A", A, N, M);
    printf("  ||A||_F   (Frobenius) = %.4f\n", normaFrobenius(A, N, M));
    printf("  ||A||_1   (max col)   = %.4f\n", normaMat1(A, N, M));
    printf("  ||A||_inf (max row)   = %.4f\n", normaMatInf(A, N, M));

    /* --- Sifat Frobenius ||I_N|| = sqrt(N) --- */
    printf("\n── Sifat ||I_N||_F = sqrt(N) ──\n");
    double I3[MAKS][MAKS] = {{1,0,0},{0,1,0},{0,0,1}};
    printf("  ||I_3||_F = %.4f  (sqrt(3) = %.4f)  %s\n",
           normaFrobenius(I3, 3, 3),
           sqrt(3.0),
           fabs(normaFrobenius(I3,3,3) - sqrt(3.0)) < EPS ? "✓" : "✗");

    return 0;
}
