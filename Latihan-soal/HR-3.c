#include <stdio.h>

int main()
{
	int x, y, sum_int, dif_int;
    float a, b, sum_float, dif_float;
    
    scanf("%d %d", &x, &y);
    scanf("%f %f", &a, &b);
    
    sum_int = x + y;
    dif_int = x - y;
    
    sum_float = a + b;
    dif_float = a - b;
    
    printf("%d %d\n", sum_int, dif_int);
    printf("%.1f %.1f\n", sum_float, dif_float);
    return 0;
}