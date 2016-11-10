#include "splay.h"
#include "func.h"


int main(int argc, char **argv)
{

#ifdef ACT // ACT needs by tests
    if (argc != 2) {
        fprintf(stderr, "Incorrect arguments\n");
        return EXIT_FAILURE;
    }

    int n = atoi(argv[1]);

    FILE *out_data_insert = fopen("insert.dat", "a+");
    FILE *out_data_find = fopen("find.dat", "a+");


#else // NO TEST
    int n = 10;
#endif

    splay_tree *tree = splayT_new_tree(&compare_int);
    printf("%d\n", n);


#ifdef ACT // TEST INSERT
    int a[n];
    double time = 0;
    printf("ADD\n");
    for(int i = 0; i < (n - 1); i++) {
        a[i] = getrand(0, 100000);
        splayT_insert(tree, a[i]);
    }
    time = wtime();
    a[n - 1] = getrand(0, 100000);
    splayT_insert(tree, a[n - 1]);
    time = (wtime() - time);
    fprintf(out_data_insert, "%d %.6f\n", n, time);
#else // NO TEST INSERT
        printf("Insert:\n");
        for (int i = 0; i < n; ++i) {
            int input = 0;
            splayT_insert(tree, scanf("%d", &input));
            printf("\nroot:%d\tmin:%d\tmax:%d\tsize:%d\n", tree->root->data, splayT_min(tree->root)->data,
                   splayT_max(tree->root)->data, tree->size);
            printf("________________________\n");
        }
#endif

#ifdef ACT // TEST LOOKUP
    printf("LOOK\n");
    for (int i = 0; i < (n - 1); i++) {
        int r = rand() % n;
        splayT_find(tree, a[r]);
    }
    time = wtime();
    a[n - 1] = getrand(0, 100000);
    splayT_find(tree, a[rand() % n]);
    time = (wtime() - time);
    fprintf(out_data_find, "%d %.6f\n", n, time);
#else // NO TEST LOOKUP
    splay_node *look = splayT_find(tree, 2);
    if (!look) printf("not founded 2\n");
    look = splayT_find(tree, 55);
    if (!look) printf("not founded 55\n");
    look = splayT_find(tree, 12);
    if (!look) printf("not founded 12\n");
    splayT_delete(tree, 7);
    look = splayT_find(tree, 7);
    if (!look) printf("7 is deleted\n");
    printf("%p\n", look);
    printf("root:%d\tmin:%d\tmax:%d\tsize:%d\n", tree->root->data, splayT_min(tree->root)->data,
            splayT_max(tree->root)->data, tree->size);
#endif
    splayT_free_tree(tree);
    return 0;
}
