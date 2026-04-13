#include <stdio.h>

int min(int a, int b) {
    if(a < b) return a;
    return b;
}

int main() {
    int n, arr[100];

    scanf("%d", &n);

    int i;

    for(i = 0; i<n; i++) {
        scanf("%d", &arr[i]);
    }

    int sum = 0;

    int j;
    for(i = 0; i<n; i++) {
        for(j = i+1; j<n; j++) {
            sum += min(arr[i], arr[j]);
        }
    }

    printf("%d\n", sum);

    return 0;
}