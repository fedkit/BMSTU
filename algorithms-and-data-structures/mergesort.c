#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void merge(int* mas, int k, int l, int r) 
{
    int t1 = l - k + 1, t2 = r - l;
    int left[t1];
    for (int i = 0; i < t1; i++) 
        left[i] = mas[k + i];
    
    int i = 0, j = l + 1, b = k;

    while ((i < t1) && (j <= r)) 
        if (abs(left[i]) <= abs(mas[j]))
            mas[b++] = left[i++];
        else 
            mas[b++] = mas[j++];

    while (i < t1) 
        mas[b++] = left[i++];
}

void insertsort(int* mas, int len)
{
    for (int i = 1; i <= len; i++) 
    {
        int k = mas[i];
        int j = i - 1;
        while ((abs(mas[j]) > abs(k)) && (j >= 0)) 
        {
            mas[j + 1] = mas[j];
            j = j - 1;
        }
        mas[j + 1] = k;
    }
}

void mergesort(int* mas, int l, int r)
{
    if (r - l < 5)
        insertsort(mas + l, r - l);
    else 
    {
        mergesort(mas, l, (l + r) / 2);
        mergesort(mas, (l + r) / 2 + 1, r);
        merge(mas, l, (l + r) / 2, r);
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    int mas[n];
    for(int i = 0; i < n; i++) 
        scanf("%d", &mas[i]);
    mergesort(mas, 0, n-1);
    for(int i = 0; i < n; i++) 
        printf("%d ", mas[i]);
    return 0;
}
