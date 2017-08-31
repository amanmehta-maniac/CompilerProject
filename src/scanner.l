%{
#include "parser.tab.h"
%}
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
string	\"(\\.|[^\\"])*\"
goto	(goto)
number {digit}{digit}*
semicolon [;] 

%%
"declblock"					return DECL;
"codeblock"					return CODE;

{equal}{equal} {
	printf ("lmao %s\n",yytext);
	return EQEQ;
}
{semicolon}{semicolon}+	{
			printf("Token type: ERROR! multiple semicolon, Lexeme/Token Value: %s\n", yytext);  
			return 1;
}
{dint}{space} {  
			printf("Token type: Datatype:int, Lexeme/Token Value: %s\n", yytext);  
			return INT;
                } 
{id}{space}*":" {
			printf("Token type: Datatype:label, Lexeme/Token Value: %s\n", yytext);  
			return LABEL;

}
{string} {
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
			printf("Token type: ID, Lexeme/Token Value: %s\n", yytext);  
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
";"		return ';';
"," 	return ',';
"=" 	return '=';
"<"		return '<';
">"		return '>';


[ \t]		{ /* Do nothing */ }
.		{ 
		  printf("Unexpected token encountered: %s\n", yytext); 
		  return ETOK;
		}


