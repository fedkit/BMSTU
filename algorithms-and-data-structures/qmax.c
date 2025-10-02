#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

struct machine
{
    int size1, size2;
    int index1, index2, indexmax1, indexmax2;
    int *s1, *s2;
    int *max_element1, *max_element2;
};

struct machine queue;

int MIN = -2000000000;

int max(int a, int b)
{
    if(a >= b)
        return a;
    return b;
}

void moveElements()
{
    while (queue.index1 != -1)
    {
        queue.index2++;
        queue.s2[queue.index2] = queue.s1[queue.index1];
        queue.s1[queue.index1] = MIN;
        queue.index1--;

        queue.indexmax2++;
        if (queue.indexmax2 == 0)
            queue.max_element2[queue.indexmax2] = queue.s2[queue.index2];
        else
            queue.max_element2[queue.indexmax2] = max(queue.s2[queue.index2],
            queue.max_element2[queue.indexmax2 - 1]);

        queue.max_element1[queue.indexmax1] = MIN;
        queue.indexmax1--;
    }
}

void qmax(char *s)
{
    if (strcmp(s, "ENQ") == 0)
    {
        int x;
        scanf("%d", &x);
        queue.index1++;
        queue.s1[queue.index1] = x;
        queue.indexmax1++;
        if (queue.indexmax1 == 0)
            queue.max_element1[queue.indexmax1] = x;
        else
            queue.max_element1[queue.indexmax1] = max(x, 
            queue.max_element1[queue.indexmax1 - 1]);
        return;
    }
    if (strcmp(s, "DEQ") == 0)
    {
        if (queue.index2 == -1)
            moveElements();
        printf("%d\n", queue.s2[queue.index2]);
        queue.s2[queue.index2] = MIN;
        queue.index2--;
        queue.max_element2[queue.indexmax2] = MIN;
        queue.indexmax2--;
        return;
    }
    if (strcmp(s, "MAX") == 0)
    {
        if (queue.indexmax1 == -1)
            printf("%d\n", queue.max_element2[queue.indexmax2]);
        else if (queue.indexmax2 == -1)
            printf("%d\n", queue.max_element1[queue.indexmax1]);
        else
            printf("%d\n", max(queue.max_element1[queue.indexmax1], 
            queue.max_element2[queue.indexmax2]));
        return;
    }
    if (strcmp(s, "EMPTY") == 0)
    {
        bool k = (queue.index1 == -1) && (queue.index2 == -1);
        if (k)
            printf("%s\n", "true");
        else
            printf("%s\n", "false");
        return;
    }
    return;
}

int main()
{
    queue.size1 = 1000000;
    queue.size2 = 1000000;
    queue.index1 = -1;
    queue.index2 = -1;
    queue.indexmax1 = -1;
    queue.indexmax2 = -1;
    queue.s1 = (int *)calloc(queue.size1, sizeof(int));
    queue.s2 = (int *)calloc(queue.size2, sizeof(int));
    queue.max_element1 = (int *)calloc(queue.size1, sizeof(int));
    queue.max_element2 = (int *)calloc(queue.size2, sizeof(int));
    char com[6];
    scanf("%s", com);
    while (strcmp(com, "END") != 0)
    {
        qmax(com);
        scanf("%s", com);
    }
    free(queue.s1);
    free(queue.s2);
    free(queue.max_element1);
    free(queue.max_element2);
    return 0;
}
