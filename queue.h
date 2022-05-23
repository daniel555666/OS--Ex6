#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NODE
{
    void *data;
    struct NODE *next;
    struct NODE *prev;
} node, *pnode;

typedef struct QUEUE
{
    pnode start;
    pnode end;
} queue, *pqueue;

pnode newNode(void *newData)
{
    pnode nod = (pnode)malloc(sizeof(node));
    if (nod == NULL)
    {
        perror("malloc pnode");
    }
    nod->data = newData;
    nod->next = NULL;
    nod->prev = NULL;
    return nod;
}

int isEmpty(pqueue Q)
{
    return (Q->start == NULL);
}
pqueue createQ()
{
    pqueue newQ = (pqueue)malloc(sizeof(queue));
    if (newQ == NULL)
    {
        perror("malloc pqueue");
    }
    newQ->start = NULL;
    newQ->end = NULL;
    return newQ;
}
void enQ(pqueue Q, void *n)
{
    pnode newN = newNode(n);
    if (!isEmpty(Q))
    {
        Q->start->prev = newN;
    }
    else
    {
        Q->end = newN;
    }
    newN->next = Q->start;
    Q->start = newN;
}
void *deQ(pqueue Q)
{
    if (Q->start == Q->end)
    {
        pnode temp = Q->start;
        Q->start = NULL;
        Q->end = NULL;
        void *res = temp->data;
        free(temp);
        return res;
    }
    pnode endN = Q->end;
    void *res = endN->data;
    endN->prev->next = NULL;
    Q->end = endN->prev;
    free(endN);
    return res;
}
void destoryQ(pqueue Q)
{
    while (!isEmpty(Q))
    {
        void* temp = deQ(Q);
        free(temp); 
    }
    free(Q);
}
