#include <stdio.h>
#include <stdlib.h>

#define N 10

typedef int Data_t;

typedef struct
{
    Data_t * data;
    int size;
    int counter;
} Stack;

Stack * stack_create(int size);
void stack_destroy(Stack * stack);
void push(Stack * stack, Data_t data);
Data_t pop(Stack * stack);
void print_stack(Stack * stack);

int main()
{
    Stack * comp;
    comp = stack_create(N);
    int x;
    while ((x = getchar()) != '=')
    {
        switch (x)
        {
        case ' ':
            break;
        case '+':
            push(comp, pop(comp) + pop(comp));
            break;
        case '-':
            {
                Data_t y = pop(comp) - pop(comp);
                push(comp, -y);
                break;
            }
        case '*':
            push(comp, pop(comp) * pop(comp));
            break;
        default:
            push(comp, x - '0');
        }
    }
    printf("%d", comp->data[comp->counter - 1]);
    stack_destroy(comp);

    return 0;
}

Stack * stack_create(int size)
{
    Stack * stack;
    stack = calloc(1, sizeof(Stack));
    stack->data = (Data_t *) calloc(N, sizeof(Data_t));
    stack->counter = 0;
    stack->size = size;
    return stack;
}

void stack_destroy(Stack * stack)
{
    free(stack->data);
    free(stack);
}

void push(Stack * stack, Data_t data)
{
    if (stack->counter >= stack->size)
        stack->data = realloc(stack->data, (stack->size += N) * sizeof(Data_t));
    stack->data[stack->counter++] = data;
}

Data_t pop(Stack * stack)
{
    if (stack->counter > 0)
        return stack->data[--stack->counter];
    else
        return -10;
}

void print_stack(Stack * stack)
{
    int n = stack->counter;
    if (n > 0)
        while (n > 0)
            printf("%d ", stack->data[--n]);
    else
        printf("Stack is empty");
}
