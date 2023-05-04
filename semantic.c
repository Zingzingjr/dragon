#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"
#include "tree.h"
#include "symtab.h"
#include "semantic.h"
#include "y.tab.h" /*list of constants like ID */

/* check that a identifier exists*/
list_t *semantic_lookup(scope_t *scope, char *name) {

	scope_t *new_scope = scope;
	list_t *p = scope_search(new_scope, name);
	
	while ((new_scope = scope_pop(new_scope)) != NULL) {
		p = scope_search(new_scope, name);
		if (p != NULL) {
			return p;
		}
	}
	fprintf(stderr, "ERROR: name(%s) used but undeclared\n", name);
	exit(1);

	// list_t *p = global_scope_search(top_scope, name);
	// if (p == NULL) {
	// 	fprintf(stderr, "ERROR: name(%s) used but undeclared\n", name);
	// 	exit(1);
	// }
	// return p;
}
/* set all types in a list of identifiers  */
void semantic_set_type(tree_t *id_list, int type_val) {
	
	if (id_list == NULL) return;
	
	tree_t *left, *right;
	left = id_list->left;
	right = id_list ->right;

	if (left == NULL && right == NULL) {
		
		id_list->attribute.sval->type = type_val;
		fprintf(stderr, "[LEAF_SET_TYPE: %s, %d]\n", id_list->attribute.sval->name, id_list->attribute.sval->type);
	}

	/* set type of right child (ID) */

	else if (right != NULL) {
		right->attribute.sval->type = type_val;
		fprintf(stderr, "[R_SET_TYPE: %s, %d]\n", right->attribute.sval->name, right->attribute.sval->type);
		semantic_set_type(left, type_val);
	}
}
/* returns the "type" of a tree */
int type_of(tree_t *t) {

	if (t == NULL) return TYPE_ERROR;
	
	int left_type, right_type;

	switch (t->type) {
	case ID:
		return t->attribute.sval->type;	
	case INUM:
		return INTEGRAL;
	case RNUM:
		return RATIONAL;
	case PROC: 
		return PROC;
	case ADDOP:
		
		if (t->right == NULL) {
			return type_of(t->left);
		}
	
	case MULOP:
	case RELOP:
	case ASSIGNOP:

		if (t->right == NULL || t->left == NULL) {
			fprintf(stderr, "ERROR: invalid expression\n");
			exit(1);
		}

		left_type = type_of(t->left);
		right_type = type_of(t->right);

		if (left_type == PROC || right_type == PROC) {
			fprintf(stderr, "ERROR: procedure not allowed in expression\n");
			exit(1);
		}



		if (left_type != right_type) {
			fprintf(stderr, "ERROR: type mismatch in %s\n", int_to_type(t->type));
			exit(1);
		}
		return left_type;

	case FUNC:
		return t->type;
	
		


	default:
		return TYPE_ERROR;
	}

}

void semantic_set(scope_t *scope, char *name) {

	list_t *p = scope_search(scope, name);
	if (p != NULL) {
		fprintf(stderr, "ERROR: name(%s) already declared\n", name);
		exit(1);
	}

	scope_insert(scope, name);

}

char *int_to_type(int type) {

	switch (type) {
	case INTEGRAL:
		return "INTEGRAL";
	case RATIONAL:
		return "RATIONAL";
	case ADDOP:
		return "ADDOP";
	case MULOP:
		return "MULOP";
	case RELOP:
		return "RELOP";
	case TYPE_ERROR:
		return "TYPE_ERROR";
	default:
		return "UNKNOWN";
	}
}
/*
Enacts these rules

1. Semantic rules for Scoping
   1.1. Local objects cannot be declared more than once
   1.2. Local objects hide non-local objects with the same name
   1.3. Non-local objects should be visible from inner scopes (unless a local object of the same name exists)
   1.4. Function and procedure names exist in the scope they are defined (and not in their own scopes)
   1.5. Local objects cease to exist once their scopes cease to exist

2. Semantic rules for Expressions
   2.1. Expressions return typed-values
   2.2. Objects must be declared before they used in expressions
   2.3. Objects of different types cannot appear in the same expression (no type promotions)

3. Semantic rules for Statements
   3.1. Statements do not return values
   3.2. The test expression for IF-THEN, IF-THEN-ELSE, WHILE-DO must be Boolean-valued;
        note that the Boolean type must be implicitly defined
   3.3. The ELSE clause always binds to the closest IF (resolution of the dangling ELSE problem)
   3.4. The variable type in FOR-DO must match the types of lower bound and upper bound expressions

4. Semantic rules for Arrays
   4.1. Non-integer valued expressions cannot be used for indexing arrays

5. Semantic rules for Functions
   5.1. Function calls return values of type Integer or Real
   5.2. Function must contain a "return" statement within its own body;
        this is of the form: <function_name> := <expression>
   5.3. Functions must accept exactly the same number of arguments as is
        declared in its header, with the correct sequence of types
   5.4. Functions are not allowed to update the value of nonlocal objects (via assignment statements)

6. Semantic rules for Procedures
   6.1. Procedure calls do not return values
   6.2. Procedures must accept exactly the same number of arguments as is
        declared in its header, with the correct sequence of types 
	*/
int semantic_validate_expr(tree_t *t) {

	if (t == NULL) return 0;	

	int left_type, right_type;

	switch (t->type) {
	case ID:
		return 1;
	case INUM:
		return 1;
	case RNUM:
		return 1;
	case ADDOP:
		
		if (t->right == NULL) {
			return semantic_validate_expr(t->left);
		}
	case MULOP:
	case RELOP:

		if (t->right == NULL || t->left == NULL) {
			fprintf(stderr, "ERROR: invalid expression\n");
			exit(1);
		}

		left_type = type_of(t->left);
		right_type = type_of(t->right);

		if (left_type != right_type) {
			fprintf(stderr, "ERROR: type mismatch in %s\n", int_to_type(t->type));
			return 0;
		}
		return 1;

	case NOT:
		return semantic_validate_expr(t->left);

	default:
		return 0;

	}
}

int semantic_validate_stmt(tree_t *t) {

	if (t == NULL) return 0;

	switch (t->type) {

		case IF:
			if (t->left == NULL || t->right == NULL) {
				fprintf(stderr, "ERROR: invalid IF statement\n");
				return 0;
			}
			if (type_of(t->left) != INUM) {
				fprintf(stderr, "ERROR: condition of IF statement does not evaluate to boolean\n");
				return 0;
			}
			return 1;
		case WHILE:
			if (t->left == NULL || t->right == NULL) {
				fprintf(stderr, "ERROR: invalid WHILE statement\n");
			}
			if (type_of(t->left) != INUM) {
				fprintf(stderr, "ERROR: condition of WHILE statement does not evaluate to boolean\n");
				return 0;
			}
	}
}