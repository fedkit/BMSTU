#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void tree(int t[], int a[], int v, int tl, int tr) 
{
    if (tl == tr)
        t[v] = a[tl];
    else 
    {
        int tm = (tl + tr) / 2;
        tree(t, a, v * 2, tl, tm);
        tree(t, a, v * 2 + 1, tm + 1, tr);
        if (t[v * 2] >= t[v * 2 + 1])
            t[v] = t[v * 2];
        else
            t[v] = t[v * 2 + 1];
    }
}

int comparison(int a, int b)
{
    if (a >= b)
        return a;
    return b;
}

int maxd(int t[], int v, int tl, int tr, int l, int r) 
{
    if (l > r)
        return -1000000001;
    if ((l == tl) && (r == tr))
        return t[v];
    return comparison(maxd(t, v * 2, tl, (tl + tr) / 2, l, fmin(r, (tl + tr) / 2)),
                      maxd(t, v * 2 + 1, (tl + tr) / 2 + 1, tr, fmax(l, (tl + tr) / 2 + 1), r));
}

void upd(int t[], int v, int tl, int tr, int pos, int new_val) 
{
    if (tl == tr)
        t[v] = new_val;
    else 
    {
        if (pos <= (tl + tr) / 2)
            upd(t, v * 2, tl, (tl + tr) / 2, pos, new_val);
        else
            upd(t, v * 2 + 1, (tl + tr) / 2 + 1, tr, pos, new_val);
        if (t[v * 2] >= t[v * 2 + 1])
            t[v] = t[v * 2];
        else
            t[v] = t[v * 2 + 1];
    }
}

int main() 
{
    int n, l, r, u, j;
    char s[4];
    scanf("%d", &n);
    int *mas = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        scanf("%d", &mas[i]);
    int *t = (int *)malloc(4 * n * sizeof(int));
    tree(t, mas, 1, 0, n - 1);
    scanf("%s", s);
    while (s[0] != 'E') 
    {
        if (s[0] == 'M') 
        {
            scanf("%d%d", &l, &r);
            printf("%d\n", maxd(t, 1, 0, n - 1, l, r));
        }
        if (s[0] == 'U') 
        {
            scanf("%d%d", &j, &u);
            upd(t, 1, 0, n - 1, j, u);
        }
        scanf("%s", s);
    }
    free(mas);
    free(t);
    return 0;
}
