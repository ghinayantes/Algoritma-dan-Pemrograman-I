#include <stdio.h>
#include <math.h>
#include <float.h>

// Hitung titik potong dua garis (P1-P2) dan (P3-P4)
// Return 1 jika berpotongan, 0 jika paralel
int titikPotong(double x1, double y1, double x2, double y2,
                double x3, double y3, double x4, double y4,
                double *px, double *py) {
    double denom = (x1-x2)*(y3-y4) - (y1-y2)*(x3-x4);
    
    if (fabs(denom) < 1e-9) return 0; // paralel
    
    double t = ((x1-x3)*(y3-y4) - (y1-y3)*(x3-x4)) / denom;
    
    *px = x1 + t*(x2-x1);
    *py = y1 + t*(y2-y1);
    return 1;
}

double jarak(double x1, double y1, double x2, double y2) {
    return sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
}

int main() {
    double xA, yA, xB, yB, xC, yC, xD, yD, xE, yE;
    scanf("%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf",
          &xA, &yA, &xB, &yB, &xC, &yC, &xD, &yD, &xE, &yE);

    double minJarak = DBL_MAX;
    double px, py;

    // Kombinasi 1: AB & CD
    if (titikPotong(xA,yA,xB,yB, xC,yC,xD,yD, &px,&py)) {
        double d = jarak(px, py, xE, yE);
        if (d < minJarak) minJarak = d;
    }

    // Kombinasi 2: AC & BD
    if (titikPotong(xA,yA,xC,yC, xB,yB,xD,yD, &px,&py)) {
        double d = jarak(px, py, xE, yE);
        if (d < minJarak) minJarak = d;
    }

    // Kombinasi 3: AD & BC
    if (titikPotong(xA,yA,xD,yD, xB,yB,xC,yC, &px,&py)) {
        double d = jarak(px, py, xE, yE);
        if (d < minJarak) minJarak = d;
    }

    printf("%.2f\n", minJarak);
    return 0;
}