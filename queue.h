#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

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
    pthread_mutex_t lock;
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
        exit(0);
    }
    newQ->start = NULL;
    newQ->end = NULL;
    if (pthread_mutex_init(&newQ->lock, NULL) != 0)
    {
        perror("mutex init failed");
        exit(0);
    }
    return newQ;
}
void enQ(pqueue Q, void *n)
{
    pthread_mutex_lock(&Q->lock);
    pnode newN = newNode(n);
    if (isEmpty(Q))
    {
        Q->end = newN;
    }
    else
    {
        Q->start->prev = newN;
    }
    newN->next = Q->start;
    Q->start = newN;
    pthread_mutex_unlock(&Q->lock);
}
void *deQ(pqueue Q)
{
    pthread_mutex_lock(&Q->lock);
    if (isEmpty(Q))
    {
        perror("The queue is empty!");
    }
    
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
    pthread_mutex_unlock(&Q->lock);
    return res;
}
void destoryQ(pqueue Q)
{
    while (!isEmpty(Q))
    {
        void *temp = deQ(Q);
        free(temp);
    }
    free(Q);
    pthread_mutex_destroy(&Q->lock);
}
