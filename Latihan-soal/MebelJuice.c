#include "MebelJuice.h"

/* Constructor minuman */
/*
 * Membuat pesanan minuman berdasarkan:
 * - nama minuman
 * - tipe suhu (DINGIN, NORMAL, HANGAT)
 * - tipe gula (LOW, MEDIUM, HIGH)
 * - jumlah es (gram)
 * - jumlah glitter (gram)
 * - jumlah permen dinosaurus
 * 
 * Hint: Bisa gunakan method strcpy()
 * Contoh penggunaan:
 * strcpy(warga.pekerjaan, pekerjaan);
*/
Minuman buatMinuman(char *nama, Suhu suhu, LevelGula levelGula, int es, int glitter, int dino) {
    Minuman L;
    Topping T;
    strcpy(L.nama, nama);
    L.suhu = suhu;
    L.levelGula = levelGula;
    L.es = es;

    T.glitter = glitter;
    T.dino = dino;
    L.topping = T;

    return L;
}

/**
 * Menghitung volume minuman dalam gram:
 * volume = 200 + berat es + (jumlah dinosaurus * 5) + berat glitter
 */
float hitungVolume(Minuman m) {
    Topping t = m.topping;
    return 200 + m.es + (t.dino * 5) + t.glitter;
}

/**
 * Menghitung kalori minuman:
 * total = base + topping.dino*10 + glitter*2
 * 
 * dengan base memiliki kalori:
 * LOW    = 20
 * MEDIUM = 40
 * HIGH   = 60
 */
float hitungKalori(Minuman m) {
    float total = m.topping.dino * 10.0 + m.topping.glitter * 2.0;

    if(m.levelGula == LOW) return total + 20.0;
    else if(m.levelGula == MEDIUM) return total + 40.0;
    else return total + 60;
}

/* Constructor pelanggan */
/*
 * Membuat pelanggan berdasarkan:
 * - nama pelanggan
 * - id pelanggan
 * 
 * Hint: Bisa gunakan method strcpy()
 * Contoh penggunaan:
 * strcpy(warga.pekerjaan, pekerjaan);
*/
Pelanggan buatPelanggan(char *nama, int id) {
    Pelanggan P;
    strcpy(P.nama, nama);
    P.id = id;

    return P;
}

/* Constructor pesanan */
/*
 * Membuat pesanan minuman dengan memasukkan detail:
 * - identitas pelanggan
 * - minuman pelanggan
 * - volume minuman
 * - kalori minuman 
 * 
 * Hint: Bisa gunakan method strcpy()
 * Contoh penggunaan:
 * strcpy(warga.pekerjaan, pekerjaan);
*/
Pesanan buatPesanan(Pelanggan pelanggan, Minuman m) {
    Pesanan P;

    P.pelanggan = pelanggan;
    P.minuman = m;
    P.volumeGelas = hitungVolume(m);
    P.kaloriGelas = hitungKalori(m);

    return P;
}

**
 * Menampilkan detail pesanan dengan format:
 * "Nama Pelanggan: <nama pelanggan>"
 * "ID Pelanggan: <id>"
 * "Minuman: <nama minuman"
 * "Suhu: <suhu>"
 * "Level Gula: <gula>"
 * "Es: <berat gula> gram"
 * "Glitter: %d gram"
 * "Dino: <jumlah dino>"
 * "Volume: <total volume dengan dua angka desimal> ml"
 * "Kalori: <total kalori dengan dua angka desimal> kkal"
 */
void tampilkanPesanan(Pesanan p) {
    printf("Nama Pelanggan: %s\n", p.pelanggan.nama);
    printf("ID Pelanggan: %d\n", p.pelanggan.id);
    printf("Minuman: %s\n", p.minuman.nama);
    printf("Suhu: ");
    if (p.minuman.suhu == DINGIN) printf("DINGIN\n");
    else if (p.minuman.suhu == NORMAL) printf("NORMAL\n");
    else printf("HANGAT\n");
    printf("Level Gula: ");
    if (p.minuman.levelGula == LOW) printf("LOW\n");
    else if (p.minuman.levelGula == MEDIUM) printf("MEDIUM\n");
    else printf("HIGH\n");
    printf("Es: %d gram\n", p.minuman.es);
    printf("Glitter: %d gram\n", p.minuman.topping.glitter);
    printf("Dino: %d\n", p.minuman.topping.dino);
    printf("Volume: %.2f ml\n", p.volumeGelas);
    printf("Kalori: %.2f kkal\n", p.kaloriGelas);
}

/**
 * Membuat daftar pesanan kosong
 */
void initList(ListPesanan *l) {
    l->jumlah = 0;
}

/**
 * Return true jika daftar pesanan kosong
 */
int isEmpty(ListPesanan l) {
    return l.jumlah == 0;
}

/**
 * Return true jika daftar pesanan penuh (MAX_PESANAN)
 */
int isFull(ListPesanan l) {
    return l.jumlah == MAX_PESANAN;
}

/**
 * Menambahkan pesanan ke daftar pesanan
 * Pesanan tidak ditambahkan jika daftar pesanan penuh
 */
void tambahPesanan(ListPesanan *l, Pesanan p) {
    if(l->jumlah != MAX_PESANAN) {
        l->data[l->jumlah] = p;
        l.jumlah += 1;
    }
}

/**
 * Menghapus pesanan terakhir dari daftar pesanan
 * Jika daftar kosong, tidak melakukan apa-apa
 */
void hapusPesanan(ListPesanan *l) {
    if(l->jumlah > 0) {
        l->jumlah--;
    }
}

/**
 * Menampilkan detail seluruh pesanan yang ada
 */
void tampilkanSemuaPesanan(ListPesanan l) {
    int i;
    for(i = 0; i < l.jumlah; i++) {
        tampilkanPesanan(l.data[i]);
    }
}

/* UTILITY */
/* Implementasi fungsi di bawah ini untuk mengubah enum menjadi string */

/* Return nilai enum suhu dalam bentuk string ke buffer*/
void suhuToString(Suhu s, char *buffer) {
    if(s == DINGIN) strcpy(buffer, "DINGIN");
    else if(s == NORMAL) strcpy(buffer, "NORMAL");
    else strcpy(buffer, "HANGAT");
}

/* Return nilai enum gula dalam bentuk string ke buffer*/
void levelGulaToString(LevelGula g, char *buffer) {
    if(g == LOW) strcpy(buffer, "LOW");
    else if(g == MEDIUM) strcpy(buffer, "MEDIUM");
    else strcpy(buffer, "HIGH");
}



