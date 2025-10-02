#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char** argv) 
{
    char *s = argv[1];
    long long pi[strlen(s)], j, i;
    pi[0] = 0;
    j = 0, i = 1;
    long long len_s = strlen(s);
    while(i < len_s)
        if(s[i] != s[j])
            if(j == 0)
            {
                pi[i] = 0;
                i++;
            }
            else
                j = pi[j - 1];
        else
        {
            pi[i]=j + 1;
            i++; 
            j++;
        }
    i = 1;
    while(i <= len_s) 
    {
        j = i - pi[i - 1];
        if ((i % j == 0) && (i != j) && (i != 0) && (j != 0)) 
            printf("%lld %lld\n", i, i / j);
        i++;
    }
    return 0;
}
