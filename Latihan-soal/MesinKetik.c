#include "MesinKetik.h"

/* ********** KONSTRUKTOR ********** */
void CreateList(ListKetik *L) {
    L->nEff = 0;
    L->cursor 0;
}
/* I.S. L sembarang */
/* F.S. Terbentuk List L kosong dengan nEff = 0 dan cursor = 0 */

/* ********** SELEKTOR ********** */
int length(ListKetik L) {
    return L.nEff;
}

/* ********** FUNGSI ********** */

void typeChar(ListKetik *L, ElType x) {
    if(L->nEff < CAPACITY) {
        
    }
}
/* I.S. L terdefinisi, mungkin penuh. */
/* F.S. Jika list belum penuh, karakter x disisipkan tepat pada posisi cursor. 
 * Semua karakter dari posisi cursor hingga akhir bergeser 1 langkah ke kanan. 
 * cursor kemudian bertambah 1. nEff bertambah 1. */

void backspace(ListKetik *L);
/* I.S. L terdefinisi. */
/* F.S. Jika cursor > 0, karakter tepat di kiri kursor (posisi cursor - 1) dihapus.
 * Karakter di kanannya bergeser 1 langkah ke kiri.
 * cursor berkurang 1. nEff berkurang 1. */

void deleteAll(ListKetik *L, ElType x);
/* I.S. L terdefinisi. */
/* F.S. SELURUH kemunculan karakter x di dalam list dihapus.
 * Sisa karakter merapat ke kiri (collapse).
 * PERHATIAN: Jika karakter yang terhapus berada di sebelah KIRI kursor, 
 * kursor harus ikut bergeser ke kiri agar posisi relatifnya terjaga. */


/* ********** NAVIGASI KURSOR ********** */

void cursorLeft(ListKetik *L);
/* Jika cursor > 0, cursor mundur 1 langkah. */

void cursorRight(ListKetik *L);
/* Jika cursor < nEff, cursor maju 1 langkah. */

void cursorHome(ListKetik *L);
/* cursor pindah ke awal list (posisi 0). */

void cursorEnd(ListKetik *L);
/* cursor pindah ke akhir teks (posisi nEff). */

void printTeks(ListKetik L);
/* I.S. L terdefinisi */
/* F.S. Mencetak karakter dalam L berderet, lalu cetak "\n" */
