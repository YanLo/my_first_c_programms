#include <stdio.h>
#include <stdlib.h>

typedef int data_t;

typedef struct Node
{
    struct Node* next;
    data_t val;
} node_t, *list_t;

//typedef struct Node node_t;
//typedef struct Node * list_t;

list_t list_create();

void push(list_t* headp, data_t x);

data_t pop(list_t* headp);

void print_list(list_t head);

int list_is_empty(list_t head);

void destroy_list(list_t* head);

data_t computer_postfix(list_t* headp);

int main()
{
    list_t head = list_create();

    int i;
    for (i = 0; i < 10; i++)
        push(&head, i);
    print_list_queue(head);
    destroy_list(&head);
    printf("%d ", list_is_empty(head));
    return 0;
}

list_t list_create()
{
    return NULL;
}

void push(list_t* headp, data_t x)
{
    list_t head = (list_t) calloc(1, sizeof(node_t));
    head->next = *headp;
    head->val = x;
    *headp = head;
}

data_t pop(list_t* headp)
{
    if (!(*headp))
        return;
    list_t temp_head = *headp;
    data_t pop_data = temp_head->val;
    *headp = temp_head->next;
    free(temp_head);
    return pop_data;
}

void print_list(list_t node)
{
    if (node != NULL)
    {
        printf("%d ", node->val);
        print_list(node->next);
    }
}

void print_list_queue(list_t node)
{
    if (node->next != NULL)
    {
        print_list_queue(node->next);
        printf("%d ", node->val);
    }
}

int list_is_empty(list_t head)
{
    return head == NULL;
}

void destroy_list(list_t* head)
{
    list_t tempp = *head;
    list_t node_free;
    while (tempp != NULL)
    {
        node_free = tempp;
        tempp = tempp->next;
        free(node_free);
    }
    *head = NULL;
}

data_t computer_postfix(list_t* headp)
{
    printf("Please, enter postfix expression, ends with '='\n");
    char c;
    while ( (c = getchar()) != '=')
        switch (c)
        {
        case '+':
            push(headp, pop(headp) + pop(headp));
            break;
        case '-':
            push(headp, - pop(headp) + pop(headp));
            break;
        case '*':
            push(headp, pop(headp) * pop(headp));
            break;
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
            push(headp, c - '0');
            break;
        case '\n': case ' ':
            break;
        default:
            printf("Wrong expression: the are not only digits and operations\n");
            return;
        }
    int res = pop(headp);
    if (!list_is_empty(*headp))
    {
        printf("Wrong expression\n");
        return;
    }
    else
        return res;
}
