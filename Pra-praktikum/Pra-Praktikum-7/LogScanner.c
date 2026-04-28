#include <stdio.h>
#include <stdlib.h>
#include "LogScanner.h"
#include "boolean.h"

void CreateLogScanner(LogScanner *l, int capacity) {
    l->buffer = (LogItem*) malloc(capacity * sizeof(LogItem));
    l->nEff = 0;
    l->capacity = capacity;
}
/* I.S. l sembarang, capacity > 0 */
/* F.S. Terbentuk list l kosong dengan kapasitas capacity */

void DealokasiLogScanner(LogScanner *l) {
    if (l->buffer != NULL) free(l->buffer);
    l->buffer = NULL;
    l->nEff = 0;
    l->capacity = 0;
}
/* I.S. l terdefinisi */
/* F.S. List l dikembalikan ke sistem, l.capacity=0, l.nEff=0 */

boolean IsEmpty(LogScanner l) {
    return l.nEff == 0;
}
/* Mengirimkan true jika list l kosong, false jika tidak */

boolean IsFull(LogScanner l) {
    return l.nEff == l.capacity;
}
/* Mengirimkan true jika list l penuh, false jika tidak */

void ExpandList(LogScanner *l) {
    LogItem *temp = (LogItem*)realloc(l->buffer, l->capacity * 2 * sizeof(LogItem));
    if (temp != NULL) {
        l->buffer = temp;
        l->capacity *= 2;
    }
}
/* Melipatgandakan kapasitas list (capacity * 2) */

void ShrinkToFit(LogScanner *l) {
    int cap;
    if (l->nEff == 0) cap = INITIAL_CAPACITY;
    else cap = l->nEff;

    LogItem *temp = (LogItem*)realloc(l->buffer, cap * sizeof(LogItem));
    
    if (temp != NULL) { 
        l->buffer = temp;
        l->capacity = cap;
    }
}
/* Mengecilkan kapasitas list agar sama dengan nEff */
/* Jika nEff == 0, set kapasitas ke INITIAL_CAPACITY */

void TambahLog(LogScanner *l, LogItem val) {
    if(IsFull(*l)) ExpandList(l);
    l->buffer[l->nEff] = val;
    l->nEff++;
}
/* Menambahkan elemen LogItem di akhir list */
/* Jika list penuh, list akan menggandakan (kali dua) kapasitas secara otomatis */

void HapusLog(LogScanner *l, int idx, LogItem *val) {
    int i;
    if(idx < 0 || idx >= l->nEff) printf("INDEKS INVALID\n");
    else {
        *val = l->buffer[idx];
        for(i = idx; i < l->nEff-1; i++) {
            l->buffer[i] = l->buffer[i+1];
        }
        l->nEff--;
    }
}
/* Menghapus log pada indeks tertentu */
/* print "INDEKS INVALID" tanpa tanda kutip diikuti newline, jika idx tidak valid */
/* Elemen sisa digeser ke depan, kapasitas tidak berubah */

void FilterHighSeverity(LogScanner l, LogScanner *l_out) {
    int i, cap = 0;
    for(i = 0; i < l.nEff; i++) {
        if(l.buffer[i].severity == 3) cap++;
    }
    if(cap > 0) {
        CreateLogScanner(l_out, cap);
        for(i = 0; i < l.nEff; i++) {
            if(l.buffer[i].severity == 3) {
                l_out->buffer[l_out->nEff] = l.buffer[i];
                l_out->nEff++;
            }
        }
    }
    else CreateLogScanner(l_out, INITIAL_CAPACITY);
}
/* I.S. l terdefinisi, l_out belum terdefinisi */
/* Mengkopi semua log dengan severity == 3 (High) ke l_out */
/* Kapasitas l_out sama dengan jumlah log High yang ditemukan */
/* Jika jumlah log High = 0, maka set kapasitas ke INITIAL_CAPACITY */

void CetakStatusList(LogScanner l) {
    int i;
    printf("Capacity: %d | nEff: %d\n", l.capacity, l.nEff);
    if(IsEmpty(l)) printf("LIST KOSONG\n");
    else {
        for(i = 0; i < l.nEff; i++) {
            printf("[%d] TS: %d | Port: %d | Sev: %d\n", i+1, l.buffer[i].timestamp, l.buffer[i].port, l.buffer[i].severity);
        }
    }
}
/* Print list saat ini dengan format:
    Capacity: <capacity> | nEff: <nEff>
diikuti dengan:
    [1] TS: <timestamp> | Port: <port> | Sev: <severity>
    ...
    [N] TS: <timestamp> | Port: <port> | Sev: <severity>
jika list berisi, atau:
    LIST KOSONG
jika list kosong.

Semua baris diakhiri newline.
*/



