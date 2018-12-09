#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "stack.c"

typedef struct Vars{
  char* varName;
  int val;
  struct Vars* next;
} Var;

typedef struct VarList {
  int num_var;
  struct Vars* head;
}VarList;

FILE* f;

VarList* vlist;

VarList* newVarList() {
  VarList* varList = (VarList*)malloc(sizeof(VarList));
  varList->num_var = 0;
  varList->head = NULL;
  return varList;
}

void addNode(char* name, int val) {
  Var* var = (Var*) malloc(sizeof(Var));
  var->val = val;
  var->varName = strdup(name);
  var->next = vlist->head;
  vlist->head = var;
  return;
}


void printData() {
  Var* v = vlist->head;
  fprintf(f, ".data\n");
  while(v != NULL) {
    if(v->val == 0) {
      fprintf(f, "\t%s: .word 0\n", v->varName);
    }
    else {
      fprintf(f, "%s", v->varName);
    }
    v = v->next;

  }
  fprintf(f, ".text\n");
}

Stack* compileCMD(CmdList* cmd_list);
int string_count = 0;


void printInstr(Stack* l) {
  while(l!=NULL) {
    switch (l->instr->kind) {

      case LDC:
      
        printf("LDC ");
        printf("%d\n", l->instr->args.arg);

        fprintf(f, "\tli $a0, %d\n", l->instr->args.arg);
        fprintf(f, "\tsw $a0, 0($sp)\n");
        fprintf(f, "\taddiu $sp, $sp, -4\n");

        break;
      
      case ADI:
      
        printf("ADI\n");
      
        fprintf(f, "\taddiu $sp, $sp, 4\n");
        fprintf(f, "\tlw $t1, 4($sp)\n");
        fprintf(f, "\taddu $a0, $a0, $t1\n");
        fprintf(f, "\tsw $a0, 4($sp)\n");

        break;
      
      case SBI:
      
        printf("SBI\n");
      
        fprintf(f, "\taddiu $sp, $sp, 4\n");
        fprintf(f, "\tlw $t1, 4($sp)\n");
        fprintf(f, "\tsubu $a0, $t1, $a0\n");
        fprintf(f, "\tsw $a0, 4($sp)\n");
      
        break;
      
      case MPI:
      
        printf("MPI\n");
      
        fprintf(f, "\taddiu $sp, $sp, 4\n");
        fprintf(f, "\tlw $t1, 4($sp)\n");
        fprintf(f, "\tmul $a0, $t1, $a0\n");
        fprintf(f, "\tsw $a0, 4($sp)\n");
      
        break;
      
      case DVI:
      
        printf("DVI\n");
      
        fprintf(f, "\taddiu $sp, $sp, 4\n");
        fprintf(f, "\tlw $t1, 4($sp)\n");
        fprintf(f, "\tdiv $a0, $t1, $a0\n");
        fprintf(f, "\tsw $a0, 4($sp)\n");
      
        break;
      
      case MOD:
      
        printf("MOD\n");
      
        fprintf(f, "\taddiu $sp, $sp, 4\n");
        fprintf(f, "\tlw $t1, 4($sp)\n");
        fprintf(f, "\tdiv $a0, $t1, $a0\n");
        fprintf(f, "\tmfhi $a0\n");
        fprintf(f, "\tsw $a0, 4($sp)\n");
      
        break;
      
      case LDA:
        printf("LDA %s\n", l->instr->args.varName);
      
        fprintf(f, "\tla $a0, %s\n", l->instr->args.varName);
        fprintf(f, "\tsw $a0, 0($sp)\n");
        fprintf(f, "\taddiu $sp, $sp, -4\n");
      
        break;
      
      case LOD:
        printf("LOD %s\n", l->instr->args.varName);
      
        fprintf(f, "\tlw $a0, %s\n", l->instr->args.varName);
        fprintf(f, "\tsw $a0, 0($sp)\n");
        fprintf(f, "\taddiu $sp, $sp, -4\n");
      
        break;
      
      case STO:
        printf("STO\n");
      
        fprintf(f, "\taddiu $sp, $sp, 4\n");
        fprintf(f, "\tlw $t1, 4($sp)\n");
        fprintf(f, "\tsw $a0, ($t1)\n");
        
        break;
      
      case LABEL:
      
        printf("LABEL %s\n", l->instr->args.varName);

        fprintf(f, "%s:\n", l->instr->args.varName);

        break;
      
      case UJP:
        
        printf("UJP %s\n", l->instr->args.varName);

        fprintf(f, "\tj %s\n", l->instr->args.varName);

        break;
      
      case BEQZ:
        
        printf("BEQZ %s\n", l->instr->args.varName);

        fprintf(f, "\taddiu $sp, $sp, 4\n");
        fprintf(f, "\tlw $t1, 0($sp)\n");
        fprintf(f, "\tbeqz $t1, %s\n", l->instr->args.varName);
        
        break;

      case BNE:
        
        printf("BNE %s\n", l->instr->args.varName);

        fprintf(f, "\taddiu $sp, $sp, 4\n");
        fprintf(f, "\tlw $t1, 0($sp)\n");
        fprintf(f, "\tbne $t1, %s\n", l->instr->args.varName);
        
        break;

      case ANDI:

        printf("ANDI\n");
        
        fprintf(f, "\taddiu $sp, $sp, 4\n");
        fprintf(f, "\tlw $t1, 4($sp)\n");
        fprintf(f, "\tsne $t1, $t1, $zero\n");
        fprintf(f, "\tsne $a0, $a0, $zero\n");
        fprintf(f, "\tand $a0, $a0, $t1\n");
        fprintf(f, "\tsw $a0, 4($sp)\n");

        break;

      case ORI:

        printf("ORI\n");
        
        fprintf(f, "\taddiu $sp, $sp, 4\n");
        fprintf(f, "\tlw $t1, 4($sp)\n");
        fprintf(f, "\tsne $t1, $t1, $zero\n");
        fprintf(f, "\tsne $a0, $a0, $zero\n");
        fprintf(f, "\tor $a0, $a0, $t1\n");
        fprintf(f, "\tsw $a0, 4($sp)\n");

        break;

      case SEQ:

        printf("SEQ\n");

        fprintf(f, "\taddiu $sp, $sp, 4\n");
        fprintf(f, "\tlw $t1, 4($sp)\n");
        fprintf(f, "\tseq $a0, $a0, $t1\n");
        fprintf(f, "\tsw $a0, 4($sp)\n");

        break;

      case SNE:

        printf("SNE\n");

        fprintf(f, "\taddiu $sp, $sp, 4\n");
        fprintf(f, "\tlw $t1, 4($sp)\n");
        fprintf(f, "\tsne $a0, $a0, $t1\n");
        fprintf(f, "\tsw $a0, 4($sp)\n");

        break;

      case SGT:

        printf("SGT\n");

        fprintf(f, "\taddiu $sp, $sp, 4\n");
        fprintf(f, "\tlw $t1, 4($sp)\n");
        fprintf(f, "\tsgt $a0, $t1, $a0\n");
        fprintf(f, "\tsw $a0, 4($sp)\n");

        break;

      case SGE:

        printf("SGE\n");

        fprintf(f, "\taddiu $sp, $sp, 4\n");
        fprintf(f, "\tlw $t1, 4($sp)\n");
        fprintf(f, "\tsge $a0, $t1, $a0\n");
        fprintf(f, "\tsw $a0, 4($sp)\n");

        break;

      case SLT:

        printf("SLT\n");

        fprintf(f, "\taddiu $sp, $sp, 4\n");
        fprintf(f, "\tlw $t1, 4($sp)\n");
        fprintf(f, "\tslt $a0, $t1, $a0\n");
        fprintf(f, "\tsw $a0, 4($sp)\n");

        break;

      case SLE:

        printf("SLE\n");
        
        fprintf(f, "\taddiu $sp, $sp, 4\n");
        fprintf(f, "\tlw $t1, 4($sp)\n");
        fprintf(f, "\tsle $a0, $t1, $a0\n");
        fprintf(f, "\tsw $a0, 4($sp)\n");

        break;

      case READ:

        printf("READ\n");
        
        fprintf(f, "\tli $v0, 5\n");
        fprintf(f, "\tsyscall\n");
        fprintf(f, "\tsw $v0, %s\n", l->instr->args.varName);

        break;

      case WRT:

        printf("WRT\n");
        
        fprintf(f, "\tli $v0, 4\n");
        fprintf(f, "\tla $a0, string_%d\n", l->instr->args.arg);
        fprintf(f, "\tsyscall\n");

        break;

      case WRT_VAR:

        printf("WRT\n");

        fprintf(f, "\tli $v0, 1\n");
        fprintf(f, "\tlw $a0, %s\n", l->instr->args.varName);
        fprintf(f, "\tsyscall\n");

        break;

    }
    l = l->next;
  }
}


Stack* compileExpr(Expr* expr) {
  Stack* result;
  if (expr == 0) {
    yyerror("Null expression!!");
  }
  else if (expr->kind == E_INTEGER) {
    result = mkList(mkInstruction(LDC, expr->attr.value), NULL);
   
  }
  else if (expr->kind == E_VAR) {
    result = append(mkList(mkInstruction_2(LOD, expr->attr.var_name), NULL), NULL);

  }
  
  else if (expr->kind == E_OPERATION) {

    result = append(compileExpr(expr->attr.op.left), compileExpr(expr->attr.op.right));

    switch (expr->attr.op.operator) {
      case PLUS:
        result = append(result, mkList(mkInstruction(ADI, 0), NULL));
        break;
      case MINUS:
        result = append(result, mkList(mkInstruction(SBI, 0), NULL));
        break;
      case MULT:
        result = append(result, mkList(mkInstruction(MPI, 0), NULL));
        break;
      case DIV:
        result = append(result, mkList(mkInstruction(DVI, 0), NULL));
        break;
      case MOD:
        result = append(result, mkList(mkInstruction(MOD, 0), NULL));
        break;
      case EQ:
        result = append(result, mkList(mkInstruction(SEQ, 0), NULL));
        break;
      case NEQ:
        result = append(result, mkList(mkInstruction(SNE, 0), NULL));
        break;
      case LT:
        result = append(result, mkList(mkInstruction(SLT, 0), NULL));
        break;
      case GT:
        result = append(result, mkList(mkInstruction(SGT, 0), NULL));        
        break;
      case LTE:
        result = append(result, mkList(mkInstruction(SLE, 0), NULL));        
        break;
      case GTE:
        result = append(result, mkList(mkInstruction(SGE, 0), NULL));        
        break;
      case AND:
        result = append(result, mkList(mkInstruction(ANDI, 0), NULL));        
        break;
      case OR:
        result = append(result, mkList(mkInstruction(ORI, 0), NULL));        
        break;
      
      default: yyerror("Unknown operator!");
    }
  }
  return result;
}

void mipsEnd() {
  fprintf(f, "\tli $v0, 10\n");
  fprintf(f, "\tsyscall\n");
}

int main(int argc, char** argv) {
  --argc; ++argv;
  if (argc != 0) {
    yyin = fopen(*argv, "r");
    if (!yyin) {
      printf("'%s': could not open file\n", *argv);
      return 1;
    }
  } //  yyin = stdin
  if (yyparse() == 0) {

      char outFileName[300];

      sprintf(outFileName, "%s.asm", *argv);

      // f = fopen("file.asm", "w");
      f = fopen(outFileName, "w");

      vlist = newVarList();
      Stack* result_ = compileCMD(root);

      printData();
      printInstr(result_);
      
      mipsEnd();

      fclose(f);
  }
  return 0;
}

int while_count = 0;
int if_count = 0;

Stack* compileCMD(CmdList* cmd_list) {
  int result = 0;
  Stack* result_ = mkList(mkInstruction_2(NLL, "init"), NULL);

  while(cmd_list!=NULL) {
    
    Cmd* cmd = cmd_list->cmd;
    if (cmd == 0)
      yyerror("Null expression!!");
    else{
      switch(cmd->kind){
        case ATTRIBUTION:{
          addNode(cmd->attr.op.varName, 0);
          result_ = append(result_, append(mkList(mkInstruction_2(LDA, cmd->attr.op.varName), NULL), compileExpr(cmd->attr.op.expr)));
          result_ = append(result_, mkList(mkInstruction(STO, 0), NULL));

        }break;
        case ATTRIBUTION_EXIST:{
        
          result_ = append(result_, append(mkList(mkInstruction_2(LDA, cmd->attr.op.varName), NULL), compileExpr(cmd->attr.op.expr)));
          result_ = append(result_, mkList(mkInstruction(STO, 0), NULL));
        
        }break;
        case PRINT_S:{
        
          char buffer[300];
          sprintf(buffer, "\tstring_%d: .asciiz %s\n", string_count, cmd->attr.string);
          addNode(buffer, 1);
          result_ = append(result_, mkList(mkInstruction(WRT, string_count), NULL));

          string_count++;
          
        }break;
        case PRINT_VAR_S:{
        
          char buffer[300];
          sprintf(buffer, "\tstring_%d: .asciiz %s\n", string_count, cmd->attr.op_print.string);
          addNode(buffer, 1);          
          result_ = append(result_, mkList(mkInstruction(WRT, string_count), NULL));
          result_ = append(result_, mkList(mkInstruction_2(WRT_VAR, cmd->attr.op_print.varName), NULL));          
          
          string_count++;
          
        }break;
        case SCAN_S:{
          
          result_ = append(result_, mkList(mkInstruction_2(READ, cmd->attr.op_scan.varName), NULL));
          
        }break;
        case IF_S:{
          
          char else_init[20];
          
          sprintf(else_init, "if_end%d", if_count);

          result_ = append(result_, compileExpr(cmd->attr.op_if.expr));
          result_ = append(result_, mkList(mkInstruction_2(BEQZ, else_init), NULL));
          result_ = append(result_, compileCMD(cmd->attr.op_if.cl_if));
          result_ = append(result_, mkList(mkInstruction_2(LABEL, else_init), NULL));

          if_count++;

        }break;
        case IF_ELSE_S:{
          
          char else_init[20];
          char else_end[20];
          
          sprintf(else_init, "else_init%d", if_count);
          sprintf(else_end, "else_end%d", if_count);

          result_ = append(result_, compileExpr(cmd->attr.op_while.expr));
          result_ = append(result_, mkList(mkInstruction_2(BEQZ, else_init), NULL));
          result_ = append(result_, compileCMD(cmd->attr.op_if_else.cl_if));
          result_ = append(result_, mkList(mkInstruction_2(UJP, else_end), NULL));
          result_ = append(result_, mkList(mkInstruction_2(LABEL, else_init), NULL));
          result_ = append(result_, compileCMD(cmd->attr.op_if_else.cl_if_else));
          result_ = append(result_, mkList(mkInstruction_2(LABEL, else_end), NULL));

          if_count++;

        }break;
        case WHILE_S:{
          
          char w[20];
          char wo[20];
          
          sprintf(w, "while_%d", while_count);
          sprintf(wo, "while_out_%d", while_count);
          
          result_ = append(result_, mkList(mkInstruction_2(LABEL, w), NULL));
          result_ = append(result_, compileExpr(cmd->attr.op_while.expr));
          result_ = append(result_, mkList(mkInstruction_2(BEQZ, wo), NULL));
          result_ = append(result_, compileCMD(cmd->attr.op_while.cl_while));
          result_ = append(result_, mkList(mkInstruction_2(UJP, w), NULL));
          result_ = append(result_, mkList(mkInstruction_2(LABEL, wo), NULL));

          while_count++;
        }break;
        default: printf("ERROR\n");
      }
    }

    cmd_list = cmd_list->next;
  }

  return result_;
}
