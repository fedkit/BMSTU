#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define HASH_SIZE 1000000

typedef struct Node 
{
    int val;
    int key;
    struct Node *next;
} Node;

void insert(Node *start[], int k, int v) 
{
    int ind = abs(k) % HASH_SIZE;
    Node **ptr = &start[ind]->next;
    while ((*ptr != NULL) && ((*ptr)->key != k))
        ptr = &(*ptr)->next;
    if (*ptr == NULL) 
    {
        *ptr = malloc(sizeof(Node));
        if (*ptr == NULL) 
        {
            fprintf(stderr, "ERROR\n");
            exit(1);
        }
        (*ptr)->key = k;
        (*ptr)->val = v;
        (*ptr)->next = NULL;
    } 
    else
        (*ptr)->val = v;
}

int main() 
{
    Node *start[HASH_SIZE];
    for (int i = 0; i < HASH_SIZE; i++) 
    {
        start[i] = malloc(sizeof(Node));
        if (start[i] == NULL) 
        {
            fprintf(stderr, "ERROR\n");
            return 1;
        }
        start[i]->next = NULL;
    }
    int n;
    scanf("%d", &n);
    int xor_val = 0;
    long long ans = 0;
    for (int i = 0; i < n; i++) 
    {
        int k;
        scanf("%d", &k);
        xor_val ^= k;
        int ind = abs(xor_val) % HASH_SIZE;
        Node **ptr = &start[ind]->next;
        while (*ptr != NULL && (*ptr)->key != xor_val)
            ptr = &(*ptr)->next;
        if (*ptr != NULL) 
        {
            ans += (*ptr)->val;
            (*ptr)->val++;
        } 
        else 
        {
            insert(start, xor_val, 0);
            ptr = &start[ind]->next;
            while (*ptr != NULL && (*ptr)->key != xor_val)
                ptr = &(*ptr)->next;
            ans += (*ptr)->val;
            (*ptr)->val++;
        }
        if (xor_val == 0)
            ans++;
    }
    printf("%lld", ans); 
    for (int i = 0; i < HASH_SIZE; i++) 
    {
        Node *now = start[i];
        while (now != NULL) 
        {
            Node *next = now->next;
            free(now);
            now = next;
        }
    }
    return 0;
}
