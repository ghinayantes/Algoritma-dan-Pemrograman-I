#include <stdio.h>

int max(int p, int q) {
    if (p > q) {
        return p;
    }
    else {
        return q;
    }
}
int max_of_four(int a, int b, int c, int d) {
    return max(max(a, b), max(c, d));
}
int main() {
    int a, b, c, d;
    scanf("%d %d %d %d", &a, &b, &c, &d);
    int ans = max_of_four(a, b, c, d);
    printf("%d", ans);
    
    return 0;
}


// versi ternary operator
/* int max_of_four(int a, int b, int c, int d) {
    int m1 = (a > b) ? a : b;
    int m2 = (c > d) ? c : d;
    return (m1 > m2) ? m1 : m2;
}*/