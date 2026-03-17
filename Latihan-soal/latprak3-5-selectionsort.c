#include <stdio.h>

void selectionSort(int A[], int n) {
    int cmpCount = 0, swapCount = 0;
    for(int i = 0; i < n-1; i++) {
        int minIdx = i;
        for(int j = i+1; j < n; j++) {
            if (A[j] < A[minIdx]) minIdx = j; 
            cmpCount++;
        }
        if (minIdx != i) {
            int temp = A[i]; A[i] = A[minIdx]; A[minIdx] = temp;
            swapCount++;
        }
    }
    for(int k = 0; k < n; k++) {
        printf("%d", A[k]);
        if (k < n-1) printf(" ");
        else printf("\n");
    }
    printf("Total perbandingan: %d\n", cmpCount);
    printf("Total swap: %d\n", swapCount);
}

int main() {
    int n, A[100], i = 0;

    do {
        printf("Masukkan N [1..100]: ");
        scanf("%d", &n);
    } while (n < 1 || n > 100);

    while (i < n) {
        do {
            printf("Masukkan input ke-%d: ", i+1);
            scanf("%d", &A[i]);
        } while (A[i] < -1000 || A[i] > 1000);
        i++;
    }

    selectionSort(A, n);

    return 0;
}