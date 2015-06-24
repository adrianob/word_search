#include "token.h"

void str_to_lower(wchar_t *p){
  for ( ; *p; ++p) *p = towlower(*p);
}

int lex_order(void *str1, void *str2){
  const wchar_t *s1,*s2;
  s1 = ( (W_TOKEN *)str1 )->word;
  s2 = ( (W_TOKEN *)str2 )->word;
  return wcscoll(s1,s2);
}
