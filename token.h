#ifndef TOKEN
#define TOKEN

#include "singly_linked_list.h"
#include <wchar.h>

typedef struct token_t {
  wchar_t * word;
  LIST_NODE * list;
} W_TOKEN;


void str_to_lower(wchar_t *p);
int lex_order(void *str1, void *str2);
#endif
