/* File: stackqueue.h */
/* Definisi ADT Queue dan Stack berbasis Linked List */

#ifndef STACKQUEUE_H
#define STACKQUEUE_H

#include "boolean.h"
#include "listberkait.h"

/* ============================================================== */
/* ======================== ADT QUEUE =========================== */
/* ============================================================== */

typedef List Queue; // Perhatikan bahwa Queue dan Stack di sini adalah abstraksi dari List

void CreateQueue(Queue *q);
/* I.S. sembarang */
/* F.S. Sebuah q kosong terbentuk */

boolean isEmptyQueue(Queue q);
/* Mengirim true jika q kosong */

int lengthQueue(Queue q);
/* Mengirimkan banyaknya elemen dalam q */

void enqueue(Queue *q, ElType val);
/* I.S. q mungkin kosong */
/* F.S. val ditambahkan sebagai elemen paling belakang q (FIFO) */

void dequeue(Queue *q, ElType *val);
/* I.S. q tidak kosong (dijamin) */
/* F.S. val berisi elemen paling depan dari q, elemen tsb dihapus */

void displayQueue(Queue q);
/* I.S. q mungkin kosong */
/* F.S. Menampilkan antrian dengan format list linier [e1,e2,...] */

/* ============================================================== */
/* ======================== ADT STACK =========================== */
/* ============================================================== */

typedef List Stack;

void CreateStack(Stack *s);
/* I.S. sembarang */
/* F.S. Sebuah s kosong terbentuk */

boolean isEmptyStack(Stack s);
/* Mengirim true jika s kosong */

int lengthStack(Stack s);
/* Mengirimkan banyaknya elemen dalam s */

void push(Stack *s, ElType val);
/* I.S. s mungkin kosong */
/* F.S. val ditambahkan sebagai elemen paling atas/depan s (LIFO) */

void pop(Stack *s, ElType *val);
/* I.S. s tidak kosong (dijamin) */
/* F.S. val berisi elemen paling atas/depan s, elemen tsb dihapus */

void displayStack(Stack s);
/* I.S. s mungkin kosong */
/* F.S. Menampilkan isi stack dari puncak (atas) ke dasar (bawah) 
        dengan format list linier [e1,e2,...] */

#endif