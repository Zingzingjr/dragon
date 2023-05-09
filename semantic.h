#ifndef SEMANTIC_H
#define SEMANTIC_H

#define TYPE_ERROR -1

list_t *semantic_lookup(scope_t *scope, char *name);
void semantic_set_type(tree_t *id_list, int type_val);
int type_of(tree_t *t);
void semantic_set(scope_t *scope, char *name);
char *int_to_type(int type);
void type_check(int, int);
void double_check(scope_t *, char *);
void declare_check(list_t *, char *);
int semantic_validate_expr(tree_t *t);
list_t* tree_to_list(tree_t *t);
#endif
