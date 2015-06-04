#include "btree.h"
#include "token.h"
#include "singly_linked_list.h"
#include <stdlib.h>
#include <stdio.h>

TREE_NODE * rotate_left( TREE_NODE* root )
{
  TREE_NODE* k1 = NULL;
  k1 = root->left;
  root->left = k1->right;
  k1->right = root;
  root->height = max( height( root->left ), height( root->right ) ) + 1;
  k1->height = max( height( k1->left ), root->height ) + 1;
  return k1;
}

TREE_NODE* rotate_right( TREE_NODE* root )
{
  TREE_NODE* k2;

  k2 = root->right;
  root->right = k2->left;
  k2->left = root;

  root->height = max( height( root->left ), height( root->right ) ) + 1;
  k2->height = max( height( k2->right ), root->height ) + 1;

  return k2;
}

TREE_NODE* double_left_rotate( TREE_NODE* root )
{
  root->left = rotate_right( root->left );
  return rotate_left( root );
}

TREE_NODE* double_right_rotate( TREE_NODE* root )
{
  root->right = rotate_left( root->right );
  return rotate_right( root );
}

int line_in_list(LIST_NODE *head, int line){
  while(head){
    if(*(int *)( head->data ) == line){
      return 1;
    }
    head = head->next;
  }

  return 0;
}

void insert_avl(TREE_NODE** t, void *data, filter filter, int line ){
  int *l;
  l = malloc(sizeof(int));
  *l = line;
  if( *t == NULL ){
    *t = (TREE_NODE*)malloc(sizeof(TREE_NODE));
    (*t)->data = data;
    if(!line_in_list(( ( (W_TOKEN *)( (*t)->data ) )->list ), line))
      append(&( ( (W_TOKEN *)( (*t)->data ) )->list ), l);
    (*t)->height = 0;
    (*t)->left = (*t)->right = NULL;
  }
  else if (filter(data , (*t)->data) == -1 ){
    insert_avl( &((*t)->left), data, filter, line );
    if( height( (*t)->left ) - height( (*t)->right ) == 2 ){
      if (filter(data , (*t)->left->data) == -1 ){
        *t = rotate_left( *t );
      }
      else if (filter(data , (*t)->left->data) == 1 ){
        *t = double_left_rotate( *t );
      }
    }
  }
  else if (filter(data , (*t)->data) == 1 ){
    insert_avl( &( (*t)->right ), data, filter, line );
    if( height( (*t)->right ) - height( (*t)->left ) == 2 ){
      if (filter(data , (*t)->right->data) == 1 ){
        *t = rotate_right( *t );
      }
      else if (filter(data , (*t)->right->data) == -1 ){
        *t = double_right_rotate( *t );
      }
    }
  }
  else{
    if(!line_in_list(( ( (W_TOKEN *)( (*t)->data ) )->list ), line))
      append(&( ( (W_TOKEN *)( (*t)->data ) )->list ), l);
  }

  (*t)->height = max( height( (*t)->left ), height( (*t)->right ) ) + 1;
}

int max(int x, int y){
  return x > y ? x : y;
}

int same(TREE_NODE *root1, TREE_NODE *root2){
  if (root1 && root2)
  {
    if(( *( (int *)root1->data ) ) != ( *( (int *)root2->data ) )){
      return 0;
    }
    if(!same(root1->left, root2->left))
      return 0;
    if(!same(root1->right, root2->right))
      return 0;
  }
  else if(root1 && !root2)
    return 0;
  else if(root2 && !root1)
    return 0;

  return 1;

}

void insert(TREE_NODE **root, void *data, filter filter){
  if (!*root)
  {
    *root = (TREE_NODE *) malloc(sizeof(TREE_NODE) );
    (*root)->data = data;
    (*root)->right = NULL;
    (*root)->left = NULL;

  }
  else if (filter(data , (*root)->data) )//left
  {
    insert(&(*root)->left, data, filter);
  }
  else{
    insert(&(*root)->right, data, filter);
  }

}

int tree_factor(TREE_NODE *root){
  static int factor = 0;
  if(root){
    factor = abs(balancing_factor(root)) > abs(factor) ? balancing_factor(root) : factor;
    tree_factor(root->left);
    tree_factor(root->right);
  }
  return abs(factor);
}

int balancing_factor(TREE_NODE * root){
  return height(root->left) - height(root->right);
}

static int height( TREE_NODE* n )
{
    if( n == NULL )
        return -1;
    else
        return n->height;
}

int is_leaf(TREE_NODE *root){
  return ( root->left == NULL ) && ( root->right == NULL );
}

void print_pre_left(TREE_NODE *root, print_function f){
  if (root)
  {
    f(root, 0);
    print_pre_left(root->left, f);
    print_pre_left(root->right, f);
  }

}

int tree_size(TREE_NODE *root){
  static int count = 0;
  if(root)
  {
    count++;
    tree_size(root->left);
    tree_size(root->right);
  }
  else
    return count;
  return count;
}

void print_all(TREE_NODE *root, print_function f, int level){
  if (root)
  {
    f(root, level);
    print_all(root->left, f, level + 1);
    print_all(root->right, f, level + 1);
  }

}
