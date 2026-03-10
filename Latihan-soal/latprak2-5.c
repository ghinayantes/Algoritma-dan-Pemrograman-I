#include <stdio.h>

int isKabisat(int yy) {
    if(((yy % 4 == 0) && (yy % 100 != 0)) || (yy % 400 == 0)) return 1;
    else return 0;
}

int dayMax(int mm, int yy) {
    if (mm == 1 || mm == 3 || mm == 5 || mm == 7 || mm == 8 || mm == 10 || mm == 12) return 31;
    else if (mm == 4 || mm == 6 || mm == 9 || mm == 11) return 30;
    else if (isKabisat(yy)) return 29;  // cek kabisat hanya untuk Feb
    else return 28;
}

int isTanggalValid(int dd, int mm, int yy) {
    if ((dd > 0 && dd <= dayMax(mm, yy)) && (mm > 0 && mm <= 12)) return 1;
    else return 0;
}

void bacaTanggal(int *dd, int *mm, int *yy) {
    do {
        printf("Masukkan tanggal sekarang (dd mm yy): ");
        scanf("%d %d %d", dd, mm, yy);
    } while(!isTanggalValid(*dd, *mm, *yy));
}

void nextDay(int *dd, int *mm, int *yy) {
    if (*dd < dayMax(*mm, *yy)) {
        *dd += 1;
    } else {
        *dd = 1;
        if (*mm < 12) {
            *mm += 1;
        } else {
            *mm = 1;
            *yy += 1;
        }
    }
}

int main() {
    int dd, mm, yy;

    bacaTanggal(&dd, &mm, &yy);
    nextDay(&dd, &mm, &yy);

    printf("Keesokan harinya: %d %d %d\n", dd, mm, yy);

    return 0;
}

    

