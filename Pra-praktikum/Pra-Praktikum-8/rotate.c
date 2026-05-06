#include <stdio.h>

int main() {
    int N, M;
    int i, j;

    do {
        scanf("%d %d", &N, &M);
    } while(N < 1 || M < 1 || N > 100 || M > 100);

    int Mr[N][M];
    
    for(i = 0; i < N; i++) {
        for(j = 0; j < M; j++) {
            scanf("%d", &Mr[i][j]);
        }
    }

    int H[M][N], cou = 0;
    int baris[N * M];

    for(i = 0; i < N; i++) {
        for(j = 0; j < M; j++) {
            baris[cou] = Mr[i][j];
            cou++;
        }
    }

    cou = 0;

    for(i = N-1; i >= 0; i--) {
        for(j = 0; j < M; j++) {
            H[j][i] = baris[cou];
            cou++;
        }
    }

    for(i = 0; i < M; i++) {
        for(j = 0; j < N; j++) {
            printf("%d", H[i][j]);
            if(j != N-1) printf(" ");
        }
        printf("\n");
    }

   /* cara gampang buat rotasinya
   for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            // Baris i menjadi kolom (N-1-i)
            H[j][N - 1 - i] = Mr[i][j];
        }
    } */

    return 0;
}