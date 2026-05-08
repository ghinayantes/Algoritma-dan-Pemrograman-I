/*
 * ============================================================
 *  op11_jacobi.c — METODE ITERASI JACOBI & GAUSS-SEIDEL
 * ============================================================
 *  Menyelesaikan sistem persamaan linear Ax = b secara iteratif.
 *
 *  METODE JACOBI:
 *    x[i]^(k+1) = ( b[i] - Σ_{j≠i} A[i][j]*x[j]^(k) ) / A[i][i]
 *    Semua x baru dihitung dari x lama.
 *
 *  METODE GAUSS-SEIDEL:
 *    x[i]^(k+1) = ( b[i] - Σ_{j<i} A[i][j]*x[j]^(k+1)
 *                         - Σ_{j>i} A[i][j]*x[j]^(k)  ) / A[i][i]
 *    Langsung pakai nilai x baru begitu tersedia.
 *
 *  SYARAT KONVERGENSI: A diagonal dominan
 *    |A[i][i]| > Σ_{j≠i} |A[i][j]|  untuk semua i
 *
 *  Kompilasi : gcc -o op11_jacobi op11_jacobi.c -lm
 *  Jalankan  : ./op11_jacobi
 * ============================================================
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define MAKS 10
#define EPS  1e-9

/* ── UTILITAS ────────────────────────────────────────────── */

void cetakMatriks(const char *nama, double A[][MAKS], int N) {
    printf("  %s:\n", nama);
    for (int i = 0; i < N; i++) {
        printf("  |");
        for (int j = 0; j < N; j++)
            printf(" %7.3f", A[i][j]);
        printf(" | x[%d] |\n", i);
    }
}

void cetakVektor(const char *nama, double *v, int N) {
    printf("  %s = [", nama);
    for (int i = 0; i < N; i++)
        printf(" %.6f%s", v[i], i < N-1 ? "," : "");
    printf(" ]\n");
}

/* Norma L∞: max |v[i]| */
double normaLinf(double *v, int N) {
    double mx = 0.0;
    for (int i = 0; i < N; i++)
        if (fabs(v[i]) > mx) mx = fabs(v[i]);
    return mx;
}

/* Residual: max |( Σ_j A[i][j]*x[j] ) - b[i]| */
double residual(double A[][MAKS], double *b, double *x, int N) {
    double mx = 0.0;
    for (int i = 0; i < N; i++) {
        double s = -b[i];
        for (int j = 0; j < N; j++) s += A[i][j] * x[j];
        if (fabs(s) > mx) mx = fabs(s);
    }
    return mx;
}

/* Cek diagonal dominan */
int diagDominan(double A[][MAKS], int N) {
    for (int i = 0; i < N; i++) {
        double sigma = 0.0;
        for (int j = 0; j < N; j++)
            if (j != i) sigma += fabs(A[i][j]);
        if (fabs(A[i][i]) < sigma - EPS) return 0;
    }
    return 1;
}

/* ── METODE JACOBI ───────────────────────────────────────── */
/*
 * MetodeJacobi:
 * I.S. : A[N][N], b[N], x[N] (tebakan awal), maks_iter, tol.
 * F.S. : x diisi solusi aproksimasi.
 *         return jumlah iterasi jika konvergen, -1 jika tidak.
 *
 * Algoritma:
 *   x_baru = alokasikan N
 *   untuk iter = 1..maks_iter:
 *     untuk i = 0..N-1:
 *       sigma = b[i]
 *       untuk j = 0..N-1:
 *         jika j ≠ i: sigma -= A[i][j] * x[j]   ← x LAMA
 *       x_baru[i] = sigma / A[i][i]
 *     error = max |x_baru[i] - x[i]|
 *     x = x_baru (update sekaligus)
 *     jika error < tol: return iter
 *   return -1
 *
 * Perlu array x_baru terpisah agar semua x[j] lama masih ada.
 * Kompleksitas per iterasi: O(N^2)
 */
int metodeJacobi(double A[][MAKS], double *b, double *x,
                 int N, int maks_iter, double tol, int verbose) {
    double x_baru[MAKS];

    for (int iter = 1; iter <= maks_iter; iter++) {
        for (int i = 0; i < N; i++) {
            double sigma = b[i];
            for (int j = 0; j < N; j++)
                if (j != i) sigma -= A[i][j] * x[j];  /* x LAMA */
            x_baru[i] = sigma / A[i][i];
        }

        /* Hitung error = max |x_baru - x| */
        double err_vec[MAKS];
        for (int i = 0; i < N; i++)
            err_vec[i] = fabs(x_baru[i] - x[i]);
        double error = normaLinf(err_vec, N);

        /* Update x */
        for (int i = 0; i < N; i++) x[i] = x_baru[i];

        if (verbose)
            printf("    Iter %3d: error = %.2e  residual = %.2e\n",
                   iter, error, residual(A, b, x, N));

        if (error < tol) return iter;
    }
    return -1;
}

/* ── METODE GAUSS-SEIDEL ─────────────────────────────────── */
/*
 * MetodeGaussSeidel:
 * I.S. : Sama dengan MetodeJacobi.
 * F.S. : x diisi solusi. return jumlah iterasi atau -1.
 *
 * Perbedaan dari Jacobi:
 *   Tidak butuh x_baru terpisah.
 *   x[j<i] yang baru langsung dipakai dalam iterasi yang sama.
 *
 * Algoritma:
 *   untuk iter = 1..maks_iter:
 *     error_maks = 0
 *     untuk i = 0..N-1:
 *       sigma = b[i]
 *       untuk j = 0..N-1:
 *         jika j ≠ i: sigma -= A[i][j] * x[j]   ← x[j<i] BARU
 *       x_baru_i = sigma / A[i][i]
 *       error_maks = max(error_maks, |x_baru_i - x[i]|)
 *       x[i] = x_baru_i   ← langsung update
 *     jika error_maks < tol: return iter
 */
int metodeGaussSeidel(double A[][MAKS], double *b, double *x,
                      int N, int maks_iter, double tol, int verbose) {
    for (int iter = 1; iter <= maks_iter; iter++) {
        double error_maks = 0.0;
        for (int i = 0; i < N; i++) {
            double sigma = b[i];
            for (int j = 0; j < N; j++)
                if (j != i) sigma -= A[i][j] * x[j];  /* x[j<i] BARU */
            double xi_baru = sigma / A[i][i];
            double err_i   = fabs(xi_baru - x[i]);
            if (err_i > error_maks) error_maks = err_i;
            x[i] = xi_baru;  /* langsung update */
        }

        if (verbose)
            printf("    Iter %3d: error = %.2e  residual = %.2e\n",
                   iter, error_maks, residual(A, b, x, N));

        if (error_maks < tol) return iter;
    }
    return -1;
}

int main(void) {
    printf("╔══════════════════════════════════════╗\n");
    printf("║    OPERASI 11 — JACOBI & GAUSS-SEIDEL║\n");
    printf("╚══════════════════════════════════════╝\n\n");

    /* Sistem Ax = b, solusi eksak: x=[1, 1.5, 1] */
    double A[MAKS][MAKS] = {
        { 4,  1,  1},
        { 1,  5,  1},
        { 1,  1,  6}
    };
    double b[] = {6.5, 8.5, 8.5};
    int N = 3;

    cetakMatriks("A", A, N);
    printf("  b = [%.1f, %.1f, %.1f]\n", b[0], b[1], b[2]);
    printf("  Solusi eksak: x = [1.0, 1.5, 1.0] (approx)\n");
    printf("  Diagonal dominan? : %s\n\n",
           diagDominan(A, N) ? "YA ✓" : "TIDAK ✗");

    double tol = 1e-6;
    int maks = 100;

    /* --- Jacobi --- */
    printf("── Metode Jacobi (verbose) ──\n");
    double xJ[MAKS] = {0, 0, 0};
    int iterJ = metodeJacobi(A, b, xJ, N, maks, tol, 1 /*verbose*/);
    if (iterJ > 0) {
        printf("  Konvergen dalam %d iterasi\n", iterJ);
        cetakVektor("x (Jacobi)", xJ, N);
        printf("  Residual akhir: %.2e\n\n", residual(A, b, xJ, N));
    } else {
        printf("  TIDAK konvergen dalam %d iterasi\n\n", maks);
    }

    /* --- Gauss-Seidel --- */
    printf("── Metode Gauss-Seidel (verbose) ──\n");
    double xGS[MAKS] = {0, 0, 0};
    int iterGS = metodeGaussSeidel(A, b, xGS, N, maks, tol, 1 /*verbose*/);
    if (iterGS > 0) {
        printf("  Konvergen dalam %d iterasi\n", iterGS);
        cetakVektor("x (Gauss-Seidel)", xGS, N);
        printf("  Residual akhir : %.2e\n\n", residual(A, b, xGS, N));
    } else {
        printf("  TIDAK konvergen dalam %d iterasi\n\n", maks);
    }

    printf("── Perbandingan ──\n");
    printf("  Metode          │ Iterasi  │ Residual\n");
    printf("  ────────────────┼──────────┼──────────\n");
    printf("  Jacobi          │ %8d │ %.2e\n", iterJ,  residual(A, b, xJ,  N));
    printf("  Gauss-Seidel    │ %8d │ %.2e\n", iterGS, residual(A, b, xGS, N));

    /* --- Uji tidak diagonal dominan --- */
    printf("\n── Uji TIDAK Diagonal Dominan ──\n");
    double B[MAKS][MAKS] = {{1, 4}, {3, 1}};
    double bB[] = {5, 4};
    double xB[MAKS] = {0, 0};
    printf("  Diagonal dominan? : %s\n", diagDominan(B, 2) ? "YA" : "TIDAK ✗");
    int res = metodeJacobi(B, bB, xB, 2, 30, tol, 0);
    printf("  Jacobi konvergen? : %s\n", res > 0 ? "YA" : "TIDAK — divergen ✗");

    return 0;
}
