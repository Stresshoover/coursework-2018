#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#include "treap.h"

void split(p_item t, int key, p_item *l, p_item *r) {
    if (!t) {
        *l = *r = NULL;
    }
    else if (key < t->key) {
        split(t->l, key, l, &t->l);
        *r = t;
    }
    else {
        split(t->r, key, &t->r, r);
        *l = t;
    }
}

void insert(p_item *t, p_item it) {
    if (!*t) {
        *t = it;
    }
    else if (it->prior > (*t)->prior){
        split(*t, it->key, &it->l, &it->r);
        *t = it;
    }
    else {
        insert(it->key < (*t)->key ? &(*t)->l : &(*t)->r, it);
    }
}


void merge(p_item *t, p_item l, p_item r) {
    if (!l || !r) {
        *t = l ? l : r;
    }
    else if (l->prior > r->prior) {
        merge(&l->r, l->r, r);
        *t = l;
    }
    else {
        merge(&r->l, l, r->l);
        *t = r;
    }
}

void erase(p_item *t, int key) {
    if ((*t)->key == key) {
        p_item save_t = *t;
        merge(t, (*t)->l, (*t)->r);
        free(save_t);
        save_t = NULL;
    }
    else {
        erase (key < (*t)->key ? &(*t)->l : &(*t)->r, key);
    }
}


void inorder(p_item t) {
    if (t) {
        inorder(t->l);
        printf("%d ", t->key);
        inorder(t->r);
    }
}

void clear(p_item t) {
    if (t) {
        clear(t->l);
        clear(t->r);
        free(t);
        t = NULL;
    }
}
