#ifndef AGE_GENERICS
#define AGE_GENERICS

#include "AGE.h"

typedef bool (*listIterator)(void*);

typedef struct listNode ListNode;

struct listNode {
    void *data;
    ListNode *next;
    ListNode *prev;
};

typedef struct {
    ListNode *head;
    ListNode *tail;
    int length;
    int elementSize;
} AGE_List;

void AGE_ListInit(AGE_List*,int);
void AGE_ListDestroy(AGE_List*);
int AGE_ListGetSize(AGE_List*);
void AGE_ListAddFront(AGE_List*, void*);
void AGE_ListInsert(AGE_List*, void*, int);
void AGE_ListAdd(AGE_List*, void*);
void AGE_ListRemoveFront(AGE_List*);
void AGE_ListRemoveLast(AGE_List*);
void AGE_ListRemoveAt(AGE_List*,int);
void AGE_ListPeekFront(AGE_List*, void*);
void AGE_ListPeekLast(AGE_List*, void*);
void AGE_ListPeekAt(AGE_List *, void *, int);
void AGE_ListForEach(AGE_List*, listIterator);

#endif