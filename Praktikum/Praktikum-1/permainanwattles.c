#include <stdio.h>

int digitPertama(int n) {
    while(n >= 10) n /= 10;
    return n;
}

int digitTerakhir(int n) {
    return n % 10;
}

int main() {
    int deep, meb;
    scanf("%d %d", &deep, &meb);

    while(deep >= 0 && meb >= 0) {
        // cek kondisi Wattles: kedua bilangan sama
        if(deep == meb) {
            printf("Wattles\n");
            return 0;
        }

        // hitung pengurangan berdasarkan bilangan lawan turn sebelumnya
        int redDeep = digitPertama(meb) + digitTerakhir(meb);
        int redMeb  = digitPertama(deep) + digitTerakhir(deep);

        deep = deep - redDeep;
        meb  = meb  - redMeb;

        // cek kondisi Wattles: keduanya negatif di turn yang sama
        if(deep < 0 && meb < 0) {
            printf("Wattles\n");
            return 0;
        }
    }

    if(deep < 0) printf("Mebel\n");
    else printf("Deeper\n");

    return 0;
}