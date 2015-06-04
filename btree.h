#ifndef BTREE
#define BTREE

typedef int (*comparator)(void *, void *);

typedef struct NODE_T {
  void * data;
  int height;
  struct NODE_T *right;
  struct NODE_T *left;

} TREE_NODE;

typedef void (*print_function)(TREE_NODE *, int);

void insert(TREE_NODE **root, void *data, comparator comparator);
void insert_avl(TREE_NODE** t, void *data, comparator comparator, int line );
void print_all(TREE_NODE *root, print_function f, int level);
void print_pre_left(TREE_NODE *root, print_function f);
int tree_size(TREE_NODE *root);
int max(int x, int y);

TREE_NODE * rotate_left( TREE_NODE* root );
TREE_NODE* rotate_right( TREE_NODE* root );
TREE_NODE* double_left_rotate( TREE_NODE* root );
TREE_NODE* double_right_rotate( TREE_NODE* root );
static int height( TREE_NODE* n );
int balancing_factor(TREE_NODE * root);
int tree_factor(TREE_NODE *root);
int same(TREE_NODE *root1, TREE_NODE *root2);
#endif
