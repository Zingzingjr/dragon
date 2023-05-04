%{
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "tree.h"
#include "y.tab.h"

%}

%option yylineno
identifier [a-zA-Z][a-zA-Z0-9]*
number [0-9]+
whitespace [ \t]+

%%
"{"[^"}"]*"}"		{;}
"(*"[^"*}"]*"*)"    {;}
"def"			{fprintf(stderr, "[DEF]"); return DEF;}
"proc"			{fprintf(stderr, "[PROC]"); return PROC;}
"func"			{fprintf(stderr, "[FUNC]"); return FUNC;}
"var"			{fprintf(stderr, "[VAR]"); return VAR;}
"array"			{fprintf(stderr, "[ARRAY]"); return ARRAY;}
"of"			{fprintf(stderr, "[OF]"); return OF;}
"integral"		{fprintf(stderr, "[INTEGRAL]"); return INTEGRAL;}
"rational"		{fprintf(stderr, "[RATIONAL]"); return RATIONAL;}
"begin"			{fprintf(stderr, "[BEGIN]"); return BBEGIN;}
"end"			{fprintf(stderr, "[END]"); return END;}
"if"			{fprintf(stderr, "[IF]"); return IF;}
"then"			{fprintf(stderr, "[THEN]"); return THEN;}
"else"			{fprintf(stderr, "[ELSE]"); return ELSE;}
"while"			{fprintf(stderr, "[WHILE]"); return WHILE;}
"repeat"		{fprintf(stderr, "[REPEAT]"); return REPEAT;}
"until"			{fprintf(stderr, "[UNTIL]"); return UNTIL;}
"for"			{fprintf(stderr, "[FOR]"); return FOR;}
"do"			{fprintf(stderr, "[DO]"); return DO;}
"<" 			{fprintf(stderr, "[RELOP:%d]", yylval.opval = LT); return RELOP;}
"<=" 			{fprintf(stderr, "[RELOP:%d]", yylval.opval = LE); return RELOP;}
">" 			{fprintf(stderr, "[RELOP:%d]", yylval.opval = GT); return RELOP;}
">=" 			{fprintf(stderr, "[RELOP:%d]", yylval.opval = GE); return RELOP;}
"<>" 			{fprintf(stderr, "[RELOP:%d]", yylval.opval = NE); return RELOP;}
"=" 			{fprintf(stderr, "[RELOP:%d]", yylval.opval = EQ); return RELOP;}
"+" 			{fprintf(stderr, "[ADDOP:%d]", yylval.opval = PLUS); return ADDOP;}
"-" 			{fprintf(stderr, "[ADDOP:%d]", yylval.opval = MINUS); return ADDOP;}
"or" 			{fprintf(stderr, "[ADDOP:%d]", yylval.opval = OR); return ADDOP;}
"*" 			{fprintf(stderr, "[MULOP:%d]", yylval.opval = STAR); return MULOP;}
"/" 			{fprintf(stderr, "[MULOP:%d]", yylval.opval = SLASH); return MULOP;}
"and" 			{fprintf(stderr, "[MULOP:%d]", yylval.opval = AND); return MULOP;}
"div" 			{fprintf(stderr, "[MULOP:%d]", yylval.opval = DIV); return MULOP;}
"mod" 			{fprintf(stderr, "[MULOP:%d]", yylval.opval = MOD); return MULOP;}
":=" 			{fprintf(stderr, "[ASSIGNOP]"); return ASSIGNOP;}
"(" 			{fprintf(stderr, "{%c}", yytext[0]); return yytext[0];}
")" 			{fprintf(stderr, "{%c}", yytext[0]); return yytext[0];}
"[" 			{fprintf(stderr, "{%c}", yytext[0]); return yytext[0];}
"]" 			{fprintf(stderr, "{%c}", yytext[0]); return yytext[0];}
":" 			{fprintf(stderr, "{%c}", yytext[0]); return yytext[0];}
";" 			{fprintf(stderr, "{%c}", yytext[0]); return yytext[0];}
"," 			{fprintf(stderr, "{%c}", yytext[0]); return yytext[0];}
"." 			{fprintf(stderr, "{%c}", yytext[0]); return yytext[0];}
{identifier} 	{fprintf(stderr, "[ID:%s]", yylval.sval = (char *)strdup(yytext)); return ID;}
{number}		{fprintf(stderr, "[NUM:%d]", yylval.ival = atoi(yytext)); return INUM;}
{number}"."{number} {fprintf(stderr, "[RNUM:%f]", yylval.rval = atof(yytext)); return RNUM;}
{whitespace}	{;}
\n				{fprintf(stderr, "\n");}
.				{fprintf(stderr, "<%c>", yytext[0]); return yytext[0];}

%%

int yyerror(char *message) {	
	fprintf(stderr, "ERROR [line:%d]: %s\n", yylineno, message);
	exit(1);
}