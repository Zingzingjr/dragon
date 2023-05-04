#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "list.h"


char *strdup(const char *);

list_t *make_list(char *str) {

	list_t *p = (list_t *)malloc(sizeof(list_t));
	assert(p != NULL);
	p->name = strdup(str);
	p->next = NULL;
	return p;	

}

void free_list(list_t *p) {
	// free(p->name);
	// free_list(p->arg_list);
	// free_list(p->next);
	// free(p);
}

void list_print(list_t *top) {

	list_t *q = top;
	
	while (q != NULL) {
		printf("[%s] -> ", q->name);
		q = q->next;
	}
	printf("\n");
}

/* insert to top of ll 
 * returns new top of linked list
 * */
list_t *list_insert(list_t *top, char *name) {

	list_t *p = make_list(name); // new node to store names
	
	if (top != NULL) {
		p->next = top;
	}
	return top = p;
}

/* search linked list for str
 * returns pointer to node (where str is) or NULL
 */
list_t *list_search(list_t *top, char *str) {

	list_t *q = top;
	
	while (q != NULL) {
		if (!strcmp(q->name, str)) {
			return q;
		}
		q = q->next;
	}
	return NULL;	
}
