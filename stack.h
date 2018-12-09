#ifndef __stack_h__
#define __stack_h__

typedef struct _Stack {
  struct _Instr* instr;
  struct _Stack* next;
} Stack;

Stack* mkStack(Instr* instr, Stack* l);
Stack* head(Stack* l);
Stack* tail(Stack* l);
Stack* append(Stack* l1, Stack* l2);

#endif
