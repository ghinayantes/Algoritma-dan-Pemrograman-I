/* File : listsirkular.h */
/* contoh ADT list sirkular berkait dengan representasi pointer ganda  */

#include "boolean.h"
#include <stdio.h>
#include <stdlib.h>
#include "listganda.h"

Address newNode(ElType val){
    Address p = (Address) malloc(sizeof(Node));
    if(p != NULL){
        INFO(p) = val;
        NEXT(p) = NULL;
        PREV(p) = NULL;
    }
    return p;
}

/* Definisi List : */
/* List kosong : CURRENT(l) = NULL */
/* CURRENT: Elemen yang ditunjuk saat ini. Karena sirkular, tidak ada elemen pertama ataupun terakhir. */

/* PROTOTYPE */

void createListGanda(ListGanda *l){
    CURRENT(*l) = NULL;
}
/* I.S. sembarang             */
/* F.S. Terbentuk list kosong */

boolean isEmpty(ListGanda l){
    return (CURRENT(l) == NULL);
}
/* Mengirim true jika list kosong */

boolean isOneElement(ListGanda l){
    return (!isEmpty(l) && NEXT(CURRENT(l)) == CURRENT(l));
}
/* Mengirim true jika list terdiri atas 1 elemen saja*/

int length(ListGanda l){
    int count = 0;
    if(isEmpty(l)){
        return 0;
    }
    else{
        Address p = CURRENT(l);
        do {
        count++;
        p = NEXT(p);
        } while (p != CURRENT(l));

        return count;
    }
}
/* Mengirimkan banyaknya elemen list; mengirimkan 0 jika list kosong */

void rotate(ListGanda *l, int k){
    if (!isEmpty(*l)) {
        int len = length(*l);
        k %= len;

        if (k < 0) {
            k += len;
        }

        for (int i = 0; i < k; i++) {
            CURRENT(*l) = NEXT(CURRENT(*l));
        }
    }
}
/* I.S. l terdefinisi, l mungkin kosong
    k mungkin positif, nol, maupun negatif, abs(k) mungkin lebih besar dari length(l) */
/* F.S. CURRENT menunjuk ke elemen ke-k dari CURRENT sebelumnya
    dengan k positif artinya ke arah NEXT dan k negatif artinya ke arah PREV */

void insertAfterCurrent(ListGanda *l, ElType x){
    Address newp = newNode(x);

    if (isEmpty(*l)) {
        CURRENT(*l) = newp;
        NEXT(newp) = newp;
        PREV(newp) = newp;
    } else {
        Address p = CURRENT(*l);
        Address oldnext = NEXT(p);

        NEXT(p) = newp;
        NEXT(newp) = oldnext;

        PREV(newp) = p;
        PREV(oldnext) = newp;

        CURRENT(*l) = newp;
    }
}
/* I.S. l terdefinisi, l mungkin kosong */
/* F.S.
    1. Terbentuk node baru E,
    2. E disisipkan pada NEXT dari CURRENT,
    3. CURRENT menunjuk ke E
 */

void deleteCurrent(ListGanda *l, ElType *x){
    if (isOneElement(*l)) {
        Address p = CURRENT(*l);
        *x = INFO(p);

        free(p);
        CURRENT(*l) = NULL;
    } 
    else {
        Address p = CURRENT(*l);
        Address pnext = NEXT(p);
        Address pprev = PREV(p);

        *x = INFO(p);
        NEXT(pprev) = pnext;
        PREV(pnext) = pprev;

        free(p);
        CURRENT(*l) = pnext;
    }
}
/* I.S. l terdefinisi, l tidak kosong */
/* F.S.
    1. Elemen CURRENT (E) dikeluarkan dari list,
    2. CURRENT menunjuk pada NEXT dari E
    3. x berisi nilai E
    4. E dihapus
 */