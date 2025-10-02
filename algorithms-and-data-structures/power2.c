#include <stdio.h>

int res = 0;

void comb(int sum, int *s, int n, int index) 
{
    if ((sum & (sum - 1)) == 0 && sum >= 1) 
        res++;
    for (int i = index + 1; i < n; i++) 
        comb(sum + s[i], s, n, i);
}

int main() 
{
    int n;
    scanf("%d", &n);
    int s[n];
    for (int i = 0; i < n; i++) 
        scanf("%d", &s[i]);
    for (int i = 0; i < n; i++) 
        comb(s[i], s, n, i);
    printf("%d", res);
    return 0;
}
