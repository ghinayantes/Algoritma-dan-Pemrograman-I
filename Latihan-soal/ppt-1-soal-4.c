#include <stdio.h>

typedef struct {
    float x, y;
} point;

int main() {
    point p; // Variabel biasa

    printf("Masukkan koordinat sumbu x: ");
    scanf("%f", &p.x); // Pakai & dan titik (.)

    printf("Masukkan koordinat sumbu y: ");
    scanf("%f", &p.y);

    printf("Koordinat: (%.2f, %.2f)\n", p.x, p.y);

    return 0;
}