#include <stdio.h>
/*insertion sort adalah algoritma sorting yang mengambil satu elemen lalu 
menyisipkan ke posisi yang benar di bagian yang sudah terurut , ulangi*/

void insertionSort(int A[], int n) {
    int pass = 0;
    for(int i = 1; i < n; i++) {
        int key = A[i];
        int j = i-1;
        while(j >= 0 && A[j] > key) {
            A[j+1] = A[j];
            j--;
        }
        A[j+1] = key;
        pass++;
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
    int n, A[50], i = 0;

    do {
        printf("Masukkan N [2..10]: ");
        scanf("%d", &n);
    } while (n < 2 || n > 10);

    while (i < n) {
        do {
            printf("Masukkan input ke-%d: ", i+1);
            scanf("%d", &A[i]);
        } while (A[i] < 1 || A[i] > 100);

        i++;
    }

    insertionSort(A, n);

    return 0;
}