#include <stdio.h>
#include <stdlib.h>
#include "Accounting.h"

void CreateJournal(Journal *l, int capacity) {
    l->buffer = (Transaction*)malloc(capacity * sizeof(Transaction));
        l->capacity = capacity;
        l->nEff = 0;
    
}
/* I.S. l sembarang, capacity > 0 */
/* F.S. Terbentuk list l kosong dengan kapasitas capacity */

void DealokasiJournal(Journal *l) {
    if(l->buffer != NULL) free(l->buffer);
    l->buffer = NULL;
    l->capacity = 0;
    l->nEff = 0;
}
/* I.S. l terdefinisi */
/* F.S. List l dikembalikan ke sistem, l.capacity=0, l.nEff=0 */

boolean IsEmpty(Journal l) {
    return l.nEff == 0;
}
/* Mengirimkan true jika list l kosong, false jika tidak */

boolean IsFull(Journal l) {
    return l.nEff == l.capacity;
}
/* Mengirimkan true jika list l penuh, false jika tidak */

void ExpandJournal(Journal *l) {
    if(l->capacity == 0) return;
    Transaction *temp = (Transaction*)realloc(l->buffer, l->capacity * 2 * sizeof(Transaction));
    if(temp != NULL) {
        l->buffer = temp;
        l->capacity *= 2;
    }
}
/* Meningkatkan kapasitas list sebesar dua kali lipat */

void InsertLastTrx(Journal *l, Transaction val) {
    if(l->nEff >= (0.75 * l->capacity)) ExpandJournal(l);
    l->buffer[l->nEff] = val;
    l->nEff++;
}
/* Memasukkan Transaction val ke ujung akhir list */
/* Sebelum insert, jika list sudah lebih dari atau sama dengan 75% penuh,
   maka kapasitas list digandakan secara otomatis */

void CloneJournal(Journal lIn, Journal *lOut) {
    int i;
    CreateJournal(lOut, lIn.nEff);
    for(i = 0; i < lIn.nEff; i++) {
        lOut->buffer[i] = lIn.buffer[i];
        lOut->nEff++;
    }
}
/* Menyalin seluruh isi lIn ke lOut di alamat memori berbeda.
   Kapasitas lOut disesuaikan tepat sebesar nEff dari lIn. */

long long GetCompanyBalance(Journal l, int idCompany) {
    int i;
    long long totdeb = 0, totkre = 0;
    for(i = 0; i< l.nEff; i++) {
        if(l.buffer[i].idCompany == idCompany) {
            totdeb += l.buffer[i].debit;
            totkre += l.buffer[i].kredit;
        }
    }
    return totdeb - totkre;
}
/* Mengembalikan total saldo (Total Debit - Total Kredit)
   khusus untuk idCompany tertentu di dalam List. */
/* Keluarkan 0 jika company tidak valid */

void SortByTimestamp(Journal *l, boolean ascending) {
    int i, j;
    if(l->nEff > 0) {
        Transaction temp;    
        if(ascending) {
            for(i = 0; i < l->nEff-1; i++) {
                for(j = i+1; j < l->nEff; j++) {
                    if(l->buffer[i].timestamp > l->buffer[j].timestamp) {
                        temp = l->buffer[i];
                        l->buffer[i] = l->buffer[j];
                        l->buffer[j] = temp;
                    }
                }
            }
        }
        else {
            for(i = 0; i < l->nEff-1; i++) {
                for(j = i+1; j < l->nEff; j++) {
                    if(l->buffer[i].timestamp < l->buffer[j].timestamp) {
                        temp = l->buffer[i];
                        l->buffer[i] = l->buffer[j];
                        l->buffer[j] = temp;
                    }
                }
            }
        }
    }
}
/* Mengurutkan elemen berdasarkan timestamp */
/* Algoritma sorting bebas */

void MergeJournal(Journal l1, Journal l2, Journal *lOut) {
    int i, j;
    CreateJournal(lOut, l1.nEff + l2.nEff);
    for(i = 0; i < l1.nEff; i++) {
        lOut->buffer[lOut->nEff] = l1.buffer[i];
        lOut->nEff++;
    }
    for(j = 0; j < l2.nEff; j++) {
        lOut->buffer[lOut->nEff] = l2.buffer[j];
        lOut->nEff++;
    }

    SortByTimestamp(lOut, true);
}
/* Menggabungkan dua list tidak terurut l1 dan l2
   ke list lOut yang terurut dengan timestamp menaik */

void PrintJournal(Journal l) {
    printf("Capacity: %d | nEff: %d\n", l.capacity, l.nEff);
    if(l.nEff == 0) {
        printf("LIST KOSONG\n");
        return;
    }
    int i;
    for(i = 0; i < l.nEff; i++) {
        printf("[%d] TrxID: %d | CompID: %d | TS: %d | D: %lld | K: %lld\n", i+1, l.buffer[i].idTrx, l.buffer[i].idCompany, l.buffer[i].timestamp, l.buffer[i].debit, l.buffer[i].kredit);
    }
}
/* Print list saat ini dengan format:
    Capacity: <capacity> | nEff: <nEff>
diikuti dengan:
    [1] TrxID: <idTrx> | CompID: <idCompany> | TS: <timestamp> | D: <debit> | K: <kredit>
    ...
    [N] TrxID: <idTrx> | CompID: <idCompany> | TS: <timestamp> | D: <debit> | K: <kredit>
jika list berisi, atau:
    LIST KOSONG
jika list kosong.

Semua baris diakhiri newline.
*/