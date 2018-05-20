#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#include "treap.h"
#include "AVL.h"
#include "RB.h"

const int MAX_N = 5000000;
const int STEP = 40000;
const int MAX_TESTS = 10;

int main() {
    freopen("out.txt", "w", stdout);

    // Дерамида
    for (int n = 1; n <= MAX_N; n += STEP) {
        printf("%d ", n);

        for (int test = 0; test < MAX_TESTS; test++) {
            srand(time(NULL));

            int *a = malloc(n * sizeof(int));

            for (int i = 0; i < n; ++i) {
                a[i] = rand();
            }

            p_item t = NULL;

            clock_t time = clock();

            for (int i = 0; i < n; ++i) {
                p_item it = malloc(sizeof(item));
                it->l = it->r = NULL;
                it->prior = rand();
                it->key = a[i];

                insert(&t, it);
            }

            printf("%f ", (double) (clock() - time) / CLOCKS_PER_SEC);

            clear(t);
            free(a);
        }

        printf("\n");
    }

    // АВЛ
    for (int n = 1; n <= MAX_N; n += STEP) {
        printf("%d ", n);

        for (int test = 0; test < MAX_TESTS; test++) {
            srand(time(NULL));

            int *a = malloc(n * sizeof(int));

            for (int i = 0; i < n; ++i) {
                a[i] = rand();
            }

            p_AVL_tree tree = malloc(sizeof(AVL_tree));
            tree->root = NULL;

            clock_t time = clock();

            for (int i = 0; i < n; ++i) {
                AVL_insert(tree, a[i]);
            }

            printf("%f ", (double) (clock() - time) / CLOCKS_PER_SEC);

            AVL_clear(tree->root);
            free(tree);
            free(a);
        }

        printf("\n");
    }

    // Красно-черное
    for (int n = 1; n <= MAX_N; n += STEP) {
        printf("%d ", n);

        for (int test = 0; test < MAX_TESTS; test++) {
            srand(time(NULL));

            int *a = malloc(n * sizeof(int));

            for (int i = 0; i < n; ++i) {
                a[i] = rand();
            }

            p_RB_tree tree = malloc(sizeof(RB_tree));
            tree->root = NULL;

            clock_t time = clock();

            for (int i = 0; i < n; ++i) {
                RB_insert(tree, a[i]);
            }

            printf("%f ", (double) (clock() - time) / CLOCKS_PER_SEC);

            RB_clear(tree->root);
            free(tree);
            free(a);
        }

        printf("\n");
    }

    return 0;
}

