#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <wchar.h>

int maxarray(void *base, size_t nel, size_t width,
             int (*compare)(void *a, void *b)) 
{
    char *ind = (char*)base; 
    //присваиваем макс элементу первый элемент и итог индексу 0
    int max = 0;
    for (size_t i = 0; i < nel; i++) //перебираем элементы массива
        //определяем тек элемент
        if (compare(ind + i * width, ind + max * width) > 0) //если оны больше тек макс, то
            max = i; //запоминаем новый индекс
    return max; //выводим итоговый индекс
}
