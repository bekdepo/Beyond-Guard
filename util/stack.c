#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

// TODO allow stack size to be set and not just hard coded
void stackInit(Stack *S){
    S->size = 0;
    S->data = malloc(sizeof(*S) * DEFAULT_STACK_VALUE);
}

void *stackTop(Stack *S){
    if(S->size == 0){
        fprintf(stderr, "Error: stack empty\n");
        return "";
    }
    return S->data[S->size-1];
}

void stackPush(Stack *S, void *word){
    if(S->size < DEFAULT_STACK_VALUE){
        S->data[S->size++] = word;
    }
    else{
        printf("Stack is full, resizing stack size...\n");
        S->data = realloc(S, S->size * 2 * sizeof(*S));
    }
}

void stackPop(Stack *S){
    if(S->size == 0){
        fprintf(stderr, "Error: stack empty\n");
    }
    else{
         S->size--;
    }
}

int stackIsEmpty(Stack *S){
    if(S->size == 0){
        return 1;
    }
    return 0;
}

void stackDestroy(Stack *S){
    free(S->data);
}
