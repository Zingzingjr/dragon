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
tree_t *tree_ptr;

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
%token RANGE
%token FOR
%token REPEAT
%token UNTIL


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
%type <tval> range

%%
program: DEF ID '(' identifier_list ')' ';'
	{
//		fprintf(stderr, "program\n");
		top_scope = scope_push(top_scope); /* create a new scope */
		//fprintf(stderr, "NEW SCOPE (program)\n");
		scope_insert(top_scope, $2); /* insert program ID into scope */
		//print_scope(top_scope);
	}
	declarations
	subprogram_declarations
	compound_statement
	'.'
	;

identifier_list: ID
		{
			fprintf(stderr, "identifier_list: ID\n");
			id_ptr = scope_insert(top_scope, $1);
			//print_scope(top_scope);
			$$ = make_id(id_ptr);
		}
	| identifier_list ',' ID
		{ 
			fprintf(stderr, "identifier_list: identifier_list ',' ID\n");
			id_ptr = scope_insert(top_scope, $3);
			//print_scope(top_scope);
			$$ = make_tree(LIST, $1, make_id(id_ptr));
		}
	;

declarations: declarations VAR identifier_list ':' type ';'
		{
//			fprintf(stderr, "declarations: declarations VAR identifier_list ':' type ';'\n");
			// for (tree_ptr = $3; tree_ptr != NULL; tree_ptr = tree_ptr->left) {
			// 	if (scope_search(top_scope, tree_ptr->attribute.sval->name) != NULL) {
			// 		fprintf(stderr, "ERROR: ID %s already declared in this scope.\n", id_ptr->name);
			// 		exit(1);
			// 	}
			// //	id_ptr->type = $5;
			// }
			// if (scope_search(top_scope, $3->attribute.sval->name) != NULL) {
			// 	fprintf(stderr, "ERROR: ID %s already declared in this scope.\n", $3->attribute.sval->name);
			// 	exit(1);
			// }
			fprintf(stderr, "declarations has begun\n");
			semantic_set_type($3, $5);
			fprintf(stderr, "declarations has finished\n");
		}
	| /* empty */
	;

type: standard_type 
		{
//			fprintf(stderr, "type: standard_type\n");
			$$ = $1;
		}
	| ARRAY '[' range ']' OF standard_type
		{ 
//			fprintf(stderr, "type: ARRAY '[' range ']' OF standard_type\n");
			$$ = -1;
		}
	;

range: INUM '.' '.' INUM
	{ 
//		fprintf(stderr, "range: INUM '.' '.' INUM\n");
		if ($1 > $4) {
			fprintf(stderr, "ERROR: range lower bound greater than upper bound.\n");
			exit(1);
		}
		make_tree(RANGE, make_inum($1), make_inum($4));
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
	{ 
	//	fprintf(stderr, "subprogram_declaration\n");
		top_scope = scope_pop(top_scope);
	} /* remove inner scope */
	;

subprogram_header: FUNC ID arguments ':' standard_type ';'
	{
//		fprintf(stderr, "subprogram_header: FUNC ID arguments ':' standard_type ';'\n");
		if (scope_search(top_scope, $2) != NULL) {
			fprintf(stderr, "ERROR: FUNC ID %s already declared in this scope.\n", $2);
			exit(1);
		}
		id_ptr = scope_insert(top_scope, $2); /* record function ID in current scope */
		//scope_print(top_scope);
		id_ptr->type = $5;
		top_scope = scope_push(top_scope); /* Create a new scope */
		//fprintf(stderr, "NEW SCOPE\n");
		scope_insert(top_scope, $2);
		//scope_print(top_scope);
		//make_tree(FUNC, make_id(semantic_lookup(top_scope, $2)), $3); /* create a tree for the function header */
	}
	| PROC ID arguments ';' {
		fprintf(stderr, "subprogram_header: PROC ID arguments ';'\n");
		if (scope_search(top_scope, $2) != NULL) {
			fprintf(stderr, "ERROR: PROC ID %s already declared in this scope.\n", $2);
			exit(1);
		}
		id_ptr = scope_insert(top_scope, $2); /* record procedure ID in current scope */
		top_scope = scope_push(top_scope);  /* create a new scope */
		//fprintf(stderr, "NEW SCOPE\n");
		scope_insert(top_scope, $2);
		//make_tree(PROC, make_id(semantic_lookup(top_scope, $2)), $3); /* create a tree for the procedure header */
	}	
	
	arguments ';'
	;

arguments: '(' parameter_list ')'
		{ fprintf(stderr, "arguments: '(' parameter_list ')'\n");}
	| /* empty */
	;

parameter_list: identifier_list ':' type
		{fprintf(stderr, "parameter_list: identifier_list ':' type\n"); semantic_set_type($1, $3); $$ = $1;}
	| parameter_list ';' identifier_list ':' type
		{fprintf(stderr, "parameter_list: parameter_list ';' identifier_list ':' type\n"); semantic_set_type($3, $5); $$ = $3;}
	;

/* ensure all below have trees */

compound_statement:
	BBEGIN
		optional_statements
	END
	{
		fprintf(stderr, "compound_statement: BEGIN optional_statements END\n"); 
		$$ = $2;
	}
	;

optional_statements: statement_list
	{
		fprintf(stderr, "optional_statements: statement_list\n"); 
		$$ = $1;
	}
	| /* empty */
	{ $$ = NULL; }
	;

statement_list: statement
	{
		fprintf(stderr, "statement_list: statement\n");
		$$ = $1;
	}
	| statement_list ';' statement
	{
		fprintf(stderr, "statement_list: statement_list ';' statement\n");
		make_tree(LIST, $1, $3);
	}
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
			fprintf(stderr, "matched_statement: IF expression THEN matched_statement ELSE matched_statement\n");
			$$ = make_tree(THEN, $4, $6);
			$$ = make_tree(IF, $2, $$);
		 } 
		| variable ASSIGNOP expression
		{ 
			fprintf(stderr, "matched_statement: variable ASSIGNOP expression\n");
			if (type_of($1) != type_of($3)) {
				fprintf(stderr, "type of $1: %d type of $3: %d\n", type_of($1), type_of($3));
				fprintf(stderr, "ERROR: type mismatch in assignment statement.\n");
				exit(1);
			}
			$$ = make_tree(ASSIGNOP, $1, $3);		
		}
	| procedure_statement
	| compound_statement
	| WHILE expression DO statement
	{ $$ = make_tree(WHILE, $2, $4); }
	| REPEAT statement UNTIL expression
	{ $$ = make_tree(REPEAT, $2, $4); }
	| FOR ID ASSIGNOP range DO statement
	{ 
		fprintf(stderr, "matched_statement: FOR ID ASSIGNOP range DO statement\n");
		$$ = make_tree(ASSIGNOP, make_id(semantic_lookup(top_scope, $2)), $4); /* create tree for assignment statement */
		$$ = make_tree(FOR, $$, $6);
	}
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
		{ 
			if (type_of($3) != INTEGRAL) {
				fprintf(stderr, "ERROR: array index must be an integer.\n");
				exit(1);
			}
			$$ = make_tree(ARRAY_ACCESS, make_id(semantic_lookup(top_scope, $1)), $3);
		}
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
		{
			if (type_of($3) != INTEGRAL) {
				fprintf(stderr, "ERROR: array index must be an integer.\n");
				exit(1);
			}
			$$ = make_tree(ARRAY_ACCESS, make_id(global_scope_search(top_scope, $1)), $3);
		}
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
	//fprintf(stderr, "NEW SCOPE\n");
	yyparse();
}