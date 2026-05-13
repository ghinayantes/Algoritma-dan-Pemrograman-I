#include <stdio.h>
#include <string.h>

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

int isEmpty(Stack s) {
    return IDX_TOP(s) == IDX_UNDEF;
}

void push(Stack *s, ElType val) {
    IDX_TOP(*s)++;
    TOP(*s) = val;
}

void pop(Stack *s, ElType *val) {
    *val = TOP(*s);
    IDX_TOP(*s)--;
} */

int isMatch(char buka, char tutup) {
    if (buka == '(' && tutup == ')') return 1;
    if (buka == '[' && tutup == ']') return 1;
    if (buka == '{' && tutup == '}') return 1;
    return 0;
}

int main() {
    char input[CAPACITY + 1];
    Stack s;
    CreateStack(&s);

    if (scanf("%s", input) != 1) return 0;

    int valid = 1;
    int count = 0;
    int i = 0;

    while(input[i] != '\0' && valid) {
        char current = input[i];

        if (current == '(' || current == '[' || current == '{') {
            push(&s, current);
        } 
        else {
            if (isEmpty(s)) {
                valid = 0;
            } 
            else {
                char topVal;
                pop(&s, &topVal);
                if (isMatch(topVal, current)) {
                    count++;
                } else {
                    valid = 0;
                }
            }
        }
        i++;
    }

    if (!isEmpty(s)) valid = 0;

    if (valid) {
        printf("Valid\n%d\n", count);
    } else {
        printf("Invalid\n%d\n", count);
    }

    return 0;
}