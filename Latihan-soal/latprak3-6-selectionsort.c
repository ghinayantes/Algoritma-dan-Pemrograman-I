#include <stdio.h>

void selectionSort(int A[], int P[], int n) {
    for(int i = 0; i < n-1; i++) {
        int maxIdx = i;
        for(int j = i+1; j < n; j++) {
            if (A[j] > A[maxIdx]) maxIdx = j;
        } 
        if (maxIdx != i) {
            int tempA = A[i]; A[i] = A[maxIdx]; A[maxIdx] = tempA;
            int tempP = P[i]; P[i] = P[maxIdx]; P[maxIdx] = tempP;
        }
    }
    for(int k = 0; k < n; k++) {
        printf("%d %d\n", A[k], P[k]); 
    }
}


int main() {
    int n, A[50], P[50], i = 0;

    do {
        printf("Masukkan N [1..100]: ");
        scanf("%d", &n);
    } while (n < 1 || n > 50);

    while (i < n) {
        do {
            printf("Masukkan input ke-%d: ", i+1);
            scanf("%d", &A[i]);
        } while (A[i] < 1 || A[i] > 1000);

        P[i] = i+1;

        i++;
    }

    selectionSort(A, P, n);

    return 0;
}