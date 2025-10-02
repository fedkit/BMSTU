#include <stdio.h>
int main()
{
    long long n, x0, a, fun = 0, proiz = 0;
    scanf("%lld%lld", &n, &x0);
    for (long long i = n; i >= 1; i--)
    {
        scanf("%lld", &a);
        fun = fun * x0 + a;
        proiz = proiz * x0 + (a * i);
    }
    scanf("%lld", &a);
    printf("%lld %lld", fun * x0 + a, proiz);
    return 0;
}
