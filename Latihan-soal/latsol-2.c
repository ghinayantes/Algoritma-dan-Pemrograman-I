#include <stdio.h>

// 1. Mendefinisikan Struct Suhu
typedef struct {
    float celcius;
} Suhu;

int main() {
    Suhu s; // Deklarasi variabel biasa (bukan pointer)
    float reamur, fahrenheit;

    // 2. Input data menggunakan operator titik (.)
    printf("Masukkan suhu dalam Celcius: ");
    scanf("%f\n", &s.celcius); // Tetap pakai & karena s.celcius adalah float

    // 3. Perhitungan menggunakan data dari dalam struct
    reamur = s.celcius * 0.8;
    fahrenheit = (s.celcius * 1.8) + 32;

    // 4. Menampilkan hasil
    printf("Hasil Konversi Suhu:\n");
    printf("Celcius    : %.2f C\n", s.celcius);
    printf("Reamur     : %.2f R\n", reamur);
    printf("Fahrenheit : %.2f F\n", fahrenheit);

    return 0;
}