#include <stddef.h>

void revarray(void *base, size_t nel, size_t width) 
{
    if(nel >= 2)
    {
        char *left = base; //делаем указатели на конец и начало массива
        char *right = left + (nel - 1) * width;
        char k;
        for(size_t i = 0; i < (nel * width / 2); i += width) //перебираем элементы по хвостам
        {
            for (size_t j = 0; j < width; j++) //меняем местами концы побитово
            {
                k = left[j];
                left[j] = right[j];
                right[j] = k;
            }
            left += width; //сокращяем хвосты
            right -= width;
        }
    }
}
