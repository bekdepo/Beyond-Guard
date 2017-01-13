#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#define DEFAULT_STACK_VALUE 100000

struct Stack {
    void     **data;
    int     size;
};
typedef struct Stack Stack;

// inititalizes stack with default size
void stackInit(Stack *S);

//  gets the top of the stack
void *stackTop(Stack *S);

// pushes onto the top of the stack
// if stack is full the stack size is resized to double the capacity
void stackPush(Stack *S, void *word);

// remove the top of the stack
void stackPop(Stack *S);

// returns 1 if stack is empty
int stackIsEmpty(Stack *S);
void stackDestroy(Stack *S);

#endif // STACK_H_INCLUDED
