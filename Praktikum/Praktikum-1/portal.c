#include <stdio.h>

int main() {
    int x;
    int langkah = 0;
    
    scanf("%d", &x);
    
    while(x != 1) {
        if(x%2 == 0) {
            x = x/2;
            langkah++;
        }
        else {
            x = 3 * x + 1;
            langkah++;
        }
    }
    if(x == 1) {
        printf("%d\n", langkah);
    }
    return 0;
}