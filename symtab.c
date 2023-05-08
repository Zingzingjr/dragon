#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "symtab.h"

#define HASH_SIZE 211
#define EOS '\0'

int hashpjw(char *);

scope_t *make_scope() {
	scope_t *p = (scope_t *)malloc(sizeof(scope_t));
	assert(p != NULL);
	int i;
	for (i = 0; i < HASH_SIZE; i++) {
		p->table[i] = NULL;
	}
	p->next = NULL;
	return p;
}

void free_scope(scope_t *p) {

	// for (int i = 0; i < HASH_SIZE; i++) {
	// 	free_list(p->table[i]);
	// }
	//free(p);
}

scope_t *scope_push( scope_t *top) {
	scope_t *p = make_scope();
	if (top != NULL) {
		p->next = top;
	}
	return p;
}

scope_t *scope_pop(scope_t *top) {

	if (top != NULL) {
		scope_t *tmp;
		tmp = top->next;
		free_scope(top);
		return tmp;
	}
	else return NULL;
}

/* search at top scope */
list_t *scope_insert(scope_t *top, char *name) {

	if (top == NULL) {
		fprintf(stderr, "scope_insert: top is NULL\n");
		return NULL;
	}

	int index = hashpjw(name);
	list_t *start = top->table[index];
	top->table[index] = list_insert(start, name);
//	fprintf(stderr, "scope_insert: inserted %s at index %d\n", name, index);
	return top->table[index];
}

list_t *scope_search(scope_t *top, char *name) {
	
	if (top == NULL)
		return NULL;

	int index = hashpjw(name);
	list_t *start = top->table[index];
//	fprintf(stderr, "printing list: ");
//	list_print(start);
	return list_search(start, name);
}

list_t *global_scope_search(scope_t *top, char *name) {

	scope_t *curr = top;
	list_t *p;
	
	while (curr != NULL) { /* searching all scopes */
		p = scope_search(curr, name);
		if ( p != NULL) { /* found name, return */
			return p;
		}
		curr = curr->next; /* try next scope */
	}
	return NULL;	/* name not found */
}


int hashpjw(char *s) {

	char *p;
	unsigned h = 0, g;
	for (p = s; *p != EOS; p++) {
		h = (h << 4) + (*p); /* evil bitshift hack */
		if ((g = h & 0xf000000)) { /* what the fuck? */
			h ^= (g >> 24); /* ??? */
			h ^= g;
		}
	}
	return h % HASH_SIZE;
}	

// void print_scope(scope_t *scope) {
// 	for (int i = 0; i < HASH_SIZE; i++) {
// 		if (scope->table[i] != NULL) {
// 			fprintf(stderr, "%i: ", i);
// 			list_print(scope->table[i]);
			
// 		}
// 	}
// }