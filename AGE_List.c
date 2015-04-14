#include "AGE/AGE_Generics.h"


void AGE_ListInit(AGE_List *list,int sizeOfElement)
{
    assert(sizeOfElement > 0);
    list->head = NULL;
    list->tail = NULL;
    list->length = 0;
    list->elementSize = sizeOfElement;
}

void AGE_ListDestroy(AGE_List *list)
{
    ListNode* currNode;

    while(list->head != NULL)
    {
        currNode = list->head;
        list->head = currNode->next;
        free(currNode->data);
        free(currNode);
    }
}

int AGE_ListGetSize(AGE_List *list)
{
    return list->length;
}

void AGE_ListAddFront(AGE_List *list, void* newData)
{
    ListNode *newNode = malloc(sizeof(ListNode));
    newNode->data = malloc(list->elementSize);
    memcpy(newNode->data, newData, list->elementSize);

    newNode->next = list->head;

    if(list->length!=0)
    {
        list->head->prev = newNode;
    }
    
    newNode->prev =NULL;
    list->head = newNode;


    //length == 0 ?
    if(!list->tail)
    {
        list->tail = list->head;
    }
    
    list->length ++;
}

void AGE_ListAddBack(AGE_List *list, void* newData)
{
    ListNode *newNode = malloc(sizeof(ListNode));
    newNode->data = malloc(list->elementSize);
    memcpy(newNode->data, newData, list->elementSize);

    newNode->next = NULL;
    newNode->prev = list->tail;

    //length == 0 ?
    if(list->length == 0)
    {
        list->head = newNode;
        list->tail = newNode;
    }
    else
    {
        list->tail->next = newNode;
        list->tail = newNode;
    }

    list->length ++;
}

void AGE_ListRemoveFront(AGE_List *list)
{
    ListNode *node = list->head;
    list->head = node->next;
    list->length--;

    free(node->data);
    free(node);
}

void AGE_ListRemoveBack(AGE_List *list)
{
     ListNode *node = list->tail;
     list->tail = node->prev;
     list->length--;

     free(node->data);
     free(node);
}

void AGE_ListPeekFront(AGE_List *list, void *result)
{
    assert(list->head != NULL);
    memcpy(result, list->head->data, list->elementSize);
}

void AGE_ListPeekBack(AGE_List *list, void *result)
{
    assert(list->tail != NULL);
    memcpy(result, list->tail->data, list->elementSize);
}

void AGE_ListForEach(AGE_List *list, listIterator iterator)
{
    assert(iterator != NULL);

    ListNode *node = list->head;
    bool result = true;

    while(node!=NULL)
    {
        result = iterator(node->data);
        node = node->next;
    }
}

// void AGE_ListInit(AGE_List* list,int sizeOfElement) {
//     list->size = 5;
//     list->index = 0;
//     list->elementSize = sizeOfElement;
//     list->data = malloc(list->size * list->elementSize);
// }

// void AGE_ListDestroy(AGE_List* list){
//     free(list->data);
//     list->size = 0;
//     list->index = 0;
// }

// int AGE_ListGetSize(AGE_List *list) {
//     return list->index;
// }

// void AGE_ListAdd(AGE_List* list, void* value) {
//     if(list->index >= list->size)
//     {
//         list_resize(list, 0);
//     }

//     list->data[list->index++] = value;
// }

// void* AGE_ListAt(AGE_List *list, int index) {
//     if(index < 0 || index >= list->index)
//     {
//         return list->data[0];
//     }

//     return list->data[index];
// }

// void* AGE_ListRemoveLast(AGE_List* list) {
//     if(list->index <= 0)
//     {
//         return list->data[0];
//     }
//     // if(list->index <= list->size / 2 && list->size >2)
//     // {
//     //     list_resize(list, 1);
//     // }

//     return list->data[--list->index];
// }

// int list_resize(AGE_List* list, int makeLower)
// {
//     int i;
//     printf("resize");    

//     if(makeLower==0)
//     {
//         list->size *= 2;
//     }
//     else
//     {
//         list->size /= 2;
//     }
//     // void *oldData[list->index];
//     // oldData = malloc(list->size * list->elementSize);
//     // for(i = 0; i < list->index; i++)
//     // {
//     //     void* p = AGE_ListAt(list,i);
//     //     printf("i:%d - %d",i, *((int*)p));
//     //     oldData[i] = p;
//     // }
//     free(list->data);    
//     int ind = list->index;
//     list->index = 0;
//     list->data = realloc(list->data, list->size * list->elementSize);

//     // for (i = 0; i < ind; ++i)
//     // {
//     //     AGE_ListAdd(list,oldData[i]);
//     // }

//     return list->size;
// }

// void AGE_ListCopy(AGE_List* from, AGE_List* to)
// {
//     AGE_ListInit(to,from->elementSize);
//     int i;

//     for(i=0; i<AGE_ListGetSize(from); i++)
//     {
//         AGE_ListAdd(to, AGE_ListAt(from,i));
//     }
// }