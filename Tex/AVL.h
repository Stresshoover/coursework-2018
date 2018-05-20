typedef struct AVL_node {
    int data;
    // Разность между высотами правого и левого поддеревьев
    int balance;
    /* Используем массив из двух указателей(лeвый сын - 0),
       чтобы избежать симметричных случаев */
    struct AVL_node *link[2];
} AVL_node, *p_AVL_node;

typedef struct AVL_tree {
    p_AVL_node root; // Корень дерева
} AVL_tree, *p_AVL_tree;

void AVL_insert(p_AVL_tree tree, int data);

void AVL_remove(p_AVL_tree tree, int data);

void AVL_clear(p_AVL_node root);
