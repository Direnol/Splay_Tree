#ifndef SPLAY_TREE_FUNC_H
#define SPLAY_TREE_FUNC_H
#include <sys/time.h>

#include <stdlib.h>


double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}
/* getrand: Returns random number from [min, max) */
int getrand(int min, int max)
{
    return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

#endif //SPLAY_TREE_FUNC_H
