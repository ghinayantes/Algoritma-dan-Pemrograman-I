#include <stdio.h>
#include <string.h>
#include "boolean.h"

#define IDX_UNDEF -1
#define CAPACITY 100

typedef char ElType;
typedef struct {
    ElType buffer[CAPACITY];
    int idxTop;
} Stack;

#define IDX_TOP(s) (s).idxTop
#define TOP(s) (s).buffer[(s).idxTop]

/* void CreateStack(Stack *s) {
    IDX_TOP(*s) = IDX_UNDEF;
}

boolean isEmpty(Stack s) {
    return IDX_TOP(s) == IDX_UNDEF;
}

boolean isFull(Stack s) {
    return IDX_TOP(s) == CAPACITY - 1;
}

int length(Stack s) {
    return IDX_TOP(s) + 1;
}

void push(Stack *s, ElType val) {
    IDX_TOP(*s)++;
    TOP(*s) = val;
}

void pop(Stack *s, ElType *val) {
    *val = TOP(*s);
    IDX_TOP(*s)--;
} */

int ubah(char c) {
    return c - '0';
}

int main() {
    char input[CAPACITY + 1];
    Stack s;
    CreateStack(&s);

    if(scanf("%s", input) != 1) return 0;

    int i = 0;

    while (input[i] != '\0') {
        ElType current = input[i];

        if (current >= '0' && current <= '9') {
            push(&s, ubah(current));
        } 
        else {
            ElType val1, val2, hasil;
            
            pop(&s, &val2); 
            pop(&s, &val1); 

            if(current == '+') hasil = val1 + val2;
            else if(current == '-') hasil = val1 - val2;
            else if(current == '*') hasil = val1 * val2;
            else if(current == '/') hasil = val1 / val2;
            else if(current == '%') hasil = val1 % val2;

            push(&s, hasil);
        }
        i++;
    }

    ElType hasilAkhir;
    pop(&s, &hasilAkhir);
    printf("%d\n", hasilAkhir);

    return 0;
}
