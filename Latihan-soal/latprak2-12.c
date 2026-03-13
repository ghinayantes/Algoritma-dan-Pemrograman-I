#include <stdio.h>
#include <string.h>

int jumlahDigit(int n) {
    int count = 0;
    while(n > 0) {
        n /= 10;
        count++;
    }
    return count;
}

char geserHuruf(char c, int k) {
    // untuk huruf kecil
    if(c >= 'a' && c <= 'z') return 'a' + (c - 'a' + k) % 26;
    // untuk huruf besar
    else return 'A' + (c - 'A' + k) % 26;
}

void enkripsi(char pesan[]) {
    int i;
    for(i = 0; pesan[i] != '\0'; i++) {
        if((pesan[i] >= 'a' && pesan[i] <= 'z') || (pesan[i] >= 'A' && pesan[i] <= 'Z')) {
            pesan[i] = geserHuruf(pesan[i], jumlahDigit(i + 1));
        }
    }
}

void deskripsi(char pesan[]) {
    int i;
    for(i = 0; pesan[i] != '\0'; i++) {
        if((pesan[i] >= 'a' && pesan[i] <= 'z') || (pesan[i] >= 'A' && pesan[i] <= 'Z')) {
            pesan[i] = geserHuruf(pesan[i], 26 - jumlahDigit(i + 1));
        }
    }
}

int main() {
    char pesan[100], perintah[50];

    while(1) {
        scanf("%s", perintah);
        
        if(strcmp(perintah, "ENKRIPSI") == 0) {
            scanf(" %[^\n]", pesan);  // baca sampai akhir baris termasuk spasi
            enkripsi(pesan);
            printf("%s\n", pesan);
        }
        else if(strcmp(perintah, "DESKRIPSI") == 0) {
            scanf(" %[^\n]", pesan);  
            deskripsi(pesan);
            printf("%s\n", pesan);
        }
        else if(strcmp(perintah, "SELESAI") == 0) {
            break;
        }
    }
}
