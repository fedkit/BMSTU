#include <stdio.h>

int main()
{    
    int n, k;
    scanf("%d", &n);
    long long sum = 0, max, elem[n];
    for(int i = 0; i < n; i++){
        scanf("%lld", &elem[i]);
    }
    scanf("%d", &k);
    for(int i = 0; i < k; i++){
        sum += elem[i];
    }
    max = sum;
    for(int i = 0; i + k != n; i++){
        sum = sum - elem[i] + elem[i + k];
        if(sum >= max){
            max = sum;
        }
    }
    printf("%lld", max);
}
