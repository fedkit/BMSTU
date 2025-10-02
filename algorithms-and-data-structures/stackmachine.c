#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct machine
{
    long long size;
    long long index;
    long long *s;
};

struct machine stack; 

void stackmachine(char *s)
{
    if (strcmp(s, "CONST") == 0)
    {
        long long x;
        scanf("%lld", &x);
        stack.index++;
        stack.s[stack.index] = x;
        return;
    }
    if (strcmp(s, "ADD") == 0)
        if(stack.index >= 1)
        {
            long long a, b;
            a = stack.s[stack.index];
            b = stack.s[stack.index - 1];
            stack.s[stack.index] = 0;
            stack.index--;
            stack.s[stack.index] = a + b;
            return;
        }
    if (strcmp(s, "SUB") == 0)
        if(stack.index >= 1)
        {
            long long a, b;
            a = stack.s[stack.index];
            b = stack.s[stack.index - 1];
            stack.s[stack.index] = 0;
            stack.index--;
            stack.s[stack.index] = a - b;
            return;
        }
    if (strcmp(s, "MUL") == 0)
        if(stack.index >= 1)
        {
            long long a, b;
            a = stack.s[stack.index];
            b = stack.s[stack.index - 1];
            stack.s[stack.index] = 0;
            stack.index--;
            stack.s[stack.index] = a * b;
            return;
        }
    if (strcmp(s, "DIV") == 0)
        if(stack.index >= 1)
        {
            long long a, b;
            a = stack.s[stack.index];
            b = stack.s[stack.index - 1];
            stack.s[stack.index] = 0;
            stack.index--;
            stack.s[stack.index] = a / b;
            return;
        }
    if (strcmp(s, "MAX") == 0)
        if(stack.index >= 1)
        {
            long long a, b;
            a = stack.s[stack.index];
            b = stack.s[stack.index - 1];
            stack.s[stack.index] = 0;
            stack.index--;
            stack.s[stack.index] = fmax(a, b);
            return;
        }
    if (strcmp(s, "MIN") == 0)
        if(stack.index >= 1)
        {
            long long a, b;
            a = stack.s[stack.index];
            b = stack.s[stack.index - 1];
            stack.s[stack.index] = 0;
            stack.index--;
            stack.s[stack.index] = fmin(a, b);
            return;
        }
    if (strcmp(s, "NEG") == 0)
        if(stack.index >= 0)
        {
            stack.s[stack.index] *= -1;
            return;
        }
    if (strcmp(s, "DUP") == 0)
        if(stack.index >= 0)
        {
            long long x;
            x = stack.s[stack.index];
            stack.index++;
            stack.s[stack.index] = x;
            return;
        }
    if (strcmp(s, "SWAP") == 0)
        if(stack.index >= 1)
        {
            long long t;
            t = stack.s[stack.index];
            stack.s[stack.index] = stack.s[stack.index - 1];
            stack.s[stack.index - 1] = t;
            return;
        }
    return;
}

int main()
{
    stack.size = 1000000;
    stack.index = -1;
    stack.s = (long long*)calloc(stack.size, sizeof(long long));
    char com[6];
    scanf("%s", com);
    while (strcmp(com, "END") != 0)
    {
        stackmachine(com);
        scanf("%s", com);
    }
    if (stack.index != -1)
        printf("%lld", stack.s[stack.index]);
    free(stack.s);
    return 0;
}
