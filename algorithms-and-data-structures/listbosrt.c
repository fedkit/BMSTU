#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Elem
{
    struct Elem *next;
    char *word;
};

struct Elem *bsort(struct Elem *list)
{
    struct Elem *end = NULL;
    while (end != list)
    {
        struct Elem *dop_list = list;
        while (dop_list->next != end)
        {
            if (strlen(dop_list->word) > strlen(dop_list->next->word))
            {
                char *t = dop_list->word;
                dop_list->word = dop_list->next->word;
                dop_list->next->word = t;
            }
            dop_list = dop_list->next;
        }
        end = dop_list;
    }
    return list;
}

struct Word
{
    char word[1000];
    int i;
    int len;
};

int next_word(char *s, struct Word *w)
{
    while (s[w->i] == ' ')
        w->i++;
    if (s[w->i] == '\n')
        return 0;
    else
    {
        int k = 0;
        while ((s[w->i] != ' ') && (s[w->i] != '\n'))
            w->word[k++] = s[w->i++];
        w->word[k] = '\0';
        return 1;
    }
}

int main()
{
    char s[1000];
    fgets(s, sizeof(s), stdin);
    struct Elem *list = NULL;
    struct Word w;
    w.i = 0;
    struct Elem *prev = NULL;
    while (next_word(s, &w))
    {
        struct Elem *n = malloc(sizeof(struct Elem));
        if (n == NULL) 
        {
            fprintf(stderr, "ERROR\n");
            return 1;
        }
        n->word = malloc((strlen(w.word) + 1) * sizeof(char));
        if (n->word == NULL) 
        {
            fprintf(stderr, "ERROR\n");
            return 1;
        }
        strcpy(n->word, w.word);
        n->next = NULL;
        if (prev == NULL)
            list = n;
        else
            prev->next = n;
        prev = n;
    }
    list = bsort(list);
    while (list != NULL)
    {
        printf("%s ", list->word);
        struct Elem *next = list->next;
        free(list->word);
        free(list);
        list = next;
    }
    return 0;
}

