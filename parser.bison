// Tokens
%token
  INT
  PLUS
  MINUS
  MULT
  DIV
  MOD
  AMPE
  COMMA
  EQ
  NEQ
  LT
  GT
  LTE
  GTE
  TRUE
  FALSE
  AND
  OR
  NOT
  OB
  CB
  INT_TYPE
  FLOAT_TYPE
  CHAR_TYPE
  MAIN
  OSB
  CSB
  VAR_NAME
  ATTR
  SC
  PRINT
  SCAN
  IF
  ELSE
  WHILE
  STRING

%left AND OR
%left EQ NEQ LT GT LTE GTE
// Operator associativity & precedence
%left PLUS MINUS
%left MULT DIV
%left MOD
//%left OR



// Root-level grammar symbol
%start program;

// Types/values in association to grammar symbols.
%union {
  int intValue;
  char* varName;
  char* stringPrint;
  Expr* exprValue;
  ExprList* exprList;
  CmdList* cmdList;
  Cmd* cmd_;
  BoolExpr* boolValue;
  int booll;
}

%type <intValue> INT
%type <varName> VAR_NAME
%type <stringPrint> STRING
%type <exprValue> expr
//%type <exprValue> bexpr
%type <booll> TRUE
%type <booll> FALSE
// %type <exprList> expr_list
%type <cmdList> cmd_list
%type <cmd_> cmd
%type <cmd_> cmd_var
%type <cmd_> cmd_printf
%type <cmd_> cmd_scanf
%type <cmd_> cmd_if
%type <cmd_> cmd_while


// Use "%code requires" to make declarations go
// into both parser.c and parser.h
%code requires {
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

extern int yylex();
extern int yyline;
extern char* yytext;
extern FILE* yyin;
extern void yyerror(const char* msg);
CmdList* root;
}

%%
program: INT_TYPE MAIN OB CB OSB cmd_list CSB { root = $6; }

cmd_list:
    cmd { $$ = ast_cmdlist($1, NULL); }
  | cmd cmd_list { $$ = ast_cmdlist($1, $2); }

cmd:
  cmd_var { $$ = $1; }
  | cmd_printf { $$ = $1; }
  | cmd_scanf { $$ = $1; }
  | cmd_if { $$ = $1; }
  | cmd_while { $$ = $1; }

cmd_var:
    INT_TYPE VAR_NAME SC { $$ = ast_attribution($2, ast_integer(0)); }
    | INT_TYPE VAR_NAME ATTR expr SC { $$ = ast_attribution($2, $4); }
    | VAR_NAME ATTR expr SC { $$ = ast_attribution_exist_variable($1, $3); }

cmd_printf:
    PRINT OB STRING CB SC { $$ = ast_print($3); }
    | PRINT OB STRING COMMA VAR_NAME CB SC { $$ = ast_print_var($3, $5); }

cmd_scanf:
    SCAN OB VAR_NAME CB  SC { $$ = ast_scan($3); }

cmd_if:
    IF OB expr CB OSB cmd_list CSB { $$ = ast_if($3, $6); }
    | IF OB expr CB OSB cmd_list CSB ELSE OSB cmd_list CSB{ $$ = ast_if_else($3, $6, $10); }

cmd_while:
    WHILE OB expr CB OSB cmd_list CSB{ $$ = ast_while($3, $6); }

// expr_list:
//     expr { $$ = ast_exprlist($1, NULL); }
//   | expr expr_list { $$ = ast_exprlist($1, $2); }

expr:
  INT { $$ = ast_integer($1); }
  | VAR_NAME {$$ = ast_var_name($1); }
  | MINUS expr{$$ = ast_invert_val($2); }
  | OB expr CB { $$ = $2; }
  | expr PLUS expr { $$ = ast_operation(PLUS, $1, $3); }
  | expr MINUS expr { $$ = ast_operation(MINUS, $1, $3); }
  | expr MULT expr { $$ = ast_operation(MULT, $1, $3); }
  | expr DIV expr { $$ = ast_operation(DIV, $1, $3); }
  | expr MOD expr { $$ = ast_operation(MOD, $1, $3); }

  | expr EQ  expr { $$ = ast_operation(EQ,  $1, $3); }
  | expr NEQ expr { $$ = ast_operation(NEQ, $1, $3); }
  | expr LT  expr { $$ = ast_operation(LT,  $1, $3); }
  | expr GT  expr { $$ = ast_operation(GT,  $1, $3); }
  | expr LTE expr { $$ = ast_operation(LTE, $1, $3); }
  | expr GTE expr { $$ = ast_operation(GTE, $1, $3); }
  | expr AND expr { $$ = ast_operation(AND, $1, $3); }
  | expr OR  expr { $$ = ast_operation(OR,  $1, $3); }

  ;
%%

void yyerror(const char* err) {
  printf("Line %d: %s - '%s'\n", yyline, err, yytext  );
}
