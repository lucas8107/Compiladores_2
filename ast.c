// AST constructor functions

#include <stdlib.h> // for malloc
#include <string.h>
#include "ast.h" // AST header

Instr* mkInstruction(int kind, int arg) {
  Instr* node = (Instr*) malloc(sizeof(Instr));
  node->kind = kind;
  node->args.arg = arg;
  return node;
}

Instr* mkInstruction_2(int kind, char* arg) {
  Instr* node = (Instr*) malloc(sizeof(Instr));
  node->kind = kind;
  node->args.varName = (char*) malloc(sizeof(arg));
  strcpy(node->args.varName, arg);
  // node->args.varName = arg;
  return node;
}

Expr* ast_integer(int v) {
  Expr* node = (Expr*) malloc(sizeof(Expr));
  node->kind = E_INTEGER;
  node->attr.value = v;
  return node;
}

Expr* ast_var_name(char* var_name) {
  Expr* node = (Expr*) malloc(sizeof(Expr));
  node->kind = E_VAR;
  node->attr.var_name = var_name;
  return node;
}

Cmd* ast_attribution(char* name, Expr* expr) {
  Cmd* node = (Cmd*) malloc(sizeof(Cmd));
  node->kind = ATTRIBUTION;
  node->attr.op.varName = name;
  node->attr.op.expr = expr;
  return node;
}

Cmd* ast_attribution_exist_variable(char* name, Expr* expr){
  Cmd* node = (Cmd*) malloc(sizeof(Cmd));
  node->kind = ATTRIBUTION_EXIST;
  node->attr.op.varName = name;
  node->attr.op.expr = expr;
  return node;
}

Cmd* ast_print(char* str) {
  Cmd* node = (Cmd*) malloc(sizeof(Cmd));
  node->kind = PRINT_S;
  node->attr.string = str;
  return node;
}

Cmd* ast_print_var(char* str, char* varName) {
  Cmd* node = (Cmd*) malloc(sizeof(Cmd));
  node->kind = PRINT_VAR_S;
  node->attr.op_print.string = str;
  node->attr.op_print.varName = varName;
  return node;
}

// Cmd* ast_scan(char* str, char* varName){
//   Cmd* node = (Cmd*) malloc(sizeof(Cmd));
//   node->kind = SCAN_S;
//   node->attr.op_scan.str = str;
//   node->attr.op_scan.varName = varName;
//   return node;
// }

Cmd* ast_scan(char* varName){
  Cmd* node = (Cmd*) malloc(sizeof(Cmd));
  node->kind = SCAN_S;
  // node->attr.op_scan.str = str;
  node->attr.op_scan.varName = varName;
  return node;
}

Cmd* ast_if(Expr* expr, CmdList* cl_if){
  Cmd* node = (Cmd*) malloc(sizeof(Cmd));
  node->kind = IF_S;
  node->attr.op_if.expr = expr;
  node->attr.op_if.cl_if = cl_if;
  return node;
}

Cmd* ast_if_else(Expr* expr, CmdList* cl_if, CmdList* cl_if_else){
  Cmd* node = (Cmd*) malloc(sizeof(Cmd));
  node->kind = IF_ELSE_S;
  node->attr.op_if_else.expr = expr;
  node->attr.op_if_else.cl_if = cl_if;
  node->attr.op_if_else.cl_if_else = cl_if_else;
  return node;
}

Cmd* ast_while(Expr* expr, CmdList* cl_while){
  Cmd* node = (Cmd*) malloc(sizeof(Cmd));
  node->kind = WHILE_S;
  node->attr.op_while.expr = expr;
  node->attr.op_while.cl_while = cl_while;
  return node;
}

Expr* ast_operation(int operator, Expr* left, Expr* right) {
  Expr* node = (Expr*) malloc(sizeof(Expr));
  node->kind = E_OPERATION;
  node->attr.op.operator = operator;
  node->attr.op.left = left;
  node->attr.op.right = right;
  return node;
}

Expr* ast_invert_val(Expr* expr){
  Expr* node = (Expr*) malloc(sizeof(Expr));
  node->kind = E_OPERATION_INVERT;
  node->attr.op_invert.expr = expr;
  return node;
}

ExprList* ast_exprlist(Expr* expr, ExprList* next) {
  ExprList* list = (ExprList*) malloc(sizeof(ExprList));
  list->expr = expr;
  list->next = next;
  return list;
}

CmdList* ast_cmdlist(Cmd* cmd, CmdList* next) {
  CmdList* list = (CmdList*) malloc(sizeof(CmdList));
  list->cmd = cmd;
  list->next = next;
  return list;
}

BoolExpr* ast_bool(int v) {
  BoolExpr* node = (BoolExpr*) malloc(sizeof(BoolExpr));
  node->kind = B_INTEGER;
  node->attr.value = v;
  return node;
}

BoolExpr* ast_boolexp(int operator, BoolExpr* left, BoolExpr* right) {
  BoolExpr* node = (BoolExpr*) malloc(sizeof(BoolExpr));
  node->kind = B_OPERATION;
  node->attr.op.operator = operator;
  node->attr.op.left = left;
  node->attr.op.right = right;
  return node;
}
