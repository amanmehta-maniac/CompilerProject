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
  class Prog* start = NULL;
  int errors=0;
%}


%locations

/*%option yylineno*/
%token DECL
%token CODE
%token NUMBER
%token ID
%token INT
%token ETOK
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

%%

program: declblock codeblock {
	$$ = new program($1,$2);
}

declblock: DECL '{' Define '}' 


Define : INT X { $$ = new declblock(string($1), $2); }
	| {$$ = new declblocks();}



X : ID ',' X { $$->push_back($3) }
	| ID '=' NUMBER ',' X { $$->push_back($3) }
	| last { $$ = new Vars(); $$->push_back($1); }


last : ID ';' Define { $$ = new Var(string("Normal"),string($1),string("NULL")); }
	| ID '=' NUMBER ';' Define { $$ = new Var(string("Normal"),string($1),$3); }
	| ARR_NUM ';' Define { $$ = new Var(string("Array")); }




codeblock: CODE '{' Expr '}'

Expr: Assign
	| If
	| While
	| Goto
	| Label
	| Print 
	| Read
	| For Expr
	|

Label: LABEL Expr

expr: expr '+' expr 
	| expr '-' expr 
	| expr '*' expr 
	| expr '/' expr 
	| ID 
	| NUMBER 
	| ARR_ID

Assign: ID '=' expr ';' Expr
	| ARR_ID '=' expr ';' Expr

for_assign: ID '=' expr 
	| ARR_ID '=' expr

Type: EQEQ
	| NOTEQ
	| '<'
	| '>'
	| '<''='
	| '>''='

BoolExp: expr Type expr
	| BoolExp OR BoolExp
	| BoolExp AND BoolExp

If:  IF BoolExp '{' Expr '}' Expr
	| IF BoolExp '{' Expr '}' ELSE '{' Expr '}' Expr

While : WHILE BoolExp '{' Expr '}' Expr


For : FOR for_assign ',' NUMBER '{' Expr '}' 
   | FOR for_assign ',' NUMBER ',' NUMBER '{' Expr '}' 

Goto: GOTO ID IF BoolExp ';' Expr
	| GOTO ID ';' Expr

Read: READ ID ';' Expr

Print : PRINT TOPRINT Content 
      | PRINT ID Content 
      | PRINT ARR_ID Content
      | PRINT NUMBER Content

Content	: ';' Expr/* epsilon */
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
