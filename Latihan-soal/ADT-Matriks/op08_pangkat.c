/*
 * ============================================================
 *  op08_pangkat.c — PANGKAT MATRIKS
 * ============================================================
 *  A^p = A × A × ... × A  (p kali)
 *
 *  Definisi:
 *    A^0 = I   (matriks identitas)
 *    A^1 = A
 *    A^p = A^(p-1) × A  untuk p >= 2
 *
 *  DUA METODE:
 *  ──────────
 *  1. Iteratif biasa   : A^p = kalikan A sebanyak p kali
 *     Kompleksitas     : O(p × N^3)
 *
 *  2. Fast Exponentiation (Eksponensiasi Cepat):
 *       A^p = I                    jika p = 0
 *       A^p = A                    jika p = 1
 *       A^p = (A^(p/2))^2          jika p genap
 *       A^p = A × (A^(p/2))^2     jika p ganjil
 *     Kompleksitas: O(log(p) × N^3)
 *
 *  Aplikasi:
 *    - Barisan Fibonacci via pangkat matriks
 *    - Rantai Markov (distribusi setelah p langkah)
 *    - Jalur panjang-p dalam graf
 *
 *  Kompilasi : gcc -o op08_pangkat op08_pangkat.c -lm
 *  Jalankan  : ./op08_pangkat
 * ============================================================
 */

#include <stdio.h>
#include <math.h>
#include <string.h>

#define MAKS 8
#define EPS  1e-9

typedef double Mat[MAKS][MAKS];

static int panggilKali = 0; /* hitung pemanggilan perkalian */

void cetakMatriks(const char *nama, Mat A, int N) {
    printf("  %s (%dx%d):\n", nama, N, N);
    for (int i = 0; i < N; i++) {
        printf("  |");
        for (int j = 0; j < N; j++) {
            if (fabs(A[i][j] - (int)A[i][j]) < EPS)
                printf(" %6.0f", A[i][j]);
            else
                printf(" %8.2f", A[i][j]);
        }
        printf(" |\n");
    }
}

void identitas(Mat I, int N) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            I[i][j] = (i==j) ? 1.0 : 0.0;
}

void salin(Mat src, Mat dst, int N) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            dst[i][j] = src[i][j];
}

void kaliMat(Mat A, Mat B, Mat C, int N) {
    panggilKali++;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
}

/* ── METODE 1: ITERATIF BIASA ────────────────────────────── */
/*
 * PangkatIteratif:
 * I.S. : A[N][N] terdefinisi, p >= 0.
 * F.S. : Hasil = A^p.
 *
 * Algoritma:
 *   Hasil = I
 *   untuk iter = 1..p:
 *     Temp = Hasil × A
 *     Hasil = Temp
 *
 * Jumlah perkalian: p
 * Kompleksitas: O(p × N^3)
 */
void pangkatIteratif(Mat A, Mat Hasil, int N, int p) {
    Mat Temp;
    identitas(Hasil, N);
    for (int iter = 0; iter < p; iter++) {
        kaliMat(Hasil, A, Temp, N);
        salin(Temp, Hasil, N);
    }
}

/* ── METODE 2: FAST EXPONENTIATION ──────────────────────── */
/*
 * PangkatCepat:
 * I.S. : A[N][N] terdefinisi, p >= 0.
 * F.S. : Hasil = A^p.
 *
 * Algoritma rekursif:
 *   Jika p = 0 → Hasil = I
 *   Jika p = 1 → Hasil = A
 *   Jika p genap:
 *     Half = PangkatCepat(A, p/2)
 *     Hasil = Half × Half
 *   Jika p ganjil:
 *     Half = PangkatCepat(A, p/2)
 *     Hasil = A × Half × Half
 *
 * Jumlah perkalian: ≈ 2 * log2(p)
 * Kompleksitas: O(log(p) × N^3)
 */
void pangkatCepat(Mat A, Mat Hasil, int N, int p) {
    if (p == 0) { identitas(Hasil, N); return; }
    if (p == 1) { salin(A, Hasil, N); return; }

    Mat Half, Temp;
    pangkatCepat(A, Half, N, p / 2);

    if (p % 2 == 0) {
        /* Hasil = Half^2 */
        kaliMat(Half, Half, Hasil, N);
    } else {
        /* Hasil = A × Half^2 */
        kaliMat(Half, Half, Temp, N);
        kaliMat(A, Temp, Hasil, N);
    }
}

int matriksSetara(Mat A, Mat B, int N) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (fabs(A[i][j] - B[i][j]) > 1e-6) return 0;
    return 1;
}

/* ── Fibonacci via Pangkat Matriks ───────────────────────── */
/*
 * F(n) dapat dihitung dengan:
 *   | F(n+1) |   | 1  1 |^n   | 1 |
 *   | F(n)   | = | 1  0 |   × | 0 |
 *
 * Jadi F(n) = (M^n)[1][0]  untuk M = {{1,1},{1,0}}
 */
long long fibonacci(int n) {
    if (n <= 1) return n;
    Mat M = {{1, 1}, {1, 0}};
    Mat Hasil;
    /* counter panggilKali tidak direset di sini */
    pangkatCepat(M, Hasil, 2, n);
    return (long long)Hasil[0][1];
}
/* Catatan: tidak ada pangkilKali, gunakan pangkatCepat langsung */
long long fibonacciCepat(int n) {
    if (n <= 1) return n;
    Mat M = {{1, 1}, {1, 0}};
    Mat Hasil;
    pangkatCepat(M, Hasil, 2, n);
    return (long long)round(Hasil[0][1]);
}

int main(void) {
    printf("╔══════════════════════════════════════╗\n");
    printf("║      OPERASI 8 — PANGKAT MATRIKS     ║\n");
    printf("╚══════════════════════════════════════╝\n\n");

    Mat A = {{1, 2}, {0, 1}};
    Mat H1, H2;
    int N = 2;

    cetakMatriks("A", A, N);

    /* --- A^0, A^1, A^3, A^5 --- */
    int pangkat[] = {0, 1, 2, 3, 5, 8};
    int jumlah = 6;
    for (int t = 0; t < jumlah; t++) {
        int p = pangkat[t];
        char nama[32];
        sprintf(nama, "A^%d", p);
        pangkatIteratif(A, H1, N, p);
        cetakMatriks(nama, H1, N);
    }

    /* --- Bandingkan jumlah perkalian: iteratif vs cepat untuk p=16 --- */
    printf("── Perbandingan Efisiensi (p=16, N=3) ──\n");
    Mat B = {{1, 1, 0}, {0, 1, 1}, {1, 0, 1}};
    int p = 16;

    panggilKali = 0;
    pangkatIteratif(B, H1, 3, p);
    int kali_iter = panggilKali;

    panggilKali = 0;
    pangkatCepat(B, H2, 3, p);
    int kali_cepat = panggilKali;

    printf("  Iteratif biasa  : %d perkalian matriks\n", kali_iter);
    printf("  Eksponensiasi cepat: %d perkalian matriks\n", kali_cepat);
    printf("  Hasil sama?     : %s\n\n",
           matriksSetara(H1, H2, 3) ? "BENAR ✓" : "SALAH ✗");

    /* --- Aplikasi: Fibonacci via pangkat matriks --- */
    printf("── Aplikasi: Fibonacci via Pangkat Matriks ──\n");
    printf("  F(n) = (M^n)[0][1]  di mana M = {{1,1},{1,0}}\n");
    int fn[] = {0,1,2,5,10,15,20};
    for (int t = 0; t < 7; t++)
        printf("  F(%2d) = %lld\n", fn[t], fibonacciCepat(fn[t]));

    printf("\n  Rumus iteratif : O(p × N^3)\n");
    printf("  Rumus cepat    : O(log(p) × N^3)\n");
    return 0;
}
