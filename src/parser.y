%{
  #include <stdio.h>
  #include <stdlib.h>
  FILE *yyin;
  int yylex (void);
  void yyerror (char const *s);
%}


%locations

/*%option yylineno*/
%token DECL
%token CODE
%token NUMBER
%token ID
%token INT
%token ETOK
%token ARR
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

program:	declblock codeblock

declblock: DECL '{' Define '}' 


Define : INT X 
	|

X : ID ',' X
	| ID '=' NUMBER ',' X
	| last


last : ID ';' Define
	| ID '=' NUMBER ';' Define

codeblock: CODE '{' Expr '}'

Expr: Assign
	| If
	| While
	| Goto
	| Label
	| Print 
	| Read
	| For
	|

Label: LABEL Expr

expr: expr '+' expr 
	| expr '-' expr 
	| expr '*' expr 
	| expr '/' expr 
	| ID 
	| NUMBER 
	| ARR

Assign: ID '=' expr ';' Expr
	| ARR '=' expr ';' Expr

for_assign: ID '=' expr 
	| ARR '=' expr

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
	| GOTO ID ';'

Read: READ ID ';' Expr

Print : PRINT TOPRINT Content 
      | PRINT ID Content 
      | PRINT ARR Content
      | PRINT NUMBER Content

Content	: ';' Expr/* epsilon */
      | ',' TOPRINT  Content
      | ',' ID Content
      | ',' ARR Content
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

}
