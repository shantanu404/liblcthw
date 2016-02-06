#ifndef _lcthw_stack_h
#define _lcthw_stack_h

#include <lcthw/list.h>

#define Stack List

#define Stack_create() (List_create())
#define Stack_destroy(A) (List_destroy(A))

#define Stack_peek(A) (List_first(A))
#define Stack_count(A) (List_count(A))

#define Stack_push(A, B) (List_unshift(A, B))
#define Stack_pop(A) (List_shift(A))

#define STACK_FOREACH(A, B) LIST_FOREACH(A, first, next, B)

#endif

