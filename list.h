#ifndef LIST_H
#define LIST_H


/* linked list data structure */
typedef struct list_s {

	char *name; /*identifier name */
	int class; /* simple variable, function name, array name */
	int type; /* type information: INTEGRAL, RATIONAL, ARRAY[LOWER, UPPER]: incomplete*/
	/* addtional info 
	FUNC, PROC: arguments and their sequence of expected types (which includes #arguments)
	code generation: */
	struct list_s *arg_list; //list of types
	struct list_s *next;

} list_t;


/* constructor/destructor */
list_t *make_list(char *);
void free_list(list_t *);
void list_print(list_t *);

/* search/insert */
list_t *list_insert(list_t *, char *);
list_t *list_search(list_t *, char *);


#endif
