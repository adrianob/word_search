#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "indexer.h"
#include "main.h"

W_TOKEN * create_word(char * token){
  char *current_word = NULL;
  W_TOKEN *w_token = NULL;
  current_word = malloc(sizeof(token) + 1);
  strcpy(current_word, token);
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

  char line [ 10000 ];
  char *token;
  const char delimiters[] = " \n,.;'\"?-|:*&!@$%{}()[]<>\\";
  int current_line = 1;
  TREE_NODE *tree = NULL;
  W_TOKEN *w_token = NULL;

  while ( fgets ( line, sizeof line, file ) != NULL ){//read line by line
    token = strtok(line, delimiters);
    if(token) w_token = create_word(token);
    while( token != NULL ) {
      insert_avl(&tree, (void *)w_token, lex_order, current_line);
      token = strtok(NULL, delimiters);
      if(token) w_token = create_word(token);
    }
    current_line++;
  }

  fclose ( file );
  return tree;
}
