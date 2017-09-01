%{
#include "parser.tab.h"
#include "temp.h"

%}

%option yylineno

dint	(int)
equal	(=)
space 	[\t\n ]
id      [a-zA-z][a-zA-Z0-9]*
digit   [0-9]
IF 		(if)
ELSE	(else)
OR 		(or)
AND		(and)
while		(while)
string_l	\"(\\.|[^\\"])*\"
goto	(goto)
number {digit}{digit}*
semicolon [;] 
colon [:]



%%
"declblock"					return DECL;
"codeblock"					return CODE;

{equal}{equal} {
	printf ("lmao %s\n",yytext);
	return EQEQ;
}
{semicolon}{semicolon}+	{
			printf(" Token type: ERROR! multiple semicolon, Lexeme/Token Value: %s \n",yytext);  
			return 1;
}
{dint}{space} {  
			printf("Token type: Datatype:int, Lexeme/Token Value: %s\n", yytext);  
			return INT;
                } 
"for"	{
			printf("Token type: Datatype: for, Lexeme/Token Value: %s\n", yytext);  
			return FOR;
		}

{id}{colon} {
			printf("Token type: Datatype:label, Lexeme/Token Value: %s\n", yytext);  
			return LABEL;

}

"<=" {
			printf("Token type: Datatype:label, Lexeme/Token Value: %s\n", yytext);  
			return LTEQ;

}

">=" {
			printf("Token type: Datatype:, Lexeme/Token Value: %s\n", yytext);  
			return GTEQ;

}
"print"{space} {
			printf("Token type: Datatype: print, Lexeme/Token Value: %s\n", yytext);  
			return PRINT;

}
{string_l} {
			printf("Token type: Datatype:string, Lexeme/Token Value: %s\n", yytext);  
			return TOPRINT;

}
{goto}{space} {  
			printf("Token type: Datatype:goto, Lexeme/Token Value: %s\n", yytext);  
			return GOTO;
                } 
{id}"["{number}"]"	{
			printf("Token type: Datatype:int, Lexeme/Token Value: %s\n", yytext);  
			return ID;
		}
{id}"["{id}"]"	{
			printf("Token type: Datatype:int, Lexeme/Token Value: %s\n", yytext);  
			return ARR;
		}

"read" {
			printf("Token type: Datatype:int, Lexeme/Token Value: %s\n", yytext);  
			return READ;
}

{IF} {
			printf("Token type: Number, Lexeme/Token Value: %s\n", yytext);  
			return IF; 

}          
{ELSE} {
			printf("Token type: Number, Lexeme/Token Value: %s\n", yytext);  
			return ELSE; 

}          
{OR} {
			printf("Token type: Number, Lexeme/Token Value: %s\n", yytext);  
			return OR; 

}          
{AND} {
			printf("Token type: Number, Lexeme/Token Value: %s\n", yytext);  
			return AND; 

}          
"!"{equal} {
			printf("Token type: Number, Lexeme/Token Value: %s\n", yytext);  
			return NOTEQ; 

}          
{while} {
			printf("Token type: Number, Lexeme/Token Value: %s\n", yytext);  
			return WHILE; 

}

{id}		{
			printf("%d, Token type: ID, Lexeme/Token Value: %s\n", yylineno,yytext);  
			return ID;
                } 
{number}	{  
			printf("Token type: Number, Lexeme/Token Value: %s\n", yytext);  
			return NUMBER; 
                }



"+"		return '+';
"-"		return '-';
"*"		return '*';
"{"		return '{';
"}"		return '}';
";"		{
		yylineno += 1;
		return ';';
	}
"," 	return ',';
"=" 	return '=';
"<"		return '<';
">"		return '>';

[ \t]		{ 
		}
.		{ 
		  printf("Unexpected token encountered: %s\n", yytext);
		  error_flag = 1;
		  return ETOK;
		}

%%
void yyerror (char const *s)
{
	printf("ERROR at (or near) Statement number -> %d\n",yylineno);
	error_flag = 1;
    fprintf (stderr, "%s\n", s);
}


