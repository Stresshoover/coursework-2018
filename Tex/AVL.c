#include<stdio.h>
#include<stdlib.h>

#include "AVL.h"

p_AVL_node AVL_make_node(int data) {
    p_AVL_node rn = malloc(sizeof(AVL_node));

    if (rn) {
        rn->data = data;
        rn->balance = 0;
        rn->link[0] = rn->link[1] = NULL;
    }

    return rn;
}

// Функция малого поворота, dir - направление вращения (левый поворот - dir = 0)
p_AVL_node AVL_single_rot(p_AVL_node root, int dir) {
    p_AVL_node save = root->link[!dir];

    root->link[!dir] = save->link[dir];
    save->link[dir] = root;

    return save;
}

// Большое вращение
p_AVL_node AVL_double_rot(p_AVL_node root, int dir) {
    p_AVL_node save = root->link[!dir]->link[dir];

    root->link[!dir]->link[dir] = save->link[!dir];
    save->link[!dir] = root->link[!dir];
    root->link[!dir] = save;

    save = root->link[!dir];
    root->link[!dir] = save->link[dir];
    save->link[dir] = root;

    return save;
}

// Установка баланса перед большим поворотом
void adjust_balance(p_AVL_node root, int dir, int bal) {
    p_AVL_node n = root->link[dir];
    p_AVL_node nn = n->link[!dir];

    if (nn->balance == 0) {
        root->balance = n->balance = 0;
    }
    else if (nn->balance == bal) {
        root->balance = -bal;
        n->balance = 0;
    }
    else { // nn->balance == -bal
        root->balance = 0;
        n->balance = bal;
    }

    nn->balance = 0;
}

// Балансировка после вставки
p_AVL_node insert_balance(p_AVL_node root, int dir) {
    p_AVL_node n = root->link[dir];
    int bal = dir == 0 ? -1 : +1;

    if (n->balance == bal) {
        root->balance = n->balance = 0;
        root = AVL_single_rot(root, !dir);
    }
    else { // n->balance == -bal
        adjust_balance(root, dir, bal);
        root = AVL_double_rot(root, !dir);
    }

    return root;
}

// Добавление вершины
p_AVL_node insert_node(p_AVL_node root, int data, int *done) {
    if (!root) {
        root = AVL_make_node(data);
    }
    else {
        int dir = root->data < data;

        root->link[dir] = insert_node(root->link[dir], data, done);

        if (!*done) {
            // Обновление баланса
            root->balance += dir == 0 ? -1 : +1;

            // Балансировка(если нужно) и выход из функции
            if (root->balance == 0) {
                *done = 1;
            }
            else if (abs(root->balance) > 1) {
                root = insert_balance(root, dir);
                *done = 1;
            }
        }
    }

    return root;
}

void AVL_insert(p_AVL_tree tree, int data) {
    int done = 0;

    tree->root = insert_node(tree->root, data, &done);
}

// Балансировка после удаления
p_AVL_node AVL_remove_balance(p_AVL_node root, int dir, int *done) {
    p_AVL_node n = root->link[!dir];
    int bal = dir == 0 ? -1 : +1;

    if (n->balance == -bal) {
        root->balance = n->balance = 0;
        root = AVL_single_rot(root, dir);
    }
    else if (n->balance == bal) {
        adjust_balance(root, !dir, -bal);
        root = AVL_double_rot(root, dir);
    }
    else { // n->balance == 0
        root->balance = -bal;
        n->balance = bal;
        root = AVL_single_rot(root, dir);
        *done = 1;
    }

    return root;
}

// Удаление вершины
p_AVL_node AVL_remove_node(p_AVL_node root, int data, int *done) {
    if (root != NULL) {
        int dir;

        // Удаление найденной вершины
        if (root->data == data) {
            // Замена текущей вершины на подходящего потомка
            if (root->link[0] == NULL || root->link[1] == NULL) {
                p_AVL_node save;

                dir = root->link[0] == NULL;
                save = root->link[dir];
                free(root);

                return save;
            }
            else {
                // Находим подходящего потомка
                p_AVL_node heir = root->link[0];

                while (heir->link[1] != NULL) {
                    heir = heir->link[1];
                }

                // Копируем значение ключа
                root->data = heir->data;
                data = heir->data;
            }
        }

        dir = root->data < data;
        root->link[dir] = AVL_remove_node(root->link[dir], data, done);

        if (!*done) {
            // Обновляем баланс
            root->balance += dir != 0 ? -1 : +1;

            // Балансировка или выход из функции
            if (abs(root->balance) == 1) {
                *done = 1;
            }
            else if (abs(root->balance) > 1) {
                root = AVL_remove_balance(root, dir, done);
            }
        }
    }

    return root;
}

void AVL_remove(p_AVL_tree tree, int data) {
    int done = 0;

    tree->root = AVL_remove_node(tree->root, data, &done);
}

void AVL_clear(p_AVL_node root) {
    if(root) {
        AVL_clear(root->link[0]);
        AVL_clear(root->link[1]);
        free(root);
        root = NULL;
    }
}

