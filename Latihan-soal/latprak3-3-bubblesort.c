#include <stdio.h>

void bubbleSort(int A[], int n) {
    int counter = 0;
    for(int i = 0; i < n-1; i++) {
        int swapped = 0;  // early termination
        for(int j = 0; j < n-i-1; j++) {
            if(A[j] > A[j+1]) {
                int temp = A[j]; A[j] = A[j+1]; A[j+1] = temp; 
                swapped = 1;
                counter++;
            }
        }
        if(!swapped) break;
    }
    for(int k = 0; k < n; k++) {
        printf("%d", A[k]);
        if(k < n-1) printf(" ");
    }
    printf("\nTotal swap: %d", counter);
}

int main() {
    int n, A[100], i = 0;
    do {
        printf("Masukkan N [1..100]: ");
        scanf("%d", &n);   // skema validasi
    } while(n < 1 || n > 100);

    while(i < n) {
        do {
            printf("Masukkan input ke-%d: ", i+1);
            scanf("%d", &A[i]);
        } while(A[i] < -1000 || A[i] > 1000);
        i++;
    }

    bubbleSort(A, n); // perhatikan syntax
    
    return 0;
}