#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Entry 
{
    int i;
    int v;
    struct Entry* next;
} Entry;

typedef struct 
{
    Entry* entries[10000];
} Hashtable;

Hashtable hashtable; 

int hash(int key) 
{
    return key % 10000;
}

void disparray(char *s) 
{
    int i, v;
    if (strcmp(s, "ASSIGN") == 0) 
    {
        scanf("%d%d", &i, &v);
        int h = hash(i);
        Entry* cur = hashtable.entries[h];
        Entry* prev = NULL;
        while ((cur != NULL) && (cur->i != i)) 
        {
            prev = cur;
            cur = cur->next;
        }
        if (cur != NULL) 
        {
            if (v != 0) 
            {
                cur->v = v;
            } 
            else 
            if (v == 0) 
            {
                cur->v = v;
                if (prev == NULL)
                    hashtable.entries[h] = cur->next;
                else
                    prev->next = cur->next;
            free(cur);
            }
        }
        Entry* newEntry = (Entry*)malloc(sizeof(Entry));
            newEntry->i = i;
            newEntry->v = v;
            newEntry->next = hashtable.entries[h];
            hashtable.entries[h] = newEntry;
        return;
    } 
    if (strcmp(s, "AT") == 0) 
    {
        int h;
        scanf("%d", &i);
        h = hash(i);
        Entry* entry = hashtable.entries[h];
        while ((entry != NULL) && (entry->i != i)) 
            entry = entry->next;
        if ((entry != NULL) && (entry != 0)) 
            printf("%d\n", entry->v);
        else 
            printf("%d\n", 0);
        return; 
    }
    return;
}

int main() 
{
    char s[7];
    for (int i = 0; i < 10000; i++)
        hashtable.entries[i] = NULL;
    scanf("%s", s);
    while (strcmp(s, "END") != 0) 
    {
        disparray(s);
        scanf("%s", s);
    }
    for (int i = 0; i < 10000; i++) 
    {
        Entry* current = hashtable.entries[i];
        while (current != NULL) 
        {
            Entry* temp = current;
            current = current->next;
            free(temp);
        }
    }
    return 0;
}
