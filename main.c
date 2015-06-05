#include "btree.h"
#include "singly_linked_list.h"
#include "token.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

void print_tree(TREE_NODE *n, int level){
  int i;
  for (i = 0; i < level; ++i)
  {
    printf("==");
  }
  LIST_NODE* list =  ( (W_TOKEN *)( n->data ) )->list;
  printf("%s %d\n", ( (W_TOKEN *)( n->data ) )->word, list_size(list));
  while(list){
    printf("%d\n", *(int *)list->data );
    list = list->next;
  }

}

//fill string up to len with zeros
char * padd_string(char *str, int len){
  char *padded = malloc(sizeof(char)*len + 1);

  padded[0] = '\0';
  strcat(padded,str);
  int i;
  for(i = strlen(str);i<len;i++){
    padded[i] = ' ';//blank char for lex order
  }
  padded[i] = '\0';

  return padded;
}

//0 if equal, -1 if str1 < str2, 1 otherwise
int lex_order(void *str1, void *str2){
  int order = 0;
  char *s1,*s2;
  s1 = ( (W_TOKEN *)str1 )->word;
  s2 = ( (W_TOKEN *)str2 )->word;

  if(strlen(s1) < strlen(s2)){
    s1 = padd_string(s1,strlen(s2));
  }
  else if(strlen(s1) > strlen(s2)){
    s2 = padd_string(s2,strlen(s1));
  }

  int i;
  for(i = 0; i < strlen(s1); i++){
    if(tolower((s1)[i]) < tolower((s2)[i])){
      return -1;
    }
    else if(tolower((s1)[i]) > tolower((s2)[i])){
      return 1;
    }
  }

  return order;
}

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

void search_word(TREE_NODE *root, W_TOKEN* word, char *result){
  if(!root){//word not found
    strcpy(result, "Consulta: ");
    strcat(result, ( (W_TOKEN *)word )->word);
    strcat(result, "\t\tPalavra não encontrada");
    return;
  }
  else if(lex_order(( (W_TOKEN *)( root->data ) ), word) == 0){
    strcpy(result, "Consulta: ");
    strcat(result, ( (W_TOKEN *)word )->word);
    strcat(result, "\t\tPalavra encontrada nas linhas ");
    char line[20];
    line[0] = '\0';
    int first_number = 1;
    LIST_NODE *node = ( (W_TOKEN *)( root->data ) )->list;
    while(node){
      if(!first_number)
        strcat(result, ", ");
      sprintf(line, "%d", *(int *)node->data);
      strcat(result, line);
      node = node->next;
      first_number = 0;
    }
    strcat(result, "\n");
    return;
  }
  else if(lex_order(( (W_TOKEN *)( root->data ) ), word) == -1){
    search_word(root->right, word, result);
  }
  else if(lex_order(( (W_TOKEN *)( root->data ) ), word) == 1){
    search_word(root->left, word, result);
  }

  return;

}

void search_words(TREE_NODE *root, char * file_name, char * output_file_name){
  FILE *file, *output_file;
  file = fopen(file_name,"r");
  output_file = fopen(output_file_name,"w");
  if(!file){
    printf("arquivo de entrada invalido\n");
    return;
  }
  if(!output_file){
    printf("arquivo de saida invalido\n");
    return;
  }

  char line [ 1000 ];

  char *result = malloc(sizeof(char) * 150);

  double start_time, end_time, time_elapsed;
  start_time = (double)clock();

  while ( fgets ( line, sizeof line, file ) != NULL ){//read line by line
    line[strlen(line) -1] = '\0';//remove new line char
    W_TOKEN *token = malloc(sizeof(W_TOKEN));
    token->word = line;
    search_word(root, token, result);
    fprintf(output_file, "%s",result);
    printf("%s", result );
  }

  end_time = (double)clock();
  time_elapsed = ( end_time - start_time )/CLOCKS_PER_SEC;

  fprintf(output_file, "%s","\n\n");
  fprintf(output_file, "O tempo gasto na busca foi de %fms.\n", time_elapsed*1000);
  printf("\n");
  printf("O tempo gasto na busca foi de %fms.\n", time_elapsed*1000);

  fclose(file);
  fclose(output_file);

}

int main(int argc, char *argv[])
{
  if(argc != 4){
    printf("entrada invalida\n");
    return 0;
  }

  TREE_NODE *tree = NULL;
  tree = index_file(argv[1]);

  search_words(tree, argv[2], argv[3]);

  return 0;
}
