#ifndef TOKEN
#define TOKEN

#include "singly_linked_list.h"
#include <wchar.h>

typedef struct token_t {
  wchar_t * word;
  LIST_NODE * list;
} W_TOKEN;

#endif
