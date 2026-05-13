#include <stdio.h>
#include "boolean.h"

#define IDX_UNDEF -1
#define CAPACITY 1000

typedef int ElType;

typedef struct {
    ElType buffer[CAPACITY];
    int idxHead;
    int idxTail;
} Queue;

#define IDX_HEAD(q) (q).idxHead
#define IDX_TAIL(q) (q).idxTail
#define     HEAD(q) (q).buffer[(q).idxHead]
#define     TAIL(q) (q).buffer[(q).idxTail]

/* void CreateQueue(Queue *q) {
    IDX_HEAD(*q) = IDX_UNDEF;
    IDX_TAIL(*q) = IDX_UNDEF;
}

boolean isEmpty(Queue q) {
    return (IDX_HEAD(q) == IDX_UNDEF) && (IDX_TAIL(q) == IDX_UNDEF);
}

boolean isFull(Queue q) {
    return IDX_TAIL(q) == CAPACITY - 1;
}

int length(Queue q) {
    if(isEmpty(q)) return 0;
    return IDX_TAIL(q) - IDX_HEAD(q) + 1;
}

void enqueue(Queue *q, ElType val) {
    if(isEmpty(*q)) {
        IDX_HEAD(*q) = 0;
        IDX_TAIL(*q) = 0;
        TAIL(*q) = val;
    }
    else {
        IDX_TAIL(*q)++;
        TAIL(*q) = val;
    }
}

void dequeue(Queue *q, ElType *val) {
    *val = HEAD(*q);
    IDX_HEAD(*q)++;
    if(IDX_HEAD(*q) > IDX_TAIL(*q)) {
        IDX_HEAD(*q) = IDX_UNDEF;
        IDX_TAIL(*q) = IDX_UNDEF;
    }
} */

int main() {
    int n, i, j;
    Queue q, subordinates[201];
    
    scanf("%d", &n);
    
    int M, id;

    for (i = 1; i <= n; i++) {
        CreateQueue(&subordinates[i]);

        scanf("%d", &M); 
        for(j = 0; j < M; j++) {
            scanf("%d", &id);
            enqueue(&subordinates[i], id); 
        }
    }

    CreateQueue(&q);
    enqueue(&q, 1);

    boolean first = 1;
    while (!isEmpty(q)) {
        ElType current;
        dequeue(&q, &current); 

        if(!first) printf(" ");
    
        printf("%d", current);
        first = 0;

        while(!isEmpty(subordinates[current])) {
            int id;
            dequeue(&subordinates[current], &id);
            enqueue(&q, id);
        }
    }

    return 0;
}
