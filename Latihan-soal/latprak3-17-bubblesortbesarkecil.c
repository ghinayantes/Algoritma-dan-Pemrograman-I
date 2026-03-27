#include <stdio.h>
//bubble sort
void showArr(int arr[], int n) {
    int i;
    for (i = 0 ; i < n ; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main () {
    int n,i;
    printf("Masukkan jumlah data : ");
    scanf("%d", &n);

    int arr[n];
    for (i = 0 ; i < n ; i++) {
        printf("Masukkan nilai ke-%d : ", i+1);
        scanf("%d", &arr[i]);
    }
    printf("Array awal   : ");
    showArr(arr, n);

    // untuk dari kecil ke besar
    for (i = 0; i < n ; i++){
        for (int j = 0 ; j < n - i - 1 ; j++) {
            if (arr[j] > arr[j+1]){
                int temp = arr[j]; // akan menukar posisi
                arr[j] = arr[j+1];
                arr[j+1] = temp ;
            }
        }
    }
    printf("Array terurut : ");
    showArr(arr,n);

    //untuk dari besar ke kecil
    for (i = 0 ; i < n ; i++) {
        for (int j = 0 ; j < n - i - 1 ; j++) {
            if (arr[j] < arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
    printf("Array terbalik : ");
    showArr(arr,n);

    return 0;
}