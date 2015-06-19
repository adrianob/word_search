//functions for looking up words in a given avl tree and saving results to a file
#include "lookup.h"
#include "main.h"
#include <stdio.h>
#include <time.h>
#include <wchar.h>
#include <string.h>
#include <stdlib.h>

//look for word in the given tree and saves result string to result
void search_word(TREE_NODE *root, W_TOKEN* word, wchar_t *result){
  if(!root){//word not found
    wcscpy(result, L"Consulta: ");
    wcscat(result, ( (W_TOKEN *)word )->word);
    wcscat(result, L"\t\tPalavra não encontrada\n");
    return;
  }
  else if(lex_order(( (W_TOKEN *)( root->data ) ), word) == 0){//found word
    wcscpy(result, L"Consulta: ");
    wcscat(result, ( (W_TOKEN *)word )->word);
    wcscat(result, L" Palavra encontrada nas linhas ");
    wchar_t line[1000];
    line[0] = '\0';
    int first_number = 1;//used to remove comma from last number
    LIST_NODE *node = ( (W_TOKEN *)( root->data ) )->list;
    while(node){//print all lines on which word was found
      if(!first_number)
        wcscat(result, L", ");
      swprintf(line, 1000, L"%d", *(int *)node->data);
      wcscat(result, line);
      node = node->next;
      first_number = 0;
    }
    wcscat(result, L"\n");
    return;
  }
  else if(lex_order(( (W_TOKEN *)( root->data ) ), word) < 0){//word bigger than root
    search_word(root->right, word, result);
  }
  else if(lex_order(( (W_TOKEN *)( root->data ) ), word) > 0){//word smaller than root
    search_word(root->left, word, result);
  }

  return;

}

//search for all words given in file_name and save results to output_file_name
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

  wchar_t line [ 10000 ];

  wchar_t *result = malloc(sizeof(wchar_t) * 10000);

  //start benchmark
  double start_time, end_time, time_elapsed;
  start_time = (double)clock();

  while ( fgetws ( line, sizeof line, file ) != NULL ){//read line by line
    line[wcslen(line) -1] = '\0';//remove new line char
    if(line[wcslen(line) -1] == ' ') line[wcslen(line) -1] = '\0';
    W_TOKEN *token = malloc(sizeof(W_TOKEN));
    str_to_lower(line);
    token->word = line;
    search_word(root, token, result);
    fwprintf(output_file, L"%ls",result);
    fputws ( result, stdout );
  }

  end_time = (double)clock();
  time_elapsed = ( end_time - start_time )/CLOCKS_PER_SEC;
  //end benchmark

  fprintf(output_file, "%s","\n");
  fprintf(output_file, "O tempo gasto na busca foi de %fms.\n", time_elapsed*1000);
  printf("\n");
  printf("O tempo gasto na busca foi de %fms.\n", time_elapsed*1000);

  fclose(file);
  fclose(output_file);

}
