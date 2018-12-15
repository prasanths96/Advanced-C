#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    void *elems;
    int loglen;
    int alloclen;
    int elemSize;
    void (*freeFunc)(void *elem);
}Stack;

void StackInit(Stack *s, int elemSize, void (*freeFunc)(void *elem));
void StackPush(Stack *s, void* elemAddr);
void StackPop(Stack *s,void* elemAddr);
void StackDispose(Stack *s);

static void growStack(Stack *s) {
    s->alloclen *= 2;
    s->elems = realloc(s->elems, s->elemSize * s->alloclen);
    if(s->elems == NULL){
        printf("Realloc failure.");
        _Exit;
    }
}

void StackInit(Stack *s, int elemSize, void (*freeFunc)(void *elem)) {
    if(elemSize <= 0){
        printf("ElemSize cannot be <= 0.Exitting.");
        _Exit;
    }
    s->alloclen = 4;
    s->loglen = 0;
    s->elemSize = elemSize;
    s->freeFunc = freeFunc;
    s->elems = malloc(elemSize*s->alloclen);
    if(s->elems == NULL){
        printf("Malloc failure: s->elems = NULL");
        _Exit;
    }
}

void StackPush(Stack *s, void *elemAddr) {
    if(s->loglen == s->alloclen) {
        growStack(s);
    }
    void *target = (char *) s->elems + (s->loglen * s->elemSize);
    
    memcpy(target, elemAddr, s->elemSize); 
    s->loglen++;
}

void StackPop(Stack *s, void *elemAddr) {
    if(s->loglen <= 0){
        printf("Empty Stack\n");
        return;
    }
    s->loglen--;
    void *source = (char *)s->elems + (s->loglen * s->elemSize);
    memcpy(elemAddr, source, s->elemSize);
}

void StackDispose(Stack *s) {
    if(s->freeFunc != NULL){
        for(int i=0; i<s->loglen; i++){
            void* elem = (char *)s->elems + s->elemSize * i;
            s->freeFunc(elem);
        }
    }
    free(s->elems);
    s->loglen = 0;
    s->alloclen = 0;
}

void StringFree (void *elem){
    free(*(char **)elem);
}

void main() {
    Stack s;
    char *string = strdup("Hellooo");
    StackInit(&s, sizeof(char *), &StringFree);
    StackPush(&s, &string);
    string = strdup("How are youuuu?");
    StackPush(&s, &string);

     printf("%s\n",string);
    for(int i=0; i<2; i++){
        char *container;
        StackPop(&s, &container);
        printf("Address: %s\n",container);
    }
    
    StackDispose(&s);
    
    printf("%s\n",string);
    for(int i=0; i<2; i++){
        char *container;
        StackPop(&s, &container);
        printf("Address: %d\n",container);
    }
}