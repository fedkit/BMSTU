#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct machine
{
    long long size;
    long long *point;
    long long **mas;
};

struct machine divide;

void sift(long long *heap, long long n, long long index) 
{
    bool k = true;
    while (k) 
    {
        long long t1 = (index * 2) + 1;
        if (t1 >= n)
            k = false;
        else 
        {
            long long swap_index = t1;
            long long t2 = t1 + 1;
            long long t1_v = divide.mas[heap[t1]][divide.point[heap[t1]]];
            long long t2_v = (t2 < n) ? 
                    divide.mas[heap[t2]][divide.point[heap[t2]]] : 0;
            long long swap_v = divide.mas[heap[swap_index]][divide.point[heap[swap_index]]];
            long long x_v = divide.mas[heap[index]][divide.point[heap[index]]];
            if ((t2 < n) && (t2_v < t1_v)) 
            {
                swap_index = t2;
                swap_v = t2_v;
            }
            if (swap_v < x_v) 
            {
                long long t;
                t = heap[index];
                heap[index] = heap[swap_index];
                heap[swap_index] = t;
                index = swap_index;
            } 
            else 
                k = false;
        }
    }
}

void build_heap_min(long long *heap, long long n) 
{
    for (long long i = (n - 1) / 2; i >= 0; i--) 
        sift(heap, n, i);
}

void process_heap(long long *heap, long long *res, long long *mass, long long n) 
{
    long long d = n, res_index = 0;
    while (d > 0) 
    {
        long long id = heap[0];
        res[res_index++] = divide.mas[id][divide.point[id]];
        divide.point[id]++;
        if (divide.point[id] == mass[id]) 
        {
            d--;
            if (d > 0) 
            {
                long long t;
                t = heap[0];
                heap[0] = heap[d];
                heap[d] = t;
                sift(heap, d, 0);
            }
        } 
        else 
            sift(heap, d, 0);
    }
}

int main() 
{
    long long k, *mass, *heap;
    divide.size = 0;
    scanf("%lld", &k);
    mass = calloc(k, sizeof(long long));
    heap = calloc(k, sizeof(long long));
    for (long long i = 0; i < k; i++) 
    {
        scanf("%lld", &mass[i]);
        divide.size  += mass[i];
        heap[i] = i;
    }
    divide.point = calloc(k, sizeof(long long));
    divide.mas = calloc(k, sizeof(long long*));
    for (long long i = 0; i < k; i++) 
    {
        divide.mas[i] = (long long*)malloc(mass[i] * sizeof(long long));
        for (long long j = 0; j < mass[i]; j++) 
            scanf("%lld", &divide.mas[i][j]);
        divide.point[i] = 0;
    }
    build_heap_min(heap, k);
    long long *res = calloc(divide.size, sizeof(long long));
    process_heap(heap, res, mass, k);
    for (long long i = 0; i < divide.size; i++) 
        printf("%lld ", res[i]);
    free(mass);
    free(heap);
    free(divide.point);
    for (long long i = 0; i < k; i++) 
        free(divide.mas[i]);
    free(divide.mas);
    free(res);
    return 0;
}
