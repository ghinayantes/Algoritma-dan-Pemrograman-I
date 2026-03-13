#include <stdio.h>

void cek(char pw[]) {
    int kecil = 0, besar = 0, panjang = 0, angka = 0, i;
    for(i = 0; pw[i] != '\0'; i++) {
        if(pw[i] >= 'a' && pw[i] <= 'z') kecil++;
        else if (pw[i] >= 'A' && pw[i] <= 'Z') besar++;
        else if (pw[i] >= '1' && pw[i] <= '9') angka++;
        panjang++;
    }
    if(kecil > 0 && besar > 0 && panjang >= 8 && angka > 0) printf("KUAT\n");
    else printf("LEMAH\n");
}

int main() {
    int panjang, count = 0;
    char temp;
    scanf("%d", &panjang);
    char pw[panjang + 1];
    pw[panjang] = '\0';

    while(count < panjang) {
        scanf(" %c", &pw[count]);
        count++;
    }

    cek(pw);

    return 0;
}