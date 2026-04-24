#include <stdio.h>
#include "Cursor.h"

void InitCursor (Cursor *C) {
    int i;
    C->CursorPos = 0;
    C->TextLen = 0;
    for(i = 0; i < MAX_LENGTH; i++){
        C->TextInput[i] = '\0';
    }
}
/* Membuat struct Cursor baru dengan posisi cursor di awal (0) dan belum ada teks apapun pada input */

void MoveLeft (Cursor *C, int step) {
    int count = step;
    while(count > 0 && C->CursorPos > 0) {
        C->CursorPos--;
        count--;
    }
}
/* Menggeser posisi cursor ke kiri sejauh step atau sampai berada sebelum karakter pertama text input */

void MoveRight (Cursor *C, int step) {
    int count = step;
    while(count > 0 && C->CursorPos != C->TextLen) {
        C->CursorPos++;
        count--;
    }
}
/* Menggeser posisi cursor ke kanan sejauh step atau sampai melewati karakter terakhir text input */

void Type (Cursor *C, char input) {
    int i;
    for(i = C->TextLen; i > C->CursorPos; i--) {
        C->TextInput[i] = C->TextInput[i-1];
    }
    C->TextInput[C->CursorPos] = input;
    C->CursorPos++;
    C->TextLen++;
    C->TextInput[C->TextLen] = '\0';
}
/* Menerima karakter input dan menambahkannya di posisi cursor saat ini
Setelah menambahkan karakter, posisi cursor akan bergeser selangkah ke kanan */

void Backspace (Cursor *C) {
    if(C->CursorPos == 0) return;
    int i;
    for(i = C->CursorPos-1; i < C->TextLen-1; i++) {
        C->TextInput[i] = C->TextInput[i+1];
    }
    C->CursorPos--;
    C->TextLen--;
    C->TextInput[C->TextLen] = '\0';
}
/* Menghapus satu karakter di kiri posisi cursor saat ini 
dan menggeser posisi cursor selangkah ke kiri */

void Home (Cursor *C) {
    C->CursorPos = 0;
}
/* Memindahkan posisi kursor ke paling awal (sebelum karakter pertama) */

void End (Cursor *C) {
    C->CursorPos = C->TextLen;
}
/* Memindahkan posisi kursor ke paling akhir (setelah karakter terakhir) */

void Print (Cursor C) {
    int i;
    for(i = 0; i <= C.TextLen; i++) {
        if(C.CursorPos == i) printf("|");
        if(i != C.TextLen) printf("%c", C.TextInput[i]);
    }
    printf("\n");
}
/* Mencetak isi dari text input saat ini yang disertai dengan posisi kursor (dilambangkan |), formatnya:
Misal, text input = "halo", posisi kursor = 1, maka cetak:
h|alo
Jangan lupa akhiri dengan newline ("\n") */