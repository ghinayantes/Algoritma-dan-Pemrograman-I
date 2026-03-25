#include <stdio.h>
#include <string.h>

void insertionSort(char A[][21], int n) {
    for(int i = 1; i < n; i++) { /*char A[][21] = array of strings. Kolom wajib ditulis 21 agar compiler tahu 
        ukuran tiap string. Tanpa angka ini compiler tidak bisa hitung offset memori.*/
        char key[21];
        strcpy(key, A[i]);
        int j = i-1;
        while(j >= 0 && strcmp(A[j], key) > 0) { 
            strcpy(A[j+1], A[j]);
            j--;
        }
        strcpy(A[j+1], key); // di sini j tdi dikurangi, maka untuk menyalin key ke kiri j harus +1
    }
    for(int k = 0; k < n; k++) {
        printf("%s\n", A[k]); // ingat! karena array of string maka pake %s
    }
}

int main() {
    int n, i = 0;
    char A[20][21];

    do {
        printf("Masukkan N [2..20]: ");
        scanf("%d", &n);
    } while (n < 2 || n > 20);

    while (i < n) {
        printf("Masukkan input ke-%d: ", i+1);
        scanf(" %[^\n]", A[i]); // spasi utk skip whitespace sisa scanf sebelumnya

        i++;
    }

    insertionSort(A, n);

    return 0;
}

/* CARA KERJA strcmp 
contoh: 
strcmp("banana", "apple")  // return > 0 karena 'b' > 'a'
strcmp("apple", "banana")  // return < 0 karena 'a' < 'b'
strcmp("apple", "apple")   // return 0 karena sama
*/