#include <stdio.h>

int linearSearch(int arr[], int n, int target) {
    for(int i = 0; i < n; i++) {
        if(arr[i] == target) return i;
    }
    return -1;
}

int main() {
    int arr[100], n, target, i = 0;

    printf("Masukkan banyak integer: ");
    scanf("%d", &n);

    while (i < n) {
        printf("Masukkan integer ke-%d: ", i+1);
        scanf("%d", &arr[i]);
        i++;
    }

    printf("Bilangan yang ingin dicari: ");
    scanf("%d", &target);
    
    if(linearSearch(arr, n, target) != -1) printf ("Nilai %d ditemukan di indeks ke-%d", target, linearSearch(arr, n, target));
    else printf("Nilai tidak ditemukan");

    return 0;
}