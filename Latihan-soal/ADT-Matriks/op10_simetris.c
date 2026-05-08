/*
 * ============================================================
 *  op10_simetris.c — DEKOMPOSISI SIMETRIS & ANTI-SIMETRIS
 * ============================================================
 *  Setiap matriks persegi dapat didekomposisi unik menjadi:
 *    A = S + K
 *  di mana:
 *    S = (A + A^T) / 2   →  S^T = S  (simetris)
 *    K = (A - A^T) / 2   →  K^T = -K  (anti-simetris / skew)
 *
 *  Sifat matriks simetris:
 *    A[i][j] = A[j][i]  untuk semua i,j
 *    Diagonal elemen anti-simetris selalu 0: K[i][i] = 0
 *
 *  Matriks definit positif (PD):
 *    A simetris DAN semua minor utama (leading principal minor) > 0
 *    Ekuivalen: semua nilai eigen > 0
 *
 *  Matriks ortogonal:
 *    A^T × A = I  ↔  A^T = A^(-1)
 *    Sifat: det(A) = ±1, kolom-kolomnya ortonormal
 *
 *  Kompilasi : gcc -o op10_simetris op10_simetris.c -lm
 *  Jalankan  : ./op10_simetris
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
            printf(" %7.3f", A[i][j]);
        printf(" |\n");
    }
}

void salin(Mat src, Mat dst, int N) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            dst[i][j] = src[i][j];
}

void kaliMat(Mat A, Mat B, Mat C, int N) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
}

/* ── DEKOMPOSISI SIMETRIS ────────────────────────────────── */
/*
 * BuatSimetris:
 * I.S. : A[N][N] terdefinisi.
 * F.S. : S[i][j] = (A[i][j] + A[j][i]) / 2
 *
 * Rumus: S = (A + A^T) / 2
 * Kompleksitas: O(N^2)
 */
void buatSimetris(Mat A, Mat S, int N) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            S[i][j] = (A[i][j] + A[j][i]) / 2.0;
}

/* ── DEKOMPOSISI ANTI-SIMETRIS ───────────────────────────── */
/*
 * BuatAntiSimetris:
 * I.S. : A[N][N] terdefinisi.
 * F.S. : K[i][j] = (A[i][j] - A[j][i]) / 2
 *         K[i][i] = 0 untuk semua i (diagonal selalu nol)
 *
 * Rumus: K = (A - A^T) / 2
 */
void buatAntiSimetris(Mat A, Mat K, int N) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            K[i][j] = (A[i][j] - A[j][i]) / 2.0;
}

/* ── CEK SIMETRIS ────────────────────────────────────────── */
/*
 * CekSimetris:
 * Return 1 jika A[i][j] = A[j][i] untuk semua i,j.
 * Hanya perlu cek segitiga atas (i < j).
 * Kompleksitas: O(N^2 / 2) → O(N^2)
 */
int cekSimetris(Mat A, int N) {
    for (int i = 0; i < N; i++)
        for (int j = i+1; j < N; j++)
            if (fabs(A[i][j] - A[j][i]) >= EPS) return 0;
    return 1;
}

/* ── CEK ANTI-SIMETRIS ───────────────────────────────────── */
int cekAntiSimetris(Mat A, int N) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (fabs(A[i][j] + A[j][i]) >= EPS) return 0;
    return 1;
}

/* ── CEK MATRIKS ORTOGONAL ───────────────────────────────── */
/*
 * CekOrtogonal:
 * A ortogonal jika A^T × A ≈ I.
 * Kolom-kolom A ortonormal.
 */
int cekOrtogonal(Mat A, int N) {
    Mat AT, Hasil;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            AT[j][i] = A[i][j];
    kaliMat(AT, A, Hasil, N);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            double harap = (i==j) ? 1.0 : 0.0;
            if (fabs(Hasil[i][j] - harap) >= 1e-6) return 0;
        }
    return 1;
}

/* ── SUBMATRIKS UTAMA & DETERMINAN ──────────────────────── */
double det2x2(double a, double b, double c, double d) {
    return a*d - b*c;
}

/* Determinan NxN rekursif */
double determinan(Mat A, int N);
void submat(Mat A, Mat S, int N, int r, int c) {
    int si = 0;
    for (int i = 0; i < N; i++) {
        if (i==r) continue;
        int sj = 0;
        for (int j = 0; j < N; j++) {
            if (j==c) continue;
            S[si][sj++] = A[i][j];
        }
        si++;
    }
}
double determinan(Mat A, int N) {
    if (N==1) return A[0][0];
    if (N==2) return A[0][0]*A[1][1]-A[0][1]*A[1][0];
    double d = 0; Mat S;
    for (int j = 0; j < N; j++) {
        submat(A, S, N, 0, j);
        d += (j%2==0?1:-1) * A[0][j] * determinan(S, N-1);
    }
    return d;
}

/* ── CEK DEFINIT POSITIF (Sylvester) ────────────────────── */
/*
 * CekDefinitPositif:
 * A definit positif ↔ simetris DAN semua minor utama ke-k > 0.
 * Minor utama ke-k = det(A[0..k-1][0..k-1])
 */
int cekDefinitPositif(Mat A, int N) {
    if (!cekSimetris(A, N)) return 0;
    for (int k = 1; k <= N; k++) {
        /* Ekstrak submatriks kxk pojok kiri atas */
        Mat Sub;
        for (int i = 0; i < k; i++)
            for (int j = 0; j < k; j++)
                Sub[i][j] = A[i][j];
        if (determinan(Sub, k) <= EPS) return 0;
    }
    return 1;
}

int main(void) {
    printf("╔══════════════════════════════════════╗\n");
    printf("║   OPERASI 10 — SIMETRIS & DEKOMPOSISI║\n");
    printf("╚══════════════════════════════════════╝\n\n");

    Mat A = {{4, 2, 6}, {8, 5, 3}, {1, 7, 9}};
    Mat S, K, Check;
    int N = 3;

    cetakMatriks("A (sembarang)", A, N);

    /* --- Dekomposisi --- */
    printf("── Dekomposisi A = S + K ──\n");
    buatSimetris(A, S, N);
    buatAntiSimetris(A, K, N);
    cetakMatriks("S = (A + A^T)/2  (simetris)", S, N);
    cetakMatriks("K = (A - A^T)/2  (anti-simetris)", K, N);

    /* Verifikasi S + K = A */
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            Check[i][j] = S[i][j] + K[i][j];
    int ok = 1;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (fabs(Check[i][j] - A[i][j]) >= EPS) { ok = 0; break; }
    printf("  Verifikasi S + K = A : %s\n\n", ok ? "BENAR ✓" : "SALAH ✗");

    printf("  S simetris?       : %s\n", cekSimetris(S, N) ? "YA ✓" : "TIDAK ✗");
    printf("  K anti-simetris?  : %s\n\n", cekAntiSimetris(K, N) ? "YA ✓" : "TIDAK ✗");

    /* --- Definit Positif --- */
    printf("── Cek Definit Positif ──\n");
    Mat PD = {{2, 1, 0}, {1, 3, 1}, {0, 1, 2}};
    cetakMatriks("PD", PD, N);
    printf("  PD definit positif? : %s\n\n",
           cekDefinitPositif(PD, N) ? "YA ✓" : "TIDAK ✗");

    Mat NoPD = {{1, 2}, {2, 1}};
    cetakMatriks("NoPD", NoPD, 2);
    printf("  NoPD definit positif? : %s  (det=%g)\n\n",
           cekDefinitPositif(NoPD, 2) ? "YA" : "TIDAK ✗",
           determinan(NoPD, 2));

    /* --- Ortogonal --- */
    printf("── Cek Matriks Ortogonal ──\n");
    /* Matriks rotasi 90 derajat */
    Mat Rot = {{ 0, -1}, {1, 0}};
    cetakMatriks("Rot (rotasi 90°)", Rot, 2);
    printf("  Rot ortogonal? : %s\n\n",
           cekOrtogonal(Rot, 2) ? "YA ✓" : "TIDAK ✗");

    /* Matriks biasa (bukan ortogonal) */
    cetakMatriks("A (3x3 sembarang)", A, N);
    printf("  A ortogonal?   : %s\n", cekOrtogonal(A, N) ? "YA" : "TIDAK ✗");

    return 0;
}
