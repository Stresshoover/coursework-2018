#include <stdlib.h>

#include "RB.h"

int is_red(p_RB_node root) {
    return root && root->red == 1;
}

p_RB_node RB_single_rot(p_RB_node root, int dir) {
    p_RB_node save = root->link[!dir];

    root->link[!dir] = save->link[dir];
    save->link[dir] = root;

    root->red = 1;
    save->red = 0;

    return save;
}

p_RB_node RB_double_rot(p_RB_node root, int dir) {
    root->link[!dir] = RB_single_rot(root->link[!dir], !dir);

    return RB_single_rot(root, dir);
}

p_RB_node RB_make_node(int data) {
    p_RB_node rn = malloc(sizeof(RB_node));

    if (rn) {
        rn->data = data;
        rn->red = 1; /* 1 is red, 0 is black */
        rn->link[0] = rn->link[1] = NULL;
    }

    return rn;
}

p_RB_node RB_insert_node(p_RB_node root, int data) {
    if (!root) {
        root = RB_make_node(data);
    }
    else if (data != root->data) {
        int dir = root->data < data;

        root->link[dir] = RB_insert_node(root->link[dir], data);

        if (is_red(root->link[dir])) {
            if (is_red(root->link[!dir])) {
                root->red = 1;
                root->link[0]->red = 0;
                root->link[1]->red = 0;
            } else {
                if (is_red(root->link[dir]->link[dir])) {
                    root = RB_single_rot(root, !dir);
                } else if (is_red(root->link[dir]->link[!dir])) {
                    root = RB_double_rot(root, !dir);
                }
            }
        }
    }

    return root;
}

void RB_insert(p_RB_tree tree, int data) {
    tree->root = RB_insert_node(tree->root, data);
    tree->root->red = 0;
}


p_RB_node RB_remove_balance(p_RB_node root, int dir, int *done) {
    p_RB_node p = root;
    p_RB_node s = root->link[!dir];

    if (is_red(s)) {
        root = RB_single_rot(root, dir);
        s = p->link[!dir];
    }

    if (s) {
        if (!is_red(s->link[0]) && !is_red(s->link[1])) {
            if (is_red(p)) {
                *done = 1;
            }

            p->red = 0;
            s->red = 1;
        }
        else {
            int save = p->red;
            int new_root = (root == p);

            if (is_red(s->link[!dir])) {
                p = RB_single_rot(p, dir);
            }
            else {
                p = RB_double_rot(p, dir);
            }

            p->red = save;
            p->link[0]->red = 0;
            p->link[1]->red = 1;

            if (new_root) {
                root = p;
            }
            else {
                root->link[dir] = p;
            }

            *done = 1;
        }
    }

    return root;
}

p_RB_node RB_remove_node(p_RB_node root, int data, int *done) {
    if (!root) {
        *done = 1;
    }
    else {
        int dir;

        if (root->data == data) {
            if (!root->link[0] || !root->link[1]) {
                p_RB_node save = root->link[!root->link[0]];

                if (is_red(root)) {
                    *done = 1;
                }
                else if (is_red(save)) {
                    save->red = 0;
                    *done = 1;
                }

                free(root);

                return save;
            }
            else {
                p_RB_node heir = root->link[0];

                while(heir->link[1]) {
                    heir = heir->link[1];
                }

                root->data = heir->data;
                data = heir->data;
            }
        }

        dir = root->data < data;
        root->link[dir] = RB_remove_node(root->link[dir], data, done);

        if (!*done) {
            root = RB_remove_balance(root, dir, done);
        }
    }

    return root;
}

void RB_remove(p_RB_tree tree, int data) {
    int done = 0;

    tree->root = RB_remove_node(tree->root, data, &done);

    if (tree->root) {
        tree->root->red = 0;
    }
}


void RB_clear(p_RB_node root) {
    if (root) {
        RB_clear(root->link[0]);
        RB_clear(root->link[1]);
        free(root);
        root = NULL;
    }
}

