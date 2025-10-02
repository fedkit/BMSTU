#include <stdio.h>

unsigned long peak(unsigned long nel,
        int (*less)(unsigned long i, unsigned long j)) {
    if(nel == 1)
        return 0;
    if(less(0, 1) == less(1, 0) || less(1, 0) == 1)
        return 0;
    for(int i = 1; i < nel - 1; i++)
        if((less(i, i + 1) == less(i + 1, i) || less(i + 1, i) == 1) &&
            (less(i, i - 1) == less(i - 1, i) || less(i - 1, i) == 1))
            return i;
    return nel - 1;
}
