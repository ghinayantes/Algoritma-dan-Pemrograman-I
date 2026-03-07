#include <stdio.h>

int main() {
   int awal_h, awal_m, awal_s, akhir_h, akhir_m, akhir_s, hasil_h, hasil_m, hasil_s;
   scanf("%d%d%d", &awal_h, &awal_m, &awal_s);
   scanf("%d%d%d", &akhir_h, &akhir_m, &akhir_s);
   hasil_h = akhir_h - awal_h;
   hasil_m = akhir_m - awal_m;
   hasil_s = akhir_s - awal_s;
   printf("%d %d %d\n", hasil_h, hasil_m, hasil_s);

return 0;
}