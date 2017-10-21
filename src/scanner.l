%{
#include <bits/stdc++.h>
#include "classdef.h"
#include "parser.tab.h"
#include "temp.h"
#define YY_DECL extern "C" int yylex()

  extern union Node yylval;
  using namespace std;
%}

%option yylineno

dint	"int"
equal	"="
space 	[\t\n ]
id      [a-zA-Z][a-zA-Z0-9]*
digit   [0-9]
IF 		"if"
ELSE	"else"
OR 		"or"
AND		"and"
while		"while"
string_l	\"(\\.|[^\\"])*\"
goto	"goto"
number {digit}{digit}*
semicolon ";" 
colon ":"
ob "["
cb "]"


%%
"declblock"					return DECL;
"codeblock"					return CODE;

"[" return '[';

"]" return ']';


{equal}{equal} {
	return EQEQ;
}

{dint}{space} {  
			yylval.ch = strdup(yytext);
			return INT;
                } 
"for"	{
			return FOR;
		}


"print"{space} {
			return PRINT;

}
"println"{space} {
			return PRINT;

}
{string_l} {
			return TOPRINT;

}
{goto}{space} {  
			return GOTO;
                } 
"read" {
			return READ;
}

{IF} {
			return IF; 

}          
{ELSE} {
			return ELSE; 

}          
{OR} {
			return OR; 

}          
{AND} {
			return AND; 

}          
{while} {
			return WHILE; 

}



"!=" {
			yylval.ch = strdup(yytext);
			return NOTEQ; 

}
"+=" 	{
			yylval.ch = strdup(yytext);
			return ADDEQ;
}
"-=" 	{
			yylval.ch = strdup(yytext);
			return SUBEQ;
		}

"+"		{
			yylval.ch = strdup(yytext);
			return '+';
		}
":"		{
			yylval.ch = strdup(yytext);
			return ':';
		}
"-"		{
			yylval.ch = strdup(yytext);
			return '-';
		}
"*"		{
			yylval.ch = strdup(yytext);
			return '*';
		}
"{"		{
			yylval.ch = strdup(yytext);
			return '{';
		}
"}"		{
			yylval.ch = strdup(yytext);
			return '}';
		}
";"		{
		yylineno += 1;
			return ';';
	}
"," 	{
			return ',';
		}
"<="	{
			yylval.ch = strdup(yytext);
			return LESSEQ;
		}
">="	{
			yylval.ch = strdup(yytext);
			return MOREEQ;
		}
"=" 	{
			yylval.ch = strdup(yytext);
			return '=';
		}
"<"		{
			yylval.ch = strdup(yytext);
			return '<';
		}
">"		{
			yylval.ch = strdup(yytext);
			return '>';
		}
{id}		{
			yylval.ch = strdup(yytext);
			return ID;
            } 
{number}	{  
			yylval.number = atoi(yytext);
			return NUMBER; 
			}

[ \t]		{ 
		}
.		{ 
		  return ETOK;
		}

%%
void yyerror (char const *s)
{
    fprintf (stderr, "%s\n", s);
}


