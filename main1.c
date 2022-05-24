#include "queue.h"
#define LENGTH 10
int main(int argc, char const *argv[])
{
    int arr[LENGTH] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    pqueue Q = createQ();
    
    for (size_t i = 0; i < LENGTH; i++)
    {
        enQ(Q, &arr[i]);
    }
    printf("[");
    while (!isEmpty(Q))
    {
        int *n = (int*)deQ(Q);
        printf("%d, ", *n);
    }
    printf("]\n");

    destoryQ(Q);

    return 0;
}
