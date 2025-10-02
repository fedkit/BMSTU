unsigned long binsearch(unsigned long nel, int (*compare)(unsigned long i)) 
{
    unsigned long left = 0, right = nel - 1, k;
    if(compare(right) == -1 || compare(left) == 1)
        return nel;
    while(left <= right)
    {
        k = (right + left) / 2;
        if(compare(k) == 0)
            return k;
        else if(compare(k) == -1)
            left = k + 1;
        else
            right = k - 1;
    }
    return nel;
}
