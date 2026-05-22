#include <stdio.h>
#include "listberkait.h"
#include "listberkait.c"
#include "boolean.h"

// hitung brp yg genap
int countEven(List l) {
    int N = length(l);
    int idx = 0;
    int count = 0;
    while(idx < N) {
        if(getElmt(l, idx) % 2 == 0) count++;
        idx++;
    }
    return count;
}

// cari max
ElType maxList(List l) {
    int idx = 0, idxMax = 0;
    Address p = l;
    ElType max = INFO(l);
    while(p != NULL) {
        if(max < INFO(p)) {
            max = INFO(p);
            idxMax = idx;
        }
        p = NEXT(p);
        idx++;
    }
    return getElmt(l, idxMax); // sengaja ribet buat sekalian nampung spek lain
}

// buat list absolut
void absAll(List *l) {
    Address p = *l;
    while(p != NULL) {
        ElType temp = INFO(p);
        if(temp < 0) temp *= (-1);
        INFO(p) = temp;
        p = NEXT(p);
    }
}

// tukar 2 2
void swapPairs(List *l) {
    Address p = *l;
    while (p != NULL && NEXT(p) != NULL) {
        ElType tmp = INFO(p);
        INFO(p) = INFO(NEXT(p));
        INFO(NEXT(p)) = tmp;
        p = NEXT(NEXT(p));
    }
}

// gabungkan 2 list tanpa membuat list baru, lalu urutkan
List mergeSorted(List l1, List l2) {
    Node dummy;
    Address tail = &dummy;
    NEXT(tail) = NULL;
 
    Address p = l1, q = l2;
    while (p != NULL && q != NULL) {
        if (INFO(p) <= INFO(q)) {
            NEXT(tail) = p; tail = p; p = NEXT(p);
        } else {
            NEXT(tail) = q; tail = q; q = NEXT(q);
        }
    }
    NEXT(tail) = (p != NULL) ? p : q;
    return NEXT(&dummy);
}

// cek list palindrom
boolean isPalindrome(List l) {
    int n = length(l);
    if (n <= 1) return true;
 
    /* Salin elemen ke array sementara */
    int arr[n];
    Address p = l;
    for (int i = 0; i < n; i++) { arr[i] = INFO(p); p = NEXT(p); }
 
    for (int i = 0; i < n / 2; i++)
        if (arr[i] != arr[n - 1 - i]) return false;
    return true;
}

// hapus elemen dari list yg terurut
void removeDuplicates(List *l) {
    Address p = *l;
    while (p != NULL && NEXT(p) != NULL) {
        if (INFO(p) == INFO(NEXT(p))) {
            Address dup = NEXT(p);
            NEXT(p) = NEXT(dup);
            free(dup);
        } else {
            p = NEXT(p);
        }
    }
}

// fungsi yang merotasi linked list ke kiri sebanyak k posisi secara in-place.
void rotateLeft(List *l, int k) {
    int n = length(*l);
    if (n <= 1) return;
    k = k % n;
    if (k == 0) return;
 
    /* Cari node ke-(k-1): node terakhir dari bagian pertama */
    Address p = *l;
    for (int i = 0; i < k - 1; i++) p = NEXT(p);
 
    /* p = node ke-(k-1), NEXT(p) = kepala baru */
    Address newHead = NEXT(p);
 
    /* Cari ekor list, sambungkan ke kepala lama */
    Address tail = newHead;
    while (NEXT(tail) != NULL) tail = NEXT(tail);
    NEXT(tail) = *l;
    NEXT(p) = NULL;
    *l = newHead;
}

// fungsi yang mendeteksi apakah sebuah linked list memiliki siklus (cycle) pada pointer-nya
boolean hasCycle(List l) {
    Address slow = l, fast = l;
    while (fast != NULL && NEXT(fast) != NULL) {
        slow = NEXT(slow);
        fast = NEXT(NEXT(fast));
        if (slow == fast) return true;
    }
    return false;
}

static Address reverseAddr(Address head) {
    Address prev = NULL, cur = head, nxt;
    while (cur != NULL) {
        nxt = NEXT(cur);
        NEXT(cur) = prev;
        prev = cur;
        cur = nxt;
    }
    return prev;
}

// fungsi yang menyusun ulang linked list menjadi pola zigzag: L[0]→L[n-1]→L[1]→L[n-2]→… secara in-place tanpa alokasi node baru.
void zigzagList(List *l) {
    int n = length(*l);
    if (n <= 2) return;
 
    /* Langkah 1: cari tengah dengan slow-fast pointer */
    Address slow = *l, fast = *l;
    while (NEXT(fast) != NULL && NEXT(NEXT(fast)) != NULL) {
        slow = NEXT(slow);
        fast = NEXT(NEXT(fast));
    }
 
    /* Langkah 2: potong dan reverse separuh kedua */
    Address secondHalf = NEXT(slow);
    NEXT(slow) = NULL;
    secondHalf = reverseAddr(secondHalf);
 
    /* Langkah 3: merge dua separuh bergantian */
    Address p1 = *l, p2 = secondHalf;
    while (p2 != NULL) {
        Address n1 = NEXT(p1);
        Address n2 = NEXT(p2);
        NEXT(p1) = p2;
        NEXT(p2) = n1;
        p1 = n1;
        p2 = n2;
    }
}

// mengunjungi elemen mundur
void printReverse(Address p) {
    if (p == NULL) return;
    printReverse(NEXT(p)); // Maju terus sampai ujung
    printf("%d ", INFO(p)); // Print saat "mundur" dari call stack
}

