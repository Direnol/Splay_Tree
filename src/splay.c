#include "splay.h"


splay_tree *splayT_new_tree(Comparator comp)
{
    splay_tree *tree = (splay_tree *) malloc(sizeof(tree));
    tree->comp = comp;
    tree->root = NULL;
    tree->size = 0;
    return tree;
}

splay_node *new_node(Data data)
{
    splay_node *node = (splay_node *) malloc(sizeof(*node));
    if (!node) return NULL;

    node->left = node->right = node->parent = NULL;
    node->data = data;

    return node;
}

splay_node *splayT_insert(splay_tree *tree, Data data)
{
    splay_node *n = new_node(data);
    if (!n) {
        perror("Can't allocation(new_node)");
        return NULL;
    }

    if (!tree->root) {
        tree->root = n;
    } else {
        splay_node *curr = tree->root;
        splay_node *parent;
        int child;
        while (curr) {
            parent = curr;
            if (tree->comp(n->data, curr->data) < 0) {
                curr = curr->left;
                child = l_child;
            } else {
                curr = curr->right;
                child = r_child;
            }
        }
        n->parent = parent;
        if (child) {
            parent->left = n;
        } else {
            parent->right = n;
        }
    }
    splay(tree, n);
    tree->size++;
    return n;
}

splay_node *splayT_find(splay_tree *tree, Data data)
{
    splay_node *curr = tree->root;
    int found = 0;

    while(curr && !found) {
        int cmp = tree->comp(data, curr->data);
        if (cmp == 0) {
            found = 1;
        } else if (cmp < 0) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }

    if (curr) {
        splay(tree, curr);
    }
    return curr;
}

int compare_int(Data l, Data r)
{
    return (l - r);
}

void *splay(splay_tree *tree, splay_node *x)
{
    while (1) {
        splay_node *p = x->parent;
        if(!p) {
            tree->root = x;
            return NULL;
        }
        splay_node *g = p->parent;
        if (!g) {
            zig(x);
        } else {
            if ((x == p->left && p == g->left) ||
                (x == p->right && p == g->right)) {
                    zigzig(x, p);
            } else {
                zigzag(x);
            }
        }
    }
}

void zig(splay_node *x)
{
    rotate(x);
}

void zigzig(splay_node *x, splay_node *p)
{
    rotate(p);
    rotate(x);
}

void zigzag(splay_node *x)
{
    rotate(x);
    rotate(x);
}

void rotate(splay_node *child)
{
    splay_node *parent = child->parent;
    if(parent->left == child) { /* A left child given. */
        mark_gp(child);
        parent->left = child->right;
        if(child->right != NULL)
            child->right->parent = parent;
        child->right = parent;
    } else { /* A right child given. */
        mark_gp(child);
        parent->right = child->left;
        if(child->left != NULL)
            child->left->parent = parent;
        child->left = parent;
    }
}

void mark_gp(splay_node *child) {
    splay_node *parent = child->parent;
    splay_node *grand = parent->parent;
    child->parent = grand;
    parent->parent = child;
    if(grand == NULL) {
        return;
    }
    if(grand->left == parent) {
        grand->left = child;
    } else {
        grand->right = child;
    }
}


splay_node* splayT_min(splay_node *node)
{
    splay_node *parent = NULL;
    while(node != NULL) {
        parent = node;
        node = node->left;
    }
    return parent;
}

splay_node* splayT_max(splay_node *node)
{
    splay_node *parent = NULL;
    while(node != NULL) {
        parent = node;
        node = node->right;
    }
    return parent;
}
void *splayT_delete(splay_tree *tree, Data data)
{
    splay_node *node = splayT_find(tree, data);
    delete_hint(tree, node);
    return NULL;
}

void delete_hint(splay_tree *tree, splay_node *node)
{
    if(!node) return;
   splay(tree, node); /* Now node is tree's root. */
   if(node->left == NULL) {
       tree->root = node->right;
       if(tree->root != NULL)
           tree->root->parent = NULL;
   } else if(node->right == NULL) {
       tree->root = node->left;
       tree->root->parent = NULL;
   } else {
       splay_node *x = splayT_min(node->right);
       if(x->parent != node) {
           x->parent->left = x->right;
           if(x->right != NULL)
               x->right->parent = x->parent;
           x->right = node->right;
           x->right->parent = x;
       }
       tree->root = x;
       x->parent = NULL;
       x->left = node->left;
       x->left->parent = x;
   }
   free(node);
   tree->size--;
}

void tree_print_dfs(splay_node *tree, int indent, int width)
{
    int i;
    if (tree == NULL)
        return;

    if (tree->parent != NULL) {
        if (tree == tree->parent->right) {
            indent += width;
            width -= 9;
        }
        else {
            indent -= width;
            width -= 9;
        }
    }

    for (i = 0; i < indent; i++)
        printf(" ");
        printf("%d\n", tree->data);



    tree_print_dfs(tree->left, indent, width);
    tree_print_dfs(tree->right, indent, width);

}

void splayT_free_tree(splay_tree *tree)
{
    while (tree->size) {
        delete_hint(tree, tree->root);
        tree->size--;
    }
}
