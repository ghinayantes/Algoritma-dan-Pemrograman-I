#ifndef MEM_ALLOC_H
#define MEM_ALLOC_H

#define ADDR_UNDEF -1

// Definisi elemen blok memori kosong
typedef struct {
    int address; // Alamat memori kosong
    int size;    // Ukuran blok memori yang tersedia
} MemBlock;

// ListMem menyimpan blok-blok memori kosong
typedef struct {
    MemBlock *buffer;
    int capacity;
    int nEff;
} ListMem;

void CreateListMem(ListMem *l, int capacity);
/* I.S. l sembarang, capacity > 0 */
/* F.S. Terbentuk list l kosong dengan kapasitas capacity */

void DealokasiListMem(ListMem *l);
/* I.S. l terdefinisi */
/* F.S. List l dikembalikan ke sistem, l.capacity=0, l.nEff=0 */

void ShrinkToFit(ListMem *l);
/* Mengecilkan kapasitas list agar sama dengan nEff */

/**** Operasi Alokasi Memori ****/

void FreeMemory(ListMem *l, int address, int size);
/* I.S. l terdefinisi, address dan size valid */
/* Menambahkan informasi blok memori kosong baru ke kanan list l.
   Otomatis meningkatkan kapasitas dua kali lipat jika penuh sebelum insert. */

int AllocateMemory(ListMem *l, int reqSize);
/* I.S. l terdefinisi */
/* Mencoba mengalokasikan memori sebesar reqSize di satu blok memori.
   Pencarian blok memori dilakukan secara linier dari kiri list */
/* Jika blok dengan ukuran mencukupi ditemukan,
   alokasikan memori sebesar reqSize di blok tersebut,
   dan naikkan address di blok sebesar reqSize */
/* Jika ukuran blok habis (0) setelah dialokasikan,
   maka hapus blok dari list, dan geser semua blok di kanannya ke kiri list */
/* Kembalikan address memori yang didapat, atau ADDR_UNDEF jika alokasi gagal atau reqSize <= 0 */

void Defragment(ListMem *l);
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
