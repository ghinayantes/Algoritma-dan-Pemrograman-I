/* Deskripsi: Program membaca sekumpulan bilangan bulat dari stdin sampai pengguna memasukkan angka -999 
(angka ini tidak termasuk yang diproses). Tampilkan jumlah bilangan, nilai rata-rata, nilai maksimum, dan nilai minimum.*/

#include <stdio.h>

int main() {
    int x;             // Variabel penampung input saat ini
    int jumlah = 0;    // Count
    int total = 0;     // Sum
    int max = -999999; // Inisialisasi dengan nilai sangat kecil
    int min = 999999;  // Inisialisasi dengan nilai sangat besar

    // Input pertama (First-Element)
    printf("Masukkan bilangan bulat (tulis -999 untuk berhenti): ");
    scanf("%d", &x);

    // Skema WHILE dengan Mark (-999)
    while (x != -999) {
        jumlah++;
        total += x;
        
        if (x > max) max = x;
        if (x < min) min = x;

        // Input elemen berikutnya (Next-Element)
        printf("Masukkan bilangan bulat (tulis -999 untuk berhenti): ");
        scanf("%d", &x);
    }

    if (jumlah > 0) {
        printf("Jumlah: %d\n", jumlah);
        printf("Rata-rata: %.2f\n", (float)total / jumlah);
        printf("Max: %d\n", max);
        printf("Min: %d\n", min);
    } else {
        printf("Data kosong\n");
    }

    return 0;
}