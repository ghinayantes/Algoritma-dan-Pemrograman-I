#include <stdio.h>

int main() {
    int N, K, P, i, j;
    scanf("%d %d %d", &N, &K, &P);

    int M1[N][K], M2[K][P];

    for(i = 0; i < N; i++) {
        for(j = 0; j < K; j++) {
            int input;
            do {
                scanf("%d", &input);
            } while(input < -10 || input > 10);
            M1[i][j] = input;
        }
    }

    for(i = 0; i < K; i++) {
        for(j = 0; j < P; j++) {
            int input;
            do {
                scanf("%d", &input);
            } while(input < -10 || input > 10);
            M2[i][j] = input;
        }
    }

    int H[N][P], k;

    // Inisialisasi matriks hasil dengan 0
    for(i = 0; i < N; i++) {
        for(j = 0; j < P; j++) {
            H[i][j] = 0; // Pastikan mulai dari nol
            for(k = 0; k < K; k++) {
                // Rumus utama: Baris i dari M1 * Kolom j dari M2
                H[i][j] += M1[i][k] * M2[k][j];
            }
        }
    }

    for(i = 0; i < N; i++) {
        for(j = 0; j < P; j++) {
            printf("%d", H[i][j]);
            if(j != P-1) printf(" ");
        }
        printf("\n");
    }

    return 0;
}