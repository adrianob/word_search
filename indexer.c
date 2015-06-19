//functions for indexing a text file using an avl tree
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include "indexer.h"
#include "main.h"

//create a w_token struct from a string with null list
W_TOKEN * create_word(wchar_t * token){
  wchar_t *current_word = NULL;
  W_TOKEN *w_token = NULL;
  current_word = malloc(wcslen(token) * sizeof(wchar_t) + 1);
  str_to_lower(token);
  wcscpy(current_word, token);
  w_token = malloc(sizeof(W_TOKEN));
  w_token->word = current_word;
  w_token->list = NULL;

  return w_token;
}

//load words into an avl tree
TREE_NODE * index_file(char *file_name){
  FILE *file;
  file = fopen(file_name,"r");
  if(!file){
    printf("arquivo de entrada invalido\n");
    return NULL;
  }

  wchar_t line [ 10000 ];
  wchar_t *token;
  wchar_t *state;
  const wchar_t delimiters[] = L" \n,.;'\"?-|:*&!@$%{}()[]<>\\";//only consider letters
  int current_line = 1;
  TREE_NODE *tree = NULL;
  W_TOKEN *w_token = NULL;

  while ( fgetws ( line, sizeof(line), file ) ){//read line by line
    for (token = wcstok(line, delimiters, &state);
           token != NULL;
           token = wcstok(NULL, delimiters, &state)) {
      if(token) w_token = create_word(token);
      insert_avl(&tree, (void *)w_token, lex_order, current_line);
      }
    current_line++;
  }

  fclose ( file );
  return tree;
}
