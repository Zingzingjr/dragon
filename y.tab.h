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
extern YYSTYPE yylval;
