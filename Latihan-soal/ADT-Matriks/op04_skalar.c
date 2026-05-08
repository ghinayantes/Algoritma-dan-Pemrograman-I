/*
 * ============================================================
 *  op04_skalar.c — PERKALIAN SKALAR & OPERASI SKALAR LAINNYA
 * ============================================================
 *  Perkalian skalar: B[i][j] = k * A[i][j]
 *
 *  Operasi skalar lainnya:
 *    - Pembagian skalar : B[i][j] = A[i][j] / k  (k ≠ 0)
 *    - Modulo skalar    : B[i][j] = A[i][j] % k  (int)
 *    - Pangkat skalar   : B[i][j] = A[i][j] ^ k  (tiap elemen)
 *
 *  Sifat:
 *    k(A + B) = kA + kB  (distributif thd penjumlahan matriks)
 *    (k + l)A = kA + lA  (distributif thd penjumlahan skalar)
 *    k(AB)    = (kA)B = A(kB)
 *    1 * A    = A
 *    0 * A    = O  (matriks nol)
 *
 *  Kompilasi : gcc -o op04_skalar op04_skalar.c -lm
 *  Jalankan  : ./op04_skalar
 * ============================================================
 */

#include <stdio.h>
#include <math.h>

#define MAKS 10

void cetakInt(const char *nama, int A[][MAKS], int N, int M) {
    printf("  %s:\n", nama);
    for (int i = 0; i < N; i++) {
        printf("  |");
        for (int j = 0; j < M; j++)
            printf(" %5d", A[i][j]);
        printf(" |\n");
    }
}

void cetakDouble(const char *nama, double A[][MAKS], int N, int M) {
    printf("  %s:\n", nama);
    for (int i = 0; i < N; i++) {
        printf("  |");
        for (int j = 0; j < M; j++)
            printf(" %7.2f", A[i][j]);
        printf(" |\n");
    }
}

/* ── PERKALIAN SKALAR (integer) ──────────────────────────── */
/*
 * KaliSkalarInt:
 * I.S. : A[N][M] terdefinisi, k adalah skalar integer.
 * F.S. : B[i][j] = k * A[i][j]  untuk semua i,j.
 *
 * Kompleksitas: O(N * M)
 */
void kaliSkalarInt(int A[][MAKS], int B[][MAKS],
                   int N, int M, int k) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            B[i][j] = k * A[i][j];
}

/* ── PEMBAGIAN SKALAR (double) ───────────────────────────── */
/*
 * BagiSkalar:
 * I.S. : A[N][M] terdefinisi, k != 0.
 * F.S. : B[i][j] = A[i][j] / k
 *
 * Kompleksitas: O(N * M)
 */
void bagiSkalar(int A[][MAKS], double B[][MAKS],
                int N, int M, double k) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            B[i][j] = A[i][j] / k;
}

/* ── MODULO SKALAR ───────────────────────────────────────── */
/*
 * ModuloSkalar:
 * I.S. : A[N][M] terdefinisi, k > 0.
 * F.S. : B[i][j] = A[i][j] % k
 *
 * Berguna untuk operasi aritmatika modular.
 */
void moduloSkalar(int A[][MAKS], int B[][MAKS],
                  int N, int M, int k) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            B[i][j] = A[i][j] % k;
}

/* ── PANGKAT TIAP ELEMEN ─────────────────────────────────── */
/*
 * PangkatElemen:
 * I.S. : A[N][M] terdefinisi, p >= 0.
 * F.S. : B[i][j] = A[i][j]^p  (setiap elemen dipangkatkan)
 *
 * Catatan: BERBEDA dari pangkat matriks (A^p = A × A × ...)
 *           Ini adalah element-wise power.
 */
void pangkatElemen(int A[][MAKS], double B[][MAKS],
                   int N, int M, int p) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            B[i][j] = pow((double)A[i][j], p);
}

/* ── Verifikasi distributif: k(A+B) = kA + kB ──────────── */
int setaraInt(int A[][MAKS], int B[][MAKS], int N, int M) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            if (A[i][j] != B[i][j]) return 0;
    return 1;
}

int main(void) {
    printf("╔══════════════════════════════════════╗\n");
    printf("║     OPERASI 4 — PERKALIAN SKALAR     ║\n");
    printf("╚══════════════════════════════════════╝\n\n");

    int N = 3, M = 3;
    int A[MAKS][MAKS] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int B[MAKS][MAKS] = {0};
    double Bd[MAKS][MAKS] = {0};

    cetakInt("A", A, N, M);

    /* --- Perkalian skalar k=3 --- */
    printf("── k * A  (k = 3) ──\n");
    kaliSkalarInt(A, B, N, M, 3);
    cetakInt("3 * A", B, N, M);

    /* --- k=0 → matriks nol --- */
    printf("── k * A  (k = 0) ──\n");
    kaliSkalarInt(A, B, N, M, 0);
    cetakInt("0 * A (harus matriks nol)", B, N, M);

    /* --- k=-1 → negasi --- */
    printf("── k * A  (k = -1) ──\n");
    kaliSkalarInt(A, B, N, M, -1);
    cetakInt("-1 * A (negasi)", B, N, M);

    /* --- Pembagian skalar --- */
    printf("── A / k  (k = 2.0) ──\n");
    bagiSkalar(A, Bd, N, M, 2.0);
    cetakDouble("A / 2", Bd, N, M);

    /* --- Modulo skalar --- */
    printf("── A %% k  (k = 3) ──\n");
    moduloSkalar(A, B, N, M, 3);
    cetakInt("A mod 3", B, N, M);

    /* --- Pangkat elemen --- */
    printf("── A^2  (element-wise) ──\n");
    pangkatElemen(A, Bd, N, M, 2);
    cetakDouble("A^2 element-wise", Bd, N, M);

    /* --- Verifikasi distributif k(A+B) = kA + kB --- */
    printf("── Verifikasi Distributif: k(A+B) = kA + kB  (k=2) ──\n");
    int X[MAKS][MAKS] = {{2, 0, 1}, {3, 1, 2}, {0, 4, 1}};
    int AplusX[MAKS][MAKS] = {0};
    int kAplusX[MAKS][MAKS] = {0};
    int kA[MAKS][MAKS] = {0};
    int kX[MAKS][MAKS] = {0};
    int kAplusKX[MAKS][MAKS] = {0};

    /* k(A+X) */
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            AplusX[i][j] = A[i][j] + X[i][j];
    kaliSkalarInt(AplusX, kAplusX, N, M, 2);

    /* kA + kX */
    kaliSkalarInt(A, kA, N, M, 2);
    kaliSkalarInt(X, kX, N, M, 2);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            kAplusKX[i][j] = kA[i][j] + kX[i][j];

    printf("  k(A+B) = kA+kB? : %s\n\n",
           setaraInt(kAplusX, kAplusKX, N, M) ? "BENAR ✓" : "SALAH ✗");

    printf("  Rumus: B[i][j] = k * A[i][j]\n");
    printf("  Kompleksitas: O(N * M)\n");
    return 0;
}
