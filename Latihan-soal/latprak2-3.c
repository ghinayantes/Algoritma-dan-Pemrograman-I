#include <stdio.h>

int isValid(int nilai) {
    if (0 <= nilai && nilai <= 100) return 1;
    else return 0;
} 

void bacaNilai(int *nilai) {
    do {
        printf("Masukkan nilai (0-100): ");
        scanf("%d", nilai);
    } while (!isValid(*nilai));
}

void cetakGrade(int nilai) {
    if(nilai >= 80) printf("A");
    else if(nilai >= 70) printf("B");
    else if(nilai >= 60) printf("C");
    else if(nilai >= 45) printf("D");
    else printf("E");
}

int main() {
    int nilai;

    bacaNilai(&nilai);
    
    printf("Nilai anda %d, grade: ", nilai);
    cetakGrade(nilai);

    return 0;
}
