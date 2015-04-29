#include "AGE_Generics.h"

ListNode* listGetNode(AGE_List*,int);

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

        if(currNode->data != NULL)
        {
            free(currNode->data);
        }
        if(currNode!=NULL)
        {
            free(currNode);
        }
    }

    list->tail = NULL;
    list->length = 0;
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

void AGE_ListAdd(AGE_List *list, void* newData)
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
    // list->head->prev = NULL;
    list->length--;

    free(node->data);    
    free(node);
}

void AGE_ListRemoveLast(AGE_List *list)
{
     ListNode *node = list->tail;
     list->tail = node->prev;
     list->tail->next = NULL;
     list->length--;

     free(node->data);
     free(node);
}

void AGE_ListPeekFront(AGE_List *list, void *result)
{
    assert(list->head != NULL);
    memcpy(result, list->head->data, list->elementSize);
}

void AGE_ListPeekLast(AGE_List *list, void *result)
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

void AGE_ListPeekAt(AGE_List *list, void *result, int index)
{
    // listGetNode(list,index);
    memcpy(result, listGetNode(list,index)->data, list->elementSize);
}

void AGE_ListRemoveAt(AGE_List *list,int index)
{
    // printf("index:%d , size:%d",index,list->length);
    ListNode *node = listGetNode(list,index);
    if(index > 0)
    {
        node->prev->next = node->next;
    }
    else
    {
        list->head = node->next;
    }
    if(index < list->length-1)
    {
        node->next->prev = node->prev;
    }
    else
    {
        list->tail = node->prev;
    }

    free(node->data);
    free(node);

    list->length--;
}

ListNode* listGetNode(AGE_List *list,int index)
{
    // printf("node%d %d\n",index,list->length);
    assert(index>=0 && index < list->length);
    int i;
    ListNode *currNode = list->head;

    for (i = 1; i <= index; ++i)
    {
        currNode = currNode->next;
    }

    return currNode;
}

void AGE_ListInsert(AGE_List *list, void *newData, int index)
{
    assert(index >= 0 && index < list->length);

    if(index == 0)
    {
        AGE_ListAddFront(list, newData);
        return;
    }

    ListNode *indexNode = listGetNode(list,index);

    ListNode *newNode = malloc(sizeof(ListNode));
    newNode->data = malloc(list->elementSize);
    memcpy(newNode->data, newData, list->elementSize);

    newNode->next = indexNode;

    indexNode->prev->next = newNode;
    indexNode->prev = newNode;

    list->length ++;
}

void AGE_ListReplace(AGE_List *list, void *newData, int index)
{
    // printf("replace%d %d\n",index,list->length);
    memcpy(listGetNode(list,index)->data, newData, list->elementSize);
}