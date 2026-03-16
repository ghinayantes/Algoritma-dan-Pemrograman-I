#include <stdio.h>

void bubbleSort(int A[], int n) {
    for(int i = 0; i < n-1; i++) {
        int swapped = 0;
        for(int j = 0; j < n-i-1; j++) {
            if(A[j] > A[j+1]) {
                int temp = A[j]; A[j] = A[j+1]; A[j+1] = temp;
                swapped = 1;
            }
        }
        if(!swapped) break;
        printf("Pass %d: ", i+1);
        for(int k = 0; k < n; k++) {
            printf("%d", A[k]);
            if(k < n-1) printf(" ");
        }
        printf("\n");
    }
}

int main() {
    int n, A[10], i = 0;
    do {
        printf("Masukkan N [2..10]: ");
        scanf("%d", &n);
    } while(n < 2 || n > 10);

    while(i < n) {
        printf("Masukkan input ke-%d: ", i+1);
        scanf("%d", &A[i]);
        i++;
    }

    bubbleSort(A, n);

    return 0;
}