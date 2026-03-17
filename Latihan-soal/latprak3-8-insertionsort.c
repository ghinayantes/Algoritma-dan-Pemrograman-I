#include <stdio.h>

void insertionSort(int A[], int n) {
    int shiftCount = 0, noShift = 0;
    for(int i = 1; i < n; i++) {
        int key = A[i];
        int jAwal = i-1, j = jAwal;
        while(j >= 0 && A[j] > key) {
            A[j+1] = A[j]; shiftCount++;
            j--;
        }
        A[j+1] = key;
        if (j == jAwal) noShift++;
    }

    for(int k = 0; k < n; k++) {
        printf("%d", A[k]);
        if (k < n-1) printf(" ");
        else printf("\n");
    }
    printf("Total pergeseran: %d\n", shiftCount);
    printf("Langsung posisi benar: %d\n", noShift);
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

    insertionSort(A, n);

    return 0;
}