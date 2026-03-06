/* Deskripsi: Program mensimulasikan login. 
Pengguna diminta memasukkan PIN (angka). PIN yang benar adalah 13521. 
Jika salah, pengguna punya maksimal 3 kali percobaan.*/

#include <stdio.h>

int main() {
    const int PIN = 13525119;
    int x;
    int percobaan = 1;

    printf("Masukkan PIN (8 digit angka): ");
    scanf("%d", &x);

    while (x != PIN && percobaan < 3) {
        printf("PIN salah! Masukkan ulang: ");
        scanf("%d", &x);
        percobaan++;
    }

    if (x == PIN) {
        printf("Login berhasil!\n");
    }
    else {
        printf("Maksimal percobaan tercapai, login gagal.\n");
    }

    return 0;
}