#include <stdlib.h>
#include "stack.h"
#include "ast.h"

Stack* mkList(Instr* instr, Stack* l) {
  Stack* list = (Stack*) malloc(sizeof(Stack));
  list->instr = instr;
  list->next = l;
  return list;
}

Stack* head(Stack* l) {
  return mkList(l->instr, NULL);
}

Stack* tail(Stack* l) {
  return l->next;
}

Stack* append(Stack* l1, Stack* l2) {
  Stack* tmp;
  for(tmp = l1; tmp->next!=NULL; tmp=tmp->next);
  tmp->next = l2;
  return l1;
}
