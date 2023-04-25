#ifndef lint
static const char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20130304

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)

#define YYPREFIX "yy"

#define YYPURE 0

#line 2 "qc.y"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"
#include "tree.h"
#include "symtab.h"
#include "semantic.h"

list_t *id_ptr;
scope_t  *top_scope;

#line 16 "qc.y"
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union {
	/* token attributes */
	int ival;	/* NUM */
	float rval; /* RNUM */
	char *sval; /* ID */
	int opval; /* RELOP ADDOP MULOP */

	tree_t *tval; /* tree attribute for grammar variables */
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 49 "y.tab.c"

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

#define DEF 257
#define VAR 258
#define ARRAY 259
#define OF 260
#define INTEGRAL 261
#define RATIONAL 262
#define BBEGIN 263
#define END 264
#define ASSIGNOP 265
#define FUNC 266
#define PROC 267
#define IF 268
#define THEN 269
#define ELSE 270
#define WHILE 271
#define DO 272
#define RELOP 273
#define LT 274
#define LE 275
#define GT 276
#define GE 277
#define EQ 278
#define NE 279
#define ADDOP 280
#define PLUS 281
#define MINUS 282
#define OR 283
#define MULOP 284
#define STAR 285
#define SLASH 286
#define DIV 287
#define MOD 288
#define AND 289
#define NOT 290
#define FUNCTION_CALL 291
#define ARRAY_ACCESS 292
#define LIST 293
#define ID 294
#define INUM 295
#define RNUM 296
#define YYERRCODE 256
static const short yylhs[] = {                           -1,
    0,    4,    4,   11,   11,    1,    1,   14,    2,    2,
   12,   12,   15,   18,   16,   19,   16,   17,   17,   20,
   20,   13,   21,   21,   22,   22,   23,   23,   24,   24,
   24,   24,   24,   25,   25,    5,    5,    3,    3,    6,
    6,    7,    7,    8,    8,    8,    9,    9,   10,   10,
   10,   10,   10,   10,   10,
};
static const short yylen[] = {                            2,
   10,    1,    3,    6,    0,    1,    6,    4,    1,    1,
    3,    0,    4,    0,    7,    0,    5,    3,    0,    3,
    5,    3,    1,    0,    1,    3,    1,    1,    6,    3,
    1,    1,    4,    4,    6,    1,    4,    1,    4,    1,
    3,    1,    3,    1,    2,    3,    1,    3,    1,    4,
    4,    1,    1,    3,    2,
};
static const short yydefred[] = {                         0,
    0,    0,    0,    0,    2,    0,    0,    0,    5,    3,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    5,
    0,    0,    0,    0,   31,    0,   32,    0,    0,   25,
   27,   28,   14,   16,    1,   11,    0,    0,    9,   10,
    0,    6,    0,    0,    0,   52,   53,    0,    0,    0,
    0,   47,    0,    0,    0,    0,   22,    0,    0,    0,
    0,    0,    4,    0,   55,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   40,    0,   30,   26,    0,    0,
    0,   13,    0,    0,    0,    0,   54,   34,    0,    0,
    0,   48,   33,   39,    0,   37,    0,    0,    0,   17,
    0,    0,   50,   51,    0,   41,    0,   18,    0,    0,
    0,    0,   29,   35,   20,    0,   15,    8,    7,    0,
   21,
};
static const short yydgoto[] = {                          2,
   41,   42,   25,    6,   26,   74,   75,   50,   51,   52,
   11,   13,   27,   84,   19,   20,   80,   59,   60,   98,
   28,   29,   30,   31,   32,
};
static const short yysindex[] = {                      -227,
 -231,    0,   25, -222,    0,   -9,   23, -209,    0,    0,
 -171, -222, -197,  -30, -250, -206, -204,   45,   33,    0,
 -185,  -40,  -40,  -33,    0, -170,    0, -168,   35,    0,
    0,    0,    0,    0,    0,    0, -171,    6,    0,    0,
   39,    0,  -37,  -37,  -29,    0,    0,  -40, -169, -223,
 -182,    0, -173,  -40,  -40,  -40,    0, -250,   64,   64,
 -197, -190,    0, -182,    0,  -40,  -40,   65, -250,  -40,
  -37,  -37, -250,    7,    0,   14,    0,    0, -222,   50,
   51,    0,   63,   18,   15,   19,    0,    0, -156, -165,
 -182,    0,    0,    0,  -40,    0,  -25,  -12, -238,    0,
   70, -143,    0,    0, -250,    0, -185,    0, -222,   59,
 -176, -238,    0,    0,    0,  -22,    0,    0,    0, -185,
    0,
};
static const short yyrindex[] = {                         0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
 -183,    0,    0,    0, -142,    0,    0,    0,    0,    0,
    0,    0,    0,  -58,    0,    0,    0,    0, -141,    0,
    0,    0,    0,    0,    0,    0, -183,    0,    0,    0,
    0,    0,    0,    0,  -39,    0,    0,    0,    0,   27,
   -4,    0,    0,    0,    0,    0,    0,    0,   66,   62,
    0,    0,    0,    8,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  -55,   34,
   20,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,
};
static const short yygindex[] = {                         0,
  -82,  -73,    0,   -6,    0,   60,  -14,   55,  -28,  -27,
  108,   92,   -1,    0,    0,    0,   71,    0,    0,    0,
    0,    0,  -42,  -59,   28,
};
#define YYTABLESIZE 306
static const short yytable[] = {                         48,
   38,   49,   48,   27,   49,   14,   54,   49,   53,   89,
   66,   18,   15,    8,   64,   78,   65,   22,    8,   49,
   23,    8,   39,   40,  115,  110,   88,   21,  108,    1,
   93,    7,  107,   68,    8,  120,   44,  121,  119,   44,
   76,   77,   91,   24,   92,  113,  109,   94,   45,   70,
   95,   45,   86,   49,   44,  103,   71,   55,   95,   82,
   46,   67,    3,   46,    4,   15,   45,   42,   16,   17,
   42,    5,   97,   38,   43,   39,   40,   43,   46,   12,
  106,    9,   12,   12,   10,   42,   12,   33,   44,   34,
   35,   36,   43,   58,   56,   57,   62,   63,   73,   69,
   45,   72,  116,   79,   83,   87,   96,   99,  101,  100,
  102,  104,   46,  105,   71,  111,  112,  117,  118,   42,
   19,   24,   23,   19,   90,   85,   43,   37,   61,    0,
   81,    0,  114,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   38,   36,    0,   27,    0,
    0,   38,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   49,    0,    0,    0,    0,   49,
   49,    0,   49,   49,    0,    0,    0,    0,    0,   43,
   49,    0,    0,    0,   49,    0,    0,    0,    0,   44,
    0,    0,   44,   45,   46,   47,   45,   46,   47,   44,
    0,    0,    0,    0,   44,   44,    0,   44,   44,    0,
    0,   45,    0,    0,    0,   44,   45,   45,    0,   45,
   45,    0,    0,   46,    0,    0,    0,   45,   46,   46,
   42,   46,   46,    0,    0,   42,   42,   43,   42,   46,
    0,    0,   43,   43,    0,   43,
};
static const short yycheck[] = {                         40,
   59,   41,   40,   59,   44,   12,   40,   22,   23,   69,
   40,   13,  263,   44,   43,   58,   44,  268,   44,   59,
  271,   44,  261,  262,  107,   99,   69,   58,   41,  257,
   73,   41,   58,   48,   44,   58,   41,  120,  112,   44,
   55,   56,   71,  294,   72,  105,   59,   41,   41,  273,
   44,   44,   67,   93,   59,   41,  280,   91,   44,   61,
   41,   91,  294,   44,   40,  263,   59,   41,  266,  267,
   44,  294,   79,  259,   41,  261,  262,   44,   59,  263,
   95,   59,  266,  267,  294,   59,  258,  294,   93,  294,
   46,   59,   59,   59,  265,  264,   91,   59,  272,  269,
   93,  284,  109,   40,  295,   41,   93,   58,   46,   59,
   93,   93,   93,  270,  280,   46,  260,   59,  295,   93,
   59,  264,  264,   58,   70,   66,   93,   20,   37,   -1,
   60,   -1,  105,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  264,  265,   -1,  264,   -1,
   -1,  270,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  264,   -1,   -1,   -1,   -1,  269,
  270,   -1,  272,  273,   -1,   -1,   -1,   -1,   -1,  280,
  280,   -1,   -1,   -1,  284,   -1,   -1,   -1,   -1,  290,
   -1,   -1,  290,  294,  295,  296,  294,  295,  296,  264,
   -1,   -1,   -1,   -1,  269,  270,   -1,  272,  273,   -1,
   -1,  264,   -1,   -1,   -1,  280,  269,  270,   -1,  272,
  273,   -1,   -1,  264,   -1,   -1,   -1,  280,  269,  270,
  264,  272,  273,   -1,   -1,  269,  270,  264,  272,  280,
   -1,   -1,  269,  270,   -1,  272,
};
#define YYFINAL 2
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 296
#if YYDEBUG
static const char *yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,"'('","')'",0,0,"','",0,"'.'",0,0,0,0,0,0,0,0,0,0,0,"':'","';'",0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"'['",0,"']'",0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"DEF","VAR","ARRAY","OF","INTEGRAL","RATIONAL","BBEGIN","END","ASSIGNOP","FUNC",
"PROC","IF","THEN","ELSE","WHILE","DO","RELOP","LT","LE","GT","GE","EQ","NE",
"ADDOP","PLUS","MINUS","OR","MULOP","STAR","SLASH","DIV","MOD","AND","NOT",
"FUNCTION_CALL","ARRAY_ACCESS","LIST","ID","INUM","RNUM",
};
static const char *yyrule[] = {
"$accept : program",
"program : DEF ID '(' identifier_list ')' ';' declarations subprogram_declarations compound_statement '.'",
"identifier_list : ID",
"identifier_list : identifier_list ',' ID",
"declarations : declarations VAR identifier_list ':' type ';'",
"declarations :",
"type : standard_type",
"type : ARRAY '[' range ']' OF standard_type",
"range : INUM '.' '.' INUM",
"standard_type : INTEGRAL",
"standard_type : RATIONAL",
"subprogram_declarations : subprogram_declarations subprogram_declaration ';'",
"subprogram_declarations :",
"subprogram_declaration : subprogram_header declarations subprogram_declarations compound_statement",
"$$1 :",
"subprogram_header : FUNC ID $$1 arguments ':' standard_type ';'",
"$$2 :",
"subprogram_header : PROC ID $$2 arguments ';'",
"arguments : '(' parameter_list ')'",
"arguments :",
"parameter_list : identifier_list ':' type",
"parameter_list : parameter_list ';' identifier_list ':' type",
"compound_statement : BBEGIN optional_statements END",
"optional_statements : statement_list",
"optional_statements :",
"statement_list : statement",
"statement_list : statement_list ';' statement",
"statement : matched_statement",
"statement : unmatched_statement",
"matched_statement : IF expression THEN matched_statement ELSE matched_statement",
"matched_statement : variable ASSIGNOP expression",
"matched_statement : procedure_statement",
"matched_statement : compound_statement",
"matched_statement : WHILE expression DO statement",
"unmatched_statement : IF expression THEN statement",
"unmatched_statement : IF expression THEN matched_statement ELSE unmatched_statement",
"variable : ID",
"variable : ID '[' expression ']'",
"procedure_statement : ID",
"procedure_statement : ID '(' expression_list ')'",
"expression_list : expression",
"expression_list : expression_list ',' expression",
"expression : simple_expression",
"expression : simple_expression RELOP simple_expression",
"simple_expression : term",
"simple_expression : ADDOP term",
"simple_expression : simple_expression ADDOP term",
"term : factor",
"term : term MULOP factor",
"factor : ID",
"factor : ID '(' expression_list ')'",
"factor : ID '[' expression ']'",
"factor : INUM",
"factor : RNUM",
"factor : '(' expression ')'",
"factor : NOT factor",

};
#endif

int      yydebug;
int      yynerrs;

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  500
#endif
#endif

#define YYINITSTACKSIZE 500

typedef struct {
    unsigned stacksize;
    short    *s_base;
    short    *s_mark;
    short    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;
#line 243 "qc.y"

main() {
	top_scope = scope_push(top_scope);
	yyparse();
}
#line 381 "y.tab.c"

#if YYDEBUG
#include <stdio.h>		/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (short *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return -1;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return -1;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack)) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = YYLEX) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
        {
            goto yyoverflow;
        }
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    yyerror("syntax error");

    goto yyerrlab;

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yystack.s_mark]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
                {
                    goto yyoverflow;
                }
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 2:
#line 75 "qc.y"
	{ 
			id_ptr = scope_insert(top_scope, yystack.l_mark[0].sval); 
			yyval.tval = make_id(id_ptr);
		}
break;
case 3:
#line 80 "qc.y"
	{ 
			scope_insert(top_scope, yystack.l_mark[0].sval); 
			yyval.tval = make_tree(LIST, yystack.l_mark[-2].tval, make_id(id_ptr));
		}
break;
case 4:
#line 87 "qc.y"
	{ semantic_set_type(yystack.l_mark[-3].tval, yystack.l_mark[-1].ival); }
break;
case 6:
#line 91 "qc.y"
	{yyval.ival = yystack.l_mark[0].ival;}
break;
case 7:
#line 93 "qc.y"
	{ yyval.ival = -1; }
break;
case 9:
#line 99 "qc.y"
	{yyval.ival = INTEGRAL;}
break;
case 10:
#line 100 "qc.y"
	{yyval.ival = RATIONAL;}
break;
case 13:
#line 112 "qc.y"
	{ top_scope = scope_pop(top_scope); }
break;
case 14:
#line 115 "qc.y"
	{ 
		id_ptr = scope_insert(top_scope, yystack.l_mark[0].sval); /* record function ID in current scope */
		top_scope = scope_push(top_scope); /* Create a new scope */
	}
break;
case 16:
#line 120 "qc.y"
	{
		id_ptr = scope_insert(top_scope, yystack.l_mark[0].sval); /* record procedure ID in current scope */
		top_scope = scope_push(top_scope);  /* create a new scope */
	}
break;
case 30:
#line 158 "qc.y"
	{ 
			if (type_of(yystack.l_mark[-2].tval) != type_of(yystack.l_mark[0].tval)) {
				fprintf(stderr, "ERROR: type mismatch in assignment statement.\n");
				exit(1);
			}
			
		}
break;
case 36:
#line 175 "qc.y"
	{
			yyval.tval = make_id(semantic_lookup(top_scope, yystack.l_mark[0].sval));
		}
break;
case 37:
#line 179 "qc.y"
	{ yyval.tval = make_tree(ARRAY_ACCESS, make_id(semantic_lookup(top_scope, yystack.l_mark[-3].sval)), yystack.l_mark[-1].tval); }
break;
case 38:
#line 183 "qc.y"
	{ yyval.tval = make_id(semantic_lookup(top_scope, yystack.l_mark[0].sval)); }
break;
case 39:
#line 185 "qc.y"
	{ yyval.tval = make_tree(PROC, make_id(semantic_lookup(top_scope, yystack.l_mark[-3].sval)), yystack.l_mark[-1].tval);}
break;
case 40:
#line 189 "qc.y"
	{yyval.tval = yystack.l_mark[0].tval;}
break;
case 41:
#line 191 "qc.y"
	{yyval.tval = make_tree(LIST, yystack.l_mark[-2].tval, yystack.l_mark[0].tval);}
break;
case 42:
#line 195 "qc.y"
	{yyval.tval = yystack.l_mark[0].tval;}
break;
case 43:
#line 197 "qc.y"
	{yyval.tval = make_tree(RELOP, yystack.l_mark[-2].tval, yystack.l_mark[0].tval); yyval.tval->attribute.opval = yystack.l_mark[-1].opval;}
break;
case 44:
#line 201 "qc.y"
	{yyval.tval = yystack.l_mark[0].tval;}
break;
case 45:
#line 203 "qc.y"
	{yyval.tval = make_tree(ADDOP, yystack.l_mark[0].tval, NULL); yyval.tval->attribute.opval = yystack.l_mark[-1].opval;}
break;
case 46:
#line 205 "qc.y"
	{yyval.tval = make_tree(ADDOP, yystack.l_mark[-2].tval, yystack.l_mark[0].tval); yyval.tval->attribute.opval = yystack.l_mark[-1].opval;}
break;
case 47:
#line 209 "qc.y"
	{yyval.tval = yystack.l_mark[0].tval;}
break;
case 48:
#line 211 "qc.y"
	{
			yyval.tval = make_tree(MULOP, yystack.l_mark[-2].tval, yystack.l_mark[0].tval);
			yyval.tval->attribute.opval = yystack.l_mark[-1].opval;
		}
break;
case 49:
#line 218 "qc.y"
	{
		yyval.tval = make_id(semantic_lookup(top_scope, yystack.l_mark[0].sval));
	}
break;
case 50:
#line 229 "qc.y"
	{yyval.tval = make_tree(FUNCTION_CALL, make_id(global_scope_search(top_scope, yystack.l_mark[-3].sval)), yystack.l_mark[-1].tval);}
break;
case 51:
#line 231 "qc.y"
	{yyval.tval = make_tree(ARRAY_ACCESS, make_id(global_scope_search(top_scope, yystack.l_mark[-3].sval)), yystack.l_mark[-1].tval);}
break;
case 52:
#line 233 "qc.y"
	{yyval.tval = make_inum(yystack.l_mark[0].ival);}
break;
case 53:
#line 235 "qc.y"
	{yyval.tval = make_rnum(yystack.l_mark[0].rval);}
break;
case 54:
#line 237 "qc.y"
	{yyval.tval = yystack.l_mark[-1].tval;}
break;
case 55:
#line 239 "qc.y"
	{yyval.tval = make_tree(NOT, yystack.l_mark[0].tval, NULL);}
break;
#line 736 "y.tab.c"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            if ((yychar = YYLEX) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
    {
        goto yyoverflow;
    }
    *++yystack.s_mark = (short) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    yyerror("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
