#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int x1;
    int x2;
} Pair;

typedef struct 
{
    int arr[100000];
    int capacity;
    int size;
} MinHeap;

void minHeapify(int *heap, int n, int i) 
{
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if ((left < n) && (heap[left] < heap[smallest]))
        smallest = left;
    if ((right < n) && (heap[right] < heap[smallest]))
        smallest = right;
    if (smallest != i) {
        int temp = heap[i];
        heap[i] = heap[smallest];
        heap[smallest] = temp;
        minHeapify(heap, n, smallest);
    }
}

void buildMinHeap(int *heap, int n) 
{
    for (int i = n / 2 - 1; i >= 0; i--)
        minHeapify(heap, n, i);
}

MinHeap createMinHeap(int capacity) 
{
    MinHeap minHeap;
    minHeap.capacity = capacity;
    minHeap.size = 0;
    return minHeap;
}

void insertMinHeap(MinHeap* minHeap, int value) 
{
    if ((minHeap == NULL) || (minHeap->size >= minHeap->capacity))
        return;
    int index = minHeap->size;
    minHeap->arr[index] = value;
    minHeap->size++;
    while ((index > 0) && (minHeap->arr[(index - 1) / 2] > minHeap->arr[index])) 
    {
        int temp = minHeap->arr[(index - 1) / 2];
        minHeap->arr[(index - 1) / 2] = minHeap->arr[index];
        minHeap->arr[index] = temp;
        index = (index - 1) / 2;
    }
}

int extractMinHeap(MinHeap* minHeap) 
{
    int min = minHeap->arr[0];
    minHeap->size--;
    minHeap->arr[0] = minHeap->arr[minHeap->size];
    minHeapify(minHeap->arr, minHeap->size, 0);
    return min;
}

int main() 
{
    int n, m;
    scanf("%d%d", &n, &m);
    Pair mas[m];
    for (int i = 0; i < m; i++) 
        scanf("%d%d", &mas[i].x1, &mas[i].x2);
    MinHeap minHeap = createMinHeap(n);
    int k = 0;
    for (int i = 0; i < m; i++) {
        if (minHeap.size == n) 
            k = extractMinHeap(&minHeap);
        int t = k;
        if (mas[i].x1 > k)
            k = mas[i].x1;
        insertMinHeap(&minHeap, k + mas[i].x2);
        k = (t > k) ? t : k;
    }
    while (minHeap.size > 0)
        k = (k > extractMinHeap(&minHeap)) ? k : extractMinHeap(&minHeap);
    printf("%d", k);
    return 0;
}
