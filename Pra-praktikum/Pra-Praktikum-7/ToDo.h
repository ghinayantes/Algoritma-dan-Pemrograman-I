#ifndef TODO_H
#define TODO_H

#include "boolean.h"
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    boolean status; /* false -> Belum selesai dikerjakan, true -> Sudah selesai dikerjakan */
} Task;

typedef struct {
    Task *tasksList;
    int nEff;
    int capacity;
} ToDoList;
/* Indeks yang digunakan [0..capacity-1] */
/* Jika T adalah ToDoList, cara akses:
   T.nEff         untuk mengetahui banyaknya task
   T.tasksList    untuk mengakses seluruh nilai elemen list
   T.tasksList[i] untuk mengakses task ke-i */
/* Definisi :
   list kosong: T.nEff = 0
   Elemen pertama : T.tasksList[0]
   Elemen terakhir yang terdefinisi: T.tasksList[T.nEff-1] */


void createList(ToDoList *T, int capacity);
/* I.S. T sembarang, capacity > 0 */
/* F.S. Terbentuk to-do list T kosong dengan kapasitas capacity */

void dealocateList(ToDoList *T);
/* I.S. T terdefinisi */
/* F.S. tasksList T dikembalikan ke sistem, T.capacity=0, T.nEff=0 */

int getNumOfTasks(ToDoList T);
/* Mengembalikan banyaknya task efektif dalam to-do list */
/* Mengembalikan 0 jika list kosong */

int getNumOfCompletedTasks(ToDoList T);
/* Mengembalikan banyaknya task yang sudah selesai dalam to-do list */
/* Mengembalikan 0 jika list kosong */

boolean isEmpty(ToDoList T);
/* Mengirimkan true jika list T kosong, false jika tidak */

boolean isFull(ToDoList T);
/* Mengirimkan true jika list T penuh, false jika tidak */

void addNewTask(ToDoList *T, char *taskName);
/* Proses: Menambahkan task baru dengan nama salinan dari taskName pada akhir list */
/* I.S. List T tidak penuh, taskName terdefinisi */
/* F.S. Task baru dengan status belum selesai ditambahkan sebagai elemen terakhir T */

void removeTask(ToDoList *T, int idx);
/* Proses: Menghapus task pada indeks idx, elemen setelahnya digeser ke kiri */
/* I.S. List T tidak kosong, 0 <= idx <= T.nEff-1 */
/* F.S. Task pada indeks idx terhapus, T.nEff berkurang satu */

void markTaskAsCompleted(ToDoList *T, int idx);
/* Proses: Mengubah status task pada indeks idx menjadi sudah selesai */
/* I.S. List T tidak kosong, 0 <= idx <= T.nEff-1 */
/* F.S. T.tasksList[idx].status = true */

int getProgress(ToDoList T);
/* Mengembalikan persentase task yang sudah selesai dari keseluruhan task */
/* Persentase dalam bentuk integer, angka di belakang koma di-truncate */
/* Prekondisi: T.nEff > 0 */

void expandList(ToDoList *T, int num);
/* Proses: Menambahkan capacity T sebanyak num */
/* I.S. T sudah terdefinisi, num > 0 */
/* F.S. Ukuran capacity bertambah sebanyak num */

void shrinkList(ToDoList *T, int num);
/* Proses: Mengurangi capacity T sebanyak num */
/* I.S. T sudah terdefinisi, capacity > num, nEff < capacity - num */
/* F.S. Ukuran capacity berkurang sebanyak num */

#endif