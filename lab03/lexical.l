%{
	#include "stdio.h"
	#include "stdlib.h"
	#include "syntax.tab.h"
	#include "string.h"
	char **p;
	int line = 1 ;
	int yycolumn = 1;
	#define YY_USER_ACTION yylloc.first_line = yylloc.last_line = yylineno; \
	yylloc.first_column = yycolumn; yylloc.last_column = yycolumn + yyleng - 1; \
	yycolumn += yyleng;
	int tag =0;
%}

%option yylineno
digit[0-9]
letter[_a-zA-Z]


%%

";" {
	return SEMI;
	}
"," {
	return COMMA;
	}
">"|"<"|"<="|">="|"=="|"!=" {
	yylval.type_str = strdup(yytext);
	return RELOP;
	}
"=" {
	return ASSIGNOP;
	}
"+" {
	return PLUS;
	}
"-" {
	return MINUS;
	}
"*" {
	return STAR;
	}
"/" {
	return DIV;
	}
"&&" {
	return AND;
	}
"||" {
	return OR;
	}
"." {
	return DOT;
	}
"!" {
	return NOT;
	}
int {
	yylval.type_str = strdup(yytext);
	return TYPE;
	}
float {
	yylval.type_str = strdup(yytext);
	return TYPE;
	}
"(" {
	return LP;
	}
")" {
	return RP;
	}
"[" {
	return LB;
	}
"]" {
	return RB;
	}
"{" {
	return LC;
	}
"}" {
	return RC;
	}
struct {
	return STRUCT;
	}
return {
	return RETURN;
	}
if {
	return IF;
	}
else {
	return ELSE;
	}
while {
	return WHILE;
}

[0]|([1-9]{digit}*) {
	yylval.type_int = atoi(yytext);
	return INT;
	}
[0][1-7][0-7]* {
	yylval.type_int = strtol(yytext,p,8);
	return INT;
	}
[0][Xx]({digit}|[A-F])+ {
	yylval.type_int = strtol(yytext+2,p,16);
	return INT;
	}
[+-]?([0-9]*\.[0-9]+|[0-9]+\.) {
	yylval.type_float = atof(yytext);
	return FLOAT;
	}
{letter}({letter}|{digit})* {
	yylval.type_str = strdup(yytext);
	return ID;
}
" "+ {
		}
"	"+ {
		}
\n { 
	line++;
	yycolumn = 1;	
	}
. {
	printf("Error type A at line %d:Mysterious character \'%s\'\n:", line, yytext);
	tag =-1;
	}


%%


