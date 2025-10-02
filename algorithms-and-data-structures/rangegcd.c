#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int algoritm_Euclidean(int a, int b) 
{
    int t;
    while (b != 0) 
    {
        t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int gcd_dop(int st[], int tl, int tr, int l, int r, int v) 
{
    if ((tl > r) || (tr < l))
        return 0;
    if ((l <= tl) && (r >= tr))
        return st[v];
    return algoritm_Euclidean(gcd_dop(st, tl, (tl + tr) / 2, l, r, v * 2 + 1), gcd_dop(st, (tl + tr) / 2 + 1, tr, l, r, v * 2 + 2));
}

int gcd(int st[], int tl, int tr, int arr[], int n) 
{
    if ((tl < 0) || (tr > n - 1) || (tl > tr)) 
        return -1;
    return gcd_dop(st, 0, n - 1, tl, tr, 0);
}

int tree(int arr[], int tl, int tr, int st[], int v) {
    if (tl == tr) 
    {
        st[v] = arr[tl];
        return st[v];
    }
    st[v] = algoritm_Euclidean(tree(arr, tl, (tl + tr) / 2, st, v * 2 + 1), tree(arr, (tl + tr) / 2 + 1, tr, st, v * 2 + 2));
    return st[v];
}

int main() 
{
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    int h = (int)ceil(log2(n));
    int a = (1 << (h + 1)) - 1;
    int mas[a];
    tree(arr, 0, n - 1, mas, 0);
    int m;
    scanf("%d", &m);
    for(int i = 0; i < m; i++)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        printf("%d\n", abs(gcd(mas, l, r, arr, n)));
    }
    return 0;
}
