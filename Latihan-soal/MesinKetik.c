#include "MesinKetik.h"

/* ********** KONSTRUKTOR ********** */
void CreateList(ListKetik *L) {
    L->nEff = 0;
    L->cursor = 0;
}
/* I.S. L sembarang */
/* F.S. Terbentuk List L kosong dengan nEff = 0 dan cursor = 0 */

/* ********** SELEKTOR ********** */
int length(ListKetik L) {
    return L.nEff;
}

/* ********** FUNGSI ********** */

void typeChar(ListKetik *L, ElType x) {
    int i;
    if(L->nEff < CAPACITY) {
        for(i = length(*L); i > L->cursor; i--) {
            L->contents[i] = L->contents[i-1];
        }
        L->contents[L->cursor] = x;
        L->nEff++;
        L->cursor++;
    }
}
/* I.S. L terdefinisi, mungkin penuh. */
/* F.S. Jika list belum penuh, karakter x disisipkan tepat pada posisi cursor. 
 * Semua karakter dari posisi cursor hingga akhir bergeser 1 langkah ke kanan. 
 * cursor kemudian bertambah 1. nEff bertambah 1. */

void backspace(ListKetik *L) {
    int i;
    if(L->cursor > 0) {
        for(i = L->cursor-1; i < length(*L)-1; i++) {
            L->contents[i] = L->contents[i+1];
        }
        L->cursor--;
        L->nEff--;
    }
}
/* I.S. L terdefinisi. */
/* F.S. Jika cursor > 0, karakter tepat di kiri kursor (posisi cursor - 1) dihapus.
 * Karakter di kanannya bergeser 1 langkah ke kiri.
 * cursor berkurang 1. nEff berkurang 1. */

void deleteAll(ListKetik *L, ElType x) {
    int i = 0, ig;
    while (i < length(*L)) {
        if(L->contents[i] == x) {
            for(ig = i; ig < length(*L)-1; ig++) {
                    L->contents[ig] = L->contents[ig+1];
                }
            if(i < L->cursor) L->cursor--;
            L->nEff--;
        }
        else i++;
    }
}
/* I.S. L terdefinisi. */
/* F.S. SELURUH kemunculan karakter x di dalam list dihapus.
 * Sisa karakter merapat ke kiri (collapse).
 * PERHATIAN: Jika karakter yang terhapus berada di sebelah KIRI kursor, 
 * kursor harus ikut bergeser ke kiri agar posisi relatifnya terjaga. */


/* ********** NAVIGASI KURSOR ********** */

void cursorLeft(ListKetik *L) {
    if(L->cursor > 0) L->cursor--;
}
/* Jika cursor > 0, cursor mundur 1 langkah. */

void cursorRight(ListKetik *L) {
    if(L->cursor < L->nEff) L->cursor++;
}
/* Jika cursor < nEff, cursor maju 1 langkah. */

void cursorHome(ListKetik *L) {
    L->cursor = 0;
}
/* cursor pindah ke awal list (posisi 0). */

void cursorEnd(ListKetik *L) {
    L->cursor = L->nEff;
}
/* cursor pindah ke akhir teks (posisi nEff). */

void printTeks(ListKetik L) {
    int i;
    for(i = 0; i < length(L); i++) {
        printf("%c", L.contents[i]);
    }
    printf("\n");
}
/* I.S. L terdefinisi */
/* F.S. Mencetak karakter dalam L berderet, lalu cetak "\n" */

