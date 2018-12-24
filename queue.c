#include <stdio.h>
#include <stdlib.h>

typedef int data_t;

typedef struct Qnode
{
    data_t val;
    struct Qnode * next;
} node_t;

typedef struct Queue
{
    node_t* firs;
    node_t* last;
} queue_t;

node_t* create_list();

void push(node_t** headp, data_t x);

data_t pop(node_t** headp);

void print_list_stack(node_t* head);

void print_list_queue(node_t* head);

int list_is_empty(node_t* head);

node_t* create_node(data_t x);

queue_t* create_queue(data_t x);

void queue_push(queue_t* queue, data_t x);

data_t queue_pop(queue_t* queue);

int queue_is_empty(queue_t* queue);

int main()
{
    queue_t* queue = create_queue(1);

    int i;
    for ( i = 2; i <= 10; i++)
        queue_push(queue, i);

    for ( i = 1; i <= 10; i++)
    printf("%d ", queue_pop(queue));

    printf("%d\n", queue_is_empty(queue));

    return 0;
}

node_t* create_list()
{
    return NULL;
}

void push(node_t** headp, data_t x)
{
    node_t* head = (node_t*) calloc(1, sizeof(node_t));
    head->next = *headp;
    head->val = x;
    *headp = head;
}

data_t pop(node_t** headp)
{
    if (!(*headp))
        return;
    node_t* temp_head = *headp;
    data_t pop_data = temp_head->val;
    *headp = temp_head->next;
    free(temp_head);
    return pop_data;
}

void print_list_stack(node_t* node)
{
    if (node != NULL)
    {
        printf("%d ", node->val);
        print_list_stack(node->next);
    }
}

void print_list_queue(node_t* node)
{
    if (node != NULL)
    {
        print_list_queue(node->next);
        printf("%d ", node->val);
    }
}

int list_is_empty(node_t* head)
{
    return head == NULL;
}

int queue_is_empty(queue_t* queue)
{
    return queue->firs == NULL;
}

node_t* create_node(data_t x)
{
    node_t* nodep = (node_t*) calloc(1, sizeof(node_t));
    nodep->next = NULL;
    nodep->val = x;
    return nodep;
}

queue_t* create_queue(data_t x)
{
    queue_t* quep = (queue_t*) calloc(1, sizeof(queue_t));
    node_t* first_node = create_node(x);
    quep->firs = quep->last = first_node;
    return quep;
}

void queue_push(queue_t* quep, data_t x)
{
    if (quep->firs == NULL)
    {
        node_t* first_node = create_node(x);
        quep->firs = quep->last = first_node;
    }
    else
    {
        node_t* last_node = create_node(x);
        quep->last->next = last_node;
        quep->last = last_node;
    }
}

data_t queue_pop(queue_t* quep)
{
    return pop(&queue->firs);
}
