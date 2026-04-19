#include <stdio.h>
#include "matrix.h"

/* REALISASI ADT
   kostruktor */
void CreateMatrix(int rows, int cols, Matrix *M) {
    int i,j;
    M->rows = rows;
    M->cols = cols;
    for(i = 0; i < rows; i++) {
        for(j = 0; j < cols; j++) {
            M->data[i][j] = 0.0;
        }
    }
}
/* I.S. rows dan cols terdefinisi dan valid (1 <= rows,cols <= MAX) */
/* F.S. Terbentuk matrix M dengan ukuran rows x cols */
/* Semua elemen diinisialisasi dengan 0.0 */

/* selektor */
int GetRows(Matrix M) {
    return M.rows;
}
/* Mengembalikan jumlah baris matrix M */

int GetCols(Matrix M) {
    return M.cols;
}
/* Mengembalikan jumlah kolom matrix M */

float *GetElement(Matrix *M, int row, int col) {
    if(row < 0 || row >= GetRows(*M) || col < 0 || col >= GetCols(*M)) {
        return NULL;
    }
    return &(M->data[row][col]);
}
/* Mengembalikan pointer ke elemen matrix M pada baris row dan kolom col */
/* Mengembalikan NULL jika row atau col tidak valid untuk matrix M */

/* Mutator */
bool SetElement(Matrix *M, int row, int col, float value) {
    if(row < 0 || row >= GetRows(*M) || col < 0 || col >= GetCols(*M)) return false;
    M->data[row][col] == value;
    return true;
}
/* I.S. M terdefinisi */
/* F.S. Jika row dan col valid, elemen M pada baris row dan kolom col bernilai value, mengembalikan true */
/*      Jika row atau col tidak valid, mengembalikan false */

/* Operasi Baca/Tulis */
void ReadMatrix(Matrix *M) {
    int rows, cols;
    do {
        scanf("%d %d", &rows, &cols);
    } while(rows < 0 || rows > MAX_ROWS || cols < 0 || cols > MAX_COLS);

    CreateMatrix(rows, cols, M);

    int i, j;
    for(i = 0; i < rows; i++) {
        for(j = 0; j < cols; j++) {
            scanf(" %f %f", M->data[i][j]);
        }
    }
}
/* I.S. M belum terdefinisi */
/* F.S. M terdefinisi dan diisi dengan nilai-nilai yang dibaca dari input */
/*      Meminta input ukuran matrix (rows, cols) hingga valid
        Valid: 0 < rows < MAX_ROWS and 0 < cols < MAX_COLS */
/*      Meminta input elemen matrix M sebanyak rows * cols 
        Format input: Setiap elemen dipisahkan oleh spasi
        Contoh input: 
        2 3
        1.0 2.0 3.0
        4.0 5.0 6.0
        Contoh input tidak valid:
        -1 -1
        2 3
        1.0 2.0 3.0
        4.0 5.0 6.0
*/

void PrintMatrix(Matrix M) {
    int i, j;

    for(i = 0; i < GetRows(M); i++) {
        (j = 0; j < GetCols(M); j++) {
            printf("%.2f", *GetElement(&M, i, j) );
            if(j < GetCols(M) - 1) printf(" ");
        }
        printf("\n");
    }
}
/* I.S. M terdefinisi */
/* F.S. Seluruh elemen M tertulis ke layar dalam format matrix */
/* Baris dipisahkan oleh newline, kolom dipisahkan oleh spasi */
/* Format output: Setiap elemen diformat "%.2f" */

/* Operator Relasional */
bool IsSymmetric(Matrix M) {
    // Cek dulu apakah persegi (opsional sih)
    if (!isSquare(M)) return false;

    int i, j;
    for (i = 0; i < GetRows(M); i++) {
        for (j = i + 1; j < GetCols(M); j++) {
            if (*GetElement(&M, i, j) != *GetElement(&M, j, i)) {
                return false;
            }
        }
    }
    return true;
}
/* Mengembalikan true jika M adalah matrix simetrik terhadap diagonal */
/* Matrix simetrik adalah matrix yang memiliki elemen tercermin oleh diagonal*/
/* Prekondisi: M adalah matrix persegi */

bool IsDiagonallyDominant(Matrix M) {
    for(i = 0; i < GetRows(M); i++){
        float sum = 0;
        for(j = 0; j < GetCols(M); j++){
            if(i != j){
                sum += *GetElement(&M1, i, j);
            }
        }
        if(fabs(*GetElement(&M1, i, i)) <= sum) return false;
    }
    return true;
}
/* Mengembalikan true jika M adalah matrix diagonal dominant */
/* |a[i][i]| > sum(|a[i][j]|) untuk j != i pada setiap baris i */
/* Hint: Gunakan fabs untuk melakukan abs terhadap float */

/* Operator Aritmatika */
Matrix *MultiplyMatrix(Matrix M1, Matrix M2) {
    // 1. Cek syarat perkalian
    if (GetCols(M1) != GetRows(M2)) return NULL;

    // 2. Alokasi memori untuk Matrix hasil
    Matrix *result = (Matrix *)malloc(sizeof(Matrix));
    
    // 3. Inisialisasi ukuran matriks hasil
    // Barisnya ikut M1, Kolomnya ikut M2
    CreateMatrix(GetRows(M1), GetCols(M2), result);

    int i, j, k;
    for (i = 0; i < GetRows(M1); i++) {
        for (j = 0; j < GetCols(M2); j++) {
            float tempSum = 0.0;
            // Loop k untuk mengalikan baris M1 dengan kolom M2
            for (k = 0; k < GetCols(M1); k++) {
                tempSum += (*GetElement(&M1, i, k)) * (*GetElement(&M2, k, j));
            }
            // Masukkan hasil penjumlahan ke matriks hasil
            *GetElement(result, i, j) = tempSum;
        }
    }

    return result;
}
/* Menghasilkan hasil perkalian matrix M1 dan M2 */
/* Mengembalikan NULL jika jumlah kolom M1 != jumlah baris M2 */
/* Hint: Gunakan Matrix* pointer = (Matrix *)malloc(sizeof(Matrix)) untuk menghasilkan pointer ke Matrix baru */
/* Jika anda membuat driver sendiri, jangan lupa di free ya -> free(pointer) */

Matrix *AddMatrix(Matrix M1, Matrix M2) {
    if((GetCols(M1) != GetCols(M2)) || GetRows(M1) != GetRows(M2)) return NULL;
    Matrix *result = (Matrix *)malloc(sizeof(Matrix));

    CreateMatrix(GetRows(M1), GetCols(M1), result);

    int i, j;
    for (i = 0; i < GetRows(M1); i++) {
        for (j = 0; j < GetCols(M2); j++) {
            *GetElement(result, i, j) = *GetElement(&M1, i, j) + *GetElement(&M2, i, j);
        }
    }
    return result;
}
/* Menghasilkan hasil penjumlahan matrix M1 dan M2 */
/* Mengembalikan NULL jika ukuran matrix M1 dan M2 berbeda */
/* Hint: Gunakan Matrix* pointer = (Matrix *)malloc(sizeof(Matrix)) untuk menghasilkan pointer ke Matrix baru */
/* Jika anda membuat driver sendiri, jangan lupa di free ya -> free(pointer) */

Matrix *SubtractMatrix(Matrix M1, Matrix M2) {
    if((GetCols(M1) != GetCols(M2)) || GetRows(M1) != GetRows(M2)) return NULL;
    Matrix *result = (Matrix *)malloc(sizeof(Matrix));

    CreateMatrix(GetRows(M1), GetCols(M1), result);

    int i, j;
    for (i = 0; i < GetRows(M1); i++) {
        for (j = 0; j < GetCols(M1); j++) {
            *GetElement(result, i, j) = *GetElement(&M1, i, j) - *GetElement(&M2, i, j);
        }
    }
    return result;
}
/* Menghasilkan hasil pengurangan matrix M1 dan M2 (M1 - M2) */
/* Mengembalikan NULL jika ukuran matrix M1 dan M2 berbeda */
/* Hint: Gunakan Matrix* pointer = (Matrix *)malloc(sizeof(Matrix)) untuk menghasilkan pointer ke Matrix baru */
/* Jika anda membuat driver sendiri, jangan lupa di free ya -> free(pointer) */

Matrix MultiplyScalar(Matrix M, float scalar) {
    int i, j;
    Matrix result;
    CreateMatrix(GetRows(M), GetCols(M), &result);

    for (i = 0; i < GetRows(M); i++) {
        for (j = 0; j < GetCols(M); j++) {
            *GetElement(&result, i, j) = *GetElement(&M, i, j) * scalar;
        }
    }
    return result;
}
/* Menghasilkan hasil perkalian matrix M dengan skalar scalar */
/* Prekondisi: M terdefinisi dan skalar terdefinisi */
/* Hint: Buat matrix baru untuk menyimpan hasil */

Matrix GetTranspose(Matrix M) {
    int i, j;
    Matrix result;
    CreateMatrix(GetCols(M), GetRows(M), &result);

    for (i = 0; i < GetCols(M); i++) {
        for (j = 0; j < GetRows(M); j++) {
            *GetElement(&result, i, j) = *GetElement(&M, j, i);
        }
    }
    return result;
}
/* Menghasilkan matrix transpose dari M */
/* Hint: Buat matrix baru untuk menyimpan hasil */