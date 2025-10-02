#include <stdio.h>

int main()
{
	unsigned long long fib[200];
    long long n, k = 1;
    fib[1] = 1;
    fib[2] = 1;
    for(int i = 3; i < 200; i++)
        fib[i] = fib[i - 1] + fib[i - 2];
    scanf("%lld", &n);
    while(fib[k] < n)
        k++;
    if(fib[k] > n)
        k--;
    if(n < 2)
        printf("%lld", n);
    else
        for(int i = k; i > 1; i--)
            if(fib[i] <= n)
            {
                n -= fib[i];
                printf("1");
            }
            else
                printf("0");
	return 0;
}
