#include <stdio.h>
#include <stdlib.h>

struct Elem 
{
    struct Elem *prev, *next;
    int v;
};

void sort(struct Elem *index) 
{
    struct Elem *n = index->next;
    while (n != index) 
    {
        struct Elem *next = n->next;
        struct Elem *save = n;
        n = n->prev;
        while ((n != index) && (save->v < n->v))
            n = n->prev;
        save->prev->next = save->next;
        save->next->prev = save->prev;
        save->next = n->next;
        n->next = save;
        save->prev = n;
        save->next->prev = save;
        n = next;
    }
}

int main() 
{
    int n_mas, element;
    scanf("%d", &n_mas);
    struct Elem elements[n_mas + 1]; 
    struct Elem *index = &elements[0];
    index->prev = index;
    index->next = index;
    for (int i = 0; i < n_mas; i++) 
    {
        scanf("%d", &element);
        struct Elem *newElement = &elements[i + 1];
        newElement->v = element;
        struct Elem *n = index->next;
        while ((n != index) && (n->v < element))
            n = n->next;
        newElement->prev = n->prev;
        newElement->next = n;
        n->prev->next = newElement;
        n->prev = newElement;
    }
    sort(index);
    struct Elem *n = index->next;
    while (n != index) 
    {
        struct Elem *next = n->next;
        printf("%d ", n->v);
        n = next;
    }
    return 0;
}
