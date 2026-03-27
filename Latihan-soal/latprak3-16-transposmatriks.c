#include <stdio.h>

void transpose(int n,int m, int A[n][m], int B[m][n]){
    int i,j;
    for (i = 0 ; i < n ; i++) {
        for (j = 0 ; j < m ; j++){
            B[j][i] = A[i][j];
        }
    }
}

int main () {
    int n,m;
    printf("Masukkan baris dan kolom : ");
    scanf("%d %d", &n, &m);

    int A[n][m];
    int B[m][n];
    int i,j;
    //input matriks 
    for (i = 0 ; i < n ; i++){
        for (j = 0 ; j < m ; j++){
            printf("Masukkan matriks[%d][%d] : ",i,j);
            scanf("%d", &A[i][j]);
        }
    }
    //proses transpose
    transpose(n,m,A,B);

    //menampilkan matriks sebelum dan sesudah transpose
    for (i = 0 ; i < n ; i++){
        for(j = 0 ; j < m ; j++){
            printf("%4d", A[i][j]);
        }
        printf("  ");

        if (i < m){
        for (j = 0; j < n ; j++) {
            printf("%4d", B[i][j]);
            }   
        }
        printf("\n");
    }
    return 0;
}