#include "lookup.h"
#include "main.h"
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

void search_word(TREE_NODE *root, W_TOKEN* word, char *result){
  if(!root){//word not found
    strcpy(result, "Consulta: ");
    strcat(result, ( (W_TOKEN *)word )->word);
    strcat(result, "\t\tPalavra não encontrada\n");
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
