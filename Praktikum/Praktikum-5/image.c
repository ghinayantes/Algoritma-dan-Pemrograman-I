#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include "image.h"

/* ***************************************************************** */
/* VALIDASI DAN KONSTRUKTOR                                          */
/* ***************************************************************** */
bool IsPixelValid(int r, int g, int b) {
    if ((r >= 0 && r <= 255) && (g >= 0 && g <= 255) && (b >= 0 && b <= 255)) return true;
    return false;
}
/* Mengirim TRUE jika nilai R, G, B berada pada rentang [0..255] (inklusif)*/

void CreatePixel(PIXEL *P, int r, int g, int b) {
    if(IsPixelValid(r,g,b)) {
        Red(*P) = r;
        Green(*P) = g;
        Blue(*P) = b;
    }
    else {
        Red(*P) = 0;
        Green(*P) = 0;
        Blue(*P) = 0;
    }
}
/* I.S. P sembarang, r, g, b terdefinisi */
/* F.S. Jika r, g, b valid, membentuk PIXEL P.
        Jika tidak valid, P diinisialisasi dengan PIXEL hitam (0,0,0) */

void CreateImage(IMAGE *I, int r, int c) {
    int i, j;
    PIXEL hitam;
    CreatePixel(&hitam, 0, 0, 0);

    Rows(*I) = r;
    Cols(*I) = c;

    for(i = 0; i <= MAX_ROWS; i++) {
        for(j = 0; j <= MAX_COLS; j++) {
            Elmt(*I, i, j) = hitam;
        }
    }
}
/* I.S. I sembarang, r dan c terdefinisi (0 < r <= MAX_ROWS, 0 < c <= MAX_COLS)
 */
/* F.S. Membentuk IMAGE I dengan ukuran r baris dan c kolom.
        Semua elemen PIXEL di dalamnya diinisialisasi dengan warna hitam (0,0,0)
 */

void CopyImage(IMAGE I1, IMAGE *I2) {
    int i, j;

    for(i = 0; i <= MAX_ROWS; i++) {
        for(j = 0; j <= MAX_COLS; j++) {
            Elmt(*I2, i, j) = Elmt(I1, i, j);
        }
    }

    Rows(*I2) = Rows(I1);
    Cols(*I2) = Cols(I1);
}
/* I.S. I1 terdefinisi, I2 sembarang */
/* F.S. I2 menjadi salinan persis (deep copy bukan hanya reference) dari I1 */

/* ***************************************************************** */
/* OPERASI DASAR PIXEL (FILTERING)                                   */
/* ***************************************************************** */
/*bool IsPixelEqual(PIXEL P1, PIXEL P2) {
    if((Red(P1) == Red(P2)) && (Green(P1) == Green(P2)) && (Blue(P1 == Blue(P2)))) return true;
    else return false;
} */
/* Mengirim true jika P1 identik dengan P2 (R, G, B sama) */

PIXEL InvertPixel(PIXEL P) {
    Red(P) = 255 - Red(P);
    Green(P) = 255 - Green(P);
    Blue(P) = 255 - Blue(P);

    return P;
}
/* Mengirim hasil inverse dari P. (Rumus: R_baru = 255 - R_lama) */

PIXEL GrayscalePixel(PIXEL P) {
    Red(P) = Green(P) = Blue(P) = ((Red(P) + Green(P) + Blue(P))/3);

    return P;
}
/* Mengirim hasil konversi P menjadi warna abu-abu.
   (Rumus: R_baru = G_baru = B_baru = (R + G + B) / 3)
   Pembagian integer mengikuti aturan C (truncation toward zero). */

PIXEL AdjustBrightnessPixel(PIXEL P, int delta) {
    
    Red(P) += delta;
    Green(P) += delta;
    Blue(P) += delta;
    

    return P;
}
/* Mengirim PIXEL baru yang nilai R, G, B-nya ditambah dengan delta.
   Delta bisa bernilai positif (menerangkan) atau negatif (menggelapkan).
   NOTE: Nilai R, G, B harus tetap valid! */

/* ***************************************************************** */
/* OPERASI DASAR IMAGE                                               */
/* ***************************************************************** */
bool IsImageEqual(IMAGE I1, IMAGE I2) {
    if((Rows(I1) == Rows(I2)) && (Cols(I1) == Cols(I2))) {
        int i,j;

        for(i = 0; i <= MAX_ROWS; i++) {
            for(j = 0; j <= MAX_COLS; j++) {
                if((I1.data[i][j].R != I2.data[i][j].R)||(I1.data[i][j].G != I2.data[i][j].G)||(I1.data[i][j].B != I2.data[i][j].B)) return false; 
            }
        }
    }
    return true;
}
/* Mengirim true jika I1 dan I2 memiliki ukuran dan isi pixel yang 100% sama */

IMAGE ApplyFilter(IMAGE I, int filterType) {
    int i,j;
    if(filterType == 1) {
        for(i = 0; i <= MAX_ROWS; i++) {
            for(j = 0; j <= MAX_COLS; j++) {
                InvertPixel(Elmt(I, i, j)); 
            }
        }
    }
    else if(filterType == 2) {
        for(i = 0; i <= MAX_ROWS; i++) {
            for(j = 0; j <= MAX_COLS; j++) {
                GrayscalePixel(Elmt(I, i, j)); 
            }
        }
    }

    return I;
}
/* Mengembalikan IMAGE baru hasil penerapan filter ke seluruh pixel I.
   Jika filterType == 1: Terapkan InvertPixel
   Jika filterType == 2: Terapkan GrayscalePixel
   Jika tipe lain: Kembalikan salinan I apa adanya. */

IMAGE CropImage(IMAGE I, int startRow, int startCol, int endRow, int endCol) {
    IMAGE Ic;
    int i,j;
    Rows(I) = endRow - startRow + 1;
    Cols(I) = endCol - startCol + 1;

    CreateImage(&Ic, Rows(I), Cols(I));

    for(i = 0; i <= Rows(I); i++) {
        for(j = 0; j <= Cols(I); j++) {
            Elmt(Ic, i, j) = Elmt(I, i, j);
        }
    }
    return Ic;
}
/* Mengembalikan IMAGE baru berupa potongan (sub-image) dari I.
   Prekondisi: startRow <= endRow, startCol <= endCol, dan koordinat valid.
   Ukuran IMAGE baru adalah (endRow - startRow + 1) x (endCol - startCol + 1).
*/

IMAGE BlendImage(IMAGE I1, IMAGE I2) {
    int i,j;
    IMAGE r;

    CreateImage(&r,Rows(I1),Cols(I1));

    for(i = 0; i <= Rows(I1); i++) {
        for(j = 0; j <= Cols(I1); j++) {
            r.data[i][j].R = (I1.data[i][j].R + I2.data[i][j].R)/2;
            r.data[i][j].G = (I1.data[i][j].G + I2.data[i][j].G)/2;
            r.data[i][j].B = (I1.data[i][j].B + I2.data[i][j].B)/2;
        }
    }

    return r;

}
/* Mengembalikan IMAGE baru hasil percampuran (overlay) I1 dan I2.
   Prekondisi: Ukuran I1 dan I2 dijamin sama.
   Rumus pixel baru: R_baru = (R_I1 + R_I2) / 2 (Lakukan pada G dan B juga).
*/


