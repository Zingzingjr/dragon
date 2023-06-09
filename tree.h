#ifndef TREE_H
#define TREE_H

#include "list.h"

typedef struct tree_s {
	
	int type;	/* token types: ADDOP, MULOP, NUM */
	
	union {
		int ival; /* INUM */
		float rval;	/* RNUM */
		list_t *sval; /* ID */
		int opval; /* RELOP ADDOP MULOP */
	} attribute;

	struct tree_s *left;
	struct tree_s *right;
} tree_t;

tree_t *make_tree(int v, tree_t *l, tree_t *r);
tree_t *make_id(list_t *);
tree_t *make_inum(int);
tree_t *make_rnum(float);
void print_tree(tree_t *t);
int eval_tree(tree_t *t);
int rank( tree_t *t, int d );
void gencode_start( tree_t *t );

#endif