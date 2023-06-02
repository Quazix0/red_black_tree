#ifndef RBT_H_INCLUDED
#define RBT_H_INCLUDED

typedef struct node {
    int key; /// значение
    int color; /// 0 - красный, 1 - чёрный
    struct node *left, *right, *parent; /// указатели на детей и родителя
} node;

typedef struct rbt {
    node *root; /// указатель на корень
} rbt;

rbt *rbt_init();
/// инициализирует дерево, возвращает указатель на него

void free_node(node *n);
/// уничтожает узел и его поддеревья, освобождает соответствующую им память

void rbt_free(rbt *t);
/// уничтожает дерево и освобождает память

node *rbt_serach (rbt *t, int key);
/// находит элемент с заданным ключом и возвращает указатель на него, NULL если отсутсвует

node *rbt_min (rbt *t);
/// возвращает указатель на минимальный элемент

node *rbt_max (rbt *t);
/// возвращает указатель на максимальный элемент

void rbt_rotate_left (rbt *t, node *x);
/// левое вращение вокруг элемента x

void rbt_rotate_right (rbt *t, node *x);
/// правое вращение вокруг элемента x

node *rbt_bst_insert (rbt *t, int key);
/// вставка элемента без учёта красно-чёрных св-в, возвращает указатель на вставленный элемент

int rbt_insert (rbt *t, int key);
/// вставка элемента в дерево, возвращает 0 в случае успеха, -1 если элемент уже есть

int rbt_delete (rbt *t, int key);
/// удаления элемента дерева, возвращает 0 в случае успеха, -1 если элемент отстутсвует

void rbt_print(const node *t);
/// выводит в консоль элементы дерева в порядке возрастания с указанием цвета и родителя

int rbt_draw_node(node *to_draw, int x, int y, int iter);
/// функция отрисовки поддерева начиная с текущего узла, возвращает 0 если узел существует, иначе -1

void rbt_draw(rbt *t);
/// функция отрисовки дерева в графическом окне

#endif // RBT_H_INCLUDED
