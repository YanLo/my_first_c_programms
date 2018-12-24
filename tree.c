#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef int Data;

struct Node
{
    Data val;
    int count ;
    struct Node * right;
    struct Node * left;
};



void tree_print(struct Node * tree);

void tree_print1(struct Node * tree);

int tree_balance(struct Node * tree, int * balance);

int tree_count_leaves(struct Node * tree);

void print_leaves(struct Node * tree);

int tree_count_node(struct Node * tree);

int tree_depth(struct Node * tree);

struct Node * tree_add(struct Node * tree, Data x);

struct Node * tree_add1(struct Node * tree, Data x);

void tree_destroy(struct Node * tree);

int main()
{
    struct Node * tree = NULL;

    int n;
    scanf("%d", &n);
    while ( n != 0)
    {
        tree = tree_add1(tree, n);
        scanf("%d", &n);
    }
    int balance;
    int x = tree_balance(tree, &balance);
    if ( balance )
        printf("Yes");
    else
        printf("No");
    tree_destroy(tree);
    return 0;
}

void tree_print(struct Node * tree)
{
    if (tree != NULL)
    {
        tree_print(tree->left);
        printf("%d ",tree->val);
        tree_print(tree->right);
    }

}

void tree_print1(struct Node * tree)
{
    if (tree != NULL)
    {
        tree_print1(tree->left);
        printf("%d %d\n",tree->val, tree->count);
        tree_print1(tree->right);
    }

}

int tree_count_leaves(struct Node * tree)
{
    int k = 0;
    if (tree != NULL)
    {
        k += tree_count_leaves(tree->left);
        if ( (tree->left == NULL) && (tree->right == NULL) )
            k++;
        k += tree_count_leaves(tree->right);
    }
    return k;
}

struct Node * tree_add(struct Node * tree, Data x)
{
    if (tree == NULL)
    {
        tree = malloc(sizeof(struct Node));
        tree->val = x;
        tree->left = tree->right = NULL;
    }
    else if (x < tree->val)
        tree->left = tree_add(tree->left, x);
    else if ( x > tree->val)
        tree->right = tree_add(tree->right, x);
    return tree;
}

struct Node * tree_add1(struct Node * tree, Data x)
{
    if (tree == NULL)
    {
        tree = malloc(sizeof(struct Node));
        tree->val = x;
        tree->count = 1;
        tree->left = tree->right = NULL;
    }
    else if (x < tree->val)
        tree->left = tree_add1(tree->left, x);
    else if ( x > tree->val)
        tree->right = tree_add1(tree->right, x);
    else if (x == tree->val)
        tree->count++;
    return tree;
}

void tree_destroy(struct Node * tree)
{
    if (tree != NULL)
    {
        tree_destroy(tree->left);
        tree_destroy(tree->right);
        free(tree);
    }

}

int tree_depth(struct Node * tree)
{
    if (tree == NULL)
        return 0;
    if ( (tree->left == NULL) && (tree->right == NULL) )
        return 1;
    int depth_left = tree_depth(tree->left);
    int depth_right = tree_depth(tree->right);
    return (depth_left > depth_right ? depth_left : depth_right) + 1;
}

int tree_count_node(struct Node * tree)
{
    if (tree == NULL)
        return 0;
    int count_left = tree_count_node(tree->left);
    int count_right = tree_count_node(tree->right);
    return count_left + count_right + 1;
}

void print_leaves(struct Node * tree)
{
    if (tree != NULL)
    {
        print_leaves(tree->left);
        if ((tree->left == NULL) && (tree->right) == NULL)
            printf("%d ", tree->val);
        print_leaves(tree->right);
    }
}

int tree_balance(struct Node * tree, int * balance)
{
    if (tree == NULL)
    {
        *balance = 1;
        return 0;
    }
    int balance_left, balance_right;
    int depth_left, depth_right;
    depth_left = tree_balance(tree->left, &balance_left);
    depth_right = tree_balance(tree->right, &balance_right);
    if ((fabs(depth_left - depth_right) <= 1) && balance_left && balance_right )
        *balance = 1;
    else
        *balance = 0;
    return (depth_left > depth_right ? depth_left : depth_right) + 1;
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
