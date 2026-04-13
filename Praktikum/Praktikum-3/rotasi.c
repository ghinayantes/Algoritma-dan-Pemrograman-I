#include <stdio.h>
#include <string.h>

void kanan(int arr[], int n) {
    int last = arr[n-1];
    int i;
    for(i = n-1; i>0; i--) {
        arr[i] = arr[i-1];
    }
    arr[0] = last;
}

void kiri(int arr[], int n) {
    int first = arr[0];
    int i;
    for(i=0; i<n-1; i++) {
        arr[i] = arr[i+1];
    }
    arr[n-1] = first;
}

int main() {
    int n, arr[100], i, q;

    scanf("%d", &n);

    for(i = 0; i<n; i++) {
        scanf("%d", &arr[i]);
    }

    scanf("%d", &q);

    for(i = 0; i<q; i++) {
        int x, j;
        char p;
        scanf(" %c %d", &p, &x);

        if(p == 'L') {
            for(j=0;j<x;j++) {
                kiri(arr, n);
            }
        }
        else if(p == 'R') {
            for(j=0;j<x;j++) {
                kanan(arr, n);
            }
        }
    }

    for(i = 0; i<n; i++) {
        printf("%d", arr[i]);
        if(i<n-1) printf(" ");
    }
    printf("\n");

    return 0;
}