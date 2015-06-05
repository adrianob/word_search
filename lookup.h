#ifndef LOOKUP
#define LOOKUP
#include "btree.h"
#include "token.h"

void search_words(TREE_NODE *root, char * file_name, char * output_file_name);
void search_word(TREE_NODE *root, W_TOKEN* word, char *result);
#endif
