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
void AGE_ListAddBack(AGE_List*, void*);
void AGE_ListRemoveFront(AGE_List*);
void AGE_ListRemoveBack(AGE_List*);
void AGE_ListPeekFront(AGE_List*, void*);
void AGE_ListPeekBack(AGE_List*, void*);
void AGE_ListForEach(AGE_List*, listIterator);

#endif