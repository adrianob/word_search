#include "btree.h"
#include "singly_linked_list.h"
#include "token.h"
#include "indexer.h"
#include "lookup.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <wctype.h>
#include <wchar.h>
#include <locale.h>

void str_to_lower(wchar_t *p){
  for ( ; *p; ++p) *p = towlower(*p);
}

int lex_order(void *str1, void *str2){
  int order;
  const wchar_t *s1,*s2;
  s1 = ( (W_TOKEN *)str1 )->word;
  s2 = ( (W_TOKEN *)str2 )->word;
  return wcscoll(s1,s2);
}

int main(int argc, char *argv[]){
  //all input files must be in UTF-8!
  setlocale(LC_ALL,"");

  if(argc != 4){
    printf("entrada invalida, formato: entrada busca saida\n");
    return 0;
  }

  TREE_NODE *tree = NULL;
  tree = index_file(argv[1]);

  search_words(tree, argv[2], argv[3]);

  return 0;
}
