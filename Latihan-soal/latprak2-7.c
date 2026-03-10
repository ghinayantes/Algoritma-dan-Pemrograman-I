#include <stdio.h>

int isPrima(int n) {
    if (n < 2) return 0;
    int i;
    for (i = 2; i < n; i++) {
        if (n % i == 0) return 0;  
    }
    return 1;  
}

int primaTerbesar(int batas) {
    int i = 2;
    int prima = 0;
    while(i <= batas) {
        if(isPrima(i)) prima = i;
        i++;
    }
    return prima;
}


void cetakPrima(int a, int b) {
    int i = a;
    
    while(i <= b) {             
    if(isPrima(i)) printf("%d ", i);
    i++;
}
}

int main() {
    int a, b;
    printf("Masukkan a dan b: \n");
    printf("a = ");
    scanf("%d", &a);
    printf("b = ");
    scanf("%d", &b);

    printf("Bilangan prima antara %d dan %d: ", a, b);
    cetakPrima(a, b);
    printf("\nPrima terbesar: %d", primaTerbesar(b));

    return 0; 
}