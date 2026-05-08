/*
 * ============================================================
 *  op12_diag_dominan.c — DIAGONAL DOMINAN & ROTASI MATRIKS
 * ============================================================
 *  CEK DIAGONAL DOMINAN:
 *    Baris i dikatakan diagonal dominan jika:
 *      |A[i][i]| >= Σ_{j≠i} |A[i][j]|
 *    Matriks diagonal dominan: berlaku untuk SEMUA baris.
 *    Ketat (strictly): |A[i][i]| > Σ_{j≠i} |A[i][j]|
 *
 *  ROTASI MATRIKS 90°:
 *    Rotasi searah jarum jam (clockwise):
 *      Hasil[j][N-1-i] = A[i][j]
 *    Rotasi berlawanan jarum jam (counter-clockwise):
 *      Hasil[N-1-j][i] = A[i][j]
 *
 *  OPERASI TAMBAHAN:
 *    - Flip horizontal (kiri-kanan)
 *    - Flip vertikal (atas-bawah)
 *    - Pergeseran melingkar baris (row circular shift)
 *    - Permutasi baris
 *
 *  Kompilasi : gcc -o op12_diag_dominan op12_diag_dominan.c -lm
 *  Jalankan  : ./op12_diag_dominan
 * ============================================================
 */

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define MAKS 10
#define EPS  1e-9

void cetakMatriks(const char *nama, int A[][MAKS], int N, int M) {
    printf("  %s (%dx%d):\n", nama, N, M);
    for (int i = 0; i < N; i++) {
        printf("  |");
        for (int j = 0; j < M; j++)
            printf(" %4d", A[i][j]);
        printf(" |\n");
    }
}

void cetakDouble(const char *nama, double A[][MAKS], int N, int M) {
    printf("  %s (%dx%d):\n", nama, N, M);
    for (int i = 0; i < N; i++) {
        printf("  |");
        for (int j = 0; j < M; j++)
            printf(" %6.2f", A[i][j]);
        printf(" |\n");
    }
}

/* ── CEK DIAGONAL DOMINAN ────────────────────────────────── */
/*
 * CekDiagDominan:
 * I.S. : A[N][N] terdefinisi.
 * F.S. : Mencetak detail setiap baris.
 *         return 1 jika semua baris dominan, 0 jika tidak.
 *
 * Algoritma:
 *   untuk i = 0..N-1:
 *     sigma = Σ_{j≠i} |A[i][j]|
 *     jika |A[i][i]| < sigma: return 0
 *   return 1
 *
 * Kompleksitas: O(N^2)
 */
int cekDiagDominan(double A[][MAKS], int N, int ketat) {
    int semua = 1;
    for (int i = 0; i < N; i++) {
        double sigma = 0.0;
        for (int j = 0; j < N; j++)
            if (j != i) sigma += fabs(A[i][j]);
        double diag = fabs(A[i][i]);
        int dominan = ketat ? (diag > sigma + EPS)
                            : (diag >= sigma - EPS);
        printf("    Baris %d: |%.2f| %s Σ=%.2f  →  %s\n",
               i, A[i][i],
               ketat ? ">" : ">=",
               sigma,
               dominan ? "OK ✓" : "GAGAL ✗");
        if (!dominan) semua = 0;
    }
    return semua;
}

/* ── PERBAIKAN: PERMUTASI BARIS untuk diagonal dominan ───── */
/*
 * UsahakanDiagDominan:
 * Mencoba mengurutkan ulang baris agar matriks diagonal dominan
 * dengan strategi greedy: tempatkan elemen terbesar di diagonal.
 *
 * Algoritma (greedy, bukan garanteed):
 *   untuk i = 0..N-1:
 *     cari baris j >= i yang punya |A[j][i]| terbesar
 *     tukar baris i dan j
 *
 * Catatan: Tidak selalu berhasil. Untuk solusi tepat gunakan
 *           algoritma Hungarian atau program linier.
 */
int usahakanDiagDominan(double A[][MAKS], double b[], int N) {
    for (int i = 0; i < N; i++) {
        /* Cari baris dengan elemen terbesar di kolom i */
        int maxBaris = i;
        for (int k = i+1; k < N; k++)
            if (fabs(A[k][i]) > fabs(A[maxBaris][i]))
                maxBaris = k;
        /* Tukar baris i dan maxBaris */
        if (maxBaris != i) {
            for (int j = 0; j < N; j++) {
                double tmp = A[i][j]; A[i][j] = A[maxBaris][j]; A[maxBaris][j] = tmp;
            }
            double tmp = b[i]; b[i] = b[maxBaris]; b[maxBaris] = tmp;
        }
    }
    return cekDiagDominan(A, N, 0);
}

/* ── ROTASI 90° SEARAH JARUM JAM ─────────────────────────── */
/*
 * Rotasi90CW (Clockwise):
 * Matriks NxM → Hasil MxN
 * Rumus: Hasil[j][N-1-i] = A[i][j]
 *
 * Visualisasi 3x3:
 *   A         →   A rotasi CW
 *   1 2 3         7 4 1
 *   4 5 6         8 5 2
 *   7 8 9         9 6 3
 */
void rotasi90CW(int A[][MAKS], int H[][MAKS], int N, int M) {
    /* Hasil berukuran M x N */
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            H[j][N-1-i] = A[i][j];
}

/* ── ROTASI 90° BERLAWANAN JARUM JAM ─────────────────────── */
/*
 * Rotasi90CCW (Counter-Clockwise):
 * Matriks NxM → Hasil MxN
 * Rumus: Hasil[M-1-j][i] = A[i][j]
 */
void rotasi90CCW(int A[][MAKS], int H[][MAKS], int N, int M) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            H[M-1-j][i] = A[i][j];
}

/* ── ROTASI 180° ─────────────────────────────────────────── */
void rotasi180(int A[][MAKS], int H[][MAKS], int N, int M) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            H[N-1-i][M-1-j] = A[i][j];
}

/* ── FLIP HORIZONTAL (kiri-kanan) ────────────────────────── */
/*
 * FlipHorizontal:
 * Rumus: B[i][M-1-j] = A[i][j]
 */
void flipHorizontal(int A[][MAKS], int B[][MAKS], int N, int M) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            B[i][M-1-j] = A[i][j];
}

/* ── FLIP VERTIKAL (atas-bawah) ──────────────────────────── */
/*
 * FlipVertikal:
 * Rumus: B[N-1-i][j] = A[i][j]
 */
void flipVertikal(int A[][MAKS], int B[][MAKS], int N, int M) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            B[N-1-i][j] = A[i][j];
}

/* ── PERGESERAN BARIS MELINGKAR ──────────────────────────── */
/*
 * GeserBarisKanan:
 * Geser setiap elemen baris i ke kanan sebanyak k posisi,
 * secara melingkar (wrap-around).
 * Rumus: B[i][(j+k) % M] = A[i][j]
 */
void geserBarisKanan(int A[][MAKS], int B[][MAKS], int N, int M, int k) {
    k = ((k % M) + M) % M; /* normalisasi k */
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            B[i][(j+k) % M] = A[i][j];
}

int main(void) {
    printf("╔══════════════════════════════════════╗\n");
    printf("║  OPERASI 12 — DIAGONAL DOMINAN &     ║\n");
    printf("║              ROTASI MATRIKS          ║\n");
    printf("╚══════════════════════════════════════╝\n\n");

    /* --- Diagonal Dominan --- */
    printf("── A. Cek Diagonal Dominan ──\n");
    double D[MAKS][MAKS] = {{7,1,2},{1,8,1},{2,1,9}};
    double B[MAKS][MAKS] = {{1,4,2},{3,2,1},{1,2,1}};
    int N = 3;

    printf("  Matriks D (diagonal dominan):\n");
    cetakDouble("D", D, N, N);
    printf("  Detail per baris (ketat):\n");
    printf("  D diagonal dominan ketat? : %s\n\n",
           cekDiagDominan(D, N, 1) ? "YA ✓" : "TIDAK ✗");

    printf("  Matriks B (bukan diagonal dominan):\n");
    cetakDouble("B", B, N, N);
    printf("  Detail per baris:\n");
    printf("  B diagonal dominan? : %s\n\n",
           cekDiagDominan(B, N, 0) ? "YA ✓" : "TIDAK ✗");

    /* --- Usahakan diagonal dominan dengan permutasi --- */
    printf("── Usahakan Diagonal Dominan (Permutasi Baris) ──\n");
    double C[MAKS][MAKS] = {{2,8,1},{5,1,3},{1,2,9}};
    double bc[] = {1, 2, 3};
    cetakDouble("C (sebelum permutasi)", C, N, N);
    printf("  Setelah permutasi:\n");
    int berhasil = usahakanDiagDominan(C, bc, N);
    cetakDouble("C (setelah permutasi)", C, N, N);
    printf("  Berhasil diagonal dominan? : %s\n\n",
           berhasil ? "YA ✓" : "TIDAK (perlu metode lain)");

    /* --- Rotasi --- */
    printf("── B. Rotasi Matriks ──\n");
    int A[MAKS][MAKS] = {{1,2,3},{4,5,6},{7,8,9}};
    int H[MAKS][MAKS] = {0};

    cetakMatriks("A (asli)", A, 3, 3);

    rotasi90CW(A, H, 3, 3);
    cetakMatriks("Rotasi 90° CW", H, 3, 3);
    memset(H, 0, sizeof(H));

    rotasi90CCW(A, H, 3, 3);
    cetakMatriks("Rotasi 90° CCW", H, 3, 3);
    memset(H, 0, sizeof(H));

    rotasi180(A, H, 3, 3);
    cetakMatriks("Rotasi 180°", H, 3, 3);
    memset(H, 0, sizeof(H));

    /* --- Flip --- */
    printf("── C. Flip Matriks ──\n");
    flipHorizontal(A, H, 3, 3);
    cetakMatriks("Flip Horizontal (kiri-kanan)", H, 3, 3);
    memset(H, 0, sizeof(H));

    flipVertikal(A, H, 3, 3);
    cetakMatriks("Flip Vertikal (atas-bawah)", H, 3, 3);
    memset(H, 0, sizeof(H));

    /* --- Geser melingkar --- */
    printf("── D. Pergeseran Baris Melingkar ──\n");
    geserBarisKanan(A, H, 3, 3, 1);
    cetakMatriks("Geser kanan k=1", H, 3, 3);
    memset(H, 0, sizeof(H));

    geserBarisKanan(A, H, 3, 3, 2);
    cetakMatriks("Geser kanan k=2", H, 3, 3);

    /* --- Demo non-persegi: rotasi 2x4 --- */
    printf("── E. Rotasi Matriks Non-Persegi (2x4) ──\n");
    int R[MAKS][MAKS] = {{1,2,3,4},{5,6,7,8}};
    int RH[MAKS][MAKS] = {0};
    cetakMatriks("R (2x4)", R, 2, 4);
    rotasi90CW(R, RH, 2, 4);
    cetakMatriks("R rotasi 90° CW → (4x2)", RH, 4, 2);

    return 0;
}
