#ifndef LINKED_LIST
#define LINKED_LIST

typedef int (*iterator)(void *);
typedef int (*filter)(void *, void *);

typedef struct _list_node {
  void *data;
  struct _list_node *next;
} LIST_NODE;

LIST_NODE * initialize(void);
LIST_NODE * last_node(LIST_NODE *head);
void push(LIST_NODE **head_ref, void *element);
void append(LIST_NODE **head_ref, void *element);
void for_each(LIST_NODE *head, iterator iterator);
void for_each_reverse(LIST_NODE *head, iterator iterator);
void destroy(LIST_NODE **head_ref);
void remove_all(LIST_NODE **head_ref, filter filter, void * filter_arg );
int list_size(LIST_NODE *head);
void sort(LIST_NODE **head_ref, filter filter);
void swap(LIST_NODE **node1, LIST_NODE **node2);

#endif
