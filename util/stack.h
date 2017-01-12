#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#define STACK_MAX 100000

struct Stack {
    void     *data[STACK_MAX];
    int     size;
};
typedef struct Stack Stack;

void stackInit(Stack *S);
void *stackTop(Stack *S);
void stackPush(Stack *S, void *word);
void stackPop(Stack *S);

#endif // STACK_H_INCLUDED
