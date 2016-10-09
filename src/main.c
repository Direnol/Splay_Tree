#include "splay.h"

int main()
{
    splay_tree *tree = splayT_new_tree(&compare_int);
    int values[] = {3, 4, 1, 2, 8, 5, 7};
    for(int i = 0; i < 7; i++) {
        splayT_insert(tree, values[i]);
        printf("root:%d\tmin:%d\tmax:%d\tsize:%d\n", tree->root->data, splayT_min(tree->root)->data,
                splayT_max(tree->root)->data, tree->size);
        printf("________________________\n");
    }

    splay_node *look = splayT_find(tree, 7);
    // printf("%d\n", look->data);
    splayT_delete(tree, 7);
    look = splayT_find(tree, 7);
    printf("%p\n", look);
    printf("root:%d\tmin:%d\tmax:%d\tsize:%d\n", tree->root->data, splayT_min(tree->root)->data,
            splayT_max(tree->root)->data, tree->size);

    splayT_free_tree(tree);
    printf("%p\t %d\n", tree->root->left, tree->size);
    return 0;
}
