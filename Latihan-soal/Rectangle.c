#include <stdio.h>
#include "Rectangle.h"

/* *** DEFINISI PROTOTIPE PRIMITIF *** */

/* *** Konstruktor membentuk RECTANGLE *** */
RECTANGLE MakeRectangle(float width, float height) {
    RECTANGLE result;

    Width(result) = width;
    Height(result) = height;

    return result;
}
/* *** Membentuk sebuah denah RECTANGLE dari komponen-komponen kayunya *** */

/* *** KELOMPOK Interaksi dengan I/O device, BACA/TULIS *** */
void readRectangle(RECTANGLE *R) {
    float w, h;

    scanf("%f %f", &w, &h);
    *R = MakeRectangle(w, h);
}
/* Membaca nilai panjang dan lebar dari keyboard (input dari Grunkle Stan) 
   dan membentuk RECTANGLE R berdasarkan dari nilai tersebut */
/* Komponen panjang dan lebar dibaca dalam 1 baris, dipisahkan 1 buah spasi */
/* Contoh: 1 2
   akan membentuk RECTANGLE dengan panjang 1 dan lebar 2 */

void printRectangle(RECTANGLE R) {
    printf("R(%.2fx%.2f)", R.width, R.height);
}
/* Nilai R ditulis ke layar monitor kasir dengan format "R(PanjangxLebar)"
   misalnya denah dengan panjang 1 dan lebar 2 akan ditulis
   sebagai "R(1.00x2.00)" */

boolean isSquare(RECTANGLE R) {
    return R.width == R.height;
}
/* Mengirimkan true jika width dan height dari RECTANGLE sama (Bujur sangkar sempurna / Anomali Geometris) */

boolean isNotSquare(RECTANGLE R) {
    return R.height != R.width;
}
/* Mengirimkan true jika width dan height dari RECTANGLE tidak sama (Normal) */

float area(RECTANGLE R) {
    return R.width * R.height;
}
/* Menghitung luas RECTANGLE dengan rumus: PanjangxLebar*/

float perimeter(RECTANGLE R) {
    return 2 * (R.width + R.height);
}
/* I.S. R terdefinisi */
/* F.S. Keliling R dengan rumus 2 * (width + height) (Untuk menghitung panjang pagar pembatas) */

void swap(RECTANGLE *R) {
    float temp = R->height;
    R->height = R->width;
    R->width = temp;
}
/* R yang panjang dan lebarnya ditukar akibat efek medan gravitasi, 
   sehingga panjang sebesar lebar dan lebar sebesar panjang */

void add(RECTANGLE *R, float deltaWidth, float deltaHeight) {
    R->width += deltaWidth;
    R->height += deltaHeight;
}
/* R yang ditambah panjangnya sebesar deltaWidth dan ditambah lebarnya sebesar deltaHeight */

RECTANGLE plusRectangle(RECTANGLE R, float deltaWidth, float deltaHeight) {
    add(&R, deltaWidth, deltaHeight);
    return R;
}
/* Mengirim salinan blueprint R yang panjangnya adalah Width(R) + deltaWidth 
   dan lebarnya adalah Height(R) + deltaHeight */
