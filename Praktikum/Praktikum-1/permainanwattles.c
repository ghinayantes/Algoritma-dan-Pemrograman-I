#include <stdio.h>

int main() {
    int deep, meb;
    int m = 0, d = 0;

    scanf("%d %d",&deep, &meb);
    int copd = deep;
    int copmeb = meb;

    while(deep >= 0 && meb >= 0) {

        m += copmeb%10;
        while(copmeb >= 10) {
            copmeb/=10;
    }
        d += copd%10;
        while(copd >= 10) {
            copd/=10;
    }
        deep = deep - m;
        meb = meb - d;
    }

    if (meb > deep) {
            printf("Mebel\n");
        }
        else if (deep > meb) {
            printf("Deeper\n");
        }
        else {
            printf("Wattles\n");
        }

    return 0;
}