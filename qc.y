%{

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"
#include "tree.h"
#include "symtab.h"
#include "semantic.h"

list_t *id_ptr;
scope_t  *top_scope;

int yylex();
int yyerror(const char*);

%}

%union {
	/* token attributes */
	int ival;	/* NUM */
	float rval; /* RNUM */
	char *sval; /* ID */
	int opval; /* RELOP ADDOP MULOP */

	tree_t *tval; /* tree attribute for grammar variables */
}

%token DEF
%token VAR
%token ARRAY OF
%token INTEGRAL RATIONAL
%token BBEGIN END
%token ASSIGNOP

%token FUNC PROC
%token IF THEN ELSE
%token WHILE DO
%token <opval> RELOP
%token LT LE GT GE EQ NE

%token <opval> ADDOP
%token PLUS MINUS OR

%token <opval> MULOP
%token STAR SLASH DIV MOD AND

%token NOT

%token FUNCTION_CALL ARRAY_ACCESS
%token LIST

%token <sval> ID
%token <ival> INUM
%token <rval> RNUM

%type <ival> type
%type <ival> standard_type

%type <tval> procedure_statement
%type <tval> identifier_list
%type <tval> variable
%type <tval> expression_list
%type <tval> expression
%type <tval> simple_expression
%type <tval> term
%type <tval> factor
%type <tval> parameter_list
%type <tval> compound_statement
%type <tval> statement_list
%type <tval> statement
%type <tval> matched_statement
%type <tval> unmatched_statement
%type <tval> optional_statements

%%
program: DEF ID '(' identifier_list ')' ';'
	declarations
	subprogram_declarations
	compound_statement
	'.'
	;

identifier_list: ID
		{ 
			id_ptr = scope_insert(top_scope, $1); 
			$$ = make_id(id_ptr);
		}
	| identifier_list ',' ID
		{ 
			scope_insert(top_scope, $3); 
			$$ = make_tree(LIST, $1, make_id(id_ptr));
		}
	;

declarations: declarations VAR identifier_list ':' type ';'
		{ semantic_set_type($3, $5); }
	| /* empty */
	;

type: standard_type {$$ = $1;}
	| ARRAY '[' range ']' OF standard_type
		{ $$ = -1; }
	;

range: INUM '.' '.' INUM
	{ if ($1 > $4) {
		fprintf(stderr, "ERROR: range lower bound greater than upper bound.\n");
		exit(1);
	}
	}
	;

standard_type: INTEGRAL {$$ = INTEGRAL;}
	| RATIONAL {$$ = RATIONAL;}
	;

subprogram_declarations: subprogram_declarations subprogram_declaration ';'
	| /* empty */ 
	;

subprogram_declaration:
	subprogram_header
	declarations
	subprogram_declarations
	compound_statement
	{ top_scope = scope_pop(top_scope); } /* remove inner scope */
	;

subprogram_header: FUNC ID arguments ':' standard_type ';'
	{
		
		id_ptr = scope_insert(top_scope, $2); /* record function ID in current scope */
		id_ptr->type = $5;
		top_scope = scope_push(top_scope); /* Create a new scope */
		scope_insert(top_scope, $2);
		make_tree(FUNC, make_id(semantic_lookup(top_scope, $2)), $3); /* create a tree for the function header */
	}
	| PROC ID {
		id_ptr = scope_insert(top_scope, $2); /* record procedure ID in current scope */
		top_scope = scope_push(top_scope);  /* create a new scope */
		scope_insert(top_scope, $2);
		make_tree(PROC, make_id(semantic_lookup(top_scope, $2)), NULL); /* create a tree for the procedure header */
	}
	
	arguments ';'
	;

arguments: '(' parameter_list ')'
	| /* empty */
	;

parameter_list: identifier_list ':' type
		{semantic_set_type($1, $3); $$ = $1;}
	| parameter_list ';' identifier_list ':' type
		{semantic_set_type($3, $5); $$ = $3;}
	;

/* ensure all below have trees */

compound_statement:
	BBEGIN
		optional_statements
	END
	{ $$ = $2;}
	;

optional_statements: statement_list
	{ $$ = $1; }
	| /* empty */
	{ $$ = NULL; }
	;

statement_list: statement
	{$$ = $1;}
	| statement_list ';' statement
		{make_tree(LIST, $1, $3);}
	;

/*ALL BELOW NEED SEMANTICS */

statement: matched_statement
	{ $$ = $1;}
	| unmatched_statement
	{$$ = $1;}
	;

matched_statement: 
		IF expression THEN matched_statement ELSE matched_statement
		 { 
			$$ = make_tree(THEN, $4, $6);
			$$ = make_tree(IF, $2, $$);
		 } 
		| variable ASSIGNOP expression
		{ 
			if (type_of($1) != type_of($3)) {
				fprintf(stderr, "ERROR: type mismatch in assignment statement.\n");
				exit(1);
			}
			$$ = make_tree(ASSIGNOP, $1, $3);
			
		}
	| procedure_statement
	| compound_statement
	| WHILE expression DO statement
	{ $$ = make_tree(WHILE, $2, $4); }
	;

unmatched_statement: IF expression THEN statement
		{ $$ = make_tree(IF, $2, $4); }
	| IF expression THEN matched_statement ELSE unmatched_statement
		{ 
			$$ = make_tree(THEN, $4, $6);
			$$ = make_tree(IF, $2, $$);
		}
	;

variable: ID
		{
			$$ = make_id(semantic_lookup(top_scope, $1));
		}
	| ID '[' expression ']'
		{ $$ = make_tree(ARRAY_ACCESS, make_id(semantic_lookup(top_scope, $1)), $3); }
	;

procedure_statement: ID
		{ $$ = make_id(semantic_lookup(top_scope, $1)); }
	| ID '(' expression_list ')'
		{ $$ = make_tree(PROC, make_id(semantic_lookup(top_scope, $1)), $3);}
	;

expression_list: expression
		{$$ = $1;}
	| expression_list ',' expression
		{$$ = make_tree(LIST, $1, $3);}
	;

expression: simple_expression	
		{$$ = $1;}
	| simple_expression RELOP simple_expression
		{$$ = make_tree(RELOP, $1, $3); $$->attribute.opval = $2;}
	;

simple_expression: term
		{$$ = $1;}
	| ADDOP term
		{
			$$ = make_tree(ADDOP, $2, NULL); 
			$$->attribute.opval = $1;
		}
	| simple_expression ADDOP term
		{
			if (type_of($1) != type_of($3)) {
				fprintf(stderr, "ERROR: type mismatch in simple expression.\n");
				exit(1);
			}
			$$ = make_tree(ADDOP, $1, $3); 
			$$->attribute.opval = $2;
		}
	;

term: factor
		{$$ = $1;}
	| term MULOP factor
		{
			if (type_of($1) != type_of($3)) {
				fprintf(stderr, "ERROR: type mismatch in term.\n");
				exit(1);
			}
			$$ = make_tree(MULOP, $1, $3);
			$$->attribute.opval = $2;
		}
	;

factor: ID
	{
		$$ = make_id(semantic_lookup(top_scope, $1));
	}
		/* {
			id_ptr = global_scope_search(top_scope, $1);
			if (id_ptr == NULL) {
				fprintf(stderr, "ERROR: name(%s) used but never defined.\n", $1);
			}
			$$ = make_id(global_scope_search(top_scope, $1));
		} */
	| ID '(' expression_list ')'
		{$$ = make_tree(FUNCTION_CALL, make_id(global_scope_search(top_scope, $1)), $3);}
	| ID '[' expression ']'
		{$$ = make_tree(ARRAY_ACCESS, make_id(global_scope_search(top_scope, $1)), $3);}
	| INUM
		{$$ = make_inum($1);}
	| RNUM
		{$$ = make_rnum($1);}
	| '(' expression ')'
		{$$ = $2;}
	| NOT factor
		{$$ = make_tree(NOT, $2, NULL);}
	;

%%

int main() {
	top_scope = scope_push(top_scope);
	yyparse();
}