#include <stdio.h>

double comp(double *s, int start, int end)
{
    double product = 1;
    while (start <= end)
    {
        product *= s[start];
        start++;
    }
    return product;
}

int main()
{
    int n, l = 0, r = 0;
    char delimiter;
    double a, b, k;
    scanf("%d", &n);
    double x_float[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%lf%c%lf", &a, &delimiter, &b);
        x_float[i] = a / b;
    }
    k = x_float[0];
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            if (comp(x_float, i, j) > k)
            {
                k = comp(x_float, i, j);
                l = i;
                r = j;
            }
        }
    }
    printf("%d %d", l, r);
    return 0;
}
