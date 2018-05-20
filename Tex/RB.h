typedef struct RB_node {
    int red; // ���� (1 = ������� �������) 
    int data;
    /* ���������� ������ �� ���� ����������(�e��� ��� - 0),
       ����� �������� ������������ ������� */
    struct RB_node *link[2];
} RB_node, *p_RB_node;

typedef struct RB_tree {
   p_RB_node root; // ������ ������
} RB_tree, *p_RB_tree;

void RB_insert(p_RB_tree tree, int data);

void RB_remove(p_RB_tree tree, int data);

void RB_clear(p_RB_node root);
