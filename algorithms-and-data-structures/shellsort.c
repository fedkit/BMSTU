void shellsort(unsigned long nel,
        int (*compare)(unsigned long i, unsigned long j),
        void (*swap)(unsigned long i, unsigned long j))
{ 
    unsigned long d; 
    long long fib[nel + 1], s, k; 
    fib[0] = 1; 
    fib[1] = 1; 
    s = 2;
    while (fib[s - 1] + fib[s - 2] <= nel) 
    { 
        fib[s] = fib[s - 1] + fib[s - 2]; 
        s++; 
    } 
    for (long long i = s - 1; i >= 1; i--) 
    { 
        d = fib[i]; 
        for (long long j = d; j < nel; j++)
            for (long long k = j - d; (k >= 0) && (compare(k, k + d) == 1); k -= d) { 
                swap(k, k + d); 
        } 
    } 
}
