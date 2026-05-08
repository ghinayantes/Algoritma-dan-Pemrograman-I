#ifndef MATRIKS_H
#define MATRIKS_H
 
#include "boolean.h"
#include <stdlib.h>
#include <math.h>
 
#define EPSILON 1e-9
 
typedef double ElMatriks;
 
typedef struct {
    ElMatriks **M; /* M[i][j], 0-indexed */
    int        N;  /* ukuran: N baris, N kolom */
} Matriks;
 
 
/* ===================== KONSTRUKTOR/DESTRUKTOR ========== */
 
void BuatMatriks (Matriks *A, int n);
/* Mengalokasikan matriks NxN dengan semua elemen bernilai 0.0.
   I.S. A sembarang, n > 0.
   F.S. A.M teralokasi, A.N = n, semua A.M[i][j] = 0.0. */
 
void HapusMatriks (Matriks *A);
/* Membebaskan memori yang dialokasikan untuk A.
   I.S. A.M teralokasi.
   F.S. Memori dibebaskan, A.M = NULL, A.N = 0. */
 
void SalinMatriks (Matriks A, Matriks *B);
/* Menyalin isi A ke B (deep copy).
   I.S. A terdefinisi; B sudah dialokasikan dengan ukuran sama (B.N = A.N).
   F.S. B.M[i][j] = A.M[i][j] untuk semua i,j. */
 
 
/* ===================== PREDIKAT ======================== */
 
boolean MatriksSetara (Matriks A, Matriks B);
/* Mengembalikan true jika A dan B berukuran sama dan
   |A.M[i][j] - B.M[i][j]| < EPSILON untuk semua i,j. */
 
boolean MatriksSimetris (Matriks A);
/* Mengembalikan true jika A[i][j] == A[j][i] untuk semua i,j. */
 
boolean MatriksDiagonalDominan (Matriks A);
/* Mengembalikan true jika untuk setiap baris i:
   |A[i][i]| >= sigma |A[i][j]| untuk j != i. */
 
 
/* ===================== OPERASI ========================= */
 
void PenjumlahanMatriks (Matriks A, Matriks B, Matriks *C);
/* C = A + B.
   Prekondisi: A.N = B.N; C sudah dialokasikan dengan C.N = A.N. */
 
void PerkalianMatriks (Matriks A, Matriks B, Matriks *C);
/* C = A x B.
   Prekondisi: A.N = B.N; C sudah dialokasikan dengan C.N = A.N.
   Catatan: C tidak boleh alias dengan A atau B. */
 
void TransposeMatriks (Matriks A, Matriks *B);
/* B = transpose(A).
   Prekondisi: B sudah dialokasikan dengan B.N = A.N. */
 
ElMatriks TraceMatriks (Matriks A);
/* Mengembalikan trace A = sigma A[i][i]. */
 
void MatriksIdentitas (Matriks *A);
/* Mengisi A dengan matriks identitas: A[i][i]=1, A[i][j]=0 untuk i!=j.
   Prekondisi: A sudah dialokasikan. */
 
void PerkalianSkalar (Matriks *A, ElMatriks k);
/* Mengalikan semua elemen A dengan skalar k (in-place).
   I.S. A terdefinisi.
   F.S. A.M[i][j] = k * A.M[i][j] untuk semua i,j. */
 
ElMatriks DeterminanMatriks (Matriks A);
/* Mengembalikan determinan A menggunakan ekspansi kofaktor rekursif.
   Kasus dasar: N=1 -> A[0][0]; N=2 -> ad-bc.
   Untuk N>2: ekspansi sepanjang baris 0. */
 
 
/* ===================== OUTPUT ========================== */
 
void CetakMatriks (Matriks A);
/* Mencetak matriks A baris per baris.
   Format: setiap elemen dicetak dengan '%.2f' diikuti spasi,
   tiap baris diakhiri newline.
   Contoh (2x2):
   1.00 2.00
   3.00 4.00  */
 
#endif
