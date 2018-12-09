%{
// HEADERS
#include <stdlib.h>
#include <string.h>
#include "parser.h"

// variables maintained by the lexical analyser
int yyline = 1;
%}

%option noyywrap

%%
[ \t]+ {  }
#.*\n { yyline++; }
\n { yyline++; }

[0-9]+ {
   yylval.intValue = atoi(yytext);
   return INT;
}

\".*\" {
    // char buff[strlen(yytext)];
    // memcpy( buff, &yytext[1], strlen(yytext) - 2);
    // buff[strlen(yytext) - 2] = '\0';
    
    // yylval.stringPrint = strcpy(buff);
    // strcpy(yylval.stringPrint, buff);
   
//    yylval.stringPrint = strdup(buff);

   yylval.stringPrint = strdup(yytext);
    return STRING;
}

"printf" { return PRINT; }
"scanf" { return SCAN; }
"if" { return IF; }
"else" {return ELSE; }
"while" {return WHILE; }

"int" { return INT_TYPE; }
"float" { return FLOAT_TYPE; }
"char" { return CHAR_TYPE; }

"main" { return MAIN; }

"{"  { return OSB; }
"}"  { return CSB; }
"\(" { return OB;  }
"\)" { return CB;  }
";"  { return SC;  }

"=" { return ATTR; }
"+" { return PLUS; }
"-" { return MINUS;}
"*" { return MULT; }
"/" { return DIV;  }
"%" { return MOD;  }

"==" { return EQ;  }
"!=" { return NEQ; }
"<"  { return LT;  }
">"  { return GT;  }
"<=" { return LTE; }
">=" { return GTE; }
"&&" { return AND; }
"||" { return OR;  }
"!"  { return NOT; }

"&" { return AMPE; }
"," { return COMMA;}

[a-zA-Z][a-zA-Z0-9_]* {
    yylval.varName = (char*) strdup(yytext);
    return VAR_NAME;
}

.  { yyerror("unexpected character"); }


%%
