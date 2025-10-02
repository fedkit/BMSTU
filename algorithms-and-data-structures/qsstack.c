#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Task 
{
    int low, high;
};

struct machine 
{
    int size;
    int index;
    struct Task *s;
};

void swap(int *a, int *b) 
{
    int t;
    t = *a;
    *a = *b;
    *b = t;
}

int partition(int *mas, int left, int right) 
{
    int i = left - 1;
    for (int j = left; j < right; j++) 
        if (mas[j] < mas[right]) 
        {
            i++;
            swap(&mas[i], &mas[j]);
        }
    swap(&mas[i + 1], &mas[right]);
    return i + 1;
}

void quickSort(struct machine *stack, int *mas, int n) 
{
    (*stack).size = 1000000;
    (*stack).index = 0;
    (*stack).s = (struct Task*)calloc((*stack).size, sizeof(struct Task));
    (*stack).s[(*stack).index].low = 0;
    (*stack).s[(*stack).index].high = n - 1;
    while ((*stack).index >= 0) 
    {
        int left = (*stack).s[(*stack).index].low;
        int right = (*stack).s[(*stack).index].high;
        (*stack).index--;
        int k = partition(mas, left, right);
        if (k < right) 
        {
            (*stack).s[(*stack).index + 1].low = k + 1;
            (*stack).index++;
            (*stack).s[(*stack).index].high = right;
        }
        if (k > left) 
        {
            (*stack).s[(*stack).index + 1].low = left;
            (*stack).index++;
            (*stack).s[(*stack).index].high = k - 1;
        }
    }
}

int main() 
{
    int n;
    scanf("%d", &n);
    int mas[n];
    for (int i = 0; i < n; i++)
        scanf("%d", &mas[i]);
    struct machine stack;
    quickSort(&stack, mas, n);
    for (int i = 0; i < n; i++)
        printf("%d ", mas[i]);
    free(stack.s);
    return 0;
}
