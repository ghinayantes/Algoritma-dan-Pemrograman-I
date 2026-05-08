#include <stdio.h>

int main() {
    int i, j, n, m;
    do {
        scanf("%d %d", &n, &m);
    } while(n < 1 || n > 100 || m < 1 || m > 100);

    int M[n][m];

    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            scanf("%d", &M[i][j]);
        }
    }

    int MT[m][n];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            MT[j][i] = M[i][j];
        }
    }
    
    for(i = 0; i < m; i++) {
        for(j = 0; j < n; j++) {
            printf("%d", MT[i][j]);
            if(j != n-1) printf(" ");
        }
        printf("\n");
    }

    return 0;
}