#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#include "treap.h"
#include "AVL.h"
#include "RB.h"

/* Change for full testing*/
const int MAX_N = 1000000;
const int MIN_N = 1000000;
const int MAX_TESTS = 5;

int main() {
    srand(time(NULL));
    freopen("out.txt", "w", stdout);

    for (int n = MIN_N; n <= MAX_N; n++){
        int *a = malloc(n * sizeof(int));

        for (int i = 0; i < n; ++i) {
            a[i] = rand();
        }

        // Testing treap
        {
            p_item t = NULL;


            for (int i = 0; i < n; ++i) {
                p_item it = malloc(sizeof(item));
                it->l = it->r = NULL;
                it->prior = rand();
                it->key = a[i];

                insert(&t, it);
            }

            for (int i = 0; i < MAX_TESTS; ++i) {
                int x = rand();

                clock_t time = clock();

                p_item it = malloc(sizeof(item));
                it->l = it->r = NULL;
                it->prior = rand();
                it->key = x;

                insert(&t, it);

                printf("treap insert at %d: %f\n", n, (double) (clock() - time) / CLOCKS_PER_SEC);

                time = clock();
                erase(&t, x);
                printf("treap erase at %d: %f\n", n, (double) (clock() - time) / CLOCKS_PER_SEC);
            }

            clear(t);
        }

        printf("\n");

        // Testing AVL
        {
            p_AVL_tree tree = malloc(sizeof(AVL_tree));
            tree->root = NULL;

            for (int i = 0; i < n; ++i) {
                AVL_insert(tree, a[i]);
            }

            for (int i = 0; i < MAX_TESTS; ++i) {
                int x = rand();

                clock_t time = clock();
                AVL_insert(tree, x);
                printf("AVL insert at %d: %f\n", n, (double) (clock() - time) / CLOCKS_PER_SEC);

                time = clock();
                AVL_remove(tree, x);
                printf("AVL erase at %d: %f\n", n, (double) (clock() - time) / CLOCKS_PER_SEC);
            }

            AVL_clear(tree->root);
            free(tree);
        }

        printf("\n");

        // Testing RBT
        {
            p_RB_tree tree = malloc(sizeof(RB_tree));
            tree->root = NULL;

            for (int i = 0; i < n; ++i) {
                RB_insert(tree, a[i]);
            }

            for (int i = 0; i < MAX_TESTS; ++i) {
                int x = rand();

                clock_t time = clock();
                RB_insert(tree, x);
                printf("RB insert at %d: %f\n", n, (double) (clock() - time) / CLOCKS_PER_SEC);

                time = clock();
                RB_remove(tree, x);
                printf("RB erase at %d: %f\n", n, (double) (clock() - time) / CLOCKS_PER_SEC);
            }

            RB_clear(tree->root);
            free(tree);
        }

        printf("\n");
        free(a);
    }
    return 0;
}