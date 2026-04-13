#include <stdio.h>

void balik(int arr[], int n) {
    int k, balik;
    for(k=0; k<n/2;k++) {
        balik = arr[k];
        arr[k] = arr[n-k-1];
        arr[n-k-1] = balik;
    }
}

int main() {
    int n, arr[100], i;

    scanf("%d", &n);

    for(i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    balik(arr, n);
    for(i = 0; i<n; i++) {
        if(i==n-1)  {
            printf("%d", arr[i]);
        }
        else {
            printf("%d ", arr[i]);
        }
    }
    printf("\n");
    return 0;
}