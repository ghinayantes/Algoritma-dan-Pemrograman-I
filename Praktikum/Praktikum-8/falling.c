#include <stdio.h>

int main() {
    int r,c;
    do {
        scanf("%d %d", &r, &c);
    } while(r < 1 || r > 100 || c < 1 || c > 100);

    int i,j,M[r][c];

    for(i = 0; i < r; i++) {
        for(j = 0; j < c; j++) {
            scanf("%d", &M[i][j]);
        } 
    }
    
    int col = r-1, it = 0;
    while(it < c) {
        int pos = 0;
        if(col == r-1 && it != c) {
            while(col >= 0) {
                pos = 0;
                if(M[col][it] == 0) {
                    for(j = col-1; j >= 0; j--) {
                        if(M[j][it] != 0) {
                            pos = j;
                            break;
                        }
                    }
                    M[col][it] = M[pos][it];
                    M[pos][it] = 0;
                    col--;
                }
                else col--;
            }
        }
        else {
            it++;
            col = r-1;
        }
        
    }

    for(i = 0; i < r; i++) {
        for(j = 0; j < c; j++) {
            printf("%d", M[i][j]);
            if(j != c-1) printf(" ");
        }
        printf("\n");
    }
    
    return 0;
}