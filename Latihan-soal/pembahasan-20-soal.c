/*
 * ================================================================
 *  pembahasan_20soal.c
 *  Pembahasan lengkap 20 soal Linked List — Praktikum Alpro ITB
 *
 *  Soal  1-15 : soal cerita competitive programming (sebelumnya)
 *  Soal 16-20 : soal dengan ADT lengkap (struct + semua fungsi)
 *
 *  Kompilasi  : gcc pembahasan_20soal.c -o pembahasan_20soal
 *  Jalankan   : ./pembahasan_20soal
 * ================================================================
 *
 *  DAFTAR SOAL
 *  -----------
 *  [listberkait]
 *   01. Lampu Jalan Gang Sempit      — hitung elemen ganjil
 *   02. Antrian Tiket Konser         — cek non-decreasing
 *   03. Kode Rahasia Dua Arah        — sum indeks genap vs ganjil
 *   04. Kompetisi Lari Estafet       — hitung > rata-rata
 *   05. Penjaga Gudang Ajaib         — partisi negatif ke depan
 *   06. Sandi Geser Peradaban Kuno   — tambah nilai indeks
 *   07. Dekoder Pesan Berpasangan    — jumlahkan pasangan
 *   08. Jembatan Penghubung          — interleave dua list
 *   09. Sensor Gempa Multi-Stasiun   — Q query selisih > K
 *  [listsirkuler]
 *   10. Roda Putar Perayaan Desa     — Josephus problem
 *   11. Permainan Lompat Katak       — hapus semua genap
 *   12. Stasiun Radio Nangor FM      — SKIP / CURRENT query
 *   13. Virus Bergulir Jaringan Cincin — maju S+T langkah
 *   14. Turnamen Cincin Petarung     — eliminasi nilai lebih kecil
 *   15. Mesin Waktu Cincin Nangor    — R / S / P operations
 *  [ADT penuh — struct + semua fungsi didefinisikan ulang]
 *   16. Pencatatan Skor Turnamen     — list berkait, sum K terbesar
 *   17. Antrian Rumah Sakit Melingkar— list sirkuler, prioritas
 *   18. Rangkaian Lampu Hias         — list berkait, run-length encode
 *   19. Misi Penjelajah Luar Angkasa — list sirkuler, split genap/ganjil
 *   20. Kriptografi Nangor           — list berkait, enkripsi XOR shift
 * ================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ================================================================
 *  BAGIAN A — ADT LIST BERKAIT (digunakan soal 1-9, 16, 18, 20)
 * ================================================================ */
#define TRUE  1
#define FALSE 0
typedef unsigned char boolean;
typedef int ElType;

/* --- Node & List berkait --- */
typedef struct LBNode *LBAddress;
typedef struct LBNode {
    ElType   info;
    LBAddress next;
} LBNode;
typedef LBAddress LBList;

#define LB_INFO(p)  ((p)->info)
#define LB_NEXT(p)  ((p)->next)
#define LB_FIRST(l) (l)

/* Alokasi */
LBAddress lb_newNode(ElType val) {
    LBAddress p = (LBAddress)malloc(sizeof(LBNode));
    if (p) { LB_INFO(p) = val; LB_NEXT(p) = NULL; }
    return p;
}
void lb_createList(LBList *l)   { *l = NULL; }
boolean lb_isEmpty(LBList l)   { return l == NULL; }

int lb_length(LBList l) {
    int c = 0; LBAddress p = l;
    while (p) { c++; p = LB_NEXT(p); }
    return c;
}
void lb_insertFirst(LBList *l, ElType val) {
    LBAddress p = lb_newNode(val);
    if (p) { LB_NEXT(p) = *l; *l = p; }
}
void lb_insertLast(LBList *l, ElType val) {
    if (lb_isEmpty(*l)) { lb_insertFirst(l, val); return; }
    LBAddress p = lb_newNode(val);
    if (p) {
        LBAddress q = *l;
        while (LB_NEXT(q)) q = LB_NEXT(q);
        LB_NEXT(q) = p;
    }
}
void lb_deleteFirst(LBList *l, ElType *val) {
    LBAddress p = *l;
    *val = LB_INFO(p);
    *l = LB_NEXT(p);
    free(p);
}
void lb_deleteLast(LBList *l, ElType *val) {
    if (!LB_NEXT(*l)) { lb_deleteFirst(l, val); return; }
    LBAddress p = *l, prev = NULL;
    while (LB_NEXT(p)) { prev = p; p = LB_NEXT(p); }
    *val = LB_INFO(p);
    LB_NEXT(prev) = NULL;
    free(p);
}
void lb_deleteAt(LBList *l, int idx, ElType *val) {
    if (idx == 0) { lb_deleteFirst(l, val); return; }
    LBAddress p = *l;
    for (int i = 0; i < idx-1; i++) p = LB_NEXT(p);
    LBAddress t = LB_NEXT(p);
    *val = LB_INFO(t);
    LB_NEXT(p) = LB_NEXT(t);
    free(t);
}
void lb_displayList(LBList l) {
    if (lb_isEmpty(l)) { printf("[]"); return; }
    printf("[%d", LB_INFO(l));
    LBAddress p = LB_NEXT(l);
    while (p) { printf(",%d", LB_INFO(p)); p = LB_NEXT(p); }
    printf("]");
}
LBList lb_concat(LBList l1, LBList l2) {
    LBList l3; lb_createList(&l3);
    LBAddress p = l1;
    while (p) { lb_insertLast(&l3, LB_INFO(p)); p = LB_NEXT(p); }
    p = l2;
    while (p) { lb_insertLast(&l3, LB_INFO(p)); p = LB_NEXT(p); }
    return l3;
}
/* Bebaskan semua node */
void lb_freeList(LBList *l) {
    ElType v;
    while (!lb_isEmpty(*l)) lb_deleteFirst(l, &v);
}

/* ================================================================
 *  BAGIAN B — ADT LIST SIRKULER (digunakan soal 10-15, 17, 19)
 * ================================================================ */
typedef struct SCNode *SCAddress;
typedef struct SCNode {
    ElType    info;
    SCAddress next;
} SCNode;
typedef struct { SCAddress first; } SCList;

#define SC_INFO(p)  ((p)->info)
#define SC_NEXT(p)  ((p)->next)
#define SC_FIRST(l) ((l).first)

SCAddress sc_allocate(ElType val) {
    SCAddress p = (SCAddress)malloc(sizeof(SCNode));
    if (p) { SC_INFO(p) = val; SC_NEXT(p) = NULL; }
    return p;
}
void sc_deallocate(SCAddress p) { SC_NEXT(p) = NULL; free(p); }
void sc_createList(SCList *l)   { SC_FIRST(*l) = NULL; }
boolean sc_isEmpty(SCList l)   { return SC_FIRST(l) == NULL; }

int sc_length(SCList l) {
    if (sc_isEmpty(l)) return 0;
    int c = 1; SCAddress p = SC_FIRST(l);
    while (SC_NEXT(p) != SC_FIRST(l)) { c++; p = SC_NEXT(p); }
    return c;
}
void sc_insertFirst(SCList *l, ElType val) {
    SCAddress p = sc_allocate(val);
    if (!p) return;
    if (sc_isEmpty(*l)) {
        SC_NEXT(p) = p; SC_FIRST(*l) = p;
    } else {
        SCAddress last = SC_FIRST(*l);
        while (SC_NEXT(last) != SC_FIRST(*l)) last = SC_NEXT(last);
        SC_NEXT(p) = SC_FIRST(*l);
        SC_NEXT(last) = p;
        SC_FIRST(*l) = p;
    }
}
void sc_insertLast(SCList *l, ElType val) {
    if (sc_isEmpty(*l)) { sc_insertFirst(l, val); return; }
    SCAddress p = sc_allocate(val);
    if (!p) return;
    SCAddress last = SC_FIRST(*l);
    while (SC_NEXT(last) != SC_FIRST(*l)) last = SC_NEXT(last);
    SC_NEXT(last) = p;
    SC_NEXT(p) = SC_FIRST(*l);
}
void sc_deleteFirst(SCList *l, ElType *val) {
    SCAddress p = SC_FIRST(*l);
    *val = SC_INFO(p);
    if (SC_NEXT(p) == SC_FIRST(*l)) {
        SC_FIRST(*l) = NULL;
    } else {
        SCAddress last = SC_FIRST(*l);
        while (SC_NEXT(last) != SC_FIRST(*l)) last = SC_NEXT(last);
        SC_FIRST(*l) = SC_NEXT(p);
        SC_NEXT(last) = SC_FIRST(*l);
    }
    sc_deallocate(p);
}
void sc_displayList(SCList l) {
    if (sc_isEmpty(l)) { printf("[]"); return; }
    SCAddress p = SC_FIRST(l);
    printf("[%d", SC_INFO(p)); p = SC_NEXT(p);
    while (p != SC_FIRST(l)) { printf(",%d", SC_INFO(p)); p = SC_NEXT(p); }
    printf("]");
}
void sc_freeList(SCList *l) {
    ElType v;
    while (!sc_isEmpty(*l)) sc_deleteFirst(l, &v);
}

/* ================================================================
 *  HELPER UMUM
 * ================================================================ */
void printSep(const char *judul) {
    printf("\n");
    printf("================================================================\n");
    printf("  %s\n", judul);
    printf("================================================================\n");
}
void printCase(int c) { printf("\n--- Contoh %d ---\n", c); }

/* ================================================================
 *  SOAL 01 — Lampu Jalan Gang Sempit
 *  Hitung elemen ganjil dalam list berkait.
 *  Input : N, lalu N bilangan
 *  Output: banyak elemen ganjil
 * ================================================================ */
int soal01_countOdd(LBList l) {
    int ctr = 0;
    LBAddress p = l;
    while (p) {
        if (LB_INFO(p) % 2 != 0) ctr++;
        p = LB_NEXT(p);
    }
    return ctr;
}
void demo01() {
    printSep("SOAL 01 — Lampu Jalan Gang Sempit (hitung elemen ganjil)");
    int cases[][6] = {{5, 1,2,3,4,5},{4, 2,4,6,8},{1, 7}};
    int exp[] = {3, 0, 1};
    for (int c = 0; c < 3; c++) {
        printCase(c+1);
        int n = cases[c][0];
        LBList l; lb_createList(&l);
        for (int i = 1; i <= n; i++) lb_insertLast(&l, cases[c][i]);
        printf("Input  : N=%d, list=", n); lb_displayList(l); printf("\n");
        int hasil = soal01_countOdd(l);
        printf("Output : %d  (expected %d) %s\n", hasil, exp[c], hasil==exp[c]?"[OK]":"[FAIL]");
        lb_freeList(&l);
    }
}

/* ================================================================
 *  SOAL 02 — Antrian Tiket Konser
 *  Cek apakah list non-decreasing (terurut tidak menurun).
 *  Output: "YA" atau "TIDAK"
 * ================================================================ */
boolean soal02_isNonDec(LBList l) {
    LBAddress p = l;
    while (p && LB_NEXT(p)) {
        if (LB_INFO(p) > LB_INFO(LB_NEXT(p))) return FALSE;
        p = LB_NEXT(p);
    }
    return TRUE;
}
void demo02() {
    printSep("SOAL 02 — Antrian Tiket Konser (cek non-decreasing)");
    int cases[][5] = {{4, 1,3,3,5},{3, 5,3,7},{1, 99}};
    const char *exp[] = {"YA","TIDAK","YA"};
    for (int c = 0; c < 3; c++) {
        printCase(c+1);
        int n = cases[c][0];
        LBList l; lb_createList(&l);
        for (int i = 1; i <= n; i++) lb_insertLast(&l, cases[c][i]);
        lb_displayList(l); printf("\n");
        const char *res = soal02_isNonDec(l) ? "YA" : "TIDAK";
        printf("Output : %s  (expected %s) %s\n", res, exp[c], strcmp(res,exp[c])==0?"[OK]":"[FAIL]");
        lb_freeList(&l);
    }
}

/* ================================================================
 *  SOAL 03 — Kode Rahasia Dua Arah
 *  Sum elemen indeks genap vs ganjil (indeks mulai 0).
 *  Output: "SAMA" jika sama, atau "BEDA <selisih_absolut>"
 * ================================================================ */
void soal03_cekSumIdx(LBList l) {
    long long sg = 0, so = 0; int idx = 0;
    LBAddress p = l;
    while (p) {
        if (idx % 2 == 0) sg += LB_INFO(p);
        else              so += LB_INFO(p);
        idx++; p = LB_NEXT(p);
    }
    if (sg == so) printf("SAMA");
    else {
        long long s = sg > so ? sg - so : so - sg;
        printf("BEDA %lld", s);
    }
    printf("\n");
}
void demo03() {
    printSep("SOAL 03 — Kode Rahasia Dua Arah (sum indeks genap vs ganjil)");
    int cases[][5] = {{4, 1,2,3,4},{4, 1,2,2,1},{3, 5,5,5}};
    /* [5,5,5]: idx0=5,idx2=5 -> sumG=10; idx1=5 -> sumO=5 -> BEDA 5 */
    const char *exp[] = {"BEDA 2","SAMA","BEDA 5"};
    for (int c = 0; c < 3; c++) {
        printCase(c+1);
        int n = cases[c][0];
        LBList l; lb_createList(&l);
        for (int i = 1; i <= n; i++) lb_insertLast(&l, cases[c][i]);
        lb_displayList(l); printf("\n");
        printf("Output : "); soal03_cekSumIdx(l);
        printf("Expected: %s\n", exp[c]);
        lb_freeList(&l);
    }
}

/* ================================================================
 *  SOAL 04 — Kompetisi Lari Estafet
 *  Hitung elemen yang > rata-rata (integer division).
 * ================================================================ */
int soal04_countAboveAvg(LBList l) {
    int n = lb_length(l);
    if (n == 0) return 0;
    long long sum = 0;
    LBAddress p = l;
    while (p) { sum += LB_INFO(p); p = LB_NEXT(p); }
    int avg = (int)(sum / n);
    int ctr = 0;
    p = l;
    while (p) { if (LB_INFO(p) > avg) ctr++; p = LB_NEXT(p); }
    return ctr;
}
void demo04() {
    printSep("SOAL 04 — Kompetisi Lari Estafet (hitung > rata-rata)");
    int cases[][6] = {{5, 1,2,3,4,5},{3, 3,3,3},{4, 1,1,1,9}};
    int exp[] = {2, 0, 1};
    for (int c = 0; c < 3; c++) {
        printCase(c+1);
        int n = cases[c][0];
        LBList l; lb_createList(&l);
        for (int i = 1; i <= n; i++) lb_insertLast(&l, cases[c][i]);
        lb_displayList(l); printf("\n");
        int hasil = soal04_countAboveAvg(l);
        printf("Output : %d  (expected %d) %s\n", hasil, exp[c], hasil==exp[c]?"[OK]":"[FAIL]");
        lb_freeList(&l);
    }
}

/* ================================================================
 *  SOAL 05 — Penjaga Gudang Ajaib
 *  Partisi: semua negatif ke depan, non-negatif ke belakang,
 *  urutan relatif dipertahankan. Gunakan dua list bantu + concat.
 * ================================================================ */
void soal05_partisiNegatif(LBList *l) {
    LBList neg, pos;
    lb_createList(&neg); lb_createList(&pos);
    LBAddress p = *l;
    while (p) {
        if (LB_INFO(p) < 0) lb_insertLast(&neg, LB_INFO(p));
        else                 lb_insertLast(&pos, LB_INFO(p));
        p = LB_NEXT(p);
    }
    lb_freeList(l);
    *l = lb_concat(neg, pos);
    lb_freeList(&neg); lb_freeList(&pos);
}
void demo05() {
    printSep("SOAL 05 — Penjaga Gudang Ajaib (partisi negatif ke depan)");
    int cases[][7] = {{6, 3,-1,2,-4,5,-2},{3, 1,2,3},{3, -3,-1,-2}};
    const char *exp[] = {"[-1,-4,-2,3,2,5]","[1,2,3]","[-3,-1,-2]"};
    for (int c = 0; c < 3; c++) {
        printCase(c+1);
        int n = cases[c][0];
        LBList l; lb_createList(&l);
        for (int i = 1; i <= n; i++) lb_insertLast(&l, cases[c][i]);
        printf("Sebelum: "); lb_displayList(l); printf("\n");
        soal05_partisiNegatif(&l);
        printf("Sesudah: "); lb_displayList(l); printf("\n");
        printf("Expected: %s\n", exp[c]);
        lb_freeList(&l);
    }
}

/* ================================================================
 *  SOAL 06 — Sandi Geser Peradaban Kuno
 *  Tambahkan nilai indeks ke setiap elemen (in-place).
 * ================================================================ */
void soal06_tambahIndeks(LBList *l) {
    int idx = 0;
    LBAddress p = *l;
    while (p) { LB_INFO(p) += idx; idx++; p = LB_NEXT(p); }
}
void demo06() {
    printSep("SOAL 06 — Sandi Geser Peradaban Kuno (elemen += indeks)");
    int cases[][6] = {{4, 1,2,3,4},{3, 0,0,0},{5, 5,4,3,2,1}};
    const char *exp[] = {"[1,3,5,7]","[0,1,2]","[5,5,5,5,5]"};
    for (int c = 0; c < 3; c++) {
        printCase(c+1);
        int n = cases[c][0];
        LBList l; lb_createList(&l);
        for (int i = 1; i <= n; i++) lb_insertLast(&l, cases[c][i]);
        printf("Sebelum: "); lb_displayList(l); printf("\n");
        soal06_tambahIndeks(&l);
        printf("Sesudah: "); lb_displayList(l); printf("\n");
        printf("Expected: %s\n", exp[c]);
        lb_freeList(&l);
    }
}

/* ================================================================
 *  SOAL 07 — Dekoder Pesan Berpasangan
 *  Jumlahkan setiap pasangan elemen berurutan. Ganjil → sisa sendiri.
 * ================================================================ */
LBList soal07_pairSum(LBList l) {
    LBList hasil; lb_createList(&hasil);
    LBAddress p = l;
    while (p) {
        if (LB_NEXT(p)) {
            lb_insertLast(&hasil, LB_INFO(p) + LB_INFO(LB_NEXT(p)));
            p = LB_NEXT(LB_NEXT(p));
        } else {
            lb_insertLast(&hasil, LB_INFO(p));
            p = LB_NEXT(p);
        }
    }
    return hasil;
}
void demo07() {
    printSep("SOAL 07 — Dekoder Pesan Berpasangan (jumlah pasangan)");
    int cases[][7] = {{6, 1,2,3,4,5,6},{5, 1,2,3,4,5},{2, 10,20}};
    const char *exp[] = {"[3,7,11]","[3,7,5]","[30]"};
    for (int c = 0; c < 3; c++) {
        printCase(c+1);
        int n = cases[c][0];
        LBList l; lb_createList(&l);
        for (int i = 1; i <= n; i++) lb_insertLast(&l, cases[c][i]);
        printf("Input  : "); lb_displayList(l); printf("\n");
        LBList h = soal07_pairSum(l);
        printf("Output : "); lb_displayList(h); printf("\n");
        printf("Expected: %s\n", exp[c]);
        lb_freeList(&l); lb_freeList(&h);
    }
}

/* ================================================================
 *  SOAL 08 — Jembatan Penghubung Dua Desa
 *  Interleave dua list. Sisa list yang lebih panjang dilampirkan.
 * ================================================================ */
LBList soal08_interleave(LBList a, LBList b) {
    LBList hasil; lb_createList(&hasil);
    LBAddress p = a, q = b;
    while (p && q) {
        lb_insertLast(&hasil, LB_INFO(p)); p = LB_NEXT(p);
        lb_insertLast(&hasil, LB_INFO(q)); q = LB_NEXT(q);
    }
    while (p) { lb_insertLast(&hasil, LB_INFO(p)); p = LB_NEXT(p); }
    while (q) { lb_insertLast(&hasil, LB_INFO(q)); q = LB_NEXT(q); }
    return hasil;
}
void demo08() {
    printSep("SOAL 08 — Jembatan Penghubung (interleave dua list)");
    /* kasus 1: [1,2,3] + [4,5,6] */
    printCase(1);
    int a1[]={1,2,3}, b1[]={4,5,6};
    LBList la, lb2; lb_createList(&la); lb_createList(&lb2);
    for(int i=0;i<3;i++) lb_insertLast(&la, a1[i]);
    for(int i=0;i<3;i++) lb_insertLast(&lb2, b1[i]);
    printf("A="); lb_displayList(la); printf(" B="); lb_displayList(lb2); printf("\n");
    LBList h1 = soal08_interleave(la, lb2);
    printf("Output : "); lb_displayList(h1); printf("\nExpected: [1,4,2,5,3,6]\n");
    lb_freeList(&la); lb_freeList(&lb2); lb_freeList(&h1);
    /* kasus 2: [1,2] + [3,4,5,6] */
    printCase(2);
    int a2[]={1,2}, b2[]={3,4,5,6};
    lb_createList(&la); lb_createList(&lb2);
    for(int i=0;i<2;i++) lb_insertLast(&la, a2[i]);
    for(int i=0;i<4;i++) lb_insertLast(&lb2, b2[i]);
    printf("A="); lb_displayList(la); printf(" B="); lb_displayList(lb2); printf("\n");
    LBList h2 = soal08_interleave(la, lb2);
    printf("Output : "); lb_displayList(h2); printf("\nExpected: [1,3,2,4,5,6]\n");
    lb_freeList(&la); lb_freeList(&lb2); lb_freeList(&h2);
}

/* ================================================================
 *  SOAL 09 — Sensor Gempa Multi-Stasiun
 *  Q query, tiap query N angka. Cek apakah ada |A[i]-A[i+1]| > K.
 * ================================================================ */
boolean soal09_adaLonjakan(LBList l, int K) {
    LBAddress p = l;
    while (p && LB_NEXT(p)) {
        int selisih = LB_INFO(p) - LB_INFO(LB_NEXT(p));
        if (selisih < 0) selisih = -selisih;
        if (selisih > K) return TRUE;
        p = LB_NEXT(p);
    }
    return FALSE;
}
void demo09() {
    printSep("SOAL 09 — Sensor Gempa Multi-Stasiun (selisih berurutan > K)");
    /* Q=2, K=3 */
    int K = 3;
    int q1[] = {4, 1,2,6,7};
    int q2[] = {3, 1,2,3};
    printCase(1); printf("K=%d\n", K);
    LBList l; lb_createList(&l);
    for(int i=1;i<=q1[0];i++) lb_insertLast(&l, q1[i]);
    printf("List: "); lb_displayList(l); printf("\n");
    printf("Output : %s  (expected BAHAYA)\n", soal09_adaLonjakan(l,K)?"BAHAYA":"AMAN");
    lb_freeList(&l);
    printCase(2);
    lb_createList(&l);
    for(int i=1;i<=q2[0];i++) lb_insertLast(&l, q2[i]);
    printf("List: "); lb_displayList(l); printf("\n");
    printf("Output : %s  (expected AMAN)\n", soal09_adaLonjakan(l,K)?"BAHAYA":"AMAN");
    lb_freeList(&l);
}

/* ================================================================
 *  SOAL 10 — Roda Putar Perayaan Desa (Josephus)
 *  N orang melingkar, setiap K langkah satu keluar. Siapa tersisa?
 * ================================================================ */
int soal10_josephus(int N, int K) {
    SCList l; sc_createList(&l);
    for (int i = 1; i <= N; i++) sc_insertLast(&l, i);
    ElType val;
    while (sc_length(l) > 1) {
        /* maju K-1 langkah: geser FIRST */
        for (int i = 0; i < K-1; i++)
            SC_FIRST(l) = SC_NEXT(SC_FIRST(l));
        sc_deleteFirst(&l, &val);
    }
    int hasil = SC_INFO(SC_FIRST(l));
    sc_freeList(&l);
    return hasil;
}
void demo10() {
    printSep("SOAL 10 — Roda Putar Perayaan Desa (Josephus)");
    int cases[][2] = {{5,2},{6,2},{1,1}};
    int exp[] = {3, 5, 1};
    for (int c = 0; c < 3; c++) {
        printCase(c+1);
        int N=cases[c][0], K=cases[c][1];
        int hasil = soal10_josephus(N, K);
        printf("N=%d K=%d  Output: %d  (expected %d) %s\n",
               N, K, hasil, exp[c], hasil==exp[c]?"[OK]":"[FAIL]");
    }
}

/* ================================================================
 *  SOAL 11 — Permainan Lompat Katak
 *  Hapus semua elemen genap dalam satu putaran penuh, cetak urutan.
 * ================================================================ */
void soal11_lompat(int N) {
    SCList l; sc_createList(&l);
    for (int i = 1; i <= N; i++) sc_insertLast(&l, i);
    boolean pertama = TRUE;
    /* Ulangi selama masih ada genap */
    boolean adaGenap = TRUE;
    while (adaGenap && !sc_isEmpty(l)) {
        adaGenap = FALSE;
        int n = sc_length(l);
        SCAddress cur = SC_FIRST(l);
        /* Satu putaran penuh */
        for (int i = 0; i < n; i++) {
            SCAddress nxt = SC_NEXT(cur);
            if (SC_INFO(cur) % 2 == 0) {
                adaGenap = TRUE;
                if (!pertama) printf(" ");
                printf("%d", SC_INFO(cur));
                pertama = FALSE;
                ElType v;
                /* Hapus cur dengan cara update pointer pendahulu */
                if (sc_length(l) == 1) {
                    sc_deleteFirst(&l, &v);
                    break;
                }
                /* Cari pendahulu cur */
                SCAddress prev = SC_FIRST(l);
                while (SC_NEXT(prev) != cur) prev = SC_NEXT(prev);
                SC_NEXT(prev) = SC_NEXT(cur);
                if (cur == SC_FIRST(l)) SC_FIRST(l) = SC_NEXT(cur);
                sc_deallocate(cur);
                cur = nxt;
            } else {
                cur = nxt;
            }
        }
    }
    printf("\n");
    sc_freeList(&l);
}
void demo11() {
    printSep("SOAL 11 — Permainan Lompat Katak (hapus semua genap)");
    int cases[] = {6, 5, 4};
    const char *exp[] = {"2 4 6", "2 4", "2 4"};
    for (int c = 0; c < 3; c++) {
        printCase(c+1);
        printf("N=%d\nOutput : ", cases[c]);
        soal11_lompat(cases[c]);
        printf("Expected: %s\n", exp[c]);
    }
}

/* ================================================================
 *  SOAL 12 — Stasiun Radio Nangor FM
 *  Query SKIP x dan CURRENT pada list sirkuler.
 * ================================================================ */
void soal12_radio(int songs[], int N, char queries[][20], int Q) {
    SCList l; sc_createList(&l);
    for (int i = 0; i < N; i++) sc_insertLast(&l, songs[i]);
    SCAddress cur = SC_FIRST(l);
    for (int i = 0; i < Q; i++) {
        if (strncmp(queries[i], "CURRENT", 7) == 0) {
            printf("%d\n", SC_INFO(cur));
        } else {
            int x; sscanf(queries[i], "SKIP %d", &x);
            for (int j = 0; j < x; j++) cur = SC_NEXT(cur);
        }
    }
    sc_freeList(&l);
}
void demo12() {
    printSep("SOAL 12 — Stasiun Radio Nangor FM (SKIP / CURRENT)");
    printCase(1);
    int s1[] = {10,20,30,40,50};
    char q1[][20] = {"CURRENT","SKIP 2","CURRENT","SKIP 6"};
    printf("Lagu: [10,20,30,40,50]\nOutput:\n");
    soal12_radio(s1, 5, q1, 4);
    printf("Expected:\n10\n30\n");
    printCase(2);
    int s2[] = {7,8,9};
    char q2[][20] = {"SKIP 1","CURRENT"};
    printf("Lagu: [7,8,9]\nOutput:\n");
    soal12_radio(s2, 3, q2, 2);
    printf("Expected:\n8\n");
}

/* ================================================================
 *  SOAL 13 — Virus Bergulir Jaringan Cincin
 *  Isi list 1..N, cari node ke-S, maju T langkah.
 * ================================================================ */
int soal13_virus(int N, int S, int T) {
    SCList l; sc_createList(&l);
    for (int i = 1; i <= N; i++) sc_insertLast(&l, i);
    SCAddress cur = SC_FIRST(l);
    for (int i = 0; i < S-1; i++) cur = SC_NEXT(cur);   /* ke posisi S */
    for (int i = 0; i < T;   i++) cur = SC_NEXT(cur);   /* maju T langkah */
    int hasil = SC_INFO(cur);
    sc_freeList(&l);
    return hasil;
}
void demo13() {
    printSep("SOAL 13 — Virus Bergulir Jaringan Cincin");
    int cases[][3] = {{5,1,3},{6,3,10},{4,4,4}};
    int exp[] = {4, 1, 4};
    for (int c = 0; c < 3; c++) {
        printCase(c+1);
        int N=cases[c][0], S=cases[c][1], T=cases[c][2];
        int h = soal13_virus(N,S,T);
        printf("N=%d S=%d T=%d  Output: %d  (expected %d) %s\n",
               N,S,T,h,exp[c],h==exp[c]?"[OK]":"[FAIL]");
    }
}

/* ================================================================
 *  SOAL 14 — Turnamen Cincin Petarung
 *  Tiap ronde: pasangkan berurutan, hapus yang lebih kecil.
 *  Ulangi sampai tersisa 1.
 * ================================================================ */
int soal14_turnamen(int arr[], int N) {
    SCList l; sc_createList(&l);
    for (int i = 0; i < N; i++) sc_insertLast(&l, arr[i]);
    while (sc_length(l) > 1) {
        int n = sc_length(l);
        int pairs = n / 2;
        SCAddress cur = SC_FIRST(l);
        for (int i = 0; i < pairs; i++) {
            SCAddress a = cur;
            SCAddress b = SC_NEXT(a);
            /* yang kalah (lebih kecil) dihapus */
            SCAddress loser = (SC_INFO(a) < SC_INFO(b)) ? a : b;
            /* cari pendahulu loser */
            SCAddress prev = SC_FIRST(l);
            while (SC_NEXT(prev) != loser) prev = SC_NEXT(prev);
            if (loser == SC_FIRST(l)) SC_FIRST(l) = SC_NEXT(loser);
            SC_NEXT(prev) = SC_NEXT(loser);
            /* tentukan next cur (pemenang lanjut ke node berikutnya */
            SCAddress winner = (loser == a) ? b : a;
            cur = SC_NEXT(winner);
            sc_deallocate(loser);
        }
        SC_FIRST(l) = cur; /* mulai dari sini ronde berikutnya */
    }
    int hasil = SC_INFO(SC_FIRST(l));
    sc_freeList(&l);
    return hasil;
}
void demo14() {
    printSep("SOAL 14 — Turnamen Cincin Petarung");
    int a1[]={3,1,4,2}, a2[]={5,1,3}, a3[]={7,9};
    int *cases[] = {a1, a2, a3};
    int ns[] = {4, 3, 2};
    int exp[] = {4, 5, 9};
    for (int c = 0; c < 3; c++) {
        printCase(c+1);
        printf("Input  : [");
        for (int i=0;i<ns[c];i++) { if(i) printf(","); printf("%d",cases[c][i]); }
        printf("]\n");
        int h = soal14_turnamen(cases[c], ns[c]);
        printf("Output : %d  (expected %d) %s\n", h, exp[c], h==exp[c]?"[OK]":"[FAIL]");
    }
}

/* ================================================================
 *  SOAL 15 — Mesin Waktu Cincin Nangor
 *  Operasi R k (rotasi kanan), S i j (swap nilai), P (print)
 * ================================================================ */
/* Rotasi kanan k: FIRST maju (N-k%N) langkah */
void soal15_rotasiKanan(SCList *l, int k) {
    int n = sc_length(*l);
    if (n == 0) return;
    k = k % n;
    if (k == 0) return;
    int langkah = n - k;
    for (int i = 0; i < langkah; i++) SC_FIRST(*l) = SC_NEXT(SC_FIRST(*l));
}
/* Swap nilai node ke-i dan ke-j (1-indexed) */
void soal15_swap(SCList *l, int i, int j) {
    SCAddress pi = SC_FIRST(*l), pj = SC_FIRST(*l);
    for (int x = 1; x < i; x++) pi = SC_NEXT(pi);
    for (int x = 1; x < j; x++) pj = SC_NEXT(pj);
    ElType tmp = SC_INFO(pi); SC_INFO(pi) = SC_INFO(pj); SC_INFO(pj) = tmp;
}
void demo15() {
    printSep("SOAL 15 — Mesin Waktu Cincin Nangor (R / S / P)");
    printCase(1);
    SCList l; sc_createList(&l);
    int arr[] = {1,2,3,4};
    for (int i=0;i<4;i++) sc_insertLast(&l, arr[i]);
    printf("Awal   : "); sc_displayList(l); printf("\n");
    printf("P      : "); sc_displayList(l); printf("\n");
    soal15_rotasiKanan(&l, 1);
    printf("R 1    : "); sc_displayList(l); printf("\n");
    printf("P      : "); sc_displayList(l); printf("\n");
    soal15_swap(&l, 1, 3);
    printf("S 1 3  : "); sc_displayList(l); printf("\n");
    printf("Expected P output:\n[1,2,3,4]\n[4,1,2,3]\n");
    sc_freeList(&l);

    printCase(2);
    sc_createList(&l);
    int arr2[] = {5,6,7};
    for (int i=0;i<3;i++) sc_insertLast(&l, arr2[i]);
    soal15_swap(&l, 1, 3);
    printf("S 1 3 pada [5,6,7] -> "); sc_displayList(l); printf("\n");
    printf("P      : "); sc_displayList(l); printf("\n");
    printf("Expected: [7,6,5]\n");
    sc_freeList(&l);
}

/* ================================================================
 *  ============================================================
 *  SOAL 16-20 : SOAL DENGAN ADT PENUH
 *  (struct + semua fungsi didefinisikan, soal baru & unik)
 *  ============================================================
 *
 *  SOAL 16 — Pencatatan Skor Turnamen Coding
 *  ADT: List Berkait (struct penuh dengan field tambahan)
 *  Cerita: K peserta terbaik mendapat hadiah. Diberikan N skor,
 *          temukan jumlah K skor terbesar.
 * ================================================================ */

/*
 * ADT Soal 16: List Berkait dengan field 'score' (sama dengan ElType)
 * Sudah tersedia di bagian A (lb_*).
 * Fungsi tambahan: sortDescending, sumFirstK
 *
 * Deskripsi soal:
 * Input : N K, lalu N bilangan bulat (skor peserta).
 * Output: Jumlah K skor terbesar.
 * Contoh masukan:
 *   6 3
 *   5 1 9 3 7 4
 * Contoh keluaran:
 *   21   (9+7+5)
 */

/* Urutkan list secara descending (selection sort pada nilai node) */
void soal16_sortDesc(LBList l) {
    for (LBAddress i = l; i; i = LB_NEXT(i))
        for (LBAddress j = LB_NEXT(i); j; j = LB_NEXT(j))
            if (LB_INFO(j) > LB_INFO(i)) {
                ElType tmp = LB_INFO(i); LB_INFO(i) = LB_INFO(j); LB_INFO(j) = tmp;
            }
}
long long soal16_sumFirstK(LBList l, int K) {
    long long s = 0; int c = 0;
    LBAddress p = l;
    while (p && c < K) { s += LB_INFO(p); c++; p = LB_NEXT(p); }
    return s;
}
void demo16() {
    printSep("SOAL 16 — Pencatatan Skor Turnamen Coding (sum K terbesar)");
    int cases[][8] = {{6,3, 5,1,9,3,7,4},{4,2, 10,20,30,40},{5,5, 1,2,3,4,5}};
    long long exp[] = {21, 70, 15};
    for (int c = 0; c < 3; c++) {
        printCase(c+1);
        int n=cases[c][0], K=cases[c][1];
        LBList l; lb_createList(&l);
        for (int i=2;i<2+n;i++) lb_insertLast(&l, cases[c][i]);
        printf("N=%d K=%d  Skor=", n, K); lb_displayList(l); printf("\n");
        soal16_sortDesc(l);
        printf("Terurut: "); lb_displayList(l); printf("\n");
        long long h = soal16_sumFirstK(l, K);
        printf("Output : %lld  (expected %lld) %s\n", h, exp[c], h==exp[c]?"[OK]":"[FAIL]");
        lb_freeList(&l);
    }
}

/* ================================================================
 *  SOAL 17 — Antrian Rumah Sakit Melingkar
 *  ADT: List Sirkuler dengan struct Pasien {id, prioritas}
 *  Cerita: Pasien masuk antrian melingkar. Setiap giliran, pasien
 *          dengan prioritas tertinggi di-pop dulu. Jika sama,
 *          yang posisinya paling depan (FIRST) yang dilayani.
 *  Input : N pasien (id prioritas per baris), lalu cetak urutan layanan.
 *  Output: ID pasien dalam urutan dilayani.
 *  Contoh masukan:
 *    4
 *    101 2
 *    102 3
 *    103 1
 *    104 3
 *  Contoh keluaran:
 *    102 104 101 103
 * ================================================================ */

typedef struct { int id; int pri; } Pasien;
typedef struct PasienNode *PAddr;
typedef struct PasienNode { Pasien data; PAddr next; } PNode;
typedef struct { PAddr first; } PList;

#define P_INFO(p) ((p)->data)
#define P_NEXT(p) ((p)->next)
#define P_FIRST(l) ((l).first)

PAddr p_alloc(Pasien val) {
    PAddr p = (PAddr)malloc(sizeof(PNode));
    if (p) { P_INFO(p) = val; P_NEXT(p) = NULL; }
    return p;
}
void p_createList(PList *l) { P_FIRST(*l) = NULL; }
boolean p_isEmpty(PList l) { return P_FIRST(l) == NULL; }
int p_length(PList l) {
    if (p_isEmpty(l)) return 0;
    int c=1; PAddr p=P_FIRST(l);
    while (P_NEXT(p)!=P_FIRST(l)) { c++; p=P_NEXT(p); }
    return c;
}
void p_insertLast(PList *l, Pasien val) {
    PAddr p = p_alloc(val);
    if (!p) return;
    if (p_isEmpty(*l)) { P_NEXT(p)=p; P_FIRST(*l)=p; return; }
    PAddr last=P_FIRST(*l);
    while (P_NEXT(last)!=P_FIRST(*l)) last=P_NEXT(last);
    P_NEXT(last)=p; P_NEXT(p)=P_FIRST(*l);
}
/* Hapus node dengan prioritas tertinggi (ties: ambil yang paling depan) */
Pasien p_popHighest(PList *l) {
    /* Cari node dengan prioritas max */
    PAddr best=P_FIRST(*l), cur=P_NEXT(P_FIRST(*l));
    while (cur!=P_FIRST(*l)) {
        if (P_INFO(cur).pri > P_INFO(best).pri) best=cur;
        cur=P_NEXT(cur);
    }
    Pasien hasil = P_INFO(best);
    /* Hapus best */
    if (p_length(*l)==1) { free(best); P_FIRST(*l)=NULL; return hasil; }
    PAddr prev=P_FIRST(*l);
    while (P_NEXT(prev)!=best) prev=P_NEXT(prev);
    P_NEXT(prev)=P_NEXT(best);
    if (best==P_FIRST(*l)) P_FIRST(*l)=P_NEXT(best);
    P_NEXT(best)=NULL; free(best);
    return hasil;
}
void demo17() {
    printSep("SOAL 17 — Antrian Rumah Sakit Melingkar (struct Pasien)");
    printCase(1);
    Pasien arr[] = {{101,2},{102,3},{103,1},{104,3}};
    PList l; p_createList(&l);
    for (int i=0;i<4;i++) p_insertLast(&l, arr[i]);
    printf("Pasien masuk: 101(pri=2), 102(pri=3), 103(pri=1), 104(pri=3)\n");
    printf("Urutan layanan: ");
    boolean first=TRUE;
    while (!p_isEmpty(l)) {
        Pasien p2 = p_popHighest(&l);
        if (!first) printf(" ");
        printf("%d", p2.id);
        first=FALSE;
    }
    printf("\nExpected: 102 104 101 103\n");
}

/* ================================================================
 *  SOAL 18 — Rangkaian Lampu Hias (Run-Length Encoding)
 *  ADT: List Berkait dengan struct RunNode {nilai, count}
 *  Cerita: N lampu berurutan, tiap lampu punya warna (integer).
 *          Kompres dengan RLE: [1,1,2,2,2,3] -> [(1,2),(2,3),(3,1)]
 *          Cetak: "nilai×count" dipisah spasi.
 *  Input : N, lalu N bilangan
 *  Output: RLE string
 *  Contoh masukan:
 *    6
 *    1 1 2 2 2 3
 *  Contoh keluaran:
 *    1x2 2x3 3x1
 * ================================================================ */

typedef struct { int val; int cnt; } RunEl;
typedef struct RLENode *RLEAddr;
typedef struct RLENode { RunEl data; RLEAddr next; } RLENode;
typedef RLEAddr RLEList;

#define RLE_INFO(p) ((p)->data)
#define RLE_NEXT(p) ((p)->next)

RLEAddr rle_alloc(RunEl e) {
    RLEAddr p=(RLEAddr)malloc(sizeof(RLENode));
    if(p){RLE_INFO(p)=e;RLE_NEXT(p)=NULL;}
    return p;
}
void rle_insertLast(RLEList *l, RunEl e) {
    RLEAddr p=rle_alloc(e);
    if(!p) return;
    if(!*l){*l=p;return;}
    RLEAddr q=*l; while(RLE_NEXT(q)) q=RLE_NEXT(q);
    RLE_NEXT(q)=p;
}
void rle_freeList(RLEList *l) {
    while(*l){RLEAddr t=*l;*l=RLE_NEXT(t);free(t);}
}

RLEList soal18_encode(LBList src) {
    RLEList rle=NULL;
    LBAddress p=src;
    while(p){
        int v=LB_INFO(p), cnt=1;
        while(LB_NEXT(p) && LB_INFO(LB_NEXT(p))==v){cnt++;p=LB_NEXT(p);}
        RunEl e={v,cnt}; rle_insertLast(&rle,e);
        p=LB_NEXT(p);
    }
    return rle;
}
void soal18_printRLE(RLEList rle) {
    boolean first=TRUE;
    RLEAddr p=rle;
    while(p){
        if(!first) printf(" ");
        printf("%dx%d",RLE_INFO(p).val,RLE_INFO(p).cnt);
        first=FALSE; p=RLE_NEXT(p);
    }
    printf("\n");
}
void demo18() {
    printSep("SOAL 18 — Rangkaian Lampu Hias (Run-Length Encoding)");
    int cases[][8]={{6, 1,1,2,2,2,3},{4, 5,5,5,5},{5, 1,2,3,4,5}};
    const char*exp[]={"1x2 2x3 3x1","5x4","1x1 2x1 3x1 4x1 5x1"};
    for(int c=0;c<3;c++){
        printCase(c+1);
        int n=cases[c][0];
        LBList l; lb_createList(&l);
        for(int i=1;i<=n;i++) lb_insertLast(&l,cases[c][i]);
        printf("Input  : "); lb_displayList(l); printf("\n");
        RLEList rle=soal18_encode(l);
        printf("Output : "); soal18_printRLE(rle);
        printf("Expected: %s\n",exp[c]);
        lb_freeList(&l); rle_freeList(&rle);
    }
}

/* ================================================================
 *  SOAL 19 — Misi Penjelajah Luar Angkasa
 *  ADT: List Sirkuler dengan struct Planet {nama[20], jarak}
 *  Cerita: N planet melingkar. Pisahkan planet ber-jarak genap ke
 *          list baru, sisakan yang ganjil. Cetak kedua list.
 *  Input : N, lalu N pasang "nama jarak"
 *  Output: Dua baris — list jarak genap, list jarak ganjil
 *  Contoh masukan:
 *    5
 *    Mars 4
 *    Venus 3
 *    Jupiter 8
 *    Saturn 5
 *    Neptune 2
 *  Contoh keluaran:
 *    Genap : [Mars(4),Jupiter(8),Neptune(2)]
 *    Ganjil: [Venus(3),Saturn(5)]
 * ================================================================ */

typedef struct { char nama[20]; int jarak; } Planet;
typedef struct PlanetNode *PLAddr;
typedef struct PlanetNode { Planet data; PLAddr next; } PLNode;

/* Menggunakan list berkait biasa (bukan sirkuler) untuk kemudahan cetak */
#define PL_INFO(p) ((p)->data)
#define PL_NEXT(p) ((p)->next)
typedef PLAddr PLList;

PLAddr pl_alloc(Planet e){
    PLAddr p=(PLAddr)malloc(sizeof(PLNode));
    if(p){PL_INFO(p)=e;PL_NEXT(p)=NULL;}
    return p;
}
void pl_insertLast(PLList *l, Planet e){
    PLAddr p=pl_alloc(e);
    if(!p) return;
    if(!*l){*l=p;return;}
    PLAddr q=*l;while(PL_NEXT(q))q=PL_NEXT(q);
    PL_NEXT(q)=p;
}
void pl_display(PLList l){
    if(!l){printf("[]");return;}
    printf("[%s(%d)",PL_INFO(l).nama,PL_INFO(l).jarak);
    PLAddr p=PL_NEXT(l);
    while(p){printf(",%s(%d)",PL_INFO(p).nama,PL_INFO(p).jarak);p=PL_NEXT(p);}
    printf("]");
}
void pl_free(PLList *l){while(*l){PLAddr t=*l;*l=PL_NEXT(t);free(t);}}

void demo19() {
    printSep("SOAL 19 — Misi Penjelajah Luar Angkasa (split genap/ganjil)");
    Planet planets[] = {{"Mars",4},{"Venus",3},{"Jupiter",8},{"Saturn",5},{"Neptune",2}};
    int N=5;
    PLList genap=NULL, ganjil=NULL;
    for(int i=0;i<N;i++){
        if(planets[i].jarak%2==0) pl_insertLast(&genap,planets[i]);
        else                       pl_insertLast(&ganjil,planets[i]);
    }
    printf("Genap : "); pl_display(genap); printf("\n");
    printf("Ganjil: "); pl_display(ganjil); printf("\n");
    printf("Expected:\nGenap : [Mars(4),Jupiter(8),Neptune(2)]\nGanjil: [Venus(3),Saturn(5)]\n");
    pl_free(&genap); pl_free(&ganjil);
}

/* ================================================================
 *  SOAL 20 — Kriptografi Nangor (XOR Shift Cipher)
 *  ADT: List Berkait dengan struct CipherNode {ch (char sebagai int), idx}
 *  Cerita: Pesan N karakter dienkripsi: setiap karakter di-XOR dengan
 *          (kunci K + indeks). Lalu list dibalik (reverse in-place).
 *          Cetak hasil enkripsi sebagai angka desimal tiap elemen.
 *  Input : K, N, lalu N bilangan bulat (kode ASCII karakter)
 *  Output: List hasil enkripsi setelah di-reverse, format [e1,e2,...,en]
 *  Contoh masukan:
 *    5 4
 *    65 66 67 68
 *  Contoh keluaran:
 *    [77,75,73,71]   (XOR dulu lalu reverse)
 *
 *  Penjelasan: idx=0: 65^(5+0)=65^5=68, idx=1: 66^6=68, idx=2: 67^7=68...
 *  Tunggu, contoh lebih menarik:
 *    K=3, N=4, input: 10 20 30 40
 *    idx0: 10^3=9, idx1: 20^4=16, idx2: 30^5=27, idx3: 40^6=46
 *    reverse: [46,27,16,9]
 * ================================================================ */

typedef struct { int ch; int idx; } CipherEl;
typedef struct CNode *CAddr;
typedef struct CNode { CipherEl data; CAddr next; } CNode;
typedef CAddr CList;
#define C_INFO(p) ((p)->data)
#define C_NEXT(p) ((p)->next)

CAddr c_alloc(CipherEl e){
    CAddr p=(CAddr)malloc(sizeof(CNode));
    if(p){C_INFO(p)=e;C_NEXT(p)=NULL;}
    return p;
}
void c_insertLast(CList *l, CipherEl e){
    CAddr p=c_alloc(e);
    if(!p) return;
    if(!*l){*l=p;return;}
    CAddr q=*l;while(C_NEXT(q))q=C_NEXT(q);
    C_NEXT(q)=p;
}
/* Reverse in-place */
void c_reverse(CList *l){
    CAddr prev=NULL,cur=*l,nxt;
    while(cur){nxt=C_NEXT(cur);C_NEXT(cur)=prev;prev=cur;cur=nxt;}
    *l=prev;
}
void c_display(CList l){
    if(!l){printf("[]");return;}
    printf("[%d",C_INFO(l).ch);
    CAddr p=C_NEXT(l);
    while(p){printf(",%d",C_INFO(p).ch);p=C_NEXT(p);}
    printf("]");
}
void c_free(CList *l){while(*l){CAddr t=*l;*l=C_NEXT(t);free(t);}}

void soal20_enkripsi(int K, int arr[], int N) {
    CList l=NULL;
    for(int i=0;i<N;i++){
        CipherEl e={arr[i]^(K+i), i};
        c_insertLast(&l,e);
    }
    c_reverse(&l);
    c_display(l); printf("\n");
    c_free(&l);
}
void demo20() {
    printSep("SOAL 20 — Kriptografi Nangor (XOR Shift + Reverse)");
    printCase(1);
    int a1[]={10,20,30,40};
    printf("K=3, N=4, Input=[10,20,30,40]\n");
    int x0=(10^3),x1=(20^4),x2=(30^5),x3=(40^6);
    printf("XOR per indeks: 10^3=%d, 20^4=%d, 30^5=%d, 40^6=%d\n", x0,x1,x2,x3);
    printf("Output (setelah reverse): ");
    soal20_enkripsi(3, a1, 4);
    int e0=(10^3),e1=(20^4),e2=(30^5),e3=(40^6);
    printf("Expected: [%d,%d,%d,%d]\n", e3, e2, e1, e0);

    printCase(2);
    int a2[]={65,66,67,68};
    printf("K=5, N=4, Input=[65,66,67,68] (ASCII A,B,C,D)\n");
    printf("XOR per indeks: 65^5=%d, 66^6=%d, 67^7=%d, 68^8=%d\n",
           65^5,66^6,67^7,68^8);
    printf("Output (setelah reverse): ");
    soal20_enkripsi(5, a2, 4);
    printf("Expected: [%d,%d,%d,%d]\n", 68^8, 67^7, 66^6, 65^5);
}

/* ================================================================
 *  MAIN
 * ================================================================ */
int main() {
    printf("================================================================\n");
    printf("  PEMBAHASAN 20 SOAL LINKED LIST — PRAKTIKUM ALPRO ITB\n");
    printf("  Soal  1-15 : competitive programming (listberkait & sirkuler)\n");
    printf("  Soal 16-20 : ADT penuh dengan struct tambahan\n");
    printf("================================================================\n");

    /* --- Soal 1-9 : listberkait --- */
    demo01();
    demo02();
    demo03();
    demo04();
    demo05();
    demo06();
    demo07();
    demo08();
    demo09();

    /* --- Soal 10-15 : listsirkuler --- */
    demo10();
    demo11();
    demo12();
    demo13();
    demo14();
    demo15();

    /* --- Soal 16-20 : ADT penuh --- */
    demo16();
    demo17();
    demo18();
    demo19();
    demo20();

    printf("\n================================================================\n");
    printf("  Selesai. Cari [FAIL] jika ada output yang tidak sesuai.\n");
    printf("================================================================\n");
    return 0;
}