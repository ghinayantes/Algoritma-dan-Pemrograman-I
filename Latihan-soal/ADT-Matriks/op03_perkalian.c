/*
 * ============================================================
 *  op03_perkalian.c — PERKALIAN MATRIKS
 * ============================================================
 *  Perkalian (A: NxK) × (B: KxP) → (C: NxP)
 *  Rumus: C[i][j] = Σ_{k=0}^{K-1} A[i][k] * B[k][j]
 *
 *  Sifat perkalian:
 *    TIDAK komutatif : AB ≠ BA (umumnya)
 *    Asosiatif       : (AB)C = A(BC)
 *    Distributif     : A(B+C) = AB + AC
 *    Elemen satuan   : AI = IA = A
 *
 *  Kompilasi : gcc -o op03_perkalian op03_perkalian.c
 *  Jalankan  : ./op03_perkalian
 * ============================================================
 */

#include <stdio.h>

#define MAKS 10

void cetakMatriks(const char *nama, int A[][MAKS], int baris, int kol) {
    printf("  %s (%dx%d):\n", nama, baris, kol);
    for (int i = 0; i < baris; i++) {
        printf("  |");
        for (int j = 0; j < kol; j++)
            printf(" %5d", A[i][j]);
        printf(" |\n");
    }
}

/* ── PERKALIAN MATRIKS ───────────────────────────────────── */
/*
 * KaliMatriks:
 * I.S. : A[N][K] dan B[K][P] terdefinisi.
 *         C[N][P] sudah diinisialisasi nol.
 * F.S. : C[i][j] = Σ_{k} A[i][k] * B[k][j]
 *
 * Algoritma triple-loop (naif):
 *   untuk i = 0..N-1:          <- baris C / baris A
 *     untuk j = 0..P-1:        <- kolom C / kolom B
 *       C[i][j] = 0
 *       untuk k = 0..K-1:      <- dimensi dalam (dot product)
 *         C[i][j] += A[i][k] * B[k][j]
 *
 * Kompleksitas: O(N * K * P)  — kubik jika persegi (N=K=P)
 */
void kaliMatriks(int A[][MAKS], int B[][MAKS], int C[][MAKS],
                 int N, int K, int P) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < P; j++) {
            C[i][j] = 0;
            for (int k = 0; k < K; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
}

/* ── MATRIKS IDENTITAS ───────────────────────────────────── */
void buatIdentitas(int I[][MAKS], int N) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            I[i][j] = (i == j) ? 1 : 0;
}

int matriksSetara(int A[][MAKS], int B[][MAKS], int N, int P) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < P; j++)
            if (A[i][j] != B[i][j]) return 0;
    return 1;
}

int main(void) {
    printf("╔══════════════════════════════════════╗\n");
    printf("║      OPERASI 3 — PERKALIAN MATRIKS   ║\n");
    printf("╚══════════════════════════════════════╝\n\n");

    /* --- Demo 1: Persegi 3x3 --- */
    printf("── Demo 1: Persegi 3x3 ──\n");
    int A[MAKS][MAKS] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int B[MAKS][MAKS] = {{9, 8, 7}, {6, 5, 4}, {3, 2, 1}};
    int C[MAKS][MAKS] = {0};
    int D[MAKS][MAKS] = {0};

    cetakMatriks("A", A, 3, 3);
    cetakMatriks("B", B, 3, 3);
    kaliMatriks(A, B, C, 3, 3, 3);
    cetakMatriks("C = A × B", C, 3, 3);
    kaliMatriks(B, A, D, 3, 3, 3);
    cetakMatriks("D = B × A", D, 3, 3);
    printf("  Komutatif (A×B = B×A)? : %s\n\n",
           matriksSetara(C, D, 3, 3) ? "YA" : "TIDAK ✗ (memang tidak harus sama)");

    /* --- Demo 2: Non-persegi (2x3) × (3x4) → (2x4) --- */
    printf("── Demo 2: (2x3) × (3x4) = (2x4) ──\n");
    int E[MAKS][MAKS] = {{1, 2, 3}, {4, 5, 6}};             /* 2x3 */
    int F[MAKS][MAKS] = {{7, 8, 9, 10}, {11, 12, 13, 14}, {15, 16, 17, 18}}; /* 3x4 */
    int G[MAKS][MAKS] = {0};                                 /* 2x4 */

    cetakMatriks("E (2x3)", E, 2, 3);
    cetakMatriks("F (3x4)", F, 3, 4);
    kaliMatriks(E, F, G, 2, 3, 4);
    cetakMatriks("G = E × F (2x4)", G, 2, 4);

    /* --- Demo 3: Sifat A × I = A --- */
    printf("── Demo 3: Sifat A × I = A ──\n");
    int I3[MAKS][MAKS] = {0};
    int H[MAKS][MAKS]  = {0};
    buatIdentitas(I3, 3);
    cetakMatriks("I (identitas 3x3)", I3, 3, 3);
    kaliMatriks(A, I3, H, 3, 3, 3);
    cetakMatriks("A × I", H, 3, 3);
    printf("  A × I = A? : %s\n\n",
           matriksSetara(A, H, 3, 3) ? "BENAR ✓" : "SALAH ✗");

    printf("  Rumus: C[i][j] = Σ_k A[i][k] * B[k][j]\n");
    printf("  Syarat: kolom(A) = baris(B) = K\n");
    printf("  Kompleksitas: O(N × K × P)\n");
    return 0;
}
