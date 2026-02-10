#include <stdio.h>

int m, h, k, total;
int harga_m = 10;
int harga_h = 15;
int harga_k = 20;

void harga() {
    total = ((m * harga_m) + (h * harga_h) + (k * harga_k)) * 100;
}
int main() {
    printf("Masukkan jumlah kelereng merah: ");
    scanf("%d", &m);
    
    printf("Masukkan jumlah kelereng hijau: ");
    scanf("%d", &h);
    
    printf("Masukkan jumlah kelereng kuning: ");
    scanf("%d", &k);
    
    harga();
    
    printf("Total yang harus dibayar adalah %d", total);
   
    return 0;
}