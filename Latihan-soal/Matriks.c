#include <stdio.h>
#include "Matriks.h"

void BuatMatriks (Matriks *A, int n) {
   int i, j;
   A->M = (ElMatriks**)malloc(n * sizeof(ElMatriks));
   A->N = n;
   if(A->M != NULL) {
      for(i = 0; i < n; i++) {
         A->M[i] = (ElMatriks*)malloc(n * sizeof(ElMatriks));
      }
      if (A->M[i] != NULL) {
         for (j = 0; j < n; j++) {
            A->M[i][j] = 0.0;
         }
      }
   }
}
/* Mengalokasikan matriks NxN dengan semua elemen bernilai 0.0.
   I.S. A sembarang, n > 0.
   F.S. A.M teralokasi, A.N = n, semua A.M[i][j] = 0.0. */
 
void HapusMatriks (Matriks *A) {
   int i;
   for(i = 0; i < A->N; i++) {
      free(A->M[i]);
      A->M[i] = NULL;
   }
   free(A->M);
   A->M = NULL;
   A->N = 0;
}
/* Membebaskan memori yang dialokasikan untuk A.
   I.S. A.M teralokasi.
   F.S. Memori dibebaskan, A.M = NULL, A.N = 0. */
 
void SalinMatriks (Matriks A, Matriks *B) {
   int i, j;
   // BuatMatriks(B, A.N);
   for(i = 0; i < A.N; i++) {
      for(j = 0; j < A.N; j++) {
         B->M[i][j] = A.M[i][j];
      }
   }
}
/* Menyalin isi A ke B (deep copy).
   I.S. A terdefinisi; B sudah dialokasikan dengan ukuran sama (B.N = A.N).
   F.S. B.M[i][j] = A.M[i][j] untuk semua i,j. */
 
 
/* ===================== PREDIKAT ======================== */
 
boolean MatriksSetara (Matriks A, Matriks B) {
   int i, j;
   if(A.N != B.N) return false;
   else {
      for(i = 0; i < A.N; i++) {
         for(j = 0; j < A.N; j++) {
            if(abs(A.M[i][j] - B.M[i][j]) >= EPSILON) {
               return false;
            }
         }
      }
   }
   return true;
}
/* Mengembalikan true jika A dan B berukuran sama dan
   |A.M[i][j] - B.M[i][j]| < EPSILON untuk semua i,j. */
 
boolean MatriksSimetris (Matriks A) {
   int i, j;
   for(i = 0; i < A.N; i++) {
      for(j = 0; j < i; j++) {
         if (fabs(A.M[i][j] - A.M[j][i]) >= EPSILON) {
                return false;
         }
      }
   }
   return true
}
/* Mengembalikan true jika A[i][j] == A[j][i] untuk semua i,j. */
 
boolean MatriksDiagonalDominan (Matriks A) {
   int i, j;
   double diagonal = 0.0, el = 0.0;
   boolean dominan = true;
   for(i = 0; i < A.N; i++) {
      diagonal = 0.0;
      el = 0.0;
      for(j = 0; j < A.N; j++) {
         if(i != j) el += fabs(A.M[i][j]);
         else diagonal += fabs(A.M[i][j]);
      }
      if(diagonal < el) return false;
   }
   return true;
}
/* Mengembalikan true jika untuk setiap baris i:
   |A[i][i]| >= sigma |A[i][j]| untuk j != i. */
 
 
/* ===================== OPERASI ========================= */
 
void PenjumlahanMatriks (Matriks A, Matriks B, Matriks *C) {
   int i, j;
   // BuatMatriks(C, A.N);
   for(i = 0; i < A.N; i++) {
      for(j = 0; j < A.N; j++) {
         C->M[i][j] = A.M[i][j] + B.M[i][j];
      }
   }
}
/* C = A + B.
   Prekondisi: A.N = B.N; C sudah dialokasikan dengan C.N = A.N. */
 
void PerkalianMatriks (Matriks A, Matriks B, Matriks *C) {
   int i, j, k;
   for(i = 0; i < A.N; i++) {
      for(j = 0; j < A.N; j++) { 
         ElMatriks hasil = 0.0;
         for(k = 0; k < A.N; k++) {
            hasil += A.M[i][k] * B.M[k][j];
         }
         C->M[i][j] = hasil;
      }
   }
}
/* C = A x B.
   Prekondisi: A.N = B.N; C sudah dialokasikan dengan C.N = A.N.
   Catatan: C tidak boleh alias dengan A atau B. */
 
void TransposeMatriks (Matriks A, Matriks *B) {
   int i, j;
   for(i = 0; i < A.N; i++) {
      for(j = 0; j < A.N; j++) { 
         B->M[i][j] = A.M[j][i];
      }
   }
}
/* B = transpose(A).
   Prekondisi: B sudah dialokasikan dengan B.N = A.N. */
 
ElMatriks TraceMatriks (Matriks A) {
   ElMatriks tot = 0;
   int i;
   for(i = 0; i < A.N; i++) {
      tot += A.M[i][i];
   }
   return tot;
}
/* Mengembalikan trace A = sigma A[i][i]. */
 
void MatriksIdentitas (Matriks *A) {
   int i, j;
   for(i = 0; i < A.N; i++) {
      for(j = 0; j < A.N; j++) {
         if(i == j) A->M[i][j] = 1.0;
         else A->M[i][j] = 0.0;
      }
   }
}
/* Mengisi A dengan matriks identitas: A[i][i]=1, A[i][j]=0 untuk i!=j.
   Prekondisi: A sudah dialokasikan. */
 
void PerkalianSkalar (Matriks *A, ElMatriks k) {
   int i, j;
   for(i = 0; i < A.N; i++) {
      for(j = 0; j < A.N; j++) {
         A->M[i][j] = k * A->M[i][j];
      }
   }
}
/* Mengalikan semua elemen A dengan skalar k (in-place).
   I.S. A terdefinisi.
   F.S. A.M[i][j] = k * A.M[i][j] untuk semua i,j. */
 
ElMatriks DeterminanMatriks (Matriks A) {
   /* Mengembalikan determinan A menggunakan ekspansi kofaktor rekursif. */
    
    // Kasus Dasar: N=1 -> A[0][0]
    if (A.N == 1) {
        return A.M[0][0];
    }
    
    // Kasus Dasar: N=2 -> ad - bc
    if (A.N == 2) {
        return (A.M[0][0] * A.M[1][1]) - (A.M[0][1] * A.M[1][0]);
    }
    
    // Untuk N > 2: Ekspansi kofaktor sepanjang baris 0
    ElMatriks det = 0;
    int j, r, c, sub_j;
    Matriks subMatriks;
    
    for (j = 0; j < A.N; j++) {
        // Buat sub-matriks untuk kofaktor (ukuran N-1 x N-1)
        BuatMatriks(&subMatriks, A.N - 1);
        
        // Isi sub-matriks dengan elemen-elemen yang bukan berada di baris 0 dan kolom j
        for (r = 1; r < A.N; r++) {
            sub_j = 0;
            for (c = 0; c < A.N; c++) {
               if (c == j) continue; // Lewati kolom j
               subMatriks.M[r - 1][sub_j] = A.M[r][c];
               sub_j++;
            }
        }
        
        // Rumus: det += (-1)^j * A[0][j] * det(subMatriks)
        if (j % 2 == 0) {
            det += A.M[0][j] * DeterminanMatriks(subMatriks);
        } else {
            det -= A.M[0][j] * DeterminanMatriks(subMatriks);
        }
        
        // Bebaskan memori sub-matriks setelah digunakan
        HapusMatriks(&subMatriks);
    }
    
    return det;
}
/* Mengembalikan determinan A menggunakan ekspansi kofaktor rekursif.
   Kasus dasar: N=1 -> A[0][0]; N=2 -> ad-bc.
   Untuk N>2: ekspansi sepanjang baris 0. */
 
 
/* ===================== OUTPUT ========================== */
 
void CetakMatriks (Matriks A) {
   int i, j;
   for(i = 0; i < A.N; i++) {
      for(j = 0; j < A.N; j++) {
         printf("%.2f", A.M[i][j]);
         if(j != A.N - 1) printf(" ");
      }
      printf("\n");
   }
}
/* Mencetak matriks A baris per baris.
   Format: setiap elemen dicetak dengan '%.2f' diikuti spasi,
   tiap baris diakhiri newline.
   Contoh (2x2):
   1.00 2.00
   3.00 4.00  */