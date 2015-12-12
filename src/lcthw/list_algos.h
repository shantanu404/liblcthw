#ifndef _lcthw_list_algos_h
#define _lcthw_list_algos_h
#include <lcthw/list.h>

typedef int (*List_compare)(const void *a, const void *b);

int List_bubble_sort(List *list, List_compare compare_func);

List *List_selection_sort(List *list, List_compare compare_func);

#endif
