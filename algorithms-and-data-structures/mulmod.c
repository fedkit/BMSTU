#include <stdio.h>
int main()
{    
    unsigned long long x, y, m, res = 0;
    long long bin[64];
    scanf("%lld%lld%lld", &x, &y, &m);
    for(int i = 63; i >= 0; i--)
    {
        bin[i] = y % 2;
        y /= 2;
    }
    for(int i = 0; i <= 62; i++)
    {
        res = ((((res % m) + (x % m) * bin[i]) % m) * 2) % m;
    }
    printf("%lld", ((res % m) + (x % m) * bin[63]) % m);
    return 0;
}
