#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef int DATATYPE;

typedef struct
{
    DATATYPE data;
    struct Node *next;
    struct Node *prev;
} Node;

typedef struct
{
    Node *Head;
    Node *Cur;
    Node *Tail;
    int NumofData;
} DoublyLinkedList;

void InitList(DoublyLinkedList *dlist);
void Insert(DoublyLinkedList *dlist, DATATYPE data, int Position);
void Delete(DoublyLinkedList *dlist, int Position);
Node *Find(DoublyLinkedList *dlist, int Position);

int main()
{
    DoublyLinkedList dlist;
    InitList(&dlist);

    int dataList[] = {2, 4, 5, 6, 3, 1};
    int positionList[] = {1, 2, 3, -1, 3, 1};
    for (int i = 0; i < 6; i++)
    {
        Insert(&dlist, dataList[i], positionList[i]);
        Node *temp = dlist.Head;
        for (int j = 0; j < i; i++)
        {
            temp = temp->next;
            printf("%d -> ", temp->data);
        }
        temp = temp->next;
        printf("%d\n\n", temp->data);
    }

    return 0;
}

void InitList(DoublyLinkedList *dlist)
{
    dlist->Head = (Node *)malloc(sizeof(Node));
    dlist->Head->next = NULL;
    dlist->Tail = NULL;
    dlist->Cur = NULL;
    dlist->NumofData = 0;
}

void Insert(DoublyLinkedList *dlist, DATATYPE data, int Position)
{
    Node *pred = dlist->Head;
    Node *temp = (Node *)malloc(sizeof(Node));
    temp->data = data;
    temp->prev = NULL;
    temp->next = NULL;

    if (Position > dlist->NumofData + 1)
    {
        printf("Insert Error!\n");
        return;
    }

    if (Position == -1 || Position == RetCount(dlist) + 1)
    {
        if (dlist->Head->next == NULL)
        {
            dlist->Head->next = temp;
        }
        else
        {
            while (pred->next != NULL)
            {
                pred = pred->next;
            }
            temp->next = pred->next;
            pred->next = temp;
            temp->prev = pred;
        }
    }
    else
    {
        while (Position--)
        {
            pred = pred->next;
        }
        temp->next = pred->next;
        temp->next->prev = temp;
        pred->next = temp;
        temp->prev = pred;
    }
    dlist->NumofData++;
}

void Delete(DoublyLinkedList *dlist, int Position)
{
    Node *pred_pre = Find(dlist, Position - 1);
    Node *pred = Find(dlist, Position);
    Node *pred_next = Find(dlist, Position + 1);

    if (pred == NULL)
    {
        printf("Delete error!");
        return;
    }
    else if (RetCount(dlist) == Position)
    {
        pred_pre->next = NULL;
        free(pred);
    }
    else
    {
        pred_pre->next = pred->next;
        pred_next->prev = pred->prev;
        free(pred);
    }
    dlist->NumofData--;
}

Node *Find(DoublyLinkedList *dlist, int Position)
{
    if (Position > dlist->NumofData)
    {
        return NULL;
    }

    Node *pred = dlist->Head;

    while (Position--)
    {
        pred = pred->next;
    }

    return pred;
}