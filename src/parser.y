%{
  #include <stdio.h>
  #include <stdlib.h>
  FILE *yyin;
  int yylex (void);
  void yyerror (char const *s);
%}


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



%left '+'
%left '*'
%left '/'
%left '-'
%left '='
%left OR
%left AND
%left EQEQ
%left NOTEQ
%left '<'
%left '>'

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

Type: EQEQ
	| NOTEQ
	| '<'
	| '>'
	| '<''='
	| '>''='

Type2: OR
	| AND

BoolExp: expr Type expr
	| BoolExp Type2 BoolExp


If:  IF BoolExp '{' Expr '}' Expr
	| IF BoolExp '{' Expr '}' ELSE '{' Expr '}' Expr

While : WHILE BoolExp '{' Expr '}' Expr

Goto: GOTO ID IF BoolExp ';' Expr
	| GOTO ID ';'

Read: READ ID ';' Expr

Print   :     PRINT TOPRINT Content
                  |     PRINT ID Content
                  |     PRINT ARR Content
                  |     PRINT NUMBER Content

Content           :      /* epsilon */
                  |     ',' TOPRINT  Content
                  |     ',' ID Content
                  |     ',' ARR Content
                  |     ',' NUMBER Content

/*
expr: 	expr '+' expr 
	|	expr '*' expr 
	| 	NUMBER
	|	IDENTIFIER
	;
*/

%%

void yyerror (char const *s)
{
       fprintf (stderr, "%s\n", s);
}

int main(int argc, char *argv[])
{
	if (argc == 1 ) {
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
