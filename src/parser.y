%{
#include "classdef.h"
#include <bits/stdc++.h>

  extern "C" int yylex();
  extern "C" int yyparse();
  extern "C" FILE *yyin;
  extern "C" int line_num;
  extern union Node yylval;
  extern "C" int errors;
  void yyerror(const char *s);
  class program* start = NULL;
  extern "C" int error_flag;
  int errors=0;
%}


%locations

/*%option yylineno*/
%start program

%token DECL
%token CODE
%token <number> NUMBER
%token <ch> INT
%token <ch> ID
%token ETOK
%token <ch> '+'
%token <ch> '='
%token <ch> '-'
%token <ch> '/'
%token <ch> ':'
%token <ch> '*'
%token <ch> '<'
%token <ch> '>'
%token ARR_ID
%token ARR_NUM
%token <ch> EQEQ
%token EQUAL
%token IF
%token ELSE	
%token <ch> OR 		
%token <ch> AND		
%token <ch> NOTEQ
%token <ch> LESSEQ
%token <ch> MOREEQ
%token WHILE
%token GOTO
%token LABEL
%token READ
%token <ch> TOPRINT
%token PRINT
%token FOR
%token <ch> SUBEQ
%token <ch> ADDEQ
%token <ch> PRINTLN


%left EQEQ
%left LTEQ
%left NOTEQ
%left GTEQ
%left '<'
%left '>'
%left OR
%left AND
%left '+'
%left '-'
%left '*' 
%left '/'
%left '='

%type <prog> program
%type <decls> declblocks
%type <decl> declblock
%type <codes> codeblocks
%type <code> codeblock
%type <vars> variables
%type <var> variable
%type <assign> Assign
%type <whilest> While
%type <ifst> If
%type <gotost> Goto
%type <forst> For
%type <printst> Print
%type <readst> Read 
%type <binexpr> expr
%type <last> Last
%type <boolex> BoolExp
%type <optype> Type
%type <unit> terminal
%type <expr> exp
%type <printst> Contents 
%type <contnt> Content

%%

program: DECL '{' declblocks '}' CODE '{' codeblocks '}' {
	$$ = new program($3,$7);
	start = $$;
}

terminal: ID { $$ = new unitClass("id", string($1)); }
	| NUMBER { $$ = new unitClass("num", $1); }


declblocks : { $$ = new declblocks(); }
	| declblocks declblock ';' { $$->push_back($2); }

declblock:
	INT variables { $$ = new declblock($2); }

variables:
	variable { $$ = new Vars(); $$->push_back($1); }
	| variables ',' variable { $$->push_back($3); }

variable: 
	ID { $$ = new Var(string("Normal"), string($1)); }
	| ID '['  NUMBER ']' { $$ = new Var(string("Array"),string($1),$3); }
	| ID '=' NUMBER { $$ = new Var(string("NormalInit"),string($1),"1",$3); }
	| ID '=' '-' NUMBER { $$ = new Var(string("NormalInit2"),string($1),"1",-1*$4); }

codeblocks:  { $$ = new codeblocks(); } 
	| codeblocks codeblock  { $$->push_back($2);  } 
	| codeblocks ID ':' codeblock{ $$->push_back($4,$2); } 

codeblock: Assign ';' { $$ = $1; }
	| If { $$ = $1; } 
	| While { $$ = $1;  } 
	| Goto ';' { $$ = $1; } 
	| Print ';' { $$ = $1; } 
	| Read ';' { $$ = $1; } 
	| For { $$ = $1; } 

Last: ID {$$ = new last(string($1),string("Normal"));}
	| ID '[' exp ']' { $$ = new last(string($1),string("Array"),$3); }

exp : expr { $$ = new Expr("expr", $1); }
	| NUMBER { $$ = new Expr("num", $1); }
	| Last { $$ = new Expr("last", $1); }
	| '-' NUMBER { $$ = new Expr("num", -1*$2); }

expr: exp '+' exp { $$ = new binExpr($1,"+",$3); }
	| exp '-' exp { $$ = new binExpr($1,"-",$3); }
	| exp '*' exp { $$ = new binExpr($1,"*",$3); }
	| exp '/' exp { $$ = new binExpr($1,"/",$3); }


Assign: Last '=' exp  { $$ = new Assign(($1), "=", $3); } 
	| Last ADDEQ exp  { $$ = new Assign(($1), "+=", $3); } 
	| Last SUBEQ exp  { $$ = new Assign(($1), "-=", $3); } 


Type: EQEQ { $$ = new OperandType(string("==")); } 
	| NOTEQ { $$ = new OperandType(string("!=")); }
	| MOREEQ { $$ = new OperandType(string(">=")); }
	| LESSEQ { $$ = new OperandType(string("<=")); }
	| '<' { $$ = new OperandType(string("<")); }
	| '>' { $$ = new OperandType(string(">")); }

BoolExp: exp Type exp { $$ = new boolExpr("expr",$1, $2, $3); }
	| BoolExp OR BoolExp { $$ = new boolExpr("bool", $1, "OR", $3); }
	| BoolExp AND BoolExp { $$ = new boolExpr("bool", $1, "AND", $3); }

If:  IF BoolExp '{' codeblocks '}' { $$ = new ifStmt("if", $2,$4); }
	| IF BoolExp '{' codeblocks '}' ELSE '{' codeblocks '}' {$$ = new ifStmt("else", $2,$4,$8);}

While : WHILE BoolExp '{' codeblocks '}' { $$ = new whileStmt($2,$4);  }


For : 
	FOR ID '=' exp ',' terminal '{' codeblocks '}' { $$ = new forStmt($2,$4,$6,$8); }
   | FOR ID '=' exp ',' terminal ',' terminal '{' codeblocks '}' { $$ = new forStmt($2,$4,$6,$8,$10); }

Goto: GOTO ID IF BoolExp { $$ = new gotoStmt("cond", $2, $4); }
	| GOTO ID { $$ = new gotoStmt("uncond", $2); }

Read: READ Last { $$ = new readStmt($2); }

Print: PRINT Contents Content { $$ = $2; $$->type = 1; $$->push_back($3); }
	| PRINTLN Contents Content { $$ = $2; $$->type = 2; $$->push_back($3); }

Contents: { $$ = new printStmt(); }
	| Contents Content ',' { $$->push_back($2); }

Content	: TOPRINT { $$ = new content($1,"string"); }
	| Last { $$ = new content($1,"last"); }
	| NUMBER { $$ = new content($1,"num"); }


/*
expr: 	expr '+' expr 
	|	expr '*' expr 
	| 	NUMBER
	|	IDENTIFIER
	;
*/

%%



int main(int argc, char *argv[])
{
	//error_flag=0;
	if (argc == 1){
		fprintf(stderr, "Correct usage: bcc filename\n");
		exit(1);
	}

	if (argc > 2) {
		fprintf(stderr, "Passing more arguments than necessary.\n");
		fprintf(stderr, "Correct usage: bcc filename\n");
	}

	yyin = fopen(argv[1], "r");
	yyparse();
	Interpreter *it = new Interpreter();
	start->accept(it);
	start->codegen();
	start->generateCode();
	//if(!error_flag){
	//printf("Done with no syntactic errors!\n");
	//}
}
