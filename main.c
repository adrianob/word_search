#include "btree.h"
#include "singly_linked_list.h"
#include "token.h"
#include "indexer.h"
#include "lookup.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

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
