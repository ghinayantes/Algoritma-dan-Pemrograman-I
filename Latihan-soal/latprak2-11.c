#include <stdio.h>
#include <string.h>

int nilaiRoman(char c) {
    if(c == 'I') return 1;
    else if(c == 'V') return 5;
    else if(c == 'X') return 10;
    else if(c == 'L') return 50;
    else if(c == 'C') return 100;
    else if(c == 'D') return 500;
    else if(c == 'M') return 1000;
    else return 0;
}

int fromRoman(char s[]) {
    int i, total = 0;
    for(i = 0; s[i] != '\0'; i++) {
        if(nilaiRoman(s[i]) < nilaiRoman(s[i+1]))
            total -= nilaiRoman(s[i]);
        else
            total += nilaiRoman(s[i]);
    }
    return total;
}

void toRoman(int n) {
    int nilai[]    = {1000,900,500,400,100,90,50,40,10,9,5,4,1};
    char *simbol[] /*array of string*/ = {"M","CM","D","CD","C","XC","L","XL","X","IX","V","IV","I"};
    int i;
    for(i = 0; i < 13; i++) {
        while(n >= nilai[i]) {
            printf("%s", simbol[i]);
            n -= nilai[i];
        }
    }
    printf("\n");
}

int main() {
    char perintah[10];
    char roman[50];
    int n;

    while(1) {
        scanf("%s", perintah);

        if(strcmp(perintah, "SELESAI") == 0) {
            break;
        }
        else if(strcmp(perintah, "DES") == 0) {
            scanf("%d", &n);
            toRoman(n);
        }
        else if(strcmp(perintah, "ROM") == 0) {
            scanf("%s", roman);
            printf("%d\n", fromRoman(roman));
        }
    }

    return 0;
}