#include <stdio.h>
#include <stdlib.h>

typedef int Data;

struct Node
{
    Data val;
    struct Node * next;
};

typedef struct Node * List;


List list_create ();
void list_push (List * plist, Data x);
Data list_pop (List * plist);
Data list_get(List list);
void list_print (List list);
int list_size(List list);
void list_clear(List * plist);

int main()
{
    List list = list_create();
    list_push(&list, 5);
    list_print(list);
    printf("%d", list_get(list));
    printf("%d", list_is_empty(list));
    list_clear(&list);

}


List list_create ()
{
    return NULL;
}

void list_push (List * plist, Data x)
{
    List newplist = calloc(1, sizeof(struct Node));
    newplist->next = *plist;
    newplist->val = x;
    *plist = newplist;
}

Data list_pop (List * plist)
{
    List templist = *plist;
    Data temp = (*plist)->val;
    *plist = (*plist)->next;
    free(templist);
    return temp;
}

Data list_get(List list)
{
    return list->val;
}

void list_print (List list)
{
    if (!list)
    {
        printf("Empty stack\n");
    }
    else
    {
        while (list != NULL)
        {
            printf("%d ", list->val);
            list = list->next;
        }
        printf("\n");
    }

}

int list_size(List list)
{
    int counter = 0;
    while (list != NULL)
    {
        counter++;
        list = list->next;
    }
    return counter;
}

void list_clear(List * plist)
{
    List list = *plist;
    while (list != NULL)
    {
        List temp = list;
        list = list->next;
        free(temp);
    }
    *plist = NULL;
}

int list_is_empty(List list)
{
    return list == NULL;
}
