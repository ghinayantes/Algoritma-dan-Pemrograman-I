#include <stdio.h>

int main() {
    int x, i, j;
    int t = 1;
    int l = 1;
    scanf("%d", &x);

    for(i = 1; i <= x; i++) {
        for(j = t; j < i + l; j++) {
            printf("%d ", j);  
            t+=1;
        }
        l = t;
        printf("\n");
    }
}