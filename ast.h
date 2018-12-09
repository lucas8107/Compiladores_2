
// AST definitions
#ifndef __ast_h__
#define __ast_h__

typedef struct _Instr {
  enum {
    LDC,  //OK
    ADI,  //OK
    SBI,  //OK
    MPI,  //OK
    DVI,  //OK
    LOD,  //OK
    STO,  //OK
    RDI,
    FJP,
    BEQZ, //OK
    BNE,
    WRT,  //OK
    WRT_VAR, //OK
    READ, //OK
    UJP,  //OK
    LABEL,//OK
    ANDI,
    ORI,
    SGT,  //OK
    SGE,  //OK
    SLT,  //OK
    SLE,  //OK
    SEQ,  //OK
    SNE,  //OK
    LDA,  //OK
    NLL
  } kind;
  union {
    int arg;
    char* varName;
  } args;
} Instr;

// AST for expressions
struct _Expr {
  enum {
    E_INTEGER,
    E_OPERATION,
    E_VAR,
    E_OPERATION_INVERT
  } kind;
  union {
    int value; // for integer values
    struct {
      int operator; // PLUS, MINUS, etc
      struct _Expr* left;
      struct _Expr* right;
    } op; // for binary expressions
    char* var_name; //for variable
    struct {
      struct _Expr* expr;
    } op_invert;
  } attr;
};

struct _Cmd {
  enum {
    ATTRIBUTION,
    ATTRIBUTION_EXIST,
    PRINT_S,
    PRINT_VAR_S,
    SCAN_S,
    IF_S,
    IF_ELSE_S,
    WHILE_S
  } kind;
  union {
    char* string;
    struct {
      char* varName;
      struct _Expr* expr;
    } op;
    struct {
      char* str;
      char* varName;
    } op_scan;
    struct {
      struct _Expr* expr;
      struct _CmdList* cl_if;
    } op_if;
    struct {
      struct _Expr* expr;
      struct _CmdList* cl_if;
      struct _CmdList* cl_if_else;
    } op_if_else;
    struct {
      struct _Expr* expr;
      struct _CmdList* cl_while;
    } op_while;
    struct {
      char* string;
      char* varName;
    } op_print;
  } attr;
};

struct _CmdList {
  struct _Cmd* cmd;
  struct _CmdList* next;
};

struct _BoolExpr {
  enum {
    B_INTEGER,
    B_OPERATION
  } kind;
  union {
    int value;
    struct {
      int operator;
      struct _BoolExpr* left;
      struct _BoolExpr* right;
    } op;

  } attr;
};

typedef struct _Expr Expr; // Convenience typedef
typedef struct _ExprList ExprList; // Convenience typedef
typedef struct _BoolExpr BoolExpr;
typedef struct _Cmd Cmd;
typedef struct _CmdList CmdList;

struct _ExprList {
  struct _Expr* expr;
  struct _ExprList* next;
};
// Constructor functions (see implementation in ast.c)
Expr* ast_integer(int v);
Expr* ast_var_name(char* var_name);
Expr* ast_operation(int operator, Expr* left, Expr* right);
Cmd* ast_attribution_exist_variable(char* name, Expr* expr);
BoolExpr* ast_bool(int v);
BoolExpr* ast_boolexp(int operator, BoolExpr* left, BoolExpr* right);
ExprList* ast_exprlist(Expr* expr, ExprList* next);

Cmd* ast_attribution(char* name, Expr* expr);
Expr* ast_invert_val(Expr* expr);

Cmd* ast_print(char* str);
Cmd* ast_print_var(char* str, char* varName);
Cmd* ast_scan(char* varName);
// Cmd* ast_scan(char* str, char* varName);

Cmd* ast_if(Expr* expr, CmdList* cl_if);
Cmd* ast_if_else(Expr* expr, CmdList* cl_if, CmdList* cl_if_else);
Cmd* ast_while(Expr* expr, CmdList* cl_if);

CmdList* ast_cmdlist(Cmd* cmd, CmdList* next);

Instr* mkInstruction(int kind, int arg);
Instr* mkInstruction_2(int kind, char* arg);
// Expr* ast_integer(int v);
// Expr* ast_operation(int operator, Expr* left, Expr* right);
// Expr* ast_operation_attrib(char* varName, Expr* expr);
// Expr* ast_varName(char* v);

#endif
