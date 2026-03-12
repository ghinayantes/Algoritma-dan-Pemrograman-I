#include <stdio.h>

int jumlahPembagi(int n) {
    int i;
    int pembagi = 0;
    for(i = 1; i < n; i++) {
        if(n % i == 0 && i != n) pembagi += i;
    }
    return pembagi;
}

int isAbundant(int n) {
    if (jumlahPembagi(n) > n) return 1;
    else return 0;
}

int isPerfect(int n) {
    if (jumlahPembagi(n) == n) return 1;
    else return 0;
}

void hitungRentang(int a, int b, int *abundant, int *perfect) {
    int i;
    for(i = a; i <= b; i++) {
        if(isAbundant(i)) (*abundant)++;
        else if(isPerfect(i)) (*perfect)++;
    }
}

int main() {
    int a, b;
    int abundant = 0, perfect = 0;
    
    printf("Masukkan rentang a--b: ");
    scanf("%d %d", &a, &b);

    hitungRentang(a, b, &abundant, &perfect);

    printf("Banyak bilangan abundant: %d\n", abundant);
    printf("Banyak bilangan perfect: %d\n", perfect);

    return 0;
}