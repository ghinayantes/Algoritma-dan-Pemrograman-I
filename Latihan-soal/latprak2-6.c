#include <stdio.h>

float celsiusToFahrenheit(float c) {
    return (c * 9/5) + 32;
}

float celsiusToKelvin(float c) {
    return c + 273.15;
}

void bacaSuhu(float *suhu) {
    do {
        printf("input suhu (dalam celcius): ");
        scanf("%f", suhu);
        if (*suhu < -273.15) printf("Suhu tidak valid! Tidak boleh di bawah -273.15 C\n");
    } while (*suhu < -273.15);
}

void cetakHasil(float c) {
    printf("Suhu dalam Celsius: %.2f\n", c);
    printf("Suhu dalam Fahrenheit: %.2f\n", celsiusToFahrenheit(c));
    printf("Suhu dalam Kelvin: %.2f\n", celsiusToKelvin(c));
}

int main() {
    float suhu;
    bacaSuhu(&suhu);
    cetakHasil(suhu);

    return 0;
}