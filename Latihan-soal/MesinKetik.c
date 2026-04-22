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

void test(char *nama, bool ok) {
    printf("[%s] %s\n", ok ? "PASS" : "FAIL", nama);
}
 
void printState(ListKetik L) {
    int i;
    printf("  Teks  : \"");
    for (i = 0; i < L.nEff; i++) printf("%c", L.contents[i]);
    printf("\"\n");
    printf("  Cursor: %d | nEff: %d\n", L.cursor, L.nEff);
 
    /* Visualisasi posisi kursor */
    printf("  Visual: ");
    for (i = 0; i < L.nEff; i++) {
        if (i == L.cursor) printf("|");
        printf("%c", L.contents[i]);
    }
    if (L.cursor == L.nEff) printf("|");
    printf("\n");
}
 
int main() {
    ListKetik L;
 
    /* ===== CreateList ===== */
    printf("=== CreateList ===\n");
    CreateList(&L);
    test("nEff = 0", L.nEff == 0);
    test("cursor = 0", L.cursor == 0);
    test("length = 0", length(L) == 0);
 
    /* ===== typeChar - basic ===== */
    printf("\n=== typeChar ===\n");
    CreateList(&L);
    typeChar(&L, 'h');
    typeChar(&L, 'e');
    typeChar(&L, 'l');
    typeChar(&L, 'l');
    typeChar(&L, 'o');
    printState(L);
    test("typeChar - nEff=5", L.nEff == 5);
    test("typeChar - cursor=5", L.cursor == 5);
    test("typeChar - contents='hello'",
         L.contents[0]=='h' && L.contents[1]=='e' &&
         L.contents[2]=='l' && L.contents[3]=='l' && L.contents[4]=='o');
 
    /* typeChar di tengah */
    cursorHome(&L);
    cursorRight(&L); cursorRight(&L); /* cursor di 2 */
    typeChar(&L, 'X');
    printState(L);
    test("typeChar di tengah - isi 'heXllo'",
         L.contents[0]=='h' && L.contents[1]=='e' &&
         L.contents[2]=='X' && L.contents[3]=='l');
    test("typeChar di tengah - cursor=3", L.cursor == 3);
    test("typeChar di tengah - nEff=6", L.nEff == 6);
 
    /* typeChar di awal */
    cursorHome(&L);
    typeChar(&L, 'Z');
    printState(L);
    test("typeChar di awal - contents[0]='Z'", L.contents[0] == 'Z');
    test("typeChar di awal - cursor=1", L.cursor == 1);
 
    /* typeChar saat penuh */
    ListKetik Lfull;
    CreateList(&Lfull);
    int k;
    for (k = 0; k < CAPACITY; k++) typeChar(&Lfull, 'a');
    test("typeChar - penuh nEff=CAPACITY", Lfull.nEff == CAPACITY);
    typeChar(&Lfull, 'b'); /* harus ditolak */
    test("typeChar - ditolak saat penuh", Lfull.nEff == CAPACITY);
 
    /* ===== backspace ===== */
    printf("\n=== backspace ===\n");
    CreateList(&L);
    typeChar(&L, 'a'); typeChar(&L, 'b'); typeChar(&L, 'c');
    /* L = "abc", cursor=3 */
    backspace(&L);
    printState(L);
    test("backspace - hapus 'c', isi='ab'",
         L.nEff==2 && L.contents[0]=='a' && L.contents[1]=='b');
    test("backspace - cursor=2", L.cursor == 2);
 
    /* backspace di tengah */
    cursorLeft(&L); /* cursor=1 */
    backspace(&L);
    printState(L);
    test("backspace di tengah - hapus 'a', isi='b'",
         L.nEff==1 && L.contents[0]=='b');
    test("backspace di tengah - cursor=0", L.cursor == 0);
 
    /* backspace di awal (cursor=0, tidak terjadi) */
    backspace(&L);
    test("backspace di awal - tidak berubah",
         L.nEff==1 && L.cursor==0);
 
    /* ===== cursorLeft / cursorRight ===== */
    printf("\n=== navigasi kursor ===\n");
    CreateList(&L);
    typeChar(&L, 'a'); typeChar(&L, 'b'); typeChar(&L, 'c');
    /* cursor=3 */
    cursorLeft(&L);
    test("cursorLeft - cursor=2", L.cursor == 2);
    cursorLeft(&L); cursorLeft(&L);
    test("cursorLeft - cursor=0", L.cursor == 0);
    cursorLeft(&L); /* sudah di 0 */
    test("cursorLeft - tidak bisa < 0", L.cursor == 0);
 
    cursorRight(&L);
    test("cursorRight - cursor=1", L.cursor == 1);
    cursorRight(&L); cursorRight(&L);
    test("cursorRight - cursor=3 (nEff)", L.cursor == 3);
    cursorRight(&L); /* sudah di nEff */
    test("cursorRight - tidak bisa > nEff", L.cursor == 3);
 
    /* ===== cursorHome / cursorEnd ===== */
    cursorHome(&L);
    test("cursorHome - cursor=0", L.cursor == 0);
    cursorEnd(&L);
    test("cursorEnd - cursor=nEff", L.cursor == L.nEff);
 
    /* ===== deleteAll ===== */
    printf("\n=== deleteAll ===\n");
 
    /* Hapus karakter yang ada */
    CreateList(&L);
    typeChar(&L, 'a'); typeChar(&L, 'b'); typeChar(&L, 'a'); typeChar(&L, 'c'); typeChar(&L, 'a');
    /* L="abaca", cursor=5 */
    printState(L);
    deleteAll(&L, 'a');
    printState(L);
    test("deleteAll 'a' dari 'abaca' -> 'bc'",
         L.nEff==2 && L.contents[0]=='b' && L.contents[1]=='c');
    test("deleteAll - cursor ikut menyesuaikan", L.cursor == 2);
 
    /* deleteAll, kursor di tengah, karakter dihapus di kiri kursor */
    CreateList(&L);
    typeChar(&L, 'a'); typeChar(&L, 'b'); typeChar(&L, 'a'); typeChar(&L, 'c');
    /* L="abac", cursor=4 */
    cursorHome(&L);
    cursorRight(&L); cursorRight(&L); cursorRight(&L);
    /* cursor=3, menunjuk sebelum 'c' */
    printf("Sebelum deleteAll 'a' (cursor di 3, teks='abac'):\n");
    printState(L);
    deleteAll(&L, 'a');
    printf("Setelah deleteAll 'a':\n");
    printState(L);
    test("deleteAll - teks='bc'",
         L.nEff==2 && L.contents[0]=='b' && L.contents[1]=='c');
    test("deleteAll - cursor bergeser kiri (2 'a' di kiri kursor -> cursor=1)",
         L.cursor == 1);
 
    /* deleteAll karakter tidak ada */
    CreateList(&L);
    typeChar(&L, 'x'); typeChar(&L, 'y'); typeChar(&L, 'z');
    int prevNEff = L.nEff, prevCursor = L.cursor;
    deleteAll(&L, 'q');
    test("deleteAll - karakter tidak ada, tidak berubah",
         L.nEff == prevNEff && L.cursor == prevCursor);
 
    /* deleteAll semua karakter */
    CreateList(&L);
    typeChar(&L, 'a'); typeChar(&L, 'a'); typeChar(&L, 'a');
    deleteAll(&L, 'a');
    test("deleteAll - hapus semua, nEff=0", L.nEff == 0);
    test("deleteAll - hapus semua, cursor=0", L.cursor == 0);
 
    /* ===== printTeks ===== */
    printf("\n=== printTeks ===\n");
    CreateList(&L);
    printf("Expected: (newline saja)\n");
    printf("Got     : "); printTeks(L);
 
    typeChar(&L, 'h'); typeChar(&L, 'i');
    printf("Expected: hi\nGot     : "); printTeks(L);
 
    /* ===== Skenario gabungan ===== */
    printf("\n=== Skenario gabungan ===\n");
    CreateList(&L);
    /* Ketik "helo" lalu backspace, ketik "llo" */
    typeChar(&L, 'h'); typeChar(&L, 'e');
    typeChar(&L, 'l'); typeChar(&L, 'o');
    backspace(&L); /* hapus 'o', cursor=3 */
    typeChar(&L, 'l'); typeChar(&L, 'o'); /* "hello", cursor=5 */
    printf("Expected: hello\nGot     : "); printTeks(L);
    test("Skenario 1 - 'hello'",
         L.nEff==5 && L.contents[4]=='o');
 
    /* Ketik " world", lalu home, lalu sisipkan "say " */
    typeChar(&L, ' '); typeChar(&L, 'w'); typeChar(&L, 'o');
    typeChar(&L, 'r'); typeChar(&L, 'l'); typeChar(&L, 'd');
    cursorHome(&L);
    typeChar(&L, 's'); typeChar(&L, 'a'); typeChar(&L, 'y'); typeChar(&L, ' ');
    printf("Expected: say hello world\nGot     : "); printTeks(L);
    test("Skenario 2 - 'say hello world'", L.nEff == 15);
 
    printf("\n===== SELESAI =====\n");
    return 0;
}
