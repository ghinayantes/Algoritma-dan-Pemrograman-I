#include <stdio.h>
#include <stdlib.h>

int digit(int n) {
    if(n == 0) return 1;
    int c = 0;
    while(n != 0) {
        n /= 10;
        c++;
    }
    return c;
}

int banding(const void *a, const void *b) {
    int A = *(int*)a;
    int B = *(int*)b;

    int digitA = digit(A);
    int digitB = digit(B);

    if(digitA != digitB) {
        return digitB - digitA;
    }
    return A-B;
}

int main() {
    int arr[1000], i, n;
    scanf(" %d", &n);

    for(i = 0;i<n;i++) {
        scanf("%d", &arr[i]);
    }
    
    qsort(arr, n, sizeof(int), banding);

    for(i = 0;i<n;i++) {
        printf("%d%s", arr[i], (i==n-1) ? "" : " ");
    }
    printf("\n");

    return 0;
}