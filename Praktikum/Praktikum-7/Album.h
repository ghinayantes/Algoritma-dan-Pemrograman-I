#ifndef ALBUM_H
#define ALBUM_H

#include "boolean.h"
#include <stdlib.h>

typedef int ElType;

typedef struct {
    ElType *buffer;
    int nEff;
    int capacity;
} Album;

void CreateAlbum(Album *A, int capacity);
/* I.S. A sembarang, capacity > 0 */
/* F.S. Album A terbentuk */

void DeallocateAlbum(Album *A);
/* I.S. A terdefinisi */
/* F.S. Memori dibebaskan */

boolean IsEmpty(Album A);
/* Mengembalikan true jika nEff == 0 */

boolean IsFull(Album A);
/* Mengembalikan true jika nEff == capacity */

void ExpandAlbum(Album *A, int num);
/* I.S. A terdefinisi, num > 0 */
/* F.S. Kapasitas bertambah sebanyak num. */

void SplitAndSwap(Album *A, int pivot);
/* Memotong album di indeks pivot, lalu menukar blok kiri dan kanan.
   Contoh: [1,2,3,4,5], pivot 1 (nilai 2) -> Potongan [1,2] dan [3,4,5]
   Hasil: [3,4,5,1,2]
   I.S. A terdefinisi, 0 <= pivot < nEff-1 */

void InjectList(Album *A1, Album A2, int idx);
/* Menyisipkan seluruh isi Album A2 ke dalam Album A1 mulai posisi idx
   Kapasitas A1 harus otomatis bertambah jika tidak muat
   I.S. A1, A2 terdefinisi, 0 <= idx <= A1.nEff */

void PrintAlbum(Album A);
/* I.S. A terdefinisi */
/* F.S. Cetak isi buffer album ke layar (akhiri \n) */
/* Contoh: [1,2,3]
Maka outputnya adalah -> 123 */

#endif