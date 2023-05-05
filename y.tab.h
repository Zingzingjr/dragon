/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    DEF = 258,
    VAR = 259,
    ARRAY = 260,
    OF = 261,
    INTEGRAL = 262,
    RATIONAL = 263,
    BBEGIN = 264,
    END = 265,
    ASSIGNOP = 266,
    FUNC = 267,
    PROC = 268,
    IF = 269,
    THEN = 270,
    ELSE = 271,
    WHILE = 272,
    DO = 273,
    RELOP = 274,
    LT = 275,
    LE = 276,
    GT = 277,
    GE = 278,
    EQ = 279,
    NE = 280,
    ADDOP = 281,
    PLUS = 282,
    MINUS = 283,
    OR = 284,
    MULOP = 285,
    STAR = 286,
    SLASH = 287,
    DIV = 288,
    MOD = 289,
    AND = 290,
    NOT = 291,
    FUNCTION_CALL = 292,
    ARRAY_ACCESS = 293,
    LIST = 294,
    RANGE = 295,
    FOR = 296,
    REPEAT = 297,
    UNTIL = 298,
    ID = 299,
    INUM = 300,
    RNUM = 301
  };
#endif
/* Tokens.  */
#define DEF 258
#define VAR 259
#define ARRAY 260
#define OF 261
#define INTEGRAL 262
#define RATIONAL 263
#define BBEGIN 264
#define END 265
#define ASSIGNOP 266
#define FUNC 267
#define PROC 268
#define IF 269
#define THEN 270
#define ELSE 271
#define WHILE 272
#define DO 273
#define RELOP 274
#define LT 275
#define LE 276
#define GT 277
#define GE 278
#define EQ 279
#define NE 280
#define ADDOP 281
#define PLUS 282
#define MINUS 283
#define OR 284
#define MULOP 285
#define STAR 286
#define SLASH 287
#define DIV 288
#define MOD 289
#define AND 290
#define NOT 291
#define FUNCTION_CALL 292
#define ARRAY_ACCESS 293
#define LIST 294
#define RANGE 295
#define FOR 296
#define REPEAT 297
#define UNTIL 298
#define ID 299
#define INUM 300
#define RNUM 301

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 20 "qc.y"

	/* token attributes */
	int ival;	/* NUM */
	float rval; /* RNUM */
	char *sval; /* ID */
	int opval; /* RELOP ADDOP MULOP */

	tree_t *tval; /* tree attribute for grammar variables */

#line 159 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
