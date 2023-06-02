#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <graphics.h>
#include <unistd.h>
#include "rbt.h"

rbt *rbt_init()
{
    rbt *tree = malloc(sizeof(rbt));
    if (!tree)
    {
        printf("Ошибка выделения памяти.\n");
        exit(-1);
    }

    tree->root = NULL;
    return tree;
}

void free_node(node *n)
{
    if (!n) return;

    free_node(n->left);
    free_node(n->right);

    free(n);
}

void rbt_free(rbt *t)
{
    free_node(t->root);
    free(t);
}

node *rbt_search(rbt *t, int key)
{
    node *x = t->root;

    while (x)
    {
        if (key < x->key) x = x->left;
        else if (key > x->key) x = x->right;
        else return x;
    }

    return NULL;
}

node *rbt_min(node *t)
{
    node *x = t;
    if (!x) return NULL;
    while (x->left) x = x->left;
    return x;
}

node *rbt_max(node *t)
{
    node *x = t;
    if (!x) return NULL;
    while (x->right) x = x->right;
    return x;
}


void rbt_rotate_left (rbt *t, node *x)
{
    node *y = x->right;
    assert(y);


    x->right = y->left;
    if (y->left)
        y->left->parent = x;

    if (!x->parent)
        t->root = y;
    else
    {
        if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;

    }
    y->parent = x->parent;

    y->left = x;
    x->parent = y;

//    printf("left\n");
    rbt_draw(t);
}

void rbt_rotate_right (rbt *t, node *x)
{
    node *y = x->left;
    assert(y);


    x->left = y->right;
    if (y->right)
        y->right->parent = x;

    if (!x->parent)
        t->root = y;
    else
    {
        if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;

    }
    y->parent = x->parent;

    y->right = x;
    x->parent = y;

//    printf("right\n");
    rbt_draw(t);
}

node *rbt_bst_insert(rbt *t, int key)
{
    node *y = NULL, *x = t->root,
            *z = malloc(sizeof(node));
    if (!z)
    {
        printf("Ошибка выделения памяти.\n");
        exit(-1);
    }

    z->key = key;
    z->color = 0;
    z->left = z->right = NULL;
    z->is_nil = 0;

    while (x)
    {
        y = x;
        if (z->key == x->key)
        {
            free(z);
            return NULL;
        }
        x = z->key < x->key ? x->left
                            : x->right;
    }

    z->parent = y;
    if (!y)
        t->root = z;
    else
    {
        if (z->key < y->key)
            y->left = z;
        else
            y->right = z;
    }

    rbt_draw(t);

    return z;
}

int rbt_insert(rbt *t, int key)
{
    node *x = rbt_bst_insert(t, key);
    if (!x)
    {
        printf("В дереве уже есть такой элемент.\n");
        return -1;
    }

    while (x != t->root && x->parent->color == 0)
    {

        node *y = x->parent == x->parent->parent->left ? x->parent->parent->right
                                                          : x->parent->parent->left;

        if (y && y->color == 0)
        {
            x->parent->color = 1;
            y->color = 1;
            x->parent->parent->color = 0;
            x = x->parent->parent;
        }
        else
        {
            if (x->parent == x->parent->parent->left && x == x->parent->right)
            {
                x = x->parent;
                rbt_rotate_left(t, x);
            }
            else if (x->parent == x->parent->parent->right && x == x->parent->left)
            {
                x = x->parent;
                rbt_rotate_right(t, x);
            }

            x->parent->color         = 1;
            x->parent->parent->color = 0;

            x == x->parent->left ? rbt_rotate_right(t, x->parent->parent) : rbt_rotate_left (t, x->parent->parent);
        }
    }

    t->root->color = 1;

    rbt_draw(t);

    return 0;
}

int rbt_delete(rbt *t, int key)
{
    node *x, *y, *z = t->root, *n = NULL;

    while (z && z->key != key)
        z = key < z->key ? z->left
                         : z->right;

    if (!z)
    {
        printf("В дереве нет такого элмента.\n");
        return -1;
    }

    if (z->left && z->right)
    {
        y = rbt_max(z->left);
        z->key = y->key;
    }
    else y = z;

    x = y->left ? y->left : y->right;

    if (!x)
    {
        n = malloc(sizeof(node));
        if (!n)
        {
            printf("Ошибка выделения памяти.\n");
            exit(-1);
        }
        n->color = 1;
        n->is_nil = 1;
        x = n;
    }

    x->parent = y->parent;

    if (!y->parent) t->root = x;
    else if (y == y->parent->left) y->parent->left = x;
    else y->parent->right = x;

//    printf("a\n");

    if (y->color == 1)
    {
        if (x->color == 0) x->color = 1;
        else
        {
//            printf("a\n");
            delete_case1(t, x);
        }
    }

    free(y);

    rbt_draw(t);

    if (n)
    {
        if (n == t->root)
            t->root = NULL;
        else
        {
            if (n == n->parent->left)
                n->parent->left = NULL;
            else
                n->parent->right = NULL;
        }
        free(n);
    }

    return 0;
}

void rbt_print(const node *t)
{
    if (t)
    {
        rbt_print(t->left);

        printf ("%d (%s, ", t->key, t->color == 0 ? "RED" : "BLACK");
        if (t->parent) printf("parent = %d) ", t->parent->key);
        else printf("root) ");

        rbt_print(t->right);

        printf("\n");
    }
}

int rbt_draw_node(node *to_draw, int x, int y, int shift)
{
    if (!to_draw) return -1;
    if (to_draw->is_nil) return -1;

    char key[5];
    itoa(to_draw->key, key, 10);
    int color = to_draw->color == 0 ? RED : BLACK;
    int y_l = y + 60, y_r = y + 60, x_l = x - shift, x_r = x + shift;

    setfillstyle(1, color);
    fillellipse(x, y, 20, 20);

    setcolor(15);
    outtextxy(x - 10, y - 10, key);
    setcolor(0);

    if (!rbt_draw_node(to_draw->left, x_l, y_l, (int) (shift * 0.75))) line(x - 10, y + 10, x_l + 10, y_l + 10);
    if (!rbt_draw_node(to_draw->right, x_r, y_r, (int) (shift * 0.75))) line(x + 10, y + 10, x_r - 10, y_r + 10);

    return 0;
}

void rbt_draw(rbt *t)
{
//    rbt_print(t->root);

    cleardevice();
    rbt_draw_node(t->root, 600, 40, 200);
    sleep(1);
}

void delete_case1(rbt *t, node *n)
{
    if (n->parent != NULL)
        delete_case2(t, n);
}

void delete_case2(rbt *t, node *n)
{
    node *s = brother(n);

//    printf("a\n");

	if (s->color == 0)
    {
		n->parent->color = 0;
		s->color = 1;

		rbt_draw(t);

		if (n == n->parent->left) rbt_rotate_left(t, n->parent);
		else rbt_rotate_right(t, n->parent);
	}
	delete_case3(t, n);
}

void delete_case3(rbt *t, node *n)
{
    node *s = brother(n);

//    printf("a\n");

	if (n->parent->color == 1 && s->color == 1 && nil_or_black(s->left) && nil_or_black(s->right))
    {
		s->color = 0;

		rbt_draw(t);

		delete_case1(t, n->parent);
	}
	else delete_case4(t, n);
}

void delete_case4(rbt *t, node *n)
{
    struct node *s = brother(n);

//    printf("%d\n", s->key);

	if (n->parent->color == 0 && s->color == 1 && nil_or_black(s->left) && nil_or_black(s->right))
    {
//		printf("a\n");

		s->color = 0;
		n->parent->color = 1;

//		printf("a\n");

		rbt_draw(t);
	}
	else delete_case5(t, n);
}

void delete_case5(rbt *t, node *n)
{
    node *s = brother(n);

//    printf("a\n");

	if  (s->color == 1)
    {
		if (n == n->parent->left && s->right->color == 1 && s->left->color == 0)
        {
			s->color = 0;
			s->left->color = 1;

			rbt_draw(t);

			rbt_rotate_right(t, s);
		}
		else if (n == n->parent->right && s->left->color == 1 && s->right->color == 0)
        {
			s->color = 0;
			s->right->color = 1;

			rbt_draw(t);

			rbt_rotate_left(t, s);
		}
	}
	delete_case6(t, n);
}

void delete_case6(rbt *t, node *n)
{
    node *s = brother(n);

//    printf("a\n");

	s->color = n->parent->color;
    n->parent->color = 1;

    rbt_draw(t);

	if (n == n->parent->left)
    {
        s->right->color = 1;

        rbt_draw(t);

		rbt_rotate_left(t, n->parent);
	}
	else
    {
		s->left->color = 1;

		rbt_draw(t);

		rbt_rotate_right(t, n->parent);
	}
}

node *brother(node *n)
{
    return n == n->parent->left ? n->parent->right : n->parent->left;
}

int nil_or_black(node *n)
{
    if (!n) return 1;
    else return n->color;
}
