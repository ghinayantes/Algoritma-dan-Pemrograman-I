#include <stdio.h>

int main() {
    int n, x, arr1[100], i, ketemu = 0;

    scanf("%d %d", &n, &x);

    for(i = 0; i<n; i++) {
        scanf(" %d", &arr1[i]);
    }

    for(i = 0; i<n; i++) {
        if(arr1[i] == x) ketemu = 1;
    }

    if(ketemu) {
        printf("%d ", x);
        for(i = 0; i<n; i++) {
            printf("%d", arr1[i]);
            if(i<n-1) printf(" ");
            else printf("\n");
        }
    }
    else {
        for(i = 0; i<n; i++) {
            printf("%d", arr1[i]);
            if(i<n-1) printf(" ");
            else printf("\n");
        }
    }
    return 0;
}