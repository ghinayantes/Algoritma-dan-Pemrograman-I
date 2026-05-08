/*
 * ============================================================
 *  op02_penjumlahan.c — PENJUMLAHAN & PENGURANGAN MATRIKS
 * ============================================================
 *  Penjumlahan: C[i][j] = A[i][j] + B[i][j]
 *  Pengurangan: C[i][j] = A[i][j] - B[i][j]
 *  Syarat: A dan B harus berukuran sama (N x M).
 *
 *  Sifat penjumlahan:
 *    Komutatif : A + B = B + A
 *    Asosiatif : (A+B)+C = A+(B+C)
 *    Elemen nol: A + O = A  (O = matriks nol)
 *    Invers    : A + (-A) = O
 *
 *  Kompilasi : gcc -o op02_penjumlahan op02_penjumlahan.c
 *  Jalankan  : ./op02_penjumlahan
 * ============================================================
 */

#include <stdio.h>

#define MAKS 10

void cetakMatriks(const char *nama, int A[][MAKS], int N, int M) {
    printf("  %s (%dx%d):\n", nama, N, M);
    for (int i = 0; i < N; i++) {
        printf("  |");
        for (int j = 0; j < M; j++)
            printf(" %4d", A[i][j]);
        printf(" |\n");
    }
}

/* ── PENJUMLAHAN ─────────────────────────────────────────── */
/*
 * JumlahMatriks:
 * I.S. : A[N][M] dan B[N][M] terdefinisi.
 * F.S. : C[N][M] terisi, C[i][j] = A[i][j] + B[i][j].
 *
 * Algoritma:
 *   untuk i = 0..N-1:
 *     untuk j = 0..M-1:
 *       C[i][j] = A[i][j] + B[i][j]
 *
 * Kompleksitas: O(N * M)
 */
void jumlahMatriks(int A[][MAKS], int B[][MAKS], int C[][MAKS],
                   int N, int M) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            C[i][j] = A[i][j] + B[i][j];
}

/* ── PENGURANGAN ─────────────────────────────────────────── */
/*
 * KurangMatriks:
 * I.S. : A[N][M] dan B[N][M] terdefinisi.
 * F.S. : C[i][j] = A[i][j] - B[i][j].
 *
 * Kompleksitas: O(N * M)
 */
void kurangMatriks(int A[][MAKS], int B[][MAKS], int C[][MAKS],
                   int N, int M) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            C[i][j] = A[i][j] - B[i][j];
}

/* ── NEGASI (−A) ─────────────────────────────────────────── */
/*
 * NegatifMatriks:
 * I.S. : A[N][M] terdefinisi.
 * F.S. : B[i][j] = -A[i][j].
 *
 * Digunakan untuk membuktikan A + (-A) = O.
 */
void negatifMatriks(int A[][MAKS], int B[][MAKS], int N, int M) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            B[i][j] = -A[i][j];
}

/* ── Cek matriks nol ─────────────────────────────────────── */
int adalahMatriksNol(int A[][MAKS], int N, int M) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            if (A[i][j] != 0) return 0;
    return 1;
}

/* ── Cek kesetaraan ──────────────────────────────────────── */
int matriksSetara(int A[][MAKS], int B[][MAKS], int N, int M) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            if (A[i][j] != B[i][j]) return 0;
    return 1;
}

int main(void) {
    printf("╔══════════════════════════════════════╗\n");
    printf("║   OPERASI 2 — PENJUMLAHAN &          ║\n");
    printf("║              PENGURANGAN              ║\n");
    printf("╚══════════════════════════════════════╝\n\n");

    int N = 3, M = 3;
    int A[MAKS][MAKS] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int B[MAKS][MAKS] = {{9, 8, 7}, {6, 5, 4}, {3, 2, 1}};
    int C[MAKS][MAKS] = {0};
    int D[MAKS][MAKS] = {0};

    cetakMatriks("A", A, N, M);
    cetakMatriks("B", B, N, M);

    /* --- Penjumlahan --- */
    printf("── A + B ──\n");
    jumlahMatriks(A, B, C, N, M);
    cetakMatriks("C = A + B", C, N, M);

    /* --- Pengurangan --- */
    printf("── A - B ──\n");
    kurangMatriks(A, B, D, N, M);
    cetakMatriks("D = A - B", D, N, M);

    /* --- Verifikasi komutatif: A+B = B+A --- */
    printf("── Verifikasi Sifat ──\n");
    int BA[MAKS][MAKS] = {0};
    jumlahMatriks(B, A, BA, N, M);
    printf("  Komutatif  (A+B = B+A)  : %s\n",
           matriksSetara(C, BA, N, M) ? "BENAR ✓" : "SALAH ✗");

    /* --- Verifikasi A + (-A) = O --- */
    int negA[MAKS][MAKS] = {0};
    int hasil[MAKS][MAKS] = {0};
    negatifMatriks(A, negA, N, M);
    jumlahMatriks(A, negA, hasil, N, M);
    printf("  Invers add (A+(-A) = O) : %s\n\n",
           adalahMatriksNol(hasil, N, M) ? "BENAR ✓" : "SALAH ✗");

    printf("  Rumus penjumlahan : C[i][j] = A[i][j] + B[i][j]\n");
    printf("  Rumus pengurangan : C[i][j] = A[i][j] - B[i][j]\n");
    printf("  Kompleksitas      : O(N * M)\n");
    return 0;
}
