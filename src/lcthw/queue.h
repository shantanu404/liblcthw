#ifndef _lcthw_stack_h
#define _lcthw_stack_h

#include <lcthw/list.h>

#define Queue List

#define Queue_create() (List_create())
#define Queue_destroy(A) (List_destroy(A))

#define Queue_peek(A) (List_first(A))
#define Queue_count(A) (List_count(A))

#define Queue_send(A, B) (List_push(A, B))
#define Queue_recv(A) (List_shift(A))

#define QUEUE_FOREACH(A, B) LIST_FOREACH(A, first, next, B)

#endif

