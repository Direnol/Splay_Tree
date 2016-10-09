#ifndef SPLAY_H
#define SPLAY_H

#include <stdio.h>
#include <stdlib.h>

#define l_child 1
#define r_child 0

typedef int Data;
typedef int (*Comparator) (Data left, Data right);

typedef struct splay_node {
    struct splay_node *left, *right, *parent;
    Data data;
} splay_node;

typedef struct splay_tree {
    splay_node *root;
    Comparator comp;
    int size;
} splay_tree;

splay_tree *splayT_new_tree(Comparator);
splay_node *splayT_insert(splay_tree *tree, Data data);
splay_node *splayT_find(splay_tree *tree, Data data);
splay_node *new_node(Data data);
splay_node* splayT_min(splay_node *node);
splay_node* splayT_max(splay_node *node);
void *splay(splay_tree *tree, splay_node *x);
void *splayT_delete(splay_tree *tree, Data data);
int compare_int(Data l, Data r);
void rotate(splay_node *child);
void zig(splay_node * x);
void zigzig(splay_node * x, splay_node *p);
void zigzag(splay_node * x);
void mark_gp(splay_node *child);
void delete_hint(splay_tree *tree, splay_node *node);
void tree_print_dfs(splay_node *tree, int indent, int width);
void splayT_free_tree(splay_tree *tree);

#endif
