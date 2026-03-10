#include <stdio.h>

int fibonacci(int n) {
    if(n <= 2) return 1;
    return fibonacci(n-1) + fibonacci(n-2);
}

int isFibonacci(int n) {
    int i = 1;
    while(fibonacci(i) < n) i++;
    return fibonacci(i) == n;
}

void cetakDeret(int n) {
    int i;
    printf("Deret fibonacci sampai suku ke-%d: ", n);
    for(i = 1; i <= n; i++) {
        printf("%d ", fibonacci(i));
    }
}

int main() {
    int n;
    do {
        printf("Masukkan bilangan n: ");
        scanf("%d", &n);
    } while(n <= 0);

    cetakDeret(n);

    if(isFibonacci(fibonacci(n)))
        printf("\nSuku ke-%d (%d) adalah bilangan Fibonacci\n", n, fibonacci(n));

    return 0;
}