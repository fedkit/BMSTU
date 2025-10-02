#include <stdio.h>
#include <string.h> 


void dsort(int *a, char *s, int k)
{
    int d;
    for(int i = 0; i < k; i++)
    {
        d = (int)(s[i]);
        a[d - 97]++;
    }
}


int main() 
{
    char s[1000010];
    int alphabet[26] = {0};
    fgets(s, sizeof(s), stdin);
    int len = strlen(s) - 1;
    char str[len];
    for(int i = 0; i < len; i++)
        str[i] = s[i];
    dsort(alphabet, str, len);
    for(int i = 0; i < 26; i++)
        while(alphabet[i] > 0)
        {
            printf("%c", (char)(i + 97));
            alphabet[i]--;
        }
    return 0;
}
