#include <stdio.h>

union Int32 {
    int x;
    unsigned char bytes[4];
};

void radixsort(union Int32 *mas, int n) 
{
    union Int32 mas_res[n];
    int b, c, t;
    for (int i = 0; i < 4; i++) 
    {
        int a[256] = {0};
        for (int j = 0; j < n; j++) 
        {
            if (i == 3) 
                if (mas[j].bytes[i] >= 128) 
                    b = mas[j].bytes[i] - 128;
                else 
                    b = mas[j].bytes[i] + 128;
            else 
                b = mas[j].bytes[i];
            a[b]++;
        }
        int d = a[0];
        a[0] = 0;
        for (int j = 1; j < 256; j++) 
        {
            t = a[j];
            a[j] = d;
            d += t;
        }
        for (int j = 0; j < n; j++) {
            if (i == 3) 
                if (mas[j].bytes[i] > 127) 
                    c = mas[j].bytes[i] - 128;
                else 
                    c = mas[j].bytes[i] + 128;
            else 
                c = mas[j].bytes[i];
            mas_res[a[c]++] = mas[j];
        }
        for (int j = 0; j < n; j++)
            mas[j] = mas_res[j];
    }
}

int main() 
{
    int n;
    scanf("%d", &n);
    union Int32 mas[n];
    for (int i = 0; i < n; i++) 
        scanf("%d", &mas[i].x);
    radixsort(mas, n);
    for (int i = 0; i < n; i++) 
        printf("%d ", mas[i].x);
    return 0;
}
