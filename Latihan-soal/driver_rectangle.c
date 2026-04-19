#include <stdio.h>
#include "Rectangle.h"

/* ============================================================
   DRIVER TEST — Rectangle ADT
   Compile: gcc driver_rectangle.c Rectangle.c -o driver_rectangle
   Run    : ./driver_rectangle
   ============================================================ */

/* Helper untuk cetak hasil test */
void printTestResult(const char *testName, boolean passed) {
    printf("[%s] %s\n", passed ? "PASS" : "FAIL", testName);
}

int main() {
    printf("========================================\n");
    printf("   DRIVER TEST - RECTANGLE ADT\n");
    printf("========================================\n\n");

    /* --------------------------------------------------
       1. MakeRectangle
       -------------------------------------------------- */
    printf("--- 1. MakeRectangle ---\n");
    RECTANGLE R1 = MakeRectangle(3.0f, 4.0f);
    printTestResult("MakeRectangle width=3", Width(R1) == 3.0f);
    printTestResult("MakeRectangle height=4", Height(R1) == 4.0f);
    printf("\n");

    /* --------------------------------------------------
       2. printRectangle
       -------------------------------------------------- */
    printf("--- 2. printRectangle ---\n");
    printf("Expected : R(3.00x4.00)\n");
    printf("Got      : ");
    printRectangle(R1);
    printf("\n\n");

    /* --------------------------------------------------
       3. isSquare & isNotSquare
       -------------------------------------------------- */
    printf("--- 3. isSquare & isNotSquare ---\n");
    RECTANGLE Rsq = MakeRectangle(5.0f, 5.0f);
    RECTANGLE Rnonsq = MakeRectangle(3.0f, 4.0f);

    printTestResult("isSquare(5x5) = TRUE",     isSquare(Rsq)    == TRUE);
    printTestResult("isSquare(3x4) = FALSE",    isSquare(Rnonsq) == FALSE);
    printTestResult("isNotSquare(3x4) = TRUE",  isNotSquare(Rnonsq) == TRUE);
    printTestResult("isNotSquare(5x5) = FALSE", isNotSquare(Rsq)    == FALSE);
    printf("\n");

    /* --------------------------------------------------
       4. area
       -------------------------------------------------- */
    printf("--- 4. area ---\n");
    float a = area(R1);  /* 3 * 4 = 12 */
    printf("area(3x4) -> Expected: 12.00, Got: %.2f\n", a);
    printTestResult("area(3x4) = 12", a == 12.0f);

    float a2 = area(Rsq);  /* 5 * 5 = 25 */
    printf("area(5x5) -> Expected: 25.00, Got: %.2f\n", a2);
    printTestResult("area(5x5) = 25", a2 == 25.0f);
    printf("\n");

    /* --------------------------------------------------
       5. perimeter
       -------------------------------------------------- */
    printf("--- 5. perimeter ---\n");
    float p = perimeter(R1);  /* 2*(3+4) = 14 */
    printf("perimeter(3x4) -> Expected: 14.00, Got: %.2f\n", p);
    printTestResult("perimeter(3x4) = 14", p == 14.0f);

    float p2 = perimeter(Rsq);  /* 2*(5+5) = 20 */
    printf("perimeter(5x5) -> Expected: 20.00, Got: %.2f\n", p2);
    printTestResult("perimeter(5x5) = 20", p2 == 20.0f);
    printf("\n");

    /* --------------------------------------------------
       6. swap
       -------------------------------------------------- */
    printf("--- 6. swap ---\n");
    RECTANGLE Rswap = MakeRectangle(3.0f, 7.0f);
    printf("Before swap: "); printRectangle(Rswap); printf("\n");
    swap(&Rswap);
    printf("After swap : "); printRectangle(Rswap); printf("\n");
    printTestResult("swap width  -> 7", Width(Rswap)  == 7.0f);
    printTestResult("swap height -> 3", Height(Rswap) == 3.0f);
    printf("\n");

    /* --------------------------------------------------
       7. add (modifikasi in-place)
       -------------------------------------------------- */
    printf("--- 7. add ---\n");
    RECTANGLE Radd = MakeRectangle(2.0f, 3.0f);
    printf("Before add: "); printRectangle(Radd); printf("\n");
    add(&Radd, 1.5f, 2.5f);
    printf("After add(+1.5, +2.5): "); printRectangle(Radd); printf("\n");
    printTestResult("add width  = 3.5", Width(Radd)  == 3.5f);
    printTestResult("add height = 5.5", Height(Radd) == 5.5f);
    printf("\n");

    /* --------------------------------------------------
       8. plusRectangle (tidak mengubah R asli)
       -------------------------------------------------- */
    printf("--- 8. plusRectangle ---\n");
    RECTANGLE Rplus_orig = MakeRectangle(4.0f, 6.0f);
    RECTANGLE Rplus_new  = plusRectangle(Rplus_orig, 2.0f, 3.0f);

    printf("Original  : "); printRectangle(Rplus_orig); printf("\n");
    printf("plusResult: "); printRectangle(Rplus_new);  printf("\n");

    /* R asli tidak boleh berubah */
    printTestResult("plusRectangle: original width  unchanged (4)", Width(Rplus_orig)  == 4.0f);
    printTestResult("plusRectangle: original height unchanged (6)", Height(Rplus_orig) == 6.0f);
    /* Nilai baru harus +delta */
    printTestResult("plusRectangle: new width  = 6", Width(Rplus_new)  == 6.0f);
    printTestResult("plusRectangle: new height = 9", Height(Rplus_new) == 9.0f);
    printf("\n");

    /* --------------------------------------------------
       9. readRectangle (interaktif)
       -------------------------------------------------- */
    printf("--- 9. readRectangle (interaktif) ---\n");
    RECTANGLE Rread;
    printf("Masukkan width dan height (pisahkan spasi, contoh: 5 8): ");
    readRectangle(&Rread);
    printf("Rectangle terbaca: ");
    printRectangle(Rread);
    printf("\n");
    printf("area     = %.2f\n", area(Rread));
    printf("perimeter= %.2f\n", perimeter(Rread));
    printf("isSquare = %s\n", isSquare(Rread) ? "TRUE" : "FALSE");
    printf("\n");

    printf("========================================\n");
    printf("   DRIVER TEST SELESAI\n");
    printf("========================================\n");

    return 0;
}