#include <stdio.h>

int isPrima(int n) {
    int i;
    if(n < 2) return 0;
    for(i = 2; i < n; i++) {
        if(n % i == 0) return 0;
    }
    return 1;
}

int digitprima(int n) {
    int d, temp = n;
    while(temp > 0) {
        d = temp % 10;
        if(!isPrima(d)) return 0;
        temp /= 10;
    }
    return 1;
}

int jumlah(int n) {
    int jumlah, temp = n;

    while(temp > 0) {
        jumlah += temp%10;
        temp /= 10;
    }

    if(!isPrima(jumlah)) return 0;
    return 1;
}

int main() {
    int n;
    scanf("%d", &n);

    if(isPrima(n) && digitprima(n) && jumlah(n)) printf("1\n");
    else printf("0\n");

    return 0;
}