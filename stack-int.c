#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int *elems;
    int loglen;
    int alloclen;
}Stack;

void StackInit(Stack *s){
    s->loglen = 0;
    s->alloclen = 4;
    s->elems = malloc(4 * sizeof(int));
    //assert(s->elems != NULL);
}

void StackDispose(Stack *s){
    free(s->elems);
}

void StackPush(Stack *s, int value){
    if(s->loglen == s->alloclen){
        s->alloclen *= 2;
        s->elems = realloc(s->elems,s->alloclen * sizeof(int));
        //_Static_assert((s->elems != NULL)? 1 : 0,"StackPush assert");
    }
    s->elems[s->loglen] = value;
    s->loglen++;
}

int StackPop(Stack *s){
    // Check if stack is empty assert();
    if(s->loglen <= 0){
        printf("Stack is Empty");
        return NULL;
    }
    s->loglen--;
    return s->elems[s->loglen];
}

void main(){
    Stack a;
    int i;
    StackInit(&a);
    for(i=0; i<100000000; i++){
        StackPush(&a,i);
    }

    /*for(i=0 ;i<100000; i++){
        printf("%d\n",a.elems[i]);
    }*/

    printf("%d\n",StackPop(&a));
    printf("%d",StackPop(&a));
}