typedef struct treap_item {
    int key, prior;
    struct treap_item *l, *r;
} item, *p_item;

void split(p_item t, int key, p_item *l, p_item *r);

void insert(p_item *t, p_item it);

void merge(p_item *t, p_item l, p_item r);

void erase(p_item *t, int key);

void inorder(p_item t);

void clear(p_item t);