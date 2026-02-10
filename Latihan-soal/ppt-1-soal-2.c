#include <stdio.h>

float r, hasil;
float pi = 3.14159;

void keliling() {
    hasil = 2 * pi * r;
}

int main() {
    printf("Masukkan jari-jari: ");
    scanf("%f", &r);

    if (r <= 0) {
        printf("Input salah! jari-jari harus > 0");
        return 1;
    }
    else {

    keliling();

    printf("Keliling lingkaran adalah %f", hasil);

    }
    
    return 0;
}

