#include <stdio.h>
/*selection sort adalah algoritma sorting yang mencari elemen terkecil
lalu menaruhnya di depan, ulangi*/ 

void selectionSort(int A[], int n) {
    int pass = 0;
    for(int i = 0; i < n-1; i++) {
        int minIdx = i;
        for(int j = i+1; j < n; j++) {
            if(A[j] < A[minIdx]) minIdx = j;
        }
        pass++;
        if (minIdx != i) {
            int temp = A[i]; A[i] = A[minIdx]; A[minIdx] = temp;
        }
        printf("Pass %d: ", pass);
        for(int k = 0; k < n; k++) {
            printf("%d", A[k]);
            if(k < n-1) printf(" ");
            else printf("\n");
        }
    }
    printf("Hasil akhir: ");
    for(int k = 0; k < n; k++) {
        printf("%d", A[k]);
        if (k < n-1) printf(" ");
        else printf("\n");
    }
}

int main() {
    int n, A[100], i = 0;

    do {
        printf("Masukkan N [2..10]: ");
        scanf("%d", &n);
    } while (n < 2 || n > 10);

    while(i < n) {
        do {
            printf("Masukkan input ke-%d: ", i+1);
            scanf("%d", &A[i]); 
        } while (A[i] < 1 || A[i] > 100);
        i++;
    }

    selectionSort(A, n);

    return 0;
}
