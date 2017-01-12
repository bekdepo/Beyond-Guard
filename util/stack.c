#include "stack.h"

#include <stdio.h>

// TODO allow stack size to be set and not just hard coded
void stackInit(Stack *S){
    S->size = 0;
}

void *stackTop(Stack *S){
    if (S->size == 0) {
        fprintf(stderr, "Error: stack empty\n");
        return "";
    }

    return S->data[S->size-1];
}

void stackPush(Stack *S, void *word){
    if (S->size < STACK_MAX){
        S->data[S->size++] = word;
    }
    else{
        fprintf(stderr, "Error: stack full\n");
    }

}

void stackPop(Stack *S){
    if (S->size == 0){
        fprintf(stderr, "Error: stack empty\n");
    }
    else{
         S->size--;
    }
}
