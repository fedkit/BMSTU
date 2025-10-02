#include <stdio.h>

unsigned long long degree(int a, int x)
{
    unsigned long long k = 1;
    for (int i = 1; i <= x; i++)
        k *= a;
    return k;
}

int main()
{    
    unsigned long long n1, n2, k1 = 0, k2 = 0, a, comp;
    int ind[32];
    for(int i = 0; i <= 31; i++)
        ind[i] = 0;
    scanf("%lld", &n1);
    for (int i = 1; i <= n1; i++)
    {
        scanf("%lld", &a);
        k1 = k1 + degree(2, a);
    }
    scanf("%lld", &n2);
    for (int i = 1; i <= n2; i++)
    {
        scanf("%lld", &a);
        k2 += degree(2, a);
    }
    comp = k1 & k2;
    for(int i = 31; i >= 0; i--)
        if(comp >= degree(2, i))
        {
            comp -= degree(2, i);
            ind[i] = 1;
        }
    for(int i = 0; i <= 31; i++)
        if(ind[i] == 1)
            printf("%d ", i);
}