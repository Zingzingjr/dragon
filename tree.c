#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "const.h"
#include "tree.h"
#include "y.tab.h"

void aux_print_tree( tree_t *, int );

/* basic constructor */
tree_t *make_tree( int type, tree_t *l, tree_t *r )
{
	tree_t *p = (tree_t *)malloc(sizeof(tree_t));
	assert( p != NULL );
	p->type = type;
	p->left = l;
	p->right = r;
	return p;
}

tree_t *make_id(list_t *id) {

	tree_t *p = make_tree(ID, NULL, NULL);
	p->attribute.sval = id;
	return p;
}

tree_t *make_inum(int val) {

	tree_t *p = make_tree(INUM, NULL, NULL);
	p->attribute.ival = val;
	return p;
}

tree_t *make_rnum(float val) {

	tree_t *p = make_tree(RNUM, NULL, NULL);
	p->attribute.rval = val;
	return p;
}

int return_scan(tree_t *t, char *name) {

	if (t == NULL) return 0;

	if (t->type == ID) {
		if (!strcmp(t->attribute.sval->name, name)) {
			return 1;
		}
	}
	return return_scan(t->left, name) || return_scan(t->right, name);
}


/* pre-order tree traversal */
void print_tree(tree_t *t) {
	fprintf(stderr, "\n\n");
	aux_print_tree(t, 0);
}
/* TODO: UPDATE */
void aux_print_tree(tree_t *t, int spaces) {
	if (t == NULL) return;

	/* indenting for visual effects */
	for (int i = 0; i < spaces; i++)
		fprintf(stderr, " ");

	switch( t->type ) {
		case RELOP:
			fprintf(stderr, "[RELOP:%d]\n", t->attribute.opval);
			aux_print_tree(t->left, spaces + 4);
			aux_print_tree(t->right, spaces + 4);
			break;
		case ADDOP:
			fprintf(stderr, "[ADDOP:%d]\n", t->attribute.opval);
			aux_print_tree( t->left, spaces+4 );
			aux_print_tree( t->right, spaces+4 );
			break;
		case MULOP:
			fprintf(stderr, "[MULOP:%d]\n", t->attribute.opval);
			aux_print_tree(t->left, spaces + 4);
			aux_print_tree(t->right, spaces + 4);
			break;
		case ID:
			fprintf(stderr, "[ID:%s]\n", t->attribute.sval->name);
			break;
		case INUM:
			fprintf( stderr, "[INUM:%d]\n", t->attribute.ival);
			break;
		case RNUM:
			fprintf( stderr, "[INUM:%f]\n", t->attribute.rval);
			break;
		default:
			fprintf( stderr, "Error: print_tree, unknown type\n" );
			exit(1);
	}
}

int eval_tree(tree_t *t) {


	if (t == NULL) return 0;

	switch (t->type) {
		case '+':
			return eval_tree(t->left) + eval_tree(t->right);
			break;
		case '*':
			return eval_tree(t->left) * eval_tree(t->right);
			break;
		case INUM:
			return t->attribute.ival;
			break;
		case RNUM:
			return t->attribute.rval;
			break;
		default:
			fprintf(stderr, "Error: eval_tree, unknown type\n");
	}
}

/*rank of tree*/
int rank( tree_t *t, int d)
{
	int left, right;

	if( (t->left == NULL) && (t->right == NULL) )
		t->rank = d;	

	else{
	left = rank( t->left, 1);
	right = rank( t->right, 0);

	if(left != right)
		t->rank = max(left, right);
	else
		t->rank = 1 + left;
	}
	
	return t->rank;
}

void gencode_start( tree_t *t ){

 	fptr = fopen("assembly.s","w"); //test 1

   	if(fptr == NULL){
      		printf("Error with file");   
      		exit(1);             
   	}	

	t->rank = rank(t, 1);
	int* stack_registers = (int*) malloc(t->rank * sizeof(int));
	//int stack_registers[t->rank];
	int i;
	for( i = 0; i < t->rank; i++)
		stack_registers[i] = i;
	int start = 0;
	gencode( t, stack_registers, start, t->rank); 
}

//gencode
//Take out?
void gencode( tree_t *t, int *registers, int start, int r){
	gencode_statements(tree_t *t, int *registers, int start, int r);
}

//generation of code for statements
void gencode_statements(tree_t *t, int *registers, int start, int r){
	int popped = 0;
	if (t->type == ASSIGNOP){
		if ( t->right->type == RNUM )
			fprintf( stderr, "MOV %d R%d\n", t->right->attribute.rval, registers[start]);
		else if ( t->right->type == INUM )
			fprintf( stderr, "MOV %d R%d\n", t->right->attribute.ival, registers[start]);
		else if ( t->right->type == ADDOP || t->right->type == MULOP ){
			popped = registers[start];
			start++;
			gencode_expression(t->right, start, r);
			fprintf( stderr, "MOV R%d R%d\n", registers[start], popped);
		}
	}

/*
 * IF --jmp
 * THEN --jmp
 * ELSE --jmp
 * ASSIGNOP --mov
 * WHILE
 * DO
 * BBEGIN
 * END
 * DEF --
 * FUNC -- push    rbp
 *         mov     rbp, rsp
 *         ...
 *         pop     rbp
 *         ret
 */
}

//generation of code for expressions
void gencode_expressions( tree_t *t, int *registers, int start, int r){
	int popped = 0;
	int right_rank = 0;
	int left_rank = 0;

	/* case 0 */
	if( (t->left == NULL) && (t->right == NULL) && (t->rank == 1) ){
		fprintf(fptr, "MOV %d, R%d\n", t->attribute, registers[start]);
	}
	else if( (t->left != NULL) || (t->right != NULL)){
		right_rank = rank(t->right, 0);
		left_rank = rank(t->left, 1);
		
		/* case 1 */
		if ( right_rank == 0 ){
			gencode(t->left, registers, start, r);
			if(t->type == ADDOP)
				//can we do a switch case statement based on what type of ADDOP value?
				fprintf(fptr, "ADD %d, R%d\n", t->right->attribute, registers[start]);
			else if (t->type == MULOP)
				fprintf(fptr, "MUL %d, R%d\n", t->right->attribute, registers[start]);
			else if (t->type == RELOP){
				switch(t->attribute.opval){
				case LT:
					//print CMP then JX where X = specific symbol
					break;
				case LE:
					//print CMP then JX where X = specific symbol
					break;
				case GT:
					//print CMP then JX where X = specific symbol
					break;
				case GE:
					//print CMP then JX where X = specific symbol
					break;
				case EQ:
					//print CMP then JX where X = specific symbol
					break;
				case NE:
					//print CMP then JX where X = specific symbol
					break;
		       	default:
                			fprintf( stderr, "Error: codegen_expression, unknown type\n" );
                			exit(1);
				}
			}
			
			//continue?
		}
		/* case 2 */
		else if (( 1 <= left_rank )&&( left_rank < right_rank )
			&& ( left_rank < r )) { //r is the number of registers
			swap_top(registers);
			gencode(t->right, registers, start, r);
			popped = registers[start];
			start++;
			gencode(t->left, registers, start, r);
			//make these all into a function
			if(t->type == '+')
				fprintf(fptr, "ADD R%d, R%d\n", popped, registers[start]); //can also make pop registers[start-1]
			if else
				fprintf(fptr, "MUL R%d, R%d\n", popped, registers[start]);
			else if (t->type == RELOP){
				switch(t->attribute.opval){
				case LT:
					//print CMP then JX where X = specific symbol
					break;
				case LE:
					//print CMP then JX where X = specific symbol
					break;
				case GT:
					//print CMP then JX where X = specific symbol
					break;
				case GE:
					//print CMP then JX where X = specific symbol
					break;
				case EQ:
					//print CMP then JX where X = specific symbol
					break;
				case NE:
					//print CMP then JX where X = specific symbol
					break;
		       	default:
                			fprintf( stderr, "Error: codegen_expression, unknown type\n" );
                			exit(1);
				}
			}
			start--;
			swap_top(registers);
		}

		/* case 3 */
		else if (( 1 <= right_rank ) && ( right_rank <= left_rank )
			&& (right_rank < r)){
			gencode(t->left, registers, start, r);
			//pop
			popped = registers[start];
			start++;
			gencode(t->right, registers, start, r);
			if(t->type == '+')
				fprintf(fptr, "ADD R%d, R%d\n", registers[start], popped);
			else if
				fprintf(fptr, "MUL R%d, R%d\n", registers[start], popped);
			else if (t->type == RELOP){
				switch(t->attribute.opval){
				case LT:
					//print CMP then JX where X = specific symbol
					break;
				case LE:
					//print CMP then JX where X = specific symbol
					break;
				case GT:
					//print CMP then JX where X = specific symbol
					break;
				case GE:
					//print CMP then JX where X = specific symbol
					break;
				case EQ:
					//print CMP then JX where X = specific symbol
					break;
				case NE:
					//print CMP then JX where X = specific symbol
					break;
		       	default:
                			fprintf( stderr, "Error: codegen_expression, unknown type\n" );
                			exit(1);
				}
			}
		//push
			start--;
		}
		else
			fprintf(stderr, "falling through");
		/* not doing case 4 yet? */
	}
}

void swap_top(int *arr){
	int temp = arr[0];
	arr[0] = arr[1];
	arr[1] = temp;
}


/*
codegen(integer){
	fprintf(fptr, "MOV register1, %d", integer);
}

codegen(expr1 ASSIGNOP expr2){
	codegen(expr1) //in register $a0
	fprintf(fptr, "SWAP $ao, 0($sp)");
	fprintf(fptr, "addiu $sp, $sp, -4");
	codegen(expr2) //in register $a0
	fprintf(fptr, "MOV $t1, 0($sp)");
	fprintf(fptr, "ASSIGNOP $ao, $ao, $t1");
	fprintf(fptr, "addiu $sp, $sp, 4");
}

codegen(IF expr1 RELOP expr2 THEN expr3 ELSE expr4){
	codegen(expr1) //in register $a0
	fprintf(fptr, "SWAP $a0, 0($sp)");
	fprintf(fptr, "addiu $sp, $sp, -4");
	codegen(expr2) //in register $a0
	fprintf(fptr, "MOV $t1, 0($sp)");
	fprintf(fptr, "addiu $sp, $sp, 4");
	fprintf(fptr, "beq $ao, 0($sp)");
	if (true)
		codegen(expr3);
	else
		codegen(expr4);
}

codegen(func(args)){
	
} */
