#include <stdio.h>

int fx(int x) {
    return x*x + 5*x + 7;
}

int gx(int x){
    return x*x*x*x + 2*x + 1;
} 

int main() {
    int x;
    scanf("%d", &x);
    printf("%d\n", fx(gx(x)));
}