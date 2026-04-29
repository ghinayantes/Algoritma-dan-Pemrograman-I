#ifndef ACCOUNTING_H
#define ACCOUNTING_H

#include "boolean.h"

typedef struct {
    int idTrx; // unik
    int idCompany;
    int timestamp; // unik
    long long debit;
    long long kredit;
} Transaction;

typedef struct {
    Transaction *buffer;
    int capacity;
    int nEff;
} Journal;

void CreateJournal(Journal *l, int capacity);
/* I.S. l sembarang, capacity > 0 */
/* F.S. Terbentuk list l kosong dengan kapasitas capacity */

void DealokasiJournal(Journal *l);
/* I.S. l terdefinisi */
/* F.S. List l dikembalikan ke sistem, l.capacity=0, l.nEff=0 */

boolean IsEmpty(Journal l);
/* Mengirimkan true jika list l kosong, false jika tidak */

boolean IsFull(Journal l);
/* Mengirimkan true jika list l penuh, false jika tidak */

void ExpandJournal(Journal *l);
/* Meningkatkan kapasitas list sebesar dua kali lipat */

void InsertLastTrx(Journal *l, Transaction val);
/* Memasukkan Transaction val ke ujung akhir list */
/* Sebelum insert, jika list sudah lebih dari atau sama dengan 75% penuh,
   maka kapasitas list digandakan secara otomatis */

void CloneJournal(Journal lIn, Journal *lOut);
/* Menyalin seluruh isi lIn ke lOut di alamat memori berbeda.
   Kapasitas lOut disesuaikan tepat sebesar nEff dari lIn. */

long long GetCompanyBalance(Journal l, int idCompany);
/* Mengembalikan total saldo (Total Debit - Total Kredit)
   khusus untuk idCompany tertentu di dalam List. */
/* Keluarkan 0 jika company tidak valid */

void SortByTimestamp(Journal *l, boolean ascending);
/* Mengurutkan elemen berdasarkan timestamp */
/* Algoritma sorting bebas */

void MergeJournal(Journal l1, Journal l2, Journal *lOut);
/* Menggabungkan dua list tidak terurut l1 dan l2
   ke list lOut yang terurut dengan timestamp menaik */

void PrintJournal(Journal l);
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

#endif