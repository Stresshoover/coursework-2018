typedef struct RB_node {
    int red; // Цвет (1 = вершина красная) 
    int data;
    /* Используем массив из двух указателей(лeвый сын - 0),
       чтобы избежать симметричных случаев */
    struct RB_node *link[2];
} RB_node, *p_RB_node;

typedef struct RB_tree {
   p_RB_node root; // Корень дерева
} RB_tree, *p_RB_tree;

void RB_insert(p_RB_tree tree, int data);

void RB_remove(p_RB_tree tree, int data);

void RB_clear(p_RB_node root);
