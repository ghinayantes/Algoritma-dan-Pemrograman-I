/*
 * ============================================================
 *  op06_trace.c — TRACE (JEJAK) MATRIKS
 * ============================================================
 *  Trace adalah jumlah elemen diagonal utama matriks persegi:
 *    trace(A) = Σ_{i=0}^{N-1} A[i][i]
 *
 *  Sifat trace:
 *    trace(A + B)  = trace(A) + trace(B)
 *    trace(kA)     = k * trace(A)
 *    trace(A^T)    = trace(A)
 *    trace(AB)     = trace(BA)  ← siklik, meskipun AB ≠ BA
 *    trace(I_N)    = N
 *
 *  Hubungan dengan nilai eigen:
 *    trace(A) = Σ λ_i  (jumlah semua nilai eigen A)
 *    det(A)   = Π λ_i  (hasil kali semua nilai eigen A)
 *
 *  Kompilasi : gcc -o op06_trace op06_trace.c
 *  Jalankan  : ./op06_trace
 * ============================================================
 */

#include <stdio.h>
#include <math.h>

#define MAKS 10
#define EPS  1e-9

void cetakMatriks(const char *nama, double A[][MAKS], int N) {
    printf("  %s (%dx%d):\n", nama, N, N);
    for (int i = 0; i < N; i++) {
        printf("  |");
        for (int j = 0; j < N; j++) {
            if (fabs(A[i][j] - (int)A[i][j]) < EPS)
                printf(" %6.0f", A[i][j]);
            else
                printf(" %6.2f", A[i][j]);
            /* tandai elemen diagonal */
            if (i == j) printf("*");
            else         printf(" ");
        }
        printf("|\n");
    }
    printf("  (* = elemen diagonal)\n");
}

/* ── TRACE ───────────────────────────────────────────────── */
/*
 * TraceMatriks:
 * I.S. : A[N][N] terdefinisi, N >= 1.
 * F.S. : Mengembalikan Σ A[i][i].
 *
 * Algoritma:
 *   tr = 0
 *   untuk i = 0..N-1:
 *     tr += A[i][i]
 *   return tr
 *
 * Kompleksitas: O(N)  — sangat efisien, hanya menyentuh diagonal
 */
double traceMatriks(double A[][MAKS], int N) {
    double tr = 0.0;
    for (int i = 0; i < N; i++)
        tr += A[i][i];
    return tr;
}

/* ── TRACE DARI HASIL KALI  trace(AB) ───────────────────── */
/*
 * TracePerkalian:
 * Menghitung trace(AB) TANPA menghitung AB secara penuh.
 *
 * Optimasi: trace(AB) = Σ_i Σ_k A[i][k] * B[k][i]
 * Hanya baris-i * kolom-i yang dibutuhkan (dot product).
 *
 * Kompleksitas: O(N^2) — sama dengan menghitung seluruh AB,
 *                         tetapi hemat ruang O(1) vs O(N^2).
 */
double tracePerkalian(double A[][MAKS], double B[][MAKS], int N) {
    double tr = 0.0;
    for (int i = 0; i < N; i++)
        for (int k = 0; k < N; k++)
            tr += A[i][k] * B[k][i];
    return tr;
}

/* ── Perkalian penuh (untuk verifikasi) ─────────────────── */
void kaliMat(double A[][MAKS], double B[][MAKS], double C[][MAKS], int N) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
}

int main(void) {
    printf("╔══════════════════════════════════════╗\n");
    printf("║       OPERASI 6 — TRACE (JEJAK)      ║\n");
    printf("╚══════════════════════════════════════╝\n\n");

    double A[MAKS][MAKS] = {
        {4, 3, 2},
        {1, 5, 7},
        {8, 6, 9}
    };
    double B[MAKS][MAKS] = {
        {1, 0, 2},
        {3, 1, 4},
        {0, 2, 1}
    };
    int N = 3;

    cetakMatriks("A", A, N);
    printf("  trace(A) = %.0f + %.0f + %.0f = %.4f\n\n",
           A[0][0], A[1][1], A[2][2], traceMatriks(A, N));

    /* --- trace(I) = N --- */
    printf("── trace(I_3) = N ──\n");
    double I[MAKS][MAKS] = {{1,0,0},{0,1,0},{0,0,1}};
    printf("  trace(I_3) = %.0f  (harus = 3) %s\n\n",
           traceMatriks(I, N),
           fabs(traceMatriks(I, N) - N) < EPS ? "✓" : "✗");

    /* --- trace(A^T) = trace(A) --- */
    printf("── Verifikasi trace(A^T) = trace(A) ──\n");
    double AT[MAKS][MAKS];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            AT[j][i] = A[i][j];
    printf("  trace(A)   = %.4f\n", traceMatriks(A, N));
    printf("  trace(A^T) = %.4f\n", traceMatriks(AT, N));
    printf("  Setara? : %s\n\n",
           fabs(traceMatriks(A,N) - traceMatriks(AT,N)) < EPS
           ? "BENAR ✓" : "SALAH ✗");

    /* --- trace(AB) = trace(BA) --- */
    printf("── Verifikasi trace(AB) = trace(BA) ──\n");
    double AB[MAKS][MAKS], BA[MAKS][MAKS];
    kaliMat(A, B, AB, N);
    kaliMat(B, A, BA, N);
    double tAB = traceMatriks(AB, N);
    double tBA = traceMatriks(BA, N);
    printf("  trace(AB) = %.4f\n", tAB);
    printf("  trace(BA) = %.4f\n", tBA);
    printf("  Setara?   : %s\n\n",
           fabs(tAB - tBA) < EPS ? "BENAR ✓" : "SALAH ✗");

    /* --- Optimasi trace(AB) tanpa alokasi penuh --- */
    printf("── Optimasi: trace(AB) tanpa menghitung AB penuh ──\n");
    double tAB_opt = tracePerkalian(A, B, N);
    printf("  trace(AB) cara penuh    = %.4f\n", tAB);
    printf("  trace(AB) cara optimasi = %.4f\n", tAB_opt);
    printf("  Setara?                 : %s\n\n",
           fabs(tAB - tAB_opt) < EPS ? "BENAR ✓" : "SALAH ✗");

    /* --- trace(kA) = k * trace(A) --- */
    printf("── Verifikasi trace(kA) = k * trace(A),  k=5 ──\n");
    double kA[MAKS][MAKS];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            kA[i][j] = 5.0 * A[i][j];
    printf("  trace(5A)      = %.4f\n", traceMatriks(kA, N));
    printf("  5 * trace(A)   = %.4f\n", 5.0 * traceMatriks(A, N));
    printf("  Setara?        : %s\n\n",
           fabs(traceMatriks(kA,N) - 5.0*traceMatriks(A,N)) < EPS
           ? "BENAR ✓" : "SALAH ✗");

    printf("  Rumus        : trace(A) = Σ A[i][i]\n");
    printf("  Kompleksitas : O(N)\n");
    return 0;
}
