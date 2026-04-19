#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "sdf.h"

/* ***************************************************************** */
/* DEFINISI KONSTRUKTOR                                              */
/* ***************************************************************** */
Point MakePoint(float x, float y) {
    Point P;
    X(P) = x;
    Y(P) = y;

    return P;
}
/*  I.S. x dan y terdefinisi
    F.S. Menghasilkan Point dengan koordinat (x, y) */

Vector MakeVector(float dx, float dy) {
    Vector V;
    DX(V) = dx;
    DY(V) = dy;

    return V;
}
/*  I.S. dx dan dy terdefinisi
    F.S. Menghasilkan Vector dengan komponen (dx, dy) */

/* ***************************************************************** */
/* OPERASI MATEMATIKA & VEKTOR                                       */
/* ***************************************************************** */
float Jarak(Point p1, Point p2) {
    float x1,x2,y1,y2;
    x1 = X(p1);
    x2 = X(p2);
    y1 = Y(p1);
    y2 = Y(p2);

    return sqrt(((x2-x1)*(x2-x1)) + ((y2-y1)*(y2-y1)));
}
/*  I.S. p1 dan p2 terdefinisi
    F.S. Menghasilkan jarak Euclidean antara p1 dan p2 
    Rumus jarak Euclidean: sqrt((x2-x1)^2 + (y2-y1)^2) */

void Normalize(Vector *v) {
    float p = sqrt(DX(*v)*DX(*v) + DY(*v)*DY(*v));
    if(p != 0) {
        DX(*v) /= p;
        DY(*v) /= p;
    }
}
/*  I.S. v terdefinisi dan memiliki panjang tidak nol
    F.S. v menjadi vektor satuan (panjang = 1.0) jika panjang awalnya tidak nol 
    Rumus normalize: v = v / ||v|| 
    ||v|| = sqrt(dx^2 + dy^2) */

/* ***************************************************************** */
/* OPERASI DASAR                                                     */
/* ***************************************************************** */
float SDF_Circle(Point p, Point center, float radius) {
    float jarak;
    float x1,x2,y1,y2;
    x1 = X(p);
    x2 = X(center);
    y1 = Y(p);
    y2 = Y(center);

    jarak = sqrt(((x2-x1)*(x2-x1)) + ((y2-y1)*(y2-y1)));

    return jarak - radius;
}
/*  I.S. p, center, dan radius terdefinisi
    F.S. Menghasilkan nilai signed distance dari titik p ke lingkaran
         berpusat di center dengan jari-jari radius.
         Nilai negatif berarti titik berada di dalam lingkaran,
         nol berarti tepat di tepi, dan positif berarti di luar lingkaran. 
    SDF dihitung sebagai jarak dari titik p ke pusat lingkaran dikurangi jari-jari. */

Point Move(Point p, Vector v, float step) {
    Point pnew;
    pnew.x = p.x + v.dx * step;
    pnew.y = p.y + v.dy * step;

    return pnew;
}
/*  I.S. p, v, dan step terdefinisi
    F.S. Menghasilkan titik baru hasil perpindahan titik p sejauh step
         ke arah vektor v */


 /*int main() {
    Point A = MakePoint(0.0, 0.0);
    Point B = MakePoint(3.0, 4.0);
    float d = Jarak(A, B);
    //printf("%.2f", d);

    Vector V = MakeVector(0.0, 10.0);
    Normalize(&V);
    //printf("%.2f", DY(V));

    Point posisiKita = MakePoint(10.0, 0.0);
    Point anomali = MakePoint(10.0, 10.0);
    float radius = 2.0;
    float d2 = SDF_Circle(posisiKita, anomali, radius);
    printf("%.2f",d2);

    Point awal = MakePoint(0.0, 0.0);
    Vector arah = MakeVector(1.0, 0.0);
    Point akhir = Move(awal, arah, 5.5);

    return 0;
} */