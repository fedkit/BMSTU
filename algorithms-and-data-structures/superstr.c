#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define min(a, b) a > b ? b : a

struct list{
    struct list *next;
    int val;
};

struct list *start;
int **economyTable;
int min = 10000;

int economy(char *a, char *b){
    if(strcmp(a, b) == 0)
        return strlen(b);
    int lena = strlen(a);
    for(int i = 1 ; i < lena ; i++){
        if(strncmp(a + i * sizeof(char), b, lena - i) == 0){
            return strlen(b) - lena + i;
        }
    }
    return strlen(b);
}

void minLen(int pred, int res){
    if(start->next == NULL) {
        min = min(min, res);
    }
    int i;
    struct list *temp;
    for(struct list *now = start ; now->next != NULL ; now = now->next){
        temp = now->next;
        i = temp->val;
        now->next = now->next->next;
        if (pred == -1){
            minLen(i, res + economyTable[i][i]);
        }else {
            minLen(i, res + economyTable[pred][i]);
        }
        now->next = temp;
    }
}

int main(int argc, char** argv) {
    int n;
    scanf("%d", &n);
    int *was = calloc(n, sizeof(int));
    start = malloc(sizeof(struct list));
    struct list *end = start;
    start->next = NULL;
    for(int i = 0 ; i < n ; i++){
        struct list *new = malloc(sizeof(struct list));
        new->val = i;
        new->next = NULL;
        end->next = new;
        end = new;
    }
    char *str[n];
    economyTable = calloc(n, sizeof(int*));
    for(int i = 0 ; i < n; i++){
        str[i] = calloc(1000, sizeof(char));
        economyTable[i] = calloc(n, sizeof(int));
        scanf("%s", str[i]);
        was[i] = 1;
    }

    for(int i = 0 ; i < n ; i++)
        for(int j = 0 ; j < n ; j++)
            economyTable[i][j] = economy(str[i], str[j]);
    minLen(-1, 0);
    printf("%d", min);
    for(int i = 0 ; i < n ; i++) {
        free(str[i]);
        free(economyTable[i]);
    }
    free(economyTable);
    free(was);
    while (start!=NULL){
        struct list *next = start->next;
        free(start);
        start = next;
    }
}

