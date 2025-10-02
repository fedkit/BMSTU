#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

struct machine
{
    int index;
    int len;
    int size;
    int *q;
};

struct machine queue;

void circbuf(char *s)
{
    if (strcmp(s, "ENQ") == 0)
    {
        int x;
        scanf("%d", &x);
        if(queue.len == queue.size)
        {
            queue.size *= 2;
            int *dop_mas = calloc(queue.size, sizeof(int));
            for(int i = 0; i < queue.len; i++)
                dop_mas[i] = queue.q[(queue.index + i) % (queue.size / 2)];
            free(queue.q);
            queue.q = dop_mas;
            queue.index = 0;
        }
        queue.q[(queue.index + queue.len) % queue.size] = x;
        queue.len++;
    }
    if (strcmp(s, "DEQ") == 0)
    {
        printf("%d\n", queue.q[queue.index]);
        queue.len--;
        queue.index = (queue.index + 1) % queue.size;
        return;
    }
    if (strcmp(s, "EMPTY") == 0)
        if(queue.len == 0)
            printf("%s\n", "true");
        else
            printf("%s\n", "false");
    return;
}

int main()
{
    queue.index = 0;
    queue.len = 0;
    queue.size = 4;
    queue.q = calloc(queue.size, sizeof(int));
    char com[6];
    scanf("%s", com);
    while (strcmp(com, "END") != 0)
    {
        circbuf(com);
        scanf("%s", com);
    }
    return 0;
}
