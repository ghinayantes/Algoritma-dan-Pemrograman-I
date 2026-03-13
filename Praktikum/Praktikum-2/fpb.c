#include <stdio.h>

int fpbDua(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int fpbSemua(int kristal[], int n) {
    int hasil = kristal[0];
    for (int i = 1; i < n; i++) {
        hasil = fpbDua(hasil, kristal[i]);
    }
    return hasil;
}

int totalNilai(int kristal[], int n) {
    int total = 0;
    int x = fpbSemua(kristal, n);
    for (int i = 0; i < n; i++) {
        total += kristal[i] / x;
    }
    return total;
}

int main() {
    int n, kristal[100], i = 0;
    scanf("%d", &n);
    while (i < n) {
        scanf(" %d", &kristal[i]);
        i++;
    }
    printf("%d\n", totalNilai(kristal, n));
    return 0;
}