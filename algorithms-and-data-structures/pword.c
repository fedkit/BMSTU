#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char** argv) 
{
    char *s = argv[1];
    char *t = argv[2];
    int pi[strlen(s)], j, i;
    pi[0] = 0;
    j = 0, i = 1;
    int len_s = strlen(s), len_t = strlen(t);
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
    i = 0, j = 0;
    while (i < len_t) 
    {
        if (j == len_s) 
            j = pi[j - 1];
        if ((j > 0) && (s[j] != t[i])) 
            j = pi[j - 1];
        else if (s[j] == t[i]) 
        {
            j++;
            i++;
        } 
        else 
        {
            printf("no");
            return 0;
        }
    }
    printf("yes");
    return 0;
}
