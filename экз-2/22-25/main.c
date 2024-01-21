#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define OK 0
#define ERR 1

// Функции динамического выделения памяти
#if OK == ERR
Узел (элемент списка) – единица хранения данных, несущая в себе ссылки на связанные с ней узлы.
Узел обычно состоит из двух частей
• информационная часть (данные);
• ссылочная часть (связь с другими узлами).

Дерево — это связный ациклический граф.
Двоичным деревом поиска называют дерево, все вершины которого упорядочены, каждая вершина имеет не более двух потомков (назовём их левым и правым),
и все вершины, кроме корня, имеют родителя.

Алгоритм удаления узла из дерева:
- Находим узел с данным значением
- Если у него отсутсвуют левое и правое поддеревья - освобождаем память из под узла
- Если у него есть только левое поддерево - заменяем данный элемент на левого соседа и освобождаем память
- Аналогично, если есть только правое поддерево
- Если есть оба поддерева, то необходимо сначала поменять местами данный элемент и минимальный из правого поддерева,
затем освободить память из под узла, вставшего на место минимального в правом поддерева 

Как освободить память из под всего дерева?
- Удалять память из под каждого узла в ходе post-order обхода

DOT - язык описания графов.
Граф, описанный на языке DOT, обычно представляет собой текстовый файл с расширением .gv  в понятном для человека и обрабатывающей программы формате.
В графическом виде графы, описанные на языке DOT, представляются с помощью специальных программ, например Graphviz.
// Описание дерева на DOT
digraph test_tree {
f -> b;
f -> k;
b -> a;
b -> d;
k -> g;
k -> l;
}
// Оформление на странице Trac
{{{
#!graphviz
digraph test_tree {
f -> b;
f -> k;
b -> a;
b -> d;
k -> g;
k -> l;
}
}}}
void to_dot(struct tree_node *tree, void *param)
{
    FILE *f = param;
    if (tree->left)
        fprintf(f, "%s -> %s;\n", tree->name, tree->left->name);
    if (tree->right)
        fprintf(f, "%s -> %s;\n", tree->name, tree->right->name);
}
void export_to_dot(FILE *f, const char *tree_name, struct tree_node *tree)
{
    fprintf(f, "digraph %s {\n", tree_name);
    apply_pre(tree, to_dot, f);
    fprintf(f, "}\n");
}
#endif

#ifdef OK // Функции
typedef struct tree_node
{
    int data;
    // меньшие
    struct tree_node *left;
    // большие
    struct tree_node *right;
} tree_t;

// Добавление элемента.
tree_t *create_node(int data)
{
    tree_t *node = malloc(sizeof(tree_t));
    if (node)
    {
        node->data = data;
        node->left = NULL;
        node->right = NULL;
    }
    return node;
}

tree_t *insert(tree_t *tree, tree_t *node)
{
    int cmp;
    if (tree == NULL)
        return node;
    cmp = node->data - tree->data;
    if (cmp == 0)
        assert(0);
    else if (cmp < 0)
        tree->left = insert(tree->left, node);
    else
        tree->right = insert(tree->right, node);
    return tree;
}
tree_t *lookup_1(tree_t *tree, int data)
{
    int cmp;
    if (tree == NULL)
        return NULL;
    cmp = data - tree->data;
    if (cmp == 0)
        return tree;
    else if (cmp < 0)
        return lookup_1(tree->left, data);
    else
        return lookup_1(tree->right, data);
}

tree_t *lookup_2(tree_t *tree, int data)
{
    int cmp;
    while (tree != NULL)
    {
        cmp = data - tree->data;
        if (cmp == 0)
            return tree;
        else if (cmp < 0)
            tree = tree->left;
        else
            tree = tree->right;
    }
    return NULL;
}
/*
// Обход дерева
Прямой (pre-order)
Фланговый или поперечный (in-order)
Обратный (post-order)
*/
void apply(tree_t *tree, void (*f)(tree_t *, void *), void *arg)
{
    if (tree == NULL)
        return;
    // pre-order
    // f(tree, arg);
    apply(tree->left, f, arg);
    // in-order
    f(tree, arg);
    apply(tree->right, f, arg);
    // post-order
    // f(tree, arg);
}

void tree_free(tree_t *tree) {
    if (tree == NULL)
        return;
    tree_free(tree->left);
    tree_free(tree->right);
    free(tree);
}

// Поиск минимального элемента в дереве (нужна для удаления узла из дерева)
tree_t *findMinNode(tree_t *node)
{
    tree_t *current = node;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}
// Удаление узла из дерева
tree_t *deleteNode(tree_t *root, int value)
{
    if (root == NULL) {
        return root;
    }

    if (value < root->data) {
        root->left = deleteNode(root->left, value);
    } else if (value > root->data) {
        root->right = deleteNode(root->right, value);
    } else {
        if (root->left == NULL) {
            tree_t *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            tree_t *temp = root->left;
            free(root);
            return temp;
        }

        tree_t *temp = findMinNode(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}
#endif




int main(void)
{
    tree_t *t = create_node(6);
    tree_t *p1 = create_node(3);
    tree_t *p2 = create_node(2);
    tree_t *p3 = create_node(4);
    tree_t *p4 = create_node(8);
    tree_t *p5 = create_node(7);
    tree_t *p6 = create_node(9);
    t = insert(t, p1);
    t = insert(t, p2);
    t = insert(t, p3);
    t = insert(t, p4);
    t = insert(t, p5);
    t = insert(t, p6);

    tree_t *min = lookup_1(t, 2);
    tree_t *max = lookup_1(t, 9);
    printf("%d %d\n", min->data, max->data);
    t = deleteNode(t, 8);
    tree_free(t);
    return OK;
}