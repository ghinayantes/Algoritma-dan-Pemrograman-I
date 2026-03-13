#include <stdio.h>
#include <string.h>

void cetakSpasi(int n) {
    int i;
    for(i = 0; i < n; i++) {
        printf(" ");
    }
}

void cetakBintang(int n) {
    int i;
    for(i = 0; i < n; i++) {
        printf("*");
    }
}

void solid(int n) {
    int i;
    for(i = 1; i <= n; i++) {
        cetakSpasi(n-i);
        cetakBintang(2*i-1);
        printf("\n");
    }
}

void hollow(int n) {
    int i;
    for(i = 1; i <= n; i++) {
        if(i == 1) {
            // baris pertama: 1 bintang di tengah
            cetakSpasi(n-1);
            printf("*");
        }
        else if(i == n) {
            // baris terakhir: semua bintang
            cetakBintang(2*n-1);
        }
        else {
            // baris tengah: bintang kiri, spasi, bintang kanan
            cetakSpasi(n-i);
            printf("*");
            cetakSpasi(2*i-3);
            printf("*");
        }
        printf("\n");
    }
}

void angka(int n) {
    int i, j;
    for(i = 1; i <= n; i++) {
        cetakSpasi(n-i);
        for(j = 1; j <= i; j++) {
            printf("%d", i);
            if(j < i) printf(" ");  // spasi antar angka kecuali terakhir
        }
        printf("\n");
    }
}

int main() {
    char perintah[10];
    int n;

    while(1) {
        scanf("%s", perintah);

        if(strcmp(perintah, "SELESAI") == 0) {
            break;
        }
        else if(strcmp(perintah, "SOLID") == 0) {
            scanf("%d", &n);
            solid(n);
        }
        else if(strcmp(perintah, "HOLLOW") == 0) {
            scanf("%d", &n);
            hollow(n);
        }
        else if(strcmp(perintah, "ANGKA") == 0) {
            scanf("%d", &n);
            angka(n);
        }
    }
    return 0;
}