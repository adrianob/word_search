#ifndef INDEXER
#define INDEXER

#include "btree.h"
#include "token.h"

TREE_NODE * index_file(char *file_name);
W_TOKEN * create_word(wchar_t * token);
#endif
