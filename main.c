#include "btree.h"
#include "indexer.h"
#include "lookup.h"
#include <locale.h>

int main(int argc, char *argv[]){
  //all input files must be in UTF-8!
  setlocale(LC_ALL,"");

  if(argc != 4){
    printf("entrada invalida, formato: entrada busca saida\n");
    return 0;
  }

  TREE_NODE *tree = index_file(argv[1]);

  search_words(tree, argv[2], argv[3]);

  return 0;
}
