/*
 * ============================================================
 *  op01_transpose.c — TRANSPOSE MATRIKS
 * ============================================================
 *  Transpose matriks A berukuran N x M menghasilkan matriks
 *  B berukuran M x N di mana: B[j][i] = A[i][j]
 *
 *  Sifat transpose:
 *    (A^T)^T = A
 *    (A+B)^T = A^T + B^T
 *    (AB)^T  = B^T * A^T  (urutan terbalik!)
 *
 *  Kompilasi : gcc -o op01_transpose op01_transpose.c
 *  Jalankan  : ./op01_transpose
 * ============================================================
 */

#include <stdio.h>

#define MAKS_BARIS 10
#define MAKS_KOL   10

/* ── Fungsi cetak matriks ──────────────────────────────────── */
void cetakMatriks(const char *nama, int A[][MAKS_KOL],
                  int baris, int kolom) {
    printf("  %s (%dx%d):\n", nama, baris, kolom);
    for (int i = 0; i < baris; i++) {
        printf("  |");
        for (int j = 0; j < kolom; j++)
            printf(" %4d", A[i][j]);
        printf(" |\n");
    }
}

/* ── Inti algoritma transpose ─────────────────────────────── */
/*
 * TransposeMatriks:
 * I.S. : A[N][M] terdefinisi
 * F.S. : B[M][N] terisi sehingga B[j][i] = A[i][j]
 *
 * Algoritma:
 *   untuk setiap i = 0..N-1:
 *     untuk setiap j = 0..M-1:
 *       B[j][i] = A[i][j]   <- tukar posisi indeks
 *
 * Kompleksitas waktu : O(N * M)
 * Kompleksitas ruang : O(M * N) untuk matriks hasil
 */
void transposeMatriks(int A[][MAKS_KOL], int B[][MAKS_KOL],
                      int N, int M) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            B[j][i] = A[i][j];
}

/* ── Transpose in-place (hanya untuk matriks persegi) ──────── */
/*
 * TransposeInPlace:
 * Menukar A[i][j] dengan A[j][i] hanya untuk i < j
 * (setengah segitiga atas) agar tidak tertukar dua kali.
 *
 * Kompleksitas waktu : O(N^2 / 2)  → O(N^2)
 */
void transposeInPlace(int A[][MAKS_KOL], int N) {
    for (int i = 0; i < N; i++)
        for (int j = i + 1; j < N; j++) {
            int tmp  = A[i][j];
            A[i][j]  = A[j][i];
            A[j][i]  = tmp;
        }
}

/* ── Verifikasi (A^T)^T = A ─────────────────────────────── */
int matriksSetara(int A[][MAKS_KOL], int B[][MAKS_KOL],
                  int baris, int kolom) {
    for (int i = 0; i < baris; i++)
        for (int j = 0; j < kolom; j++)
            if (A[i][j] != B[i][j]) return 0;
    return 1;
}

/* ── Main ─────────────────────────────────────────────────── */
int main(void) {
    printf("╔══════════════════════════════════════╗\n");
    printf("║       OPERASI 1 — TRANSPOSE          ║\n");
    printf("╚══════════════════════════════════════╝\n\n");

    /* --- Demo 1: Matriks non-persegi 3x4 --- */
    int N = 3, M = 4;
    int A[MAKS_BARIS][MAKS_KOL] = {
        { 1,  2,  3,  4},
        { 5,  6,  7,  8},
        { 9, 10, 11, 12}
    };
    int B[MAKS_KOL][MAKS_BARIS] = {0};  /* akan menjadi 4x3 */

    printf("── Demo 1: Matriks non-persegi (3x4) ──\n");
    cetakMatriks("A", A, N, M);
    transposeMatriks(A, B, N, M);
    cetakMatriks("A^T", B, M, N);

    /* Verifikasi (A^T)^T = A */
    int C[MAKS_BARIS][MAKS_KOL] = {0};
    transposeMatriks(B, C, M, N);
    printf("  Verifikasi (A^T)^T = A : %s\n\n",
           matriksSetara(A, C, N, M) ? "BENAR ✓" : "SALAH ✗");

    /* --- Demo 2: Transpose in-place matriks persegi 3x3 --- */
    int N2 = 3;
    int P[MAKS_BARIS][MAKS_KOL] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    printf("── Demo 2: Transpose in-place (3x3) ──\n");
    cetakMatriks("Sebelum", P, N2, N2);
    transposeInPlace(P, N2);
    cetakMatriks("Setelah transposeInPlace", P, N2, N2);

    printf("\n  Rumus: B[j][i] = A[i][j]\n");
    printf("  Ukuran: (%dx%d) → (%dx%d)\n", N, M, M, N);
    return 0;
}
