#ifndef LOG_SCANNER_H
#define LOG_SCANNER_H

#include "boolean.h"

#define INITIAL_CAPACITY 5

typedef struct {
    int timestamp;
    int port;
    int severity;       // 1 = Low, 2 = Medium, 3 = High
} LogItem;

typedef struct {
    LogItem *buffer; // Pointer ke blok memori array
    int capacity;       // Kapasitas teralokasi saat ini
    int nEff;           // Jumlah elemen efektif
} LogScanner;

void CreateLogScanner(LogScanner *l, int capacity);
/* I.S. l sembarang, capacity > 0 */
/* F.S. Terbentuk list l kosong dengan kapasitas capacity */

void DealokasiLogScanner(LogScanner *l);
/* I.S. l terdefinisi */
/* F.S. List l dikembalikan ke sistem, l.capacity=0, l.nEff=0 */

boolean IsEmpty(LogScanner l);
/* Mengirimkan true jika list l kosong, false jika tidak */

boolean IsFull(LogScanner l);
/* Mengirimkan true jika list l penuh, false jika tidak */

void ExpandList(LogScanner *l);
/* Melipatgandakan kapasitas list (capacity * 2) */

void ShrinkToFit(LogScanner *l);
/* Mengecilkan kapasitas list agar sama dengan nEff */
/* Jika nEff == 0, set kapasitas ke INITIAL_CAPACITY */

void TambahLog(LogScanner *l, LogItem val);
/* Menambahkan elemen LogItem di akhir list */
/* Jika list penuh, list akan menggandakan (kali dua) kapasitas secara otomatis */

void HapusLog(LogScanner *l, int idx, LogItem *val);
/* Menghapus log pada indeks tertentu */
/* print "INDEKS INVALID" tanpa tanda kutip diikuti newline, jika idx tidak valid */
/* Elemen sisa digeser ke depan, kapasitas tidak berubah */

void FilterHighSeverity(LogScanner l, LogScanner *l_out);
/* I.S. l terdefinisi, l_out belum terdefinisi */
/* Mengkopi semua log dengan severity == 3 (High) ke l_out */
/* Kapasitas l_out sama dengan jumlah log High yang ditemukan */
/* Jika jumlah log High = 0, maka set kapasitas ke INITIAL_CAPACITY */

void CetakStatusList(LogScanner l);
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
#endif