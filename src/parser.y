%{
#include "ClassDefs.h"
#include <bits/stdc++.h>

  extern "C" int yylex();
  extern "C" int yyparse();
  extern "C" FILE *yyin;
  extern "C" int line_num;
  extern union Node yylval;
  extern "C" int errors;
  void yyerror(const char *s);
  class program* start = NULL;
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
%token <ch> '*'
%token ARR_ID
%token ARR_NUM
%token EQEQ
%token EQUAL
%token IF
%token ELSE	
%token OR 		
%token AND		
%token NOTEQ
%token WHILE
%token GOTO
%token LABEL
%token READ
%token TOPRINT
%token PRINT
%token FOR
%token <ch> SUBEQ
%token <ch> ADDEQ


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

%type <program> program
%type <decls> declblocks
%type <decl> declblock
%type <codes> codeblocks
%type <code> codeblock
%type <vars> variables
%type <var> variable
%type <assign> Assign
%type <ifst> If
%type <forst> For
%type <whilest> While
%type <gotost> Goto
%type <printst> Print
%type <readst> Read
%type <binexpr> expr
%type <last> Last
%type <boolExpr> BoolExp






%%

program: DECL '{' declblocks '}' CODE '{' codeblocks '}' {
	$$ = new program($3,$7);
}

declblocks : { $$ = new declblocks(); }
	| declblocks declblock ';' { $$->push_back($2); }

declblock:
	INT variables { $$ = new declblock(string($1),$2); }

variables:
	variable { $$ = new Vars(); $$->push_back($1); }
	| variables ',' variable { $$->push_back($3); }

variable: 
	ID { $$ = new Var(string("Normal"), string($1)); }
	| ID '[' NUMBER ']' { $$ = new Var(string("Array"),string($1)); }

codeblocks:  { $$ = new codeblocks(); } 
	| codeblocks codeblock ';' { $$->push_back($2); } 

codeblock: Assign { $$ = $1; }
	| If { $$ = $1; }
	| While { $$ = $1; }
	| Goto { $$ = $1; }
/*	| Label { $$ = $1; } */
	| Print { $$ = $1; }
	| Read { $$ = $1; }
	| For { $$ = $1; }

/*-Label: LABEL codeblock { }*/


Last: ID {$$ = new last(string($1),string("Normal"));}
	| ID '[' expr ']' { $$ = new Location(string($1),string("Array"),$3); }

expr: expr '+' expr { $$ = new binExpr($1,string($2),$3); }
	| expr '-' expr { $$ = new binExpr($1,string($2),$3); }
	| expr '*' expr { $$ = new binExpr($1,string($2),$3); }
	| expr '/' expr { $$ = new binExpr($1,string($2),$3); }
	| NUMBER { $$ = $1; }
	| Last { $$ = $1; }




Assign: 
	Last '=' expr ';'  { $$ = new Assign(string($1),string($2), $3); } 
	| Last ADDEQ expr ';'  { $$ = new Assign(string($1), string($2), $3); } 
	| Last SUBEQ expr ';'  { $$ = new Assign(string($1), string($2), $3); } 


/*if you want to add more for_assign statements, currently only using i = 0 type */
for_assign: ID '=' expr 
/*	| ARR_ID '=' expr
	| ARR_NUM '=' expr
*/
Type: EQEQ
	| NOTEQ
	| '<'
	| '>'
	| '<''='
	| '>''='

BoolExp: expr Type expr 
	| BoolExp OR BoolExp
	| BoolExp AND BoolExp

If:  IF BoolExp '{' codeblock '}' { $$ = new ifStmt($2,$4); }
	| IF BoolExp '{' codeblock '}' ELSE '{' codeblock '}' {$$ = new ifStmt($2,$4,$8);}

While : WHILE BoolExp '{' codeblock '}' { $$ = new whileStmt($2,$4); }


For : 
	FOR ID '=' expr ',' NUMBER '{' codeblock '}' { $$ = new forStmt($2,$4,$6,NULL,$8)}
   | FOR ID '=' expr ',' NUMBER ',' NUMBER '{' codeblock '}' { $$ = new forStmt($2,$4,$6,$8,10)}

Goto: GOTO ID IF BoolExp ';' codeblock
	| GOTO ID ';' codeblock

Read: READ ID ';' codeblock

Print : PRINT TOPRINT Content 
      | PRINT ID Content 
      | PRINT ARR_ID Content
      | PRINT NUMBER Content

Content	: ';' codeblock /* epsilon */
      | ',' TOPRINT  Content
      | ',' ID Content
      | ',' ARR_ID Content
      | ',' NUMBER Content



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
	error_flag=0;
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
	if(!error_flag){
	printf("Done with no syntactic errors!\n");
	}
}
