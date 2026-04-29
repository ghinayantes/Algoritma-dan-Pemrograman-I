#include <stdio.h>
#include <stdlib.h>
#include "MemAllocator.h"

void CreateListMem(ListMem *l, int capacity) {
    l->buffer = (MemBlock*)malloc(capacity * sizeof(MemBlock));
    l->capacity = capacity;
    l->nEff = 0;
}
/* I.S. l sembarang, capacity > 0 */
/* F.S. Terbentuk list l kosong dengan kapasitas capacity */

void DealokasiListMem(ListMem *l) {
    if(l->buffer != NULL) free(l->buffer);
    l->buffer = NULL;
    l->capacity = 0;
    l->nEff = 0;
}
/* I.S. l terdefinisi */
/* F.S. List l dikembalikan ke sistem, l.capacity=0, l.nEff=0 */

void ShrinkToFit(ListMem *l) {
    int cap = l->nEff;
    MemBlock *temp = (MemBlock*)realloc(l->buffer, cap * sizeof(MemBlock));
    
    if (temp != NULL) { 
        l->buffer = temp;
        l->capacity = cap;
    }
}
/* Mengecilkan kapasitas list agar sama dengan nEff */

/**** Operasi Alokasi Memori ****/

void FreeMemory(ListMem *l, int address, int size) {
    if(l->nEff == l->capacity) {
        MemBlock *temp = (MemBlock*)realloc(l->buffer, l->capacity * 2 * sizeof(MemBlock));
        if(temp != NULL) {
            l->buffer = temp;
            l->capacity *= 2;
        }
    }

    l->buffer[l->nEff].address = address;
    l->buffer[l->nEff].size = size;
    l->nEff++;
}
/* I.S. l terdefinisi, address dan size valid */
/* Menambahkan informasi blok memori kosong baru ke kanan list l.
   Otomatis meningkatkan kapasitas dua kali lipat jika penuh sebelum insert. */

int AllocateMemory(ListMem *l, int reqSize) {
    int i, j;
    int allocaddr;
    if(reqSize <= 0) return ADDR_UNDEF;
    for(i = 0; i < l->nEff; i++) {
        if(l->buffer[i].size >= reqSize) {
            allocaddr = l->buffer[i].address;
            l->buffer[i].address += reqSize;
            l->buffer[i].size -= reqSize;
 
            if(l->buffer[i].size == 0) {
                for(j = i; j < l->nEff - 1; j++) {
                    l->buffer[j] = l->buffer[j + 1];
                }
                l->nEff--;
            }
            return allocaddr;
        }
    }
    return ADDR_UNDEF;
}
/* I.S. l terdefinisi */
/* Mencoba mengalokasikan memori sebesar reqSize di satu blok memori.
   Pencarian blok memori dilakukan secara linier dari kiri list */
/* Jika blok dengan ukuran mencukupi ditemukan,
   alokasikan memori sebesar reqSize di blok tersebut,
   dan naikkan address di blok sebesar reqSize */
/* Jika ukuran blok habis (0) setelah dialokasikan,
   maka hapus blok dari list, dan geser semua blok di kanannya ke kiri list */
/* Kembalikan address memori yang didapat, atau ADDR_UNDEF jika alokasi gagal atau reqSize <= 0 */

/* Fungsi bantu: sort blok berdasarkan address ascending */
static void SortByAddress(ListMem *l) {
    int i, j;
    MemBlock key;
    for(i = 1; i < l->nEff; i++) {
        key = l->buffer[i];
        j = i - 1;
        while(j >= 0 && l->buffer[j].address > key.address) {
            l->buffer[j+1] = l->buffer[j];
            j--;
        }
        l->buffer[j + 1] = key;
    }
}

void Defragment(ListMem *l) {
    int i, j;
    SortByAddress(l);
    i = 0;
    while (i < l->nEff - 1) {
        if(l->buffer[i].address + l->buffer[i].size == l->buffer[i + 1].address) {
            l->buffer[i].size += l->buffer[i + 1].size;
            for(j = i + 1; j < l->nEff - 1; j++) {
                l->buffer[j] = l->buffer[j + 1];
            }
            l->nEff--;
        } 
        else i++;
    }
    ShrinkToFit(l);
}
/* I.S. l terdefinisi, blok memori didalamnya belum tentu urut berdasarkan address */
/* Menyatukan pecahan/fragmen informasi blok memori di address yang tersebar */
/* Proses defragmentasi:
    - Untuk setiap blok memori:
        - Jika blok memori persis bersebelahan dengan blok setelahnya,
          maka gabungkan kedua blok menjadi satu blok memori di list l.
    - Kompres list agar kapasitasnya sama dengan nEff.

   ILUSTRASI:
   Address: 1 2 3 4 5 6 7 8 9
   Blok:    x x x y y y - - -
   Karena blok x & y bersebelahan, maka disatukan menjadi:

   Address: 1 2 3 4 5 6 7 8 9
   Blok:    x x x x x x - - -

   Boleh membuat fungsi tambahan untuk membantu.
*/