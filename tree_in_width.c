#include <stdio.h>
#include <stdlib.h>

typedef int data_t;

typedef struct Tnode
{
    data_t val;
    struct Tnode * right;
    struct Tnode * left;
} tnode_t;

typedef struct Qnode
{
    tnode_t* tnodep;
    struct Qnode * next;
} node_t;

typedef struct Queue
{
    node_t* firs;
    node_t* last;
} queue_t;

tnode_t* create_tree();

tnode_t* tree_add(tnode_t * tree, data_t x);

void tree_destroy(tnode_t * tree);

node_t* create_node(tnode_t* tnodep);

queue_t* create_queue(tnode_t* tnodep);

void queue_push(queue_t* quep, tnode_t* tnodep);

tnode_t* pop(node_t** headp);

tnode_t* queue_pop(queue_t* queue);

int queue_is_empty(queue_t* queue);

void tree_print_in_width(tnode_t* root);

int main()
{
    tnode_t* root = create_tree();

    data_t temp;
    scanf("%d", &temp);
    while ( temp != 0)
    {
        root = tree_add(root, temp);
        scanf("%d", &temp);
    }

    tree_print_in_width(root);
    tree_destroy(root);
    return 0;
}

tnode_t* create_tree()
{
    return NULL;
}

tnode_t * tree_add(tnode_t * tree, data_t x)
{
    if (tree == NULL)
    {
        tree = malloc(sizeof(tnode_t));
        tree->val = x;
        tree->left = tree->right = NULL;
    }
    else if (x < tree->val)
        tree->left = tree_add(tree->left, x);
    else if ( x > tree->val)
        tree->right = tree_add(tree->right, x);
    return tree;
}

void tree_destroy(tnode_t * tree)
{
    if (tree != NULL)
    {
        tree_destroy(tree->left);
        tree_destroy(tree->right);
        free(tree);
    }
}

int queue_is_empty(queue_t* queue)
{
    return queue->firs == NULL;
}

node_t* create_node(tnode_t* tnodep)
{
    node_t* nodep = (node_t*) calloc(1, sizeof(node_t));
    nodep->next = NULL;
    nodep->tnodep = tnodep;
    return nodep;
}

queue_t* create_queue(tnode_t* tnodep)
{
    queue_t* quep = (queue_t*) calloc(1, sizeof(queue_t));
    node_t* first_node = create_node(tnodep);
    quep->firs = quep->last = first_node;
    return quep;
}

void queue_push(queue_t* quep, tnode_t* tnodep)
{
    if (quep->firs == NULL)
    {
        node_t* first_node = create_node(tnodep);
        quep->firs = quep->last = first_node;
    }
    else
    {
        node_t* last_node = create_node(tnodep);
        quep->last->next = last_node;
        quep->last = last_node;
    }
}

tnode_t* queue_pop(queue_t* quep)
{
    return pop(&quep->firs);
}

tnode_t* pop(node_t** headp)
{
    if (!(*headp))
        return;
    node_t* temp_head = *headp;
    tnode_t* pop_data = temp_head->tnodep;
    *headp = temp_head->next;
    free(temp_head);
    return pop_data;
}

void tree_print_in_width(tnode_t* root)
{
    queue_t* queue = create_queue(root);
    tnode_t* tempp;
    while (!queue_is_empty(queue))
    {
        tempp = queue_pop(queue);
        printf("%d ", tempp->val);
        if (tempp->left)
            queue_push(queue, tempp->left);
        if (tempp->right)
            queue_push(queue, tempp->right);
    }
    free(queue);
}

int tree_search(Tree* t, const char* value, tree_search_cb cb, void* data)
{
	if ( t )
	{
		int cmp = strcmp(value, t->value);
		if(cmp == 0)
		{
			cb(t->value, data);
			return tree_search(t->left, value, cb, data);
		} else if (cmp < 0) {
			return tree_search(t->left, value, cb, data);
		} else {
			return tree_search(t->right, value, cb, data);
		}
	}
	return 0;
}
