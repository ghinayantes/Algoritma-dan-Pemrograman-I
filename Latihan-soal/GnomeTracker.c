#include <stdio.h>
#include <string.h>
#include "GnomeTracker.h"

/* ********** KONSTRUKTOR ********** */
/**
 * I.S. sembarang
 * F.S. Terbentuk list kosong dengan jumlah elemen efektif 0
 */
void createTracker(GnomeTrack *L) {
    L->nEff= 0;
}

/* ********** SELEKTOR ********** */
/**
 * Mengembalikan banyaknya elemen efektif
 */
int length(GnomeTrack L) {
    return L.nEff;
}

/**
 * Mengembalikan kapasitas maksimum list
 */
int maximumCap() {
    return CAPACITY;
}

/**
 * Prekondisi: L tidak kosong
 * Mengembalikan indeks elemen pertama
 */
IdxType getFirstIdx(GnomeTrack L) {
    if(L.nEff != 0) return 0;
    return IDX_UNDEF;
}

/**
 * Prekondisi: L tidak kosong
 * Mengembalikan indeks elemen terakhir
 */
IdxType getLastIdx(GnomeTrack L) {
    if(L.nEff != 0) return L.nEff - 1;
    return IDX_UNDEF;
}

/**
 * Mengembalikan Gnome pada indeks ke-i
 * Prekondisi: i adalah indeks efektif yang valid
 */
Gnome getElmt(GnomeTrack L, IdxType i) {
    return L.contents[i];
}

/* ********** SETTER ********** */
/**
 * Mengubah elemen pada indeks i menjadi nilai val
 */
void setElmt(GnomeTrack *L, IdxType i, Gnome val) {
    L->contents[i] = val;
}

/**
 * Mengatur nilai jumlah elemen efektif menjadi N
 */
void setLength(GnomeTrack *L, int N) {
    L->nEff = N;
}

/* ********** Validasi INDEKS ********** */
/**
 * Mengembalikan true jika indeks berada dalam rentang kapasitas [0..CAPACITY-1]
 */
boolean isIdxValid(IdxType i) {
    return i >= 0 && i < CAPACITY;
}

/**
 * Mengembalikan true jika indeks adalah indeks efektif [0..nEff-1]
 */
boolean isIdxEff(GnomeTrack L, IdxType i) {
    return i >= 0 && i < L.nEff;
}

/* ********** TEST KOSONG/PENUH ********** */
/**
 * Mengembalikan true jika list kosong
 */
boolean isEmpty(GnomeTrack L) {
    return L.nEff == 0;
}

/**
 * Mengembalikan true jika list penuh
 */
boolean isFull(GnomeTrack L) {
    return L.nEff == CAPACITY;
}

/* ********** Operasi Dasar ********** */
/**
 * Menyisipkan Gnome pada indeks tertentu
 * Semua elemen setelah indeks digeser ke kanan
 */
void insertAt(GnomeTrack *L, Gnome g, IdxType idx) {
    IdxType i; 
    if(isIdxEff(*L, idx)) {
        for(i = length(*L); i > idx; i--) {
            L->contents[i] = L->contents[i-1];
        }
        L->contents[idx] = g;
        L->nEff++;
    }
}

/**
 * Menambahkan Gnome ke posisi pertama dalam list
 * Semua elemen yang ada digeser ke kanan
 */
void insertFirst(GnomeTrack *L, Gnome g) {
    IdxType i;
    if(L->nEff == 0) {
        L->contents[0] = g;
        L->nEff++;
    }
    else {
        for(i = length(*L); i > 0; i--) {
            L->contents[i] = L->contents[i-1];
        }
        L->contents[0] = g;
        L->nEff++;
    }
}

/**
 * Menambahkan Gnome ke posisi terakhir dalam list
 */
void insertLast(GnomeTrack *L, Gnome g) {
    setElmt(L, length(*L), g);
    L->nEff++;
}

/**
 * Menghapus Gnome pada indeks tertentu
 * Semua elemen setelahnya digeser ke kiri
 * Elemen yang dihapus disimpan pada *g
 */
void deleteAt(GnomeTrack *L, IdxType idx, Gnome *g) {
    IdxType i;
    if(isIdxEff(*L, idx)) {
        *g = L->contents[idx];
        for(i = idx; i < length(*L); i++) {
            L->contents[i] = L->contents[i+1];
        }
        L->nEff--;
    }
}

/**
 * Menghapus Gnome pada indeks pertama (0)
 * Semua elemen setelahnya digeser ke kiri
 * Elemen yang dihapus disimpan pada *g
 */
void deleteFirst(GnomeTrack *L, Gnome *g) {
    IdxType i;
    if(isIdxEff(*L, 0)) {
        *g = L->contents[0];
        for(i = 0; i < length(*L)-1; i++) {
            L->contents[i] = L->contents[i+1];
        }
        L->nEff--;
    }
}

/**
 * Menghapus Gnome pada indeks terakhir
 * Elemen terakhir disimpan pada *g
 */
void deleteLast(GnomeTrack *L, Gnome *g) {
    if(L->nEff != 0) {
        *g = L->contents[length(*L)-1];
        L->nEff--;
    }
}

/**
 * Mengembalikan indeks Gnome berdasarkan ID
 * Jika tidak ditemukan, mengembalikan IDX_UNDEF
 */
IdxType indexOf(GnomeTrack L, int id) {
    IdxType i;
    for(i = 0; i < L.nEff; i++) {
        if(L.contents[i].id == id) return i;
    }
    return IDX_UNDEF;
}

/* ********** Utilitas dan Output ********** */
/**
 * Menampilkan seluruh isi list GnomeTrack
 * Format:
 * Gnome Entry-<index>: 
 * ID=xxx 
 * NAME=xxx 
 * HEIGHT=xxx.xx (2 angka di belakang koma)
 * TYPE=xxx 
 * FRIENDLY=Yes/No
 */
/* Setiap tampilan elemen dipisahkan dengan baris kosong */
/* Jika L kosong : Hanya menulis "List kosong" dan diakhiri newline */
void printAllGnome(GnomeTrack L) {
    IdxType i;
    if(L.nEff == 0) printf("List Kosong\n");
    else {
        for(i = 0; i < L.nEff; i++) {
        printf("Gnome Entry-%d:\n", i);
        printf("ID=%d\n", L.contents[i].id);
        printf("NAME=%s\n", L.contents[i].name);
        printf("HEIGHT=%.2f\n", L.contents[i].height);
        printf("TYPE=%s\n", L.contents[i].type);
        printf("FRIENDLY=%s\n", L.contents[i].isFriendly ? "Yes" : "No");
        printf("\n");
        }  
    }
}

/**
 * Menghapus seluruh Gnome yang tidak ramah (isFriendly == false)
 * Setiap Gnome yang dihapus akan dicetak namanya ke layar
 * Format output: "DELETED: <nama_gnome>"
 * I.S. L terdefinisi
 * F.S. Semua Gnome tidak ramah dihapus dari list dan ditampilkan namanya
 */
/* Jika L kosong : Hanya menulis "List kosong" dan diakhiri newline */
void deleteUnfriendly(GnomeTrack *L) {
    IdxType i;
    if(L->nEff == 0) printf("List kosong\n");
    else {
        for(i = 0; i < L->nEff; ) {
            if(!L->contents[i].isFriendly) {
            printf("DELETED: %s\n", L->contents[i].name);
            Gnome tmp;
            deleteAt(L, i, &tmp);
            } 
            else {
                i++;
            }
        }
    }
}
/**
 * Menampilkan hanya Gnome dengan height >= minHeight
 * format penampilan sama seperti printAllGnome
 */
/* Jika L kosong : Hanya menulis "List kosong" dan diakhiri newline */
void filterByHeight(GnomeTrack L, float minHeight) {
    IdxType i;
    if(L.nEff == 0) printf("List kosong\n");
    else {
        for(i = 0; i < L.nEff; i++) {
            if(L.contents[i].height >= minHeight) {
                printf("Gnome Entry-%d:\n", i);
                printf("ID:%d\n", L.contents[i].id);
                printf("NAME=%s\n", L.contents[i].name);
                printf("HEIGHT=%.2f\n", L.contents[i].height);
                printf("TYPE=%s\n", L.contents[i].type);
                printf("FRIENDLY=%s\n", L.contents[i].isFriendly ? "Yes" : "No");
                printf("\n");
            }
        }
    }
}

/**
 * Menampilkan hanya Gnome dengan tipe tertentu
 * format penampilan sama seperti printAllGnome
 */
/* Jika L kosong : Hanya menulis "List kosong" dan diakhiri newline */
void filterByType(GnomeTrack L, char *targetType) {
    IdxType i;
    if(L.nEff == 0) printf("List kosong\n");
    else {
        for(i = 0; i < L.nEff; i++) {
            if(strcmp(L.contents[i].type, targetType) == 0) {
                printf("Gnome Entry-%d:\n", i);
                printf("ID:%d\n", L.contents[i].id);
                printf("NAME=%s\n", L.contents[i].name);
                printf("HEIGHT=%.2f\n", L.contents[i].height);
                printf("TYPE=%s\n", L.contents[i].type);
                printf("FRIENDLY=%s\n", L.contents[i].isFriendly ? "Yes" : "No");
                printf("\n");
            }
        }
    }
}


/* ===== HELPER ===== */
Gnome makeGnome(int id, const char *name, float height, const char *type, boolean isFriendly) {
    Gnome g;
    g.id = id;
    strncpy(g.name, name, 29); g.name[29] = '\0';
    g.height = height;
    strncpy(g.type, type, 19); g.type[19] = '\0';
    g.isFriendly = isFriendly;
    return g;
}
 
void printSeparator(const char *title) {
    printf("\n========================================\n");
    printf(" %s\n", title);
    printf("========================================\n");
}
 
int passed = 0, failed = 0;
 
void check(const char *label, int condition) {
    if (condition) { printf("  [PASS] %s\n", label); passed++; }
    else           { printf("  [FAIL] %s\n", label); failed++; }
}
 
/* ===== MAIN ===== */
int main() {
    GnomeTrack L, emptyL;
    Gnome g;
    IdxType idx;
    int i, lenBefore, friendlyCount, allFriendly;
 
    printf("========================================\n");
    printf("      DRIVER TEST: GnomeTracker\n");
    printf("========================================\n");
 
    /* ---- TEST 1: createTracker ---- */
    printSeparator("TEST 1: createTracker");
    createTracker(&L);
    check("isEmpty = TRUE setelah createTracker", isEmpty(L) == TRUE);
    check("length = 0",                           length(L) == 0);
    check("maximumCap = 100",                     maximumCap() == CAPACITY);
    check("isFull = FALSE",                       isFull(L) == FALSE);
 
    /* ---- TEST 2: insertLast ---- */
    printSeparator("TEST 2: insertLast");
    insertLast(&L, makeGnome(1, "Timmy",   45.5f, "forest",  TRUE));
    insertLast(&L, makeGnome(2, "Grumpy",  38.0f, "leader",  FALSE));
    insertLast(&L, makeGnome(3, "Blinky",  52.3f, "builder", TRUE));
    insertLast(&L, makeGnome(4, "Shadow",  41.0f, "forest",  FALSE));
    insertLast(&L, makeGnome(5, "Sparkle", 60.0f, "leader",  TRUE));
    check("length = 5 setelah 5x insertLast",     length(L) == 5);
    check("isEmpty = FALSE",                      isEmpty(L) == FALSE);
    check("Elemen pertama ID=1",                  getElmt(L, getFirstIdx(L)).id == 1);
    check("Elemen terakhir ID=5",                 getElmt(L, getLastIdx(L)).id == 5);
 
    /* ---- TEST 3: insertFirst ---- */
    printSeparator("TEST 3: insertFirst");
    insertFirst(&L, makeGnome(0, "Elder", 70.0f, "leader", TRUE));
    check("length = 6 setelah insertFirst",       length(L) == 6);
    check("Elemen pertama jadi ID=0",             getElmt(L, 0).id == 0);
    check("Elemen kedua tetap ID=1 (geser benar)",getElmt(L, 1).id == 1);
 
    /* ---- TEST 4: insertAt ---- */
    printSeparator("TEST 4: insertAt (indeks 2)");
    insertAt(&L, makeGnome(99, "MidGnome", 50.0f, "builder", TRUE), 2);
    check("length = 7 setelah insertAt",          length(L) == 7);
    check("Elemen indeks 2 = ID=99",              getElmt(L, 2).id == 99);
    check("Elemen indeks 3 geser = ID=2",         getElmt(L, 3).id == 2);
 
    /* ---- TEST 5: getElmt & setElmt ---- */
    printSeparator("TEST 5: getElmt & setElmt");
    g = getElmt(L, 0);
    check("getElmt(0) ID=0",                      g.id == 0);
    g.height = 88.8f;
    setElmt(&L, 0, g);
    check("setElmt -> getElmt height=88.80",      getElmt(L, 0).height == 88.8f);
 
    /* ---- TEST 6: isIdxValid & isIdxEff ---- */
    printSeparator("TEST 6: isIdxValid & isIdxEff");
    check("isIdxValid(0) = TRUE",                 isIdxValid(0)   == TRUE);
    check("isIdxValid(99) = TRUE",                isIdxValid(99)  == TRUE);
    check("isIdxValid(-1) = FALSE",               isIdxValid(-1)  == FALSE);
    check("isIdxValid(100) = FALSE",              isIdxValid(100) == FALSE);
    check("isIdxEff(0) = TRUE",                   isIdxEff(L, 0) == TRUE);
    check("isIdxEff(length) = FALSE",             isIdxEff(L, length(L)) == FALSE);
 
    /* ---- TEST 7: indexOf ---- */
    printSeparator("TEST 7: indexOf");
    idx = indexOf(L, 3);
    check("indexOf(ID=3) != IDX_UNDEF",           idx != IDX_UNDEF);
    check("Gnome di idx tersebut ID=3",           getElmt(L, idx).id == 3);
    idx = indexOf(L, 999);
    check("indexOf(ID=999) = IDX_UNDEF",          idx == IDX_UNDEF);
 
    /* ---- TEST 8: deleteLast ---- */
    printSeparator("TEST 8: deleteLast");
    lenBefore = length(L);
    deleteLast(&L, &g);
    check("Elemen terhapus adalah ID=5 (Sparkle)", g.id == 5);
    check("length berkurang 1",                    length(L) == lenBefore - 1);
 
    /* ---- TEST 9: deleteFirst ---- */
    printSeparator("TEST 9: deleteFirst");
    lenBefore = length(L);
    deleteFirst(&L, &g);
    check("Elemen terhapus adalah ID=0 (Elder)",  g.id == 0);
    check("length berkurang 1",                   length(L) == lenBefore - 1);
    check("Elemen pertama baru = ID=1",           getElmt(L, 0).id == 1);
 
    /* ---- TEST 10: deleteAt ---- */
    printSeparator("TEST 10: deleteAt (indeks 1)");
    int idAfterIdx1 = getElmt(L, 2).id;
    lenBefore = length(L);
    deleteAt(&L, 1, &g);
    check("length berkurang 1",                   length(L) == lenBefore - 1);
    check("Elemen setelahnya geser ke kiri",      getElmt(L, 1).id == idAfterIdx1);
 
    /* ---- TEST 11: filterByHeight ---- */
    printSeparator("TEST 11: filterByHeight (minHeight=50.0)");
    printf("  [Output]\n");
    filterByHeight(L, 50.0f);
 
    /* ---- TEST 12: filterByType ---- */
    printSeparator("TEST 12: filterByType (\"forest\")");
    printf("  [Output]\n");
    filterByType(L, "forest");
 
    /* ---- TEST 13: printAllGnome ---- */
    printSeparator("TEST 13: printAllGnome (state saat ini)");
    printAllGnome(L);
 
    /* ---- TEST 14: deleteUnfriendly ---- */
    printSeparator("TEST 14: deleteUnfriendly");
    insertLast(&L, makeGnome(10, "Meanie", 44.0f, "forest",  FALSE));
    insertLast(&L, makeGnome(11, "Nasty",  39.0f, "builder", FALSE));
    friendlyCount = 0;
    for(i = 0; i < length(L); i++)
        if(getElmt(L, i).isFriendly) friendlyCount++;
    printf("  Jumlah friendly sebelum: %d\n", friendlyCount);
    printf("  Jumlah unfriendly sebelum: %d\n", length(L) - friendlyCount);
    deleteUnfriendly(&L);
    allFriendly = 1;
    for(i = 0; i < length(L); i++)
        if(!getElmt(L, i).isFriendly) { allFriendly = 0; break; }
    check("Semua sisa elemen isFriendly=TRUE",    allFriendly == 1);
    check("length = jumlah friendly sebelumnya",  length(L) == friendlyCount);
 
    /* ---- TEST 15: isFull ---- */
    printSeparator("TEST 15: isFull");
    createTracker(&L);
    for(i = 0; i < CAPACITY; i++) {
        char nm[10]; sprintf(nm, "G%d", i);
        insertLast(&L, makeGnome(i, nm, 40.0f + i * 0.1f, "forest", TRUE));
    }
    check("isFull = TRUE setelah CAPACITY insert", isFull(L) == TRUE);
    check("length = CAPACITY",                     length(L) == CAPACITY);
 
    /* ---- TEST 16: edge case list kosong ---- */
    printSeparator("TEST 16: Edge case list kosong");
    createTracker(&emptyL);
    printf("  printAllGnome    -> "); printAllGnome(emptyL);
    printf("  filterByHeight   -> "); filterByHeight(emptyL, 10.0f);
    printf("  filterByType     -> "); filterByType(emptyL, "forest");
    printf("  deleteUnfriendly -> "); deleteUnfriendly(&emptyL);
 
    /* ---- HASIL AKHIR ---- */
    printf("\n========================================\n");
    printf("  HASIL: %d PASS | %d FAIL\n", passed, failed);
    printf("========================================\n");
 
    return failed > 0 ? 1 : 0;
}