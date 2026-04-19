#include <stdio.h>
#include "Polynomial.h"

/* ============================================================
   DRIVER TEST — Polynomial ADT
   Compile: gcc driver_polynomial.c Polynomial.c -o driver_polynomial -lm
   Run    : ./driver_polynomial
   ============================================================ */

void printTestResult(const char *testName, int passed) {
    printf("[%s] %s\n", passed ? "PASS" : "FAIL", testName);
}

/* Helper: buat polynomial manual tanpa ReadPolynomial */
Polynomial makeP(int degree, int coefs[]) {
    Polynomial P;
    int i;
    CreatePolynomial(&P, degree);
    for(i = 0; i <= degree; i++) P.coef[i] = coefs[i];
    return P;
}

int main() {
    printf("========================================\n");
    printf("   DRIVER TEST - POLYNOMIAL ADT\n");
    printf("========================================\n\n");

    /* --------------------------------------------------
       1. CreatePolynomial — semua coef harus 0
       -------------------------------------------------- */
    printf("--- 1. CreatePolynomial ---\n");
    Polynomial P0;
    CreatePolynomial(&P0, 3);
    printTestResult("degree = 3",    P0.degree   == 3);
    printTestResult("coef[0] = 0",   P0.coef[0]  == 0);
    printTestResult("coef[1] = 0",   P0.coef[1]  == 0);
    printTestResult("coef[2] = 0",   P0.coef[2]  == 0);
    printTestResult("coef[3] = 0",   P0.coef[3]  == 0);
    printf("\n");

    /* --------------------------------------------------
       2. WritePolynomial
       -------------------------------------------------- */
    printf("--- 2. WritePolynomial ---\n");

    // 5x^2 - 2x + 1
    int c1[] = {1, -2, 5};
    Polynomial Pw1 = makeP(2, c1);
    printf("Expected : 5x^2 - 2x + 1\nGot      : ");
    WritePolynomial(Pw1); printf("\n");

    // -3x^3 + 0x^2 + 4x - 7
    int c2[] = {-7, 4, 0, -3};
    Polynomial Pw2 = makeP(3, c2);
    printf("Expected : -3x^3 + 4x - 7\nGot      : ");
    WritePolynomial(Pw2); printf("\n");

    // Konstan: 5
    int c3[] = {5};
    Polynomial Pw3 = makeP(0, c3);
    printf("Expected : 5\nGot      : ");
    WritePolynomial(Pw3); printf("\n");

    // Nol semua
    int c4[] = {0, 0, 0};
    Polynomial Pw4 = makeP(2, c4);
    printf("Expected : 0\nGot      : ");
    WritePolynomial(Pw4); printf("\n");
    printf("\n");

    /* --------------------------------------------------
       3. AddPolynomial
       -------------------------------------------------- */
    printf("--- 3. AddPolynomial ---\n");

    // (x^2 + 2x + 3) + (x^2 - x + 1) = 2x^2 + x + 4
    int a1[] = {3, 2, 1};
    int a2[] = {1, -1, 1};
    Polynomial PA1 = makeP(2, a1);
    Polynomial PA2 = makeP(2, a2);
    Polynomial Radd = AddPolynomial(PA1, PA2);
    printf("(x^2+2x+3) + (x^2-x+1)\nExpected : 2x^2 + x + 4\nGot      : ");
    WritePolynomial(Radd); printf("\n");
    printTestResult("coef[2]=2", Radd.coef[2] == 2);
    printTestResult("coef[1]=1", Radd.coef[1] == 1);
    printTestResult("coef[0]=4", Radd.coef[0] == 4);

    // Beda degree: (x^3 + 1) + (2x + 3) = x^3 + 2x + 4
    int a3[] = {1, 0, 0, 1};
    int a4[] = {3, 2};
    Polynomial PA3 = makeP(3, a3);
    Polynomial PA4 = makeP(1, a4);
    Polynomial Radd2 = AddPolynomial(PA3, PA4);
    printf("(x^3+1) + (2x+3)\nExpected : x^3 + 2x + 4\nGot      : ");
    WritePolynomial(Radd2); printf("\n");
    printTestResult("degree=3",    Radd2.degree   == 3);
    printTestResult("coef[3]=1",   Radd2.coef[3]  == 1);
    printTestResult("coef[1]=2",   Radd2.coef[1]  == 2);
    printTestResult("coef[0]=4",   Radd2.coef[0]  == 4);
    printf("\n");

    /* --------------------------------------------------
       4. MultiplyPolynomial
       -------------------------------------------------- */
    printf("--- 4. MultiplyPolynomial ---\n");

    // (x + 1) * (x + 2) = x^2 + 3x + 2
    int m1[] = {1, 1};
    int m2[] = {2, 1};
    Polynomial PM1 = makeP(1, m1);
    Polynomial PM2 = makeP(1, m2);
    Polynomial Rmul = MultiplyPolynomial(PM1, PM2);
    printf("(x+1)*(x+2)\nExpected : x^2 + 3x + 2\nGot      : ");
    WritePolynomial(Rmul); printf("\n");
    printTestResult("coef[2]=1", Rmul.coef[2] == 1);
    printTestResult("coef[1]=3", Rmul.coef[1] == 3);
    printTestResult("coef[0]=2", Rmul.coef[0] == 2);

    // (x^2 + 1) * (x - 1) = x^3 - x^2 + x - 1
    int m3[] = {1, 0, 1};
    int m4[] = {-1, 1};
    Polynomial PM3 = makeP(2, m3);
    Polynomial PM4 = makeP(1, m4);
    Polynomial Rmul2 = MultiplyPolynomial(PM3, PM4);
    printf("(x^2+1)*(x-1)\nExpected : x^3 - x^2 + x - 1\nGot      : ");
    WritePolynomial(Rmul2); printf("\n");
    printTestResult("coef[3]=1",  Rmul2.coef[3] ==  1);
    printTestResult("coef[2]=-1", Rmul2.coef[2] == -1);
    printTestResult("coef[1]=1",  Rmul2.coef[1] ==  1);
    printTestResult("coef[0]=-1", Rmul2.coef[0] == -1);
    printf("\n");

    /* --------------------------------------------------
       5. EvaluatePolynomial
       -------------------------------------------------- */
    printf("--- 5. EvaluatePolynomial ---\n");

    // P(x) = x^2 - 2x + 1, P(3) = 9-6+1 = 4
    int e1[] = {1, -2, 1};
    Polynomial PE1 = makeP(2, e1);
    int eval1 = EvaluatePolynomial(PE1, 3);
    printf("P(x)=x^2-2x+1, P(3) -> Expected: 4, Got: %d\n", eval1);
    printTestResult("P(3)=4", eval1 == 4);

    // P(x) = 2x^3 + 0x^2 - x + 5, P(2) = 16+0-2+5 = 19
    int e2[] = {5, -1, 0, 2};
    Polynomial PE2 = makeP(3, e2);
    int eval2 = EvaluatePolynomial(PE2, 2);
    printf("P(x)=2x^3-x+5, P(2) -> Expected: 19, Got: %d\n", eval2);
    printTestResult("P(2)=19", eval2 == 19);

    // P(x) = 7 (konstan), P(100) = 7
    int e3[] = {7};
    Polynomial PE3 = makeP(0, e3);
    int eval3 = EvaluatePolynomial(PE3, 100);
    printf("P(x)=7 (konstan), P(100) -> Expected: 7, Got: %d\n", eval3);
    printTestResult("P(100)=7", eval3 == 7);
    printf("\n");

    /* --------------------------------------------------
       6. DerivativePolynomial
       -------------------------------------------------- */
    printf("--- 6. DerivativePolynomial ---\n");

    // d/dx(x^3 + 2x^2 + 3x + 4) = 3x^2 + 4x + 3
    int d1[] = {4, 3, 2, 1};
    Polynomial PD1 = makeP(3, d1);
    Polynomial Rd1 = DerivativePolynomial(PD1);
    printf("d/dx(x^3+2x^2+3x+4)\nExpected : 3x^2 + 4x + 3\nGot      : ");
    WritePolynomial(Rd1); printf("\n");
    printTestResult("degree=2",   Rd1.degree   == 2);
    printTestResult("coef[2]=3",  Rd1.coef[2]  == 3);
    printTestResult("coef[1]=4",  Rd1.coef[1]  == 4);
    printTestResult("coef[0]=3",  Rd1.coef[0]  == 3);

    // d/dx(5) = 0
    int d2[] = {5};
    Polynomial PD2 = makeP(0, d2);
    Polynomial Rd2 = DerivativePolynomial(PD2);
    printf("d/dx(5)\nExpected : 0\nGot      : ");
    WritePolynomial(Rd2); printf("\n");
    printTestResult("degree=0",   Rd2.degree   == 0);
    printTestResult("coef[0]=0",  Rd2.coef[0]  == 0);
    printf("\n");

    /* --------------------------------------------------
       7. ReadPolynomial (interaktif)
       -------------------------------------------------- */
    printf("--- 7. ReadPolynomial (interaktif) ---\n");
    printf("Format input:\n");
    printf("  Baris 1 : degree\n");
    printf("  Baris 2 : koefisien dari x^0, x^1, ..., x^degree\n");
    printf("  Contoh untuk 2x^2 - 3x + 1 : ketik '2' lalu '1 -3 2'\n\n");
    Polynomial Pr;
    printf("Masukkan degree: ");
    ReadPolynomial(&Pr);
    printf("Polynomial terbaca: ");
    WritePolynomial(Pr);
    printf("\n");
    printf("Nilai P(1) = %d\n", EvaluatePolynomial(Pr, 1));
    printf("Nilai P(2) = %d\n", EvaluatePolynomial(Pr, 2));
    printf("\n");

    printf("========================================\n");
    printf("   DRIVER TEST SELESAI\n");
    printf("========================================\n");

    return 0;
}
