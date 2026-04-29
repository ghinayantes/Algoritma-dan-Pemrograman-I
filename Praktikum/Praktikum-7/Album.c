#include <stdio.h>
#include "Album.h"

void CreateAlbum(Album *A, int capacity) {
    A->buffer = (ElType*)malloc(capacity * sizeof(ElType));
    A->capacity = capacity;
    A->nEff = 0;
}
/* I.S. A sembarang, capacity > 0 */
/* F.S. Album A terbentuk */

void DeallocateAlbum(Album *A) {
    if(A->buffer != NULL) free(A->buffer);
    A->buffer = NULL;
    A->capacity = 0;
    A->nEff = 0;
}
/* I.S. A terdefinisi */
/* F.S. Memori dibebaskan */

boolean IsEmpty(Album A) {
    return A.nEff == 0;
}
/* Mengembalikan true jika nEff == 0 */

boolean IsFull(Album A) {
    return A.nEff == A.capacity;
}
/* Mengembalikan true jika nEff == capacity */

void ExpandAlbum(Album *A, int num) {
    ElType *temp = (ElType*)realloc(A->buffer, (A->capacity + num) * sizeof(ElType));
    if(temp != NULL) {
        A->buffer = temp;
        A->capacity += num;
    }
}
/* I.S. A terdefinisi, num > 0 */
/* F.S. Kapasitas bertambah sebanyak num. */

void SplitAndSwap(Album *A, int pivot) {
    int kiri  = pivot + 1;
    int kanan = A->nEff - kiri;
    int i;
    ElType *temp = (ElType*)malloc(A->nEff * sizeof(ElType));

    if(temp == NULL) return;
    for(i = 0; i < kanan; i++) {
        temp[i] = A->buffer[kiri + i];
    }
    for(i = 0; i < kiri; i++) {
        temp[kanan + i] = A->buffer[i];
    }
    for(i = 0; i < A->nEff; i++) {
        A->buffer[i] = temp[i];
    }
    free(temp);
}
/* Memotong album di indeks pivot, lalu menukar blok kiri dan kanan.
   Contoh: [1,2,3,4,5], pivot 1 (nilai 2) -> Potongan [1,2] dan [3,4,5]
   Hasil: [3,4,5,1,2]
   I.S. A terdefinisi, 0 <= pivot < nEff-1 */

void InjectList(Album *A1, Album A2, int idx) {
    int i;
    if(A1->nEff + A2.nEff > A1->capacity) {
        ExpandAlbum(A1, A2.nEff);
    }
    for(i = A1->nEff - 1; i >= idx; i--) {
        A1->buffer[i + A2.nEff] = A1->buffer[i];
    }
    for(i = 0; i < A2.nEff; i++) {
        A1->buffer[idx + i] = A2.buffer[i];
    }
 
    A1->nEff += A2.nEff;
}
/* Menyisipkan seluruh isi Album A2 ke dalam Album A1 mulai posisi idx
   Kapasitas A1 harus otomatis bertambah jika tidak muat
   I.S. A1, A2 terdefinisi, 0 <= idx <= A1.nEff */

void PrintAlbum(Album A) {
    int i;
    for(i = 0; i < A.nEff; i++) {
        printf("%d", A.buffer[i]);
    }
    printf("\n");
}
/* I.S. A terdefinisi */
/* F.S. Cetak isi buffer album ke layar (akhiri \n) */
/* Contoh: [1,2,3]
Maka outputnya adalah -> 123 */
